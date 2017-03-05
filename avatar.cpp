#include "main.h"
#include "avatar.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureAvatar =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffAvatar =NULL;	//���_�p�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posAvatar;	//�|���S���̈ʒu
D3DXVECTOR3 g_rotAvatar;		//�|���S���̉�]�p
D3DXVECTOR3 g_moveAvatar;		//�|���S���̈ړ���
int g_nCounterAnim_Avatar;		//�A�����[�V�����J�E���^
int g_nPatternAnim_Avatar;		//�A�����[�V�����p�^�[��NO
float animRow_Avatar =1.0f;
float maxAnimX_Avatar = 3.0f;
float maxAnimY_Avatar = 1.0f;
float AvatarWidth = 240.0f;		//�|���S���̕�
float AvatarHeight =50.0f;		//�|���S���̍���
float g_fLengthAvatar;		//�|���S���̑Ίp���̒���
float g_fAngleAvatar;		//�|���S���̑Ίp���̊p�x
float startAnimY_Avatar = 0.0f;
AVATAR g_Avatarstate =AVATAR_MAN;
//=============================================================================
//  �֐����@�FInitAvatar
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitAvatar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffAvatar,NULL)))
	{
		return E_FAIL;
	}
		VERTEX_2D *pVtx;
		g_pVtxBuffAvatar ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾
		//�e�N�X�`���̓ǂݍ���	
		D3DXCreateTextureFromFile(
			pDevice,
			".\\data\\TEXTURE\\avatar.png",
		&g_pTextureAvatar);
		bUseAvatar = false;
			//����������
		g_posAvatar.x = 80.0f;
		g_posAvatar.y = 700.0f;
		g_posAvatar = D3DXVECTOR3(g_posAvatar.x,g_posAvatar.y,0.0f);

			//��]����������
		g_rotAvatar = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_fLengthAvatar =sqrtf(AvatarWidth * AvatarWidth + AvatarHeight * AvatarHeight)*0.5f;
		g_fAngleAvatar =atan2f(AvatarWidth,AvatarHeight)*0.5f;


		//���_���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3 (g_posAvatar.x - sinf( g_fAngleAvatar + g_rotAvatar.z ) * g_fLengthAvatar,
								   g_posAvatar.y - cosf( g_fAngleAvatar + g_rotAvatar.z ) * g_fLengthAvatar,
								   0.0f);

		pVtx[1].pos = D3DXVECTOR3 (g_posAvatar.x + sinf( g_fAngleAvatar - g_rotAvatar.z ) * g_fLengthAvatar,
								   g_posAvatar.y - cosf( g_fAngleAvatar - g_rotAvatar.z ) * g_fLengthAvatar,
								   0.0f);

		pVtx[2].pos = D3DXVECTOR3 (g_posAvatar.x - sinf( g_fAngleAvatar - g_rotAvatar.z ) * g_fLengthAvatar,
								   g_posAvatar.y + cosf( g_fAngleAvatar - g_rotAvatar.z ) * g_fLengthAvatar,
								   0.0f);

		pVtx[3].pos = D3DXVECTOR3 (g_posAvatar.x + sinf( g_fAngleAvatar + g_rotAvatar.z ) * g_fLengthAvatar,
								   g_posAvatar.y + cosf( g_fAngleAvatar + g_rotAvatar.z ) * g_fLengthAvatar,
								   0.0f);
		//UV�ݒ�
		switch(g_Avatarstate)
		{
		case AVATAR_MAN:
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(1.0f / maxAnimX_Avatar,0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f / maxAnimY_Avatar);
			pVtx[3].tex = D3DXVECTOR2(1.0f / maxAnimX_Avatar, 1.0f / maxAnimY_Avatar);
			break;

		case AVATAR_BOSS1:
			pVtx[0].tex = D3DXVECTOR2(1.0f / maxAnimX_Avatar, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(2.0f / maxAnimX_Avatar,0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f / maxAnimX_Avatar, 1.0f / maxAnimY_Avatar);
			pVtx[3].tex = D3DXVECTOR2(2.0f / maxAnimX_Avatar, 1.0f / maxAnimY_Avatar);
			break;

		case AVATAR_BOSS2:
			pVtx[0].tex = D3DXVECTOR2(2.0f / maxAnimX_Avatar, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(3.0f / maxAnimX_Avatar,0.0f);
			pVtx[2].tex = D3DXVECTOR2(2.0f / maxAnimX_Avatar, 1.0f / maxAnimY_Avatar);
			pVtx[3].tex = D3DXVECTOR2(3.0f / maxAnimX_Avatar, 1.0f / maxAnimY_Avatar);
			break;
		}
		//���W�ϊ�	
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
			
		//���_�F�ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 128);	//���_���i�[���[�N
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 128);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 128);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 128);

		g_pVtxBuffAvatar ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitAvatar
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitAvatar(void)
{

	if(g_pVtxBuffAvatar!=NULL)
	{
		g_pVtxBuffAvatar->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffAvatar=NULL;
	}
	if(g_pTextureAvatar!=NULL)
	{
		g_pTextureAvatar->Release();
		g_pTextureAvatar=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawAvatar
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawAvatar(void)
{
	if(bUseAvatar == true)
	{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureAvatar);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffAvatar,
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

}
//=============================================================================
//  �֐����@�FUpdateAvatar
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateAvatar(void)
{
	if(bUseAvatar == true)
	{
	}
}