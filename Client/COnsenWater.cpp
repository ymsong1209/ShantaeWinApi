#include "pch.h"
#include "COnsenWater.h"
#include "CCollider.h"
#include "CResMgr.h"
#include "CPlayer.h"
#include "CHealEffect.h"
#include "CSound.h"
#include "CTimeMgr.h"


COnsenWater::COnsenWater()
	: m_fTime(0)
	, m_sound(nullptr)
{
	CreateCollider();
	m_sound = CResMgr::GetInst()->LoadSound(L"Heart", L"sound\\fx\\pickup_heart_small.wav");
	GetCollider()->SetScale(Vec2(600.f,135.f));
}

COnsenWater::~COnsenWater()
{
}

void COnsenWater::tick()
{
	m_fTime += DT;
	CObj::tick();
}

void COnsenWater::render(HDC _dc)
{
	CObj::render(_dc);
}

void COnsenWater::BeginOverlap(CCollider* _pOther)
{
}

void COnsenWater::OnOverlap(CCollider* _pOther)
{
	CPlayer* cPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (nullptr != cPlayer) {
		if (m_fTime > 1.0f) {
			if (cPlayer->ReturnHP() < cPlayer->ReturnMaxHP()) {
				CObj* pHeal = new CHealEffect(1);
				m_sound->Play(false);
				Vec2 vPos = Vec2(cPlayer->GetPos().x, cPlayer->GetPos().y - cPlayer->GetCollider()->GetScale().y);
				Instantiate(pHeal, vPos, LAYER::DAMAGE);
				cPlayer->SetHP(cPlayer->ReturnHP() + 1);
				cPlayer->UpdateHeartContainer();
				m_fTime = 0.f;
			}
		}
	}
}


