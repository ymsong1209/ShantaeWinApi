#include "pch.h"
#include "CPlayer.h"
#include "CEngine.h"
#include "CResMgr.h"
#include "CLevelMgr.h"
#include "CTexture.h"
#include "CLevel.h"
#include "CHeartContainer.h"
#include "CPanelUI.h"
#include "CUI.h"
#include "CMoneyUI.h"
#include "CMoneyNum.h"
#include "CItemPortrait.h"
#include "CItemNum.h"

void CPlayer::CreateHeartContainer() {
	

	//기존 UI
	CLevelMgr::GetInst()->GetCurLevel()->DeleteObject(LAYER::HP);
	Vec2 StartPos = Vec2(20.f, 20.f);
	Vec2 Space = Vec2(20.f, 0.f);
	
	//지정된 가로 세로 숫자에 맞추어 타일 배치
	for (UINT iRow = 0; iRow < m_iMaxHp/4; ++iRow) {
		if (iRow == 2) {
			int a = 0;
		}
		CObj* cheart = new CHeartContainer(0);
		Vec2 size = ((CHeartContainer*)cheart)->ReturnSize();
		Vec2 pos = Vec2(size.x * iRow + StartPos.x + Space.x * iRow, StartPos.y);
		Instantiate(cheart, pos, LAYER::HP);
	}
}
void CPlayer::UpdateHeartContainer() {
	//기존 UI
	CLevelMgr::GetInst()->GetCurLevel()->DeleteObject(LAYER::HP);
	Vec2 StartPos = Vec2(20.f, 20.f);
	Vec2 Space = Vec2(20.f, 0.f);

	//지정된 가로 세로 숫자에 맞추어 타일 배치
	for (UINT iRow = 0; iRow < m_iHP / 4; ++iRow) {
		if (iRow == 2) {
			int a = 0;
		}
		CObj* cheart = new CHeartContainer(0);
		Vec2 size = ((CHeartContainer*)cheart)->ReturnSize();
		Vec2 pos = Vec2(size.x * iRow + StartPos.x + Space.x * iRow, StartPos.y);
		Instantiate(cheart, pos, LAYER::HP);
	}
	if (m_iHP % 4 > 0) {
		CObj* cheart = new CHeartContainer(4 - m_iHP%4);
		Vec2 size = ((CHeartContainer*)cheart)->ReturnSize();
		Vec2 pos = Vec2(size.x * (m_iHP / 4) + StartPos.x + Space.x * (m_iHP /4) , StartPos.y);
		Instantiate(cheart, pos, LAYER::HP);
		for (UINT iRow = 0; iRow < (m_iMaxHp - m_iHP) / 4; ++iRow) {
			CObj* cheart = new CHeartContainer(4);
			Vec2 size = ((CHeartContainer*)cheart)->ReturnSize();
			Vec2 pos = Vec2(size.x * (iRow + (m_iHP / 4 + 1)) + StartPos.x + Space.x * (iRow + (m_iHP/4 + 1)), StartPos.y);
			Instantiate(cheart, pos, LAYER::HP);
		}
	}
	else if (m_iHP % 4 == 0) {
		for (UINT iRow = 0; iRow < (m_iMaxHp - m_iHP) / 4; ++iRow) {
			CObj* cheart = new CHeartContainer(4);
			Vec2 size = ((CHeartContainer*)cheart)->ReturnSize();
			Vec2 pos = Vec2(size.x * (iRow + m_iHP / 4) + StartPos.x  + Space.x * (iRow + (m_iHP / 4)), StartPos.y);
			Instantiate(cheart, pos, LAYER::HP);
		}
	}
	
}
void CPlayer::UpdateMoney() {

	Vec2 vResolution = CEngine::GetInst()->GetResolution();

	//CTexture* number = 
	CLevelMgr::GetInst()->GetCurLevel()->DeleteObject(LAYER::MONEY);
	CMoneyUI* MoneyUI = new CMoneyUI(this);
	Instantiate(MoneyUI, Vec2(vResolution.x - MoneyUI->ReturnSize().x , 10.f), LAYER::MONEY);
	CLevelMgr::GetInst()->GetCurLevel()->DeleteObject(LAYER::MONEYNUM);
	int num = ReturnMoney() / 100;
	CMoneyNum* moneynum1 = new CMoneyNum(num);
	Instantiate(moneynum1, Vec2(MoneyUI->GetPos().x + 190.f, 20.f), LAYER::MONEYNUM);
	int num2 = (ReturnMoney() - num*100) / 10;
	CMoneyNum* moneynum2 = new CMoneyNum(num2);
	Instantiate(moneynum2, Vec2(MoneyUI->GetPos().x + 260.f, 20.f), LAYER::MONEYNUM);
	int num3 = (ReturnMoney() - num*100 - num2*10);
	CMoneyNum* moneynum3 = new CMoneyNum(num3);
	Instantiate(moneynum3, Vec2(MoneyUI->GetPos().x + 330.f, 20.f), LAYER::MONEYNUM);
	
}

void CPlayer::UpdateItem() {

	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CItemPortrait* cPortrait = new CItemPortrait(this);
	Instantiate(cPortrait, Vec2(vResolution.x - cPortrait->ReturnSize().x, 105.f), LAYER::PORTRAIT);
	CLevelMgr::GetInst()->GetCurLevel()->DeleteObject(LAYER::PORTRAITNUM);
	int num = m_iMeatCount;
	CItemNum* itemnum1 = new CItemNum(num);
	Instantiate(itemnum1, Vec2(cPortrait->GetPos().x + 92.f, 187.f), LAYER::PORTRAITNUM);

	int num2 = m_iMonsterMilkCount;
	CItemNum* itemnum2 = new CItemNum(num2);
	Instantiate(itemnum2, Vec2(cPortrait->GetPos().x + 210.f, 187.f), LAYER::PORTRAITNUM);

	int num3 = m_iPikeBallCount;
	CItemNum* itemnum3 = new CItemNum(num3);
	Instantiate(itemnum3, Vec2(cPortrait->GetPos().x + 330.f, 187.f), LAYER::PORTRAITNUM);


}