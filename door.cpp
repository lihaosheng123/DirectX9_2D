#include "main.h"
#include "door.h"
#include "polygon.h"
#include "input.h"
//�O���[�o���ϐ�
VERTEX_2D g_Door[4];
LPDIRECT3DTEXTURE9 g_pTextureDoor =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffDoor =NULL;	//���_�p�b�t�@�ւ̃|�C���^
float maxAnimX_Door = 2.0f;
float maxAnimY_Door = 1.0f;
float startAnimY_Door = 0.0f;
float DoorHeight_Door1;
float DoorWidth_Door1;
float DoorCoordX_Door1;
float DoorCoordY_Door1;
bool bUse_Door1;
void DrawDoor1(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureDoor);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffDoor,
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


HRESULT InitDoor1 (void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*(4*Door_MAX),D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffDoor,NULL)))
	{
		return E_FAIL;
	}
	VERTEX_2D *pVtx;
		g_pVtxBuffDoor ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(
			pDevice,
			".\\data\\TEXTURE\\door.png",
		&g_pTextureDoor);

		DoorHeight_Door1 = 170.0f;
		DoorWidth_Door1 = 80.0f;
		DoorCoordX_Door1 = 1040.0f;
		DoorCoordY_Door1 =260.0f;
		bUse_Door1 = true;

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f );
		pVtx[1].tex = D3DXVECTOR2(0.5f,0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

		pVtx[0].pos = D3DXVECTOR3( DoorCoordX_Door1+DoorWidth_Door1, DoorCoordY_Door1, 0.0f);
		pVtx[1].pos = D3DXVECTOR3( DoorCoordX_Door1 + DoorWidth_Door1+DoorWidth_Door1, DoorCoordY_Door1, 0.0f);
		pVtx[2].pos = D3DXVECTOR3( DoorCoordX_Door1+DoorWidth_Door1 ,DoorCoordY_Door1 + DoorHeight_Door1, 0.0f);
		pVtx[3].pos = D3DXVECTOR3( DoorCoordX_Door1 + DoorWidth_Door1+DoorWidth_Door1,DoorCoordY_Door1 + DoorHeight_Door1, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 127);	//���_���i�[���[�N
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 127);

	g_pVtxBuffDoor ->Unlock();	//LOCK
	return S_OK;
}

void UpdateDoor1 (void)
{

	VERTEX_2D *pVtx;
	g_pVtxBuffDoor ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾
	pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f );
	pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	g_pVtxBuffDoor ->Unlock();	//LOCK
}
void UninitDoor1(void)
{

	if(g_pVtxBuffDoor!=NULL)
	{
		g_pVtxBuffDoor->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffDoor=NULL;
	}
	if(g_pTextureDoor!=NULL)
	{
		g_pTextureDoor->Release();
		g_pTextureDoor=NULL;
	}
}
