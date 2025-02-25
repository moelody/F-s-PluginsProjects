﻿//-----------------------------------------------------------------------------------
/*
	F's Plugins for VS2010/VS2012
*/
//-----------------------------------------------------------------------------------


#include "SparkGrand.h"


//-------------------------------------------------------------------------------------------------
//AfterEffextsにパラメータを通達する
//Param_Utils.hを参照のこと
static PF_Err ParamsSetup (
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output)
{
	PF_Err			err = PF_Err_NONE;
	PF_ParamDef		def;

	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(STR_SEED,	//パラメータの名前
		-30000, 				//数値入力する場合の最小値
		30000,			//数値入力する場合の最大値
		0,				//スライダーの最小値 
		1000,			//スライダーの最大値
		0,				//デフォルトの値
		ID_SEED
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(STR_SEEDPOS,	//パラメータの名前
		-30000, 				//数値入力する場合の最小値
		30000,			//数値入力する場合の最大値
		0,				//スライダーの最小値 
		1000,			//スライダーの最大値
		0,				//デフォルトの値
		ID_SEEDPOS
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(STR_SEEDMOVE,	//パラメータの名前
		-30000, 				//数値入力する場合の最小値
		30000,			//数値入力する場合の最大値
		0,				//スライダーの最小値 
		1000,			//スライダーの最大値
		0,				//デフォルトの値
		ID_SEEDMOVE
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_ANGLE(STR_OFFSET, 0, ID_OFFSET);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_FLOAT_SLIDER(STR_WIPE,	//Name
		0,						//VALID_MIN
		200,						//VALID_MAX
		0,						//SLIDER_MIN
		200,						//SLIDER_MAX
		1,						//CURVE_TOLERANCE
		100,						//DFLT
		1,						//PREC
		0,						//DISP
		0,						//WANT_PHASE
		ID_WIPE
	);
	//----------------------------------------------------------------
	//位置の指定
	AEFX_CLR_STRUCT(def);
	PF_ADD_POINT(STR_START,			/*"New Center"*/
		25,	// X
		10,	// Y
		0,	// Flag
		ID_START
	);
	//----------------------------------------------------------------
	//位置の指定
	AEFX_CLR_STRUCT(def);
	PF_ADD_POINT(STR_LAST1,			/*"New Center"*/
		15,	// X
		90,	// Y
		0,	// Flag
		ID_LAST1
	);
	//----------------------------------------------------------------
	//位置の指定
	AEFX_CLR_STRUCT(def);
	PF_ADD_POINT(STR_LAST2,			/*"New Center"*/
		85,	// X
		90,	// Y
		0,	// Flag
		ID_LAST2
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(STR_DRAWCOUNT,	//パラメータの名前
		1, 				//数値入力する場合の最小値
		10,			//数値入力する場合の最大値
		1,				//スライダーの最小値 
		5,				//スライダーの最大値
		2,				//デフォルトの値
		ID_DRAW_COUNT
	);
	
	
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(STR_START_RX,	//パラメータの名前
		0, 			//数値入力する場合の最小値
		400,			//数値入力する場合の最大値
		0,				//スライダーの最小値 
		100,			//スライダーの最大値
		10,			//デフォルトの値
		ID_START_RX
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(STR_START_RY,	//パラメータの名前
		0, 			//数値入力する場合の最小値
		400,			//数値入力する場合の最大値
		0,				//スライダーの最小値 
		100,			//スライダーの最大値
		10,			//デフォルトの値
		ID_START_RY
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(STR_LAST_RX,	//パラメータの名前
		0, 			//数値入力する場合の最小値
		400,			//数値入力する場合の最大値
		0,				//スライダーの最小値 
		100,			//スライダーの最大値
		10,			//デフォルトの値
		ID_LAST_RX
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(STR_LAST_RY,	//パラメータの名前
		0, 			//数値入力する場合の最小値
		400,			//数値入力する場合の最大値
		0,				//スライダーの最小値 
		100,			//スライダーの最大値
		10,			//デフォルトの値
		ID_LAST_RY
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_FLOAT_SLIDER(STR_LINE_SIZE,	//Name
		0,						//VALID_MIN
		300,						//VALID_MAX
		0,						//SLIDER_MIN
		100,						//SLIDER_MAX
		1,						//CURVE_TOLERANCE
		15,						//DFLT
		1,						//PREC
		0,						//DISP
		0,						//WANT_PHASE
		ID_LINE_SIZE
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(STR_LINE_MOVE,	//パラメータの名前
		0, 				//数値入力する場合の最小値
		2000,			//数値入力する場合の最大値
		0,				//スライダーの最小値 
		100,				//スライダーの最大値
		60,				//デフォルトの値
		ID_LINE_MOVE
	);	
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(STR_FOLDCOUNT,	//パラメータの名前
		2, 				//数値入力する場合の最小値
		9,			//数値入力する場合の最大値
		2,				//スライダーの最小値 
		6,				//スライダーの最大値
		4,				//デフォルトの値
		ID_FOLD_COUNT
	);	
	
	//----------------------------------------------------------------
//色の指定
	AEFX_CLR_STRUCT(def);
	PF_ADD_COLOR(STR_COLOR,
		0xFF,
		0xFF,
		0xFF,
		ID_COLOR
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_CHECKBOX(STR_BLEND,
		STR_ON,
		FALSE,
		0,
		ID_BLEND
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
	PF_Err				err = PF_Err_NONE;
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
	PF_Err 	err = PF_Err_NONE;
	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err
RedBlendIn8(
	refconType	refcon,
	A_long		xL,
	A_long		yL,
	PF_Pixel* inP,
	PF_Pixel* outP)
{
	PF_Err			err = PF_Err_NONE;

	A_u_char v = outP->alpha;

	if (v <= 0) {
		*outP = *inP;
	}
	else {
		PF_FpLong v0 = (PF_FpLong)inP->alpha / PF_MAX_CHAN8;
		PF_FpLong r0 = (PF_FpLong)inP->red * v0;
		PF_FpLong g0 = (PF_FpLong)inP->green * v0;
		PF_FpLong b0 = (PF_FpLong)inP->blue * v0;

		PF_FpLong v1 = (PF_FpLong)outP->alpha / PF_MAX_CHAN8;
		PF_FpLong r1 = (PF_FpLong)outP->red * v1;
		PF_FpLong g1 = (PF_FpLong)outP->green * v1;
		PF_FpLong b1 = (PF_FpLong)outP->blue * v1;

		r1 = r0 * (1 - v1) + r1 * v1;
		g1 = g0 * (1 - v1) + g1 * v1;
		b1 = b0 * (1 - v1) + b1 * v1;

		v1 = v0 + v1 - v0 * v1;

		r1 /= v1;
		g1 /= v1;
		b1 /= v1;

		outP->alpha = RoundByteFpLong(v1*PF_MAX_CHAN8);
		outP->red = RoundByteFpLong(r1);
		outP->green = RoundByteFpLong(g1);
		outP->blue = RoundByteFpLong(b1);

	}

	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err
RedBlendIn16(
	refconType	refcon,
	A_long		xL,
	A_long		yL,
	PF_Pixel16* inP,
	PF_Pixel16* outP)
{
	PF_Err			err = PF_Err_NONE;

	A_u_short v = outP->alpha;

	if (v <= 0) {
		*outP = *inP;
	}
	else {
		PF_FpLong v0 = (PF_FpLong)inP->alpha / PF_MAX_CHAN16;
		PF_FpLong r0 = (PF_FpLong)inP->red * v0;
		PF_FpLong g0 = (PF_FpLong)inP->green * v0;
		PF_FpLong b0 = (PF_FpLong)inP->blue * v0;

		PF_FpLong v1 = (PF_FpLong)outP->alpha / PF_MAX_CHAN16;
		PF_FpLong r1 = (PF_FpLong)outP->red * v1;
		PF_FpLong g1 = (PF_FpLong)outP->green * v1;
		PF_FpLong b1 = (PF_FpLong)outP->blue * v1;

		r1 = r0 * (1 - v1) + r1 * v1;
		g1 = g0 * (1 - v1) + g1 * v1;
		b1 = b0 * (1 - v1) + b1 * v1;

		v1 = v0 + v1 - v0 * v1;

		r1 /= v1;
		g1 /= v1;
		b1 /= v1;

		outP->alpha = RoundShortFpLong(v1 * PF_MAX_CHAN16);
		outP->red = RoundShortFpLong(r1);
		outP->green = RoundShortFpLong(g1);
		outP->blue = RoundShortFpLong(b1);

	}

	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err
RedBlendIn32(
	refconType	refcon,
	A_long		xL,
	A_long		yL,
	PF_PixelFloat* inP,
	PF_PixelFloat* outP)
{
	PF_Err			err = PF_Err_NONE;

	PF_FpShort v = outP->alpha;

	if (v <= 0) {
		*outP = *inP;
	}
	else {
		PF_FpLong v0 = (PF_FpLong)inP->alpha;
		if (v0 > 1) v0 = 1;
		PF_FpLong r0 = (PF_FpLong)inP->red * v0;
		PF_FpLong g0 = (PF_FpLong)inP->green * v0;
		PF_FpLong b0 = (PF_FpLong)inP->blue * v0;

		PF_FpLong v1 = (PF_FpLong)outP->alpha;
		if (v1 > 1) v1 = 1;
		PF_FpLong r1 = (PF_FpLong)outP->red * v1;
		PF_FpLong g1 = (PF_FpLong)outP->green * v1;
		PF_FpLong b1 = (PF_FpLong)outP->blue * v1;

		r1 = r0 * (1 - v1) + r1 * v1;
		g1 = g0 * (1 - v1) + g1 * v1;
		b1 = b0 * (1 - v1) + b1 * v1;

		v1 = v0 + v1 - v0 * v1;

		r1 /= v1;
		g1 /= v1;
		b1 /= v1;

		outP->alpha = RoundFpShortDouble(v1);
		outP->red = RoundFpShortDouble(r1);
		outP->green = RoundFpShortDouble(g1);
		outP->blue = RoundFpShortDouble(b1);

	}

	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err GetParams(CFsAE *ae, ParamInfo *infoP)
{
	PF_Err		err 		= PF_Err_NONE;


	PF_InData* in_data = ae->in_data;
	PF_FpLong ds = (PF_FpLong)in_data->downsample_x.num / (PF_FpLong)in_data->downsample_x.den;

	ERR(ae->GetADD(ID_SEED, &infoP->seed));
	infoP->seed %= 30000;
	if (infoP->seed < 0)infoP->seed += 30000;

	ERR(ae->GetADD(ID_SEEDPOS, &infoP->seedPos));
	infoP->seedPos %= 30000;
	if (infoP->seedPos < 0)infoP->seedPos += 30000;

	ERR(ae->GetADD(ID_SEEDMOVE, &infoP->seedMove));
	infoP->seedMove %= 30000;
	if (infoP->seedMove < 0)infoP->seedMove += 30000;

	PF_Fixed r;
	ERR(ae->GetANGLE(ID_OFFSET, &r));
	if (!err) {
		r = r % (360L << 16);
		if (r < 0) r += (360L << 16);
		infoP->offset = (PF_FpLong)r / 65536;
	}
	ERR(ae->GetFLOAT(ID_WIPE, &infoP->wipe));
	if (!err) {
		infoP->wipe /= 100;
		if (infoP->wipe < 0) infoP->wipe = 0;
		else if (infoP->wipe > 2) infoP->wipe = 2;
	}

	PF_FixedPoint v;

	ERR(ae->GetFIXEDPOINT(ID_START, &v));
	if (!err) {
		infoP->start.p.x = (int)((double)v.x / 65536 + 0.5);
		infoP->start.p.y = (int)((double)v.y / 65536 + 0.5);
	}
	ERR(ae->GetFIXEDPOINT(ID_LAST1, &v));
	if (!err) {
		infoP->last1.p.x = (int)((double)v.x / 65536 + 0.5);
		infoP->last1.p.y = (int)((double)v.y / 65536 + 0.5);
	}
	ERR(ae->GetFIXEDPOINT(ID_LAST2, &v));
	if (!err) {
		infoP->last2.p.x = (int)((double)v.x / 65536 + 0.5);
		infoP->last2.p.y = (int)((double)v.y / 65536 + 0.5);
	}
	ERR(ae->GetADD(ID_FOLD_COUNT, &infoP->foldCount));


	ERR(ae->GetADD(ID_START_RX, &infoP->startRandX));
	if (!err) {
		infoP->startRandX = (A_long)((PF_FpLong)infoP->startRandX * ds + 0.5);
	}
	ERR(ae->GetADD(ID_START_RY, &infoP->startRandY));
	if (!err) {
		infoP->startRandY = (A_long)((PF_FpLong)infoP->startRandY * ds + 0.5);
	}
	ERR(ae->GetADD(ID_LAST_RX, &infoP->lastRandX));
	if (!err) {
		infoP->lastRandX = (A_long)((PF_FpLong)infoP->lastRandX * ds + 0.5);
	}
	ERR(ae->GetADD(ID_LAST_RY, &infoP->lastRandY));
	if (!err) {
		infoP->lastRandY = (A_long)((PF_FpLong)infoP->lastRandY * ds + 0.5);
	}

	ERR(ae->GetFLOAT(ID_LINE_SIZE, &infoP->lineSize));
	if (!err) {
		infoP->lineSize = (A_long)((PF_FpLong)infoP->lineSize * ds + 0.5);
	}
	ERR(ae->GetADD(ID_LINE_MOVE, &infoP->lineMove));
	if (!err) {
		infoP->lineMove = (A_long)((PF_FpLong)infoP->lineMove * ds + 0.5);
	}

	ERR(ae->GetADD(ID_DRAW_COUNT, &infoP->drawCount));

	ERR(ae->GetCOLOR(ID_COLOR, &infoP->color));
	ERR(ae->GetCHECKBOX(ID_BLEND, &infoP->blend));


	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err 
	Exec (CFsAE *ae , ParamInfo *infoP)
{
	PF_InData* in_data = ae->in_data;

	PF_Err	err = PF_Err_NONE;
	infoP->frame = ae->frame();
	A_long r = infoP->seed + infoP->seedPos;
	r %= 30000;
	if (r < 0) r += 30000;
	init_xorShift(r);
	r = infoP->seed + infoP->seedMove;
	r %= 30000;
	if (r < 0) r += 30000;
	init_xorShiftM(r);

	CLineDraw ld(ae->output, ae->in_data,ae->pixelFormat());

	for (A_long dc = 0; dc < infoP->drawCount; dc++)
	{

		PointInfo p0 = infoP->start;
		//中心の1本は中心へ
		PointInfo p1;
		if (dc == 0) 
		{
			p1 = ld.Points.PointInter(infoP->last1, infoP->last2);
			xorShiftMDouble();
		}
		else {
			p1 = ld.Points.PointInterRandom(infoP->last1, infoP->last2);
		}

		p0 = ld.Points.Random(p0, infoP->startRandX, infoP->startRandY);
		p1 = ld.Points.Random(p1, infoP->lastRandX, infoP->lastRandY);
		ld.Points.Clear();
		ld.Points.Push(p0);
		ld.Points.Push(p1);
		A_long depth = 0;
		for (A_long fc = 0; fc < infoP->foldCount; fc++)
		{
			ld.Points.CalcCenterPos(
				infoP->lineSize,
				infoP->lineMove,
				infoP->offset,
				depth
			);
			depth++;

		}
		ld.Points.Wipe(infoP->wipe);
		ld.Line();
		ld.Points.Backup();
		A_long pcnt = ld.Points.Count();
		A_long ff = infoP->foldCount;
		ff--;
		A_long rc = 0;
		A_long rcm = 0;
		while (ff>2)
		{
			A_long pos = pcnt - (A_long)PF_POW(2, ff);
			ld.Points.RemoveTail(pos);
			p1 = ld.Points.PointInterRandom(infoP->last1, infoP->last2);
			rcm++;
			p1 = ld.Points.Random(p1, infoP->lastRandX, infoP->lastRandY);
			rc += 2;
			ld.Points.Push(p1);
			A_long depth = 0;
			for (A_long fc = 0; fc < ff; fc++)
			{
				ld.Points.CalcCenterPos2(
					infoP->lineSize * 0.7,
					infoP->lineMove*4/3,
					infoP->offset,
					depth,
					pos-1
				);
				rcm+=3;
				depth++;
			}
			ld.Points.Wipe(infoP->wipe);
			ld.Line();
			ff--;
		}
		if (rc < 50) {
			for (A_long i = 0; i < 50-rc; i++)
			{
				xorShiftDouble();
			}
		}
		if (rcm < 50) {
			for (A_long i = 0; i < 50 - rcm; i++)
			{
				xorShiftMDouble();
			}
		}

	}


	ld.Colorize(infoP->color);

	if (ae->pixelFormat() == PF_PixelFormat_ARGB128) {
		if (infoP->blend == TRUE) {
			ERR(ae->iterate32((refconType)infoP, RedBlendIn32));
		}

	}
	else if (ae->pixelFormat() == PF_PixelFormat_ARGB64) {
		if (infoP->blend == TRUE) {
			ERR(ae->iterate16((refconType)infoP, RedBlendIn16));
		}
	}
	else if (ae->pixelFormat() == PF_PixelFormat_ARGB32) {
		
		if (infoP->blend == TRUE) {
			ERR(ae->iterate8((refconType)infoP, RedBlendIn8));
		}
	}

	return err;
}

//-------------------------------------------------------------------------------------------------
//レンダリングのメイン
/*
	SmartFXに対応していないホスト(After Effects7以前のもの)はこの関数が呼び出されて描画する
	この関数を書いておけば一応v6.5対応になる
*/
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
		ParamInfo info;
		ERR(GetParams(&ae,&info));
		ERR(Exec(&ae,&info));
	}
	return err;
}
//-----------------------------------------------------------------------------------
/*
	SmartFX対応の場合、まずこの関数が呼ばれてパラメータの獲得を行う
*/
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
#endif
//-----------------------------------------------------------------------------------
#if defined(SUPPORT_SMARTFX)
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

#include "Fs_Entry.h"
