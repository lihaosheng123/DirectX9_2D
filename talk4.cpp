#include "main.h"
#include "talk4.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTalk4 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTalk4 =NULL;	//頂点パッファへのポインタ
D3DXVECTOR3 g_posTalk4;	//ポリゴンの位置
D3DXVECTOR3 g_rotTalk4;		//ポリゴンの回転角
D3DXVECTOR3 g_moveTalk4;		//ポリゴンの移動量
int g_nCounterAnim_Talk4;		//アンメーションカウンタ
int g_nPatternAnim_Talk4;		//アンメーションパターンNO
float animRow_Talk4 =1.0f;
float maxAnimX_Talk4 = 1.0f;
float maxAnimY_Talk4 = 1.0f;
float Talk4Width = 800.0f;		//ポリゴンの幅
float Talk4Height = 150.0f;
float Talk4_X = 160.0f;
float Talk4_Y = 600.0f;
float g_fLengthTalk4;		//ポリゴンの対角線の長さ
float g_fAngleTalk4;		//ポリゴンの対角線の角度
//=============================================================================
//  関数名　：InitTalk4
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitTalk4(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffTalk4,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *Talk4;
		g_pVtxBuffTalk4 ->Lock(0,0,(void **)&Talk4,0);		//頂点情報へのポインタを取得
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\talk4.png",
		&g_pTextureTalk4);

		bUseTalk4 = false;
		Talk4[0].pos = D3DXVECTOR3(Talk4_X,Talk4_Y,0.0f);
		Talk4[1].pos = D3DXVECTOR3(Talk4_X+Talk4Width,Talk4_Y,0.0f);
		Talk4[2].pos = D3DXVECTOR3(Talk4_X,Talk4_Y+Talk4Height,0.0f);
		Talk4[3].pos = D3DXVECTOR3(Talk4_X+Talk4Width,Talk4_Y+Talk4Height,0.0f);
		Talk4[0].rhw = 1.0f;
		Talk4[1].rhw = 1.0f;
		Talk4[2].rhw = 1.0f;
		Talk4[3].rhw = 1.0f;
		Talk4[0].col=D3DCOLOR_RGBA(200,200,200,255);	//頂点情報格納ワーク
		Talk4[1].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk4[2].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk4[3].col=D3DCOLOR_RGBA(200,200,200,255);

		Talk4[0].tex = D3DXVECTOR2(0.0f,0.0f);
		Talk4[1].tex = D3DXVECTOR2(1.0f,0.0f);
		Talk4[2].tex = D3DXVECTOR2(0.0f,1.0f);
		Talk4[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffTalk4 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：UninitTalk4
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitTalk4(void)
{
	if(g_pTextureTalk4!=NULL)
	{
		g_pTextureTalk4->Release();
		g_pTextureTalk4=NULL;
	}
	if(g_pVtxBuffTalk4!=NULL)
	{
		g_pVtxBuffTalk4->Release();		//頂点バッファの開放
		g_pVtxBuffTalk4=NULL;
	}
}
//=============================================================================
//  関数名　：DrawTalk4
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawTalk4(void)
{
	if(bUseTalk4 == true)
	{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureTalk4);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffTalk4,
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
//  関数名　：UpdateTalk41
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateTalk4(void)
{
	if(bUseTalk4 == true)
	{
	}
}
