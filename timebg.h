#ifndef _TIMEBG_H_
#define _TIMEBG_H_
//�v���g�^�C�v�錾
HRESULT InitTimebg(void);
void UninitTimebg(void);
void UpdateTimebg(void);
void DrawTimebg(void);
void AddTimebg(int valueTimebg);
//time�̍\����
typedef struct
{
	int time;
	int frame;
} TIME;
#endif