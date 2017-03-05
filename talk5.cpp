#include "main.h"
#include "talk5.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTalk5 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTalk5 =NULL;	//頂点パッファへのポインタ
D3DXVECTOR3 g_posTalk5;	//ポリゴンの位置
D3DXVECTOR3 g_rotTalk5;		//ポリゴンの回転角
D3DXVECTOR3 g_moveTalk5;		//ポリゴンの移動量
int g_nCounterAnim_Talk5;		//アンメーションカウンタ
int g_nPatternAnim_Talk5;		//アンメーションパターンNO
float animRow_Talk5 =1.0f;
float maxAnimX_Talk5 = 1.0f;
float maxAnimY_Talk5 = 1.0f;
float Talk5Width = 800.0f;		//ポリゴンの幅
float Talk5Height = 150.0f;
float Talk5_X = 160.0f;
float Talk5_Y = 600.0f;
float g_fLengthTalk5;		//ポリゴンの対角線の長さ
float g_fAngleTalk5;		//ポリゴンの対角線の角度
//=============================================================================
//  関数名　：InitTalk5
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitTalk5(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffTalk5,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *Talk5;
		g_pVtxBuffTalk5 ->Lock(0,0,(void **)&Talk5,0);		//頂点情報へのポインタを取得
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\talk5.png",
		&g_pTextureTalk5);

		bUseTalk5 = false;
		Talk5[0].pos = D3DXVECTOR3(Talk5_X,Talk5_Y,0.0f);
		Talk5[1].pos = D3DXVECTOR3(Talk5_X+Talk5Width,Talk5_Y,0.0f);
		Talk5[2].pos = D3DXVECTOR3(Talk5_X,Talk5_Y+Talk5Height,0.0f);
		Talk5[3].pos = D3DXVECTOR3(Talk5_X+Talk5Width,Talk5_Y+Talk5Height,0.0f);
		Talk5[0].rhw = 1.0f;
		Talk5[1].rhw = 1.0f;
		Talk5[2].rhw = 1.0f;
		Talk5[3].rhw = 1.0f;
		Talk5[0].col=D3DCOLOR_RGBA(200,200,200,255);	//頂点情報格納ワーク
		Talk5[1].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk5[2].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk5[3].col=D3DCOLOR_RGBA(200,200,200,255);

		Talk5[0].tex = D3DXVECTOR2(0.0f,0.0f);
		Talk5[1].tex = D3DXVECTOR2(1.0f,0.0f);
		Talk5[2].tex = D3DXVECTOR2(0.0f,1.0f);
		Talk5[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffTalk5 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：UninitTalk5
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitTalk5(void)
{
	if(g_pTextureTalk5!=NULL)
	{
		g_pTextureTalk5->Release();
		g_pTextureTalk5=NULL;
	}
	if(g_pVtxBuffTalk5!=NULL)
	{
		g_pVtxBuffTalk5->Release();		//頂点バッファの開放
		g_pVtxBuffTalk5=NULL;
	}
}
//=============================================================================
//  関数名　：DrawTalk5
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawTalk5(void)
{
	if(bUseTalk5 == true)
	{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureTalk5);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffTalk5,
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
//  関数名　：UpdateTalk51
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateTalk5(void)
{
	if(bUseTalk5 == true)
	{
	}
}
