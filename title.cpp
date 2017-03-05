#include "main.h"
#include "title.h"
#include "input.h"
#include "press.h"
#include "sound.h"
//グローバル変数
VERTEX_2D g_title[4];
LPDIRECT3DTEXTURE9 g_pTexturetitle =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufftitle =NULL;	//頂点パッファへのポインタ
//=============================================================================
//  関数名　：Inittitle
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBufftitle,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *title;
		g_pVtxBufftitle ->Lock(0,0,(void **)&title,0);		//頂点情報へのポインタを取得
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\title.png",
		&g_pTexturetitle);
		title[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		title[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
		title[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		title[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		title[0].rhw = 1.0f;
		title[1].rhw = 1.0f;
		title[2].rhw = 1.0f;
		title[3].rhw = 1.0f;
		title[0].col=D3DCOLOR_RGBA(200,200,200,255);	//頂点情報格納ワーク
		title[1].col=D3DCOLOR_RGBA(200,200,200,255);
		title[2].col=D3DCOLOR_RGBA(200,200,200,255);
		title[3].col=D3DCOLOR_RGBA(200,200,200,255);

		title[0].tex = D3DXVECTOR2(0.0f,0.0f);
		title[1].tex = D3DXVECTOR2(1.0f,0.0f);
		title[2].tex = D3DXVECTOR2(0.0f,1.0f);
		title[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBufftitle ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：Uninittitle
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitTitle(void)
{
	if(g_pTexturetitle!=NULL)
	{
		g_pTexturetitle->Release();
		g_pTexturetitle=NULL;
	}
	if(g_pVtxBufftitle!=NULL)
	{
		g_pVtxBufftitle->Release();		//頂点バッファの開放
		g_pVtxBufftitle=NULL;
	}
}
//=============================================================================
//  関数名　：Drawtitle
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTexturetitle);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBufftitle,
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
//  関数名　：Updatetitle
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateTitle(void)
{

}
