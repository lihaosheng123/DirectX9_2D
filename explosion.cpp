#include "main.h"
#include "explosion.h"
//彈の構造体///////////////
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	int nLife;
} EXPLOSION;
/////////////////////////

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion =NULL;
EXPLOSION g_aExplosion [MAX_EXPLOSION];
float ExplosionWidth = 100.0f;		//弾の幅
float ExplosionHeight = 100.0f;		//弾の高さ

//=============================================================================	
//  関数名　：InitExplosion
//  機能概要：弾の初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*(MAX_EXPLOSION*4),D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffExplosion,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *pVtx;
		g_pVtxBuffExplosion ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\explosion.png",
		&g_pTextureExplosion);
	for(int i = 0; i < MAX_EXPLOSION; i++)
	{
				pVtx[0+(4*i)].pos = D3DXVECTOR3( g_aExplosion[i].pos.x- (ExplosionWidth/2) ,
												 g_aExplosion[i].pos.y- (ExplosionHeight/2) ,
												 0.0f);
				pVtx[1+(4*i)].pos = D3DXVECTOR3( g_aExplosion[i].pos.x+ (ExplosionWidth/2) ,
												 g_aExplosion[i].pos.y- (ExplosionHeight/2) ,
												 0.0f);
				pVtx[2+(4*i)].pos = D3DXVECTOR3( g_aExplosion[i].pos.x- (ExplosionWidth/2) ,
												 g_aExplosion[i].pos.y+ (ExplosionHeight/2) ,
												 0.0f);
				pVtx[3+(4*i)].pos = D3DXVECTOR3( g_aExplosion[i].pos.x+ (ExplosionWidth/2) ,
												 g_aExplosion[i].pos.y+ (ExplosionHeight/2) ,
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

		bUseExplosion = false;	 /* 弾を未使用状態に */
	}
	g_pVtxBuffExplosion ->Unlock();	//LOCK
	return S_OK;

}
/*******************************************************************************
* 関数 :void UpdateExplosion(void)
* 説明 :	弾の更新処理初期化処理の関数。
*******************************************************************************/
void UpdateExplosion(void)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffExplosion ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得

	for(int i= 0;i<MAX_EXPLOSION;i++)
	{
		if(bUseExplosion == true)/* 弾が使用*/
			{
				/* 位置を更新 */
				pVtx[0+(4*i)].pos= D3DXVECTOR3( g_aExplosion[i].pos.x-(ExplosionWidth/2) ,
												 g_aExplosion[i].pos.y-(ExplosionHeight/2) ,
												 0.0f);
				pVtx[1+(4*i)].pos = D3DXVECTOR3( g_aExplosion[i].pos.x+(ExplosionWidth/2) ,
												 g_aExplosion[i].pos.y-(ExplosionHeight/2) ,
												 0.0f);
				pVtx[2+(4*i)].pos = D3DXVECTOR3( g_aExplosion[i].pos.x- (ExplosionWidth/2) ,
												 g_aExplosion[i].pos.y+ (ExplosionHeight/2) ,
												 0.0f);
				pVtx[3+(4*i)].pos = D3DXVECTOR3( g_aExplosion[i].pos.x+ (ExplosionWidth/2) ,
												 g_aExplosion[i].pos.y+(ExplosionHeight/2) ,
												 0.0f);


			}
		if(g_aExplosion[i].pos.x < 0.0f
			|| g_aExplosion[i].pos.x > SCREEN_WIDTH
			|| g_aExplosion[i].pos.y < 0.0f
			|| g_aExplosion[i].pos.y > SCREEN_HEIGHT)
		/* 弾が画面外に */
			{
				/* 前回の位置での弾を消去 */
				bUseExplosion = false;		/* 弾を未使用状態に */
			}
	}
	g_pVtxBuffExplosion ->Unlock();	//LOCK
}

/*******************************************************************************
* 関数 :void SetExplosion (D3DXVECTOR3 pos,D3DXVECTOR3 vecMove,int nLife)
* 説明 :	弾の生成の関数。
*******************************************************************************/
void SetExplosion (D3DXVECTOR3 pos,D3DXVECTOR3 vecMove,int nLife)
{
	for(int i = 0; i< MAX_EXPLOSION; i++)
	{
		if(bUseExplosion == false)
		{/* 弾が未使用状態 */
			g_aExplosion[i].pos.x = pos.x;
			g_aExplosion[i].pos.y = pos.y;
			g_aExplosion[i].move.x =vecMove.x;
			g_aExplosion[i].move.y = vecMove.y;
			g_aExplosion[i].nLife = nLife;
			bUseExplosion = true;	 /* 弾を使用状態に */
			break;
		}
	}

}
//=============================================================================
//  関数名　：DrawExplosion
//  機能概要：弾の描画処理
//  戻り値　：
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureExplosion);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffExplosion,
								0,
								sizeof(VERTEX_2D)
								);
	for(int i = 0; i < MAX_EXPLOSION; i++)
	{
		if(bUseExplosion == true)
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
* 関数 :void UpdateExplosion(void)
* 説明 :	弾の終了処理初期化処理の関数。
*******************************************************************************/
void UninitExplosion(void)
{
	if(g_pTextureExplosion!=NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion=NULL;
	}
	if(g_pVtxBuffExplosion!=NULL)
	{
		g_pVtxBuffExplosion->Release();		//頂点バッファの開放
		g_pVtxBuffExplosion=NULL;
	}
}