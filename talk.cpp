#include "main.h"
#include "talk.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTalk =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTalk =NULL;	//頂点パッファへのポインタ
D3DXVECTOR3 g_posTalk;	//ポリゴンの位置
D3DXVECTOR3 g_rotTalk;		//ポリゴンの回転角
D3DXVECTOR3 g_moveTalk;		//ポリゴンの移動量
int g_nCounterAnim_Talk;		//アンメーションカウンタ
int g_nPatternAnim_Talk;		//アンメーションパターンNO
float animRow_Talk =1.0f;
float maxAnimX_Talk = 1.0f;
float maxAnimY_Talk = 1.0f;
float TalkWidth = 1200.0f;		//ポリゴンの幅
float Talk_Y = 600.0f;
float g_fLengthTalk;		//ポリゴンの対角線の長さ
float g_fAngleTalk;		//ポリゴンの対角線の角度
//=============================================================================
//  関数名　：InitTalk
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitTalk(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffTalk,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *Talk;
		g_pVtxBuffTalk ->Lock(0,0,(void **)&Talk,0);		//頂点情報へのポインタを取得
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\talk.png",
		&g_pTextureTalk);

		bUseTalk = false;
		Talk[0].pos = D3DXVECTOR3(0.0f,Talk_Y,0.0f);
		Talk[1].pos = D3DXVECTOR3(0.0f+TalkWidth,Talk_Y,0.0f);
		Talk[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		Talk[3].pos = D3DXVECTOR3(0.0f+TalkWidth,SCREEN_HEIGHT,0.0f);
		Talk[0].rhw = 1.0f;
		Talk[1].rhw = 1.0f;
		Talk[2].rhw = 1.0f;
		Talk[3].rhw = 1.0f;
		Talk[0].col=D3DCOLOR_RGBA(200,200,200,255);	//頂点情報格納ワーク
		Talk[1].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk[2].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk[3].col=D3DCOLOR_RGBA(200,200,200,255);

		Talk[0].tex = D3DXVECTOR2(0.0f,0.0f);
		Talk[1].tex = D3DXVECTOR2(1.0f,0.0f);
		Talk[2].tex = D3DXVECTOR2(0.0f,1.0f);
		Talk[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffTalk ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：UninitTalk
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitTalk(void)
{
	if(g_pTextureTalk!=NULL)
	{
		g_pTextureTalk->Release();
		g_pTextureTalk=NULL;
	}
	if(g_pVtxBuffTalk!=NULL)
	{
		g_pVtxBuffTalk->Release();		//頂点バッファの開放
		g_pVtxBuffTalk=NULL;
	}
}
//=============================================================================
//  関数名　：DrawTalk
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawTalk(void)
{
	if(bUseTalk == true)
	{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureTalk);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffTalk,
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
//  関数名　：UpdateTalk1
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateTalk(void)
{
	if(bUseTalk == true)
	{
	}
}
