#include "main.h"
#include "polygon.h"
#include "input.h"
#include "bullet.h"
#include "door.h"
#include "fade.h"
#include "talk.h"
#include "avatar.h"
#include "score.h"
#include "explosion.h"
#include "prop.h"
#include "prop2.h"
#include "talk1.h"
#include "talk2.h"
#include "bg2.h"
#include "talk3.h"
#include "talk4.h"
#include "effect.h"
#include "pause.h"
//�O���[�o���ϐ�
POLYGON g_aPolygon;
VERTEX_2D g_aVertex[4];
LPDIRECT3DTEXTURE9 g_pTexturePolygon =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon =NULL;	//���_�p�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posPolygon;	//�|���S���̈ʒu
D3DXVECTOR3 g_rotPolygon;		//�|���S���̉�]�p
D3DXVECTOR3 g_movePolygon;		//�|���S���̈ړ���
int g_nCounterAnim_Polygon;		//�A�����[�V�����J�E���^
int g_nPatternAnim_Polygon;		//�A�����[�V�����p�^�[��NO
float animRow_Polygon =1.0f;
float maxAnimX_Polygon = 4.0f;
float maxAnimY_Polygon = 1.0f;
float g_fLengthPolygon;		//�|���S���̑Ίp���̒���
float g_fAnglePolygon;		//�|���S���̑Ίp���̊p�x
float move_Polygon = 7.0f;		//�ړ���
float spinmove =0.1f;		//��]��
float runSpeed_Polygon = 3.0f;
int animMaxnum_Polygon = 4;
float startAnimY_Polygon = 0.0f;
int cnt_polygon ;
bool bProp;
bool bProp2 ;
bool bUseEnemy2;
bool bUseTalk ;
bool bUseAvatar ;
bool bKey;
bool bPropUpdate;
bool bPropUpdate2;
bool bUsebg3;
bool bUseTalk1 ;
bool bUseTalk2 ;
bool bUseTalk3 ;
bool bUseTalk4 ;
bool bUseTalk5 ;
bool bUseTalk6 ;
bool bUseTalk7 ;
bool bUseTalk8;
bool bUseTalk9;
bool jieshaobUse;
MODE g_map = MODE_GAME1;

//=============================================================================
//  �֐����@�FInitPolygon
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffPolygon,NULL)))
	{
		return E_FAIL;
	}
		VERTEX_2D *pVtx;
		g_pVtxBuffPolygon ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾
		//�e�N�X�`���̓ǂݍ���	
		D3DXCreateTextureFromFile(
			pDevice,
			".\\data\\TEXTURE\\002.png",
		&g_pTexturePolygon);
			//����������
		g_aPolygon.fWidth = 120.0f;		//�|���S���̕�
		g_aPolygon.fHeight =120.0f;		//�|���S���̍���
		g_aPolygon.pos.x = 50.0f;
		g_aPolygon.pos.y = 500.0f;
		g_posPolygon = D3DXVECTOR3(g_aPolygon.pos.x,g_aPolygon.pos.y,0.0f);
		g_aPolygon.bUse= true;
		g_aPolygon.bDoorUse=true;
		g_aPolygon.nLife = 4;
			//��]����������
		g_rotPolygon = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_fLengthPolygon =sqrtf(g_aPolygon.fWidth * g_aPolygon.fWidth + g_aPolygon.fHeight * g_aPolygon.fHeight)*0.5f;
		g_fAnglePolygon =atan2f(g_aPolygon.fWidth,g_aPolygon.fHeight)*0.5f;

		//���_���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3 (g_aPolygon.pos.x - sinf( g_fAnglePolygon + g_rotPolygon.z ) * g_fLengthPolygon,
								   g_aPolygon.pos.y - cosf( g_fAnglePolygon + g_rotPolygon.z ) * g_fLengthPolygon,
								   0.0f);

		pVtx[1].pos = D3DXVECTOR3 (g_aPolygon.pos.x + sinf( g_fAnglePolygon - g_rotPolygon.z ) * g_fLengthPolygon,
								   g_aPolygon.pos.y - cosf( g_fAnglePolygon - g_rotPolygon.z ) * g_fLengthPolygon,
								   0.0f);

		pVtx[2].pos = D3DXVECTOR3 (g_aPolygon.pos.x - sinf( g_fAnglePolygon - g_rotPolygon.z ) * g_fLengthPolygon,
								   g_aPolygon.pos.y + cosf( g_fAnglePolygon - g_rotPolygon.z ) * g_fLengthPolygon,
								   0.0f);

		pVtx[3].pos = D3DXVECTOR3 (g_aPolygon.pos.x + sinf( g_fAnglePolygon + g_rotPolygon.z ) * g_fLengthPolygon,
								   g_aPolygon.pos.y + cosf( g_fAnglePolygon + g_rotPolygon.z ) * g_fLengthPolygon,
								   0.0f);

		//UV�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f );
		pVtx[1].tex = D3DXVECTOR2(1.0f / maxAnimX_Polygon,0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f / maxAnimY_Polygon);
		pVtx[3].tex = D3DXVECTOR2(1.0f / maxAnimX_Polygon, 1.0f / maxAnimY_Polygon);

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
	
		g_pVtxBuffPolygon ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitPolygon
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitPolygon(void)
{

	if(g_pVtxBuffPolygon!=NULL)
	{
		g_pVtxBuffPolygon->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffPolygon=NULL;
	}
	if(g_pTexturePolygon!=NULL)
	{
		g_pTexturePolygon->Release();
		g_pTexturePolygon=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawPolygon
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTexturePolygon);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffPolygon,
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
//  �֐����@�FUpdatePolygon
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdatePolygon(void)
{
	PAUSEUSE *bUseCheck = GetPause();
	if(bUseCheck->bUse == false)
	{
	MapPolygon();
//	SetEffect(D3DXVECTOR3(g_aPolygon.pos.x,g_aPolygon.pos.y,0.0f), D3DXCOLOR(120.0f, 100.0f, 50.0f, 1.0f), 30.0f, 80, EFFECTTYPE_RANDOMCOLOR);
	if(GetKeyboardTrigger(DIK_J) )
	{
		/* �e���� */
		SetBullet(D3DXVECTOR3(g_aPolygon.pos.x,g_aPolygon.pos.y,0.0f),D3DXVECTOR3(10.0f,0.0f,0.0f),1);
	}
	if(GetKeyboardPress(DIK_W) || GetKeyboardPress(DIK_A) || GetKeyboardPress(DIK_S) || GetKeyboardPress(DIK_D))
	{
	g_nCounterAnim_Polygon++;
		if(g_nCounterAnim_Polygon == runSpeed_Polygon )
		{
			g_nCounterAnim_Polygon = 0;
			g_nPatternAnim_Polygon ++;
			if(g_nPatternAnim_Polygon == animMaxnum_Polygon)	//�p�^�[����
			{
				startAnimY_Polygon = 0;//��ʏ�
				animRow_Polygon = 1;
				g_nPatternAnim_Polygon = 0;
			}
			else if(g_nPatternAnim_Polygon == 5)
			{
				animRow_Polygon++;
				startAnimY_Polygon += (1.0f / maxAnimY_Polygon);
			}
			VERTEX_2D *pVtx;
			g_pVtxBuffPolygon ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾

			if(GetKeyboardPress(DIK_W) == true)		//��ړ�
			{
			g_aPolygon.pos.y -= move_Polygon;
			if(GetKeyboardPress(DIK_A) == true)		//�㍶�ړ�
			{
				g_aPolygon.pos.x -= sinf(-D3DX_PI*(3/4) *move_Polygon);
				g_aPolygon.pos.y -= cosf(-D3DX_PI*(3/4) *move_Polygon);
			}
			else if(GetKeyboardPress(DIK_D) == true)		//��E�ړ�
			{
				g_aPolygon.pos.x += sinf(D3DX_PI*(3/4) *move_Polygon);
				g_aPolygon.pos.y -= cosf(D3DX_PI*(3/4) *move_Polygon);
			}
		}
		else if(GetKeyboardPress(DIK_S) == true)		//���ړ�
		{
			g_aPolygon.pos.y += move_Polygon;
			if(GetKeyboardPress(DIK_A) == true)		//�����ړ�
			{
				g_aPolygon.pos.x -= sinf(-D3DX_PI*(1/4) *move_Polygon);
				g_aPolygon.pos.y += cosf(-D3DX_PI*(1/4) *move_Polygon);
			}
			else if(GetKeyboardPress(DIK_D) == true)		//���E�ړ�
			{
				g_aPolygon.pos.x += sinf(D3DX_PI*(1/4) *move_Polygon);
				g_aPolygon.pos.y -= cosf(D3DX_PI*(1/4) *move_Polygon);
			}
		}


		if(GetKeyboardPress(DIK_A)== true)		//���ړ�
		{
			g_aPolygon.pos.x -= move_Polygon;
		}
		if(GetKeyboardPress(DIK_D) == true)		//�E�ړ�
		{
			g_aPolygon.pos.x += move_Polygon;
		}

	//if(GetKeyboardTrigger(DIK_UP) == true)		//�g��
	//{
	//	g_fLengthPolygon += move;
	//}


	//if(GetKeyboardTrigger(DIK_DOWN) == true)		//�k��
	//{
	//	g_fLengthPolygon -= move;
	//}

	//if(GetKeyboardPress(DIK_LEFT) == true)		//����]
	//{
	//	g_rotPolygon.z +=spinmove ;
	//}

	//if(GetKeyboardPress(DIK_RIGHT) == true)		//�E��]
	//{
	//	g_rotPolygon.z -=spinmove ;
	//}

		if((g_aPolygon.pos.x-g_aPolygon.fWidth/5) <= 0)
		{
			g_aPolygon.pos.x = (g_aPolygon.fWidth/5);
		}
	
		if((g_aPolygon.pos.x+g_aPolygon.fWidth/3)>= SCREEN_WIDTH)
		{
			g_aPolygon.pos.x = SCREEN_WIDTH+-(g_aPolygon.fWidth/3);
			if((g_aPolygon.pos.y-g_aPolygon.fHeight/2)>=260.0f && (g_aPolygon.pos.y+g_aPolygon.fHeight/2)<=(260.0f+170.0f) )/*�h�A����*/
			{

				switch(g_map)
				{

					case MODE_JIESHAO:
					if(g_aPolygon.bDoorUse==true && jieshaobUse == true)
					{
					UpdateDoor1();
					g_map = MODE_GAME1;
					SetFade(FADE_OUT,MODE_GAME1);
					}
					g_aPolygon.bDoorUse=false;
					break;

				case MODE_GAME1:
					if(g_aPolygon.bDoorUse==true && bKey == true)
					{
					
					UpdateDoor1();
					g_map = MODE_GAME2;
					SetFade(FADE_OUT,MODE_GAME2);
					}
					g_aPolygon.bDoorUse=false;
					break;

					case MODE_GAME2:
					if(g_aPolygon.bDoorUse==true&& bKey == true)
					{
					UpdateDoor1();
					g_map = MODE_GAME3;
					SetFade(FADE_OUT,MODE_GAME3);
					}
					g_aPolygon.bDoorUse=false;
					break;

					case MODE_GAME3:
					if(g_aPolygon.bDoorUse==true&& bKey == true)
					{
						UpdateDoor1();
					g_map = MODE_RESULT;
					SetFade(FADE_OUT,MODE_RESULT);
					}
					g_aPolygon.bDoorUse=false;
					break;

				}
			}
		}

		if((g_aPolygon.pos.y-g_aPolygon.fHeight/5) <= 0)
		{
			g_aPolygon.pos.y=(g_aPolygon.fHeight/5);
		}

		if((g_aPolygon.pos.y+g_aPolygon.fHeight/5) >= SCREEN_HEIGHT)
		{
			g_aPolygon.pos.y = SCREEN_HEIGHT+-(g_aPolygon.fHeight/5);
		}

			pVtx[0].pos = D3DXVECTOR3 (g_aPolygon.pos.x - sinf( g_fAnglePolygon + g_rotPolygon.z ) * g_fLengthPolygon,
									   g_aPolygon.pos.y - cosf( g_fAnglePolygon + g_rotPolygon.z ) * g_fLengthPolygon,
									   0.0f);

			pVtx[1].pos = D3DXVECTOR3 (g_aPolygon.pos.x + sinf( g_fAnglePolygon - g_rotPolygon.z ) * g_fLengthPolygon,
									   g_aPolygon.pos.y - cosf( g_fAnglePolygon - g_rotPolygon.z ) * g_fLengthPolygon,
									   0.0f);
	
			pVtx[2].pos = D3DXVECTOR3 (g_aPolygon.pos.x - sinf( g_fAnglePolygon - g_rotPolygon.z ) * g_fLengthPolygon,
									   g_aPolygon.pos.y + cosf( g_fAnglePolygon - g_rotPolygon.z ) * g_fLengthPolygon,
									   0.0f);

			pVtx[3].pos = D3DXVECTOR3 (g_aPolygon.pos.x + sinf( g_fAnglePolygon + g_rotPolygon.z ) * g_fLengthPolygon,
									   g_aPolygon.pos.y + cosf( g_fAnglePolygon + g_rotPolygon.z ) * g_fLengthPolygon,
									   0.0f);

			pVtx[0].tex.x = g_nPatternAnim_Polygon *(1.0f / maxAnimX_Polygon);
			pVtx[0].tex.y = startAnimY_Polygon;

			pVtx[1].tex.x = (g_nPatternAnim_Polygon * (1.0f /  maxAnimX_Polygon)) + (1.0f / maxAnimX_Polygon);
			pVtx[1].tex.y = startAnimY_Polygon;
				
			pVtx[2].tex.x = g_nPatternAnim_Polygon * (1.0f /  maxAnimX_Polygon);
			pVtx[2].tex.y = animRow_Polygon *(1.0f / maxAnimY_Polygon);

			pVtx[3].tex.x = (g_nPatternAnim_Polygon * (1.0f /  maxAnimX_Polygon)) + (1.0f / maxAnimX_Polygon);
			pVtx[3].tex.y = animRow_Polygon *(1.0f / maxAnimY_Polygon);

	////////////////////////////////////////////////////////
	//if(GetKeyboardPress(DIK_W) == true)		//��ړ�
	//{
	//	g_movePolygon.y -= move;
	//	if(GetKeyboardPress(DIK_A) == true)		//�㍶�ړ�
	//	{
	//		g_movePolygon.x -= sinf(-D3DX_PI*(3/4) *move);
	//		g_movePolygon.y -= cosf(-D3DX_PI*(3/4) *move);
	//	}
	//	else if(GetKeyboardPress(DIK_D) == true)		//��E�ړ�
	//	{
	//		g_movePolygon.x += sinf(D3DX_PI*(3/4) *move);
	//		g_movePolygon.y -= cosf(D3DX_PI*(3/4) *move);
	//	}
	//}
	//else if(GetKeyboardPress(DIK_S) == true)		//���ړ�
	//{
	//	g_movePolygon.y += move;
	//	if(GetKeyboardPress(DIK_A) == true)		//�����ړ�
	//	{
	//		g_movePolygon.x -= sinf(-D3DX_PI*(1/4) *move);
	//		g_movePolygon.y -= cosf(-D3DX_PI*(1/4) *move);
	//	}
	//	else if(GetKeyboardPress(DIK_D) == true)		//���E�ړ�
	//	{
	//		g_movePolygon.x += sinf(D3DX_PI*(1/4) *move);
	//		g_movePolygon.y -= cosf(D3DX_PI*(1/4) *move);
	//	}
	//}


	//if(GetKeyboardPress(DIK_A)== true)		//���ړ�
	//{
	//	g_movePolygon.x -= move;
	//}
	//if(GetKeyboardPress(DIK_D) == true)		//�E�ړ�
	//{
	//	g_movePolygon.x += move;
	//}

	//g_aPolygon.pos.x += g_movePolygon.x;
	//g_aPolygon.pos.y += g_movePolygon.y;
	//g_movePolygon.x -= /*(g_aPolygon.pos.x -g_aPolygon.pos.x )*/2*0.2f;
	//g_movePolygon.y += /*(g_aPolygon.pos.y -g_aPolygon.pos.y )*/2*0.2f;
	///////////////////////////////////////////////////////////////

	//	g_fLengthPolygon -= move_Polygon;
	//	}

	g_pVtxBuffPolygon ->Unlock();	//LOCK
		}
	}
	}
}
void MapPolygon(void)
{

		//�������Ȃ���
		if(  bKey == false && (g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=1000.0f && (g_aPolygon.pos.x - g_aPolygon.fWidth/5)<= 1020.0f && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>= 170.0f && (g_aPolygon.pos.y+g_aPolygon.fHeight/5) <= 470.0f )
		{
			g_aPolygon.pos.x =1000.0f- g_aPolygon.fWidth/5;
		}

		if( bUsebg3 == false && bUsebg2 == true && bProp2== false &&  (g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=940.0f && (g_aPolygon.pos.x - g_aPolygon.fWidth/5)<= 1000.0f && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>= 170.0f && (g_aPolygon.pos.y+g_aPolygon.fHeight/5) <= 470.0f )
		{
			g_aPolygon.pos.x =940.0f- g_aPolygon.fWidth/5;
		}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if(GetKeyboardPress(DIK_C) )
			{
				bUseTalk= false;
				bUseAvatar = false;
				bUseTalk1 = false;
				bUseTalk2 = false;
				bUseTalk3 = false;
				bUseTalk4 = false;
				bUseTalk5 = false;
				bUseTalk6 = false;
				bUseTalk7 = false;
				bUseTalk8 = false;
				bUseTalk9 = false;
			}
		if(bUsebg3 == false)
		{
		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)<=50.f && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=570.0f)
		{
			g_aPolygon.pos.y=570.0f-(g_aPolygon.fHeight/5);
		}

		if((g_aPolygon.pos.x - g_aPolygon.fWidth/5)<=50.f && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.x=50.0f+(g_aPolygon.fWidth/5);
		}

		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)<=100.f && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.y=610.0f-(g_aPolygon.fHeight/5);
		}

		if((g_aPolygon.pos.x - g_aPolygon.fWidth/5)<=100.f && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.x=100.0f+(g_aPolygon.fWidth/5);
			if(GetKeyboardTrigger(DIK_E) )/*����*/
			{
			bUseTalk= true;
			bUseAvatar = true;
			bUseTalk1 = true;
			bUseTalk7 = true;
			}
		}
////////////////////////////////////////////////////////////////////////////////////////////////////////

		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_ONE && (g_aPolygon.pos.x + g_aPolygon.fWidth/5)<=(50.f+WIDTH_ONE) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=570.0f)
		{
			g_aPolygon.pos.y=570.0f-(g_aPolygon.fHeight/5);
		}

		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_ONE && (g_aPolygon.pos.x - g_aPolygon.fWidth/5)<=(50.f+WIDTH_ONE) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.x=(50.0f+WIDTH_ONE)+(g_aPolygon.fWidth/5);
		}

		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_ONE &&(g_aPolygon.pos.x + g_aPolygon.fWidth/5)<=(100.f+WIDTH_ONE) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.y=610.0f-(g_aPolygon.fHeight/5);
		}

		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_ONE &&(g_aPolygon.pos.x - g_aPolygon.fWidth/5)<=(100.f+WIDTH_ONE) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.x=(100.0f+WIDTH_ONE)+(g_aPolygon.fWidth/5);
			if(GetKeyboardTrigger(DIK_E) )/*����*/
			{
			bUseTalk= true;
			bUseAvatar = true;
			bUseTalk2 = true;
			bUseTalk8 = true;
			}
		}

//////////////////////////////////////////////////////////////////////////////////////////////////////////


		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_TWO && (g_aPolygon.pos.x + g_aPolygon.fWidth/5)<=(50.f+WIDTH_TWO) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=570.0f)
		{
			g_aPolygon.pos.y=570.0f-(g_aPolygon.fHeight/5);
		}

		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_TWO && (g_aPolygon.pos.x - g_aPolygon.fWidth/5)<=(50.f+WIDTH_TWO) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.x=(50.0f+WIDTH_TWO)+(g_aPolygon.fWidth/5);
		}

		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_TWO && (g_aPolygon.pos.x + g_aPolygon.fWidth/5)<=(100.f+WIDTH_TWO) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.y=610.0f-(g_aPolygon.fHeight/5);
		}

		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_TWO && (g_aPolygon.pos.x - g_aPolygon.fWidth/5)<=(100.f+WIDTH_TWO) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.x=(100.0f+WIDTH_TWO)+(g_aPolygon.fWidth/5);
			if(GetKeyboardTrigger(DIK_E) )/*����*/
			{
			bUseTalk= true;
			bUseAvatar = true;
			bUseTalk3 =true;
			bUseTalk8 = true;
			}
		}
////////////////////////////////////////////////////////////////////////////////////////////////////////


		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_THREE && (g_aPolygon.pos.x + g_aPolygon.fWidth/5)<=(50.f+WIDTH_THREE) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=570.0f)
		{
			g_aPolygon.pos.y=570.0f-(g_aPolygon.fHeight/5);
		}

		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_THREE && (g_aPolygon.pos.x - g_aPolygon.fWidth/5)<=(50.f+WIDTH_THREE) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.x=(50.0f+WIDTH_THREE)+(g_aPolygon.fWidth/5);
		}

		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_THREE && (g_aPolygon.pos.x + g_aPolygon.fWidth/5)<=(100.f+WIDTH_THREE) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.y=610.0f-(g_aPolygon.fHeight/5);
		}

		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_THREE && (g_aPolygon.pos.x - g_aPolygon.fWidth/5)<=(100.f+WIDTH_THREE) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.x=(100.0f+WIDTH_THREE)+(g_aPolygon.fWidth/5);
			if(GetKeyboardTrigger(DIK_E) )/*����*/
			{
			bUseTalk= true;
			bUseAvatar = true;
			bUseTalk4 =true;
			bUseTalk8 = true;
			}
		}
////////////////////////////////////////////////////////////////////////////////////////////////////////



		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_FOUR && (g_aPolygon.pos.x + g_aPolygon.fWidth/5)<=(50.f+WIDTH_FOUR) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=570.0f)
		{
			g_aPolygon.pos.y=570.0f-(g_aPolygon.fHeight/5);
		}

		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_FOUR && (g_aPolygon.pos.x - g_aPolygon.fWidth/5)<=(50.f+WIDTH_FOUR) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.x=(50.0f+WIDTH_FOUR)+(g_aPolygon.fWidth/5);
		}

		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_FOUR && (g_aPolygon.pos.x + g_aPolygon.fWidth/5)<=(100.f+WIDTH_FOUR) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.y=610.0f-(g_aPolygon.fHeight/5);
		}

		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=WIDTH_FOUR && (g_aPolygon.pos.x - g_aPolygon.fWidth/5)<=(100.f+WIDTH_FOUR) && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=610.0f)
		{
			g_aPolygon.pos.x=(100.0f+WIDTH_FOUR)+(g_aPolygon.fWidth/5);
			if(GetKeyboardTrigger(DIK_E) )/*����*/
			{
			bUseTalk= true;
			bUseAvatar = true;
			bUseTalk5 =true;
			bUseTalk8 = true;
			}
		}
////////////////////////////////////////////////////////////////////////////////////////////////////////
//�E��
		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=850.f && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)<=270.0f)
		{
			g_aPolygon.pos.x=850.0f-(g_aPolygon.fWidth/5);
		}

		if((g_aPolygon.pos.x - g_aPolygon.fWidth/5)>=850.f && (g_aPolygon.pos.y-g_aPolygon.fHeight/5)<=260.0f)
		{
			g_aPolygon.pos.y=260.0f+g_aPolygon.fHeight/5;
		}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//�E��
		/*�|���S���P*/
		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=ONE_POLYGON_ONE_DOWN_X && (g_aPolygon.pos.x - g_aPolygon.fWidth/5)<= ONE_POLYGON_ONE_NAKA && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>= ONE_POLYGON_ONE_UP_Y && (g_aPolygon.pos.y+g_aPolygon.fHeight/5) <= ONE_POLYGON_ONE_DOWN_Y)
		{
			g_aPolygon.pos.x =ONE_POLYGON_ONE_DOWN_X - g_aPolygon.fWidth/5;
		}	

		if((g_aPolygon.pos.x - g_aPolygon.fWidth/5)<=ONE_POLYGON_TWO_DOWN_X && (g_aPolygon.pos.x - g_aPolygon.fWidth/5)>=ONE_POLYGON_TWO_NAKA && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=ONE_POLYGON_TWO_UP_Y && (g_aPolygon.pos.y+g_aPolygon.fHeight/5) <= ONE_POLYGON_TWO_DOWN_Y)
		{
			g_aPolygon.pos.x =ONE_POLYGON_TWO_DOWN_X + g_aPolygon.fWidth/5;
		}

		if((g_aPolygon.pos.x - g_aPolygon.fWidth/5)>=ONE_POLYGON_THREE_DOWN_X && (g_aPolygon.pos.x + g_aPolygon.fWidth/5)<=ONE_POLYGON_THREE_UP_X && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=ONE_POLYGON_THREE_DOWN_Y && (g_aPolygon.pos.y+g_aPolygon.fHeight/5) <= ONE_POLYGON_THREE_NAKA)
		{
			g_aPolygon.pos.y=ONE_POLYGON_THREE_DOWN_Y-g_aPolygon.fHeight/5 ;
		}
		
		if((g_aPolygon.pos.x - g_aPolygon.fWidth/5)>=ONE_POLYGON_FOUR_DOWN_X && (g_aPolygon.pos.x +
			g_aPolygon.fWidth/5)<=ONE_POLYGON_FOUR_UP_X && (g_aPolygon.pos.y-g_aPolygon.fHeight/5)>=ONE_POLYGON_FOUR_NAKA && (g_aPolygon.pos.y-g_aPolygon.fHeight/5) <= ONE_POLYGON_FOUR_UP_Y)
		{
			g_aPolygon.pos.y= ONE_POLYGON_FOUR_UP_Y + g_aPolygon.fHeight/5 ;
			if(bProp== true && bKey == false && GetKeyboardTrigger(DIK_E))/*����*/
			{
				bProp= false;
				bKey = true;
				bPropUpdate = true;
			}
		}

		/*�|���S��2*/
		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=TWO_POLYGON_ONE_DOWN_X && (g_aPolygon.pos.x - g_aPolygon.fWidth/5)<= TWO_POLYGON_ONE_NAKA && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>= TWO_POLYGON_ONE_UP_Y && (g_aPolygon.pos.y+g_aPolygon.fHeight/5) <= TWO_POLYGON_ONE_DOWN_Y)
		{
			g_aPolygon.pos.x =TWO_POLYGON_ONE_DOWN_X- g_aPolygon.fWidth/5;
		}	

		if((g_aPolygon.pos.x - g_aPolygon.fWidth/5)<=TWO_POLYGON_TWO_DOWN_X && (g_aPolygon.pos.x - g_aPolygon.fWidth/5)>=TWO_POLYGON_TWO_NAKA && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=TWO_POLYGON_TWO_UP_Y && (g_aPolygon.pos.y+g_aPolygon.fHeight/5) <= TWO_POLYGON_TWO_DOWN_Y)
		{
			g_aPolygon.pos.x =TWO_POLYGON_TWO_DOWN_X + g_aPolygon.fWidth/5;
		}

		///*�|���S��3�����܂�*/


		if((g_aPolygon.pos.x - g_aPolygon.fWidth/5)>=THREE_POLYGON_THREE_DOWN_X && (g_aPolygon.pos.x + g_aPolygon.fWidth/5)<=THREE_POLYGON_THREE_UP_X && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>=THREE_POLYGON_THREE_DOWN_Y && (g_aPolygon.pos.y+g_aPolygon.fHeight/5) <= THREE_POLYGON_THREE_NAKA)
		{
			g_aPolygon.pos.y=THREE_POLYGON_THREE_DOWN_Y-g_aPolygon.fHeight/5;
		}
		
		if((g_aPolygon.pos.x - g_aPolygon.fWidth/5)>=THREE_POLYGON_FOUR_DOWN_X && (g_aPolygon.pos.x +g_aPolygon.fWidth/5)<=THREE_POLYGON_FOUR_UP_X && (g_aPolygon.pos.y-g_aPolygon.fHeight/5)>=THREE_POLYGON_FOUR_NAKA && (g_aPolygon.pos.y-g_aPolygon.fHeight/5) <= THREE_POLYGON_FOUR_UP_Y)
		{
			g_aPolygon.pos.y= THREE_POLYGON_FOUR_UP_Y + g_aPolygon.fHeight/5 ;
			if(GetKeyboardTrigger(DIK_E) )/*���茮��PROP�Ȃ��ꍇ�iPROP�����j*/
			{
			bProp= true;
			bUseAvatar = true;
			bUseTalk = true;
			bUseTalk6 = true;
			if(GetKeyboardTrigger(DIK_E) && bUsebg2 == true)
			{
				bUseAvatar = true;
				bUseTalk = true;
				bUseTalk9 = true;
				bProp2 =true;
				UpdateProp2();
			}
			}
		}


		/*�|���S��4*/
		if((g_aPolygon.pos.x + g_aPolygon.fWidth/5)>=FOUR_POLYGON_ONE_DOWN_X && (g_aPolygon.pos.x - g_aPolygon.fWidth/5)<= FOUR_POLYGON_ONE_NAKA && (g_aPolygon.pos.y+g_aPolygon.fHeight/5)>= FOUR_POLYGON_ONE_UP_Y && (g_aPolygon.pos.y+g_aPolygon.fHeight/5) <= FOUR_POLYGON_ONE_DOWN_Y)
		{
			g_aPolygon.pos.x =FOUR_POLYGON_ONE_DOWN_X - g_aPolygon.fWidth/5;
		}	

		if((g_aPolygon.pos.x - g_aPolygon.fWidth/5)>=FOUR_POLYGON_FOUR_DOWN_X && (g_aPolygon.pos.x +g_aPolygon.fWidth/5)<=FOUR_POLYGON_FOUR_UP_X && (g_aPolygon.pos.y-g_aPolygon.fHeight/5)>=FOUR_POLYGON_FOUR_NAKA && (g_aPolygon.pos.y-g_aPolygon.fHeight/5) <= FOUR_POLYGON_FOUR_UP_Y)
		{
			g_aPolygon.pos.y= FOUR_POLYGON_FOUR_UP_Y + g_aPolygon.fHeight/5 ;
		}
		}
		if(bUsebg3 == true && (GetKeyboardTrigger(DIK_E)))
		{
			if(( g_aPolygon.pos.x- (g_aPolygon.fWidth/5))>=(166.0f)
				&&( g_aPolygon.pos.x+ (g_aPolygon.fWidth/5))<=(393.0f)
				&&( g_aPolygon.pos.y- (g_aPolygon.fHeight/5))>=(41.0f)
				&&( g_aPolygon.pos.y+ (g_aPolygon.fHeight/5))<=(268.0f)
				)
				{		//SHITOU
					cnt_polygon = 0;
					SetFade(FADE_OUT,MODE_RESULT);
				}

			if(( g_aPolygon.pos.x- (g_aPolygon.fWidth/5))>=(151.0f)
				&&( g_aPolygon.pos.x+ (g_aPolygon.fWidth/5))<=(392.0f)
				&&( g_aPolygon.pos.y- (g_aPolygon.fHeight/5))>=(275.0f)
				&&( g_aPolygon.pos.y+ (g_aPolygon.fHeight/5))<=(516.0f)
				)
				{		//JIANDAO
					cnt_polygon = 1;
					SetFade(FADE_OUT,MODE_RESULT);
				}

			if(( g_aPolygon.pos.x- (g_aPolygon.fWidth/5))>=(151.0f)
				&&( g_aPolygon.pos.x+ (g_aPolygon.fWidth/5))<=(392.0f)
				&&( g_aPolygon.pos.y- (g_aPolygon.fHeight/5))>=(522.0f)
				&&( g_aPolygon.pos.y+ (g_aPolygon.fHeight/5))<=(768.0f)
				)
				{		//BU
					cnt_polygon = 2;
					SetFade(FADE_OUT,MODE_RESULT);
				}
		}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	
}
void SetPolygon(D3DXVECTOR3 pos)
{
	g_aPolygon.pos.x = pos.x;
	g_aPolygon.pos.y = pos.y;
}
POLYGON *GetPolygon(void)
{
	return &g_aPolygon;
}