#include "pch.h"
#include "CEditorLevel.h"

#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CEngine.h"
#include "CCamera.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CTile.h"

#include "CUI.h"
#include "CPanelUI.h"
#include "CButton.h"

#include "resource.h"

void CEditorLevel::init()
{
	// ī�޶� ����
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);
	//LoadBackground(L"boss", L"texture\\background\\fixed\\enhanced\\boss.bmp", Vec2(1600.f, 1069.f));
	//LoadBackground(L"outskirts2_enlarge", L"texture\\background\\fixed\\enhanced\\outskirts2_enlarge.bmp", Vec2(6272.f, 1876.f));
	LoadBackground(L"maze", L"texture\\background\\fixed\\enhanced\\maze.bmp", Vec2(3694.f, 1231.f));
	//LoadBackground(L"maze2", L"texture\\background\\fixed\\enhanced\\maze2.bmp", Vec2(3240.f, 1140.f));
	//LoadBackground(L"town", L"texture\\background\\fixed\\enhanced\\town.bmp", Vec2(4944.f, 1488.f));
	

	// UI ��ġ
	//CreateUI();



	// Ÿ���� ����� ��Ʋ�� �̹��� �ε�
	//CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"TileAtlas", L"texture\\TILE.bmp");

	// Ÿ�� ����
	CreateTile(1000, 1000);

	// �� Ÿ�Ͽ��ٰ� ����� ��Ʋ�� �̹�����, �̹��� �ε����� �������ش�.
	/*const vector<CObj*>& vecTile = GetLayer(LAYER::TILE);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->SetAtlas(pTex);
		((CTile*)vecTile[i])->SetImgIdx(0);
	}*/
}

void CEditorLevel::CreateUI()
{
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	
	// Button�� ����� �ؽ���
	CTexture* pButtonTex = CResMgr::GetInst()->LoadTexture(L"Button", L"texture\\button.bmp");
	CTexture* pButtonPressedTex = CResMgr::GetInst()->LoadTexture(L"Button_Pressed", L"texture\\button_pressed.bmp");
	CTexture* pPanelTex = CResMgr::GetInst()->LoadTexture(L"Panel", L"texture\\OakUI.bmp");

	// Panel UI
	CPanelUI* pPanelUI = new CPanelUI();
	pPanelUI->SetIdleTex(pPanelTex);
	pPanelUI->SetPos(Vec2(vResolution.x - (pPanelTex->Width() + 20.f), 10.f));

	// Tile Save ��ư
	CButton* pSaveTileBtn = new CButton;
	pSaveTileBtn->SetScale(Vec2(100.f, 50.f));
	Vec2 vUIPos = Vec2(10.f, 20.f);
	pSaveTileBtn->SetPos(vUIPos);
	pSaveTileBtn->SetDelegate(this, (DELEGATE)&CEditorLevel::SaveTile);
	pSaveTileBtn->SetIdleTex(pButtonTex);
	pSaveTileBtn->SetPressedTex(pButtonPressedTex);

	// Tile Load ��ư
	CButton* pLoadTileBtn = pSaveTileBtn->Clone();
	pLoadTileBtn->SetPos(Vec2(150.f, 20.f));
	pLoadTileBtn->SetDelegate(this, (DELEGATE)&CEditorLevel::LoadTile);

	// Save, Load ��ư�� Panel�� �ڽ����� �߰�
	pPanelUI->AddChildUI(pSaveTileBtn);
	pPanelUI->AddChildUI(pLoadTileBtn);

	// �θ��� Panel�� ���� UI���̾ ����ִ´�.
	AddObject(pPanelUI, LAYER::UI);

	//�Ȱ��� Panel �ϳ� ����
	CUI* pOtherPanelUI = pPanelUI->Clone();
	pOtherPanelUI->SetPos(Vec2(vResolution.x - (pPanelTex->Width() * 2.f + 20.f), 10.f));
	AddObject(pOtherPanelUI, LAYER::UI);
}

void CEditorLevel::CreateObjectUI() {
	Vec2 vResolution = CEngine::GetInst()->GetResolution();

	// Button�� ����� �ؽ���
	CTexture* pButtonTex_L = CResMgr::GetInst()->LoadTexture(L"Button_L", L"texture\\button_L.bmp");
	CTexture* pButtonTex_R = CResMgr::GetInst()->LoadTexture(L"Button_R", L"texture\\button_R.bmp");
	CTexture* pButtonPressedTex_L = CResMgr::GetInst()->LoadTexture(L"Button_Pressed_L", L"texture\\button_pressed.bmp");
	CTexture* pButtonPressedTex_R = CResMgr::GetInst()->LoadTexture(L"Button_Pressed_R", L"texture\\button_pressed.bmp");
	CTexture* pPanelTex = CResMgr::GetInst()->LoadTexture(L"Panel", L"texture\\OakUI.bmp");

	
	//// ��ǥ �̹���
	//CTexture* Fighter = CResMgr::GetInst()->LoadTexture(L"Fighter", L"texture\\Fighter.bmp");
	//CTexture* Bomb = CResMgr::GetInst()->LoadTexture(L"Bomb", L"texture\\Bomb.bmp");
	//m_mapObj.insert(make_pair(_strName, pAnim));

	//// Panel UI
	//CPanelUI* pPanelUI = new CPanelUI();
	//pPanelUI->SetIdleTex(pPanelTex);
	//pPanelUI->SetPos(Vec2(vResolution.x - (pPanelTex->Width() + 20.f), 10.f));

	//// �������� ���� ��ư
	//CButton* pSaveTileBtn = new CButton;
	//pSaveTileBtn->SetScale(Vec2(100.f, 50.f));
	//Vec2 vUIPos = Vec2(10.f, 20.f);
	//pSaveTileBtn->SetPos(vUIPos);
	//pSaveTileBtn->SetDelegate(this, (DELEGATE)&CEditorLevel::SaveTile);
	//pSaveTileBtn->SetIdleTex(pButtonTex);
	//pSaveTileBtn->SetPressedTex(pButtonPressedTex);
}