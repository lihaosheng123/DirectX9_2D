#include "main.h"
#include "enemy2.h"
#include "input.h"
#include "bulletEnemy.h"
#include "explosion.h"
//グローバル変数
ENEMY2 g_aEnemy2[MAX_ENEMY2];
LPDIRECT3DTEXTURE9 g_pTextureEnemy2 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy2 =NULL;	//頂点パッファへのポインタ
D3DXVECTOR3 g_posEnemy2;	//ポリゴンの位置
D3DXVECTOR3 g_rotEnemy2;		//ポリゴンの回転角
D3DXVECTOR3 g_moveEnemy2;		//ポリゴンの移動量
int g_nCounterAnim_Enemy2;		//アンメーションカウンタ
int g_nPatternAnim_Enemy2;		//アンメーションパターンNO
float animRow_Enemy2 =1.0f;
float maxAnimX_Enemy2 = 7.0f;
float maxAnimY_Enemy2 = 1.0f;
float g_fLengthEnemy2;		//ポリゴンの対角線の長さ
float g_fAngleEnemy2;		//ポリゴンの対角線の角度
float move_Enemy2 = 3.0f;		//移動量

float runSpeed_Enemy2 = 3.0f;
int animMaxnum_Enemy2 = 4;
float startAnimY_Enemy2 = 0.0f;
//=============================================================================
//  関数名　：InitEnemy2
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitEnemy2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffEnemy2,NULL)))
	{
		return E_FAIL;
	}
		VERTEX_2D *pVtx;
		g_pVtxBuffEnemy2 ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得
		//テクスチャの読み込み	
		D3DXCreateTextureFromFile(
			pDevice,
			".\\data\\TEXTURE\\cat.png",
		&g_pTextureEnemy2);
		 bUseEnemy2 = true;
		for(int i= 0;i<MAX_ENEMY2;i++)
		{
		g_aEnemy2[i].nLifeenemy2 = 5;
		g_aEnemy2[i].fHeight=25.0f;
		g_aEnemy2[i].fWidth=170.0f;
			//初期化処理

		g_aEnemy2[i].pos.x = 900.0f;
		g_aEnemy2[i].pos.y = 220.0f;
		g_posEnemy2 = D3DXVECTOR3(g_aEnemy2[i].pos.x,g_aEnemy2[i].pos.y,0.0f);
		}
			//回転初期化処理
		g_rotEnemy2 = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_fLengthEnemy2 =sqrtf(g_aEnemy2[0].fWidth * g_aEnemy2[0].fWidth + g_aEnemy2[0].fHeight * g_aEnemy2[0].fHeight)*0.5f;
		g_fAngleEnemy2 =atan2f(g_aEnemy2[0].fWidth,g_aEnemy2[0].fHeight)*0.5f;

		g_aEnemy2[0].bUse = true;
		g_aEnemy2[0].bUpMove = true;
		//頂点座標設定
		pVtx[0].pos = D3DXVECTOR3 (g_aEnemy2[0].pos.x - sinf( g_fAngleEnemy2 + g_rotEnemy2.z ) * g_fLengthEnemy2,
								   g_aEnemy2[0].pos.y - cosf( g_fAngleEnemy2 + g_rotEnemy2.z ) * g_fLengthEnemy2,
								   0.0f);

		pVtx[1].pos = D3DXVECTOR3 (g_aEnemy2[0].pos.x + sinf( g_fAngleEnemy2 - g_rotEnemy2.z ) * g_fLengthEnemy2,
								   g_aEnemy2[0].pos.y - cosf( g_fAngleEnemy2 - g_rotEnemy2.z ) * g_fLengthEnemy2,
								   0.0f);

		pVtx[2].pos = D3DXVECTOR3 (g_aEnemy2[0].pos.x - sinf( g_fAngleEnemy2 - g_rotEnemy2.z ) * g_fLengthEnemy2,
								   g_aEnemy2[0].pos.y + cosf( g_fAngleEnemy2 - g_rotEnemy2.z ) * g_fLengthEnemy2,
								   0.0f);

		pVtx[3].pos = D3DXVECTOR3 (g_aEnemy2[0].pos.x + sinf( g_fAngleEnemy2 + g_rotEnemy2.z ) * g_fLengthEnemy2,
								   g_aEnemy2[0].pos.y + cosf( g_fAngleEnemy2 + g_rotEnemy2.z ) * g_fLengthEnemy2,
								   0.0f);

			pVtx[0].tex = D3DXVECTOR2(1.0f / maxAnimX_Enemy2, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(2.0f / maxAnimX_Enemy2,0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f / maxAnimX_Enemy2, 1.0f / maxAnimY_Enemy2);
			pVtx[3].tex = D3DXVECTOR2(2.0f / maxAnimX_Enemy2, 1.0f / maxAnimY_Enemy2);

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

		g_pVtxBuffEnemy2 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：UninitEnemy2
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitEnemy2(void)
{

	if(g_pVtxBuffEnemy2!=NULL)
	{
		g_pVtxBuffEnemy2->Release();		//頂点バッファの開放
		g_pVtxBuffEnemy2=NULL;
	}
	if(g_pTextureEnemy2!=NULL)
	{
		g_pTextureEnemy2->Release();
		g_pTextureEnemy2=NULL;
	}
}
//=============================================================================
//  関数名　：DrawEnemy2
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawEnemy2(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureEnemy2);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffEnemy2,
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
//  関数名　：UpdateEnemy2
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateEnemy2(void)
{
	if( bUseEnemy2 == true)
	{
	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy2 ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得

		Enemy2Move();


		if((g_aEnemy2[0].pos.x-g_aEnemy2[0].fWidth/5) <= 0)
		{
			g_aEnemy2[0].pos.x = (g_aEnemy2[0].fWidth/5);
		}
	
		if((g_aEnemy2[0].pos.x+g_aEnemy2[0].fWidth/3)>= SCREEN_WIDTH)
		{
			g_aEnemy2[0].pos.x = SCREEN_WIDTH+-(g_aEnemy2[0].fWidth/3);
		}

		if((g_aEnemy2[0].pos.y-g_aEnemy2[0].fHeight/5) <= 0)
		{
			g_aEnemy2[0].pos.y=(g_aEnemy2[0].fHeight/5);
		}

		if((g_aEnemy2[0].pos.y+g_aEnemy2[0].fHeight/5) >= SCREEN_HEIGHT)
		{
			g_aEnemy2[0].pos.y = SCREEN_HEIGHT+-(g_aEnemy2[0].fHeight/5);
		}

			pVtx[0].pos = D3DXVECTOR3 (g_aEnemy2[0].pos.x - sinf( g_fAngleEnemy2 + g_rotEnemy2.z ) * g_fLengthEnemy2,
									   g_aEnemy2[0].pos.y - cosf( g_fAngleEnemy2 + g_rotEnemy2.z ) * g_fLengthEnemy2,
									   0.0f);

			pVtx[1].pos = D3DXVECTOR3 (g_aEnemy2[0].pos.x + sinf( g_fAngleEnemy2 - g_rotEnemy2.z ) * g_fLengthEnemy2,
									   g_aEnemy2[0].pos.y - cosf( g_fAngleEnemy2 - g_rotEnemy2.z ) * g_fLengthEnemy2,
									   0.0f);
	
			pVtx[2].pos = D3DXVECTOR3 (g_aEnemy2[0].pos.x - sinf( g_fAngleEnemy2 - g_rotEnemy2.z ) * g_fLengthEnemy2,
									   g_aEnemy2[0].pos.y + cosf( g_fAngleEnemy2 - g_rotEnemy2.z ) * g_fLengthEnemy2,
									   0.0f);

			pVtx[3].pos = D3DXVECTOR3 (g_aEnemy2[0].pos.x + sinf( g_fAngleEnemy2 + g_rotEnemy2.z ) * g_fLengthEnemy2,
									   g_aEnemy2[0].pos.y + cosf( g_fAngleEnemy2 + g_rotEnemy2.z ) * g_fLengthEnemy2,
									   0.0f);

		g_pVtxBuffEnemy2 ->Unlock();	//LOCK

	}
		if(  bUseEnemy2  ==false)
		{
			VERTEX_2D *pVtx;
			g_pVtxBuffEnemy2 ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得
			bUseExplosionenemy = false;
			pVtx[0].tex = D3DXVECTOR2(6.0f / maxAnimX_Enemy2, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(7.0f / maxAnimX_Enemy2,0.0f);
			pVtx[2].tex = D3DXVECTOR2(6.0f / maxAnimX_Enemy2, 1.0f / maxAnimY_Enemy2);
			pVtx[3].tex = D3DXVECTOR2(7.0f / maxAnimX_Enemy2, 1.0f / maxAnimY_Enemy2);

			pVtx[0].pos = D3DXVECTOR3 (g_aEnemy2[0].pos.x - sinf( g_fAngleEnemy2 + g_rotEnemy2.z ) * g_fLengthEnemy2,
									   g_aEnemy2[0].pos.y - cosf( g_fAngleEnemy2 + g_rotEnemy2.z ) * g_fLengthEnemy2,
									   0.0f);

			pVtx[1].pos = D3DXVECTOR3 (g_aEnemy2[0].pos.x + sinf( g_fAngleEnemy2 - g_rotEnemy2.z ) * g_fLengthEnemy2,
									   g_aEnemy2[0].pos.y - cosf( g_fAngleEnemy2 - g_rotEnemy2.z ) * g_fLengthEnemy2,
									   0.0f);
	
			pVtx[2].pos = D3DXVECTOR3 (g_aEnemy2[0].pos.x - sinf( g_fAngleEnemy2 - g_rotEnemy2.z ) * g_fLengthEnemy2,
									   g_aEnemy2[0].pos.y + cosf( g_fAngleEnemy2 - g_rotEnemy2.z ) * g_fLengthEnemy2,
									   0.0f);

			pVtx[3].pos = D3DXVECTOR3 (g_aEnemy2[0].pos.x + sinf( g_fAngleEnemy2 + g_rotEnemy2.z ) * g_fLengthEnemy2,
									   g_aEnemy2[0].pos.y + cosf( g_fAngleEnemy2 + g_rotEnemy2.z ) * g_fLengthEnemy2,
									   0.0f);
				g_pVtxBuffEnemy2 ->Unlock();	//LOCK
				
		}


}

ENEMY2 *GetEnemy2(void)
{
	return &g_aEnemy2[0];
}
void Enemy2Move(void)
{
	if( g_aEnemy2[0].pos.y <= 210.0f)
	{
		g_aEnemy2[0].bUpMove =false;
		bUseExplosion=false;
		bUseExplosionenemy = false;
	}
	else if(g_aEnemy2[0].pos.y >= 450.0f)
	{
		g_aEnemy2[0].bUpMove = true;

	}

	if(g_aEnemy2[0].bUpMove == true)
	{
		g_aEnemy2[0].pos.y -= move_Enemy2;
	}
	else if(g_aEnemy2[0].bUpMove ==	false)
	{
		g_aEnemy2[0].pos.y += move_Enemy2;

	}
}
void SetEnemy2(D3DXVECTOR3 pos)
{
	for(int i = 0; i< MAX_ENEMY2; i++)
	{
		g_aEnemy2[i].pos.x = pos.x;
		g_aEnemy2[i].pos.y = pos.y;
		
	}
}