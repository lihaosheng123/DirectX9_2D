#include "input.h"
//グローバル変数
LPDIRECTINPUT8 g_pInput = NULL;		//DirectInputオラジェクトへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;		//入力デバイス（キーボード）へのポインタ
BYTE g_keyState[ 256 ];
BYTE g_keyStatePress[ 256 ];		//キーボード入力情報ワーク
BYTE g_keyStateTrigger[ 256 ];		// キートリガー情報
BYTE g_keyStateRelease [256];		// キーリリース情報
//BYTE g_KeyStateRepeat [256];		// リピート情報
//int g_KeyStateRepeatCount[256];		// リピートカウンタ情報

//=============================================================================
//  関数名　：HRESULT InitInput(HINSTANCE hInstance,HWND hwnd)
//  機能概要：キーボード初期化処理
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitInput(HINSTANCE hInstance,HWND hwnd)
{
	if(g_pInput == NULL)		//DirectInput　オラジェクトの生成
	{
		if(FAILED(DirectInput8Create(hInstance,DIRECTINPUT_VERSION,IID_IDirectInput8,(void **)&g_pInput,NULL)))
		{	
			return E_FAIL;
		}
	}
	return S_OK;
}
//=============================================================================
//  関数名　：void UninitInput(void)
//  機能概要：キーボード終了処理
//  戻り値　：
//=============================================================================
void UninitInput(void)
{
	if(g_pInput!= NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
//=============================================================================
//  関数名　：void UpdateInput(void)
//  機能概要：キーボード更新処理
//  戻り値　：
//=============================================================================
void UpdateInput(void)
{

}
//=============================================================================
//  関数名　：HRESULT InitKeyboard(HINSTANCE hInstance,HWND hwnd)
//  機能概要：キーボード初期化処理
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitKeyboard(HINSTANCE hInstance,HWND hWnd)
{
	if(FAILED(InitInput(hInstance,hWnd)))
	{
		return E_FAIL;
	}
	if(FAILED(g_pInput->CreateDevice(GUID_SysKeyboard,&g_pDevKeyboard,NULL)))		//デバイスの生成
	{
		return E_FAIL;
	}
	if(FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))		//データフォーマットの生成
	{
		return E_FAIL;
	}//協調モードの設定
	if(FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	g_pDevKeyboard->Acquire();		//アクセス権の取的
	return S_OK;
}
//=============================================================================
//  関数名　：void UninitKeyboard(void)
//  機能概要：キーボード終了処理
//  戻り値　：
//=============================================================================
void UninitKeyboard(void)
{
	if(g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}
	UninitInput();
}
//=============================================================================
//  関数名　：void UpadateKeyboard(void)
//  機能概要：キーボード更新処理
//  戻り値　：
//=============================================================================
void UpadateKeyboard(void)
{
	int cnt;
	BYTE aKeyState [ 256 ];


	if(SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState),&aKeyState[0])))
	{
		for( cnt = 0 ;cnt < 256 ;cnt++ )
		{

			//トリガー
			g_keyStateTrigger[ cnt ] =( g_keyState[ cnt ] ^ aKeyState[ cnt ] ) & aKeyState[ cnt ];

			//リリース

			g_keyStateRelease[cnt] =( g_keyState[ cnt ] ^ aKeyState[ cnt ] ) & g_keyState[ cnt ];
			g_keyState[ cnt ] = aKeyState[ cnt ];
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();
	}

}
//=============================================================================
//  関数名　：bool GetKeyboardPress(int nKey)
//  機能概要：キーボードGET処理
//  戻り値　：bool
//=============================================================================
bool GetKeyboardPress(int nKey)
{
	return (g_keyState[nKey]&0x80)?true:false;
}

/*******************************************************************************
* 関数名: IsTriggerKey
* 
* 引数  : nKey
* 戻り値: bool
* 説明  : 
*******************************************************************************/
bool GetKeyboardTrigger( int nKey )
{
	return (g_keyStateTrigger[nKey]&0x80)?true:false;
}

/*******************************************************************************
* 関数名: IsReleaseKey
* 
* 引数  : nKey
* 戻り値: bool
* 説明  : 
*******************************************************************************/
bool GetKeyboardRelease( int nKey )
{
	return (g_keyStateRelease[nKey]&0x80)?true:false;
}
/*******************************************************************************
* 関数名: IsRepeatKey
* 
* 引数  : nKey
* 戻り値: bool
* 説明  : 
*******************************************************************************/
//bool GetKeyboardRepeat( int nKey )
//{
//	return (g_KeyStateRepeat[nKey]&0x80)?true:false;
//}
