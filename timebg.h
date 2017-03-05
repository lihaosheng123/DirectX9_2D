#ifndef _TIMEBG_H_
#define _TIMEBG_H_
//プロトタイプ宣言
HRESULT InitTimebg(void);
void UninitTimebg(void);
void UpdateTimebg(void);
void DrawTimebg(void);
void AddTimebg(int valueTimebg);
//timeの構造体
typedef struct
{
	int time;
	int frame;
} TIME;
#endif