#include "main.h"
#include "press.h"
#include "input.h"
#include "fade.h"
//�O���[�o���ϐ�
VERTEX_2D g_Press[4];
LPDIRECT3DTEXTURE9 g_pTexturePress =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPress =NULL;	//���_�p�b�t�@�ւ̃|�C���^
float widthPress = 500.0f;
float heightPress = 100.0f;
float PressCoordX = 400.0f;
float PressCoordY = 0.0f;
bool bUse = false;
float maxAnimX_Press = 1.0f;
float maxAnimY_Press = 2.0f;
float runSpeed_Press = 4.0f;
int animMaxnum_Press = 4;
float startAnimY_Press = 0.0f;
int g_nCounterAnim_Press;		//�A�����[�V�����J�E���^
int g_nPatternAnim_Press;		//�A�����[�V�����p�^�[��NO
float animRow_Press =1.0f;
//=============================================================================
//  �֐����@�FInitPress
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitPress(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffPress,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *Press;
		g_pVtxBuffPress ->Lock(0,0,(void **)&Press,0);		//���_���ւ̃|�C���^���擾
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\press.png",
		&g_pTexturePress);
		Press[0].pos = D3DXVECTOR3(PressCoordX,PressCoordY,0.0f);
		Press[1].pos = D3DXVECTOR3((PressCoordX+widthPress),PressCoordY,0.0f);
		Press[2].pos = D3DXVECTOR3(PressCoordX,(PressCoordY+heightPress),0.0f);
		Press[3].pos = D3DXVECTOR3((PressCoordX+widthPress),(PressCoordY+heightPress),0.0f);
		Press[0].rhw = 1.0f;
		Press[1].rhw = 1.0f;
		Press[2].rhw = 1.0f;
		Press[3].rhw = 1.0f;
		//���_�F�ݒ�
		Press[0].col = D3DCOLOR_RGBA(255, 255, 255, 128);	//���_���i�[���[�N
		Press[1].col = D3DCOLOR_RGBA(255, 255, 255, 128);
		Press[2].col = D3DCOLOR_RGBA(255, 255, 255, 128);
		Press[3].col = D3DCOLOR_RGBA(255, 255, 255, 128);

		Press[0].tex = D3DXVECTOR2(0.0f,0.0f);
		Press[1].tex = D3DXVECTOR2(1.0f,0.0f);
		Press[2].tex = D3DXVECTOR2(0.0f,0.5f);
		Press[3].tex = D3DXVECTOR2(1.0f,0.5f);
		g_pVtxBuffPress ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitPress
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitPress(void)
{
	if(g_pTexturePress!=NULL)
	{
		g_pTexturePress->Release();
		g_pTexturePress=NULL;
	}
	if(g_pVtxBuffPress!=NULL)
	{
		g_pVtxBuffPress->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffPress=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawPress
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawPress(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTexturePress);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffPress,
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
//  �֐����@�FUpdatePress1
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdatePress(void)
{
	PressCoordY++;
	if(PressCoordY >= 500.0f ||GetKeyboardPress(DIK_RETURN) == true  )
	{
		PressCoordY = 500.0f;
	}
	//if(PressCoordY == 500.0f && GetKeyboardPress(DIK_RETURN) == true )		//��ʑJ��
	//{
	g_nCounterAnim_Press++;
		if(g_nCounterAnim_Press == runSpeed_Press )
		{
			g_nCounterAnim_Press = 0;
			g_nPatternAnim_Press ++;
			if(g_nPatternAnim_Press == animMaxnum_Press)	//�p�^�[����
			{
				startAnimY_Press = 0;//��ʏ�
				animRow_Press = 1;
				g_nPatternAnim_Press = 0;
			}
			else if(g_nPatternAnim_Press == 1)
			{
				animRow_Press++;
				startAnimY_Press += (1.0f / maxAnimY_Press);
			}
	if(PressCoordY == 500.0f && GetKeyboardPress(DIK_RETURN) == true )		//��ʑJ��
	{
		SetFade(FADE_OUT,MODE_JIESHAO);
		}
	}
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *Press;
	g_pVtxBuffPress ->Lock(0,0,(void **)&Press,0);		//���_���ւ̃|�C���^���擾
	Press[0].tex.x = g_nPatternAnim_Press *(1.0f / maxAnimX_Press);
	Press[0].tex.y = startAnimY_Press;

	Press[1].tex.x = (g_nPatternAnim_Press * (1.0f /  maxAnimX_Press)) + (1.0f / maxAnimX_Press);
	Press[1].tex.y = startAnimY_Press;
				
	Press[2].tex.x = g_nPatternAnim_Press * (1.0f /  maxAnimX_Press);
	Press[2].tex.y = animRow_Press *(1.0f / maxAnimY_Press);

	Press[3].tex.x = (g_nPatternAnim_Press * (1.0f /  maxAnimX_Press)) + (1.0f / maxAnimX_Press);
	Press[3].tex.y = animRow_Press *(1.0f / maxAnimY_Press);
	Press[0].pos = D3DXVECTOR3(PressCoordX,PressCoordY,0.0f);
	Press[1].pos = D3DXVECTOR3((PressCoordX+widthPress),PressCoordY,0.0f);
	Press[2].pos = D3DXVECTOR3(PressCoordX,(PressCoordY+heightPress),0.0f);
	Press[3].pos = D3DXVECTOR3((PressCoordX+widthPress),(PressCoordY+heightPress),0.0f);

	g_pVtxBuffPress ->Unlock();	//LOCK
	
}