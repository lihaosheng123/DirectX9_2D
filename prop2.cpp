#include "main.h"
#include "prop2.h"
#include "input.h"
//グローバル変数
PROP2 g_aProp2[MAX_PROP2];
LPDIRECT3DTEXTURE9 g_pTextureProp2 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffProp2 =NULL;	//頂点パッファへのポインタ
D3DXVECTOR3 g_posProp2;	//ポリゴンの位置
D3DXVECTOR3 g_rotProp2;		//ポリゴンの回転角
D3DXVECTOR3 g_moveProp2;		//ポリゴンの移動量
float animRow_Prop2 =1.0f;
float maxAnimX_Prop2 = 2.0f;
float maxAnimY_Prop2 = 1.0f;
float g_fLengthProp2;		//ポリゴンの対角線の長さ
float g_fAngleProp2;		//ポリゴンの対角線の角度
float move_Prop2 = 2.0f;		//移動量
float runSpeed_Prop2 = 3.0f;
int animMaxnum_Prop2 = 2;
float startAnimY_Prop2 = 0.0f;
bool bUseComputer;
//=============================================================================
//  関数名　：InitProp2
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitProp2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffProp2,NULL)))
	{
		return E_FAIL;
	}
		VERTEX_2D *pVtx;
		g_pVtxBuffProp2 ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得
		//テクスチャの読み込み	
		D3DXCreateTextureFromFile(
			pDevice,
			".\\data\\TEXTURE\\prop.png",
		&g_pTextureProp2);
		 bProp2 = false;

		g_aProp2[0].fHeight=50.0f;
		g_aProp2[0].fWidth=150.0f;
			//初期化処理
		g_aProp2[0].pos.x = 1115.0f;
		g_aProp2[0].pos.y = 540.0f;
		g_posProp2 = D3DXVECTOR3(g_aProp2[0].pos.x,g_aProp2[0].pos.y,0.0f);
		
			//回転初期化処理
		g_rotProp2 = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_fLengthProp2 =sqrtf(g_aProp2[0].fWidth * g_aProp2[0].fWidth + g_aProp2[0].fHeight * g_aProp2[0].fHeight)*0.5f;
		g_fAngleProp2 =atan2f(g_aProp2[0].fWidth,g_aProp2[0].fHeight)*0.5f;


		
		//頂点座標設定
		pVtx[0].pos = D3DXVECTOR3 (g_aProp2[0].pos.x - sinf( g_fAngleProp2 + g_rotProp2.z ) * g_fLengthProp2,
								   g_aProp2[0].pos.y - cosf( g_fAngleProp2 + g_rotProp2.z ) * g_fLengthProp2,
								   0.0f);

		pVtx[1].pos = D3DXVECTOR3 (g_aProp2[0].pos.x + sinf( g_fAngleProp2 - g_rotProp2.z ) * g_fLengthProp2,
								   g_aProp2[0].pos.y - cosf( g_fAngleProp2 - g_rotProp2.z ) * g_fLengthProp2,
								   0.0f);

		pVtx[2].pos = D3DXVECTOR3 (g_aProp2[0].pos.x - sinf( g_fAngleProp2 - g_rotProp2.z ) * g_fLengthProp2,
								   g_aProp2[0].pos.y + cosf( g_fAngleProp2 - g_rotProp2.z ) * g_fLengthProp2,
								   0.0f);

		pVtx[3].pos = D3DXVECTOR3 (g_aProp2[0].pos.x + sinf( g_fAngleProp2 + g_rotProp2.z ) * g_fLengthProp2,
								   g_aProp2[0].pos.y + cosf( g_fAngleProp2 + g_rotProp2.z ) * g_fLengthProp2,
								   0.0f);


			pVtx[0].tex = D3DXVECTOR2(1.0f / maxAnimX_Prop2, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(2.0f / maxAnimX_Prop2,0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f / maxAnimX_Prop2, 1.0f / maxAnimY_Prop2);
			pVtx[3].tex = D3DXVECTOR2(2.0f / maxAnimX_Prop2, 1.0f / maxAnimY_Prop2);


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

		g_pVtxBuffProp2 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：UninitProp2
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitProp2(void)
{

	if(g_pVtxBuffProp2!=NULL)
	{
		g_pVtxBuffProp2->Release();		//頂点バッファの開放
		g_pVtxBuffProp2=NULL;
	}
	if(g_pTextureProp2!=NULL)
	{
		g_pTextureProp2->Release();
		g_pTextureProp2=NULL;
	}
}
//=============================================================================
//  関数名　：DrawProp2
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawProp2(void)
{
	//if(bProp2 == false )
	//{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureProp2);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffProp2,
								0,
								sizeof(VERTEX_2D)
								);
	// フェードの描画設定内容
	pDevice -> DrawPrimitive(
							  D3DPT_TRIANGLESTRIP,		// プリミティブの種類
							  0,		// 最初の頂点のインデックス
							  2			// 描画するプリミティブ数
							);
	//}
}
//=============================================================================
//  関数名　：UpdateProp2
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateProp2(void)
{
	if( bProp2 ==true)
	{
	g_aProp2[0].pos.y++;
	}
	if(g_aProp2[0].pos.y >=600.0f)
	{
		bUseComputer = false;
		g_aProp2[0].pos.y = 600.0f;
	}
		VERTEX_2D *pVtx;
		g_pVtxBuffProp2 ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得


		
		//頂点座標設定
		pVtx[0].pos = D3DXVECTOR3 (g_aProp2[0].pos.x - sinf( g_fAngleProp2 + g_rotProp2.z ) * g_fLengthProp2,
								   g_aProp2[0].pos.y - cosf( g_fAngleProp2 + g_rotProp2.z ) * g_fLengthProp2,
								   0.0f);

		pVtx[1].pos = D3DXVECTOR3 (g_aProp2[0].pos.x + sinf( g_fAngleProp2 - g_rotProp2.z ) * g_fLengthProp2,
								   g_aProp2[0].pos.y - cosf( g_fAngleProp2 - g_rotProp2.z ) * g_fLengthProp2,
								   0.0f);

		pVtx[2].pos = D3DXVECTOR3 (g_aProp2[0].pos.x - sinf( g_fAngleProp2 - g_rotProp2.z ) * g_fLengthProp2,
								   g_aProp2[0].pos.y + cosf( g_fAngleProp2 - g_rotProp2.z ) * g_fLengthProp2,
								   0.0f);

		pVtx[3].pos = D3DXVECTOR3 (g_aProp2[0].pos.x + sinf( g_fAngleProp2 + g_rotProp2.z ) * g_fLengthProp2,
								   g_aProp2[0].pos.y + cosf( g_fAngleProp2 + g_rotProp2.z ) * g_fLengthProp2,
								   0.0f);


			pVtx[0].tex = D3DXVECTOR2(1.0f / maxAnimX_Prop2, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(2.0f / maxAnimX_Prop2,0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f / maxAnimX_Prop2, 1.0f / maxAnimY_Prop2);
			pVtx[3].tex = D3DXVECTOR2(2.0f / maxAnimX_Prop2, 1.0f / maxAnimY_Prop2);


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

		g_pVtxBuffProp2 ->Unlock();	//LOCK

}

PROP2 *GetProp2(void)
{
	return &g_aProp2[0];
}

