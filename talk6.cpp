#include "main.h"
#include "talk6.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTalk6 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTalk6 =NULL;	//頂点パッファへのポインタ
D3DXVECTOR3 g_posTalk6;	//ポリゴンの位置
D3DXVECTOR3 g_rotTalk6;		//ポリゴンの回転角
D3DXVECTOR3 g_moveTalk6;		//ポリゴンの移動量
int g_nCounterAnim_Talk6;		//アンメーションカウンタ
int g_nPatternAnim_Talk6;		//アンメーションパターンNO
float animRow_Talk6 =1.0f;
float maxAnimX_Talk6 = 1.0f;
float maxAnimY_Talk6 = 1.0f;
float Talk6Width = 800.0f;		//ポリゴンの幅
float Talk6Height = 150.0f;
float Talk6_X = 160.0f;
float Talk6_Y = 600.0f;
float g_fLengthTalk6;		//ポリゴンの対角線の長さ
float g_fAngleTalk6;		//ポリゴンの対角線の角度
//=============================================================================
//  関数名　：InitTalk6
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitTalk6(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffTalk6,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *Talk6;
		g_pVtxBuffTalk6 ->Lock(0,0,(void **)&Talk6,0);		//頂点情報へのポインタを取得
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\talk6.png",
		&g_pTextureTalk6);

		bUseTalk6 = false;
		Talk6[0].pos = D3DXVECTOR3(Talk6_X,Talk6_Y,0.0f);
		Talk6[1].pos = D3DXVECTOR3(Talk6_X+Talk6Width,Talk6_Y,0.0f);
		Talk6[2].pos = D3DXVECTOR3(Talk6_X,Talk6_Y+Talk6Height,0.0f);
		Talk6[3].pos = D3DXVECTOR3(Talk6_X+Talk6Width,Talk6_Y+Talk6Height,0.0f);
		Talk6[0].rhw = 1.0f;
		Talk6[1].rhw = 1.0f;
		Talk6[2].rhw = 1.0f;
		Talk6[3].rhw = 1.0f;
		Talk6[0].col=D3DCOLOR_RGBA(200,200,200,255);	//頂点情報格納ワーク
		Talk6[1].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk6[2].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk6[3].col=D3DCOLOR_RGBA(200,200,200,255);

		Talk6[0].tex = D3DXVECTOR2(0.0f,0.0f);
		Talk6[1].tex = D3DXVECTOR2(1.0f,0.0f);
		Talk6[2].tex = D3DXVECTOR2(0.0f,1.0f);
		Talk6[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffTalk6 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：UninitTalk6
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitTalk6(void)
{
	if(g_pTextureTalk6!=NULL)
	{
		g_pTextureTalk6->Release();
		g_pTextureTalk6=NULL;
	}
	if(g_pVtxBuffTalk6!=NULL)
	{
		g_pVtxBuffTalk6->Release();		//頂点バッファの開放
		g_pVtxBuffTalk6=NULL;
	}
}
//=============================================================================
//  関数名　：DrawTalk6
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawTalk6(void)
{
	if(bUseTalk6 == true)
	{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureTalk6);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffTalk6,
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
//  関数名　：UpdateTalk61
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateTalk6(void)
{
	if(bUseTalk6 == true)
	{
	}
}
