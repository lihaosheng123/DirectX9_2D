#include "main.h"
#include "bg.h"
//グローバル変数
VERTEX_2D g_bg[4];
LPDIRECT3DTEXTURE9 g_pTexturebg =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffbg =NULL;	//頂点パッファへのポインタ
//=============================================================================
//  関数名　：Initbg
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT Initbg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffbg,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *bg;
		g_pVtxBuffbg ->Lock(0,0,(void **)&bg,0);		//頂点情報へのポインタを取得
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\001.png",
		&g_pTexturebg);
		bg[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		bg[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
		bg[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		bg[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		bg[0].rhw = 1.0f;
		bg[1].rhw = 1.0f;
		bg[2].rhw = 1.0f;
		bg[3].rhw = 1.0f;
		bg[0].col=D3DCOLOR_RGBA(200,200,200,255);	//頂点情報格納ワーク
		bg[1].col=D3DCOLOR_RGBA(200,200,200,255);
		bg[2].col=D3DCOLOR_RGBA(200,200,200,255);
		bg[3].col=D3DCOLOR_RGBA(200,200,200,255);

		bg[0].tex = D3DXVECTOR2(0.0f,0.0f);
		bg[1].tex = D3DXVECTOR2(1.0f,0.0f);
		bg[2].tex = D3DXVECTOR2(0.0f,1.0f);
		bg[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffbg ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：Uninitbg
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void Uninitbg(void)
{
	if(g_pTexturebg!=NULL)
	{
		g_pTexturebg->Release();
		g_pTexturebg=NULL;
	}
	if(g_pVtxBuffbg!=NULL)
	{
		g_pVtxBuffbg->Release();		//頂点バッファの開放
		g_pVtxBuffbg=NULL;
	}
}
//=============================================================================
//  関数名　：Drawbg
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void Drawbg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTexturebg);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffbg,
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
//  関数名　：Updatebg
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void Updatebg(void)
{

}
