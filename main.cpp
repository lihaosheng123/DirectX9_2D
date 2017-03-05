/********************************************************************************
* �^�C�g���@04
* �t�@�C�����@main.cpp
* �쐬�� AT11D243 36 ���ݐ�
* �쐬�� 2015/06/04
*
********************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
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
* �v���g�^�C�v�錾
*******************************************************************************/
LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);

HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow);
void Update( void );
void Draw( void );
void Uninit( void );
#ifdef _DEBUG
void DrawFPS( void );
#endif

//�O���[�o���ϐ�
MODE g_mode = MODE_TITLEHONG;		//���݂̃��[�h
LPDIRECT3D9 g_pD3D = NULL;		//Direct3D�I�u�W	�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice=NULL;	//Direct3D�f�o�C�X�ւ̃|�C���^
LPD3DXFONT g_pFont = NULL;		//�t�H���g�ւ̃|�C���^
int g_nCountFPS;		//FPS�J�E���^
//�錾
int nID;
/********************************************************************
WinMain�֐��@Windows �v���O������ WinMain ����J�n
*	�\���E�B���h�E�̑����ݒ��Windows�ւ̓o�^
*	�����ݒ�
*	���b�Z�[�W���[�v
*********************************************************************/
int WINAPI WinMain ( HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR LPCmdLine,int nCmdShow )
{
	HWND hWnd;//���C���h�E�n���h��
	MSG msg;//���b�Z�[�W

	WNDCLASSEX wcex=
	{
		sizeof(WNDCLASSEX),//�����X���擾
		CS_CLASSDC,//�E�C���h�E�X�g
		WndProc,//�E�C���h���t���V�W�̃A�h���X
		0,
		0,
		hInstance,//�C���X�^���X�n���h����
		NULL,
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW+1),
		NULL,
		"box",//���O
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
	if(FAILED(Init(hInstance,hWnd,TRUE)))	//����������(���s������)
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
	//���b�Z�[�W���[�v
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
				TranslateMessage( &msg );//���b�Z�[�W�̖|��//�L�[�{�[�h���p���\�ɂ���
				DispatchMessage( &msg ) ;// �����Windows�ɖ߂�
			}
		}
		{
			/*FPS�̌v�Z*/
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

				Update();        /*�X�V����*/
				Draw();          /*�`�揈��*/

				dwFrameCount ++;
			}

		}
	}

	Uninit();				/*�I������*/

	UnregisterClass("box",wcex.hInstance);//�E�C���h�E�N���X�̓o�^�Ɖ���*
	timeEndPeriod(1);
	return(int)msg.wParam;
}
//=============================================================================
//  �֐����@�FLPDIRECT3DDEVICE9 GetDevice(void)
//  �@�\�T�v�F�l��n��
//  �߂�l�@�FLPDIRECT3DDEVICE9
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
/*******************************************************************************
* �֐���:HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow)
* ����:�������̐ݒ�
*******************************************************************************/
HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow)
{
	/*�ϐ��̐錾*/
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);	//Direct3D�I�u�W�F�N�g�̊���
	InitKeyboard(hInstance,hWnd);	//
		if(g_pD3D == NULL)
	{
		return E_FAIL;
	}
	if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3ddm)))	//�f�B�X�v���C���[�h�i��ʉ𑜓x�j
	{
		return E_FAIL;
	}
	ZeroMemory(&d3dpp,sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;		//size
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;		//size
	d3dpp.BackBufferFormat = d3ddm.Format;	//�o�[�N�o�b�t�@�`��
	d3dpp.BackBufferCount = 1;	//�o�[�N�o�b�t�@��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;	//�e�b�O�X�o�b�t�@�ƃX�e���V���o�t�@�̐���
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//	16�r�b�g�Ŏg�p
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	
	if(FAILED(g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,	//�`��
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,	//���_����
		&d3dpp,
		&g_pD3DDevice)))	//Direce 3D�f�o�C�X�̐���
	{
		if(FAILED(g_pD3D->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))	//Direce 3D�f�o�C�X�̐���
		{
			if(FAILED(g_pD3D->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))	//Direce 3D�f�o�C�X�̐���
			{
				return E_FAIL;
			}
		}
	}
	/*�����_�[�X�e�[�g�̐ݒ�*/
	g_pD3DDevice -> SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);
	g_pD3DDevice -> SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	g_pD3DDevice -> SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	g_pD3DDevice -> SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	/*�T���v���[�X�e�[�g�̐ݒ�*/
	g_pD3DDevice -> SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
	g_pD3DDevice -> SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
	g_pD3DDevice -> SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP);
	g_pD3DDevice -> SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_WRAP);

	/*�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�*/
	//g_pD3DDevice -> SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
	//g_pD3DDevice -> SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
	//g_pD3DDevice -> SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_CURRENT);

	//����������
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
	InitKeyboard(hInstance,hWnd);//�L�[�{�[�h���쏉��������
	return S_OK;
}
//=============================================================================
//  �֐����@�FUninit
//  �@�\�T�v�F�S�v���O�����I������
//  �߂�l�@�F
//=============================================================================
void Uninit (void)
{ 
	UninitSound();
	UninitKeyboard();
	//UninitEffect();
	UninitPause();
	//�L�[�{�[�h����I������
	/*�|�C���^�ϐ��̊J��*/
	if(g_pD3DDevice!=NULL)
	{
		g_pD3DDevice->Release();	//�f�o�C�X�̊֐�
		g_pD3DDevice = NULL;
	}
	if(g_pD3D!=NULL)
	{
		g_pD3D->Release();	//�I�u�W�F�N�g�̊֐�
		g_pD3D = NULL;
	}

}
//=============================================================================
//  �֐����@�FDraw
//  �@�\�T�v�F���b�Z�[�W��ʕ`��
//  �߂�l�@�F
//=============================================================================
void Draw (void)
{
	g_pD3DDevice->Clear(0,NULL,
	(D3DCLEAR_TARGET|
	D3DCLEAR_ZBUFFER),
	D3DCOLOR_RGBA(0,0,0,0),	//R,G,B,�����x
	1.0f,0);	//��ʂ̃N���A

	if(SUCCEEDED(g_pD3DDevice->BeginScene()))	//�`��J�n
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
		/*DEBUG����FPS*/
#ifdef _DEBUG
		DrawFPS();
#endif
		g_pD3DDevice->EndScene();
	}
	g_pD3DDevice->Present(NULL,NULL,NULL,NULL);	//�o�b�N�o�b�t�@���f�B�X�v���C�ɕ\��
}
//=============================================================================
//  �֐����@�FUpdate
//  �@�\�T�v�F�v���O�����X�V����
//  �߂�l�@�F
//=============================================================================
void Update(void)
{
	UpadateKeyboard();//�L�[�{�[�h����̍X�V����
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
//		�E�B���h�E�v���V�[�W���֐��iWindowProcedure�j
//		(Windows���b�Z�[�W�������s��)
//=============================================================================
LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch(uMsg)
	{
	case WM_DESTROY://"WM_QUIT"���b�Z�[�W��Ԃ�//����{�^�����N���b�N������
		PostQuitMessage(0);// WM_QUIT���b�Z�[�W�𔭍s
		break;
	case WM_KEYDOWN://�L�[�������ꂽ
		switch(wParam)
		{
		case VK_ESCAPE://ESC�L�[
		nID=MessageBox(hWnd,"ESC���܂���","ESC",MB_YESNO);

		if(nID==IDYES)
		{
			DestroyWindow(hWnd);
		}
		break;
		}

		default:	//��L�ȊO�̃��b�Z�[�W��Windows�֏�����C����
		break;

	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

void DrawFPS(void)
{
	/*�ϐ��̐錾*/
	RECT rect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	char aStr[256];

	wsprintf(&aStr[0],"FPS:%d\n",g_nCountFPS);
	g_pFont ->DrawText(NULL,&aStr[0],-1,&rect,DT_LEFT,D3DCOLOR_RGBA(255,255,255,255));
}
//=============================================================================
//  �֐����@�FSetMode
//  �@�\�T�v�F
//  �߂�l�@�F
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
//  �֐����@�FMODE GetMode(void)
//  �@�\�T�v�F
//  �߂�l�@�Fg_mode
//=============================================================================
MODE GetMode(void)
{
	return g_mode;
}
