#include "pch.h"
#include "CWall.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CRigidbody.h"
#include "CPlatform.h"

CWall::CWall()
	: m_vLeftBottom()
	, m_vLeftTop()
	, m_vRightBottom()
	, m_vRightTop()
	, m_cPlatform(nullptr)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(400.f, 500.f));
	m_vLeftTop = Vec2(GetCollider()->GetFinalPos().x - GetCollider()->GetScale().x / 2, GetCollider()->GetFinalPos().y - GetCollider()->GetScale().y / 2);
	m_vLeftBottom = Vec2(GetCollider()->GetFinalPos().x - GetCollider()->GetScale().x / 2, GetCollider()->GetFinalPos().y + GetCollider()->GetScale().y / 2);
	m_vRightTop = Vec2(GetCollider()->GetFinalPos().x + GetCollider()->GetScale().x / 2, GetCollider()->GetFinalPos().y - GetCollider()->GetScale().y / 2);
	m_vRightBottom = Vec2(GetCollider()->GetFinalPos().x + GetCollider()->GetScale().x / 2, GetCollider()->GetFinalPos().y + GetCollider()->GetScale().y / 2);

	/*m_cPlatform = new CPlatform();
	Vec2 m_vPlatScale = m_cPlatform->GetCollider()->GetScale();
	Vec2 m_vPos = GetCollider()->GetFinalPos();
	Vec2 m_vScale = GetCollider()->GetScale();
	m_cPlatform->GetCollider()->SetScale(Vec2(m_vScale.x, m_vPlatScale.y));
	m_cPlatform->SetPos(Vec2(m_vPos.x - m_vScale.x / 2, m_vPos.y - m_vScale.y / 2));
	Instantiate(m_cPlatform, GetCollider()->GetFinalPos(), LAYER::PLATFORM);*/
}

CWall::~CWall()
{
}

void CWall::render(HDC _dc)
{
	if (GetChosen()) {
		TCHAR str[100];
		TCHAR str2[100];
		TCHAR str3[100];
		Vec2 vPos = GetPos();
		Vec2 vRealPos = CCamera::GetInst()->GetRenderPos(vPos);
		Vec2 Scale = GetCollider()->GetScale();
		wsprintf(str, TEXT("X : %d, Y : %d"), (int)vPos.x, (int)vPos.y);
		wsprintf(str2, TEXT("X Scale : %d, Y Scale : %d"), (int)Scale.x, (int)Scale.y);
		wsprintf(str3, TEXT("Wall"));
		TextOut(_dc, (int)vRealPos.x, (int)vRealPos.y, str, lstrlen(str));
		TextOut(_dc, (int)vRealPos.x, (int)vRealPos.y + 30, str2, lstrlen(str2));
		TextOut(_dc, (int)vRealPos.x, (int)vRealPos.y + 60, str3, lstrlen(str3));
	}
	CObj::render(_dc);
}


void CWall::Save(FILE* _pFile)
{

	// Wall 이름 저장
	fwprintf_s(_pFile, L"\n");
	fwprintf_s(_pFile, L"[WALL]\n");

	// 위치
	Vec2 vPos = GetPos();
	fwprintf_s(_pFile, L"[POS]\n");
	fwprintf_s(_pFile, L"%.1f %.1f\n", vPos.x, vPos.y);

	// SIZE
	Vec2 vScale = GetCollider()->GetScale();
	fwprintf_s(_pFile, L"[SIZE]\n");
	fwprintf_s(_pFile, L"%.1f %.1f\n", vScale.x, vScale.y);

	fwprintf_s(_pFile, L"\n");
	//fclose(_pFile);

}
void CWall::Load(FILE* _pFile, int _PlatformCount)
{
	wchar_t szBuffer[256] = {};

	while (true) {
		fwscanf_s(_pFile, L"%s", szBuffer, 256);
		if (!wcscmp(szBuffer, L"[POS]"))
		{
			Vec2 vPos;
			fwscanf_s(_pFile, L"%f %f", &vPos.x, &vPos.y);
			SetPos(vPos);
		}
		else if (!wcscmp(szBuffer, L"[SIZE]"))
		{
			Vec2 vScale;
			fwscanf_s(_pFile, L"%f %f", &vScale.x, &vScale.y);
			GetCollider()->SetScale(vScale);
			break;
		}
	}



}



void CWall::BeginOverlap(CCollider* _pOther)
{

}

void CWall::OnOverlap(CCollider* _pOther)
{
	//플레이어는 바깥으로 밀어냄

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (nullptr == pPlayer)
		return;
	pPlayer->SetPos(pPlayer->GetPrevPos());

	//플레이어가 오른쪽에서 들어왔을 경우
	if (pPlayer->GetPos().x > GetPos().x) {
		/*Vec2 pVel = pPlayer->GetRigidbody()->GetVelocity();
		if (pPlayer->GetRigidbody()->GetVelocity().x < 0) {
			pPlayer->GetRigidbody()->AddVelocity(Vec2(-pVel.x, 0));
		}
		else {
			Vec2 vPlayerPos = pPlayer->GetPos();
			pPlayer->SetPos(Vec2(vPlayerPos.x + 1, vPlayerPos.y));
		}*/
		Vec2 vPlayerPos = pPlayer->GetPos();
		pPlayer->SetPos(Vec2(vPlayerPos.x + 1, vPlayerPos.y));
					
	}
	//플레이어가 왼쪽에서 들어왔을 경우
	else if (pPlayer->GetPos().x < GetPos().x) {
		/*Vec2 pVel = pPlayer->GetRigidbody()->GetVelocity();
		if (pPlayer->GetRigidbody()->GetVelocity().x > 0) {
			pPlayer->GetRigidbody()->AddVelocity(Vec2(-pVel.x, 0));
		}
		else {
			Vec2 vPlayerPos = pPlayer->GetPos();
			pPlayer->SetPos(Vec2(vPlayerPos.x - 1, vPlayerPos.y));
		}*/
		Vec2 vPlayerPos = pPlayer->GetPos();
		pPlayer->SetPos(Vec2(vPlayerPos.x - 1, vPlayerPos.y));
		
	}
	//몬스터도 바깥으로 밀어냄
	CMonster* pMonster = dynamic_cast<CMonster*>(_pOther->GetOwner());
	if (nullptr == pMonster)
		return;
	pMonster->SetPos(pMonster->GetPrevPos());

	//몬스터가 오른쪽에서 들어왔을 경우
	if (pMonster->GetPos().x > GetPos().x) {
		Vec2 vMonsterPos = pMonster->GetPos();
		pMonster->SetPos(Vec2(vMonsterPos.x + 1, vMonsterPos.y));

	}
	//몬스터가 왼쪽에서 들어왔을 경우
	else if (pMonster->GetPos().x < GetPos().x) {
		Vec2 vMonsterPos = pMonster->GetPos();
		pMonster->SetPos(Vec2(vMonsterPos.x - 1, vMonsterPos.y));

	}

}

void CWall::EndOverlap(CCollider* _pOther)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (nullptr == pPlayer)
		return;
	
}