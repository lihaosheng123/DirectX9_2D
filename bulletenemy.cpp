#include "main.h"
#include "bulletenemy.h"
#include "polygon.h"
#include "score.h"
#include "explosion.h"
#include "fade.h"
#include "life.h"
#include "pause.h"
//彈の構造体///////////////
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	int nLife;
	bool bUse;
} BulletEnemy;
/////////////////////////

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBulletEnemy = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBulletEnemy =NULL;
BulletEnemy g_aBulletEnemy [BULLETENEMY_MAX];
float BulletEnemyWidth = 60.0f;		//弾の幅
float BulletEnemyHeight = 60.0f;		//弾の高さ

//=============================================================================
//  関数名　：InitBulletEnemy
//  機能概要：弾の初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitBulletEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*(BULLETENEMY_MAX*4),D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffBulletEnemy,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *pVtx;
		g_pVtxBuffBulletEnemy ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\bulletenemy.png",
		&g_pTextureBulletEnemy);
	for(int i = 0; i < BULLETENEMY_MAX; i++)
	{
				pVtx[0+(4*i)].pos = D3DXVECTOR3( g_aBulletEnemy[i].pos.x- (BulletEnemyWidth/2) ,
												 g_aBulletEnemy[i].pos.y- (BulletEnemyHeight/2) ,
												 0.0f);
				pVtx[1+(4*i)].pos = D3DXVECTOR3( g_aBulletEnemy[i].pos.x+ (BulletEnemyWidth/2) ,
												 g_aBulletEnemy[i].pos.y- (BulletEnemyHeight/2) ,
												 0.0f);
				pVtx[2+(4*i)].pos = D3DXVECTOR3( g_aBulletEnemy[i].pos.x- (BulletEnemyWidth/2) ,
												 g_aBulletEnemy[i].pos.y+ (BulletEnemyHeight/2) ,
												 0.0f);
				pVtx[3+(4*i)].pos = D3DXVECTOR3( g_aBulletEnemy[i].pos.x+ (BulletEnemyWidth/2) ,
												 g_aBulletEnemy[i].pos.y+ (BulletEnemyHeight/2) ,
												 0.0f);

		pVtx[0+(4*i)].rhw = 1.0f;
		pVtx[1+(4*i)].rhw = 1.0f;
		pVtx[2+(4*i)].rhw = 1.0f;
		pVtx[3+(4*i)].rhw = 1.0f;

		pVtx[0+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255,127 );	//頂点情報格納ワーク
		pVtx[1+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		pVtx[2+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		pVtx[3+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);

		pVtx[0+(4*i)].tex = D3DXVECTOR2(0.0f, 0.0f );
		pVtx[1+(4*i)].tex = D3DXVECTOR2(1.f,0.0f);
		pVtx[2+(4*i)].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3+(4*i)].tex = D3DXVECTOR2(1.0f, 1.0f);

		g_aBulletEnemy[i].bUse = false;	 /* 弾を未使用状態に */
	}
	g_pVtxBuffBulletEnemy ->Unlock();	//LOCK
	return S_OK;

}
/*******************************************************************************
* 関数 :void UpdateBulletEnemy(void)
* 説明 :	弾の更新処理初期化処理の関数。
*******************************************************************************/
void UpdateBulletEnemy(void)
{
	PAUSEUSE *bUseCheck = GetPause();
	if(bUseCheck->bUse == false)
	{
	VERTEX_2D *pVtx;
	g_pVtxBuffBulletEnemy ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得

	for(int i= 0;i<BULLETENEMY_MAX;i++)
	{
		if(g_aBulletEnemy[i].bUse == true)/* 弾が使用*/
			{
				g_aBulletEnemy[i].pos-=g_aBulletEnemy[i].move;
				/* 位置を更新 */
				pVtx[0+(4*i)].pos= D3DXVECTOR3( g_aBulletEnemy[i].pos.x-(BulletEnemyWidth/2) ,
												 g_aBulletEnemy[i].pos.y-(BulletEnemyHeight/2) ,
												 0.0f);
				pVtx[1+(4*i)].pos = D3DXVECTOR3( g_aBulletEnemy[i].pos.x+(BulletEnemyWidth/2) ,
												 g_aBulletEnemy[i].pos.y-(BulletEnemyHeight/2) ,
												 0.0f);
				pVtx[2+(4*i)].pos = D3DXVECTOR3( g_aBulletEnemy[i].pos.x- (BulletEnemyWidth/2) ,
												 g_aBulletEnemy[i].pos.y+ (BulletEnemyHeight/2) ,
												 0.0f);
				pVtx[3+(4*i)].pos = D3DXVECTOR3( g_aBulletEnemy[i].pos.x+ (BulletEnemyWidth/2) ,
												 g_aBulletEnemy[i].pos.y+(BulletEnemyHeight/2) ,
												 0.0f);
				POLYGON *pPolygon = GetPolygon();
					if(pPolygon->bUse == true)
					{
						if(bUseTalk == false)
						{
						if(( g_aBulletEnemy[i].pos.x- (BulletEnemyWidth/2))>=(pPolygon->pos.x -(pPolygon->fWidth)/2)
							&&( g_aBulletEnemy[i].pos.x+ (BulletEnemyWidth/2))<=(pPolygon->pos.x+(pPolygon->fWidth)/2)
							&&( g_aBulletEnemy[i].pos.y- (BulletEnemyHeight/2))>=(pPolygon->pos.y -(pPolygon->fHeight)/2)
							&&( g_aBulletEnemy[i].pos.y+ (BulletEnemyHeight/2))<=(pPolygon->pos.y+(pPolygon->fHeight)/2))
						{
							SetExplosion(D3DXVECTOR3(g_aBulletEnemy[i].pos.x,g_aBulletEnemy[i].pos.y,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),1);
							pPolygon->nLife--;
							UpdateLife();
							if(pPolygon->nLife <= 0)
							{
								SetFade(FADE_OUT,MODE_RESULT);
							}
							g_aBulletEnemy[i].bUse = false;
						}
						}
					}
			}
		if(g_aBulletEnemy[i].pos.x < 0.0f
			|| g_aBulletEnemy[i].pos.x > SCREEN_WIDTH
			|| g_aBulletEnemy[i].pos.y < 0.0f
			|| g_aBulletEnemy[i].pos.y > SCREEN_HEIGHT)
		/* 弾が画面外に */
			{
				/* 前回の位置での弾を消去 */
				g_aBulletEnemy[i].bUse = false;		/* 弾を未使用状態に */
			}
	}
	g_pVtxBuffBulletEnemy ->Unlock();	//LOCK
	}
}

/*******************************************************************************
* 関数 :void SetBulletEnemy (D3DXVECTOR3 pos,D3DXVECTOR3 vecMove,int nLife)
* 説明 :	弾の生成の関数。
*******************************************************************************/
void SetBulletEnemy (D3DXVECTOR3 posEnemy,D3DXVECTOR3 vecMoveEnemy,int nLifeEnemy)
{
	for(int i = 0; i< BULLETENEMY_MAX; i++)
	{
		if(g_aBulletEnemy[i].bUse == false)
		{/* 弾が未使用状態 */
			g_aBulletEnemy[i].pos.x = posEnemy.x;
			g_aBulletEnemy[i].pos.y = posEnemy.y;
			g_aBulletEnemy[i].move.x =vecMoveEnemy.x;
			g_aBulletEnemy[i].move.y = vecMoveEnemy.y;
			g_aBulletEnemy[i].nLife = nLifeEnemy;
			g_aBulletEnemy[i].bUse = true;	 /* 弾を使用状態に */
			break;
		}
	}

}
//=============================================================================
//  関数名　：DrawBulletEnemy
//  機能概要：弾の描画処理
//  戻り値　：
//=============================================================================
void DrawBulletEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureBulletEnemy);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffBulletEnemy,
								0,
								sizeof(VERTEX_2D)
								);
	for(int i = 0; i < BULLETENEMY_MAX; i++)
	{
		if(g_aBulletEnemy[i].bUse == true)
		{
	// フェードの描画設定内容
	pDevice -> DrawPrimitive(
							  D3DPT_TRIANGLESTRIP,		// プリミティブの種類
							  4*i,		// 最初の頂点のインデックス
							  2			// 描画するプリミティブ数
							);
		}
	}

}
/*******************************************************************************
* 関数 :void UpdateBulletEnemy(void)
* 説明 :	弾の終了処理初期化処理の関数。
*******************************************************************************/
void UnintBulletEnemy(void)
{
	if(g_pTextureBulletEnemy!=NULL)
	{
		g_pTextureBulletEnemy->Release();
		g_pTextureBulletEnemy=NULL;
	}
	if(g_pVtxBuffBulletEnemy!=NULL)
	{
		g_pVtxBuffBulletEnemy->Release();		//頂点バッファの開放
		g_pVtxBuffBulletEnemy=NULL;
	}
}