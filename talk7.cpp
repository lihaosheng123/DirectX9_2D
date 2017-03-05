#include "main.h"
#include "talk7.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTalk7 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTalk7 =NULL;	//頂点パッファへのポインタ
D3DXVECTOR3 g_posTalk7;	//ポリゴンの位置
D3DXVECTOR3 g_rotTalk7;		//ポリゴンの回転角
D3DXVECTOR3 g_moveTalk7;		//ポリゴンの移動量
int g_nCounterAnim_Talk7;		//アンメーションカウンタ
int g_nPatternAnim_Talk7;		//アンメーションパターンNO
float animRow_Talk7 =1.0f;
float maxAnimX_Talk7 = 1.0f;
float maxAnimY_Talk7 = 1.0f;
float Talk7Width = 800.0f;		//ポリゴンの幅
float Talk7Height = 150.0f;
float Talk7_X = 160.0f;
float Talk7_Y = 600.0f;
float g_fLengthTalk7;		//ポリゴンの対角線の長さ
float g_fAngleTalk7;		//ポリゴンの対角線の角度
//=============================================================================
//  関数名　：InitTalk7
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitTalk7(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffTalk7,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *Talk7;
		g_pVtxBuffTalk7 ->Lock(0,0,(void **)&Talk7,0);		//頂点情報へのポインタを取得
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\Talk7.png",
		&g_pTextureTalk7);

		bUseTalk7 = false;
		Talk7[0].pos = D3DXVECTOR3(Talk7_X,Talk7_Y,0.0f);
		Talk7[1].pos = D3DXVECTOR3(Talk7_X+Talk7Width,Talk7_Y,0.0f);
		Talk7[2].pos = D3DXVECTOR3(Talk7_X,Talk7_Y+Talk7Height,0.0f);
		Talk7[3].pos = D3DXVECTOR3(Talk7_X+Talk7Width,Talk7_Y+Talk7Height,0.0f);
		Talk7[0].rhw = 1.0f;
		Talk7[1].rhw = 1.0f;
		Talk7[2].rhw = 1.0f;
		Talk7[3].rhw = 1.0f;
		Talk7[0].col=D3DCOLOR_RGBA(200,200,200,255);	//頂点情報格納ワーク
		Talk7[1].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk7[2].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk7[3].col=D3DCOLOR_RGBA(200,200,200,255);

		Talk7[0].tex = D3DXVECTOR2(0.0f,0.0f);
		Talk7[1].tex = D3DXVECTOR2(1.0f,0.0f);
		Talk7[2].tex = D3DXVECTOR2(0.0f,1.0f);
		Talk7[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffTalk7 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：UninitTalk7
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitTalk7(void)
{
	if(g_pTextureTalk7!=NULL)
	{
		g_pTextureTalk7->Release();
		g_pTextureTalk7=NULL;
	}
	if(g_pVtxBuffTalk7!=NULL)
	{
		g_pVtxBuffTalk7->Release();		//頂点バッファの開放
		g_pVtxBuffTalk7=NULL;
	}
}
//=============================================================================
//  関数名　：DrawTalk7
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawTalk7(void)
{
	if(bUseTalk7 == true)
	{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureTalk7);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffTalk7,
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
//  関数名　：UpdateTalk71
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateTalk7(void)
{
	if(bUseTalk7 == true)
	{
	}
}
