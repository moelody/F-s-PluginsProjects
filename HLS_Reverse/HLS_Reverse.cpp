﻿//-----------------------------------------------------------------------------------
/*
	F's Plugins for VS2010/VS2012
*/
//-----------------------------------------------------------------------------------

#include "HLS_Reverse.h"
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
static PF_Err 
About (	
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	PF_Err	err				= PF_Err_NONE;
	CFsAE ae;
	err = ae.About(in_data,out_data,params,output);
	return err;
}
//-----------------------------------------------------------------------------------
static PF_Err 
GlobalSetup (
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	PF_Err	err				= PF_Err_NONE;
	CFsAE ae;
	err = ae.GlobalSetup(in_data,out_data,params,output);
	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err GlobalSetdown(
	PF_InData	*in_data)
{
	PF_Err	err				= PF_Err_NONE;
	CFsAE ae;
	err = ae.GlobalSetdown(in_data);
	return PF_Err_NONE;
}

//-------------------------------------------------------------------------------------------------
static PF_Err SequenceSetup (
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{

	return PF_Err_NONE;
}
//-------------------------------------------------------------------------------------------------
static PF_Err SequenceSetdown (
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	return PF_Err_NONE;
}

//-------------------------------------------------------------------------------------------------
static PF_Err SequenceResetup (
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	return PF_Err_NONE;
}

//-------------------------------------------------------------------------------------------------
static PF_Err 
ParamsSetup (
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output)
{
	PF_Err			err = PF_Err_NONE;
	PF_ParamDef		def;
	//----------------------------------------------------------------
	//チェックボックス
	AEFX_CLR_STRUCT(def);
	PF_ADD_CHECKBOX(STR_HUE,
					STR_REV,
					FALSE,
					0,
					ID_HUE
					);
	//----------------------------------------------------------------
	//チェックボックス
	AEFX_CLR_STRUCT(def);
	PF_ADD_CHECKBOX(STR_LUM,
					STR_REV,
					TRUE,
					0,
					ID_LUM
					);

	//----------------------------------------------------------------
	//チェックボックス
	AEFX_CLR_STRUCT(def);
	PF_ADD_CHECKBOX(STR_SAT,
					STR_REV,
					FALSE,
					0,
					ID_SAT
					);

	//----------------------------------------------------------------
	//固定小数のスライダーバー
	AEFX_CLR_STRUCT(def);
	PF_ADD_FIXED(	STR_ORG_BLEND,	//パラメータの名前
					0, 				//数値入力する場合の最小値
					100,			//数値入力する場合の最大値
					0,				//スライダーの最小値 
					100,			//スライダーの最大値
					0,				//デフォルトの値
					3,				//数値表示に関するフラグ 
					0,
					0,
					ID_ORG_BLEND
					);

	//----------------------------------------------------------------
	out_data->num_params = 	ID_NUM_PARAMS; 

	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err
HandleChangedParam(
	PF_InData					*in_data,
	PF_OutData					*out_data,
	PF_ParamDef					*params[],
	PF_LayerDef					*outputP,
	PF_UserChangedParamExtra	*extraP)
{
	PF_Err				err					= PF_Err_NONE,
						err2				= PF_Err_NONE;
	/*
	try{
		CFsAE ae;
		err =ae.HandleChangedParam(in_data,out_data,params,outputP,extraP,ID_NUM_PARAMS);
		if (!err){
			PF_Boolean b = FALSE;
			ERR(ae.GetCHECKBOX(ID_NOISE_FRAME,&b));
			ERR(ae.UI_DISABLE(ID_NOISE_OFFSET, b));
			if (!err){
				out_data->out_flags |= PF_OutFlag_FORCE_RERENDER | PF_OutFlag_REFRESH_UI;
			}
		}
	}catch ( PF_Err & errP){
		err = errP;
	}
	*/
	return err;
}
//-----------------------------------------------------------------------------------
static PF_Err
QueryDynamicFlags(	
	PF_InData		*in_data,	
	PF_OutData		*out_data,	
	PF_ParamDef		*params[],	
	void			*extra)	
{
	PF_Err 	err 	= PF_Err_NONE,
			err2 	= PF_Err_NONE;
	//PF_OutFlag_NON_PARAM_VARYの値をout_flagsへ設定して
	//毎フレームごとの描画をするか切り替える。
	/*
	CFsAE ae;
	err = ae.QueryDynamicFlags(in_data,out_data,params,extra,ID_NUM_PARAMS);
	if (!err){
		PF_ParamDef def;
		AEFX_CLR_STRUCT(def);
		ERR(ae.checkout_param(ID_NOISE_FRAME,&def));
		ERR(ae.SetOutFlag_NON_PARAM_VARY((PF_Boolean)def.u.bd.value));
		ERR(ae.checkin_param(&def));
	}
	*/
	return err;
}
//-----------------------------------------------------------------------------------
static PF_Err 
FilterImage8 (
	refconType		refcon, 
	A_long		xL, 
	A_long		yL, 
	PF_Pixel8	*inP, 
	PF_Pixel8	*outP)
{
	PF_Err			err = PF_Err_NONE;
	ParamInfo *	niP		= reinterpret_cast<ParamInfo*>(refcon);
					
	if (niP){
		PF_PixelFloat p;
		p.blue	= (PF_FpShort)inP->blue	/ PF_MAX_CHAN8;
		p.green	= (PF_FpShort)inP->green/ PF_MAX_CHAN8;
		p.red	= (PF_FpShort)inP->red	/ PF_MAX_CHAN8;
		HLSA hls = RGBtoHLS(p);
		if (niP->h) hls.H = 1.0 - hls.H;
		if (niP->l) hls.L = 1.0 - hls.L;
		if (niP->s) hls.S = 1.0 - hls.S;
		p = HLStoRGB(hls);
		outP->alpha = inP->alpha;
		A_u_char r = (A_u_char)(PF_MAX_CHAN8 * p.red);  
		A_u_char g = (A_u_char)(PF_MAX_CHAN8 * p.green);  
		A_u_char b = (A_u_char)(PF_MAX_CHAN8 * p.blue); 
		if (  niP->org_blend  ==0){
			outP->red	= r;
			outP->green	= g;
			outP->blue	= b;
		}else{
			PF_FpLong k = 1 - niP->org_blend;
			outP->red	= RoundByteFpLong( (PF_FpLong)inP->red   * niP->org_blend + (PF_FpLong)r * k);
			outP->green	= RoundByteFpLong( (PF_FpLong)inP->green * niP->org_blend + (PF_FpLong)g * k);
			outP->blue	= RoundByteFpLong( (PF_FpLong)inP->blue  * niP->org_blend + (PF_FpLong)b * k);
		}
	}

	return err;
}

//-----------------------------------------------------------------------------------
static PF_Err 
FilterImage16 (
	refconType		refcon, 
	A_long		xL, 
	A_long		yL, 
	PF_Pixel16	*inP, 
	PF_Pixel16	*outP)
{
	PF_Err			err = PF_Err_NONE;
	ParamInfo *	niP		= reinterpret_cast<ParamInfo*>(refcon);
					
	if (niP){
		PF_PixelFloat p;
		p.blue	= (PF_FpShort)inP->blue	/ PF_MAX_CHAN16;
		p.green	= (PF_FpShort)inP->green/ PF_MAX_CHAN16;
		p.red	= (PF_FpShort)inP->red	/ PF_MAX_CHAN16;
		HLSA hls = RGBtoHLS(p);
		if (niP->h) hls.H = 1.0 - hls.H;
		if (niP->l) hls.L = 1.0 - hls.L;
		if (niP->s) hls.S = 1.0 - hls.S;
		p = HLStoRGB(hls);
		outP->alpha = inP->alpha;
		A_u_short r = (A_u_short)(PF_MAX_CHAN16 * p.red);  
		A_u_short g = (A_u_short)(PF_MAX_CHAN16 * p.green);  
		A_u_short b = (A_u_short)(PF_MAX_CHAN16 * p.blue);  
		if ( niP->org_blend ==0){
			outP->red	= r;
			outP->green	= g;
			outP->blue	= b;
		}else{
			PF_FpLong k = 1 - niP->org_blend;
			outP->red	= RoundShortFpLong( (PF_FpLong)inP->red   * niP->org_blend + (PF_FpLong)r * k);
			outP->green	= RoundShortFpLong( (PF_FpLong)inP->green * niP->org_blend + (PF_FpLong)g * k);
			outP->blue	= RoundShortFpLong( (PF_FpLong)inP->blue  * niP->org_blend + (PF_FpLong)b * k);
		}
	}

	return err;
}
//-----------------------------------------------------------------------------------
static PF_Err 
FilterImage32 (
	refconType		refcon, 
	A_long		xL, 
	A_long		yL, 
	PF_PixelFloat	*inP, 
	PF_PixelFloat	*outP)
{
	PF_Err			err = PF_Err_NONE;
	ParamInfo *	niP		= reinterpret_cast<ParamInfo*>(refcon);
					
	if (niP){
		PF_PixelFloat p;
		p.blue	= (PF_FpShort)inP->blue;
		p.green	= (PF_FpShort)inP->green;
		p.red	= (PF_FpShort)inP->red;
		HLSA hls = RGBtoHLS(p);
		if (niP->h) hls.H = 1.0 - hls.H;
		if (niP->l) hls.L = 1.0 - hls.L;
		if (niP->s) hls.S = 1.0 - hls.S;
		p = HLStoRGB(hls);
		outP->alpha = inP->alpha;
		PF_FpShort r = p.red;  
		PF_FpShort g = p.green;  
		PF_FpShort b = p.blue;  
		if ( niP->org_blend ==0){
			outP->red	= r;
			outP->green	= g;
			outP->blue	= b;
		}else{
			PF_FpLong k = 1 - niP->org_blend;
			outP->red	= RoundFpShortDouble( (PF_FpLong)inP->red   * niP->org_blend + (PF_FpLong)r * k);
			outP->green	= RoundFpShortDouble( (PF_FpLong)inP->green * niP->org_blend + (PF_FpLong)g * k);
			outP->blue	= RoundFpShortDouble( (PF_FpLong)inP->blue  * niP->org_blend + (PF_FpLong)b * k);
		}
	}

	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err GetParams(CFsAE *ae, ParamInfo *infoP)
{
	PF_Err		err 		= PF_Err_NONE;

	ERR(ae->GetCHECKBOX(ID_HUE,&infoP->h));
	ERR(ae->GetCHECKBOX(ID_LUM,&infoP->l));
	ERR(ae->GetCHECKBOX(ID_SAT,&infoP->s));
	ERR(ae->GetFIXED2FpShort(ID_ORG_BLEND,&infoP->org_blend));
	if ( !err) infoP->org_blend /= 100;
	infoP->in_data = ae->in_data;
	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err 
	Exec (CFsAE *ae , ParamInfo *infoP)
{
	PF_Err	err = PF_Err_NONE;

	if ( infoP->org_blend<1){
		switch(ae->pixelFormat())
		{
		case PF_PixelFormat_ARGB128:
			ERR(ae->iterate32((refconType)infoP,FilterImage32));
			break;
		case PF_PixelFormat_ARGB64:
			ERR(ae->iterate16((refconType)infoP,FilterImage16));
			break;
		case PF_PixelFormat_ARGB32:
			ERR(ae->iterate8((refconType)infoP,FilterImage8));
			break;
		}
	}else{
		ERR(ae->CopyInToOut());
	}
	return err;
}

//-------------------------------------------------------------------------------------------------
static PF_Err 
Render ( 
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{

	PF_Err	err = PF_Err_NONE;
	PF_Handle		pixelTable = NULL;
	
	CFsAE ae(in_data,out_data,params,output,ID_NUM_PARAMS);
	err =ae.resultErr();
	if (!err){
		ERR(ae.CopyInToOut());
		ParamInfo info;
		ERR(GetParams(&ae,&info));
		ERR(Exec(&ae,&info));
	}
	return err;
}
//-----------------------------------------------------------------------------------
#if defined(SUPPORT_SMARTFX)
static PF_Err
PreRender(
	PF_InData			*in_data,
	PF_OutData			*out_data,
	PF_PreRenderExtra	*extraP)
{
	PF_Err		err 		= PF_Err_NONE;
	CFsAE ae(in_data,out_data,extraP,sizeof(ParamInfo),ID_NUM_PARAMS);
	err = ae.resultErr();
	if (!err){

		ParamInfo *infoP = reinterpret_cast<ParamInfo*>(ae.LockPreRenderData());
		if (infoP){
			ae.SetHostPreRenderData();
			ERR(GetParams(&ae,infoP));
			ERR(ae.UnSetPreRenderData());
			ae.UnlockPreRenderData();
		}else{
			err = PF_Err_OUT_OF_MEMORY;
		}
	}
	return err;
}

//-----------------------------------------------------------------------------------
static PF_Err
SmartRender(
	PF_InData				*in_data,
	PF_OutData				*out_data,
	PF_SmartRenderExtra		*extraP)
{
	PF_Err			err		= PF_Err_NONE,
					err2 	= PF_Err_NONE;

	CFsAE ae(in_data,out_data,extraP,ID_NUM_PARAMS);
	err = ae.resultErr();
	if (!err){
		ParamInfo *infoP = reinterpret_cast<ParamInfo*>(ae.LockPreRenderData());
		if (infoP){
			ERR(Exec(&ae,infoP));
			ERR2(ae.UnsetSmartRender());
			ae.UnlockPreRenderData();
		}else{
			err = PF_Err_OUT_OF_MEMORY;
		}
	}
	return err;
}
#endif
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
static PF_Err 
RespondtoAEGP ( 	
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output,
	void*			extraP)
{
	PF_Err			err = PF_Err_NONE;
	
	AEGP_SuiteHandler suites(in_data->pica_basicP);
	
	suites.ANSICallbacksSuite1()->sprintf(	out_data->return_msg, 
											"%s",	
											reinterpret_cast<A_char*>(extraP));

	return err;
}

//-----------------------------------------------------------------------------------
DllExport	PF_Err 
EntryPointFunc (
	PF_Cmd			cmd,
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output,
	void			*extraP)
{
	PF_Err		err = PF_Err_NONE;
	
	try
	{
		CFsAE ae;
		switch (cmd) {
			case PF_Cmd_ABOUT:
				err = About(in_data,out_data,params,output);
				break;
			case PF_Cmd_GLOBAL_SETUP:
				err = GlobalSetup(	in_data,out_data,params,output);
				break;
			case PF_Cmd_GLOBAL_SETDOWN:
				err = GlobalSetdown(in_data);
				break;
			case PF_Cmd_PARAMS_SETUP:
				err = ParamsSetup(	in_data,out_data,params,output);
				break;
			case PF_Cmd_SEQUENCE_SETUP:
				err = SequenceSetup(in_data,out_data,params,output);
				break;
			case PF_Cmd_SEQUENCE_SETDOWN:
				err = SequenceSetdown(in_data,out_data,params,output);
				break;
			case PF_Cmd_SEQUENCE_RESETUP:
				err = SequenceResetup(in_data,out_data,params,output);
				break;
			case PF_Cmd_RENDER:
					err = Render(in_data,out_data,params,output);
					break;
#if defined(SUPPORT_SMARTFX)
			case PF_Cmd_SMART_PRE_RENDER:
				err = PreRender(in_data,out_data,reinterpret_cast<PF_PreRenderExtra*>(extraP));
				break;
			case PF_Cmd_SMART_RENDER:
				err = SmartRender(	in_data,out_data,reinterpret_cast<PF_SmartRenderExtra*>(extraP));
				break;
#endif
			case PF_Cmd_COMPLETELY_GENERAL:
				err = RespondtoAEGP(in_data,out_data,params,output,extraP);
				break;
			case PF_Cmd_DO_DIALOG:
				//err = PopDialog(in_data,out_data,params,output);
				break;		
			case PF_Cmd_USER_CHANGED_PARAM:
				err = HandleChangedParam(	in_data,
											out_data,
											params,
											output, 
											reinterpret_cast<PF_UserChangedParamExtra*>(extraP));
				break;
			case PF_Cmd_QUERY_DYNAMIC_FLAGS:
				err = QueryDynamicFlags(in_data,
										out_data,
										params,
										reinterpret_cast<PF_UserChangedParamExtra*>(extraP));
				break;
		}
	}
	catch(PF_Err &thrown_err){
		err = thrown_err;
	}
	return err;
}

//-------------------------------------------------------------------------------------------------
