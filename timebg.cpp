#include "main.h"
#include "timebg.h"
#include "input.h"
#include "pause.h"
//マクロ定義
#define TIMEBG_MAX (2)
//グローバル変数
VERTEX_2D g_aTimebgtex[4];
LPDIRECT3DTEXTURE9 g_pTextureTimebg =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimebg =NULL;	//頂点パッファへのポインタ
int g_nTimebg;		//スコアの数
int animMaxnumTimebg= 10;		//0~9
float maxTimebgX = 10.0f;
float maxTimebgY = 1.0f;
int g_nCounterAnimTimebg;		//アンメーションカウンタ
int g_nPatternAnimTimebg;		//アンメーションパターンNO
float TimebgHeight = 60.0f;
float TimebgWidth = 40.0f;
float TimebgCoordX =500.0f;
float TimebgCoordY = 0.0f;
float animTimebg =1.0f;
float startAnimYTimebg = 0.0f;
int nTimebg [TIMEBG_MAX];
TIME g_time;
//=============================================================================
//  関数名　：InitTimebg
//  機能概要：スコアの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitTimebg(void)
{
	g_time.time =0 ;
	g_time.frame = 0;
	g_nTimebg= 60;		//
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//初期化処理
	g_nCounterAnimTimebg = 0;
	g_nPatternAnimTimebg = 0;
//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*(4*TIMEBG_MAX),D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffTimebg,NULL)))
	{
		return E_FAIL;
	}
	VERTEX_2D *pVtx;
		g_pVtxBuffTimebg ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(
			pDevice,
			".\\data\\TEXTURE\\timebg.png",
		&g_pTextureTimebg);
	for(int i= 0;i<TIMEBG_MAX;i++)
	{
		pVtx[0+(4*i)].tex = D3DXVECTOR2(0.0f, 0.0f );
		pVtx[1+(4*i)].tex = D3DXVECTOR2(0.1f,0.0f);
		pVtx[2+(4*i)].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3+(4*i)].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx[0+(4*i)].pos = D3DXVECTOR3( TimebgCoordX+(i*TimebgWidth), TimebgCoordY, 0.0f);
		pVtx[1+(4*i)].pos = D3DXVECTOR3( TimebgCoordX + TimebgWidth+(i*TimebgWidth), TimebgCoordY, 0.0f);
		pVtx[2+(4*i)].pos = D3DXVECTOR3( TimebgCoordX+(i*TimebgWidth) , TimebgCoordY + TimebgHeight, 0.0f);
		pVtx[3+(4*i)].pos = D3DXVECTOR3( TimebgCoordX + TimebgWidth+(i*TimebgWidth), TimebgCoordY + TimebgHeight, 0.0f);

		pVtx[0+(4*i)].rhw = 1.0f;
		pVtx[1+(4*i)].rhw = 1.0f;
		pVtx[2+(4*i)].rhw = 1.0f;
		pVtx[3+(4*i)].rhw = 1.0f;

		pVtx[0+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255,127 );	//頂点情報格納ワーク
		pVtx[1+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		pVtx[2+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		pVtx[3+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		}
		g_pVtxBuffTimebg ->Unlock();	//LOCK

		return S_OK;
}
//=============================================================================
//  関数名　：UninitTimebg
//  機能概要：スコアの終了処理
//  戻り値　：
//=============================================================================
void UninitTimebg(void)
{

	if(g_pVtxBuffTimebg!=NULL)
	{
		g_pVtxBuffTimebg->Release();		//頂点バッファの開放
		g_pVtxBuffTimebg=NULL;
	}
	if(g_pTextureTimebg!=NULL)
	{
		g_pTextureTimebg->Release();
		g_pTextureTimebg=NULL;
	}
}
//=============================================================================
//  関数名　：DrawTimebg
//  機能概要：スコアの描画処理
//  戻り値　：
//=============================================================================
void DrawTimebg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureTimebg);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffTimebg,
								0,
								sizeof(VERTEX_2D)
								);
	for(int i=0;i<TIMEBG_MAX;i++)
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
//  関数名　：UpdateTimebg
//  機能概要：スコアの更新処理
//  戻り値　：
//=============================================================================
void UpdateTimebg(void)
{
	PAUSEUSE *bUseCheck = GetPause();
	if(bUseCheck->bUse == false)
	{
	if(g_time.frame>=60)
	{
		g_time.time ++;
		g_time.frame = 0;
		AddTimebg(-1);
	}
	else
	{
		g_time.frame++;
	}
	//nTimebg[0] =g_nTimebg / 10000000 % 100;		//千万
	//nTimebg[1] =g_nTimebg / 1000000 % 10;		//100万
	//nTimebg[2] =g_nTimebg / 100000 % 10;		//10万
	//nTimebg[3] =g_nTimebg / 10000 % 10;		//1万
	//nTimebg[4] =g_nTimebg / 1000 % 10;		//1千
	//nTimebg[5] =g_nTimebg / 100 % 10;		//100
	nTimebg[0] =g_nTimebg / 10 % 10;		//10
	nTimebg[1] =g_nTimebg / 1 % 10;		//1
	VERTEX_2D *pVtx;
	g_pVtxBuffTimebg ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得

	for(int i= 0;i<TIMEBG_MAX;i++)
	{

		pVtx[0+(4*i)].tex = D3DXVECTOR2(0.1f*nTimebg[i], 0.0f );
		pVtx[1+(4*i)].tex = D3DXVECTOR2(0.1f*nTimebg[i]+0.1f,0.0f);
		pVtx[2+(4*i)].tex = D3DXVECTOR2(0.1f*nTimebg[i], 1.0f);
		pVtx[3+(4*i)].tex = D3DXVECTOR2(0.1f*nTimebg[i]+0.1f,1.0f);

	}
		g_pVtxBuffTimebg ->Unlock();	//LOCK
	}
}
/*******************************************************************************
* 関数名:AddTimebg
* 
* 引数  : value
* 戻り値: ナシ
*******************************************************************************/
void AddTimebg(int valueTimebg)
{	
	g_nTimebg +=valueTimebg;
}

