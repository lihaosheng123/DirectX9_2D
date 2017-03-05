/*******************************************************************************
* タイトル：ポーズ処理
* ファイル名：pause.cpp
* 作成者：AT12A244 46 LI
* 作成日：2016/03/01
*******************************************************************************/

/*******************************************************************************
* 更新履歴：
*******************************************************************************/

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "main.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "sound.h"
#include "pause.h"

/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define PAUSE_POSX ( SCREEN_CENTER_X )
#define PAUSE_POSY ( SCREEN_CENTER_Y )
#define PAUSE_WIDTH ( 250.0f )
#define PAUSE_HEIGHT ( 50.0f )
#define PAUSE_SPACE ( 5.0f )

/*******************************************************************************
* グローバル変数
********************************************************************************/
VERTEX_2D g_aVertexPause[ 4 ];								//頂点情報格納ワーク
LPDIRECT3DTEXTURE9 g_pTexturePause[ PAUSE_MENU_MAX ] = {NULL, NULL, NULL };		//テクスチャポリゴンへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;				//頂点バッファへのポインタ
PAUSE g_aPause[ PAUSE_MENU_MAX ];							//ポーズのワーク
PAUSE_MENU g_pauseMenu;										//ポーズメニューのワーク
PAUSEUSE bUseCheck;
/*******************************************************************************
* 関数名: InitPause
*******************************************************************************/
HRESULT InitPause( void )
{
	bUseCheck.bUse = false;
	//デバイスのゲッター
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成
	if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_2D ) * PAUSE_MENU_MAX * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPause, NULL ) ) )
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	g_pVtxBuffPause -> Lock( 0, 0, ( void** ) &pVtx, 0 );

	for( int nCntPause = 0; nCntPause < PAUSE_MENU_MAX; nCntPause++ )
	{
		//ポーズの位置の初期化
		g_aPause[ nCntPause ].pos = D3DXVECTOR3( PAUSE_POSX, PAUSE_POSY + ( PAUSE_HEIGHT + PAUSE_SPACE ) * nCntPause, 0.0f );

		switch( nCntPause )
		{
			case PAUSE_MENU_CONTINUE:
				D3DXCreateTextureFromFile( pDevice, PAUSE_CONTINUE_FILE, &g_pTexturePause[ PAUSE_MENU_CONTINUE ] );
				break;
			case PAUSE_MENU_RETRY:
				D3DXCreateTextureFromFile( pDevice, PAUSE_RETRY_FILE, &g_pTexturePause[ PAUSE_MENU_RETRY ] );
				break;
			case PAUSE_MENU_QUIT:
				D3DXCreateTextureFromFile( pDevice, PAUSE_QUIT_FILE, &g_pTexturePause[ PAUSE_MENU_QUIT ] );
				break;
			default:
				break;
		}

		//4頂点座標のX Y Zの初期化
		pVtx[ 0 + nCntPause * 4 ].pos.x = g_aPause[ nCntPause ].pos.x - PAUSE_WIDTH * 0.50f;
		pVtx[ 0 + nCntPause * 4 ].pos.y = g_aPause[ nCntPause ].pos.y - PAUSE_HEIGHT * 0.50f;
		pVtx[ 0 + nCntPause * 4 ].pos.z = 0.0f;

		pVtx[ 1 + nCntPause * 4 ].pos.x = g_aPause[ nCntPause ].pos.x + PAUSE_WIDTH * 0.50f;
		pVtx[ 1 + nCntPause * 4 ].pos.y = g_aPause[ nCntPause ].pos.y - PAUSE_HEIGHT * 0.50f;
		pVtx[ 1 + nCntPause * 4 ].pos.z = 0.0f;

		pVtx[ 2 + nCntPause * 4 ].pos.x = g_aPause[ nCntPause ].pos.x - PAUSE_WIDTH * 0.50f;
		pVtx[ 2 + nCntPause * 4 ].pos.y = g_aPause[ nCntPause ].pos.y + PAUSE_HEIGHT * 0.50f;
		pVtx[ 2 + nCntPause * 4 ].pos.z = 0.0f;

		pVtx[ 3 + nCntPause * 4 ].pos.x = g_aPause[ nCntPause ].pos.x + PAUSE_WIDTH * 0.50f;
		pVtx[ 3 + nCntPause * 4 ].pos.y = g_aPause[ nCntPause ].pos.y + PAUSE_HEIGHT * 0.50f;
		pVtx[ 3 + nCntPause * 4 ].pos.z = 0.0f;

		//頂点座標の設定
		pVtx[ 0 + nCntPause * 4 ].pos = D3DXVECTOR3( pVtx[ 0 + nCntPause * 4 ].pos.x, pVtx[ 0 + nCntPause * 4 ].pos.y, pVtx[ 0 + nCntPause * 4 ].pos.z );
		pVtx[ 1 + nCntPause * 4 ].pos = D3DXVECTOR3( pVtx[ 1 + nCntPause * 4 ].pos.x, pVtx[ 1 + nCntPause * 4 ].pos.y, pVtx[ 1 + nCntPause * 4 ].pos.z );
		pVtx[ 2 + nCntPause * 4 ].pos = D3DXVECTOR3( pVtx[ 2 + nCntPause * 4 ].pos.x, pVtx[ 2 + nCntPause * 4 ].pos.y, pVtx[ 2 + nCntPause * 4 ].pos.z );
		pVtx[ 3 + nCntPause * 4 ].pos = D3DXVECTOR3( pVtx[ 3 + nCntPause * 4 ].pos.x, pVtx[ 3 + nCntPause * 4 ].pos.y, pVtx[ 3 + nCntPause * 4 ].pos.z );

		pVtx[ 0 + nCntPause * 4 ].rhw = 1.0f;
		pVtx[ 1 + nCntPause * 4 ].rhw = 1.0f;
		pVtx[ 2 + nCntPause * 4 ].rhw = 1.0f;
		pVtx[ 3 + nCntPause * 4 ].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[ 0 + nCntPause * 4 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
		pVtx[ 1 + nCntPause * 4 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
		pVtx[ 2 + nCntPause * 4 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
		pVtx[ 3 + nCntPause * 4 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );

		//テクスチャ座標の設定
		pVtx[ 0 + nCntPause * 4 ].tex = D3DXVECTOR2( 0.0f, 0.0f );
		pVtx[ 1 + nCntPause * 4 ].tex = D3DXVECTOR2( 1.0f, 0.0f );
		pVtx[ 2 + nCntPause * 4 ].tex = D3DXVECTOR2( 0.0f, 1.0f );
		pVtx[ 3 + nCntPause * 4 ].tex = D3DXVECTOR2( 1.0f, 1.0f );
	}

	g_pauseMenu = PAUSE_MENU_CONTINUE;
	g_aPause[ PAUSE_MENU_CONTINUE ].bUse = true;
	g_aPause[ PAUSE_MENU_RETRY ].bUse = false;
	g_aPause[ PAUSE_MENU_QUIT ].bUse = false;

	g_pVtxBuffPause -> Unlock();

	return S_OK;
}

/*******************************************************************************
* 関数名: UninitPause
*******************************************************************************/
void UninitPause( void )
{
	for( int nCntPause = 0; nCntPause < PAUSE_MENU_MAX; nCntPause++ )
	{
		if( g_pTexturePause[ nCntPause ] != NULL )
		{
			g_pTexturePause[ nCntPause ] -> Release();		//テクスチャポリゴンの開放
			g_pTexturePause[ nCntPause ] = NULL;
		}
	}

	if( g_pVtxBuffPause != NULL )
	{
		g_pVtxBuffPause -> Release();		//頂点バッファの開放
		g_pVtxBuffPause = NULL;
	}
}

/*******************************************************************************
* 関数名: UpdatePause
*******************************************************************************/
void UpdatePause( void )
{
	if(bUseCheck.bUse == true)
	{
	VERTEX_2D *pVtx;

	g_pVtxBuffPause -> Lock( 0, 0, ( void** ) &pVtx, 0 );

	MODE pMode = GetMode();;

	if( GetKeyboardTrigger( DIK_W ) || GetKeyboardTrigger( DIK_UP ) )
	{
		////選択SEの開始
		//PlaySound( SOUND_LABEL_SE_SELECT );
		switch( g_pauseMenu )
		{
			case PAUSE_MENU_CONTINUE:
				g_pauseMenu = PAUSE_MENU_QUIT;
				g_aPause[ PAUSE_MENU_CONTINUE ].bUse = false;
				g_aPause[ PAUSE_MENU_RETRY ].bUse = false;
				g_aPause[ PAUSE_MENU_QUIT ].bUse = true;
				break;
			case PAUSE_MENU_RETRY:
				g_pauseMenu = PAUSE_MENU_CONTINUE;
				g_aPause[ PAUSE_MENU_CONTINUE ].bUse = true;
				g_aPause[ PAUSE_MENU_RETRY ].bUse = false;
				g_aPause[ PAUSE_MENU_QUIT ].bUse = false;
				break;
			case PAUSE_MENU_QUIT:
				g_pauseMenu = PAUSE_MENU_RETRY;
				g_aPause[ PAUSE_MENU_CONTINUE ].bUse = false;
				g_aPause[ PAUSE_MENU_RETRY ].bUse = true;
				g_aPause[ PAUSE_MENU_QUIT ].bUse = false;
				break;
			default:
				break;
		}
	}

	if( GetKeyboardTrigger( DIK_S ) || GetKeyboardTrigger( DIK_DOWN ) )
	{
		////選択SEの開始
		//PlaySound( SOUND_LABEL_SE_SELECT );
		switch( g_pauseMenu )
		{
			case PAUSE_MENU_CONTINUE:
				g_pauseMenu = PAUSE_MENU_RETRY;
				g_aPause[ PAUSE_MENU_CONTINUE ].bUse = false;
				g_aPause[ PAUSE_MENU_RETRY ].bUse = true;
				g_aPause[ PAUSE_MENU_QUIT ].bUse = false;
				break;
			case PAUSE_MENU_RETRY:
				g_pauseMenu = PAUSE_MENU_QUIT;
				g_aPause[ PAUSE_MENU_CONTINUE ].bUse = false;
				g_aPause[ PAUSE_MENU_RETRY ].bUse = false;
				g_aPause[ PAUSE_MENU_QUIT ].bUse = true;
				break;
			case PAUSE_MENU_QUIT:
				g_pauseMenu = PAUSE_MENU_CONTINUE;
				g_aPause[ PAUSE_MENU_CONTINUE ].bUse = true;
				g_aPause[ PAUSE_MENU_RETRY ].bUse = false;
				g_aPause[ PAUSE_MENU_QUIT ].bUse = false;
				break;
			default:
				break;
		}
	}

	if( GetKeyboardTrigger( DIK_L ) )
	{
		switch( g_pauseMenu )
		{
			case PAUSE_MENU_CONTINUE:
				bUseCheck.bUse = false;
				break;
			case PAUSE_MENU_RETRY:
				SetFade( FADE_OUT, MODE_GAME1);
				bUseCheck.bUse = false;
				break;
			case PAUSE_MENU_QUIT:
				SetFade( FADE_OUT, MODE_TITLEHONG);
				bUseCheck.bUse = false;
				break;
			default:
				break;
		}

	}

	for( int nCntPause = 0; nCntPause < PAUSE_MENU_MAX; nCntPause++ )
	{
		//頂点カラーの設定
		if( g_aPause[ nCntPause ].bUse == true )
		{
			pVtx[ 0 + nCntPause * 4 ].col = D3DCOLOR_RGBA( 255, 0, 0, 255 );
			pVtx[ 1 + nCntPause * 4 ].col = D3DCOLOR_RGBA( 255, 0, 0, 255 );
			pVtx[ 2 + nCntPause * 4 ].col = D3DCOLOR_RGBA( 255, 0, 0, 255 );
			pVtx[ 3 + nCntPause * 4 ].col = D3DCOLOR_RGBA( 255, 0, 0, 255 );
		}
		else
		{
			pVtx[ 0 + nCntPause * 4 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ 1 + nCntPause * 4 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ 2 + nCntPause * 4 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ 3 + nCntPause * 4 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
		}
	}

	g_pVtxBuffPause -> Unlock();
	}
}

/*******************************************************************************
* 関数名: DrawPause
*******************************************************************************/
void DrawPause( void )
{
	if(bUseCheck.bUse == true)
	{
	//デバイスのゲッター
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource( 0, g_pVtxBuffPause, 0, sizeof( VERTEX_2D ) );

	//頂点フォーマットの設定
	pDevice -> SetFVF( FVF_VERTEX_2D );

	for( int nCntPause = 0; nCntPause < PAUSE_MENU_MAX; nCntPause++ )
	{
		//テクスチャの設定
		pDevice -> SetTexture( 0, g_pTexturePause[ nCntPause ] );

		//ポリゴンの描画
		pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP, nCntPause * 4, 2 );
	}
	}
}
PAUSEUSE *GetPause(void)
{
	return &bUseCheck;
}