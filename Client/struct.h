#pragma once

struct Vec2
{
	float x;
	float y;


public:
	bool IsZero()
	{
		return x == 0.f && y == 0.f;
	}

	void Normalize() // ����ȭ
	{
		float fDist = sqrtf(x * x + y * y);
		x /= fDist;
		y /= fDist;
	}
	float Length()
	{
		return sqrtf(x * x + y * y);
	}



	Vec2 operator +(Vec2 _vOther)
	{
		return Vec2(x + _vOther.x, y + _vOther.y);
	}

	void operator += (Vec2 _vOther)
	{
		x += _vOther.x;
		y += _vOther.y;
	}

	Vec2 operator -(Vec2 _vOther)
	{
		return Vec2(x - _vOther.x, y - _vOther.y);
	}

	void operator -= (Vec2 _vOther)
	{
		x -= _vOther.x;
		y -= _vOther.y;
	}
	Vec2 operator -()
	{
		return Vec2(-x, -y);
	}

	Vec2 operator / (float _f)
	{
		return Vec2(x / _f, y / _f);
	}

	void operator /= (float _f)
	{
		x /= _f;
		y /= _f;
	}



	Vec2 operator / (Vec2 _vOther)
	{
		return Vec2(x / _vOther.x, y / _vOther.y);
	}

	void operator /= (Vec2 _vOther)
	{
		x /= _vOther.x;
		y /= _vOther.y;
	}
	Vec2 operator * (Vec2 _vOther)
	{
		return Vec2(x * _vOther.x, y * _vOther.y);
	}

	Vec2 operator * (float _f)
	{
		return Vec2(x * _f, y * _f);
	}

	void operator *= (float _f)
	{
		x *= _f;
		y *= _f;
	}

	bool operator != (Vec2 _vOther)
	{
		return (x != _vOther.x) || (y != _vOther.y);
	}

	bool operator == (Vec2 _vOther)
	{
		return (x == _vOther.x) && (y == _vOther.y);
	}




public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{}

	Vec2(float _x, float _y)
		: x(_x), y(_y)
	{}

	Vec2(UINT _x, UINT _y)
		: x((float)_x), y((float)_y)
	{}

	Vec2(POINT _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{

	}

	~Vec2()
	{}
};


struct tEvent
{
	EVENT_TYPE	eType;
	DWORD_PTR	wParam;
	DWORD_PTR	lParam;
};
struct tAnimFrm
{
	Vec2	vLeftTop;	// �̹��� ������ �������� �»�� ��ġ
	Vec2	vSize;		// ������ ������
	Vec2	vSpace;		// ������ ������ ����
	Vec2	vOffset;	// �߰� �̵�
	float	fDuration;	// �ش� ������ ���� �ð�
	bool	iMirror;	// true�Ͻ� ����, false�Ͻ� ����
};

struct tMonsterInfo
{
	int	m_iHP;
	int	m_iMaxHP;
	int m_iGemValue;

	float	m_fAtt;
	float	m_fDef;
	float	m_fAgi;

	float	m_fSpeed;
	float	m_fDetectRange;
	float	m_fAttRange;
	float   m_fPatrolRange;
	
	bool	m_bIsLeft;


	float	m_fTime;
	float	m_fAttackFinalDist;
	int		m_iSquidAnger;
	bool	m_bIsPhase1;
	bool	m_bIsArmored;
	int		m_iWallHit;
	bool	m_bBannerSpawn;
	int		m_iGobbleCount;
	bool	m_bJumpPoint1;
	bool	m_bJumpPoint2;
	bool	m_bJumpPoint3;
	bool	m_bDeathIntensify;
};

