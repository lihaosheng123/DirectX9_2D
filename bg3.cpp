
#include "main.h"
#include "bg3.h"
#include "score.h"
//�O���[�o���ϐ�
VERTEX_2D g_bg3[4];
LPDIRECT3DTEXTURE9 g_pTexturebg3 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffbg3 =NULL;	//���_�p�b�t�@�ւ̃|�C���^
bool bSwitch;
//=============================================================================
//  �֐����@�FInitbg3
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT Initbg3(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffbg3,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *bg3;
		g_pVtxBuffbg3 ->Lock(0,0,(void **)&bg3,0);		//���_���ւ̃|�C���^���擾
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\bg003.png",
		&g_pTexturebg3);
		bUsebg3 = true;
		bg3[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		bg3[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
		bg3[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		bg3[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		bg3[0].rhw = 1.0f;
		bg3[1].rhw = 1.0f;
		bg3[2].rhw = 1.0f;
		bg3[3].rhw = 1.0f;
		bg3[0].col=D3DCOLOR_RGBA(200,200,200,255);	//���_���i�[���[�N
		bg3[1].col=D3DCOLOR_RGBA(200,200,200,255);
		bg3[2].col=D3DCOLOR_RGBA(200,200,200,255);
		bg3[3].col=D3DCOLOR_RGBA(200,200,200,255);

		bg3[0].tex = D3DXVECTOR2(0.0f,0.0f);
		bg3[1].tex = D3DXVECTOR2(1.0f,0.0f);
		bg3[2].tex = D3DXVECTOR2(0.0f,1.0f);
		bg3[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffbg3 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitbg3
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void Uninitbg3(void)
{
	if(g_pTexturebg3!=NULL)
	{
		g_pTexturebg3->Release();
		g_pTexturebg3=NULL;
	}
	if(g_pVtxBuffbg3!=NULL)
	{
		g_pVtxBuffbg3->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffbg3=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawbg3
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void Drawbg3(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTexturebg3);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffbg3,
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
//  �֐����@�FUpdatebg31
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void Updatebg3(void)
{



}
