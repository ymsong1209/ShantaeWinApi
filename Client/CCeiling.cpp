#include "pch.h"
#include "CCeiling.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CRigidbody.h"
#include "CMonster.h"

CCeiling::CCeiling()
{
	SetPos(Vec2(0.f, 0.f));
	CreateCollider();
	GetCollider()->SetScale(Vec2(400.f, 5.f));
}

CCeiling::~CCeiling()
{
}



void CCeiling::render(HDC _dc)
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
		wsprintf(str3, TEXT("Ceiling"));
		TextOut(_dc, (int)vRealPos.x, (int)vRealPos.y, str, lstrlen(str));
		TextOut(_dc, (int)vRealPos.x, (int)vRealPos.y + 30, str2, lstrlen(str2));
		TextOut(_dc, (int)vRealPos.x, (int)vRealPos.y + 60, str3, lstrlen(str3));
	}
	CObj::render(_dc);
}

void CCeiling::Save(FILE* _pFile)
{
	// Platform 이름 저장
	fwprintf_s(_pFile, L"\n");
	fwprintf_s(_pFile, L"[CEILING]\n");
	//fwprintf_s(_pFile, GetName().c_str());
	//fwprintf_s(_pFile, L"\n\n");

	// 위치
	Vec2 vPos = GetPos();
	fwprintf_s(_pFile, L"[POS]\n");
	fwprintf_s(_pFile, L"%.1f %.1f\n", vPos.x, vPos.y);

	// SIZE
	Vec2 vScale = GetCollider()->GetScale();
	fwprintf_s(_pFile, L"[SIZE]\n");
	fwprintf_s(_pFile, L"%.1f %.1f\n", vScale.x, vScale.y);

	fwprintf_s(_pFile, L"\n");
}

void CCeiling::Load(FILE* _pFile, int _PlatformCount)
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

void CCeiling::BeginOverlap(CCollider* _pOther)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (nullptr != pPlayer) {
		Vec2 vPlayerPos = pPlayer->GetPos();
		Vec2 vPlayerVelocity = pPlayer->GetRigidbody()->GetVelocity();
		pPlayer->GetRigidbody()->SetVelocity(Vec2(vPlayerVelocity.x, 0.f));
		pPlayer->SetPos(Vec2(vPlayerPos.x, vPlayerPos.y + 1));
	}

	CMonster* pMonster = dynamic_cast<CMonster*>(_pOther->GetOwner());
	if (nullptr != pMonster) {
		Vec2 vMonsterPos = pMonster->GetPos();
		pMonster->SetPos(Vec2(vMonsterPos.x, vMonsterPos.y+1));
	}
}

void CCeiling::OnOverlap(CCollider* _pOther)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (nullptr != pPlayer) {
		Vec2 vPlayerPos = pPlayer->GetPos();
		pPlayer->SetPos(Vec2(vPlayerPos.x, vPlayerPos.y + 1));
	}

	CMonster* pMonster = dynamic_cast<CMonster*>(_pOther->GetOwner());
	if (nullptr != pMonster) {
		Vec2 vMonsterPos = pMonster->GetPos();
		pMonster->SetPos(Vec2(vMonsterPos.x, vMonsterPos.y + 1));
	}
}

void CCeiling::EndOverlap(CCollider* _pOther)
{
}

