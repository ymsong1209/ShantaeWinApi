#include "pch.h"
#include "CPlatform.h"

#include "CPlayer.h"
#include "CCollider.h"
#include "CRigidbody.h"
#include "CMonster.h"

CPlatform::CPlatform()
	/*: m_vLeftBottom()
	, m_vLeftTop()
	, m_vRightBottom()
	, m_vRightTop()*/
{
	SetPos(Vec2(0.f, 0.f));
	CreateCollider();
	GetCollider()->SetScale(Vec2(400.f, 5.f));
	/*m_vLeftTop = Vec2(GetCollider()->GetFinalPos().x - GetCollider()->GetScale().x / 2, GetCollider()->GetFinalPos().y - GetCollider()->GetScale().y / 2);
	m_vLeftBottom = Vec2(GetCollider()->GetFinalPos().x - GetCollider()->GetScale().x / 2, GetCollider()->GetFinalPos().y + GetCollider()->GetScale().y / 2);
	m_vRightTop = Vec2(GetCollider()->GetFinalPos().x + GetCollider()->GetScale().x / 2, GetCollider()->GetFinalPos().y - GetCollider()->GetScale().y / 2);
	m_vRightBottom = Vec2(GetCollider()->GetFinalPos().x + GetCollider()->GetScale().x / 2, GetCollider()->GetFinalPos().y + GetCollider()->GetScale().y / 2);*/
}

CPlatform::~CPlatform()
{
}

void CPlatform::render(HDC _dc)
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
		wsprintf(str3, TEXT("Platform"));
		TextOut(_dc, (int)vRealPos.x, (int)vRealPos.y, str, lstrlen(str));
		TextOut(_dc, (int)vRealPos.x, (int)vRealPos.y + 30, str2, lstrlen(str2));
		TextOut(_dc, (int)vRealPos.x, (int)vRealPos.y + 60, str3, lstrlen(str3));
	
	}
	CObj::render(_dc);
}

void CPlatform::Save(FILE* _pFile)
{

	// Platform 이름 저장
	fwprintf_s(_pFile, L"\n");
	fwprintf_s(_pFile, L"[PLATFORM]\n");
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
	//fclose(_pFile);

}
void CPlatform::Load(FILE* _pFile, int _PlatformCount)
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

void CPlatform::BeginOverlap(CCollider* _pOther)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (nullptr != pPlayer) {
		if (pPlayer->ReturnAnim() != PLAYER_ANIM::JUMP) {
			if (pPlayer->ReturnAnim() == PLAYER_ANIM::FALL) {
				if (pPlayer->GetPos().y - pPlayer->GetCollider()->GetScale().y / 2 <= GetCollider()->GetFinalPos().y) {
					pPlayer->GetRigidbody()->SetGround(true);
				}
			}
			else {
				pPlayer->GetRigidbody()->SetGround(true);
			}
			
		}
	}

	CMonster* pMonster = dynamic_cast<CMonster*>(_pOther->GetOwner());
	if (nullptr != pMonster) {
		pMonster->GetRigidbody()->SetGround(true);
	}
	
}

void CPlatform::OnOverlap(CCollider* _pOther)
{
	int a = 0;
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (nullptr != pPlayer) {
		if (pPlayer->ReturnAnim() != PLAYER_ANIM::JUMP) {
			if (pPlayer->GetRigidbody()->GetGround() == false) {
				if (pPlayer->GetPos().y <= GetCollider()->GetFinalPos().y) {
					pPlayer->GetRigidbody()->SetGround(true);
				}
			}
			else {
				if (pPlayer->GetPos().y > GetCollider()->GetFinalPos().y - GetCollider()->GetScale().y / 2) {
					float pos = GetCollider()->GetFinalPos().y - pPlayer->GetPos().y;
					pPlayer->SetPos(Vec2(pPlayer->GetPos().x, GetCollider()->GetFinalPos().y - GetCollider()->GetScale().y / 2));
				}
			}
			
		}
	}
	
	CMonster* pMonster = dynamic_cast<CMonster*>(_pOther->GetOwner());
	if (nullptr != pMonster) {
		if (pMonster->GetRigidbody()->GetGround() == false) pMonster->GetRigidbody()->SetGround(true);
		//Monster가 중력을 사용한다면 위로 보내기
		if (pMonster->GetRigidbody()->GetGravityUse()) {
			if (pMonster->GetPos().y > GetCollider()->GetFinalPos().y - GetCollider()->GetScale().y / 2) {
				float pos = GetCollider()->GetFinalPos().y - pMonster->GetPos().y;
				pMonster->SetPos(Vec2(pMonster->GetPos().x, GetCollider()->GetFinalPos().y - GetCollider()->GetScale().y / 2));
			}
		}
	}
	
	
}

void CPlatform::EndOverlap(CCollider* _pOther)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (nullptr != pPlayer) {
		pPlayer->GetRigidbody()->SetGround(false);
	}

	CMonster* pMonster = dynamic_cast<CMonster*>(_pOther->GetOwner());
	if (nullptr != pMonster) {
		pMonster->GetRigidbody()->SetGround(false);
	}
}

	
