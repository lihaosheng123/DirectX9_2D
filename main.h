#ifndef _MAIN_H_
#define _MAIN_H_
#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"		//入力処理に必要
#pragma comment(lib,"dinput8.lib")//入力処理に必要
//インクルードファイル
#include <windows.h>
#include "d3dx9.h"	//描画処理に必要
//#pragmaディレィディブ追加（ライブラリのリンク）
#pragma comment(lib,"d3d9.lib")		//描画処理に必要
#pragma comment(lib,"d3dx9.lib")	//上記の拡張うイブウリ
#pragma comment(lib,"dxguid.lib")	//DirectXコンボ―ネント使用に必要
#pragma comment(lib,"winmm.lib")

//マクロ定義
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//テクスチャ座標
#define SCREEN_CENTER_X	( SCREEN_WIDTH / 2 )		//ウインドウの中心Ｘ座標
#define SCREEN_CENTER_Y	( SCREEN_HEIGHT / 2 )		//ウインドウの中心Ｙ座標
//構造体
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float rhw;	//座標変換用係数(法線)
	D3DCOLOR col;		//頂点ワーク(頂点色)	
	D3DXVECTOR2 tex;	//テクスチャ座標
} VERTEX_2D;
//モードの種類
typedef enum
{
	MODE_TITLEHONG = 0,		//タイトル画面
	MODE_JIESHAO,
	MODE_GAME1,		//ゲーム画面1
	MODE_GAME2,		//ゲーム画面2
	MODE_GAME3,		//ゲーム画面3
	MODE_RESULT,		//リザルト画面
	MODE_MAX
} MODE;
//プロトタイプ宣言
LPDIRECT3DDEVICE9 GetDevice(void);
void DrawFPS(void);
void SetMode( MODE mode);
MODE GetMode(void);
#endif