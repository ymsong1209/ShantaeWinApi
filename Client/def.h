#pragma once

//static�� ������ ������ �޸𸮸� ����.
//���� ��� �Լ�.static �Լ� - ��ü�� ��� ȣ���� ���� ��� this��� �Ұ�(���� ȣ�� �Ұ�)
//��� private���� ����
//private�� �ִ� ���� ��� ������ ������ ������ �� �ϳ��� �����Ƿ� ���� ����(this�� ���󵵵�)
// static CEngine *m_Pinst ���� ����
#define SINGLE(type) public:\
					 static type* GetInst()\
					 {\
						 static type inst;\
						 return &inst;\
					 }\
					 private:\
						type();\
						~type();

#define DT CTimeMgr::GetInst()->GetDeltaTime()
#define IsTap(key) CKeyMgr::GetInst()->GetKeyState(key) == KEY_STATE::TAP
#define IsPressed(key) CKeyMgr::GetInst()->GetKeyState(key) == KEY_STATE::PRESSED
#define IsRelease(key) CKeyMgr::GetInst()->GetKeyState(key) == KEY_STATE::RELEASE
#define IsNone(key) CKeyMgr::GetInst()->GetKeyState(key) == KEY_STATE::NONE
#define transBlt(type,val1,val2,val3) Vec2 vLeftTop = Vec2(vPos.x - type->Width() / 2.f, vPos.y - type->Height() / 2.f);\
						TransparentBlt(_dc\
									, (int)vLeftTop.x, (int)vLeftTop.y\
									, (int)type->Width(), (int)type->Height()\
									, type->GetDC()\
									, 0, 0\
									, (int)type->Width(), (int)type->Height()\
									, RGB(val1, val2, val3));

#define DEL(p) if(nullptr != p) delete p;
#define PI 3.1415926535f
#define MOUSE_POS CKeyMgr::GetInst()->GetMousePos()
#define CLONE(type) virtual type* Clone() { return new type(*this); }
#define CLONE_DEACTIVATE(type) virtual type* Clone() { assert(nullptr); return nullptr; }
#define TILE_SIZE 64
enum class LEVEL_TYPE
{
	DEBUG,
	START,
	NORMAL_STAGE_01,
	NORMAL_STAGE_02,
	NORMAL_STAGE_03,
	NORMAL_STAGE_04,
	TOWN,
	SQUIDSMITH,
	ONSEN,
	BOSS,
	EDITOR,
	END,
};
enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	BLACK,

	END,
};


enum class LAYER
{
	BACKGROUND,
	TILE,
	WALL,
	PLATFORM,
	CEILING,
	PLAYER,
	MONSTER,
	NPC,
	PLAYER_PROJECTILE,
	MONSTER_PROJECTILE,
	DEATH_LEFTOVER,
	FIELD_OBJ,
	DAMAGE,
	FORCE,
	
	HP,
	MONEY,
	MONEYNUM,
	PORTRAIT,
	PORTRAITNUM,
	DEFAULT,
	UI = 31,
	END = 32
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,	//	wParam : Object Adress   lParam : Layer Type
	DELETE_OBJECT,	//  wParam : Object Adress
	LEVEL_CHANGE,	//  wParam : LEVEL_TYPE(Next Level Type)
	CHANGE_AI_STATE, // wParam : AI Component Adress, lParam : Next State Name
};

enum class CAMERA_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
};

enum class PLAYER_ANIM
{
	IDLE,
	RUN,
	DUCK,
	JUMP,
	HAT,
	FALL,
	LAND,
	ATTACK,
	SHOOT,
	SCIMITAR,
	EAT,
	DRINK,
	ENTER,
	EXIT,
	TWIRL,

	NONE
};
enum class PLAYER_DIR
{
	LEFT = -1,
	RIGHT = 1,
	NONE
};
enum class PLAYER_STATE
{
	NORMAL,
	HIT,
	NONE
};

enum class F_OBJ
{
	HEART,
	NONE
};
