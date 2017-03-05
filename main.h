#ifndef _MAIN_H_
#define _MAIN_H_
#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"		//���͏����ɕK�v
#pragma comment(lib,"dinput8.lib")//���͏����ɕK�v
//�C���N���[�h�t�@�C��
#include <windows.h>
#include "d3dx9.h"	//�`�揈���ɕK�v
//#pragma�f�B���B�f�B�u�ǉ��i���C�u�����̃����N�j
#pragma comment(lib,"d3d9.lib")		//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")	//��L�̊g�����C�u�E��
#pragma comment(lib,"dxguid.lib")	//DirectX�R���{�\�l���g�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")

//�}�N����`
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//�e�N�X�`�����W
#define SCREEN_CENTER_X	( SCREEN_WIDTH / 2 )		//�E�C���h�E�̒��S�w���W
#define SCREEN_CENTER_Y	( SCREEN_HEIGHT / 2 )		//�E�C���h�E�̒��S�x���W
//�\����
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;	//���W�ϊ��p�W��(�@��)
	D3DCOLOR col;		//���_���[�N(���_�F)	
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
} VERTEX_2D;
//���[�h�̎��
typedef enum
{
	MODE_TITLEHONG = 0,		//�^�C�g�����
	MODE_JIESHAO,
	MODE_GAME1,		//�Q�[�����1
	MODE_GAME2,		//�Q�[�����2
	MODE_GAME3,		//�Q�[�����3
	MODE_RESULT,		//���U���g���
	MODE_MAX
} MODE;
//�v���g�^�C�v�錾
LPDIRECT3DDEVICE9 GetDevice(void);
void DrawFPS(void);
void SetMode( MODE mode);
MODE GetMode(void);
#endif