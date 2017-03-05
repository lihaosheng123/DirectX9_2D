#ifndef _AVATAR_H_
#define _AVATAR_H_
HRESULT InitAvatar(void);
void UpdateAvatar(void);
void DrawAvatar(void);
void UninitAvatar(void);
extern bool bUseAvatar ;
//éÌóﬁ
typedef enum
{
	AVATAR_MAN = 0,		//éÂêlåˆ
	AVATAR_BOSS1,		//BOSS
	AVATAR_BOSS2,		//BOSS
	AVATAR_MAX
} AVATAR;
#endif