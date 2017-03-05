#include "main.h"
#include "result.h"
#include "input.h"
#include "sound.h"
//グローバル変数
VERTEX_2D g_result[4];
LPDIRECT3DTEXTURE9 g_pTextureresult =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffresult =NULL;	//頂点パッファへのポインタ
//=============================================================================
//  関数名　：Initresult
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitResult(void)
{
	PlaySound(SOUND_LABEL_BGM002);
	StopSound(SOUND_LABEL_BGM001);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffresult,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *result;
		g_pVtxBuffresult ->Lock(0,0,(void **)&result,0);		//頂点情報へのポインタを取得
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\result.png",
		&g_pTextureresult);
		result[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		result[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
		result[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		result[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		result[0].rhw = 1.0f;
		result[1].rhw = 1.0f;
		result[2].rhw = 1.0f;
		result[3].rhw = 1.0f;
		result[0].col=D3DCOLOR_RGBA(200,200,200,255);	//頂点情報格納ワーク
		result[1].col=D3DCOLOR_RGBA(200,200,200,255);
		result[2].col=D3DCOLOR_RGBA(200,200,200,255);
		result[3].col=D3DCOLOR_RGBA(200,200,200,255);

		result[0].tex = D3DXVECTOR2(0.0f,0.0f);
		result[1].tex = D3DXVECTOR2(1.0f,0.0f);
		result[2].tex = D3DXVECTOR2(0.0f,1.0f);
		result[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffresult ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：Uninitresult
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitResult(void)
{
	if(g_pTextureresult!=NULL)
	{
		g_pTextureresult->Release();
		g_pTextureresult=NULL;
	}
	if(g_pVtxBuffresult!=NULL)
	{
		g_pVtxBuffresult->Release();		//頂点バッファの開放
		g_pVtxBuffresult=NULL;
	}
}
//=============================================================================
//  関数名　：Drawresult
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureresult);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffresult,
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
//=============================================================================
//  関数名　：Updateresult
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateResult(void)
{
	MODE mode;
	mode = GetMode();
	//if(GetKeyboardTrigger(DIK_RETURN) == true)
	//{
	//	mode = MODE_TITLE;
	//	SetMode(mode);
	//}


}
