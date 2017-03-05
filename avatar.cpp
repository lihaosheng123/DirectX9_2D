#include "main.h"
#include "avatar.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureAvatar =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffAvatar =NULL;	//頂点パッファへのポインタ
D3DXVECTOR3 g_posAvatar;	//ポリゴンの位置
D3DXVECTOR3 g_rotAvatar;		//ポリゴンの回転角
D3DXVECTOR3 g_moveAvatar;		//ポリゴンの移動量
int g_nCounterAnim_Avatar;		//アンメーションカウンタ
int g_nPatternAnim_Avatar;		//アンメーションパターンNO
float animRow_Avatar =1.0f;
float maxAnimX_Avatar = 3.0f;
float maxAnimY_Avatar = 1.0f;
float AvatarWidth = 240.0f;		//ポリゴンの幅
float AvatarHeight =50.0f;		//ポリゴンの高さ
float g_fLengthAvatar;		//ポリゴンの対角線の長さ
float g_fAngleAvatar;		//ポリゴンの対角線の角度
float startAnimY_Avatar = 0.0f;
AVATAR g_Avatarstate =AVATAR_MAN;
//=============================================================================
//  関数名　：InitAvatar
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitAvatar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffAvatar,NULL)))
	{
		return E_FAIL;
	}
		VERTEX_2D *pVtx;
		g_pVtxBuffAvatar ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得
		//テクスチャの読み込み	
		D3DXCreateTextureFromFile(
			pDevice,
			".\\data\\TEXTURE\\avatar.png",
		&g_pTextureAvatar);
		bUseAvatar = false;
			//初期化処理
		g_posAvatar.x = 80.0f;
		g_posAvatar.y = 700.0f;
		g_posAvatar = D3DXVECTOR3(g_posAvatar.x,g_posAvatar.y,0.0f);

			//回転初期化処理
		g_rotAvatar = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_fLengthAvatar =sqrtf(AvatarWidth * AvatarWidth + AvatarHeight * AvatarHeight)*0.5f;
		g_fAngleAvatar =atan2f(AvatarWidth,AvatarHeight)*0.5f;


		//頂点座標設定
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
		//UV設定
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
		//座標変換	
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
			
		//頂点色設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 128);	//頂点情報格納ワーク
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 128);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 128);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 128);

		g_pVtxBuffAvatar ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：UninitAvatar
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitAvatar(void)
{

	if(g_pVtxBuffAvatar!=NULL)
	{
		g_pVtxBuffAvatar->Release();		//頂点バッファの開放
		g_pVtxBuffAvatar=NULL;
	}
	if(g_pTextureAvatar!=NULL)
	{
		g_pTextureAvatar->Release();
		g_pTextureAvatar=NULL;
	}
}
//=============================================================================
//  関数名　：DrawAvatar
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawAvatar(void)
{
	if(bUseAvatar == true)
	{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureAvatar);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffAvatar,
								0,
								sizeof(VERTEX_2D)
								);
	// フェードの描画設定内容
	pDevice -> DrawPrimitive(
							  D3DPT_TRIANGLESTRIP,		// プリミティブの種類
							  0,		// 最初の頂点のインデックス
							  2			// 描画するプリミティブ数
							);
	}

}
//=============================================================================
//  関数名　：UpdateAvatar
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateAvatar(void)
{
	if(bUseAvatar == true)
	{
	}
}