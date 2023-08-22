#include "pch.h"
#include "CScorpGalAttack.h"
#include "CTimeMgr.h"
#include "CScorpGal.h"
#include "CCollider.h"

CScorpGalAttack::CScorpGalAttack(CScorpGal* _pOwner)
	: m_pOwner(_pOwner)
	, m_fTime(0)
	, m_iDmg(0)
{
	m_iDmg = (int)m_pOwner->GetMonInfo().m_fAtt;
	CreateCollider();
	GetCollider()->SetScale(Vec2(336.f, 104.f));
}

CScorpGalAttack::~CScorpGalAttack()
{
}

void CScorpGalAttack::tick()
{
	//Vec2 pos = GetPos();

	//Vec2 prevpos = GetOwner()->GetPrevPos();
	//Vec2 curpos = GetOwner()->GetPos();
	//Vec2 diff = curpos - prevpos;

	////공격 도중 이동을 하면 그에 맞게 whip도 이동해야함
	//SetPos(Vec2(pos.x + diff.x, pos.y + diff.y));

	m_fTime += DT;
	if (0.4f < m_fTime) {
		SetDead();
	}
	CObj::tick();
}

void CScorpGalAttack::render(HDC _dc)
{
	CObj::render(_dc);
}
