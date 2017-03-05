#include "main.h"
#include "life.h"
//グローバル変数
VERTEX_2D g_aLifetex[4];
LPDIRECT3DTEXTURE9 g_pTextureLife =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife =NULL;	//頂点パッファへのポインタ
int g_nCounterAnim_Life;		//アンメーションカウンタ
int g_nPatternAnim_Life;		//アンメーションパターンNO
float animRow_Life =1.0f;
int g_nLife;		//スコアの数
float maxAnimX_Life = 6.0f;
float maxAnimY_Life = 1.0f;
int g_nCounterAnimLife;		//アンメーションカウンタ
int g_nPatternAnimLife;		//アンメーションパターンNO
float LifeHeight = 120.0f;
float LifeWidth = 130.0f;
float LifeCoordX = 0.0f;
float LifeCoordY = 0.0f;
float animLife =1.0f;
float runSpeed_Life = 1.0f;
int animMaxnum_Life = 6;
float startAnimY_Life = 0.0f;
int nLife = MAX_LIFE;
float LifeX= 10.0f;
//=============================================================================
//  関数名　：InitLife
//  機能概要：スコアの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitLife(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//初期化処理
	g_nCounterAnimLife = 0;
	g_nPatternAnimLife = 0;
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*(4*MAX_LIFE),D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffLife,NULL)))
	{
		return E_FAIL;
	}
	VERTEX_2D *pVtx;
		g_pVtxBuffLife ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(
			pDevice,
			".\\data\\TEXTURE\\life.png",
		&g_pTextureLife);
		nLife =MAX_LIFE;
	for(int i= 0;i<MAX_LIFE;i++)
	{
		//UV設定
		pVtx[0+(4*i)].tex = D3DXVECTOR2(0.0f, 0.0f );
		pVtx[1+(4*i)].tex = D3DXVECTOR2(1.0f / maxAnimX_Life,0.0f);
		pVtx[2+(4*i)].tex = D3DXVECTOR2(0.0f, 1.0f / maxAnimY_Life);
		pVtx[3+(4*i)].tex = D3DXVECTOR2(1.0f / maxAnimX_Life, 1.0f / maxAnimY_Life);

		pVtx[0+(4*i)].pos = D3DXVECTOR3( LifeCoordX+(i*LifeWidth)+(i*LifeX), LifeCoordY, 0.0f);
		pVtx[1+(4*i)].pos = D3DXVECTOR3( LifeCoordX + LifeWidth+(i*LifeWidth)+(i*LifeX), LifeCoordY, 0.0f);
		pVtx[2+(4*i)].pos = D3DXVECTOR3( LifeCoordX+(i*LifeWidth)+(i*LifeX) , LifeCoordY + LifeHeight, 0.0f);
		pVtx[3+(4*i)].pos = D3DXVECTOR3( LifeCoordX + LifeWidth+(i*LifeWidth)+(i*LifeX), LifeCoordY + LifeHeight, 0.0f);

		pVtx[0+(4*i)].rhw = 1.0f;
		pVtx[1+(4*i)].rhw = 1.0f;
		pVtx[2+(4*i)].rhw = 1.0f;
		pVtx[3+(4*i)].rhw = 1.0f;

		pVtx[0+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255,127 );	//頂点情報格納ワーク
		pVtx[1+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		pVtx[2+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		pVtx[3+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		}
		g_pVtxBuffLife ->Unlock();	//LOCK

		return S_OK;
}
//=============================================================================
//  関数名　：UninitLife
//  機能概要：スコアの終了処理
//  戻り値　：
//=============================================================================
void UninitLife(void)
{

	if(g_pVtxBuffLife!=NULL)
	{
		g_pVtxBuffLife->Release();		//頂点バッファの開放
		g_pVtxBuffLife=NULL;
	}
	if(g_pTextureLife!=NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife=NULL;
	}
}
//=============================================================================
//  関数名　：DrawLife
//  機能概要：スコアの描画処理
//  戻り値　：
//=============================================================================
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureLife);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffLife,
								0,
								sizeof(VERTEX_2D)
								);
	for(int i=0;i<nLife;i++)
	{
	// フェードの描画設定内容
	pDevice -> DrawPrimitive(
							  D3DPT_TRIANGLESTRIP,		// プリミティブの種類
							  (0+4*i),		// 最初の頂点のインデックス
							  2			// 描画するプリミティブ数
							);
	}
}
//=============================================================================
//  関数名　：UpdateLife
//  機能概要：スコアの更新処理
//  戻り値　：
//=============================================================================
void UpdateLife(void)
{
	nLife--;
}