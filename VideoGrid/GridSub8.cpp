﻿#include "VideoGrid.h"

//-------------------------------------------------------------------------------------------------
void BlockBevelSubTwo8(gridParam *prm)
{
	A_long x0,x1,y0,y1;
	A_long target, target2;
	x0 = prm->x;
	x1 = prm->x + 1;
	y0 = prm->y;
	y1 = prm->y + 1;
	if ( (x1<0)||(x0>=prm->width)||(y1<0)||(y0>=prm->height) ) return;
	
	PF_Pixel8 *data;
	data = (PF_Pixel8 *)prm->data;
	target = x0 + y0*prm->widthTrue;
	target2 = target;
	if ( (x0>=0)&&(y0>=0) ){
		data[target] = lineBright8(data[target],prm->info.hilight);
	}
	if ( (x1<prm->width)&&(y0>=0) ){
		target2 = target +1;
		data[target2] = lineBright8(data[target2],prm->info.hilight);
	}
	if ( (x0>=0)&&(y1<prm->height) ){
		target2 = target + prm->widthTrue;	
		data[target2] = lineBright8(data[target2],prm->info.hilight);
	}
	if ( (x1<prm->width)&&(y1<prm->height) ){
		target2 = target + 1 + prm->widthTrue;	
		data[target2] = lineBright8(data[target2],prm->info.shadow);
	}
}
//-------------------------------------------------------------------------------------------------
void BlockBevelSub8(gridParam *prm)
{
	A_long x0,x1,y0,y1;
	A_long target,i;
	A_long w,s0,s1;

	if (prm->info.gridSize<=2){
		BlockBevelSubTwo8(prm);
		return;
	}

	x0 = prm->x ;
	x1 = prm->x + prm->info.gridSize -1;
	y0 = prm->y;
	y1 = prm->y + prm->info.gridSize -1;
	if ( (x1<0)||(x0>=prm->width)||(y1<0)||(y0>=prm->height) ) return;

	PF_Pixel8 *data;
	data = (PF_Pixel8 *)prm->data;

	if (y0>=0) {
		if (x0<0) { s0 = 0; }else{ s0 = x0; }
		if (x1>=prm->width) { s1 = prm->width-1; }else{ s1 = x1; }
		w = s1 - s0 + 1;
		target = s0 + (y0*prm->widthTrue);
		for (i=0 ; i< w ;i++){
			data[target] = lineBright8(data[target],prm->info.hilight);
			target++;
		}
	}
	if (x0>=0) {
		if (y0<0) { s0 = 0; }else{ s0 = y0; }
		s0+=1;
		if (y1>=prm->height) { s1 = prm->height-1; }else{ s1 = y1; }
		w = s1 - s0 + 1;
		target = x0 + (s0*prm->widthTrue);
		for (i=0 ; i< w ;i++){
			data[target] = lineBright8(data[target],prm->info.hilight);
			target+=prm->widthTrue;
		}
	}

	if (y1<prm->height) {
		if (x0<0) { s0 = 0; }else{ s0 = x0; }
		s0+=1;
		if (x1>=prm->width) { s1 = prm->width-1; }else{ s1 = x1; }
		w = s1 - s0 + 1;
		target = s0 + (y1*prm->widthTrue);
		for (i=0 ; i< w ;i++){
			data[target] = lineBright8(data[target],prm->info.shadow);
			target++;
		}
	}

	if (x1<prm->width) {
		if (y0<0) { s0 = 0; }else{ s0 = y0; }
		s0+=1;
		if (y1>=prm->height) { s1 = prm->height-1; }else{ s1 = y1; }
		s1-=1;
		w = s1 - s0 + 1;
		target = x1 + (s0*prm->widthTrue);
		for (i=0 ; i< w ;i++){
			data[target] = lineBright8(data[target],prm->info.shadow);
			target+=prm->widthTrue;
		}
	}


}
//-------------------------------------------------------------------------------------------------
void BlockBevel8(gridParam *prm)
{
	A_long i;
	
	gridParam pr;
	pr.data				= prm->data;
	pr.info.gridSize	= prm->info.gridSize;
	pr.info.isMosaic	= prm->info.isMosaic;
	pr.info.hilight		= prm->info.hilight;
	pr.info.shadow		= prm->info.shadow;
	pr.info.height		= prm->info.height;
	pr.width			= prm->width;
	pr.widthTrue		= prm->widthTrue;
	pr.height			= prm->height;
	pr.x				= prm->x;
	pr.y				= prm->y;

	for (i=0 ;i<pr.info.height;i++){
		if (pr.info.gridSize<2) break;
		BlockBevelSub8(&pr);
		pr.info.gridSize -=2;
		pr.x += 1;
		pr.y += 1;
	}
}
//-------------------------------------------------------------------------------------------------
void BlockMosaic8(gridParam *prm)
{
	gridParam pr;
	pr.data				= prm->data;
	pr.info.gridSize	= prm->info.gridSize;
	pr.info.isMosaic	= prm->info.isMosaic;
	pr.info.hilight		= prm->info.hilight;
	pr.info.shadow		= prm->info.shadow;
	pr.info.height		= prm->info.height;
	pr.width			= prm->width;
	pr.widthTrue		= prm->widthTrue;
	pr.height			= prm->height;
	pr.x				= prm->x;
	pr.y				= prm->y;

	A_long x0,x1,y0,y1;
	A_long target,i,j;
	A_long r,g,b,a;
	A_long w,h;
	A_long offset;

	PF_Pixel8 *data;
	data =(PF_Pixel8 *)(pr.data);
	PF_Pixel col;

	//モザイクかける範囲を求める
	x0 = pr.x ;
	x1 = pr.x + pr.info.gridSize -1;
	y0 = pr.y;
	y1 = pr.y + pr.info.gridSize -1;

	if ( (x1<0)||(x0>=pr.width)||(y1<0)||(y0>=pr.height) ) return;

	//範囲をクリッピング
	if (x0<0) x0 = 0;
	if (y0<0) y0 = 0;
	if (x1>=pr.width)  x1 = pr.width -1;
	if (y1>=pr.height) y1 = pr.height -1;
	
	w	= x1 - x0 + 1;
	h	= y1 - y0 + 1;
	//rgaの平均値を求める
	r=g=b=a=0;
	A_long count=0;
	offset = pr.widthTrue - w;
	target = x0 + (y0 * pr.widthTrue);
	for (j=0; j<h;j++){
		for (i=0; i<w;i++){
			col = data[target];
			a += (A_long)col.alpha;
			b += (A_long)col.blue;
			g += (A_long)col.green;
			r += (A_long)col.red;
			target++;
			count++;
		}
		target+= offset;
	}
	col.alpha	= RoundByteLong(a / count);
	col.blue	= RoundByteLong(b / count);
	col.green	= RoundByteLong(g / count);
	col.red		= RoundByteLong(r / count);

	//塗りつぶす
	target = x0 + (y0 * pr.widthTrue);
	for (j=0; j<h;j++){
		for (i=0; i<w;i++){
			data[target] = col;
			target++;			
		}
		target+= offset;
	}

}
//-------------------------------------------------------------------------------------------------


