#include "main.h"
#include "explosionenemy.h"
//彈の構造体///////////////
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	int nLife;
}EXPLOSIONENEMY;
/////////////////////////

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureExplosionenemy = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosionenemy =NULL;
EXPLOSIONENEMY g_aExplosionenemy [MAX_EXPLOSIONENEMY];
float ExplosionenemyWidth = 100.0f;		//弾の幅
float ExplosionenemyHeight = 100.0f;		//弾の高さ

//=============================================================================	
//  関数名　：InitExplosionenemy
//  機能概要：弾の初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitExplosionenemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*(MAX_EXPLOSIONENEMY*4),D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffExplosionenemy,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *pVtx;
		g_pVtxBuffExplosionenemy ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\explosionenemy.png",
		&g_pTextureExplosionenemy);
	for(int i = 0; i < MAX_EXPLOSIONENEMY; i++)
	{
				pVtx[0+(4*i)].pos = D3DXVECTOR3( g_aExplosionenemy[i].pos.x- (ExplosionenemyWidth/2) ,
												 g_aExplosionenemy[i].pos.y- (ExplosionenemyHeight/2) ,
												 0.0f);
				pVtx[1+(4*i)].pos = D3DXVECTOR3( g_aExplosionenemy[i].pos.x+ (ExplosionenemyWidth/2) ,
												 g_aExplosionenemy[i].pos.y- (ExplosionenemyHeight/2) ,
												 0.0f);
				pVtx[2+(4*i)].pos = D3DXVECTOR3( g_aExplosionenemy[i].pos.x- (ExplosionenemyWidth/2) ,
												 g_aExplosionenemy[i].pos.y+ (ExplosionenemyHeight/2) ,
												 0.0f);
				pVtx[3+(4*i)].pos = D3DXVECTOR3( g_aExplosionenemy[i].pos.x+ (ExplosionenemyWidth/2) ,
												 g_aExplosionenemy[i].pos.y+ (ExplosionenemyHeight/2) ,
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

		bUseExplosionenemy = false;	 /* 弾を未使用状態に */
	}
	g_pVtxBuffExplosionenemy ->Unlock();	//LOCK
	return S_OK;

}
/*******************************************************************************
* 関数 :void UpdateExplosionenemy(void)
* 説明 :	弾の更新処理初期化処理の関数。
*******************************************************************************/
void UpdateExplosionenemy(void)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffExplosionenemy ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得

	for(int i= 0;i<MAX_EXPLOSIONENEMY;i++)
	{
		if(bUseExplosionenemy == true)/* 弾が使用*/
			{
				/* 位置を更新 */
				pVtx[0+(4*i)].pos= D3DXVECTOR3( g_aExplosionenemy[i].pos.x-(ExplosionenemyWidth/2) ,
												 g_aExplosionenemy[i].pos.y-(ExplosionenemyHeight/2) ,
												 0.0f);
				pVtx[1+(4*i)].pos = D3DXVECTOR3( g_aExplosionenemy[i].pos.x+(ExplosionenemyWidth/2) ,
												 g_aExplosionenemy[i].pos.y-(ExplosionenemyHeight/2) ,
												 0.0f);
				pVtx[2+(4*i)].pos = D3DXVECTOR3( g_aExplosionenemy[i].pos.x- (ExplosionenemyWidth/2) ,
												 g_aExplosionenemy[i].pos.y+ (ExplosionenemyHeight/2) ,
												 0.0f);
				pVtx[3+(4*i)].pos = D3DXVECTOR3( g_aExplosionenemy[i].pos.x+ (ExplosionenemyWidth/2) ,
												 g_aExplosionenemy[i].pos.y+(ExplosionenemyHeight/2) ,
												 0.0f);


			}
		if(g_aExplosionenemy[i].pos.x < 0.0f
			|| g_aExplosionenemy[i].pos.x > SCREEN_WIDTH
			|| g_aExplosionenemy[i].pos.y < 0.0f
			|| g_aExplosionenemy[i].pos.y > SCREEN_HEIGHT)
		/* 弾が画面外に */
			{
				/* 前回の位置での弾を消去 */
				bUseExplosionenemy = false;		/* 弾を未使用状態に */
			}
	}
	g_pVtxBuffExplosionenemy ->Unlock();	//LOCK
}

/*******************************************************************************
* 関数 :void SetExplosionenemy (D3DXVECTOR3 pos,D3DXVECTOR3 vecMove,int nLife)
* 説明 :	弾の生成の関数。
*******************************************************************************/
void SetExplosionenemy (D3DXVECTOR3 pos,D3DXVECTOR3 vecMove,int nLife)
{
	for(int i = 0; i< MAX_EXPLOSIONENEMY; i++)
	{
		if(bUseExplosionenemy == false)
		{/* 弾が未使用状態 */
			g_aExplosionenemy[i].pos.x = pos.x;
			g_aExplosionenemy[i].pos.y = pos.y;
			g_aExplosionenemy[i].move.x =vecMove.x;
			g_aExplosionenemy[i].move.y = vecMove.y;
			g_aExplosionenemy[i].nLife = nLife;
			bUseExplosionenemy = true;	 /* 弾を使用状態に */
			break;
		}
	}

}
//=============================================================================
//  関数名　：DrawExplosionenemy
//  機能概要：弾の描画処理
//  戻り値　：
//=============================================================================
void DrawExplosionenemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureExplosionenemy);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffExplosionenemy,
								0,
								sizeof(VERTEX_2D)
								);
	for(int i = 0; i < MAX_EXPLOSIONENEMY; i++)
	{
		if(bUseExplosionenemy == true)
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
* 関数 :void UpdateExplosionenemy(void)
* 説明 :	弾の終了処理初期化処理の関数。
*******************************************************************************/
void UninitExplosionenemy(void)
{
	if(g_pTextureExplosionenemy!=NULL)
	{
		g_pTextureExplosionenemy->Release();
		g_pTextureExplosionenemy=NULL;
	}
	if(g_pVtxBuffExplosionenemy!=NULL)
	{
		g_pVtxBuffExplosionenemy->Release();		//頂点バッファの開放
		g_pVtxBuffExplosionenemy=NULL;
	}
}