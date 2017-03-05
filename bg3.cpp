
#include "main.h"
#include "bg3.h"
#include "score.h"
//グローバル変数
VERTEX_2D g_bg3[4];
LPDIRECT3DTEXTURE9 g_pTexturebg3 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffbg3 =NULL;	//頂点パッファへのポインタ
bool bSwitch;
//=============================================================================
//  関数名　：Initbg3
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT Initbg3(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffbg3,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *bg3;
		g_pVtxBuffbg3 ->Lock(0,0,(void **)&bg3,0);		//頂点情報へのポインタを取得
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\bg003.png",
		&g_pTexturebg3);
		bUsebg3 = true;
		bg3[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		bg3[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
		bg3[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		bg3[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		bg3[0].rhw = 1.0f;
		bg3[1].rhw = 1.0f;
		bg3[2].rhw = 1.0f;
		bg3[3].rhw = 1.0f;
		bg3[0].col=D3DCOLOR_RGBA(200,200,200,255);	//頂点情報格納ワーク
		bg3[1].col=D3DCOLOR_RGBA(200,200,200,255);
		bg3[2].col=D3DCOLOR_RGBA(200,200,200,255);
		bg3[3].col=D3DCOLOR_RGBA(200,200,200,255);

		bg3[0].tex = D3DXVECTOR2(0.0f,0.0f);
		bg3[1].tex = D3DXVECTOR2(1.0f,0.0f);
		bg3[2].tex = D3DXVECTOR2(0.0f,1.0f);
		bg3[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffbg3 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：Uninitbg3
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void Uninitbg3(void)
{
	if(g_pTexturebg3!=NULL)
	{
		g_pTexturebg3->Release();
		g_pTexturebg3=NULL;
	}
	if(g_pVtxBuffbg3!=NULL)
	{
		g_pVtxBuffbg3->Release();		//頂点バッファの開放
		g_pVtxBuffbg3=NULL;
	}
}
//=============================================================================
//  関数名　：Drawbg3
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void Drawbg3(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTexturebg3);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffbg3,
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
//  関数名　：Updatebg31
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void Updatebg3(void)
{



}
