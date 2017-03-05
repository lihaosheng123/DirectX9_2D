/********************************************************************************
* タイトル　04
* ファイル名　main.cpp
* 作成者 AT11D243 36 李昊盛
* 作成日 2015/06/04
*
********************************************************************************/
/*******************************************************************************
* インクルードファイル
******************************************************************************/
#include "main.h"
#include "polygon.h"
#include "bg1.h"
#include "bg2.h"
#include "bg3.h"
#include "input.h"
#include "bullet.h"
#include "bulletenemy.h"
#include "title.h"
#include "title1.h"
#include "result.h"
#include "game1.h"
#include "game2.h"
#include "game3.h"
#include "score.h"
#include "fade.h"
#include "sound.h"
#include "enemy.h"
#include "door.h"
#include "timebg.h"
#include "press.h"
#include "avatar.h"
#include "talk.h"
#include "talk1.h"
#include "talk2.h"
#include "talk3.h"
#include "talk4.h"
//#include "talk5.h"
//#include "talk6.h"
//#include "talk7.h"
#include "explosion.h"
#include "life.h"
#include "prop.h"
#include "prop2.h"
#include "key.h"
#include "explosionenemy.h"
#include "lifeenemy.h"
#include "enemy2.h"
#include "enemy3.h"
#include "computer.h"
#include "jieshao.h"
#include "jieshaobg.h"
#include "caiquan.h"
#include "effect.h"
#include "pause.h"
/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);

HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow);
void Update( void );
void Draw( void );
void Uninit( void );
#ifdef _DEBUG
void DrawFPS( void );
#endif

//グローバル変数
MODE g_mode = MODE_TITLEHONG;		//現在のモード
LPDIRECT3D9 g_pD3D = NULL;		//Direct3Dオブジ	ェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice=NULL;	//Direct3Dデバイスへのポインタ
LPD3DXFONT g_pFont = NULL;		//フォントへのポインタ
int g_nCountFPS;		//FPSカウンタ
//宣言
int nID;
/********************************************************************
WinMain関数　Windows プログラムは WinMain から開始
*	表示ウィンドウの属性設定とWindowsへの登録
*	初期設定
*	メッセージループ
*********************************************************************/
int WINAPI WinMain ( HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR LPCmdLine,int nCmdShow )
{
	HWND hWnd;//ワインドウハンドル
	MSG msg;//メッセージ

	WNDCLASSEX wcex=
	{
		sizeof(WNDCLASSEX),//メリスを取得
		CS_CLASSDC,//ウインドウスト
		WndProc,//ウインドロフロシジのアドレス
		0,
		0,
		hInstance,//インスタンスハンドラレ
		NULL,
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW+1),
		NULL,
		"box",//名前
		NULL
	};

	RegisterClassEx(&wcex);
	hWnd = CreateWindowEx(0,
	"box",
	"DirectX",
	WS_OVERLAPPEDWINDOW,
	CW_USEDEFAULT,
	CW_USEDEFAULT,
	SCREEN_WIDTH,
	SCREEN_HEIGHT,
	NULL,
	NULL,
	hInstance,
	NULL);
	if(FAILED(Init(hInstance,hWnd,TRUE)))	//初期化処理(失敗したら)
	{
		return -1;
	}

	ShowWindow( hWnd, nCmdShow ) ;
	UpdateWindow( hWnd ) ;
	DWORD dwFrameCount;
	DWORD dwCurrentTime;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	timeBeginPeriod (1);
	dwFrameCount =
	dwCurrentTime = 0;
	dwExecLastTime =
	dwFPSLastTime = timeGetTime();
	//メッセージループ
	while(1)
	{
		if(PeekMessage( &msg, NULL, 0, 0 ,PM_REMOVE)!= 0)
		{
			if(msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage( &msg );//メッセージの翻訳//キーボード利用を可能にする
				DispatchMessage( &msg ) ;// 制御をWindowsに戻す
			}
		}
		{
			/*FPSの計算*/
			dwCurrentTime = timeGetTime();
			if((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				Update();        /*更新処理*/
				Draw();          /*描画処理*/

				dwFrameCount ++;
			}

		}
	}

	Uninit();				/*終了処理*/

	UnregisterClass("box",wcex.hInstance);//ウインドウクラスの登録と解除*
	timeEndPeriod(1);
	return(int)msg.wParam;
}
//=============================================================================
//  関数名　：LPDIRECT3DDEVICE9 GetDevice(void)
//  機能概要：値を渡す
//  戻り値　：LPDIRECT3DDEVICE9
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
/*******************************************************************************
* 関数名:HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow)
* 説明:初期化の設定
*******************************************************************************/
HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow)
{
	/*変数の宣言*/
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);	//Direct3Dオブジェクトの完成
	InitKeyboard(hInstance,hWnd);	//
		if(g_pD3D == NULL)
	{
		return E_FAIL;
	}
	if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3ddm)))	//ディスプレイモード（画面解像度）
	{
		return E_FAIL;
	}
	ZeroMemory(&d3dpp,sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;		//size
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;		//size
	d3dpp.BackBufferFormat = d3ddm.Format;	//バークバッファ形式
	d3dpp.BackBufferCount = 1;	//バークバッファ数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;	//テッグスバッファとステンシルバファの生成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//	16ビットで使用
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	
	if(FAILED(g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,	//描画
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,	//頂点処理
		&d3dpp,
		&g_pD3DDevice)))	//Direce 3Dデバイスの生成
	{
		if(FAILED(g_pD3D->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))	//Direce 3Dデバイスの生成
		{
			if(FAILED(g_pD3D->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))	//Direce 3Dデバイスの生成
			{
				return E_FAIL;
			}
		}
	}
	/*レンダーステートの設定*/
	g_pD3DDevice -> SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);
	g_pD3DDevice -> SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	g_pD3DDevice -> SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	g_pD3DDevice -> SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	/*サンプラーステートの設定*/
	g_pD3DDevice -> SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
	g_pD3DDevice -> SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
	g_pD3DDevice -> SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP);
	g_pD3DDevice -> SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_WRAP);

	/*テクスチャステージステートの設定*/
	//g_pD3DDevice -> SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
	//g_pD3DDevice -> SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
	//g_pD3DDevice -> SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_CURRENT);

	//初期化処理
	D3DXCreateFont(g_pD3DDevice,18,0,0,0,FALSE,
			SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH,
			"Terminal",
			&g_pFont);
	InitSound(hWnd);
	InitFade();
	//InitEffect();
	InitPause();
	SetMode(g_mode);
	InitKeyboard(hInstance,hWnd);//キーボード操作初期化処理
	return S_OK;
}
//=============================================================================
//  関数名　：Uninit
//  機能概要：全プログラム終了処理
//  戻り値　：
//=============================================================================
void Uninit (void)
{ 
	UninitSound();
	UninitKeyboard();
	//UninitEffect();
	UninitPause();
	//キーボード操作終了処理
	/*ポインタ変数の開放*/
	if(g_pD3DDevice!=NULL)
	{
		g_pD3DDevice->Release();	//デバイスの関数
		g_pD3DDevice = NULL;
	}
	if(g_pD3D!=NULL)
	{
		g_pD3D->Release();	//オブジェクトの関数
		g_pD3D = NULL;
	}

}
//=============================================================================
//  関数名　：Draw
//  機能概要：メッセージ画面描画
//  戻り値　：
//=============================================================================
void Draw (void)
{
	g_pD3DDevice->Clear(0,NULL,
	(D3DCLEAR_TARGET|
	D3DCLEAR_ZBUFFER),
	D3DCOLOR_RGBA(0,0,0,0),	//R,G,B,透明度
	1.0f,0);	//画面のクリア

	if(SUCCEEDED(g_pD3DDevice->BeginScene()))	//描画開始
	{
		switch (g_mode)
		{
		case MODE_TITLEHONG:
			DrawTitle1();
			break;

		case MODE_JIESHAO:
			DrawJieshao();
			break;

		case MODE_GAME1:
			DrawGame1();
			break;

		case MODE_GAME2:
			DrawGame2();
			break;

		case MODE_GAME3:
			DrawGame3();
			break;

		case MODE_RESULT:
			DrawResult();
			break;
		default:
		break;
		}
		DrawFade();
	//	DrawEffect();
		DrawPause();
		/*DEBUG時のFPS*/
#ifdef _DEBUG
		DrawFPS();
#endif
		g_pD3DDevice->EndScene();
	}
	g_pD3DDevice->Present(NULL,NULL,NULL,NULL);	//バックバッファをディスプレイに表示
}
//=============================================================================
//  関数名　：Update
//  機能概要：プログラム更新処理
//  戻り値　：
//=============================================================================
void Update(void)
{
	UpadateKeyboard();//キーボード操作の更新処理
		PAUSEUSE *bUseCheck = GetPause();
	if(bUseCheck->bUse == false)
	{
	switch(g_mode)
		{
	case MODE_TITLEHONG:
		UpdateTitle1();
		break;

	case MODE_JIESHAO:
		UpdateJieshao();
		break;

	case MODE_GAME1:
		UpdateGame1();
		break;

	case MODE_GAME2:
		UpdateGame2();
		break;

	case MODE_GAME3:
		UpdateGame3();
		break;

	case MODE_RESULT:
		UpdateResult();
		break;

	default:
	break;
		}
	}
	if(GetKeyboardTrigger(DIK_RETURN) == true )
	{
	switch(g_mode)
		{
	case MODE_TITLEHONG:
		SetFade(FADE_OUT,MODE_GAME1);
		break;
		case MODE_JIESHAO:
		SetFade(FADE_OUT,MODE_GAME1);
		break;

	case MODE_GAME1:
		SetFade(FADE_OUT,MODE_GAME2);
		break;

	case MODE_GAME2:
		SetFade(FADE_OUT,MODE_GAME3);
		break;

	case MODE_GAME3:
		SetFade(FADE_OUT,MODE_RESULT);
		break;

	case MODE_RESULT:
		SetFade(FADE_OUT,MODE_TITLEHONG);
		break;

	default:
	break;
		}
	}
	if(bUseCheck->bUse == false)
	{
	UpdateFade();
//	UpdateEffect();
	}
	UpdatePause();

	if(GetKeyboardTrigger(DIK_P))
	{
	bUseCheck->bUse = true;
	}

	if(GetKeyboardTrigger(DIK_O))
	{
	bUseCheck->bUse = false;
	}
}
//=============================================================================
//		ウィンドウプロシージャ関数（WindowProcedure）
//		(Windowsメッセージ処理を行う)
//=============================================================================
LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch(uMsg)
	{
	case WM_DESTROY://"WM_QUIT"メッセージを返す//閉じるボタンをクリックした時
		PostQuitMessage(0);// WM_QUITメッセージを発行
		break;
	case WM_KEYDOWN://キーが押された
		switch(wParam)
		{
		case VK_ESCAPE://ESCキー
		nID=MessageBox(hWnd,"ESCしますか","ESC",MB_YESNO);

		if(nID==IDYES)
		{
			DestroyWindow(hWnd);
		}
		break;
		}

		default:	//上記以外のメッセージはWindowsへ処理を任せる
		break;

	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

void DrawFPS(void)
{
	/*変数の宣言*/
	RECT rect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	char aStr[256];

	wsprintf(&aStr[0],"FPS:%d\n",g_nCountFPS);
	g_pFont ->DrawText(NULL,&aStr[0],-1,&rect,DT_LEFT,D3DCOLOR_RGBA(255,255,255,255));
}
//=============================================================================
//  関数名　：SetMode
//  機能概要：
//  戻り値　：
//=============================================================================
void SetMode(MODE mode)
{
	switch(g_mode)
	{
	case MODE_TITLEHONG:
		UninitTitle1();
		break;

	case MODE_JIESHAO:
		UninitJieshao();
		break;

	case MODE_GAME1:
		UninitGame1();
		break;

	case MODE_GAME2:
		UninitGame2();
		break;

	case MODE_GAME3:
		UninitGame3();
		break;

	case MODE_RESULT:
		UninitResult();
		break;

	default:
	break;
	}
	switch(mode)
	{
	case MODE_TITLEHONG:
		InitTitle1();
		break;

	case MODE_JIESHAO:
		InitJieshao();
		break;

	case MODE_GAME1:
		InitGame1();
		break;

	case MODE_GAME2:
		InitGame2();
		break;

	case MODE_GAME3:
		InitGame3();
		break;

	case MODE_RESULT:
		InitResult();
		break;

	default:
	break;
	}
	g_mode = mode;
}

//=============================================================================
//  関数名　：MODE GetMode(void)
//  機能概要：
//  戻り値　：g_mode
//=============================================================================
MODE GetMode(void)
{
	return g_mode;
}
