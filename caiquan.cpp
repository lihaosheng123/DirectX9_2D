#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "caiquan.h"
#include "score.h"
#include "input.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureCaiquan =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCaiquan =NULL;	//���_�p�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posCaiquan;	//�|���S���̈ʒu
D3DXVECTOR3 g_rotCaiquan;		//�|���S���̉�]�p
D3DXVECTOR3 g_moveCaiquan;		//�|���S���̈ړ���
int g_nCounterAnim_Caiquan;		//�A�����[�V�����J�E���^
int g_nPatternAnim_Caiquan;		//�A�����[�V�����p�^�[��NO
float animRow_Caiquan =1.0f;
float maxAnimX_Caiquan = 3.0f;
float maxAnimY_Caiquan = 1.0f;
float CaiquanWidth = 100.0f;		//�|���S���̕�
float CaiquanHeight = 150.0f;
float Caiquan_X = 700.0f;
float Caiquan_Y = 100.0f;
float g_fLengthCaiquan;		//�|���S���̑Ίp���̒���
float g_fAngleCaiquan;		//�|���S���̑Ίp���̊p�x
float runSpeed_Caiquan =10.0f;
float animMaxnum_Caiquan = 3;
float startAnimY_Caiquan = 0;
int cnt_enemy ;
//=============================================================================
//  �֐����@�FInitCaiquan
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitCaiquan(void)
{
	srand ((unsigned)time(NULL));
	cnt_polygon = 0;
	cnt_enemy = 1+rand() % 3;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffCaiquan,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *Caiquan;
		g_pVtxBuffCaiquan ->Lock(0,0,(void **)&Caiquan,0);		//���_���ւ̃|�C���^���擾
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\caiquan.png",
		&g_pTextureCaiquan);

		//bUseCaiquan = true;
		Caiquan[0].pos = D3DXVECTOR3(Caiquan_X,Caiquan_Y,0.0f);
		Caiquan[1].pos = D3DXVECTOR3(Caiquan_X+CaiquanWidth,Caiquan_Y,0.0f);
		Caiquan[2].pos = D3DXVECTOR3(Caiquan_X,Caiquan_Y+CaiquanHeight,0.0f);
		Caiquan[3].pos = D3DXVECTOR3(Caiquan_X+CaiquanWidth,Caiquan_Y+CaiquanHeight,0.0f);
		Caiquan[0].rhw = 1.0f;
		Caiquan[1].rhw = 1.0f;
		Caiquan[2].rhw = 1.0f;
		Caiquan[3].rhw = 1.0f;
		Caiquan[0].col=D3DCOLOR_RGBA(200,200,200,255);	//���_���i�[���[�N
		Caiquan[1].col=D3DCOLOR_RGBA(200,200,200,255);
		Caiquan[2].col=D3DCOLOR_RGBA(200,200,200,255);
		Caiquan[3].col=D3DCOLOR_RGBA(200,200,200,255);

		Caiquan[0].tex = D3DXVECTOR2(0.0f, 0.0f );
		Caiquan[1].tex = D3DXVECTOR2(1.0f / maxAnimX_Caiquan,0.0f);
		Caiquan[2].tex = D3DXVECTOR2(0.0f, 1.0f / maxAnimY_Caiquan);
		Caiquan[3].tex = D3DXVECTOR2(1.0f / maxAnimX_Caiquan, 1.0f / maxAnimY_Caiquan);
		g_pVtxBuffCaiquan ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitCaiquan
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitCaiquan(void)
{
	if(g_pTextureCaiquan!=NULL)
	{
		g_pTextureCaiquan->Release();
		g_pTextureCaiquan=NULL;
	}
	if(g_pVtxBuffCaiquan!=NULL)
	{
		g_pVtxBuffCaiquan->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffCaiquan=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawCaiquan
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawCaiquan(void)
{
	/*if(bUseCaiquan == true)
	{*/
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureCaiquan);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffCaiquan,
								0,
								sizeof(VERTEX_2D)
								);

	// �t�F�[�h�̕`��ݒ���e
	pDevice -> DrawPrimitive(
							  D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
							  0,		// �ŏ��̒��_�̃C���f�b�N�X
							  2			// �`�悷��v���~�e�B�u��
							);
	/*}*/
	
}
//=============================================================================
//  �֐����@�FUpdateCaiquan1
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateCaiquan(void)
{
	g_nCounterAnim_Caiquan++;
		if(g_nCounterAnim_Caiquan == runSpeed_Caiquan )
		{
			g_nCounterAnim_Caiquan = 0;
			g_nPatternAnim_Caiquan ++;
			if(g_nPatternAnim_Caiquan == animMaxnum_Caiquan)	//�p�^�[����
			{
				startAnimY_Caiquan = 0;//��ʏ�
				animRow_Caiquan = 1;
				g_nPatternAnim_Caiquan = 0;
			}
			else if(g_nPatternAnim_Caiquan == 5)
			{
				animRow_Caiquan++;
				startAnimY_Caiquan += (1.0f / maxAnimY_Caiquan);
			}
			VERTEX_2D *Caiquan;
			g_pVtxBuffCaiquan ->Lock(0,0,(void **)&Caiquan,0);		//���_���ւ̃|�C���^���擾
		Caiquan[0].pos = D3DXVECTOR3(Caiquan_X,Caiquan_Y,0.0f);
		Caiquan[1].pos = D3DXVECTOR3(Caiquan_X+CaiquanWidth,Caiquan_Y,0.0f);
		Caiquan[2].pos = D3DXVECTOR3(Caiquan_X,Caiquan_Y+CaiquanHeight,0.0f);
		Caiquan[3].pos = D3DXVECTOR3(Caiquan_X+CaiquanWidth,Caiquan_Y+CaiquanHeight,0.0f);

			Caiquan[0].tex.x = g_nPatternAnim_Caiquan *(1.0f / maxAnimX_Caiquan);
			Caiquan[0].tex.y = startAnimY_Caiquan;

			Caiquan[1].tex.x = (g_nPatternAnim_Caiquan * (1.0f /  maxAnimX_Caiquan)) + (1.0f / maxAnimX_Caiquan);
			Caiquan[1].tex.y = startAnimY_Caiquan;
				
			Caiquan[2].tex.x = g_nPatternAnim_Caiquan * (1.0f /  maxAnimX_Caiquan);
			Caiquan[2].tex.y = animRow_Caiquan *(1.0f / maxAnimY_Caiquan);

			Caiquan[3].tex.x = (g_nPatternAnim_Caiquan * (1.0f /  maxAnimX_Caiquan)) + (1.0f / maxAnimX_Caiquan);
			Caiquan[3].tex.y = animRow_Caiquan *(1.0f / maxAnimY_Caiquan);
	g_pVtxBuffCaiquan ->Unlock();	//LOCK
		}
}
//if(GetKeyboardTrigger(DIK_E))
//{
//	switch(cnt_enemy)
//	{
//	case 0:
//		switch(cnt_polygon)
//		{
//			case 0:		//����
//			AddScore(0);
//				break;
//
//			case 1:		//����
//				AddScore(10);
//				break;
//
//			case 2:		//����
//				AddScore(100);
//				break;
//
//		}
//		break;
//
//	case 1:
//		switch(cnt_polygon)
//		{
//			case 0:		//����
//				AddScore(100);
//				break;
//
//			case 1:		//����
//				AddScore(0);
//				break;
//
//			case 2:		//����
//				AddScore(10);
//				break;
//
//		}
//		break;
//
//	case 2:
//		switch(cnt_polygon)
//		{
//			case 0:		//����
//				AddScore(10);
//				break;
//
//			case 1:		//����
//				AddScore(100);
//				break;
//
//			case 2:		//����
//				AddScore(0);
//				break;
//
//		}
//		break;
//	}
//}

