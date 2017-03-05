#include "main.h"
#include "title.h"
#include "input.h"
#include "press.h"
#include "sound.h"
//�O���[�o���ϐ�
VERTEX_2D g_title[4];
LPDIRECT3DTEXTURE9 g_pTexturetitle =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufftitle =NULL;	//���_�p�b�t�@�ւ̃|�C���^
//=============================================================================
//  �֐����@�FInittitle
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBufftitle,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *title;
		g_pVtxBufftitle ->Lock(0,0,(void **)&title,0);		//���_���ւ̃|�C���^���擾
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\title.png",
		&g_pTexturetitle);
		title[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		title[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
		title[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		title[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		title[0].rhw = 1.0f;
		title[1].rhw = 1.0f;
		title[2].rhw = 1.0f;
		title[3].rhw = 1.0f;
		title[0].col=D3DCOLOR_RGBA(200,200,200,255);	//���_���i�[���[�N
		title[1].col=D3DCOLOR_RGBA(200,200,200,255);
		title[2].col=D3DCOLOR_RGBA(200,200,200,255);
		title[3].col=D3DCOLOR_RGBA(200,200,200,255);

		title[0].tex = D3DXVECTOR2(0.0f,0.0f);
		title[1].tex = D3DXVECTOR2(1.0f,0.0f);
		title[2].tex = D3DXVECTOR2(0.0f,1.0f);
		title[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBufftitle ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninittitle
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitTitle(void)
{
	if(g_pTexturetitle!=NULL)
	{
		g_pTexturetitle->Release();
		g_pTexturetitle=NULL;
	}
	if(g_pVtxBufftitle!=NULL)
	{
		g_pVtxBufftitle->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBufftitle=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawtitle
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTexturetitle);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBufftitle,
								0,
								sizeof(VERTEX_2D)
								);
	// �t�F�[�h�̕`��ݒ���e
	pDevice -> DrawPrimitive(
							  D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
							  0,		// �ŏ��̒��_�̃C���f�b�N�X
							  2			// �`�悷��v���~�e�B�u��
							);
}
//=============================================================================
//  �֐����@�FUpdatetitle
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateTitle(void)
{

}
