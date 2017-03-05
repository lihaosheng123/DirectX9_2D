#include "main.h"
#include "polygon.h"
#include "input.h"
#include "bullet.h"
#include "door.h"
#include "fade.h"
#include "talk.h"
#include "avatar.h"
#include "score.h"
#include "explosion.h"
#include "prop.h"
#include "prop2.h"
#include "talk1.h"
#include "talk2.h"
#include "bg2.h"
#include "talk3.h"
#include "talk4.h"
#include "effect.h"
#include "pause.h"
//グローバル変数
POLYGON g_aPolygon;
VERTEX_2D g_aVertex[4];
LPDIRECT3DTEXTURE9 g_pTexturePolygon =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon =NULL;	//頂点パッファへのポインタ
D3DXVECTOR3 g_posPolygon;	//ポリゴンの位置
D3DXVECTOR3 g_rotPolygon;		//ポリゴンの回転角
D3DXVECTOR3 g_movePolygon;		//ポリゴンの移動量
int g_nCounterAnim_Polygon;		//アンメーションカウンタ
int g_nPatternAnim_Polygon;		//アンメーションパターンNO
float animRow_Polygon =1.0f;
float maxAnimX_Polygon = 4.0f;
float maxAnimY_Polygon = 1.0f;
float g_fLengthPolygon;		//ポリゴンの対角線の長さ
float g_fAnglePolygon;		//ポリゴンの対角線の角度
float move_Polygon = 7.0f;		//移動量
float spinmove =0.1f;		//回転量
float runSpeed_Polygon = 3.0f;
int animMaxnum_Polygon = 4;
float startAnimY_Polygon = 0.0f;
int cnt_polygon ;
bool bProp;
bool bProp2 ;
bool bUseEnemy2;
bool bUseTalk ;
bool bUseAvatar ;
bool bKey;
bool bPropUpdate;
bool bPropUpdate2;
bool bUsebg3;
bool bUseTalk1 ;
bool bUseTalk2 ;
bool bUseTalk3 ;
bool bUseTalk4 ;
bool bUseTalk5 ;
bool bUseTalk6 ;
bool bUseTalk7 ;
bool bUseTalk8;
bool bUseTalk9;
bool jieshaobUse;
MODE g_map = MODE_GAME1;

//=============================================================================
//  関数名　：InitPolygon
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffPolygon,NULL)))
	{
		return E_FAIL;
	}
		VERTEX_2D *pVtx;
		g_pVtxBuffPolygon ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得
		//テクスチャの読み込み	
		D3DXCreateTextureFromFile(
			pDevice,
			".\\data\\TEXTURE\\002.png",
		&g_pTexturePolygon);
			//初期化処理
		g_aPolygon.fWidth = 120.0f;		//ポリゴンの幅
		g_aPolygon.fHeight =120.0f;		//ポリゴンの高さ
		g_aPolygon.pos.x = 50.0f;
		g_aPolygon.pos.y = 500.0f;
		g_posPolygon = D3DXVECTOR3(g_aPolygon.pos.x,g_aPolygon.pos.y,0.0f);
		g_aPolygon.bUse= true;
		g_aPolygon.bDoorUse=true;
		g_aPolygon.nLife = 4;
			//回転初期化処理
		g_rotPolygon = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_fLengthPolygon =sqrtf(g_aPolygon.fWidth * g_aPolygon.fWidth + g_aPolygon.fHeight * g_aPolygon.fHeight)*0.5f;
		g_fAnglePolygon =atan2f(g_aPolygon.fWidth,g_aPolygon.fHeight)*0.5f;

		//頂点座標設定
		pVtx[0].pos = D3DXVECTOR3 (g_aPolygon.pos.x - sinf( g_fAnglePolygon + g_rotPolygon.z ) * g_fLengthPolygon,
								   g_aPolygon.pos.y - cosf( g_fAnglePolygon + g_rotPolygon.z ) * g_fLengthPolygon,
								   0.0f);

		pVtx[1].pos = D3DXVECTOR3 (g_aPolygon.pos.x + sinf( g_fAnglePolygon - g_rotPolygon.z ) * g_fLengthPolygon,
								   g_aPolygon.pos.y - cosf( g_fAnglePolygon - g_rotPolygon.z ) * g_fLengthPolygon,
								   0.0f);

		pVtx[2].pos = D3DXVECTOR3 (g_aPolygon.pos.x - sinf( g_fAnglePolygon - g_rotPolygon.z ) * g_fLengthPolygon,
								   g_aPolygon.pos.y + cosf( g_fAnglePolygon - g_rotPolygon.z ) * g_fLengthPolygon,
								   0.0f);

		pVtx[3].pos = D3DXVECTOR3 (g_aPolygon.pos.x + sinf( g_fAnglePolygon + g_rotPolygon.z ) * g_fLengthPolygon,
								   g_aPolygon.pos.y + cosf( g_fAnglePolygon + g_rotPolygon.z ) * g_fLengthPolygon,
								   0.0f);

		//UV設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f );
		pVtx[1].tex = D3DXVECTOR2(1.0f / maxAnimX_Polygon,0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f / maxAnimY_Polygon);
		pVtx[3].tex = D3DXVECTOR2(1.0f / maxAnimX_Polygon, 1.0f / maxAnimY_Polygon);

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
	
		g_pVtxBuffPolygon ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：UninitPolygon
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitPolygon(void)
{

	if(g_pVtxBuffPolygon!=NULL)
	{
		g_pVtxBuffPolygon->Release();		//頂点バッファの開放
		g_pVtxBuffPolygon=NULL;
	}
	if(g_pTexturePolygon!=NULL)
	{
		g_pTexturePolygon->Release();
		g_pTexturePolygon=NULL;
	}
}
//=============================================================================
//  関数名　：DrawPolygon
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTexturePolygon);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffPolygon,
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
//  関数名　：UpdatePolygon
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdatePolygon(void)
{
	PAUSEUSE *bUseCheck = GetPause();
	if(bUseCheck->bUse == false)
	{
	MapPolygon();
//	SetEffect(D3DXVECTOR3(g_aPolygon.pos.x,g_aPolygon.pos.y,0.0f), D3DXCOLOR(120.0f, 100.0f, 50.0f, 1.0f), 30.0f, 80, EFFECTTYPE_RANDOMCOLOR);
	if(GetKeyboardTrigger(DIK_J) )
	{
		/* 弾生成 */
		SetBullet(D3DXVECTOR3(g_aPolygon.pos.x,g_aPolygon.pos.y,0.0f),D3DXVECTOR3(10.0f,0.0f,0.0f),1);
	}
	if(GetKeyboardPress(DIK_W) || GetKeyboardPress(DIK_A) || GetKeyboardPress(DIK_S) || GetKeyboardPress(DIK_D))
	{
	g_nCounterAnim_Polygon++;
		if(g_nCounterAnim_Polygon == runSpeed_Polygon )
		{
			g_nCounterAnim_Polygon = 0;
			g_nPatternAnim_Polygon ++;
			if(g_nPatternAnim_Polygon == animMaxnum_Polygon)	//パターン数
			{
				startAnimY_Polygon = 0;//画面上
				animRow_Polygon = 1;
				g_nPatternAnim_Polygon = 0;
			}
			else if(g_nPatternAnim_Polygon == 5)
			{
				animRow_Polygon++;
				startAnimY_Polygon += (1.0f / maxAnimY_Polygon);
			}
			VERTEX_2D *pVtx;
			g_pVtxBuffPolygon ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得

			if(GetKeyboardPress(DIK_W) == true)		//上移動
			{
			g_aPolygon.pos.y -= move_Polygon;
			if(GetKeyboardPress(DIK_A) == true)		//上左移動
			{
				g_aPolygon.pos.x -= sinf(-D3DX_PI*(3/4) *move_Polygon);
				g_aPolygon.pos.y -= cosf(-D3DX_PI*(3/4) *move_Polygon);
			}
			else if(GetKeyboardPress(DIK_D) == true)		//上右移動
			{
				g_aPolygon.pos.x += sinf(D3DX_PI*(3/4) *move_Polygon);
				g_aPolygon.pos.y -= cosf(D3DX_PI*(3/4) *move_Polygon);
			}
		}
		else if(GetKeyboardPress(DIK_S) == true)		//下移動
		{
			g_aPolygon.pos.y += move_Polygon;
			if(GetKeyboardPress(DIK_A) == true)		//下左移動
			{
				g_aPolygon.pos.x -= sinf(-D3DX_PI*(1/4) *move_Polygon);
				g_aPolygon.pos.y += cosf(-D3DX_PI*(1/4) *move_Polygon);
			}
			else if(GetKeyboardPress(DIK_D) == true)		//下右移動
			{
				g_aPolygon.pos.x += sinf(D3DX_PI*(1/4) *move_Polygon);
				g_aPolygon.pos.y -= cosf(D3DX_PI*(1/4) *move_Polygon);
			}
		}


		if(GetKeyboardPress(DIK_A)== true)		//左移動
		{
			g_aPolygon.pos.x -= move_Polygon;
		}
		if(GetKeyboardPress(DIK_D) == true)		//右移動
		{
			g_aPolygon.pos.x += move_Polygon;
		}

	//if(GetKeyboardTrigger(DIK_UP) == true)		//拡大
	//{
	//	g_fLengthPolygon += move;
	//}


	//if(GetKeyboardTrigger(DIK_DOWN) == true)		//縮小
	//{
	//	g_fLengthPolygon -= move;
	//}

	//if(GetKeyboardPress(DIK_LEFT) == true)		//左回転
	//{
	//	g_rotPolygon.z +=spinmove ;
	//}

	//if(GetKeyboardPress(DIK_RIGHT) == true)		//右回転
	//{
	//	g_rotPolygon.z -=spinmove ;
	//}

		if((g_aPolygon.pos.x-g_aPolygon.fWidth/5) <= 0)
		{
			g_aPolygon.pos.x = (g_aPolygon.fWidth/5);
		}
	
		if((g_aPolygon.pos.x+g_aPolygon.fWidth/3)>= SCREEN_WIDTH)
		{
			g_aPolygon.pos.x = SCREEN_WIDTH+-(g_aPolygon.fWidth/3);
			if((g_aPolygon.pos.y-g_aPolygon.fHeight/2)>=260.0f && (g_aPolygon.pos.y+g_aPolygon.fHeight/2)<=(260.0f+170.0f) )/*ドア判定*/
			{

				switch(g_map)
				{

					case MODE_JIESHAO:
					if(g_aPolygon.bDoorUse==true && jieshaobUse == true)
					{
					UpdateDoor1();
					g_map = MODE_GAME1;
					SetFade(FADE_OUT,MODE_GAME1);
					}
					g_aPolygon.bDoorUse=false;
					break;

				case MODE_GAME1:
					if(g_aPolygon.bDoorUse==true && bKey == true)
					{
					
					UpdateDoor1();
					g_map = MODE_GAME2;
					SetFade(FADE_OUT,MODE_GAME2);
					}
					g_aPolygon.bDoorUse=false;
					break;

					case MODE_GAME2:
					if(g_aPolygon.bDoorUse==true&& bKey == true)
					{
					UpdateDoor1();
					g_map = MODE_GAME3;
					SetFade(FADE_OUT,MODE_GAME3);
					}
					g_aPolygon.bDoorUse=false;
					break;

					case MODE_GAME3:
					if(g_aPolygon.bDoorUse==true&& bKey == true)
					{
						UpdateDoor1();
					g_map = MODE_RESULT;
					SetFade(FADE_OUT,MODE_RESULT);
					}
					g_aPolygon.bDoorUse=false;
					break;

				}
			}
		}

		if((g_aPolygon.pos.y-g_aPolygon.fHeight/5) <= 0)
		{
			g_aPolygon.pos.y=(g_aPolygon.fHeight/5);
		}

		if((g_aPolygon.pos.y+g_aPolygon.fHeight/5) >= SCREEN_HEIGHT)
		{
			g_aPolygon.pos.y = SCREEN_HEIGHT+-(g_aPolygon.fHeight/5);
		}

			pVtx[0].pos = D3DXVECTOR3 (g_aPolygon.pos.x - sinf( g_fAnglePolygon + g_rotPolygon.z ) * g_fLengthPolygon,
									   g_aPolygon.pos.y - cosf( g_fAnglePolygon + g_rotPolygon.z ) * g_fLengthPolygon,
									   0.0f);

			pVtx[1].pos = D3DXVECTOR3 (g_aPolygon.pos.x + sinf( g_fAnglePolygon - g_rotPolygon.z ) * g_fLengthPolygon,
									   g_aPolygon.pos.y - cosf( g_fAnglePolygon - g_rotPolygon.z ) * g_fLengthPolygon,
									   0.0f);
	
			pVtx[2].pos = D3DXVECTOR3 (g_aPolygon.pos.x - sinf( g_fAnglePolygon - g_rotPolygon.z ) * g_fLengthPolygon,
									   g_aPolygon.pos.y + cosf( g_fAnglePolygon - g_rotPolygon.z ) * g_fLengthPolygon,
									   0.0f);

			pVtx[3].pos = D3DXVECTOR3 (g_aPolygon.pos.x + sinf( g_fAnglePolygon + g_rotPolygon.z ) * g_fLengthPolygon,
									   g_aPolygon.pos.y + cosf( g_fAnglePolygon + g_rotPolygon.z ) * g_fLengthPolygon,
									   0.0f);

			pVtx[0].tex.x = g_nPatternAnim_Polygon *(1.0f / maxAnimX_Polygon);
			pVtx[0].tex.y = startAnimY_Polygon;

			pVtx[1].tex.x = (g_nPatternAnim_Polygon * (1.0f /  maxAnimX_Polygon)) + (1.0f / maxAnimX_Polygon);
			pVtx[1].tex.y = startAnimY_Polygon;
				
			pVtx[2].tex.x = g_nPatternAnim_Polygon * (1.0f /  maxAnimX_Polygon);
			pVtx[2].tex.y = animRow_Polygon *(1.0f / maxAnimY_Polygon);

			pVtx[3].tex.x = (g_nPatternAnim_Polygon * (1.0f /  maxAnimX_Polygon)) + (1.0f / maxAnimX_Polygon);
			pVtx[3].tex.y = animRow_Polygon *(1.0f / maxAnimY_Polygon);

	////////////////////////////////////////////////////////
	//if(GetKeyboardPress(DIK_W) == true)		//上移動
	//{
	//	g_movePolygon.y -= move;
	//	if(GetKeyboardPress(DIK_A) == true)		//上左移動
	//	{
	//		g_movePolygon.x -= sinf(-D3DX_PI*(3/4) *move);
	//		g_movePolygon.y -= cosf(-D3DX_PI*(3/4) *move);
	//	}
	//	else if(GetKeyboardPress(DIK_D) == true)		//上右移動
	//	{
	//		g_movePolygon.x += sinf(D3DX_PI*(3/4) *move);
	//		g_movePolygon.y -= cosf(D3DX_PI*(3/4) *move);
	//	}
	//}
	//else if(GetKeyboardPress(DIK_S) == true)		//下移動
	//{
	//	g_movePolygon.y += move;
	//	if(GetKeyboardPress(DIK_A) == true)		//下左移動
	//	{
	//		g_movePolygon.x -= sinf(-D3DX_PI*(1/4) *move);
	//		g_movePolygon.y -= cosf(-D3DX_PI*(1/4) *move);
	//	}
	//	else if(GetKeyboardPress(DIK_D) == true)		//下右移動
	//	{
	//		g_movePolygon.x += sinf(D3DX_PI*(1/4) *move);
	//		g_movePolygon.y -= cosf(D3DX_PI*(1/4) *move);
	//	}
	//}


	//if(GetKeyboardPress(DIK_A)== true)		//左移動
	//{
	//	g_movePolygon.x -= move;
	//}
	//if(GetKeyboardPress(DIK_D) == true)		//右移動
	//{
	//	g_movePolygon.x += move;
	//}

	//g_aPolygon.pos.x += g_movePolygon.x;
	//g_aPolygon.pos.y += g_movePolygon.y;
	//g_movePolygon.x -= /*(g_aPolygon.pos.x -g_aPolygon.pos.x )*/2*0.2f;
	//g_movePolygon.y += /*(g_aPolygon.pos.y -g_aPolygon.pos.y )*/2*0.2f;
	///////////////////////////////////////////////////////////////

	//	g_fLengthPolygon -= move_Polygon;
	//	}

	g_pVtxBuffPolygon ->Unlock();	//LOCK
		}
	}
	}
}
void MapPolygon(void)
{

		//鍵を取らない時
		if(  bKey == false && (g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=1000.0f && (g_aPolygon.pos.x - g_aPolygon.fWidth/5)<= 1020.0f && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>= 170.0f && (g_aPolygon.pos.y+g_aPolygon.fHeight/5) <= 470.0f )
		{
			g_aPolygon.pos.x =1000.0f- g_aPolygon.fWidth/5;
		}

		if( bUsebg3 == false && bUsebg2 == true && bProp2== false &&  (g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=940.0f && (g_aPolygon.pos.x - g_aPolygon.fWidth/5)<= 1000.0f && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>= 170.0f && (g_aPolygon.pos.y+g_aPolygon.fHeight/5) <= 470.0f )
		{
			g_aPolygon.pos.x =940.0f- g_aPolygon.fWidth/5;
		}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if(GetKeyboardPress(DIK_C) )
			{
				bUseTalk= false;
				bUseAvatar = false;
				bUseTalk1 = false;
				bUseTalk2 = false;
				bUseTalk3 = false;
				bUseTalk4 = false;
				bUseTalk5 = false;
				bUseTalk6 = false;
				bUseTalk7 = false;
				bUseTalk8 = false;
				bUseTalk9 = false;
			}
		if(bUsebg3 == false)
		{
		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)<=50.f && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=570.0f)
		{
			g_aPolygon.pos.y=570.0f-(g_aPolygon.fHeight/5);
		}

		if((g_aPolygon.pos.x - g_aPolygon.fWidth/5)<=50.f && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.x=50.0f+(g_aPolygon.fWidth/5);
		}

		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)<=100.f && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.y=610.0f-(g_aPolygon.fHeight/5);
		}

		if((g_aPolygon.pos.x - g_aPolygon.fWidth/5)<=100.f && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.x=100.0f+(g_aPolygon.fWidth/5);
			if(GetKeyboardTrigger(DIK_E) )/*判定*/
			{
			bUseTalk= true;
			bUseAvatar = true;
			bUseTalk1 = true;
			bUseTalk7 = true;
			}
		}
////////////////////////////////////////////////////////////////////////////////////////////////////////

		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_ONE && (g_aPolygon.pos.x + g_aPolygon.fWidth/5)<=(50.f+WIDTH_ONE) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=570.0f)
		{
			g_aPolygon.pos.y=570.0f-(g_aPolygon.fHeight/5);
		}

		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_ONE && (g_aPolygon.pos.x - g_aPolygon.fWidth/5)<=(50.f+WIDTH_ONE) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.x=(50.0f+WIDTH_ONE)+(g_aPolygon.fWidth/5);
		}

		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_ONE &&(g_aPolygon.pos.x + g_aPolygon.fWidth/5)<=(100.f+WIDTH_ONE) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.y=610.0f-(g_aPolygon.fHeight/5);
		}

		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_ONE &&(g_aPolygon.pos.x - g_aPolygon.fWidth/5)<=(100.f+WIDTH_ONE) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.x=(100.0f+WIDTH_ONE)+(g_aPolygon.fWidth/5);
			if(GetKeyboardTrigger(DIK_E) )/*判定*/
			{
			bUseTalk= true;
			bUseAvatar = true;
			bUseTalk2 = true;
			bUseTalk8 = true;
			}
		}

//////////////////////////////////////////////////////////////////////////////////////////////////////////


		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_TWO && (g_aPolygon.pos.x + g_aPolygon.fWidth/5)<=(50.f+WIDTH_TWO) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=570.0f)
		{
			g_aPolygon.pos.y=570.0f-(g_aPolygon.fHeight/5);
		}

		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_TWO && (g_aPolygon.pos.x - g_aPolygon.fWidth/5)<=(50.f+WIDTH_TWO) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.x=(50.0f+WIDTH_TWO)+(g_aPolygon.fWidth/5);
		}

		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_TWO && (g_aPolygon.pos.x + g_aPolygon.fWidth/5)<=(100.f+WIDTH_TWO) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.y=610.0f-(g_aPolygon.fHeight/5);
		}

		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_TWO && (g_aPolygon.pos.x - g_aPolygon.fWidth/5)<=(100.f+WIDTH_TWO) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.x=(100.0f+WIDTH_TWO)+(g_aPolygon.fWidth/5);
			if(GetKeyboardTrigger(DIK_E) )/*判定*/
			{
			bUseTalk= true;
			bUseAvatar = true;
			bUseTalk3 =true;
			bUseTalk8 = true;
			}
		}
////////////////////////////////////////////////////////////////////////////////////////////////////////


		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_THREE && (g_aPolygon.pos.x + g_aPolygon.fWidth/5)<=(50.f+WIDTH_THREE) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=570.0f)
		{
			g_aPolygon.pos.y=570.0f-(g_aPolygon.fHeight/5);
		}

		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_THREE && (g_aPolygon.pos.x - g_aPolygon.fWidth/5)<=(50.f+WIDTH_THREE) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.x=(50.0f+WIDTH_THREE)+(g_aPolygon.fWidth/5);
		}

		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_THREE && (g_aPolygon.pos.x + g_aPolygon.fWidth/5)<=(100.f+WIDTH_THREE) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.y=610.0f-(g_aPolygon.fHeight/5);
		}

		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_THREE && (g_aPolygon.pos.x - g_aPolygon.fWidth/5)<=(100.f+WIDTH_THREE) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.x=(100.0f+WIDTH_THREE)+(g_aPolygon.fWidth/5);
			if(GetKeyboardTrigger(DIK_E) )/*判定*/
			{
			bUseTalk= true;
			bUseAvatar = true;
			bUseTalk4 =true;
			bUseTalk8 = true;
			}
		}
////////////////////////////////////////////////////////////////////////////////////////////////////////



		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_FOUR && (g_aPolygon.pos.x + g_aPolygon.fWidth/5)<=(50.f+WIDTH_FOUR) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=570.0f)
		{
			g_aPolygon.pos.y=570.0f-(g_aPolygon.fHeight/5);
		}

		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_FOUR && (g_aPolygon.pos.x - g_aPolygon.fWidth/5)<=(50.f+WIDTH_FOUR) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.x=(50.0f+WIDTH_FOUR)+(g_aPolygon.fWidth/5);
		}

		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_FOUR && (g_aPolygon.pos.x + g_aPolygon.fWidth/5)<=(100.f+WIDTH_FOUR) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.y=610.0f-(g_aPolygon.fHeight/5);
		}

		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_FOUR && (g_aPolygon.pos.x - g_aPolygon.fWidth/5)<=(100.f+WIDTH_FOUR) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.x=(100.0f+WIDTH_FOUR)+(g_aPolygon.fWidth/5);
			if(GetKeyboardTrigger(DIK_E) )/*判定*/
			{
			bUseTalk= true;
			bUseAvatar = true;
			bUseTalk5 =true;
			bUseTalk8 = true;
			}
		}
////////////////////////////////////////////////////////////////////////////////////////////////////////
//右上
		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=850.f && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)<=270.0f)
		{
			g_aPolygon.pos.x=850.0f-(g_aPolygon.fWidth/5);
		}

		if((g_aPolygon.pos.x - g_aPolygon.fWidth/5)>=850.f && (g_aPolygon.pos.y-g_aPolygon.fHeight/5)<=260.0f)
		{
			g_aPolygon.pos.y=260.0f+g_aPolygon.fHeight/5;
		}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//右下
		/*ポリゴン１*/
		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=ONE_POLYGON_ONE_DOWN_X && (g_aPolygon.pos.x - g_aPolygon.fWidth/5)<= ONE_POLYGON_ONE_NAKA && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>= ONE_POLYGON_ONE_UP_Y && (g_aPolygon.pos.y+g_aPolygon.fHeight/5) <= ONE_POLYGON_ONE_DOWN_Y)
		{
			g_aPolygon.pos.x =ONE_POLYGON_ONE_DOWN_X - g_aPolygon.fWidth/5;
		}	

		if((g_aPolygon.pos.x - g_aPolygon.fWidth/5)<=ONE_POLYGON_TWO_DOWN_X && (g_aPolygon.pos.x - g_aPolygon.fWidth/5)>=ONE_POLYGON_TWO_NAKA && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=ONE_POLYGON_TWO_UP_Y && (g_aPolygon.pos.y+g_aPolygon.fHeight/5) <= ONE_POLYGON_TWO_DOWN_Y)
		{
			g_aPolygon.pos.x =ONE_POLYGON_TWO_DOWN_X + g_aPolygon.fWidth/5;
		}

		if((g_aPolygon.pos.x - g_aPolygon.fWidth/5)>=ONE_POLYGON_THREE_DOWN_X && (g_aPolygon.pos.x + g_aPolygon.fWidth/5)<=ONE_POLYGON_THREE_UP_X && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=ONE_POLYGON_THREE_DOWN_Y && (g_aPolygon.pos.y+g_aPolygon.fHeight/5) <= ONE_POLYGON_THREE_NAKA)
		{
			g_aPolygon.pos.y=ONE_POLYGON_THREE_DOWN_Y-g_aPolygon.fHeight/5 ;
		}
		
		if((g_aPolygon.pos.x - g_aPolygon.fWidth/5)>=ONE_POLYGON_FOUR_DOWN_X && (g_aPolygon.pos.x +
			g_aPolygon.fWidth/5)<=ONE_POLYGON_FOUR_UP_X && (g_aPolygon.pos.y-g_aPolygon.fHeight/5)>=ONE_POLYGON_FOUR_NAKA && (g_aPolygon.pos.y-g_aPolygon.fHeight/5) <= ONE_POLYGON_FOUR_UP_Y)
		{
			g_aPolygon.pos.y= ONE_POLYGON_FOUR_UP_Y + g_aPolygon.fHeight/5 ;
			if(bProp== true && bKey == false && GetKeyboardTrigger(DIK_E))/*判定*/
			{
				bProp= false;
				bKey = true;
				bPropUpdate = true;
			}
		}

		/*ポリゴン2*/
		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=TWO_POLYGON_ONE_DOWN_X && (g_aPolygon.pos.x - g_aPolygon.fWidth/5)<= TWO_POLYGON_ONE_NAKA && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>= TWO_POLYGON_ONE_UP_Y && (g_aPolygon.pos.y+g_aPolygon.fHeight/5) <= TWO_POLYGON_ONE_DOWN_Y)
		{
			g_aPolygon.pos.x =TWO_POLYGON_ONE_DOWN_X- g_aPolygon.fWidth/5;
		}	

		if((g_aPolygon.pos.x - g_aPolygon.fWidth/5)<=TWO_POLYGON_TWO_DOWN_X && (g_aPolygon.pos.x - g_aPolygon.fWidth/5)>=TWO_POLYGON_TWO_NAKA && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=TWO_POLYGON_TWO_UP_Y && (g_aPolygon.pos.y+g_aPolygon.fHeight/5) <= TWO_POLYGON_TWO_DOWN_Y)
		{
			g_aPolygon.pos.x =TWO_POLYGON_TWO_DOWN_X + g_aPolygon.fWidth/5;
		}

		///*ポリゴン3消します*/


		if((g_aPolygon.pos.x - g_aPolygon.fWidth/5)>=THREE_POLYGON_THREE_DOWN_X && (g_aPolygon.pos.x + g_aPolygon.fWidth/5)<=THREE_POLYGON_THREE_UP_X && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=THREE_POLYGON_THREE_DOWN_Y && (g_aPolygon.pos.y+g_aPolygon.fHeight/5) <= THREE_POLYGON_THREE_NAKA)
		{
			g_aPolygon.pos.y=THREE_POLYGON_THREE_DOWN_Y-g_aPolygon.fHeight/5;
		}
		
		if((g_aPolygon.pos.x - g_aPolygon.fWidth/5)>=THREE_POLYGON_FOUR_DOWN_X && (g_aPolygon.pos.x +g_aPolygon.fWidth/5)<=THREE_POLYGON_FOUR_UP_X && (g_aPolygon.pos.y-g_aPolygon.fHeight/5)>=THREE_POLYGON_FOUR_NAKA && (g_aPolygon.pos.y-g_aPolygon.fHeight/5) <= THREE_POLYGON_FOUR_UP_Y)
		{
			g_aPolygon.pos.y= THREE_POLYGON_FOUR_UP_Y + g_aPolygon.fHeight/5 ;
			if(GetKeyboardTrigger(DIK_E) )/*判定鍵とPROPない場合（PROPを取る）*/
			{
			bProp= true;
			bUseAvatar = true;
			bUseTalk = true;
			bUseTalk6 = true;
			if(GetKeyboardTrigger(DIK_E) && bUsebg2 == true)
			{
				bUseAvatar = true;
				bUseTalk = true;
				bUseTalk9 = true;
				bProp2 =true;
				UpdateProp2();
			}
			}
		}


		/*ポリゴン4*/
		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=FOUR_POLYGON_ONE_DOWN_X && (g_aPolygon.pos.x - g_aPolygon.fWidth/5)<= FOUR_POLYGON_ONE_NAKA && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>= FOUR_POLYGON_ONE_UP_Y && (g_aPolygon.pos.y+g_aPolygon.fHeight/5) <= FOUR_POLYGON_ONE_DOWN_Y)
		{
			g_aPolygon.pos.x =FOUR_POLYGON_ONE_DOWN_X - g_aPolygon.fWidth/5;
		}	

		if((g_aPolygon.pos.x - g_aPolygon.fWidth/5)>=FOUR_POLYGON_FOUR_DOWN_X && (g_aPolygon.pos.x +g_aPolygon.fWidth/5)<=FOUR_POLYGON_FOUR_UP_X && (g_aPolygon.pos.y-g_aPolygon.fHeight/5)>=FOUR_POLYGON_FOUR_NAKA && (g_aPolygon.pos.y-g_aPolygon.fHeight/5) <= FOUR_POLYGON_FOUR_UP_Y)
		{
			g_aPolygon.pos.y= FOUR_POLYGON_FOUR_UP_Y + g_aPolygon.fHeight/5 ;
		}
		}
		if(bUsebg3 == true && (GetKeyboardTrigger(DIK_E)))
		{
			if(( g_aPolygon.pos.x- (g_aPolygon.fWidth/5))>=(166.0f)
				&&( g_aPolygon.pos.x+ (g_aPolygon.fWidth/5))<=(393.0f)
				&&( g_aPolygon.pos.y- (g_aPolygon.fHeight/5))>=(41.0f)
				&&( g_aPolygon.pos.y+ (g_aPolygon.fHeight/5))<=(268.0f)
				)
				{		//SHITOU
					cnt_polygon = 0;
					SetFade(FADE_OUT,MODE_RESULT);
				}

			if(( g_aPolygon.pos.x- (g_aPolygon.fWidth/5))>=(151.0f)
				&&( g_aPolygon.pos.x+ (g_aPolygon.fWidth/5))<=(392.0f)
				&&( g_aPolygon.pos.y- (g_aPolygon.fHeight/5))>=(275.0f)
				&&( g_aPolygon.pos.y+ (g_aPolygon.fHeight/5))<=(516.0f)
				)
				{		//JIANDAO
					cnt_polygon = 1;
					SetFade(FADE_OUT,MODE_RESULT);
				}

			if(( g_aPolygon.pos.x- (g_aPolygon.fWidth/5))>=(151.0f)
				&&( g_aPolygon.pos.x+ (g_aPolygon.fWidth/5))<=(392.0f)
				&&( g_aPolygon.pos.y- (g_aPolygon.fHeight/5))>=(522.0f)
				&&( g_aPolygon.pos.y+ (g_aPolygon.fHeight/5))<=(768.0f)
				)
				{		//BU
					cnt_polygon = 2;
					SetFade(FADE_OUT,MODE_RESULT);
				}
		}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	
}
void SetPolygon(D3DXVECTOR3 pos)
{
	g_aPolygon.pos.x = pos.x;
	g_aPolygon.pos.y = pos.y;
}
POLYGON *GetPolygon(void)
{
	return &g_aPolygon;
}