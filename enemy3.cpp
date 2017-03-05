#include "main.h"
#include "enemy3.h"
#include "input.h"
#include "explosionenemy.h"
#include "explosion.h"
#include "bulletenemy.h"
//グローバル変数
ENEMY3 g_aEnemy3[MAX_ENEMY3];
LPDIRECT3DTEXTURE9 g_pTextureEnemy3 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy3 =NULL;	//頂点パッファへのポインタ
D3DXVECTOR3 g_posEnemy3;	//ポリゴンの位置
D3DXVECTOR3 g_rotEnemy3;		//ポリゴンの回転角
D3DXVECTOR3 g_moveEnemy3;		//ポリゴンの移動量
int g_nCounterAnim_Enemy3;		//アンメーションカウンタ
int g_nPatternAnim_Enemy3;		//アンメーションパターンNO
float animRow_Enemy3 =1.0f;
float maxAnimX_Enemy3 = 1.0f;
float maxAnimY_Enemy3 = 1.0f;
float g_fLengthEnemy3;		//ポリゴンの対角線の長さ
float g_fAngleEnemy3;		//ポリゴンの対角線の角度
float move_Enemy3 = 3.0f;		//移動量
float runSpeed_Enemy3 = 3.0f;
int animMaxnum_Enemy3 = 4;
float startAnimY_Enemy3 = 0.0f;
//=============================================================================
//  関数名　：InitEnemy3
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitEnemy3(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffEnemy3,NULL)))
	{
		return E_FAIL;
	}
		VERTEX_2D *pVtx;
		g_pVtxBuffEnemy3 ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得
		//テクスチャの読み込み	
		D3DXCreateTextureFromFile(
			pDevice,
			".\\data\\TEXTURE\\catboss.png",
		&g_pTextureEnemy3);
		bUseEnemy3 = true;
		for(int i= 0;i<MAX_ENEMY3;i++)
		{
		g_aEnemy3[i]. nLifeenemy3 = 5;
		g_aEnemy3[i].fHeight=70.0f;
		g_aEnemy3[i].fWidth=240.0f;
			//初期化処理

		g_aEnemy3[i].pos.x = 1100.0f;
		g_aEnemy3[i].pos.y = 130.0f;
		g_posEnemy3 = D3DXVECTOR3(g_aEnemy3[i].pos.x,g_aEnemy3[i].pos.y,0.0f);
		}
			//回転初期化処理
		g_rotEnemy3 = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_fLengthEnemy3 =sqrtf(g_aEnemy3[0].fWidth * g_aEnemy3[0].fWidth + g_aEnemy3[0].fHeight * g_aEnemy3[0].fHeight)*0.5f;
		g_fAngleEnemy3 =atan2f(g_aEnemy3[0].fWidth,g_aEnemy3[0].fHeight)*0.5f;

		g_aEnemy3[0].bUse = true;
		g_aEnemy3[0].bUpMove = true;
		//頂点座標設定
		pVtx[0].pos = D3DXVECTOR3 (g_aEnemy3[0].pos.x - sinf( g_fAngleEnemy3 + g_rotEnemy3.z ) * g_fLengthEnemy3,
								   g_aEnemy3[0].pos.y - cosf( g_fAngleEnemy3 + g_rotEnemy3.z ) * g_fLengthEnemy3,
								   0.0f);

		pVtx[1].pos = D3DXVECTOR3 (g_aEnemy3[0].pos.x + sinf( g_fAngleEnemy3 - g_rotEnemy3.z ) * g_fLengthEnemy3,
								   g_aEnemy3[0].pos.y - cosf( g_fAngleEnemy3 - g_rotEnemy3.z ) * g_fLengthEnemy3,
								   0.0f);

		pVtx[2].pos = D3DXVECTOR3 (g_aEnemy3[0].pos.x - sinf( g_fAngleEnemy3 - g_rotEnemy3.z ) * g_fLengthEnemy3,
								   g_aEnemy3[0].pos.y + cosf( g_fAngleEnemy3 - g_rotEnemy3.z ) * g_fLengthEnemy3,
								   0.0f);

		pVtx[3].pos = D3DXVECTOR3 (g_aEnemy3[0].pos.x + sinf( g_fAngleEnemy3 + g_rotEnemy3.z ) * g_fLengthEnemy3,
								   g_aEnemy3[0].pos.y + cosf( g_fAngleEnemy3 + g_rotEnemy3.z ) * g_fLengthEnemy3,
								   0.0f);

			pVtx[0].tex = D3DXVECTOR2(0.0f / maxAnimX_Enemy3, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(1.0f / maxAnimX_Enemy3,0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f / maxAnimX_Enemy3, 1.0f / maxAnimY_Enemy3);
			pVtx[3].tex = D3DXVECTOR2(1.0f / maxAnimX_Enemy3, 1.0f / maxAnimY_Enemy3);

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

		g_pVtxBuffEnemy3 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：UninitEnemy3
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitEnemy3(void)
{

	if(g_pVtxBuffEnemy3!=NULL)
	{
		g_pVtxBuffEnemy3->Release();		//頂点バッファの開放
		g_pVtxBuffEnemy3=NULL;
	}
	if(g_pTextureEnemy3!=NULL)
	{
		g_pTextureEnemy3->Release();
		g_pTextureEnemy3=NULL;
	}
}
//=============================================================================
//  関数名　：DrawEnemy3
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawEnemy3(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureEnemy3);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffEnemy3,
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
//  関数名　：UpdateEnemy3
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateEnemy3(void)
{
	if( bUseEnemy3 == true)
	{
	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy3 ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得

		Enemy3Move();


		if((g_aEnemy3[0].pos.x-g_aEnemy3[0].fWidth/5) <= 0)
		{
			g_aEnemy3[0].pos.x = (g_aEnemy3[0].fWidth/5);
		}
	
		if((g_aEnemy3[0].pos.x+g_aEnemy3[0].fWidth/3)>= SCREEN_WIDTH)
		{
			g_aEnemy3[0].pos.x = SCREEN_WIDTH+-(g_aEnemy3[0].fWidth/3);
		}

		if((g_aEnemy3[0].pos.y-g_aEnemy3[0].fHeight/5) <= 0)
		{
			g_aEnemy3[0].pos.y=(g_aEnemy3[0].fHeight/5);
		}

		if((g_aEnemy3[0].pos.y+g_aEnemy3[0].fHeight/5) >= SCREEN_HEIGHT)
		{
			g_aEnemy3[0].pos.y = SCREEN_HEIGHT+-(g_aEnemy3[0].fHeight/5);
		}

			pVtx[0].pos = D3DXVECTOR3 (g_aEnemy3[0].pos.x - sinf( g_fAngleEnemy3 + g_rotEnemy3.z ) * g_fLengthEnemy3,
									   g_aEnemy3[0].pos.y - cosf( g_fAngleEnemy3 + g_rotEnemy3.z ) * g_fLengthEnemy3,
									   0.0f);

			pVtx[1].pos = D3DXVECTOR3 (g_aEnemy3[0].pos.x + sinf( g_fAngleEnemy3 - g_rotEnemy3.z ) * g_fLengthEnemy3,
									   g_aEnemy3[0].pos.y - cosf( g_fAngleEnemy3 - g_rotEnemy3.z ) * g_fLengthEnemy3,
									   0.0f);
	
			pVtx[2].pos = D3DXVECTOR3 (g_aEnemy3[0].pos.x - sinf( g_fAngleEnemy3 - g_rotEnemy3.z ) * g_fLengthEnemy3,
									   g_aEnemy3[0].pos.y + cosf( g_fAngleEnemy3 - g_rotEnemy3.z ) * g_fLengthEnemy3,
									   0.0f);

			pVtx[3].pos = D3DXVECTOR3 (g_aEnemy3[0].pos.x + sinf( g_fAngleEnemy3 + g_rotEnemy3.z ) * g_fLengthEnemy3,
									   g_aEnemy3[0].pos.y + cosf( g_fAngleEnemy3 + g_rotEnemy3.z ) * g_fLengthEnemy3,
									   0.0f);

		g_pVtxBuffEnemy3 ->Unlock();	//LOCK

	}
		if(  bUseEnemy3  ==false)
		{
			VERTEX_2D *pVtx;
			g_pVtxBuffEnemy3 ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得
			bUseExplosionenemy = false;
			pVtx[0].tex = D3DXVECTOR2(6.0f / maxAnimX_Enemy3, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(7.0f / maxAnimX_Enemy3,0.0f);
			pVtx[2].tex = D3DXVECTOR2(6.0f / maxAnimX_Enemy3, 1.0f / maxAnimY_Enemy3);
			pVtx[3].tex = D3DXVECTOR2(7.0f / maxAnimX_Enemy3, 1.0f / maxAnimY_Enemy3);

			pVtx[0].pos = D3DXVECTOR3 (g_aEnemy3[0].pos.x - sinf( g_fAngleEnemy3 + g_rotEnemy3.z ) * g_fLengthEnemy3,
									   g_aEnemy3[0].pos.y - cosf( g_fAngleEnemy3 + g_rotEnemy3.z ) * g_fLengthEnemy3,
									   0.0f);

			pVtx[1].pos = D3DXVECTOR3 (g_aEnemy3[0].pos.x + sinf( g_fAngleEnemy3 - g_rotEnemy3.z ) * g_fLengthEnemy3,
									   g_aEnemy3[0].pos.y - cosf( g_fAngleEnemy3 - g_rotEnemy3.z ) * g_fLengthEnemy3,
									   0.0f);
	
			pVtx[2].pos = D3DXVECTOR3 (g_aEnemy3[0].pos.x - sinf( g_fAngleEnemy3 - g_rotEnemy3.z ) * g_fLengthEnemy3,
									   g_aEnemy3[0].pos.y + cosf( g_fAngleEnemy3 - g_rotEnemy3.z ) * g_fLengthEnemy3,
									   0.0f);

			pVtx[3].pos = D3DXVECTOR3 (g_aEnemy3[0].pos.x + sinf( g_fAngleEnemy3 + g_rotEnemy3.z ) * g_fLengthEnemy3,
									   g_aEnemy3[0].pos.y + cosf( g_fAngleEnemy3 + g_rotEnemy3.z ) * g_fLengthEnemy3,
									   0.0f);
				g_pVtxBuffEnemy3 ->Unlock();	//LOCK
				
		}


}

ENEMY3 *GetEnemy3(void)
{
	return &g_aEnemy3[0];
}
void Enemy3Move(void)
{

	if( g_aEnemy3[0].pos.y <= 130.0f)
	{
		g_aEnemy3[0].bUpMove =false;
			SetBulletEnemy(D3DXVECTOR3(g_aEnemy3[0].pos.x,g_aEnemy3[0].pos.y,0.0f) ,D3DXVECTOR3(5.0f,-5.0f,0.0f),5);
			SetBulletEnemy(D3DXVECTOR3(g_aEnemy3[0].pos.x,g_aEnemy3[0].pos.y,0.0f) ,D3DXVECTOR3(8.0f,-8.0f,0.0f),5);
			SetBulletEnemy(D3DXVECTOR3(g_aEnemy3[0].pos.x,g_aEnemy3[0].pos.y,0.0f) ,D3DXVECTOR3(7.0f,-7.0f,0.0f),5);
			SetBulletEnemy(D3DXVECTOR3(g_aEnemy3[0].pos.x,g_aEnemy3[0].pos.y,0.0f) ,D3DXVECTOR3(6.0f,-6.0f,0.0f),5);
			SetBulletEnemy(D3DXVECTOR3(g_aEnemy3[0].pos.x,g_aEnemy3[0].pos.y,0.0f) ,D3DXVECTOR3(5.0f,-5.0f,0.0f),5);
			SetBulletEnemy(D3DXVECTOR3(g_aEnemy3[0].pos.x,g_aEnemy3[0].pos.y,0.0f) ,D3DXVECTOR3(4.0f,-4.0f,0.0f),5);
	}
	else if(g_aEnemy3[0].pos.y >= 720.0f)
	{
			SetBulletEnemy(D3DXVECTOR3(g_aEnemy3[0].pos.x,g_aEnemy3[0].pos.y,0.0f) ,D3DXVECTOR3(5.0f,-5.0f,0.0f),5);
			SetBulletEnemy(D3DXVECTOR3(g_aEnemy3[0].pos.x,g_aEnemy3[0].pos.y,0.0f) ,D3DXVECTOR3(8.0f,-8.0f,0.0f),5);
			SetBulletEnemy(D3DXVECTOR3(g_aEnemy3[0].pos.x,g_aEnemy3[0].pos.y,0.0f) ,D3DXVECTOR3(7.0f,-7.0f,0.0f),5);
			SetBulletEnemy(D3DXVECTOR3(g_aEnemy3[0].pos.x,g_aEnemy3[0].pos.y,0.0f) ,D3DXVECTOR3(6.0f,-6.0f,0.0f),5);
			SetBulletEnemy(D3DXVECTOR3(g_aEnemy3[0].pos.x,g_aEnemy3[0].pos.y,0.0f) ,D3DXVECTOR3(5.0f,-5.0f,0.0f),5);
			SetBulletEnemy(D3DXVECTOR3(g_aEnemy3[0].pos.x,g_aEnemy3[0].pos.y,0.0f) ,D3DXVECTOR3(4.0f,-4.0f,0.0f),5);
		g_aEnemy3[0].bUpMove = true;

	}

	if(g_aEnemy3[0].bUpMove == true)
	{
		g_aEnemy3[0].pos.y --;
	}
	else if(g_aEnemy3[0].bUpMove ==	false)
	{
		g_aEnemy3[0].pos.y ++;

	}
}

void SetEnemy3(D3DXVECTOR3 pos)
{
	for(int i = 0; i< MAX_ENEMY3; i++)
	{
		g_aEnemy3[i].pos.x = pos.x;
		g_aEnemy3[i].pos.y = pos.y;
		
	}
}