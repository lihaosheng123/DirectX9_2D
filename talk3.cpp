#include "main.h"
#include "talk3.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTalk3 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTalk3 =NULL;	//頂点パッファへのポインタ
D3DXVECTOR3 g_posTalk3;	//ポリゴンの位置
D3DXVECTOR3 g_rotTalk3;		//ポリゴンの回転角
D3DXVECTOR3 g_moveTalk3;		//ポリゴンの移動量
int g_nCounterAnim_Talk3;		//アンメーションカウンタ
int g_nPatternAnim_Talk3;		//アンメーションパターンNO
float animRow_Talk3 =1.0f;
float maxAnimX_Talk3 = 1.0f;
float maxAnimY_Talk3 = 1.0f;
float Talk3Width = 800.0f;		//ポリゴンの幅
float Talk3Height = 150.0f;
float Talk3_X = 160.0f;
float Talk3_Y = 600.0f;
float g_fLengthTalk3;		//ポリゴンの対角線の長さ
float g_fAngleTalk3;		//ポリゴンの対角線の角度
//=============================================================================
//  関数名　：InitTalk3
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitTalk3(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffTalk3,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *Talk3;
		g_pVtxBuffTalk3 ->Lock(0,0,(void **)&Talk3,0);		//頂点情報へのポインタを取得
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\talk3.png",
		&g_pTextureTalk3);

		bUseTalk3 = false;
		Talk3[0].pos = D3DXVECTOR3(Talk3_X,Talk3_Y,0.0f);
		Talk3[1].pos = D3DXVECTOR3(Talk3_X+Talk3Width,Talk3_Y,0.0f);
		Talk3[2].pos = D3DXVECTOR3(Talk3_X,Talk3_Y+Talk3Height,0.0f);
		Talk3[3].pos = D3DXVECTOR3(Talk3_X+Talk3Width,Talk3_Y+Talk3Height,0.0f);
		Talk3[0].rhw = 1.0f;
		Talk3[1].rhw = 1.0f;
		Talk3[2].rhw = 1.0f;
		Talk3[3].rhw = 1.0f;
		Talk3[0].col=D3DCOLOR_RGBA(200,200,200,255);	//頂点情報格納ワーク
		Talk3[1].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk3[2].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk3[3].col=D3DCOLOR_RGBA(200,200,200,255);

		Talk3[0].tex = D3DXVECTOR2(0.0f,0.0f);
		Talk3[1].tex = D3DXVECTOR2(1.0f,0.0f);
		Talk3[2].tex = D3DXVECTOR2(0.0f,1.0f);
		Talk3[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffTalk3 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：UninitTalk3
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitTalk3(void)
{
	if(g_pTextureTalk3!=NULL)
	{
		g_pTextureTalk3->Release();
		g_pTextureTalk3=NULL;
	}
	if(g_pVtxBuffTalk3!=NULL)
	{
		g_pVtxBuffTalk3->Release();		//頂点バッファの開放
		g_pVtxBuffTalk3=NULL;
	}
}
//=============================================================================
//  関数名　：DrawTalk3
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawTalk3(void)
{
	if(bUseTalk3 == true)
	{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureTalk3);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffTalk3,
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
	
}
//=============================================================================
//  関数名　：UpdateTalk31
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateTalk3(void)
{
	if(bUseTalk3 == true)
	{
	}
}
