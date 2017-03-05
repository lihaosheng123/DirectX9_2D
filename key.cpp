#include "main.h"
#include "key.h"
#include "input.h"
//�O���[�o���ϐ�
KEY g_aKey[MAX_KEY];
LPDIRECT3DTEXTURE9 g_pTextureKey =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffKey =NULL;	//���_�p�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posKey;	//�|���S���̈ʒu
D3DXVECTOR3 g_rotKey;		//�|���S���̉�]�p
D3DXVECTOR3 g_moveKey;		//�|���S���̈ړ���
int g_nCounterAnim_Key;		//�A�����[�V�����J�E���^
int g_nPatternAnim_Key;		//�A�����[�V�����p�^�[��NO
float animRow_Key =1.0f;
float maxAnimX_Key = 2.0f;
float maxAnimY_Key = 1.0f;
float g_fLengthKey;		//�|���S���̑Ίp���̒���
float g_fAngleKey;		//�|���S���̑Ίp���̊p�x
float move_Key = 3.0f;		//�ړ���
float runSpeed_Key = 5.0f;
int animMaxnum_Key = 2;
float startAnimY_Key = 0.0f;

//=============================================================================
//  �֐����@�FInitKey
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitKey(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffKey,NULL)))
	{
		return E_FAIL;
	}
		VERTEX_2D *pVtx;
		g_pVtxBuffKey ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾
		//�e�N�X�`���̓ǂݍ���	
		D3DXCreateTextureFromFile(
			pDevice,
			".\\data\\TEXTURE\\key.png",
		&g_pTextureKey);

		bKey = false;
		
		g_aKey[0].fHeight=2.0f;
		g_aKey[0].fWidth=80.0f;
			//����������
		g_aKey[0].pos.x = 960.0f;
		g_aKey[0].pos.y = 670.0f;
		g_posKey = D3DXVECTOR3(g_aKey[0].pos.x,g_aKey[0].pos.y,0.0f);
		
			//��]����������
		g_rotKey = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_fLengthKey =sqrtf(g_aKey[0].fWidth * g_aKey[0].fWidth + g_aKey[0].fHeight * g_aKey[0].fHeight)*0.5f;
		g_fAngleKey =atan2f(g_aKey[0].fWidth,g_aKey[0].fHeight)*0.5f;


		
		//���_���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3 (g_aKey[0].pos.x - sinf( g_fAngleKey + g_rotKey.z ) * g_fLengthKey,
								   g_aKey[0].pos.y - cosf( g_fAngleKey + g_rotKey.z ) * g_fLengthKey,
								   0.0f);

		pVtx[1].pos = D3DXVECTOR3 (g_aKey[0].pos.x + sinf( g_fAngleKey - g_rotKey.z ) * g_fLengthKey,
								   g_aKey[0].pos.y - cosf( g_fAngleKey - g_rotKey.z ) * g_fLengthKey,
								   0.0f);

		pVtx[2].pos = D3DXVECTOR3 (g_aKey[0].pos.x - sinf( g_fAngleKey - g_rotKey.z ) * g_fLengthKey,
								   g_aKey[0].pos.y + cosf( g_fAngleKey - g_rotKey.z ) * g_fLengthKey,
								   0.0f);

		pVtx[3].pos = D3DXVECTOR3 (g_aKey[0].pos.x + sinf( g_fAngleKey + g_rotKey.z ) * g_fLengthKey,
								   g_aKey[0].pos.y + cosf( g_fAngleKey + g_rotKey.z ) * g_fLengthKey,
								   0.0f);

			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(1.0f / maxAnimX_Key,0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f / maxAnimY_Key);
			pVtx[3].tex = D3DXVECTOR2(1.0f / maxAnimX_Key, 1.0f / maxAnimY_Key);

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
		
		g_pVtxBuffKey ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitKey
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitKey(void)
{

	if(g_pVtxBuffKey!=NULL)
	{
		g_pVtxBuffKey->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffKey=NULL;
	}
	if(g_pTextureKey!=NULL)
	{
		g_pTextureKey->Release();
		g_pTextureKey=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawKey
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawKey(void)
{
	if(bKey == false)
	{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureKey);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffKey,
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
//  �֐����@�FUpdateKey
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateKey(void)
{
	g_nCounterAnim_Key++;
		if(g_nCounterAnim_Key == runSpeed_Key )
		{
			g_nCounterAnim_Key = 0;
			g_nPatternAnim_Key ++;
			if(g_nPatternAnim_Key == animMaxnum_Key)	//�p�^�[����
			{
				startAnimY_Key = 0;//��ʏ�
				animRow_Key = 1;
				g_nPatternAnim_Key = 0;
			}
			else if(g_nPatternAnim_Key == 5)
			{
				animRow_Key++;
				startAnimY_Key += (1.0f / maxAnimY_Key);
			}
			VERTEX_2D *pVtx;
			g_pVtxBuffKey ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾
			pVtx[0].tex.x = g_nPatternAnim_Key *(1.0f / maxAnimX_Key);
			pVtx[0].tex.y = startAnimY_Key;

			pVtx[1].tex.x = (g_nPatternAnim_Key * (1.0f /  maxAnimX_Key)) + (1.0f / maxAnimX_Key);
			pVtx[1].tex.y = startAnimY_Key;
				
			pVtx[2].tex.x = g_nPatternAnim_Key * (1.0f /  maxAnimX_Key);
			pVtx[2].tex.y = animRow_Key *(1.0f / maxAnimY_Key);

			pVtx[3].tex.x = (g_nPatternAnim_Key * (1.0f /  maxAnimX_Key)) + (1.0f / maxAnimX_Key);
			pVtx[3].tex.y = animRow_Key *(1.0f / maxAnimY_Key);
		}
		g_pVtxBuffKey ->Unlock();	//LOCK
}


