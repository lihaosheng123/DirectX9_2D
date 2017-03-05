#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "caiquan.h"
#include "score.h"
#include "input.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureCaiquan =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCaiquan =NULL;	//頂点パッファへのポインタ
D3DXVECTOR3 g_posCaiquan;	//ポリゴンの位置
D3DXVECTOR3 g_rotCaiquan;		//ポリゴンの回転角
D3DXVECTOR3 g_moveCaiquan;		//ポリゴンの移動量
int g_nCounterAnim_Caiquan;		//アンメーションカウンタ
int g_nPatternAnim_Caiquan;		//アンメーションパターンNO
float animRow_Caiquan =1.0f;
float maxAnimX_Caiquan = 3.0f;
float maxAnimY_Caiquan = 1.0f;
float CaiquanWidth = 100.0f;		//ポリゴンの幅
float CaiquanHeight = 150.0f;
float Caiquan_X = 700.0f;
float Caiquan_Y = 100.0f;
float g_fLengthCaiquan;		//ポリゴンの対角線の長さ
float g_fAngleCaiquan;		//ポリゴンの対角線の角度
float runSpeed_Caiquan =10.0f;
float animMaxnum_Caiquan = 3;
float startAnimY_Caiquan = 0;
int cnt_enemy ;
//=============================================================================
//  関数名　：InitCaiquan
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitCaiquan(void)
{
	srand ((unsigned)time(NULL));
	cnt_polygon = 0;
	cnt_enemy = 1+rand() % 3;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffCaiquan,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *Caiquan;
		g_pVtxBuffCaiquan ->Lock(0,0,(void **)&Caiquan,0);		//頂点情報へのポインタを取得
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\caiquan.png",
		&g_pTextureCaiquan);

		//bUseCaiquan = true;
		Caiquan[0].pos = D3DXVECTOR3(Caiquan_X,Caiquan_Y,0.0f);
		Caiquan[1].pos = D3DXVECTOR3(Caiquan_X+CaiquanWidth,Caiquan_Y,0.0f);
		Caiquan[2].pos = D3DXVECTOR3(Caiquan_X,Caiquan_Y+CaiquanHeight,0.0f);
		Caiquan[3].pos = D3DXVECTOR3(Caiquan_X+CaiquanWidth,Caiquan_Y+CaiquanHeight,0.0f);
		Caiquan[0].rhw = 1.0f;
		Caiquan[1].rhw = 1.0f;
		Caiquan[2].rhw = 1.0f;
		Caiquan[3].rhw = 1.0f;
		Caiquan[0].col=D3DCOLOR_RGBA(200,200,200,255);	//頂点情報格納ワーク
		Caiquan[1].col=D3DCOLOR_RGBA(200,200,200,255);
		Caiquan[2].col=D3DCOLOR_RGBA(200,200,200,255);
		Caiquan[3].col=D3DCOLOR_RGBA(200,200,200,255);

		Caiquan[0].tex = D3DXVECTOR2(0.0f, 0.0f );
		Caiquan[1].tex = D3DXVECTOR2(1.0f / maxAnimX_Caiquan,0.0f);
		Caiquan[2].tex = D3DXVECTOR2(0.0f, 1.0f / maxAnimY_Caiquan);
		Caiquan[3].tex = D3DXVECTOR2(1.0f / maxAnimX_Caiquan, 1.0f / maxAnimY_Caiquan);
		g_pVtxBuffCaiquan ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：UninitCaiquan
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitCaiquan(void)
{
	if(g_pTextureCaiquan!=NULL)
	{
		g_pTextureCaiquan->Release();
		g_pTextureCaiquan=NULL;
	}
	if(g_pVtxBuffCaiquan!=NULL)
	{
		g_pVtxBuffCaiquan->Release();		//頂点バッファの開放
		g_pVtxBuffCaiquan=NULL;
	}
}
//=============================================================================
//  関数名　：DrawCaiquan
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawCaiquan(void)
{
	/*if(bUseCaiquan == true)
	{*/
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureCaiquan);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffCaiquan,
								0,
								sizeof(VERTEX_2D)
								);

	// フェードの描画設定内容
	pDevice -> DrawPrimitive(
							  D3DPT_TRIANGLESTRIP,		// プリミティブの種類
							  0,		// 最初の頂点のインデックス
							  2			// 描画するプリミティブ数
							);
	/*}*/
	
}
//=============================================================================
//  関数名　：UpdateCaiquan1
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateCaiquan(void)
{
	g_nCounterAnim_Caiquan++;
		if(g_nCounterAnim_Caiquan == runSpeed_Caiquan )
		{
			g_nCounterAnim_Caiquan = 0;
			g_nPatternAnim_Caiquan ++;
			if(g_nPatternAnim_Caiquan == animMaxnum_Caiquan)	//パターン数
			{
				startAnimY_Caiquan = 0;//画面上
				animRow_Caiquan = 1;
				g_nPatternAnim_Caiquan = 0;
			}
			else if(g_nPatternAnim_Caiquan == 5)
			{
				animRow_Caiquan++;
				startAnimY_Caiquan += (1.0f / maxAnimY_Caiquan);
			}
			VERTEX_2D *Caiquan;
			g_pVtxBuffCaiquan ->Lock(0,0,(void **)&Caiquan,0);		//頂点情報へのポインタを取得
		Caiquan[0].pos = D3DXVECTOR3(Caiquan_X,Caiquan_Y,0.0f);
		Caiquan[1].pos = D3DXVECTOR3(Caiquan_X+CaiquanWidth,Caiquan_Y,0.0f);
		Caiquan[2].pos = D3DXVECTOR3(Caiquan_X,Caiquan_Y+CaiquanHeight,0.0f);
		Caiquan[3].pos = D3DXVECTOR3(Caiquan_X+CaiquanWidth,Caiquan_Y+CaiquanHeight,0.0f);

			Caiquan[0].tex.x = g_nPatternAnim_Caiquan *(1.0f / maxAnimX_Caiquan);
			Caiquan[0].tex.y = startAnimY_Caiquan;

			Caiquan[1].tex.x = (g_nPatternAnim_Caiquan * (1.0f /  maxAnimX_Caiquan)) + (1.0f / maxAnimX_Caiquan);
			Caiquan[1].tex.y = startAnimY_Caiquan;
				
			Caiquan[2].tex.x = g_nPatternAnim_Caiquan * (1.0f /  maxAnimX_Caiquan);
			Caiquan[2].tex.y = animRow_Caiquan *(1.0f / maxAnimY_Caiquan);

			Caiquan[3].tex.x = (g_nPatternAnim_Caiquan * (1.0f /  maxAnimX_Caiquan)) + (1.0f / maxAnimX_Caiquan);
			Caiquan[3].tex.y = animRow_Caiquan *(1.0f / maxAnimY_Caiquan);
	g_pVtxBuffCaiquan ->Unlock();	//LOCK
		}
}
//if(GetKeyboardTrigger(DIK_E))
//{
//	switch(cnt_enemy)
//	{
//	case 0:
//		switch(cnt_polygon)
//		{
//			case 0:		//同じ
//			AddScore(0);
//				break;
//
//			case 1:		//負け
//				AddScore(10);
//				break;
//
//			case 2:		//勝ち
//				AddScore(100);
//				break;
//
//		}
//		break;
//
//	case 1:
//		switch(cnt_polygon)
//		{
//			case 0:		//勝ち
//				AddScore(100);
//				break;
//
//			case 1:		//同じ
//				AddScore(0);
//				break;
//
//			case 2:		//負け
//				AddScore(10);
//				break;
//
//		}
//		break;
//
//	case 2:
//		switch(cnt_polygon)
//		{
//			case 0:		//負け
//				AddScore(10);
//				break;
//
//			case 1:		//勝ち
//				AddScore(100);
//				break;
//
//			case 2:		//同じ
//				AddScore(0);
//				break;
//
//		}
//		break;
//	}
//}

