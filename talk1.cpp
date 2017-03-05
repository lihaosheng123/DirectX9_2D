#include "main.h"
#include "talk1.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTalk1 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTalk1 =NULL;	//頂点パッファへのポインタ
D3DXVECTOR3 g_posTalk1;	//ポリゴンの位置
D3DXVECTOR3 g_rotTalk1;		//ポリゴンの回転角
D3DXVECTOR3 g_moveTalk1;		//ポリゴンの移動量
int g_nCounterAnim_Talk1;		//アンメーションカウンタ
int g_nPatternAnim_Talk1;		//アンメーションパターンNO
float animRow_Talk1 =1.0f;
float maxAnimX_Talk1 = 1.0f;
float maxAnimY_Talk1 = 1.0f;
float Talk1Width = 800.0f;		//ポリゴンの幅
float Talk1Height = 150.0f;
float Talk1_X = 160.0f;
float Talk1_Y = 600.0f;
float g_fLengthTalk1;		//ポリゴンの対角線の長さ
float g_fAngleTalk1;		//ポリゴンの対角線の角度
//=============================================================================
//  関数名　：InitTalk1
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitTalk1(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffTalk1,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *Talk1;
		g_pVtxBuffTalk1 ->Lock(0,0,(void **)&Talk1,0);		//頂点情報へのポインタを取得
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\talk1.png",
		&g_pTextureTalk1);

		bUseTalk1 = false;
		Talk1[0].pos = D3DXVECTOR3(Talk1_X,Talk1_Y,0.0f);
		Talk1[1].pos = D3DXVECTOR3(Talk1_X+Talk1Width,Talk1_Y,0.0f);
		Talk1[2].pos = D3DXVECTOR3(Talk1_X,Talk1_Y+Talk1Height,0.0f);
		Talk1[3].pos = D3DXVECTOR3(Talk1_X+Talk1Width,Talk1_Y+Talk1Height,0.0f);
		Talk1[0].rhw = 1.0f;
		Talk1[1].rhw = 1.0f;
		Talk1[2].rhw = 1.0f;
		Talk1[3].rhw = 1.0f;
		Talk1[0].col=D3DCOLOR_RGBA(200,200,200,255);	//頂点情報格納ワーク
		Talk1[1].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk1[2].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk1[3].col=D3DCOLOR_RGBA(200,200,200,255);

		Talk1[0].tex = D3DXVECTOR2(0.0f,0.0f);
		Talk1[1].tex = D3DXVECTOR2(1.0f,0.0f);
		Talk1[2].tex = D3DXVECTOR2(0.0f,1.0f);
		Talk1[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffTalk1 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：UninitTalk1
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitTalk1(void)
{
	if(g_pTextureTalk1!=NULL)
	{
		g_pTextureTalk1->Release();
		g_pTextureTalk1=NULL;
	}
	if(g_pVtxBuffTalk1!=NULL)
	{
		g_pVtxBuffTalk1->Release();		//頂点バッファの開放
		g_pVtxBuffTalk1=NULL;
	}
}
//=============================================================================
//  関数名　：DrawTalk1
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawTalk1(void)
{
	if(bUseTalk1 == true)
	{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureTalk1);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffTalk1,
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
//  関数名　：UpdateTalk11
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateTalk1(void)
{
	if(bUseTalk1 == true)
	{
	}
}
