#include "pch.h"
#include "CForceDuck.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CRigidbody.h"

CForceDuck::CForceDuck()
	: m_vLeftBottom()
	, m_vLeftTop()
	, m_vRightBottom()
	, m_vRightTop()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(400.f, 5.f));
	m_vLeftTop = Vec2(GetCollider()->GetFinalPos().x - GetCollider()->GetScale().x / 2, GetCollider()->GetFinalPos().y - GetCollider()->GetScale().y / 2);
	m_vLeftBottom = Vec2(GetCollider()->GetFinalPos().x - GetCollider()->GetScale().x / 2, GetCollider()->GetFinalPos().y + GetCollider()->GetScale().y / 2);
	m_vRightTop = Vec2(GetCollider()->GetFinalPos().x + GetCollider()->GetScale().x / 2, GetCollider()->GetFinalPos().y - GetCollider()->GetScale().y / 2);
	m_vRightBottom = Vec2(GetCollider()->GetFinalPos().x + GetCollider()->GetScale().x / 2, GetCollider()->GetFinalPos().y + GetCollider()->GetScale().y / 2);
}

CForceDuck::~CForceDuck()
{
}


void CForceDuck::BeginOverlap(CCollider* _pOther)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (nullptr == pPlayer)
		return;
	pPlayer->SetForceDuck(true);
}

void CForceDuck::OnOverlap(CCollider* _pOther)
{
	int a = 0;
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (nullptr == pPlayer)
		return;
	pPlayer->SetForceDuck(true);
}

void CForceDuck::EndOverlap(CCollider* _pOther)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (nullptr == pPlayer)
		return;
	pPlayer->SetForceDuck(false);
}
