#include "main.h"
#include "enemy.h"
#include "input.h"
#include "bulletenemy.h"
#include "explosion.h"
#include "pause.h"
//グローバル変数
ENEMY g_aEnemy[MAX_ENEMY];
LPDIRECT3DTEXTURE9 g_pTextureEnemy =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy =NULL;	//頂点パッファへのポインタ
D3DXVECTOR3 g_posEnemy;	//ポリゴンの位置
D3DXVECTOR3 g_rotEnemy;		//ポリゴンの回転角
D3DXVECTOR3 g_moveEnemy;		//ポリゴンの移動量
int g_nCounterAnim_Enemy;		//アンメーションカウンタ
int g_nPatternAnim_Enemy;		//アンメーションパターンNO
float animRow_Enemy =1.0f;
float maxAnimX_Enemy = 7.0f;
float maxAnimY_Enemy = 1.0f;
float g_fLengthEnemy;		//ポリゴンの対角線の長さ
float g_fAngleEnemy;		//ポリゴンの対角線の角度
float move_Enemy = 3.0f;		//移動量
float spinmove_cat =0.1f;		//回転量
float runSpeed_Enemy = 3.0f;
int animMaxnum_Enemy = 4;
float startAnimY_Enemy = 0.0f;
ENEMYSTATE g_enemystate = ENEMYSTATE_NORMAL;
ENEMYMOVE g_enemymove = ENEMYMOVE_1;
CATTYPE g_type = CAT_1;
bool bUseExplosion ;
 bool bUseExplosionenemy ;
//=============================================================================
//  関数名　：InitEnemy
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffEnemy,NULL)))
	{
		return E_FAIL;
	}
		VERTEX_2D *pVtx;
		g_pVtxBuffEnemy ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得
		//テクスチャの読み込み	
		D3DXCreateTextureFromFile(
			pDevice,
			".\\data\\TEXTURE\\cat.png",
		&g_pTextureEnemy);
		 bUseEnemy = true;
		for(int i= 0;i<MAX_ENEMY;i++)
		{
		g_aEnemy[i].nLifeenemy = 5;
		g_aEnemy[i].fHeight=25.0f;
		g_aEnemy[i].fWidth=170.0f;
			//初期化処理
		g_aEnemy[i].pos.x = 1000.0f;
		g_aEnemy[i].pos.y = 220.0f;
		g_posEnemy = D3DXVECTOR3(g_aEnemy[i].pos.x,g_aEnemy[i].pos.y,0.0f);
		}
			//回転初期化処理
		g_rotEnemy = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_fLengthEnemy =sqrtf(g_aEnemy[0].fWidth * g_aEnemy[0].fWidth + g_aEnemy[0].fHeight * g_aEnemy[0].fHeight)*0.5f;
		g_fAngleEnemy =atan2f(g_aEnemy[0].fWidth,g_aEnemy[0].fHeight)*0.5f;

		g_aEnemy[0].bUse = true;
		g_aEnemy[0].bUpMove = true;
		//頂点座標設定
		pVtx[0].pos = D3DXVECTOR3 (g_aEnemy[0].pos.x - sinf( g_fAngleEnemy + g_rotEnemy.z ) * g_fLengthEnemy,
								   g_aEnemy[0].pos.y - cosf( g_fAngleEnemy + g_rotEnemy.z ) * g_fLengthEnemy,
								   0.0f);

		pVtx[1].pos = D3DXVECTOR3 (g_aEnemy[0].pos.x + sinf( g_fAngleEnemy - g_rotEnemy.z ) * g_fLengthEnemy,
								   g_aEnemy[0].pos.y - cosf( g_fAngleEnemy - g_rotEnemy.z ) * g_fLengthEnemy,
								   0.0f);

		pVtx[2].pos = D3DXVECTOR3 (g_aEnemy[0].pos.x - sinf( g_fAngleEnemy - g_rotEnemy.z ) * g_fLengthEnemy,
								   g_aEnemy[0].pos.y + cosf( g_fAngleEnemy - g_rotEnemy.z ) * g_fLengthEnemy,
								   0.0f);

		pVtx[3].pos = D3DXVECTOR3 (g_aEnemy[0].pos.x + sinf( g_fAngleEnemy + g_rotEnemy.z ) * g_fLengthEnemy,
								   g_aEnemy[0].pos.y + cosf( g_fAngleEnemy + g_rotEnemy.z ) * g_fLengthEnemy,
								   0.0f);
		//UV設定
		switch(g_type)
		{
		case CAT_1:
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(1.0f / maxAnimX_Enemy,0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f / maxAnimY_Enemy);
			pVtx[3].tex = D3DXVECTOR2(1.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);
			break;

		case CAT_2:
			pVtx[0].tex = D3DXVECTOR2(1.0f / maxAnimX_Enemy, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(2.0f / maxAnimX_Enemy,0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);
			pVtx[3].tex = D3DXVECTOR2(2.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);
			break;

		case CAT_3:
			pVtx[0].tex = D3DXVECTOR2(2.0f / maxAnimX_Enemy, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(3.0f / maxAnimX_Enemy,0.0f);
			pVtx[2].tex = D3DXVECTOR2(2.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);
			pVtx[3].tex = D3DXVECTOR2(3.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);
			break;

		case CAT_4:
			pVtx[0].tex = D3DXVECTOR2(3.0f / maxAnimX_Enemy, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(4.0f / maxAnimX_Enemy,0.0f);
			pVtx[2].tex = D3DXVECTOR2(3.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);
			pVtx[3].tex = D3DXVECTOR2(4.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);
			break;

		case CAT_5:
			pVtx[0].tex = D3DXVECTOR2(4.0f / maxAnimX_Enemy, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(5.0f / maxAnimX_Enemy,0.0f);
			pVtx[2].tex = D3DXVECTOR2(4.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);
			pVtx[3].tex = D3DXVECTOR2(5.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);
			break;

		case CAT_6:
			pVtx[0].tex = D3DXVECTOR2(5.0f / maxAnimX_Enemy, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(6.0f / maxAnimX_Enemy,0.0f);
			pVtx[2].tex = D3DXVECTOR2(5.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);
			pVtx[3].tex = D3DXVECTOR2(6.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);
			break;

		case CAT_7:
			pVtx[0].tex = D3DXVECTOR2(6.0f / maxAnimX_Enemy, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(7.0f / maxAnimX_Enemy,0.0f);
			pVtx[2].tex = D3DXVECTOR2(6.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);
			pVtx[3].tex = D3DXVECTOR2(7.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);
			break;
		}
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

		g_pVtxBuffEnemy ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：UninitEnemy
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitEnemy(void)
{

	if(g_pVtxBuffEnemy!=NULL)
	{
		g_pVtxBuffEnemy->Release();		//頂点バッファの開放
		g_pVtxBuffEnemy=NULL;
	}
	if(g_pTextureEnemy!=NULL)
	{
		g_pTextureEnemy->Release();
		g_pTextureEnemy=NULL;
	}
}
//=============================================================================
//  関数名　：DrawEnemy
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawEnemy(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureEnemy);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffEnemy,
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
//  関数名　：UpdateEnemy
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateEnemy(void)
{
	PAUSEUSE *bUseCheck = GetPause();
	if(bUseCheck->bUse == false)
	{
	if(  bUseEnemy  ==true)
	{
	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得
	switch(g_enemystate)
		{
		case ENEMYSTATE_NORMAL:
			EnemyMove();
			break;
		}
		if((g_aEnemy[0].pos.x-g_aEnemy[0].fWidth/5) <= 0)
		{
			g_aEnemy[0].pos.x = (g_aEnemy[0].fWidth/5);
		}
	
		if((g_aEnemy[0].pos.x+g_aEnemy[0].fWidth/3)>= SCREEN_WIDTH)
		{
			g_aEnemy[0].pos.x = SCREEN_WIDTH+-(g_aEnemy[0].fWidth/3);
		}

		if((g_aEnemy[0].pos.y-g_aEnemy[0].fHeight/5) <= 0)
		{
			g_aEnemy[0].pos.y=(g_aEnemy[0].fHeight/5);
		}

		if((g_aEnemy[0].pos.y+g_aEnemy[0].fHeight/5) >= SCREEN_HEIGHT)
		{
			g_aEnemy[0].pos.y = SCREEN_HEIGHT+-(g_aEnemy[0].fHeight/5);
		}

			pVtx[0].pos = D3DXVECTOR3 (g_aEnemy[0].pos.x - sinf( g_fAngleEnemy + g_rotEnemy.z ) * g_fLengthEnemy,
									   g_aEnemy[0].pos.y - cosf( g_fAngleEnemy + g_rotEnemy.z ) * g_fLengthEnemy,
									   0.0f);

			pVtx[1].pos = D3DXVECTOR3 (g_aEnemy[0].pos.x + sinf( g_fAngleEnemy - g_rotEnemy.z ) * g_fLengthEnemy,
									   g_aEnemy[0].pos.y - cosf( g_fAngleEnemy - g_rotEnemy.z ) * g_fLengthEnemy,
									   0.0f);
	
			pVtx[2].pos = D3DXVECTOR3 (g_aEnemy[0].pos.x - sinf( g_fAngleEnemy - g_rotEnemy.z ) * g_fLengthEnemy,
									   g_aEnemy[0].pos.y + cosf( g_fAngleEnemy - g_rotEnemy.z ) * g_fLengthEnemy,
									   0.0f);

			pVtx[3].pos = D3DXVECTOR3 (g_aEnemy[0].pos.x + sinf( g_fAngleEnemy + g_rotEnemy.z ) * g_fLengthEnemy,
									   g_aEnemy[0].pos.y + cosf( g_fAngleEnemy + g_rotEnemy.z ) * g_fLengthEnemy,
									   0.0f);

		g_pVtxBuffEnemy ->Unlock();	//LOCK
	}
		if(  bUseEnemy  ==false)
		{
			VERTEX_2D *pVtx;
			g_pVtxBuffEnemy ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得

			pVtx[0].tex = D3DXVECTOR2(6.0f / maxAnimX_Enemy, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(7.0f / maxAnimX_Enemy,0.0f);
			pVtx[2].tex = D3DXVECTOR2(6.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);
			pVtx[3].tex = D3DXVECTOR2(7.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);

			pVtx[0].pos = D3DXVECTOR3 (g_aEnemy[0].pos.x - sinf( g_fAngleEnemy + g_rotEnemy.z ) * g_fLengthEnemy,
									   g_aEnemy[0].pos.y - cosf( g_fAngleEnemy + g_rotEnemy.z ) * g_fLengthEnemy,
									   0.0f);

			pVtx[1].pos = D3DXVECTOR3 (g_aEnemy[0].pos.x + sinf( g_fAngleEnemy - g_rotEnemy.z ) * g_fLengthEnemy,
									   g_aEnemy[0].pos.y - cosf( g_fAngleEnemy - g_rotEnemy.z ) * g_fLengthEnemy,
									   0.0f);
	
			pVtx[2].pos = D3DXVECTOR3 (g_aEnemy[0].pos.x - sinf( g_fAngleEnemy - g_rotEnemy.z ) * g_fLengthEnemy,
									   g_aEnemy[0].pos.y + cosf( g_fAngleEnemy - g_rotEnemy.z ) * g_fLengthEnemy,
									   0.0f);

			pVtx[3].pos = D3DXVECTOR3 (g_aEnemy[0].pos.x + sinf( g_fAngleEnemy + g_rotEnemy.z ) * g_fLengthEnemy,
									   g_aEnemy[0].pos.y + cosf( g_fAngleEnemy + g_rotEnemy.z ) * g_fLengthEnemy,
									   0.0f);
				g_pVtxBuffEnemy ->Unlock();	//LOCK
				 bUseExplosionenemy = false;
		}

	}
	
}

ENEMY *GetEnemy(void)
{
	return &g_aEnemy[0];
}
void EnemyMove(void)
{
	if( g_aEnemy[0].pos.y <= 210.0f)
	{
	SetBulletEnemy(D3DXVECTOR3(g_aEnemy[0].pos.x,g_aEnemy[0].pos.y,0.0f) ,D3DXVECTOR3(5.0f,-5.0f,0.0f),5);
	SetBulletEnemy(D3DXVECTOR3(g_aEnemy[0].pos.x,g_aEnemy[0].pos.y,0.0f) ,D3DXVECTOR3(5.0f,0.0f,0.0f),5);
	SetBulletEnemy(D3DXVECTOR3(g_aEnemy[0].pos.x,g_aEnemy[0].pos.y,0.0f) ,D3DXVECTOR3(5.0f,5.0f,0.0f),5);
		g_aEnemy[0].bUpMove =false;
		bUseExplosion=false;
	}
	else if(g_aEnemy[0].pos.y >= 370.0f)
	{
	SetBulletEnemy(D3DXVECTOR3(g_aEnemy[0].pos.x,g_aEnemy[0].pos.y,0.0f) ,D3DXVECTOR3(5.0f,0.0f,0.0f),5);
	SetBulletEnemy(D3DXVECTOR3(g_aEnemy[0].pos.x,g_aEnemy[0].pos.y,0.0f) ,D3DXVECTOR3(5.0f,5.0f,0.0f),5);
	SetBulletEnemy(D3DXVECTOR3(g_aEnemy[0].pos.x,g_aEnemy[0].pos.y,0.0f) ,D3DXVECTOR3(5.0f,-5.0f,0.0f),5);
		g_aEnemy[0].bUpMove = true;
		 bUseExplosionenemy = false;

	}

	if(g_aEnemy[0].bUpMove == true)
	{
		g_aEnemy[0].pos.y -= move_Enemy;
	}
	else if(g_aEnemy[0].bUpMove ==	false)
	{
		g_aEnemy[0].pos.y += move_Enemy;

	}
}
void SetEnemy(D3DXVECTOR3 pos)
{
	for(int i = 0; i< MAX_ENEMY; i++)
	{
		g_aEnemy[i].pos.x = pos.x;
		g_aEnemy[i].pos.y = pos.y;
		
	}
}