#include "pch.h"
#include "CForce.h"
#include "CTimeMgr.h"
#include "CEngine.h"
#include "CLevel.h"
#include "CLevelMgr.h"
#include "CRigidbody.h"


CForce::CForce()
	: m_fAccTime(0.f)
	, m_fLifeTime(0.f)
	, m_fForce(0.f)
	, m_fRadius(0.f)
{

}

CForce::~CForce()
{
}

void CForce::tick()
{
	m_fAccTime += DT;
	if (m_fAccTime > m_fLifeTime) {
		SetDead();
		return;
	}

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	const vector<CObj*> vecPlayerLayer = pCurLevel->GetLayer(LAYER::PLAYER);

	for (size_t i = 0; i < vecPlayerLayer.size(); ++i) {
		if (vecPlayerLayer[i]->GetRigidbody() == nullptr)
			continue;
		//Force -> Player�� ���ϴ� ����
		Vec2 vForceDir = vecPlayerLayer[i]->GetPos() - GetPos();
		//Force�� Player ������ �Ÿ�
		float fDistance = vForceDir.Length();

		//float fRatio = 1.f - (fDistance / m_fRadius)
		//Saturate(fRatio); // 0 ���� 1 ���� ����
		float fRatio = cosf((fDistance / m_fRadius) * PI * 0.5f);
		Saturate(fRatio); // 0 ���� 1 ���� ����

		// Force ���� �÷��̸� ���ؼ� �� ���� ũ��
		vForceDir.Normalize();
		vForceDir *= m_fForce * fRatio;

		vecPlayerLayer[i]->GetRigidbody()->AddForce(vForceDir);
	}

}

void CForce::render(HDC _dc)
{
	HPEN hGreenPen = CEngine::GetInst()->GetPen(PEN_TYPE::GREEN);
	HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	// DC �� ���� ��� �귯�ø� ���� ������ �͵�� ��ü�Ѵ�
	HPEN hOriginPen = (HPEN)SelectObject(_dc, hGreenPen);
	HBRUSH hOriginBrush = (HBRUSH)SelectObject(_dc, hNullBrush);

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	// �簢�� �׸���
	Ellipse(_dc
		, (int)(vPos.x - m_fRadius)
		, (int)(vPos.y - m_fRadius)
		, (int)(vPos.x + m_fRadius)
		, (int)(vPos.y + m_fRadius));

	// DC �� GDI ������Ʈ���� ������ ��� �귯�÷� �ǵ�����.
	SelectObject(_dc, hOriginPen);
	SelectObject(_dc, hOriginBrush);
}