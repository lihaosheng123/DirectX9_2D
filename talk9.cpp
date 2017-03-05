#include "main.h"
#include "talk9.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTalk9 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTalk9 =NULL;	//頂点パッファへのポインタ
D3DXVECTOR3 g_posTalk9;	//ポリゴンの位置
D3DXVECTOR3 g_rotTalk9;		//ポリゴンの回転角
D3DXVECTOR3 g_moveTalk9;		//ポリゴンの移動量
int g_nCounterAnim_Talk9;		//アンメーションカウンタ
int g_nPatternAnim_Talk9;		//アンメーションパターンNO
float animRow_Talk9 =1.0f;
float maxAnimX_Talk9 = 1.0f;
float maxAnimY_Talk9 = 1.0f;
float Talk9Width = 500.0f;		//ポリゴンの幅
float Talk9Height = 100.0f;
float Talk9_X = 300.0f;
float Talk9_Y = 600.0f;
float g_fLengthTalk9;		//ポリゴンの対角線の長さ
float g_fAngleTalk9;		//ポリゴンの対角線の角度
//=============================================================================
//  関数名　：InitTalk9
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitTalk9(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffTalk9,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *Talk9;
		g_pVtxBuffTalk9 ->Lock(0,0,(void **)&Talk9,0);		//頂点情報へのポインタを取得
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\talk9.png",
		&g_pTextureTalk9);

		bUseTalk9 = false;
		Talk9[0].pos = D3DXVECTOR3(Talk9_X,Talk9_Y,0.0f);
		Talk9[1].pos = D3DXVECTOR3(Talk9_X+Talk9Width,Talk9_Y,0.0f);
		Talk9[2].pos = D3DXVECTOR3(Talk9_X,Talk9_Y+Talk9Height,0.0f);
		Talk9[3].pos = D3DXVECTOR3(Talk9_X+Talk9Width,Talk9_Y+Talk9Height,0.0f);
		Talk9[0].rhw = 1.0f;
		Talk9[1].rhw = 1.0f;
		Talk9[2].rhw = 1.0f;
		Talk9[3].rhw = 1.0f;
		Talk9[0].col=D3DCOLOR_RGBA(200,200,200,255);	//頂点情報格納ワーク
		Talk9[1].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk9[2].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk9[3].col=D3DCOLOR_RGBA(200,200,200,255);

		Talk9[0].tex = D3DXVECTOR2(0.0f,0.0f);
		Talk9[1].tex = D3DXVECTOR2(1.0f,0.0f);
		Talk9[2].tex = D3DXVECTOR2(0.0f,1.0f);
		Talk9[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffTalk9 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：UninitTalk9
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitTalk9(void)
{
	if(g_pTextureTalk9!=NULL)
	{
		g_pTextureTalk9->Release();
		g_pTextureTalk9=NULL;
	}
	if(g_pVtxBuffTalk9!=NULL)
	{
		g_pVtxBuffTalk9->Release();		//頂点バッファの開放
		g_pVtxBuffTalk9=NULL;
	}
}
//=============================================================================
//  関数名　：DrawTalk9
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawTalk9(void)
{
	if(bUseTalk9 == true)
	{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureTalk9);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffTalk9,
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
//  関数名　：UpdateTalk91
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateTalk9(void)
{
	if(bUseTalk9 == true)
	{
	}
}
