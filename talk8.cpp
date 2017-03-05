#include "main.h"
#include "talk8.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTalk8 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTalk8 =NULL;	//頂点パッファへのポインタ
D3DXVECTOR3 g_posTalk8;	//ポリゴンの位置
D3DXVECTOR3 g_rotTalk8;		//ポリゴンの回転角
D3DXVECTOR3 g_moveTalk8;		//ポリゴンの移動量
int g_nCounterAnim_Talk8;		//アンメーションカウンタ
int g_nPatternAnim_Talk8;		//アンメーションパターンNO
float animRow_Talk8 =1.0f;
float maxAnimX_Talk8 = 1.0f;
float maxAnimY_Talk8 = 1.0f;
float Talk8Width = 800.0f;		//ポリゴンの幅
float Talk8Height = 150.0f;
float Talk8_X = 160.0f;
float Talk8_Y = 600.0f;
float g_fLengthTalk8;		//ポリゴンの対角線の長さ
float g_fAngleTalk8;		//ポリゴンの対角線の角度
//=============================================================================
//  関数名　：InitTalk8
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitTalk8(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffTalk8,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *Talk8;
		g_pVtxBuffTalk8 ->Lock(0,0,(void **)&Talk8,0);		//頂点情報へのポインタを取得
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\talk8.png",
		&g_pTextureTalk8);

		bUseTalk8 = false;
		Talk8[0].pos = D3DXVECTOR3(Talk8_X,Talk8_Y,0.0f);
		Talk8[1].pos = D3DXVECTOR3(Talk8_X+Talk8Width,Talk8_Y,0.0f);
		Talk8[2].pos = D3DXVECTOR3(Talk8_X,Talk8_Y+Talk8Height,0.0f);
		Talk8[3].pos = D3DXVECTOR3(Talk8_X+Talk8Width,Talk8_Y+Talk8Height,0.0f);
		Talk8[0].rhw = 1.0f;
		Talk8[1].rhw = 1.0f;
		Talk8[2].rhw = 1.0f;
		Talk8[3].rhw = 1.0f;
		Talk8[0].col=D3DCOLOR_RGBA(200,200,200,255);	//頂点情報格納ワーク
		Talk8[1].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk8[2].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk8[3].col=D3DCOLOR_RGBA(200,200,200,255);

		Talk8[0].tex = D3DXVECTOR2(0.0f,0.0f);
		Talk8[1].tex = D3DXVECTOR2(1.0f,0.0f);
		Talk8[2].tex = D3DXVECTOR2(0.0f,1.0f);
		Talk8[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffTalk8 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：UninitTalk8
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitTalk8(void)
{
	if(g_pTextureTalk8!=NULL)
	{
		g_pTextureTalk8->Release();
		g_pTextureTalk8=NULL;
	}
	if(g_pVtxBuffTalk8!=NULL)
	{
		g_pVtxBuffTalk8->Release();		//頂点バッファの開放
		g_pVtxBuffTalk8=NULL;
	}
}
//=============================================================================
//  関数名　：DrawTalk8
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawTalk8(void)
{
	if(bUseTalk8 == true)
	{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureTalk8);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffTalk8,
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
//  関数名　：UpdateTalk81
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateTalk8(void)
{
	if(bUseTalk8 == true)
	{
	}
}
