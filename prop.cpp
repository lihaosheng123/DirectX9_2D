#include "main.h"
#include "prop.h"
#include "input.h"
#include "score.h"
//グローバル変数
PROP g_aProp[MAX_PROP];
LPDIRECT3DTEXTURE9 g_pTextureProp =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffProp =NULL;	//頂点パッファへのポインタ
D3DXVECTOR3 g_posProp;	//ポリゴンの位置
D3DXVECTOR3 g_rotProp;		//ポリゴンの回転角
D3DXVECTOR3 g_moveProp;		//ポリゴンの移動量
float animRow_Prop =1.0f;
float maxAnimX_Prop = 2.0f;
float maxAnimY_Prop = 1.0f;
float g_fLengthProp;		//ポリゴンの対角線の長さ
float g_fAngleProp;		//ポリゴンの対角線の角度
float move_Prop = 2.0f;		//移動量
float runSpeed_Prop = 3.0f;
int animMaxnum_Prop = 2;
float startAnimY_Prop = 0.0f;
MODE g_ptype;
//=============================================================================
//  関数名　：InitProp
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitProp(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffProp,NULL)))
	{
		return E_FAIL;
	}
		VERTEX_2D *pVtx;
		g_pVtxBuffProp ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得
		//テクスチャの読み込み	
		D3DXCreateTextureFromFile(
			pDevice,
			".\\data\\TEXTURE\\prop.png",
		&g_pTextureProp);
		bProp = false;
		bPropUpdate = false;
		g_aProp[0].fHeight=50.0f;
		g_aProp[0].fWidth=150.0f;
			//初期化処理
		g_aProp[0].pos.x = 1115.0f;
		g_aProp[0].pos.y = 540.0f;
		g_posProp = D3DXVECTOR3(g_aProp[0].pos.x,g_aProp[0].pos.y,0.0f);
		
			//回転初期化処理
		g_rotProp = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_fLengthProp =sqrtf(g_aProp[0].fWidth * g_aProp[0].fWidth + g_aProp[0].fHeight * g_aProp[0].fHeight)*0.5f;
		g_fAngleProp =atan2f(g_aProp[0].fWidth,g_aProp[0].fHeight)*0.5f;


		
		//頂点座標設定
		pVtx[0].pos = D3DXVECTOR3 (g_aProp[0].pos.x - sinf( g_fAngleProp + g_rotProp.z ) * g_fLengthProp,
								   g_aProp[0].pos.y - cosf( g_fAngleProp + g_rotProp.z ) * g_fLengthProp,
								   0.0f);

		pVtx[1].pos = D3DXVECTOR3 (g_aProp[0].pos.x + sinf( g_fAngleProp - g_rotProp.z ) * g_fLengthProp,
								   g_aProp[0].pos.y - cosf( g_fAngleProp - g_rotProp.z ) * g_fLengthProp,
								   0.0f);

		pVtx[2].pos = D3DXVECTOR3 (g_aProp[0].pos.x - sinf( g_fAngleProp - g_rotProp.z ) * g_fLengthProp,
								   g_aProp[0].pos.y + cosf( g_fAngleProp - g_rotProp.z ) * g_fLengthProp,
								   0.0f);

		pVtx[3].pos = D3DXVECTOR3 (g_aProp[0].pos.x + sinf( g_fAngleProp + g_rotProp.z ) * g_fLengthProp,
								   g_aProp[0].pos.y + cosf( g_fAngleProp + g_rotProp.z ) * g_fLengthProp,
								   0.0f);
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(1.0f / maxAnimX_Prop,0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f / maxAnimY_Prop);
			pVtx[3].tex = D3DXVECTOR2(1.0f / maxAnimX_Prop, 1.0f / maxAnimY_Prop);
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

		g_pVtxBuffProp ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：UninitProp
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitProp(void)
{

	if(g_pVtxBuffProp!=NULL)
	{
		g_pVtxBuffProp->Release();		//頂点バッファの開放
		g_pVtxBuffProp=NULL;
	}
	if(g_pTextureProp!=NULL)
	{
		g_pTextureProp->Release();
		g_pTextureProp=NULL;
	}
}
//=============================================================================
//  関数名　：DrawProp
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawProp(void)
{
	if(bProp == false )
	{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureProp);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffProp,
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
//  関数名　：UpdateProp
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateProp(void)
{
	if(bPropUpdate== true)
	{
		if(bProp == false)
		{
			VERTEX_2D *pVtx;
			g_pVtxBuffProp ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得


			g_aProp[0].pos.x = 980.0f;
			g_aProp[0].pos.y = 730.0f;

			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(1.0f / maxAnimX_Prop,0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f / maxAnimY_Prop);
			pVtx[3].tex = D3DXVECTOR2(1.0f / maxAnimX_Prop, 1.0f / maxAnimY_Prop);
		//頂点座標設定
		pVtx[0].pos = D3DXVECTOR3 (g_aProp[0].pos.x - sinf( g_fAngleProp + g_rotProp.z ) * g_fLengthProp,
								   g_aProp[0].pos.y - cosf( g_fAngleProp + g_rotProp.z ) * g_fLengthProp,
								   0.0f);

		pVtx[1].pos = D3DXVECTOR3 (g_aProp[0].pos.x + sinf( g_fAngleProp - g_rotProp.z ) * g_fLengthProp,
								   g_aProp[0].pos.y - cosf( g_fAngleProp - g_rotProp.z ) * g_fLengthProp,
								   0.0f);

		pVtx[2].pos = D3DXVECTOR3 (g_aProp[0].pos.x - sinf( g_fAngleProp - g_rotProp.z ) * g_fLengthProp,
								   g_aProp[0].pos.y + cosf( g_fAngleProp - g_rotProp.z ) * g_fLengthProp,
								   0.0f);

		pVtx[3].pos = D3DXVECTOR3 (g_aProp[0].pos.x + sinf( g_fAngleProp + g_rotProp.z ) * g_fLengthProp,
								   g_aProp[0].pos.y + cosf( g_fAngleProp + g_rotProp.z ) * g_fLengthProp,
								   0.0f);
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

		g_pVtxBuffProp ->Unlock();	//LOCK
		}
	}



}

PROP *GetProp(void)
{
	return &g_aProp[0];
}

