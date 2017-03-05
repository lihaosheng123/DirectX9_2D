#include "input.h"
//�O���[�o���ϐ�
LPDIRECTINPUT8 g_pInput = NULL;		//DirectInput�I���W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;		//���̓f�o�C�X�i�L�[�{�[�h�j�ւ̃|�C���^
BYTE g_keyState[ 256 ];
BYTE g_keyStatePress[ 256 ];		//�L�[�{�[�h���͏�񃏁[�N
BYTE g_keyStateTrigger[ 256 ];		// �L�[�g���K�[���
BYTE g_keyStateRelease [256];		// �L�[�����[�X���
//BYTE g_KeyStateRepeat [256];		// ���s�[�g���
//int g_KeyStateRepeatCount[256];		// ���s�[�g�J�E���^���

//=============================================================================
//  �֐����@�FHRESULT InitInput(HINSTANCE hInstance,HWND hwnd)
//  �@�\�T�v�F�L�[�{�[�h����������
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitInput(HINSTANCE hInstance,HWND hwnd)
{
	if(g_pInput == NULL)		//DirectInput�@�I���W�F�N�g�̐���
	{
		if(FAILED(DirectInput8Create(hInstance,DIRECTINPUT_VERSION,IID_IDirectInput8,(void **)&g_pInput,NULL)))
		{	
			return E_FAIL;
		}
	}
	return S_OK;
}
//=============================================================================
//  �֐����@�Fvoid UninitInput(void)
//  �@�\�T�v�F�L�[�{�[�h�I������
//  �߂�l�@�F
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
//  �֐����@�Fvoid UpdateInput(void)
//  �@�\�T�v�F�L�[�{�[�h�X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateInput(void)
{

}
//=============================================================================
//  �֐����@�FHRESULT InitKeyboard(HINSTANCE hInstance,HWND hwnd)
//  �@�\�T�v�F�L�[�{�[�h����������
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitKeyboard(HINSTANCE hInstance,HWND hWnd)
{
	if(FAILED(InitInput(hInstance,hWnd)))
	{
		return E_FAIL;
	}
	if(FAILED(g_pInput->CreateDevice(GUID_SysKeyboard,&g_pDevKeyboard,NULL)))		//�f�o�C�X�̐���
	{
		return E_FAIL;
	}
	if(FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))		//�f�[�^�t�H�[�}�b�g�̐���
	{
		return E_FAIL;
	}//�������[�h�̐ݒ�
	if(FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	g_pDevKeyboard->Acquire();		//�A�N�Z�X���̎�I
	return S_OK;
}
//=============================================================================
//  �֐����@�Fvoid UninitKeyboard(void)
//  �@�\�T�v�F�L�[�{�[�h�I������
//  �߂�l�@�F
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
//  �֐����@�Fvoid UpadateKeyboard(void)
//  �@�\�T�v�F�L�[�{�[�h�X�V����
//  �߂�l�@�F
//=============================================================================
void UpadateKeyboard(void)
{
	int cnt;
	BYTE aKeyState [ 256 ];


	if(SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState),&aKeyState[0])))
	{
		for( cnt = 0 ;cnt < 256 ;cnt++ )
		{

			//�g���K�[
			g_keyStateTrigger[ cnt ] =( g_keyState[ cnt ] ^ aKeyState[ cnt ] ) & aKeyState[ cnt ];

			//�����[�X

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
//  �֐����@�Fbool GetKeyboardPress(int nKey)
//  �@�\�T�v�F�L�[�{�[�hGET����
//  �߂�l�@�Fbool
//=============================================================================
bool GetKeyboardPress(int nKey)
{
	return (g_keyState[nKey]&0x80)?true:false;
}

/*******************************************************************************
* �֐���: IsTriggerKey
* 
* ����  : nKey
* �߂�l: bool
* ����  : 
*******************************************************************************/
bool GetKeyboardTrigger( int nKey )
{
	return (g_keyStateTrigger[nKey]&0x80)?true:false;
}

/*******************************************************************************
* �֐���: IsReleaseKey
* 
* ����  : nKey
* �߂�l: bool
* ����  : 
*******************************************************************************/
bool GetKeyboardRelease( int nKey )
{
	return (g_keyStateRelease[nKey]&0x80)?true:false;
}
/*******************************************************************************
* �֐���: IsRepeatKey
* 
* ����  : nKey
* �߂�l: bool
* ����  : 
*******************************************************************************/
//bool GetKeyboardRepeat( int nKey )
//{
//	return (g_KeyStateRepeat[nKey]&0x80)?true:false;
//}
