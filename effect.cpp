#include "effect.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_EFFECT		"data/TEXTURE/effect000.jpg"	// 読み込むテクスチャファイル名

#ifdef USE_TEXTURE_EFFECT
#define	NUM_VERTEX_CIRCLE	(4)			// 頂点数
#define	NUM_POLYGON_CIRCLE	(2)			// ポリゴン数
#else
#define	NUM_VERTEX_CIRCLE	(16 + 2)	// 頂点数
#define	NUM_POLYGON_CIRCLE	(16)		// ポリゴン数
#endif	

#define	MAX_EFFECT			(8000)		// エフェクトの最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 posBase;	// 基準位置
	D3DXVECTOR3 rot;		// 向き
	D3DXVECTOR3 move;		// 移動量
	D3DXCOLOR col;			// 色
	float fColAlphaValue;	// 色変化量
	float fAngle;			// 角度
	float fRadius;			// 半径
	float fRadiusValue;		// 半径変化量
	D3DXVECTOR2 swingRate;	// 揺れ係数
	D3DXVECTOR2 swingWidth;	// 揺れ幅
	D3DXVECTOR2 swingValue;	// 揺れ幅変化量
	int nLife;				// ライフ
	int nType;				// 種類
	bool bUse;				// 使用しているかどうか
} EFFECT;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);
void SetVertexEffect(int nEffectID, D3DXVECTOR3 pos);
void SetColorEffect(int nEffectID, D3DXCOLOR col, D3DXCOLOR colFade);
void SetRadiusEffect(int nEffectID, float fRadius);

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureEffect = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	// 頂点バッファへのポインタ

EFFECT					g_aEffect[MAX_EFFECT];		// エフェクトのワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].rot= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].fColAlphaValue = 0.0f;
		g_aEffect[nCntEffect].fAngle = 0.0f;
		g_aEffect[nCntEffect].fRadius = 40.0f;
		g_aEffect[nCntEffect].fRadiusValue = 0.0f;
		g_aEffect[nCntEffect].swingRate.x = 0.0f;
		g_aEffect[nCntEffect].swingRate.y = 0.0f;
		g_aEffect[nCntEffect].swingWidth.x = 0.0f;
		g_aEffect[nCntEffect].swingWidth.y = 0.0f;
		g_aEffect[nCntEffect].swingValue.x = 0.0f;
		g_aEffect[nCntEffect].swingValue.y = 0.0f;
		g_aEffect[nCntEffect].nType = EFFECTTYPE_NORMAL;
		g_aEffect[nCntEffect].nLife = 0;
		g_aEffect[nCntEffect].bUse = false;
	}

#ifdef USE_TEXTURE_EFFECT
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
								TEXTURE_EFFECT,			// ファイルの名前
								&g_pTextureEffect);		// 読み込むメモリー
#endif

	// 頂点情報の作成
	MakeVertexEffect(pDevice);

	return S_OK;
}

	//=============================================================================
	// 終了処理
	//=============================================================================
	void UninitEffect(void)
	{
		if(g_pTextureEffect != NULL)
		{// テクスチャの開放
			g_pTextureEffect->Release();
			g_pTextureEffect = NULL;
		}

		if(g_pVtxBuffEffect != NULL)
		{// 頂点バッファの開放
			g_pVtxBuffEffect->Release();
			g_pVtxBuffEffect = NULL;
		}
	}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffect(void)
{
	EFFECT *pEffect;

	pEffect = &g_aEffect[0];
	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{
		if(pEffect->bUse == true)
		{// エフェクトが使用中なら描画
			pEffect->nLife--;
			if(pEffect->nLife <= 0)
			{// エフェクトを消滅させる
				pEffect->bUse = false;
			}
			else
			{// エフェクトを調整
				// 色の設定
				pEffect->col.a -= pEffect->fColAlphaValue;
				if(pEffect->col.a <= 0.0f)
				{
					pEffect->col.a = 0.0f;
				}
				SetColorEffect(nCntEffect, pEffect->col, D3DXCOLOR(0.25f, 0.25f, 0.25f, 0.20f));

				// 半径の設定
				pEffect->fRadius -= pEffect->fRadiusValue;
				if(pEffect->fRadius <= 0.0f)
				{
					pEffect->fRadius = 0.0f;
				}
				SetRadiusEffect(nCntEffect, pEffect->fRadius);

				// 揺れ(X方向)の設定
				pEffect->swingRate.x += D3DX_PI * pEffect->swingValue.x;
				if(pEffect->swingRate.x > D3DX_PI)
				{
					pEffect->swingRate.x -= D3DX_PI * 2.0f;
				}
				pEffect->pos.x = pEffect->posBase.x + sinf(pEffect->swingRate.x) * pEffect->swingWidth.x;

				// 揺れ(Y方向)の設定
				pEffect->swingRate.y += D3DX_PI * pEffect->swingValue.y;
				if(pEffect->swingRate.y > D3DX_PI)
				{
					pEffect->swingRate.y -= D3DX_PI * 2.0f;
				}
				pEffect->pos.y = pEffect->posBase.y + sinf(pEffect->swingRate.y) * pEffect->swingWidth.y;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureEffect);

	// ブレンド加算処理
	pDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);		// αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);				// αデスティネーションカラーの指定

	// ポリゴンの描画
	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if(g_aEffect[nCntEffect].bUse == true)
		{// エフェクトが使用中なら描画
#ifdef USE_TEXTURE_EFFECT
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntEffect * NUM_VERTEX_CIRCLE), NUM_POLYGON_CIRCLE);
#else
			pDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, (nCntEffect * NUM_VERTEX_CIRCLE), NUM_POLYGON_CIRCLE);
#endif
		}
	}

	// 通常ブレンド
	pDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);		// αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// αデスティネーションカラーの指定
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX_CIRCLE * MAX_EFFECT,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,								// 頂点バッファの使用法
												FVF_VERTEX_2D,									// 使用する頂点フォーマット
												D3DPOOL_MANAGED,								// リソースのバッファを保持するメモリクラスを指定
												&g_pVtxBuffEffect,								// 頂点バッファインターフェースへのポインタ
												NULL)))											// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;
		const float ANGLE = (D3DX_PI * 2.0f) / NUM_POLYGON_CIRCLE;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

#ifdef USE_TEXTURE_EFFECT
		for(int cntTarget = 0; cntTarget < MAX_EFFECT; cntTarget++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].pos.x = g_aEffect[cntTarget].pos.x - cosf(D3DX_PI * 0.25f + g_aEffect[cntTarget].fAngle) * g_aEffect[cntTarget].fRadius;
			pVtx[0].pos.y = g_aEffect[cntTarget].pos.y - sinf(D3DX_PI * 0.25f + g_aEffect[cntTarget].fAngle) * g_aEffect[cntTarget].fRadius;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aEffect[cntTarget].pos.x + cosf(D3DX_PI * 0.25f - g_aEffect[cntTarget].fAngle) * g_aEffect[cntTarget].fRadius;
			pVtx[1].pos.y = g_aEffect[cntTarget].pos.y - sinf(D3DX_PI * 0.25f - g_aEffect[cntTarget].fAngle) * g_aEffect[cntTarget].fRadius;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aEffect[cntTarget].pos.x - cosf(D3DX_PI * 0.25f - g_aEffect[cntTarget].fAngle) * g_aEffect[cntTarget].fRadius;
			pVtx[2].pos.y = g_aEffect[cntTarget].pos.y + sinf(D3DX_PI * 0.25f - g_aEffect[cntTarget].fAngle) * g_aEffect[cntTarget].fRadius;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aEffect[cntTarget].pos.x + cosf(D3DX_PI * 0.25f + g_aEffect[cntTarget].fAngle) * g_aEffect[cntTarget].fRadius;
			pVtx[3].pos.y = g_aEffect[cntTarget].pos.y + sinf(D3DX_PI * 0.25f + g_aEffect[cntTarget].fAngle) * g_aEffect[cntTarget].fRadius;
			pVtx[3].pos.z = 0.0f;

			// rhwの設定
			pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

			// 頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
#else
		for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
		{
			// 頂点座標の設定
			pVtx->pos.x = g_aEffect[nCntEffect].pos.x;
			pVtx->pos.y = g_aEffect[nCntEffect].pos.y;
			pVtx->pos.z = 0.0f;

			// テクスチャのパースペクティブコレクト用
			pVtx->rhw = 1.0f;

			// 頂点カラーの設定
			pVtx->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// １頂点目の色

			// テクスチャ座標の設定
			pVtx->tex = D3DXVECTOR2(0.0f, 0.0f);		// １頂点目のテクスチャ座標

			pVtx++;

			for(int nCntVtx = 0; nCntVtx <= NUM_POLYGON_CIRCLE; nCntVtx++, pVtx++)
			{
				// 頂点座標の設定
				pVtx->pos.x = g_aEffect[nCntEffect].pos.x - sinf(ANGLE * nCntVtx) * g_aEffect[nCntEffect].fRadius;
				pVtx->pos.y = g_aEffect[nCntEffect].pos.y + cosf(ANGLE * nCntVtx) * g_aEffect[nCntEffect].fRadius;
				pVtx->pos.z = 0.0f;

				// テクスチャのパースペクティブコレクト用
				pVtx->rhw = 1.0f;

				// 頂点カラーの設定
				pVtx->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// テクスチャ座標の設定
				pVtx->tex.x = 0.0f;
				pVtx->tex.y = 0.0f;
			}
		}
#endif

		// 頂点データをアンロックする
		g_pVtxBuffEffect->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEffect(int nEffectID, D3DXVECTOR3 pos)
{
	g_aEffect[nEffectID].pos = pos;

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;
		const float ANGLE = (D3DX_PI * 2.0f) / NUM_POLYGON_CIRCLE;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nEffectID * NUM_VERTEX_CIRCLE);

		// 頂点座標の設定
#ifdef USE_TEXTURE_EFFECT
		pVtx[0].pos.x = g_aEffect[nEffectID].pos.x - cosf(D3DX_PI * 0.25f + g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[0].pos.y = g_aEffect[nEffectID].pos.y - sinf(D3DX_PI * 0.25f + g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_aEffect[nEffectID].pos.x + cosf(D3DX_PI * 0.25f - g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[1].pos.y = g_aEffect[nEffectID].pos.y - sinf(D3DX_PI * 0.25f - g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_aEffect[nEffectID].pos.x - cosf(D3DX_PI * 0.25f - g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[2].pos.y = g_aEffect[nEffectID].pos.y + sinf(D3DX_PI * 0.25f - g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_aEffect[nEffectID].pos.x + cosf(D3DX_PI * 0.25f + g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[3].pos.y = g_aEffect[nEffectID].pos.y + sinf(D3DX_PI * 0.25f + g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[3].pos.z = 0.0f;
#else
		pVtx->pos.x = g_aEffect[nEffectID].pos.x;
		pVtx->pos.y = g_aEffect[nEffectID].pos.y;
		pVtx->pos.z = 0.0f;
		pVtx++;

		for(int nCntVtx = 0; nCntVtx <= NUM_POLYGON_CIRCLE; nCntVtx++, pVtx++)
		{
			pVtx->pos.x = g_aEffect[nEffectID].pos.x - sinf(ANGLE * nCntVtx) * g_aEffect[nEffectID].fRadius;
			pVtx->pos.y = g_aEffect[nEffectID].pos.y + cosf(ANGLE * nCntVtx) * g_aEffect[nEffectID].fRadius;
			pVtx->pos.z = 0.0f;
		}
#endif

		// 頂点データをアンロックする
		g_pVtxBuffEffect->Unlock();
	}
}

//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorEffect(int nEffectID, D3DXCOLOR col, D3DXCOLOR colFade)
{
	g_aEffect[nEffectID].col = col;
	
	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nEffectID * NUM_VERTEX_CIRCLE);

#ifdef USE_TEXTURE_EFFECT
		pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = col;
#else
		pVtx->col = col;
		pVtx++;

		// 頂点カラーの設定
		for(int nCntVtx = 0; nCntVtx <= NUM_POLYGON_CIRCLE; nCntVtx++, pVtx++)
		{
			pVtx->col = D3DXCOLOR(col.r * colFade.r, col.g * colFade.g, col.b * colFade.b, col.a * colFade.a);
		}
#endif

		// 頂点データをアンロックする
		g_pVtxBuffEffect->Unlock();
	}
}

//=============================================================================
// サイズ設定
//=============================================================================
void SetRadiusEffect(int nEffectID, float fRadius)
{
	g_aEffect[nEffectID].fRadius = fRadius;

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;
		const float ANGLE = (D3DX_PI * 2.0f) / NUM_POLYGON_CIRCLE;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += nEffectID * NUM_VERTEX_CIRCLE;

		// 頂点座標の設定
#ifdef USE_TEXTURE_EFFECT
		pVtx[0].pos.x = g_aEffect[nEffectID].pos.x - cosf(D3DX_PI * 0.25f + g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[0].pos.y = g_aEffect[nEffectID].pos.y - sinf(D3DX_PI * 0.25f + g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_aEffect[nEffectID].pos.x + cosf(D3DX_PI * 0.25f - g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[1].pos.y = g_aEffect[nEffectID].pos.y - sinf(D3DX_PI * 0.25f - g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_aEffect[nEffectID].pos.x - cosf(D3DX_PI * 0.25f - g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[2].pos.y = g_aEffect[nEffectID].pos.y + sinf(D3DX_PI * 0.25f - g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_aEffect[nEffectID].pos.x + cosf(D3DX_PI * 0.25f + g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[3].pos.y = g_aEffect[nEffectID].pos.y + sinf(D3DX_PI * 0.25f + g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[3].pos.z = 0.0f;
#else
		pVtx->pos.x = g_aEffect[nEffectID].pos.x;
		pVtx->pos.y = g_aEffect[nEffectID].pos.y;
		pVtx->pos.z = 0.0f;

		pVtx++;

		for(int nCntVtx = 0; nCntVtx <= NUM_POLYGON_CIRCLE; nCntVtx++, pVtx++)
		{
			// 頂点座標の設定
			pVtx->pos.x = g_aEffect[nEffectID].pos.x - sinf(ANGLE * nCntVtx) * g_aEffect[nEffectID].fRadius;
			pVtx->pos.y = g_aEffect[nEffectID].pos.y + cosf(ANGLE * nCntVtx) * g_aEffect[nEffectID].fRadius;
			pVtx->pos.z = 0.0f;
		}
#endif

		// 頂点データをアンロックする
		g_pVtxBuffEffect->Unlock();
	}
}

//=============================================================================
// エフェクト設定
//=============================================================================
int SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife, int nType)
{
	EFFECT *pEffect;
	int nEffectID = -1;

	pEffect = &g_aEffect[0];
	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{
		if(pEffect->bUse == false)
		{
			// ライフの設定
			pEffect->nLife = nLife;

			// タイプの設定
			pEffect->nType = nType;

			// 頂点座標の設定
			pEffect->posBase = pos;
			SetVertexEffect(nCntEffect, pos);

			// 移動量の設定
			pEffect->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// 反射光の設定
			if(pEffect->nType == EFFECTTYPE_RANDOMCOLOR
			|| pEffect->nType == EFFECTTYPE_RANDOMCOLORSWING)
			{// ランダムカラーの場合
#if 0
				int colR,colG,colB,colBase;

				colBase = 98;
				colR = rand() % colBase + 1;
				colBase = 99 - colR;
				colG = rand() % colBase + 1;
				colBase = 100 - (colR + colG);
				colB = colBase + 1;
				col.r = colR / 100.0f;
				col.g = colG / 100.0f;		// [(※)この数値を変更すると緑の要素が増減する(0～10)]
				col.b = colB / 100.0f;		// [(※)この数値を変更すると青の要素が増減する(0～10)]
				col.a = 1.0f;
#else
				col.r = (float)(rand() % 50 + 1) / 100.0f;		// [(※)この数値を変更すると赤の要素が増減する(1～100)]
				col.g = (float)(rand() % 50 + 1) / 100.0f;		// [(※)この数値を変更すると緑の要素が増減する(1～100)]
				col.b = (float)(rand() % 50 + 1) / 100.0f;		// [(※)この数値を変更すると青の要素が増減する(1～100)]
				col.a = 1.0f;
#endif
			}
			pEffect->fColAlphaValue = 1.0f / nLife;
			SetColorEffect(nCntEffect, col, D3DXCOLOR(0.25f, 0.25f, 0.25f, 0.20f));

			// 半径の設定
			pEffect->fRadius = fRadius;
			pEffect->fRadiusValue = (fRadius * 0.55f) / nLife;
			SetRadiusEffect(nCntEffect, fRadius);

			switch(pEffect->nType)
			{
			case EFFECTTYPE_NORMAL:				// 通常エフェクト
			case EFFECTTYPE_RANDOMCOLOR:		// ランダムカラーエフェクト
				pEffect->swingRate.x = 
				pEffect->swingWidth.x = 
				pEffect->swingRate.x = 0.0f;
				pEffect->swingRate.y = 
				pEffect->swingWidth.y = 
				pEffect->swingRate.y = 0.0f;
				break;

			case EFFECTTYPE_SWING:				// 揺れエフェクト
			case EFFECTTYPE_RANDOMCOLORSWING:	// ランダムカラー揺れエフェクト
				// 揺れ(X方向)の設定 [(※)ここで横方向の動きの設定をする]
				pEffect->swingRate.x = 0.0f;//(float)(rand() % 314 - 628) / 100.0f;
				pEffect->swingWidth.x = (float)(rand() % 80 + 40) / 10.0f;
				pEffect->swingValue.x = (float)(rand() % 60 + 30) / 1000.0f;

				// 揺れ(Y方向)の設定 [(※)ここで縦方向の動きの設定をする]
				pEffect->swingRate.y = 0.0f;//(float)(rand() % 314 - 628) / 100.0f;
				pEffect->swingWidth.y = (float)(rand() % 80 + 40) / 10.0f;
				pEffect->swingValue.y = (float)(rand() % 60 + 30) / 1000.0f;
				break;
			}

			pEffect->bUse = true;

			nEffectID = nCntEffect;
			break;
		}
	}

	return nEffectID;
}
