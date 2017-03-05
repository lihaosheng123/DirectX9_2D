#include "main.h"
#include "result.h"
#include "input.h"
#include "sound.h"
//�O���[�o���ϐ�
VERTEX_2D g_result[4];
LPDIRECT3DTEXTURE9 g_pTextureresult =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffresult =NULL;	//���_�p�b�t�@�ւ̃|�C���^
//=============================================================================
//  �֐����@�FInitresult
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitResult(void)
{
	PlaySound(SOUND_LABEL_BGM002);
	StopSound(SOUND_LABEL_BGM001);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffresult,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *result;
		g_pVtxBuffresult ->Lock(0,0,(void **)&result,0);		//���_���ւ̃|�C���^���擾
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\result.png",
		&g_pTextureresult);
		result[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		result[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
		result[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		result[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		result[0].rhw = 1.0f;
		result[1].rhw = 1.0f;
		result[2].rhw = 1.0f;
		result[3].rhw = 1.0f;
		result[0].col=D3DCOLOR_RGBA(200,200,200,255);	//���_���i�[���[�N
		result[1].col=D3DCOLOR_RGBA(200,200,200,255);
		result[2].col=D3DCOLOR_RGBA(200,200,200,255);
		result[3].col=D3DCOLOR_RGBA(200,200,200,255);

		result[0].tex = D3DXVECTOR2(0.0f,0.0f);
		result[1].tex = D3DXVECTOR2(1.0f,0.0f);
		result[2].tex = D3DXVECTOR2(0.0f,1.0f);
		result[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffresult ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitresult
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitResult(void)
{
	if(g_pTextureresult!=NULL)
	{
		g_pTextureresult->Release();
		g_pTextureresult=NULL;
	}
	if(g_pVtxBuffresult!=NULL)
	{
		g_pVtxBuffresult->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffresult=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawresult
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureresult);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffresult,
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
//  �֐����@�FUpdateresult
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateResult(void)
{
	MODE mode;
	mode = GetMode();
	//if(GetKeyboardTrigger(DIK_RETURN) == true)
	//{
	//	mode = MODE_TITLE;
	//	SetMode(mode);
	//}


}
