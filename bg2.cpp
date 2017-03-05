#include "main.h"
#include "bg2.h"
#include "enemy.h"
//グローバル変数
VERTEX_2D g_bg2[4];
LPDIRECT3DTEXTURE9 g_pTexturebg2 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffbg2 =NULL;	//頂点パッファへのポインタ

//=============================================================================
//  関数名　：Initbg2
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT Initbg2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffbg2,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *bg2;
		g_pVtxBuffbg2 ->Lock(0,0,(void **)&bg2,0);		//頂点情報へのポインタを取得
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\bg002.png",
		&g_pTexturebg2);
		bUseEnemy2 = true;
		bUsebg2 = true;
		bg2[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		bg2[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
		bg2[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		bg2[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		bg2[0].rhw = 1.0f;
		bg2[1].rhw = 1.0f;
		bg2[2].rhw = 1.0f;
		bg2[3].rhw = 1.0f;
		bg2[0].col=D3DCOLOR_RGBA(200,200,200,255);	//頂点情報格納ワーク
		bg2[1].col=D3DCOLOR_RGBA(200,200,200,255);
		bg2[2].col=D3DCOLOR_RGBA(200,200,200,255);
		bg2[3].col=D3DCOLOR_RGBA(200,200,200,255);

		bg2[0].tex = D3DXVECTOR2(0.0f,0.0f);
		bg2[1].tex = D3DXVECTOR2(1.0f,0.0f);
		bg2[2].tex = D3DXVECTOR2(0.0f,1.0f);
		bg2[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffbg2 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：Uninitbg2
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void Uninitbg2(void)
{
	if(g_pTexturebg2!=NULL)
	{
		g_pTexturebg2->Release();
		g_pTexturebg2=NULL;
	}
	if(g_pVtxBuffbg2!=NULL)
	{
		g_pVtxBuffbg2->Release();		//頂点バッファの開放
		g_pVtxBuffbg2=NULL;
	}
}
//=============================================================================
//  関数名　：Drawbg2
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void Drawbg2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTexturebg2);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffbg2,
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
//  関数名　：Updatebg21
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void Updatebg2(void)
{
}
