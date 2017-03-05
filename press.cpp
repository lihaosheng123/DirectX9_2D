#include "main.h"
#include "press.h"
#include "input.h"
#include "fade.h"
//グローバル変数
VERTEX_2D g_Press[4];
LPDIRECT3DTEXTURE9 g_pTexturePress =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPress =NULL;	//頂点パッファへのポインタ
float widthPress = 500.0f;
float heightPress = 100.0f;
float PressCoordX = 400.0f;
float PressCoordY = 0.0f;
bool bUse = false;
float maxAnimX_Press = 1.0f;
float maxAnimY_Press = 2.0f;
float runSpeed_Press = 4.0f;
int animMaxnum_Press = 4;
float startAnimY_Press = 0.0f;
int g_nCounterAnim_Press;		//アンメーションカウンタ
int g_nPatternAnim_Press;		//アンメーションパターンNO
float animRow_Press =1.0f;
//=============================================================================
//  関数名　：InitPress
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitPress(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffPress,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *Press;
		g_pVtxBuffPress ->Lock(0,0,(void **)&Press,0);		//頂点情報へのポインタを取得
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\press.png",
		&g_pTexturePress);
		Press[0].pos = D3DXVECTOR3(PressCoordX,PressCoordY,0.0f);
		Press[1].pos = D3DXVECTOR3((PressCoordX+widthPress),PressCoordY,0.0f);
		Press[2].pos = D3DXVECTOR3(PressCoordX,(PressCoordY+heightPress),0.0f);
		Press[3].pos = D3DXVECTOR3((PressCoordX+widthPress),(PressCoordY+heightPress),0.0f);
		Press[0].rhw = 1.0f;
		Press[1].rhw = 1.0f;
		Press[2].rhw = 1.0f;
		Press[3].rhw = 1.0f;
		//頂点色設定
		Press[0].col = D3DCOLOR_RGBA(255, 255, 255, 128);	//頂点情報格納ワーク
		Press[1].col = D3DCOLOR_RGBA(255, 255, 255, 128);
		Press[2].col = D3DCOLOR_RGBA(255, 255, 255, 128);
		Press[3].col = D3DCOLOR_RGBA(255, 255, 255, 128);

		Press[0].tex = D3DXVECTOR2(0.0f,0.0f);
		Press[1].tex = D3DXVECTOR2(1.0f,0.0f);
		Press[2].tex = D3DXVECTOR2(0.0f,0.5f);
		Press[3].tex = D3DXVECTOR2(1.0f,0.5f);
		g_pVtxBuffPress ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：UninitPress
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitPress(void)
{
	if(g_pTexturePress!=NULL)
	{
		g_pTexturePress->Release();
		g_pTexturePress=NULL;
	}
	if(g_pVtxBuffPress!=NULL)
	{
		g_pVtxBuffPress->Release();		//頂点バッファの開放
		g_pVtxBuffPress=NULL;
	}
}
//=============================================================================
//  関数名　：DrawPress
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawPress(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTexturePress);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffPress,
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
//  関数名　：UpdatePress1
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdatePress(void)
{
	PressCoordY++;
	if(PressCoordY >= 500.0f ||GetKeyboardPress(DIK_RETURN) == true  )
	{
		PressCoordY = 500.0f;
	}
	//if(PressCoordY == 500.0f && GetKeyboardPress(DIK_RETURN) == true )		//画面遷移
	//{
	g_nCounterAnim_Press++;
		if(g_nCounterAnim_Press == runSpeed_Press )
		{
			g_nCounterAnim_Press = 0;
			g_nPatternAnim_Press ++;
			if(g_nPatternAnim_Press == animMaxnum_Press)	//パターン数
			{
				startAnimY_Press = 0;//画面上
				animRow_Press = 1;
				g_nPatternAnim_Press = 0;
			}
			else if(g_nPatternAnim_Press == 1)
			{
				animRow_Press++;
				startAnimY_Press += (1.0f / maxAnimY_Press);
			}
	if(PressCoordY == 500.0f && GetKeyboardPress(DIK_RETURN) == true )		//画面遷移
	{
		SetFade(FADE_OUT,MODE_JIESHAO);
		}
	}
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *Press;
	g_pVtxBuffPress ->Lock(0,0,(void **)&Press,0);		//頂点情報へのポインタを取得
	Press[0].tex.x = g_nPatternAnim_Press *(1.0f / maxAnimX_Press);
	Press[0].tex.y = startAnimY_Press;

	Press[1].tex.x = (g_nPatternAnim_Press * (1.0f /  maxAnimX_Press)) + (1.0f / maxAnimX_Press);
	Press[1].tex.y = startAnimY_Press;
				
	Press[2].tex.x = g_nPatternAnim_Press * (1.0f /  maxAnimX_Press);
	Press[2].tex.y = animRow_Press *(1.0f / maxAnimY_Press);

	Press[3].tex.x = (g_nPatternAnim_Press * (1.0f /  maxAnimX_Press)) + (1.0f / maxAnimX_Press);
	Press[3].tex.y = animRow_Press *(1.0f / maxAnimY_Press);
	Press[0].pos = D3DXVECTOR3(PressCoordX,PressCoordY,0.0f);
	Press[1].pos = D3DXVECTOR3((PressCoordX+widthPress),PressCoordY,0.0f);
	Press[2].pos = D3DXVECTOR3(PressCoordX,(PressCoordY+heightPress),0.0f);
	Press[3].pos = D3DXVECTOR3((PressCoordX+widthPress),(PressCoordY+heightPress),0.0f);

	g_pVtxBuffPress ->Unlock();	//LOCK
	
}