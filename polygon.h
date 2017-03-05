#ifndef _POLYGON_H_
#define _POLYGON_H_
//マクロ定義

#define WIDTH_ONE 180
#define WIDTH_TWO 365
#define WIDTH_THREE 550
#define WIDTH_FOUR 730
//1
#define ONE_POLYGON_ONE_DOWN_X 920
#define ONE_POLYGON_ONE_DOWN_Y 750
#define ONE_POLYGON_ONE_UP_X 920
#define ONE_POLYGON_ONE_UP_Y 570
#define ONE_POLYGON_ONE_NAKA 1010

#define ONE_POLYGON_TWO_DOWN_X 1070
#define ONE_POLYGON_TWO_DOWN_Y 750
#define ONE_POLYGON_TWO_UP_X 1080
#define ONE_POLYGON_TWO_UP_Y 570
#define ONE_POLYGON_TWO_NAKA 1000

#define ONE_POLYGON_THREE_DOWN_X 920
#define ONE_POLYGON_THREE_DOWN_Y 560
#define ONE_POLYGON_THREE_UP_X 1070
#define ONE_POLYGON_THREE_UP_Y 560
#define ONE_POLYGON_THREE_NAKA 610

#define ONE_POLYGON_FOUR_DOWN_X 920
#define ONE_POLYGON_FOUR_DOWN_Y 750
#define ONE_POLYGON_FOUR_UP_X 1070
#define ONE_POLYGON_FOUR_UP_Y 730
#define ONE_POLYGON_FOUR_NAKA 710
//2
#define TWO_POLYGON_ONE_DOWN_X 1000
#define TWO_POLYGON_ONE_DOWN_Y 560
#define TWO_POLYGON_ONE_UP_X 1000
#define TWO_POLYGON_ONE_UP_Y 410
#define TWO_POLYGON_ONE_NAKA 1020

#define TWO_POLYGON_TWO_DOWN_X 1080
#define TWO_POLYGON_TWO_DOWN_Y 560
#define TWO_POLYGON_TWO_UP_X 1080
#define TWO_POLYGON_TWO_UP_Y 400
#define TWO_POLYGON_TWO_NAKA 1040


//3
#define THREE_POLYGON_THREE_DOWN_X 1000
#define THREE_POLYGON_THREE_DOWN_Y 400
#define THREE_POLYGON_THREE_UP_X 1200
#define THREE_POLYGON_THREE_UP_Y 400
#define THREE_POLYGON_THREE_NAKA 450

#define THREE_POLYGON_FOUR_DOWN_X 970
#define THREE_POLYGON_FOUR_DOWN_Y 490
#define THREE_POLYGON_FOUR_UP_X 1200
#define THREE_POLYGON_FOUR_UP_Y 490
#define THREE_POLYGON_FOUR_NAKA 480

//4
#define FOUR_POLYGON_ONE_DOWN_X 1140
#define FOUR_POLYGON_ONE_DOWN_Y 640
#define FOUR_POLYGON_ONE_UP_X 1140
#define FOUR_POLYGON_ONE_UP_Y 470
#define FOUR_POLYGON_ONE_NAKA 1150
	
#define FOUR_POLYGON_FOUR_DOWN_X 1140
#define FOUR_POLYGON_FOUR_DOWN_Y 640
#define FOUR_POLYGON_FOUR_UP_X 1200
#define FOUR_POLYGON_FOUR_UP_Y 640
#define FOUR_POLYGON_FOUR_NAKA 610
//プロトタイプ宣言
HRESULT InitPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(void);
void MapPolygon(void);
void SetPolygon(D3DXVECTOR3 pos);
typedef struct
{
	D3DXVECTOR3 pos;		//場所
	float fWidth;		//幅
	float fHeight;		//高さ
	int nLife;		//寿命
	bool bUse;
	bool bDoorUse;
} POLYGON;
POLYGON *GetPolygon (void);
#endif