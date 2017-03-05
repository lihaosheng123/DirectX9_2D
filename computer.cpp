#include "main.h"
#include "computer.h"
#include "bulletenemy.h"
//グローバル変数
COMPUTER g_aComputer[MAX_COMPUTER];
LPDIRECT3DTEXTURE9 g_pTextureComputer =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffComputer =NULL;	//頂点パッファへのポインタ
D3DXVECTOR3 g_posComputer;	//ポリゴンの位置
D3DXVECTOR3 g_rotComputer;		//ポリゴンの回転角
D3DXVECTOR3 g_moveComputer;		//ポリゴンの移動量
int g_nCounterAnim_Computer;		//アンメーションカウンタ
int g_nPatternAnim_Computer;		//アンメーションパターンNO
float animRow_Computer =1.0f;
float maxAnimX_Computer = 2.0f;
float maxAnimY_Computer = 1.0f;
float g_fLengthComputer;		//ポリゴンの対角線の長さ
float g_fAngleComputer;		//ポリゴンの対角線の角度
float move_Computer = 4.0f;		//移動量

float runSpeed_Computer = 3.0f;
int animMaxnum_Computer = 4;
float startAnimY_Computer = 0.0f;
//=============================================================================
//  関数名　：InitComputer
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitComputer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffComputer,NULL)))
	{
		return E_FAIL;
	}
		VERTEX_2D *pVtx;
		g_pVtxBuffComputer ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得
		//テクスチャの読み込み	
		D3DXCreateTextureFromFile(
			pDevice,
			".\\data\\TEXTURE\\computer.png",
		&g_pTextureComputer);
		 bUseComputer = true ;
		for(int i= 0;i<MAX_COMPUTER;i++)
		{
		g_aComputer[i].fHeight=90.0f;
		g_aComputer[i].fWidth=90.0f;
			//初期化処理

		g_aComputer[i].pos.x = 950.0f;
		g_aComputer[i].pos.y = 220.0f;
		g_posComputer = D3DXVECTOR3(g_aComputer[i].pos.x,g_aComputer[i].pos.y,0.0f);
		}
			//回転初期化処理
		g_rotComputer = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_fLengthComputer =sqrtf(g_aComputer[0].fWidth * g_aComputer[0].fWidth + g_aComputer[0].fHeight * g_aComputer[0].fHeight)*0.5f;
		g_fAngleComputer =atan2f(g_aComputer[0].fWidth,g_aComputer[0].fHeight)*0.5f;

		g_aComputer[0].bUse = true;
		g_aComputer[0].bUpMove = true;
		//頂点座標設定
		pVtx[0].pos = D3DXVECTOR3 (g_aComputer[0].pos.x - sinf( g_fAngleComputer + g_rotComputer.z ) * g_fLengthComputer,
								   g_aComputer[0].pos.y - cosf( g_fAngleComputer + g_rotComputer.z ) * g_fLengthComputer,
								   0.0f);

		pVtx[1].pos = D3DXVECTOR3 (g_aComputer[0].pos.x + sinf( g_fAngleComputer - g_rotComputer.z ) * g_fLengthComputer,
								   g_aComputer[0].pos.y - cosf( g_fAngleComputer - g_rotComputer.z ) * g_fLengthComputer,
								   0.0f);

		pVtx[2].pos = D3DXVECTOR3 (g_aComputer[0].pos.x - sinf( g_fAngleComputer - g_rotComputer.z ) * g_fLengthComputer,
								   g_aComputer[0].pos.y + cosf( g_fAngleComputer - g_rotComputer.z ) * g_fLengthComputer,
								   0.0f);

		pVtx[3].pos = D3DXVECTOR3 (g_aComputer[0].pos.x + sinf( g_fAngleComputer + g_rotComputer.z ) * g_fLengthComputer,
								   g_aComputer[0].pos.y + cosf( g_fAngleComputer + g_rotComputer.z ) * g_fLengthComputer,
								   0.0f);

			pVtx[0].tex = D3DXVECTOR2(1.0f / maxAnimX_Computer, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(2.0f / maxAnimX_Computer,0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f / maxAnimX_Computer, 1.0f / maxAnimY_Computer);
			pVtx[3].tex = D3DXVECTOR2(2.0f / maxAnimX_Computer, 1.0f / maxAnimY_Computer);

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

		g_pVtxBuffComputer ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：UninitComputer
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitComputer(void)
{

	if(g_pVtxBuffComputer!=NULL)
	{
		g_pVtxBuffComputer->Release();		//頂点バッファの開放
		g_pVtxBuffComputer=NULL;
	}
	if(g_pTextureComputer!=NULL)
	{
		g_pTextureComputer->Release();
		g_pTextureComputer=NULL;
	}
}
//=============================================================================
//  関数名　：DrawComputer
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawComputer(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureComputer);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffComputer,
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
//=============================================================================
//  関数名　：UpdateComputer
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateComputer(void)
{

	VERTEX_2D *pVtx;
	g_pVtxBuffComputer ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取

		if((g_aComputer[0].pos.x-g_aComputer[0].fWidth/5) <= 0)
		{
			g_aComputer[0].pos.x = (g_aComputer[0].fWidth/5);
		}
	
		if((g_aComputer[0].pos.x+g_aComputer[0].fWidth/3)>= SCREEN_WIDTH)
		{
			g_aComputer[0].pos.x = SCREEN_WIDTH+-(g_aComputer[0].fWidth/3);
		}

		if((g_aComputer[0].pos.y-g_aComputer[0].fHeight/5) <= 0)
		{
			g_aComputer[0].pos.y=(g_aComputer[0].fHeight/5);
		}

		if((g_aComputer[0].pos.y+g_aComputer[0].fHeight/5) >= SCREEN_HEIGHT)
		{
			g_aComputer[0].pos.y = SCREEN_HEIGHT+-(g_aComputer[0].fHeight/5);
		}

			pVtx[0].pos = D3DXVECTOR3 (g_aComputer[0].pos.x - sinf( g_fAngleComputer + g_rotComputer.z ) * g_fLengthComputer,
									   g_aComputer[0].pos.y - cosf( g_fAngleComputer + g_rotComputer.z ) * g_fLengthComputer,
									   0.0f);

			pVtx[1].pos = D3DXVECTOR3 (g_aComputer[0].pos.x + sinf( g_fAngleComputer - g_rotComputer.z ) * g_fLengthComputer,
									   g_aComputer[0].pos.y - cosf( g_fAngleComputer - g_rotComputer.z ) * g_fLengthComputer,
									   0.0f);
	
			pVtx[2].pos = D3DXVECTOR3 (g_aComputer[0].pos.x - sinf( g_fAngleComputer - g_rotComputer.z ) * g_fLengthComputer,
									   g_aComputer[0].pos.y + cosf( g_fAngleComputer - g_rotComputer.z ) * g_fLengthComputer,
									   0.0f);

			pVtx[3].pos = D3DXVECTOR3 (g_aComputer[0].pos.x + sinf( g_fAngleComputer + g_rotComputer.z ) * g_fLengthComputer,
									   g_aComputer[0].pos.y + cosf( g_fAngleComputer + g_rotComputer.z ) * g_fLengthComputer,
									   0.0f);

		g_pVtxBuffComputer ->Unlock();	//LOCK


		if(  bUseComputer  ==false)
		{
			VERTEX_2D *pVtx;
			g_pVtxBuffComputer ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得
			
			pVtx[0].tex = D3DXVECTOR2(0.0f / maxAnimX_Computer, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(1.0f / maxAnimX_Computer,0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f / maxAnimX_Computer, 1.0f / maxAnimY_Computer);
			pVtx[3].tex = D3DXVECTOR2(1.0f / maxAnimX_Computer, 1.0f / maxAnimY_Computer);

			pVtx[0].pos = D3DXVECTOR3 (g_aComputer[0].pos.x - sinf( g_fAngleComputer + g_rotComputer.z ) * g_fLengthComputer,
									   g_aComputer[0].pos.y - cosf( g_fAngleComputer + g_rotComputer.z ) * g_fLengthComputer,
									   0.0f);

			pVtx[1].pos = D3DXVECTOR3 (g_aComputer[0].pos.x + sinf( g_fAngleComputer - g_rotComputer.z ) * g_fLengthComputer,
									   g_aComputer[0].pos.y - cosf( g_fAngleComputer - g_rotComputer.z ) * g_fLengthComputer,
									   0.0f);
	
			pVtx[2].pos = D3DXVECTOR3 (g_aComputer[0].pos.x - sinf( g_fAngleComputer - g_rotComputer.z ) * g_fLengthComputer,
									   g_aComputer[0].pos.y + cosf( g_fAngleComputer - g_rotComputer.z ) * g_fLengthComputer,
									   0.0f);

			pVtx[3].pos = D3DXVECTOR3 (g_aComputer[0].pos.x + sinf( g_fAngleComputer + g_rotComputer.z ) * g_fLengthComputer,
									   g_aComputer[0].pos.y + cosf( g_fAngleComputer + g_rotComputer.z ) * g_fLengthComputer,
									   0.0f);
				g_pVtxBuffComputer ->Unlock();	//LOCK
				
		}
		else
		{
			ComputerMove();
		}


}

COMPUTER *GetComputer(void)
{
	return &g_aComputer[0];
}
void ComputerMove(void)
{
	if( g_aComputer[0].pos.y <= 210.0f)
	{
		if( bUseComputer  == true)
		{

	SetBulletEnemy(D3DXVECTOR3(g_aComputer[0].pos.x,g_aComputer[0].pos.y,0.0f) ,D3DXVECTOR3(5.0f,-3.0f,0.0f),5);
	SetBulletEnemy(D3DXVECTOR3(g_aComputer[0].pos.x,g_aComputer[0].pos.y,0.0f) ,D3DXVECTOR3(10.0f,0.0f,0.0f),5);

		}
	g_aComputer[0].bUpMove =false;
	}
	else if(g_aComputer[0].pos.y >= 450.0f)
	{
		if( bUseComputer == true)
		{

	SetBulletEnemy(D3DXVECTOR3(g_aComputer[0].pos.x,g_aComputer[0].pos.y,0.0f) ,D3DXVECTOR3(10.0f,0.0f,0.0f),5);
		}
	g_aComputer[0].bUpMove = true;

	}

	if(g_aComputer[0].bUpMove == true)
	{
		g_aComputer[0].pos.y -= move_Computer;
	}
	else if(g_aComputer[0].bUpMove == false)
	{
		g_aComputer[0].pos.y += move_Computer;

	}
}
void SetComputer(D3DXVECTOR3 pos)
{
	for(int i = 0; i< MAX_COMPUTER; i++)
	{
		g_aComputer[i].pos.x = pos.x;
		g_aComputer[i].pos.y = pos.y;
		
	}
}