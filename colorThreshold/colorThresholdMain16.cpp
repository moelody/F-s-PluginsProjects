﻿#include "colorThreshold.h"

//*************************************************************************************************
//-------------------------------------------------------------------------------------------------
/*
	アルファを2値化
*/
PF_Err 
AlphaThreshold16 (
	refconType		refcon, 
	A_long		xL, 
	A_long		yL, 
	PF_Pixel16	*inP, 
	PF_Pixel16	*outP)
{
	PF_Err			err = PF_Err_NONE;
	ParamInfo *	niP		= reinterpret_cast<ParamInfo*>(refcon);
	PF_Pixel16 tp = {0,PF_MAX_CHAN16,PF_MAX_CHAN16,PF_MAX_CHAN16};

	A_u_char v = RoundByteLong(FS_CONVERT16TO8(inP->alpha));
	if (v >= niP->alpha_border){
		*outP = *inP;
		outP->alpha = (A_u_short)CT_TARGET;
	}else{
		*outP = tp;
	}

	return err;
}
//-------------------------------------------------------------------------------------------------
PF_Err 
AlphaFix16 (
	refconType		refcon, 
	A_long		xL, 
	A_long		yL, 
	PF_Pixel16	*inP, 
	PF_Pixel16	*outP)
{
	PF_Err			err = PF_Err_NONE;
	A_long v = (A_long)outP->alpha & CT_DECISION;
	if ( v == 0) { 
		outP->alpha = 0;
	}else{
		outP->alpha = PF_MAX_CHAN16;
	}

	return err;
}
//*************************************************************************************************
//-------------------------------------------------------------------------------------------------
/*
	指定された色ならONにする
*/
//-------------------------------------------------------------------------------------------------
PF_Err 
hslMatch16 (
	refconType		refcon, 
	A_long		xL, 
	A_long		yL, 
	PF_Pixel16	*inP, 
	PF_Pixel16	*outP)
{
	PF_Err			err = PF_Err_NONE;
	ParamInfo *	niP	= reinterpret_cast<ParamInfo*>(refcon);
	
	if ( ((A_long)outP->alpha & CT_DECISION)== CT_TARGET){
		hls o = rgbToHls( CONV16TO8(*outP));

		if (niP->main_col_count>0){
			for ( A_long i = 0; i< niP->main_col_count; i++){
				if ( colorCompare(o,niP->main_col[i],niP->hs_level,niP->l_level)==TRUE)
				{
					*outP	= niP->main_col16[i];
					A_long a =  (A_long)outP->alpha;
					a |= CT_DECISION;
					outP->alpha =  (A_u_short)a; 
					return err;
				}
			}
		}
		if(niP->sub_col_count>0){
			for ( A_long i = 0; i< niP->sub_col_count; i++){
				if ( colorCompare(o,niP->sub_col[i],niP->hs_level,niP->l_level)==TRUE)
				{
					*outP	= niP->sub_col16[i];
					A_long a =  (A_long)outP->alpha;
					a |= CT_DECISION;
					outP->alpha =  (A_u_short)a; 
					return err;
				}
			}
		}
	}
	return err;
}
//-------------------------------------------------------------------------------------------------
PF_Err 
line_search16 (
	refconType		refcon, 
	A_long		xL, 
	A_long		yL, 
	PF_Pixel16	*inP, 
	PF_Pixel16	*outP)
{
	PF_Err			err = PF_Err_NONE;
	ParamInfo *	niP		= reinterpret_cast<ParamInfo*>(refcon);
	
	A_long v = (A_long)outP->alpha; 
	if ( (v&CT_DECISION)== CT_TARGET){
		hls o = rgbToHls( CONV16TO8( *outP));
		for (A_long i=0; i<niP->main_col_count; i++ ){
			if ( colorCompare(o,niP->main_col[i],niP->main_hs[i],niP->main_l[i])==TRUE)
			{
				*outP = niP->main_col16[i];
				A_long a =  (A_long)outP->alpha;
				a |= CT_DECISION;
				outP->alpha =  (A_u_short)a; 
				break;
			}
		}

	}
	return err;
}
//-------------------------------------------------------------------------------------------------
PF_Err 
use_search16 (
	refconType		refcon, 
	A_long		xL, 
	A_long		yL, 
	PF_Pixel16	*inP, 
	PF_Pixel16	*outP)
{
	PF_Err			err = PF_Err_NONE;
	ParamInfo *	niP		= reinterpret_cast<ParamInfo*>(refcon);
	
	if ( ((A_long)outP->alpha&CT_DECISION)== CT_TARGET){
		PF_Pixel16 tbl[4];
		tbl[0] = (niP->out->getPixel16(xL  ,yL-1));
		tbl[1] = (niP->out->getPixel16(xL-1,yL  ));
		tbl[2] = (niP->out->getPixel16(xL+1,yL  ));
		tbl[3] = (niP->out->getPixel16(xL  ,yL+1));

		A_long idx = -1;
		PF_FpLong dis = 100.0;
		hls o = rgbToHls( CONV16TO8( *outP));
		for ( A_long i=0; i<4; i++)
		{
			A_long a = (A_long)tbl[i].alpha; 
			if ( (a&CT_DECISION)== CT_DECISION) {
				PF_FpLong dis2 = colorDiatance(o,tbl[i]);
				if (dis > dis2) {
					dis = dis2;
					idx = (A_long)tbl[i].alpha;
				} 
			}
		}
		if (idx>=0){
			outP->alpha = (A_u_short)((idx & 0xFC) | CT_SEARCH);
		}else{
			niP->finFlag = FALSE;
		}

	}
	return err;
}
//-------------------------------------------------------------------------------------------------
PF_Err 
use_searchSub16 (
	refconType		refcon, 
	A_long		xL, 
	A_long		yL, 
	PF_Pixel16	*inP, 
	PF_Pixel16	*outP)
{
	PF_Err			err = PF_Err_NONE;
	ParamInfo *	niP		= reinterpret_cast<ParamInfo*>(refcon);
	
	if ( ((A_long)outP->alpha&CT_DECISION)== CT_SEARCH){
		A_long idx = ((A_long)outP->alpha>>2) & 0x3F;
		if ( idx<COUNT_OF_MAIN) {
			*outP = niP->main_col16[idx];
			A_long a = (A_long)outP->alpha;
			a |= CT_DECISION;
			outP->alpha = (A_u_short)a;
		}else if ( idx< (COUNT_OF_MAIN +COUNT_OF_SUB) ){
			*outP = niP->sub_col16[idx-COUNT_OF_MAIN];
			A_long a = (A_long)outP->alpha;
			a |= CT_DECISION;
			outP->alpha = (A_u_short)a;
		}
	}
	return err;
}

