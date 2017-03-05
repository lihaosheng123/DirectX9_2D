#include "main.h"
#include "lifeenemy.h"
#include "score.h"
//グローバル変数
VERTEX_2D g_aLifeenemytex[4];
LPDIRECT3DTEXTURE9 g_pTextureLifeenemy =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLifeenemy =NULL;	//頂点パッファへのポインタ
int g_nCounterAnim_Lifeenemy;		//アンメーションカウンタ
int g_nPatternAnim_Lifeenemy;		//アンメーションパターンNO
float animRow_Lifeenemy =1.0f;
int g_nLifeenemy;		//スコアの数
float maxAnimX_Lifeenemy = 1.0f;
float maxAnimY_Lifeenemy = 1.0f;
int g_nCounterAnimLifeenemy;		//アンメーションカウンタ
int g_nPatternAnimLifeenemy;		//アンメーションパターンNO
float LifeenemyHeight = 50.0f;
float LifeenemyWidth = 50.0f;
float LifeenemyCoordX = 600.0f;
float LifeenemyCoordY = 0.0f;
float animLifeenemy =1.0f;
float runSpeed_Lifeenemy = 1.0f;
int animMaxnum_Lifeenemy = 1;
float startAnimY_Lifeenemy = 0.0f;
int nLifeenemy = MAX_LIFEENMEY;
float LifeenemyX= 5.0f;
bool bUseLifechangeenemy = true;
//=============================================================================
//  関数名　：InitLifeenemy
//  機能概要：スコアの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitLifeenemy(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//初期化処理
	g_nCounterAnimLifeenemy = 0;
	g_nPatternAnimLifeenemy = 0;
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*(4*MAX_LIFEENMEY),D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffLifeenemy,NULL)))
	{
		return E_FAIL;
	}
	VERTEX_2D *pVtx;
		g_pVtxBuffLifeenemy ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(
			pDevice,
			".\\data\\TEXTURE\\lifeenemy.png",
		&g_pTextureLifeenemy);
		nLifeenemy =MAX_LIFEENMEY;
		bUseLifechangeenemy =true;
	for(int i= 0;i<MAX_LIFEENMEY;i++)
	{
		//UV設定
		pVtx[0+(4*i)].tex = D3DXVECTOR2(0.0f, 0.0f );
		pVtx[1+(4*i)].tex = D3DXVECTOR2(1.0f / maxAnimX_Lifeenemy,0.0f);
		pVtx[2+(4*i)].tex = D3DXVECTOR2(0.0f, 1.0f / maxAnimY_Lifeenemy);
		pVtx[3+(4*i)].tex = D3DXVECTOR2(1.0f / maxAnimX_Lifeenemy, 1.0f / maxAnimY_Lifeenemy);

		pVtx[0+(4*i)].pos = D3DXVECTOR3( LifeenemyCoordX+(i*LifeenemyWidth)+(i*LifeenemyX), LifeenemyCoordY, 0.0f);
		pVtx[1+(4*i)].pos = D3DXVECTOR3( LifeenemyCoordX + LifeenemyWidth+(i*LifeenemyWidth)+(i*LifeenemyX), LifeenemyCoordY, 0.0f);
		pVtx[2+(4*i)].pos = D3DXVECTOR3( LifeenemyCoordX+(i*LifeenemyWidth)+(i*LifeenemyX) , LifeenemyCoordY + LifeenemyHeight, 0.0f);
		pVtx[3+(4*i)].pos = D3DXVECTOR3( LifeenemyCoordX + LifeenemyWidth+(i*LifeenemyWidth)+(i*LifeenemyX), LifeenemyCoordY + LifeenemyHeight, 0.0f);

		pVtx[0+(4*i)].rhw = 1.0f;
		pVtx[1+(4*i)].rhw = 1.0f;
		pVtx[2+(4*i)].rhw = 1.0f;
		pVtx[3+(4*i)].rhw = 1.0f;

		pVtx[0+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255,127 );	//頂点情報格納ワーク
		pVtx[1+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		pVtx[2+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		pVtx[3+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		}
		g_pVtxBuffLifeenemy ->Unlock();	//LOCK

		return S_OK;
}
//=============================================================================
//  関数名　：UninitLifeenemy
//  機能概要：スコアの終了処理
//  戻り値　：
//=============================================================================
void UninitLifeenemy(void)
{

	if(g_pVtxBuffLifeenemy!=NULL)
	{
		g_pVtxBuffLifeenemy->Release();		//頂点バッファの開放
		g_pVtxBuffLifeenemy=NULL;
	}
	if(g_pTextureLifeenemy!=NULL)
	{
		g_pTextureLifeenemy->Release();
		g_pTextureLifeenemy=NULL;
	}
}
//=============================================================================
//  関数名　：DrawLifeenemy
//  機能概要：スコアの描画処理
//  戻り値　：
//=============================================================================
void DrawLifeenemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureLifeenemy);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffLifeenemy,
								0,
								sizeof(VERTEX_2D)
								);
	for(int i=0;i<nLifeenemy;i++)
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
//  関数名　：UpdateLifeenemy
//  機能概要：スコアの更新処理
//  戻り値　：
//=============================================================================
void UpdateLifeenemy(void)
{

	nLifeenemy=nLifeenemy--;

}
