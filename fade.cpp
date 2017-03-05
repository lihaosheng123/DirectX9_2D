#include "main.h"
#include "fade.h"
#include "input.h"
//グローバル変数
D3DXCOLOR g_colorFade;		//フェード色
FADE g_fade;		//フェードの状態
MODE g_modeNext;		//次のモード
VERTEX_2D g_pfade[4];
LPDIRECT3DTEXTURE9 g_pTexturefade =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufffade =NULL;	//頂点パッファへのポインタ
//=============================================================================
//  関数名　：Initfade
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitFade(void)
{
	g_fade = FADE_IN;
	g_modeNext = MODE_TITLEHONG;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBufffade,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *fade;
		g_pVtxBufffade ->Lock(0,0,(void **)&fade,0);		//頂点情報へのポインタを取得

		g_colorFade = D3DXCOLOR(0.0f,0.0f,0.0f,1.0f);

		fade[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		fade[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
		fade[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		fade[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		fade[0].rhw = 1.0f;
		fade[1].rhw = 1.0f;
		fade[2].rhw = 1.0f;
		fade[3].rhw = 1.0f;
		fade[0].col=g_colorFade;	//頂点情報格納ワーク
		fade[1].col=g_colorFade;
		fade[2].col=g_colorFade;
		fade[3].col=g_colorFade;

		fade[0].tex = D3DXVECTOR2(0.0f,0.0f);
		fade[1].tex = D3DXVECTOR2(1.0f,0.0f);
		fade[2].tex = D3DXVECTOR2(0.0f,1.0f);
		fade[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBufffade ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：Uninitfade
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitFade(void)
{
	if(g_pTexturefade!=NULL)
	{
		g_pTexturefade->Release();
		g_pTexturefade=NULL;
	}
	if(g_pVtxBufffade!=NULL)
	{
		g_pVtxBufffade->Release();		//頂点バッファの開放
		g_pVtxBufffade=NULL;
	}
}
//=============================================================================
//  関数名　：Drawfade
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTexturefade);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBufffade,
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
//=============================================================================
//  関数名　：Updatefade
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateFade(void)
{
	if( g_fade == FADE_IN)
	{
		g_colorFade.a -= 0.01f;

		if( g_colorFade.a < 0.0f )
		{
			g_fade = FADE_NONE;
		}

	}
	else if( g_fade == FADE_OUT )
	{
		g_colorFade.a +=0.01f;
		if( g_colorFade.a >= 1.0f )
		{
			g_fade = FADE_IN;
			SetMode( g_modeNext);
		}
	}
	// 頂点情報へのポインタ
	VERTEX_2D *pVtx;

	g_pVtxBufffade -> Lock(0,0,(void**)&pVtx,0);

	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;
	g_pVtxBufffade -> Unlock();
}

//=============================================================================
//  関数名　：FADE GetFade(void)
//  機能概要：
//  戻り値　：g_fade
//=============================================================================
FADE GetFade(void)
{
	return g_fade;
}
//=============================================================================
//  関数名　：SetFade
//  機能概要：
//  戻り値　：
//  引数　：FADE fade,MODE modeNext
//=============================================================================
void SetFade(FADE fade,MODE modeNext)
{
	g_fade = fade;
	g_modeNext = modeNext;
}