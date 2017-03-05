#include "main.h"
#include "talk2.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTalk2 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTalk2 =NULL;	//頂点パッファへのポインタ
D3DXVECTOR3 g_posTalk2;	//ポリゴンの位置
D3DXVECTOR3 g_rotTalk2;		//ポリゴンの回転角
D3DXVECTOR3 g_moveTalk2;		//ポリゴンの移動量
int g_nCounterAnim_Talk2;		//アンメーションカウンタ
int g_nPatternAnim_Talk2;		//アンメーションパターンNO
float animRow_Talk2 =1.0f;
float maxAnimX_Talk2 = 1.0f;
float maxAnimY_Talk2 = 1.0f;
float Talk2Width = 800.0f;		//ポリゴンの幅
float Talk2Height = 150.0f;
float Talk2_X = 160.0f;
float Talk2_Y = 600.0f;
float g_fLengthTalk2;		//ポリゴンの対角線の長さ
float g_fAngleTalk2;		//ポリゴンの対角線の角度
//=============================================================================
//  関数名　：InitTalk2
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitTalk2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffTalk2,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *Talk2;
		g_pVtxBuffTalk2 ->Lock(0,0,(void **)&Talk2,0);		//頂点情報へのポインタを取得
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\talk2.png",
		&g_pTextureTalk2);

		bUseTalk2 = false;
		Talk2[0].pos = D3DXVECTOR3(Talk2_X,Talk2_Y,0.0f);
		Talk2[1].pos = D3DXVECTOR3(Talk2_X+Talk2Width,Talk2_Y,0.0f);
		Talk2[2].pos = D3DXVECTOR3(Talk2_X,Talk2_Y+Talk2Height,0.0f);
		Talk2[3].pos = D3DXVECTOR3(Talk2_X+Talk2Width,Talk2_Y+Talk2Height,0.0f);
		Talk2[0].rhw = 1.0f;
		Talk2[1].rhw = 1.0f;
		Talk2[2].rhw = 1.0f;
		Talk2[3].rhw = 1.0f;
		Talk2[0].col=D3DCOLOR_RGBA(200,200,200,255);	//頂点情報格納ワーク
		Talk2[1].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk2[2].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk2[3].col=D3DCOLOR_RGBA(200,200,200,255);

		Talk2[0].tex = D3DXVECTOR2(0.0f,0.0f);
		Talk2[1].tex = D3DXVECTOR2(1.0f,0.0f);
		Talk2[2].tex = D3DXVECTOR2(0.0f,1.0f);
		Talk2[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffTalk2 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：UninitTalk2
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitTalk2(void)
{
	if(g_pTextureTalk2!=NULL)
	{
		g_pTextureTalk2->Release();
		g_pTextureTalk2=NULL;
	}
	if(g_pVtxBuffTalk2!=NULL)
	{
		g_pVtxBuffTalk2->Release();		//頂点バッファの開放
		g_pVtxBuffTalk2=NULL;
	}
}
//=============================================================================
//  関数名　：DrawTalk2
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawTalk2(void)
{
	if(bUseTalk2 == true)
	{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureTalk2);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffTalk2,
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
//  関数名　：UpdateTalk21
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateTalk2(void)
{
	if(bUseTalk2 == true)
	{
	}
}
