#include "main.h"
#include "score.h"
#include "input.h"
//マクロ定義
#define SCORE_MAX (4)
//グローバル変数
VERTEX_2D g_aScoretex[4];
LPDIRECT3DTEXTURE9 g_pTextureScore =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore =NULL;	//頂点パッファへのポインタ
int g_nScore;		//スコアの数
int animMaxnum = 10;		//0~9
float maxScoreX = 10.0f;
float maxScoreY = 1.0f;
int g_nCounterAnimScore;		//アンメーションカウンタ
int g_nPatternAnimScore;		//アンメーションパターンNO
float ScoreHeight = 90.0f;
float ScoreWidth = 50.0f;
float ScoreCoordX = 1000.0f;
float ScoreCoordY = 0.0f;
float animScore =1.0f;
float startAnimY = 0.0f;
int nScore [SCORE_MAX];
//=============================================================================
//  関数名　：InitScore
//  機能概要：スコアの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitScore(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//初期化処理
	g_nCounterAnimScore = 0;
	g_nPatternAnimScore = 0;
//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*(4*SCORE_MAX),D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffScore,NULL)))
	{
		return E_FAIL;
	}
	VERTEX_2D *pVtx;
		g_pVtxBuffScore ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(
			pDevice,
			".\\data\\TEXTURE\\score.png",
		&g_pTextureScore);
	for(int i= 0;i<SCORE_MAX;i++)
	{
		pVtx[0+(4*i)].tex = D3DXVECTOR2(0.0f, 0.0f );
		pVtx[1+(4*i)].tex = D3DXVECTOR2(0.1f,0.0f);
		pVtx[2+(4*i)].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3+(4*i)].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx[0+(4*i)].pos = D3DXVECTOR3( ScoreCoordX+(i*ScoreWidth), ScoreCoordY, 0.0f);
		pVtx[1+(4*i)].pos = D3DXVECTOR3( ScoreCoordX + ScoreWidth+(i*ScoreWidth), ScoreCoordY, 0.0f);
		pVtx[2+(4*i)].pos = D3DXVECTOR3( ScoreCoordX+(i*ScoreWidth) , ScoreCoordY + ScoreHeight, 0.0f);
		pVtx[3+(4*i)].pos = D3DXVECTOR3( ScoreCoordX + ScoreWidth+(i*ScoreWidth), ScoreCoordY + ScoreHeight, 0.0f);

		pVtx[0+(4*i)].rhw = 1.0f;
		pVtx[1+(4*i)].rhw = 1.0f;
		pVtx[2+(4*i)].rhw = 1.0f;
		pVtx[3+(4*i)].rhw = 1.0f;

		pVtx[0+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255,127 );	//頂点情報格納ワーク
		pVtx[1+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		pVtx[2+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		pVtx[3+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		}
		g_pVtxBuffScore ->Unlock();	//LOCK

		return S_OK;
}
//=============================================================================
//  関数名　：UninitScore
//  機能概要：スコアの終了処理
//  戻り値　：
//=============================================================================
void UninitScore(void)
{

	if(g_pVtxBuffScore!=NULL)
	{
		g_pVtxBuffScore->Release();		//頂点バッファの開放
		g_pVtxBuffScore=NULL;
	}
	if(g_pTextureScore!=NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore=NULL;
	}
}
//=============================================================================
//  関数名　：DrawScore
//  機能概要：スコアの描画処理
//  戻り値　：
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureScore);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffScore,
								0,
								sizeof(VERTEX_2D)
								);
	for(int i=0;i<SCORE_MAX;i++)
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
//  関数名　：UpdateScore
//  機能概要：スコアの更新処理
//  戻り値　：
//=============================================================================
void UpdateScore(void)
{
	if(GetKeyboardTrigger(DIK_SPACE) == true)
	{
		AddScore(1);
	}
	//nScore[0] =g_nScore / 10000000 % 100;		//千万
	//nScore[1] =g_nScore / 1000000 % 10;		//100万
	//nScore[2] =g_nScore / 100000 % 10;		//10万
	//nScore[3] =g_nScore / 10000 % 10;		//1万
	nScore[0] =g_nScore / 1000 % 10;		//1千
	nScore[1] =g_nScore / 100 % 10;		//100
	nScore[2] =g_nScore / 10 % 10;		//10
	nScore[3] =g_nScore / 1 % 10;		//1
	VERTEX_2D *pVtx;
	g_pVtxBuffScore ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得

	for(int i= 0;i<SCORE_MAX;i++)
	{

		pVtx[0+(4*i)].tex = D3DXVECTOR2(0.1f*nScore[i], 0.0f );
		pVtx[1+(4*i)].tex = D3DXVECTOR2(0.1f*nScore[i]+0.1f,0.0f);
		pVtx[2+(4*i)].tex = D3DXVECTOR2(0.1f*nScore[i], 1.0f);
		pVtx[3+(4*i)].tex = D3DXVECTOR2(0.1f*nScore[i]+0.1f,1.0f);

	}
		g_pVtxBuffScore ->Unlock();	//LOCK
}
/*******************************************************************************
* 関数名:AddScore
* 
* 引数  : value
* 戻り値: ナシ
*******************************************************************************/
void AddScore(int value)
{	
	g_nScore +=value;
}

