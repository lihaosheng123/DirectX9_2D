#include "main.h"
#include "key.h"
#include "input.h"
//グローバル変数
KEY g_aKey[MAX_KEY];
LPDIRECT3DTEXTURE9 g_pTextureKey =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffKey =NULL;	//頂点パッファへのポインタ
D3DXVECTOR3 g_posKey;	//ポリゴンの位置
D3DXVECTOR3 g_rotKey;		//ポリゴンの回転角
D3DXVECTOR3 g_moveKey;		//ポリゴンの移動量
int g_nCounterAnim_Key;		//アンメーションカウンタ
int g_nPatternAnim_Key;		//アンメーションパターンNO
float animRow_Key =1.0f;
float maxAnimX_Key = 2.0f;
float maxAnimY_Key = 1.0f;
float g_fLengthKey;		//ポリゴンの対角線の長さ
float g_fAngleKey;		//ポリゴンの対角線の角度
float move_Key = 3.0f;		//移動量
float runSpeed_Key = 5.0f;
int animMaxnum_Key = 2;
float startAnimY_Key = 0.0f;

//=============================================================================
//  関数名　：InitKey
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitKey(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffKey,NULL)))
	{
		return E_FAIL;
	}
		VERTEX_2D *pVtx;
		g_pVtxBuffKey ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得
		//テクスチャの読み込み	
		D3DXCreateTextureFromFile(
			pDevice,
			".\\data\\TEXTURE\\key.png",
		&g_pTextureKey);

		bKey = false;
		
		g_aKey[0].fHeight=2.0f;
		g_aKey[0].fWidth=80.0f;
			//初期化処理
		g_aKey[0].pos.x = 960.0f;
		g_aKey[0].pos.y = 670.0f;
		g_posKey = D3DXVECTOR3(g_aKey[0].pos.x,g_aKey[0].pos.y,0.0f);
		
			//回転初期化処理
		g_rotKey = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_fLengthKey =sqrtf(g_aKey[0].fWidth * g_aKey[0].fWidth + g_aKey[0].fHeight * g_aKey[0].fHeight)*0.5f;
		g_fAngleKey =atan2f(g_aKey[0].fWidth,g_aKey[0].fHeight)*0.5f;


		
		//頂点座標設定
		pVtx[0].pos = D3DXVECTOR3 (g_aKey[0].pos.x - sinf( g_fAngleKey + g_rotKey.z ) * g_fLengthKey,
								   g_aKey[0].pos.y - cosf( g_fAngleKey + g_rotKey.z ) * g_fLengthKey,
								   0.0f);

		pVtx[1].pos = D3DXVECTOR3 (g_aKey[0].pos.x + sinf( g_fAngleKey - g_rotKey.z ) * g_fLengthKey,
								   g_aKey[0].pos.y - cosf( g_fAngleKey - g_rotKey.z ) * g_fLengthKey,
								   0.0f);

		pVtx[2].pos = D3DXVECTOR3 (g_aKey[0].pos.x - sinf( g_fAngleKey - g_rotKey.z ) * g_fLengthKey,
								   g_aKey[0].pos.y + cosf( g_fAngleKey - g_rotKey.z ) * g_fLengthKey,
								   0.0f);

		pVtx[3].pos = D3DXVECTOR3 (g_aKey[0].pos.x + sinf( g_fAngleKey + g_rotKey.z ) * g_fLengthKey,
								   g_aKey[0].pos.y + cosf( g_fAngleKey + g_rotKey.z ) * g_fLengthKey,
								   0.0f);

			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(1.0f / maxAnimX_Key,0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f / maxAnimY_Key);
			pVtx[3].tex = D3DXVECTOR2(1.0f / maxAnimX_Key, 1.0f / maxAnimY_Key);

		//座標変換
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
			
		//頂点色設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 128);	//頂点情報格納ワーク
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 128);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 128);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 128);
		
		g_pVtxBuffKey ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：UninitKey
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitKey(void)
{

	if(g_pVtxBuffKey!=NULL)
	{
		g_pVtxBuffKey->Release();		//頂点バッファの開放
		g_pVtxBuffKey=NULL;
	}
	if(g_pTextureKey!=NULL)
	{
		g_pTextureKey->Release();
		g_pTextureKey=NULL;
	}
}
//=============================================================================
//  関数名　：DrawKey
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawKey(void)
{
	if(bKey == false)
	{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureKey);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffKey,
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
//  関数名　：UpdateKey
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateKey(void)
{
	g_nCounterAnim_Key++;
		if(g_nCounterAnim_Key == runSpeed_Key )
		{
			g_nCounterAnim_Key = 0;
			g_nPatternAnim_Key ++;
			if(g_nPatternAnim_Key == animMaxnum_Key)	//パターン数
			{
				startAnimY_Key = 0;//画面上
				animRow_Key = 1;
				g_nPatternAnim_Key = 0;
			}
			else if(g_nPatternAnim_Key == 5)
			{
				animRow_Key++;
				startAnimY_Key += (1.0f / maxAnimY_Key);
			}
			VERTEX_2D *pVtx;
			g_pVtxBuffKey ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得
			pVtx[0].tex.x = g_nPatternAnim_Key *(1.0f / maxAnimX_Key);
			pVtx[0].tex.y = startAnimY_Key;

			pVtx[1].tex.x = (g_nPatternAnim_Key * (1.0f /  maxAnimX_Key)) + (1.0f / maxAnimX_Key);
			pVtx[1].tex.y = startAnimY_Key;
				
			pVtx[2].tex.x = g_nPatternAnim_Key * (1.0f /  maxAnimX_Key);
			pVtx[2].tex.y = animRow_Key *(1.0f / maxAnimY_Key);

			pVtx[3].tex.x = (g_nPatternAnim_Key * (1.0f /  maxAnimX_Key)) + (1.0f / maxAnimX_Key);
			pVtx[3].tex.y = animRow_Key *(1.0f / maxAnimY_Key);
		}
		g_pVtxBuffKey ->Unlock();	//LOCK
}


