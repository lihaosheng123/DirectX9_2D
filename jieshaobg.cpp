#include "main.h"
#include "jieshaobg.h"
#include "key.h"
//グローバル変数
VERTEX_2D g_Jieshaobg[4];
LPDIRECT3DTEXTURE9 g_pTextureJieshaobg =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffJieshaobg =NULL;	//頂点パッファへのポインタ

//=============================================================================
//  関数名　：InitJieshaobg
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitJieshaobg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffJieshaobg,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *Jieshaobg;
		g_pVtxBuffJieshaobg ->Lock(0,0,(void **)&Jieshaobg,0);		//頂点情報へのポインタを取得
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\jieshao.png",
		&g_pTextureJieshaobg);
		jieshaobUse = true;
		Jieshaobg[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		Jieshaobg[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
		Jieshaobg[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		Jieshaobg[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		Jieshaobg[0].rhw = 1.0f;
		Jieshaobg[1].rhw = 1.0f;
		Jieshaobg[2].rhw = 1.0f;
		Jieshaobg[3].rhw = 1.0f;
		Jieshaobg[0].col=D3DCOLOR_RGBA(200,200,200,255);	//頂点情報格納ワーク
		Jieshaobg[1].col=D3DCOLOR_RGBA(200,200,200,255);
		Jieshaobg[2].col=D3DCOLOR_RGBA(200,200,200,255);
		Jieshaobg[3].col=D3DCOLOR_RGBA(200,200,200,255);

		Jieshaobg[0].tex = D3DXVECTOR2(0.0f,0.0f);
		Jieshaobg[1].tex = D3DXVECTOR2(1.0f,0.0f);
		Jieshaobg[2].tex = D3DXVECTOR2(0.0f,1.0f);
		Jieshaobg[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffJieshaobg ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：UninitJieshaobg
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitJieshaobg(void)
{
	if(g_pTextureJieshaobg!=NULL)
	{
		g_pTextureJieshaobg->Release();
		g_pTextureJieshaobg=NULL;
	}
	if(g_pVtxBuffJieshaobg!=NULL)
	{
		g_pVtxBuffJieshaobg->Release();		//頂点バッファの開放
		g_pVtxBuffJieshaobg=NULL;
	}
}
//=============================================================================
//  関数名　：DrawJieshaobg
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawJieshaobg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureJieshaobg);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffJieshaobg,
								0,
								sizeof(VERTEX_2D)
								);

	// フェードの描画設定内容
	pDevice -> DrawPrimitive(
							  D3DPT_TRIANGLESTRIP,		// プリミティブの種類
							  0,		// 最初の頂点のインデックス
							  2			// 描画するプリミティブ数
							);
}
//=============================================================================
//  関数名　：UpdateJieshaobg1
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateJieshaobg(void)
{

}
