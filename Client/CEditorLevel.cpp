#include "pch.h"
#include "CEditorLevel.h"

#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CEngine.h"
#include "CCamera.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CCollider.h"

#include "CTile.h"
#include "CButton.h"
#include "CUI.h"
#include "CPlatform.h"
#include "CCeiling.h"
#include "CWall.h"
#include "CHeart.h"
#include "CGem.h"
#include "CSquidHeart.h"

#include "CMonster.h"
#include "CBat.h"
#include "CScareCrow.h"
#include "CScorpGal.h"
#include "CCactus.h"
#include "CSquidBaron.h"

#include "resource.h"


CEditorLevel::CEditorLevel()
	: m_hMenu(nullptr)
	, m_eMode(EDITOR_MODE::PLATFORM)
	, m_EObj(FIELD_OBJ::HEART)
	, m_vLeftTop(0.f,0.f)
	, m_vSize(0.f,0.f)
	, m_ICurPlatform(0)
	, m_ICurWall(0)
	, m_ICurCeiling(0)
	, m_ICurMonster(0)
	, m_IMonsterNum(1)
	, m_IMaxMonsterNum(5)
	, m_vMousePos1{}
	, m_vMousePos2{}
	, m_bMousePos1active(false)
{
}

CEditorLevel::~CEditorLevel()
{
	if (nullptr != m_hMenu)
		DestroyMenu(m_hMenu);
}




void CEditorLevel::tick()
{
	CLevel::tick();
	
	if (IsTap(KEY::ENTER)) {
		ChangeLevel(LEVEL_TYPE::START);
	}
	if (IsTap(KEY::_1)) {
		//m_eMode = EDITOR_MODE::TILE;
		ChangeLevel(LEVEL_TYPE::DEBUG);
	}
	if (IsTap(KEY::_2)) {
		m_eMode = EDITOR_MODE::MONSTER;
		m_bMousePos1active = false;
		ReleaseIsChosen();
		//몬스터 첫번째 선택되게 만들기
		const vector<CObj*>& vecMonster = GetLayer(LAYER::MONSTER);
		if (vecMonster.begin() != vecMonster.end()) {
			((CMonster*)vecMonster[0])->SetChosen(true);
		}
	}
	if (IsTap(KEY::_3)) {
		m_eMode = EDITOR_MODE::OBJECT;
	}
	if (IsTap(KEY::_4)) {
		m_eMode = EDITOR_MODE::PLATFORM;
		m_bMousePos1active = false;
		ReleaseIsChosen();
		//플랫폼 첫번째 선택되게 만들기
		const vector<CObj*>& vecPlatform = GetLayer(LAYER::PLATFORM);
		if (vecPlatform.begin() != vecPlatform.end()) {
			((CPlatform*)vecPlatform[0])->SetChosen(true);
		}
	}
	if (IsTap(KEY::_5)) {
		m_eMode = EDITOR_MODE::WALL;
		m_bMousePos1active = false;
		ReleaseIsChosen();
		//첫번째 Wall 선택되게 만들기
		const vector<CObj*>& vecWall = GetLayer(LAYER::WALL);
		if (vecWall.begin() != vecWall.end()) {
			((CWall*)vecWall[0])->SetChosen(true);
		}
	}
	if (IsTap(KEY::_6)) {
		m_eMode = EDITOR_MODE::CEILING;
		m_bMousePos1active = false;
		ReleaseIsChosen();
		//첫번째 Wall 선택되게 만들기
		const vector<CObj*>& vecCeiling = GetLayer(LAYER::CEILING);
		if (vecCeiling.begin() != vecCeiling.end()) {
			((CCeiling*)vecCeiling[0])->SetChosen(true);
		}
	}
	

	if (IsTap(KEY::_0)) {
		m_eMode = EDITOR_MODE::NONE;
	}
	update();
}



void CEditorLevel::Enter()
{
	//메뉴바 생성
	if (nullptr == m_hMenu) {
		m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT));
	}
	HWND hWnd = CEngine::GetInst()->GetMainWnd();
	SetMenu(hWnd, m_hMenu);

	//메뉴바가 추가되었으므로 삐져나온만큼 해상도를 다시 재설정
	POINT ptResolution = CEngine::GetInst()->GetResolution();
	CEngine::GetInst()->ChangeWindowSize(ptResolution.x, ptResolution.y);

	//초기 오브젝트 설정
	init();

}

void CEditorLevel::Exit()
{
	//메뉴바 제거
	HWND hWnd = CEngine::GetInst()->GetMainWnd();
	SetMenu(hWnd, nullptr);
	//메뉴바가 없어졌으므로 메인 윈도우 크기를 늘린다.
	POINT ptResolution = CEngine::GetInst()->GetResolution();
	CEngine::GetInst()->ChangeWindowSize(ptResolution.x, ptResolution.y);


}

void CEditorLevel::update()
{
	switch (m_eMode)
	{
	case EDITOR_MODE::TILE:
		tile_update();
		break;
	case EDITOR_MODE::MONSTER:
		monster_update();
		break;
	case EDITOR_MODE::OBJECT:
		object_update();
		break;
	case EDITOR_MODE::PLATFORM:
		platform_update();
		break;
	case EDITOR_MODE::WALL:
		wall_update();
		break;
	case EDITOR_MODE::CEILING:
		ceiling_update();
		break;
	case EDITOR_MODE::NONE:
		break;
	default:
		break;
	}
}

void CEditorLevel::tile_update()
{
	if (IsTap(KEY::LBTN))
	{
		// 마우스 위치를 받아와서 실제좌표로 변환	
		Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);

		UINT iCol = (int)vMousePos.x / TILE_SIZE;
		UINT iRow = (int)vMousePos.y / TILE_SIZE;

		if (0.f <= vMousePos.x && iCol < GetTileXCount()
			&& 0.f <= vMousePos.y && iRow < GetTileYCount())
		{
			int iIdx = iRow * GetTileXCount() + iCol;
			const vector<CObj*>& vecTile = GetLayer(LAYER::TILE);
			((CTile*)vecTile[iIdx])->AddImgIdx();
		}
	}

	if (IsTap(KEY::_8))
	{
		SaveTile();
	}
	else if (IsTap(KEY::_9))
	{
		LoadTile();
	}
}

void CEditorLevel::animation_save()
{
	
}

void CEditorLevel::monster_update() {
	const vector<CObj*>& vecMonster = GetLayer(LAYER::MONSTER);
	// Monster 생성
	if (IsTap(KEY::LBTN))
	{
		// 마우스 위치를 받아와서 실제좌표로 변환	
		Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		if (m_IMonsterNum == 1) {
			CMonster* pBat = new CBat;
			Instantiate(pBat, vMousePos, LAYER::MONSTER);
		}
		else if (m_IMonsterNum == 2) {
			CMonster* pCactus = new CCactus;
			Instantiate(pCactus, vMousePos, LAYER::MONSTER);
		}
		else if (m_IMonsterNum == 3) {
			CMonster* pScareCrow = new CScareCrow;
			Instantiate(pScareCrow, vMousePos, LAYER::MONSTER);
		}
		else if (m_IMonsterNum == 4) {
			CMonster* pScorpGal = new CScorpGal;
			Instantiate(pScorpGal, vMousePos, LAYER::MONSTER);
		}
		else if (m_IMonsterNum == 5) {
			CMonster* pSquidBaron = new CSquidBaron;
			Instantiate(pSquidBaron, vMousePos, LAYER::MONSTER);
		}
	}
	//MonsterSpawn 위치 이동
	if (IsTap(KEY::RIGHT)) {
		Vec2 vPos = ((CMonster*)vecMonster[m_ICurMonster])->ReturnSpawnPos();
		((CMonster*)vecMonster[m_ICurMonster])->SetSpawnPos(Vec2(vPos.x + 1, vPos.y));
	}
	else if (IsTap(KEY::LEFT)) {
		Vec2 vPos = ((CMonster*)vecMonster[m_ICurMonster])->ReturnSpawnPos();
		((CMonster*)vecMonster[m_ICurMonster])->SetSpawnPos(Vec2(vPos.x - 1, vPos.y));
	}
	else if (IsTap(KEY::UP)) {
		Vec2 vPos = ((CMonster*)vecMonster[m_ICurMonster])->ReturnSpawnPos();
		((CMonster*)vecMonster[m_ICurMonster])->SetSpawnPos(Vec2(vPos.x, vPos.y - 1));
	}
	else if (IsTap(KEY::DOWN)) {
		Vec2 vPos = ((CMonster*)vecMonster[m_ICurMonster])->ReturnSpawnPos();
		((CMonster*)vecMonster[m_ICurMonster])->SetSpawnPos(Vec2(vPos.x, vPos.y + 1));
	}
	
	//다음 Monster로 이동
	if (IsTap(KEY::Z)) {
		((CMonster*)vecMonster[m_ICurMonster])->SetChosen(false);
		--m_ICurMonster;
		if (m_ICurMonster < 0) {
			m_ICurMonster = (int)vecMonster.size() - 1;
		}
		((CMonster*)vecMonster[m_ICurMonster])->SetChosen(true);
		CCamera::GetInst()->SetLook(Vec2(((CMonster*)vecMonster[m_ICurMonster])->GetPos().x, ((CMonster*)vecMonster[m_ICurMonster])->GetPos().y));
	}
	else if (IsTap(KEY::X)) {
		((CMonster*)vecMonster[m_ICurMonster])->SetChosen(false);
		++m_ICurMonster;
		if (m_ICurMonster >= (int)vecMonster.size()) {
			m_ICurMonster = 0;
		}
		((CMonster*)vecMonster[m_ICurMonster])->SetChosen(true);
		CCamera::GetInst()->SetLook(Vec2(((CMonster*)vecMonster[m_ICurMonster])->GetPos().x, ((CMonster*)vecMonster[m_ICurMonster])->GetPos().y));
	}
	//몬스터 종류 변경
	if (IsTap(KEY::PLUS)) {
		++m_IMonsterNum;
		if (m_IMonsterNum > m_IMaxMonsterNum) {
			m_IMonsterNum = 1;
		}
	}
	if (IsTap(KEY::MINUS)) {
		--m_IMonsterNum;
		if (m_IMonsterNum < 1) {
			m_IMonsterNum = m_IMaxMonsterNum;
		}
	}
	//몬스터 삭제
	if (IsTap(KEY::DELETEKEY)) {
		if (vecMonster.size() != 0) {
			((CMonster*)vecMonster[m_ICurMonster])->SetDead();
			--m_ICurMonster;
			if (m_ICurMonster <= 0)
			{
				m_ICurMonster = (int)vecMonster.size() - 2;
				if (vecMonster.size() == 1) {
					m_ICurMonster = 0;
				}
			}
			if (vecMonster.begin() != vecMonster.end()) {
				((CMonster*)vecMonster[m_ICurMonster])->SetChosen(true);
				CCamera::GetInst()->SetLook(Vec2(((CMonster*)vecMonster[m_ICurMonster])->GetPos().x, ((CMonster*)vecMonster[m_ICurMonster])->GetPos().y));
			}
		}

	}
	// 저장, 로드
	if (IsTap(KEY::_8))
	{
		((CMonster*)vecMonster[m_ICurMonster])->SetChosen(false);
		SaveWall();
	}
	else if (IsTap(KEY::_9))
	{
		LoadWall();
	}
}

void CEditorLevel::object_update()
{
	if (IsTap(KEY::LEFT))
	{
		(UINT)m_EObj;
		// 마우스 위치를 받아와서 실제좌표로 변환	
		Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);

		UINT iCol = (int)vMousePos.x / TILE_SIZE;
		UINT iRow = (int)vMousePos.y / TILE_SIZE;

		if (0.f <= vMousePos.x && iCol < GetTileXCount()
			&& 0.f <= vMousePos.y && iRow < GetTileYCount())
		{
			int iIdx = iRow * GetTileXCount() + iCol;
			const vector<CObj*>& vecTile = GetLayer(LAYER::TILE);
			((CTile*)vecTile[iIdx])->AddImgIdx();
		}
	}

	if (IsTap(KEY::_8))
	{
		SaveTile();
	}
	else if (IsTap(KEY::_9))
	{
		LoadTile();
	}
}

void CEditorLevel::wall_update()
{
	const vector<CObj*>& vecWall = GetLayer(LAYER::WALL);
	// Wall 생성
	if (IsTap(KEY::LBTN))
	{
		// 마우스 위치를 받아와서 실제좌표로 변환	
		Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		if (m_bMousePos1active == false) {
			m_vMousePos1 = vMousePos;
			m_bMousePos1active = true;
		}
		else if (m_bMousePos1active == true) {
			m_vMousePos2 = vMousePos;
			CWall* pWall = new CWall;
			if (m_vMousePos2.x > m_vMousePos1.x) {
				//좌측상단 -> 우측하단
				if (m_vMousePos2.y > m_vMousePos1.y) {
					Vec2 Scale = Vec2(m_vMousePos2.x - m_vMousePos1.x, m_vMousePos2.y - m_vMousePos1.y);
					Instantiate(pWall, Vec2(m_vMousePos1.x + Scale.x / 2, m_vMousePos1.y + Scale.y/2), LAYER::WALL);
					pWall->GetCollider()->SetScale(Scale);
					m_bMousePos1active = false;
				}
				//좌측하단 ->우측상단
				else if (m_vMousePos1.y > m_vMousePos2.y) {
					Vec2 Scale = Vec2(m_vMousePos2.x - m_vMousePos1.x, m_vMousePos1.y - m_vMousePos2.y);
					Instantiate(pWall, Vec2(m_vMousePos1.x + Scale.x / 2, m_vMousePos2.y + Scale.y / 2), LAYER::WALL);
					pWall->GetCollider()->SetScale(Scale);
					m_bMousePos1active = false;
				}
			}
			else if (m_vMousePos1.x > m_vMousePos2.x) {
				//우측 하단->좌측 상단
				if (m_vMousePos1.y > m_vMousePos2.y) {
					Vec2 Scale = Vec2(m_vMousePos1.x - m_vMousePos2.x, m_vMousePos1.y - m_vMousePos2.y);
					Instantiate(pWall, Vec2(m_vMousePos2.x + Scale.x / 2, m_vMousePos2.y + Scale.y / 2), LAYER::WALL);
					pWall->GetCollider()->SetScale(Scale);
					m_bMousePos1active = false;
				}
				//우측 상단->좌측 하단
				else if (m_vMousePos1.y < m_vMousePos2.y) {
					Vec2 Scale = Vec2(m_vMousePos1.x - m_vMousePos2.x, m_vMousePos2.y - m_vMousePos1.y);
					Instantiate(pWall, Vec2(m_vMousePos2.x + Scale.x / 2, m_vMousePos1.y + Scale.y / 2), LAYER::WALL);
					pWall->GetCollider()->SetScale(Scale);
					m_bMousePos1active = false;
				}
			}
		}
	}
	//Wall 위치 이동
	if (IsTap(KEY::RIGHT)) {
		Vec2 vPos = ((CWall*)vecWall[m_ICurWall])->GetPos();
		((CWall*)vecWall[m_ICurWall])->SetPos(Vec2(vPos.x + 1, vPos.y));
	}
	else if (IsTap(KEY::LEFT)) {
		Vec2 vPos = ((CWall*)vecWall[m_ICurWall])->GetPos();
		((CWall*)vecWall[m_ICurWall])->SetPos(Vec2(vPos.x - 1, vPos.y));
	}
	else if (IsTap(KEY::UP)) {
		Vec2 vPos = ((CWall*)vecWall[m_ICurWall])->GetPos();
		((CWall*)vecWall[m_ICurWall])->SetPos(Vec2(vPos.x, vPos.y - 1));
	}
	else if (IsTap(KEY::DOWN)) {
		Vec2 vPos = ((CWall*)vecWall[m_ICurWall])->GetPos();
		((CWall*)vecWall[m_ICurWall])->SetPos(Vec2(vPos.x, vPos.y + 1));
	}
	//Wall 크기 변경
	if (IsTap(KEY::PLUS))
	{
		Vec2 Scale = ((CWall*)vecWall[m_ICurWall])->GetCollider()->GetScale();
		Scale = Vec2(Scale.x + 1, Scale.y);
		((CWall*)vecWall[m_ICurWall])->GetCollider()->SetScale(Scale);
	}
	if (IsTap(KEY::MINUS))
	{
		Vec2 Scale = ((CWall*)vecWall[m_ICurWall])->GetCollider()->GetScale();
		Scale = Vec2(Scale.x - 1, Scale.y);
		((CWall*)vecWall[m_ICurWall])->GetCollider()->SetScale(Scale);
	}
	//다음 Wall 이동
	if (IsTap(KEY::Z)) {
		((CWall*)vecWall[m_ICurWall])->SetChosen(false);
		--m_ICurWall;
		if (m_ICurWall < 0) {
			m_ICurWall = (int)vecWall.size() - 1;
		}
		((CWall*)vecWall[m_ICurWall])->SetChosen(true);
		CCamera::GetInst()->SetLook(Vec2(((CWall*)vecWall[m_ICurWall])->GetPos().x, ((CWall*)vecWall[m_ICurWall])->GetPos().y));
	}
	else if (IsTap(KEY::X)) {
		((CWall*)vecWall[m_ICurWall])->SetChosen(false);
		++m_ICurWall;
		if (m_ICurWall >= (int)vecWall.size())
		{
			m_ICurWall = 0;
		}
		((CWall*)vecWall[m_ICurWall])->SetChosen(true);
		CCamera::GetInst()->SetLook(Vec2(((CWall*)vecWall[m_ICurWall])->GetPos().x, ((CWall*)vecWall[m_ICurWall])->GetPos().y));
	}
	//플랫폼 삭제
	if (IsTap(KEY::DELETEKEY)) {
		if (vecWall.size() != 0) {
			((CWall*)vecWall[m_ICurWall])->SetDead();
			--m_ICurWall;
			if (m_ICurWall <= 0)
			{
				m_ICurWall = (int)vecWall.size() - 2;
				if (vecWall.size() == 1) {
					m_ICurWall = 0;
				}
			}
			if (vecWall.begin() != vecWall.end()) {
				((CWall*)vecWall[m_ICurWall])->SetChosen(true);
				CCamera::GetInst()->SetLook(Vec2(((CWall*)vecWall[m_ICurWall])->GetPos().x, ((CWall*)vecWall[m_ICurWall])->GetPos().y));
			}
		}

	}
	// 저장, 로드
	if (IsTap(KEY::_8))
	{
		((CWall*)vecWall[m_ICurWall])->SetChosen(false);
		SaveWall();
	}
	else if (IsTap(KEY::_9))
	{
		LoadWall();
	}
}

void CEditorLevel::platform_update()
{
	const vector<CObj*>& vecPlatform = GetLayer(LAYER::PLATFORM);
	// 플랫폼 생성
	if (IsTap(KEY::LBTN))
	{
		// 마우스 위치를 받아와서 실제좌표로 변환	
		Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		if (m_bMousePos1active == false) {
			m_vMousePos1 = vMousePos;
			m_bMousePos1active = true;
		}
		else if (m_bMousePos1active == true) {
			m_vMousePos2 = vMousePos;
			CPlatform* pPlatform = new CPlatform;
			if (m_vMousePos2.x > m_vMousePos1.x) {
				Vec2 Scale = Vec2(m_vMousePos2.x - m_vMousePos1.x, 5.f);
				Instantiate(pPlatform, Vec2(m_vMousePos1.x + Scale.x / 2, m_vMousePos2.y), LAYER::PLATFORM);
				pPlatform->GetCollider()->SetScale(Scale);
				m_bMousePos1active = false;
			}
			else if (m_vMousePos1.x > m_vMousePos2.x) {
				Vec2 Scale = Vec2(m_vMousePos1.x - m_vMousePos2.x, 5.f);
				Instantiate(pPlatform, Vec2(m_vMousePos2.x + Scale.x / 2, m_vMousePos2.y), LAYER::PLATFORM);
				pPlatform->GetCollider()->SetScale(Scale);
				m_bMousePos1active = false;
			}
		}
	}
	//플랫폼 위치 이동
	if (IsTap(KEY::RIGHT)) {
		Vec2 vPos = ((CPlatform*)vecPlatform[m_ICurPlatform])->GetPos();
		((CPlatform*)vecPlatform[m_ICurPlatform])->SetPos(Vec2(vPos.x + 1, vPos.y));
	}
	else if (IsTap(KEY::LEFT)) {
		Vec2 vPos = ((CPlatform*)vecPlatform[m_ICurPlatform])->GetPos();
		((CPlatform*)vecPlatform[m_ICurPlatform])->SetPos(Vec2(vPos.x - 1, vPos.y));
	}
	else if (IsTap(KEY::UP)) {
		Vec2 vPos = ((CPlatform*)vecPlatform[m_ICurPlatform])->GetPos();
		((CPlatform*)vecPlatform[m_ICurPlatform])->SetPos(Vec2(vPos.x, vPos.y - 1));
	}
	else if (IsTap(KEY::DOWN)) {
		Vec2 vPos = ((CPlatform*)vecPlatform[m_ICurPlatform])->GetPos();
		((CPlatform*)vecPlatform[m_ICurPlatform])->SetPos(Vec2(vPos.x, vPos.y + 1));
	}
	//플랫폼 크기 변경
	if (IsTap(KEY::PLUS))
	{
		Vec2 Scale = ((CPlatform*)vecPlatform[m_ICurPlatform])->GetCollider()->GetScale();
		Scale = Vec2(Scale.x + 1, Scale.y);
		((CPlatform*)vecPlatform[m_ICurPlatform])->GetCollider()->SetScale(Scale);
	}
	if (IsTap(KEY::MINUS))
	{
		Vec2 Scale = ((CPlatform*)vecPlatform[m_ICurPlatform])->GetCollider()->GetScale();
		Scale = Vec2(Scale.x - 1, Scale.y);
		((CPlatform*)vecPlatform[m_ICurPlatform])->GetCollider()->SetScale(Scale);
	}
	//다음 플랫폼으로 이동
	if (IsTap(KEY::Z)) {
		((CPlatform*)vecPlatform[m_ICurPlatform])->SetChosen(false);
		--m_ICurPlatform;
		if (m_ICurPlatform < 0) {
			m_ICurPlatform = (int)vecPlatform.size() - 1;
		}
		((CPlatform*)vecPlatform[m_ICurPlatform])->SetChosen(true);
		CCamera::GetInst()->SetLook(Vec2(((CPlatform*)vecPlatform[m_ICurPlatform])->GetPos().x, ((CPlatform*)vecPlatform[m_ICurPlatform])->GetPos().y));
	}
	else if (IsTap(KEY::X)) {
		((CPlatform*)vecPlatform[m_ICurPlatform])->SetChosen(false);
		++m_ICurPlatform;
		if (m_ICurPlatform >= (int)vecPlatform.size())
		{
			m_ICurPlatform = 0;
		}
		((CPlatform*)vecPlatform[m_ICurPlatform])->SetChosen(true);
		CCamera::GetInst()->SetLook(Vec2(((CPlatform*)vecPlatform[m_ICurPlatform])->GetPos().x, ((CPlatform*)vecPlatform[m_ICurPlatform])->GetPos().y));
	}
	//플랫폼 삭제
	if (IsTap(KEY::DELETEKEY)) {
		if (vecPlatform.size()!= 0) {
			((CPlatform*)vecPlatform[m_ICurPlatform])->SetDead();
			--m_ICurPlatform;
			if (m_ICurPlatform <= 0)
			{
				m_ICurPlatform = (int)vecPlatform.size() - 2;
				if (vecPlatform.size() == 1) {
					m_ICurPlatform = 0;
				}
			}
			if (vecPlatform.begin() != vecPlatform.end()) {
				((CPlatform*)vecPlatform[m_ICurPlatform])->SetChosen(true);
				CCamera::GetInst()->SetLook(Vec2(((CPlatform*)vecPlatform[m_ICurPlatform])->GetPos().x, ((CPlatform*)vecPlatform[m_ICurPlatform])->GetPos().y));
			}
		}
		
	}
	// 저장, 로드
	if (IsTap(KEY::_8))
	{
		((CPlatform*)vecPlatform[m_ICurPlatform])->SetChosen(false);
		SavePlatform();
	}
	else if (IsTap(KEY::_9))
	{
		LoadPlatform();
	}
}

void CEditorLevel::ceiling_update() {
	const vector<CObj*>& vecCeiling = GetLayer(LAYER::CEILING);
	// 플랫폼 생성
	if (IsTap(KEY::LBTN))
	{
		// 마우스 위치를 받아와서 실제좌표로 변환	
		Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		if (m_bMousePos1active == false) {
			m_vMousePos1 = vMousePos;
			m_bMousePos1active = true;
		}
		else if (m_bMousePos1active == true) {
			m_vMousePos2 = vMousePos;
			CCeiling* pCeiling = new CCeiling;
			if (m_vMousePos2.x > m_vMousePos1.x) {
				Vec2 Scale = Vec2(m_vMousePos2.x - m_vMousePos1.x, 5.f);
				Instantiate(pCeiling, Vec2(m_vMousePos1.x + Scale.x/2, m_vMousePos2.y), LAYER::CEILING);
				pCeiling->GetCollider()->SetScale(Scale);
				m_bMousePos1active = false;
			}
			else if (m_vMousePos1.x > m_vMousePos2.x) {
				Vec2 Scale = Vec2(m_vMousePos1.x - m_vMousePos2.x, 5.f);
				Instantiate(pCeiling, Vec2(m_vMousePos2.x + Scale.x / 2, m_vMousePos2.y), LAYER::CEILING);
				pCeiling->GetCollider()->SetScale(Scale);
				m_bMousePos1active = false;
			}
		}
	}
	//플랫폼 위치 이동
	if (IsTap(KEY::RIGHT)) {
		Vec2 vPos = ((CCeiling*)vecCeiling[m_ICurCeiling])->GetPos();
		((CCeiling*)vecCeiling[m_ICurCeiling])->SetPos(Vec2(vPos.x + 1, vPos.y));
	}
	else if (IsTap(KEY::LEFT)) {
		Vec2 vPos = ((CCeiling*)vecCeiling[m_ICurCeiling])->GetPos();
		((CCeiling*)vecCeiling[m_ICurCeiling])->SetPos(Vec2(vPos.x - 1, vPos.y));
	}
	else if (IsTap(KEY::UP)) {
		Vec2 vPos = ((CCeiling*)vecCeiling[m_ICurCeiling])->GetPos();
		((CCeiling*)vecCeiling[m_ICurCeiling])->SetPos(Vec2(vPos.x, vPos.y - 1));
	}
	else if (IsTap(KEY::DOWN)) {
		Vec2 vPos = ((CCeiling*)vecCeiling[m_ICurCeiling])->GetPos();
		((CCeiling*)vecCeiling[m_ICurCeiling])->SetPos(Vec2(vPos.x, vPos.y + 1));
	}
	//플랫폼 크기 변경
	if (IsTap(KEY::PLUS))
	{
		Vec2 Scale = ((CCeiling*)vecCeiling[m_ICurCeiling])->GetCollider()->GetScale();
		Scale = Vec2(Scale.x + 1, Scale.y);
		((CCeiling*)vecCeiling[m_ICurCeiling])->GetCollider()->SetScale(Scale);
	}
	if (IsTap(KEY::MINUS))
	{
		Vec2 Scale = ((CCeiling*)vecCeiling[m_ICurCeiling])->GetCollider()->GetScale();
		Scale = Vec2(Scale.x - 1, Scale.y);
		((CCeiling*)vecCeiling[m_ICurCeiling])->GetCollider()->SetScale(Scale);
	}
	//다음 플랫폼으로 이동
	if (IsTap(KEY::Z)) {
		((CCeiling*)vecCeiling[m_ICurCeiling])->SetChosen(false);
		--m_ICurCeiling;
		if (m_ICurCeiling < 0) {
			m_ICurCeiling = (int)vecCeiling.size() - 1;
		}
		((CCeiling*)vecCeiling[m_ICurCeiling])->SetChosen(true);
		CCamera::GetInst()->SetLook(Vec2(((CCeiling*)vecCeiling[m_ICurCeiling])->GetPos().x, ((CCeiling*)vecCeiling[m_ICurCeiling])->GetPos().y));
	}
	else if (IsTap(KEY::X)) {
		((CCeiling*)vecCeiling[m_ICurCeiling])->SetChosen(false);
		++m_ICurCeiling;
		if (m_ICurCeiling >= (int)vecCeiling.size())
		{
			m_ICurCeiling = 0;
		}
		((CCeiling*)vecCeiling[m_ICurCeiling])->SetChosen(true);
		CCamera::GetInst()->SetLook(Vec2(((CCeiling*)vecCeiling[m_ICurCeiling])->GetPos().x, ((CCeiling*)vecCeiling[m_ICurCeiling])->GetPos().y));
	}
	//플랫폼 삭제
	if (IsTap(KEY::DELETEKEY)) {
		if (vecCeiling.size() != 0) {
			((CCeiling*)vecCeiling[m_ICurCeiling])->SetDead();
			--m_ICurCeiling;
			if (m_ICurCeiling <= 0)
			{
				m_ICurCeiling = (int)vecCeiling.size() - 2;
				if (vecCeiling.size() == 1) {
					m_ICurCeiling = 0;
				}
			}
			if (vecCeiling.begin() != vecCeiling.end()) {
				((CCeiling*)vecCeiling[m_ICurCeiling])->SetChosen(true);
				CCamera::GetInst()->SetLook(Vec2(((CCeiling*)vecCeiling[m_ICurCeiling])->GetPos().x, ((CCeiling*)vecCeiling[m_ICurCeiling])->GetPos().y));
			}
		}

	}
	// 저장, 로드
	if (IsTap(KEY::_8))
	{
		((CCeiling*)vecCeiling[m_ICurCeiling])->SetChosen(false);
		SaveCeiling();
	}
	else if (IsTap(KEY::_9))
	{
		LoadCeiling();
	}
}

//----------------Tile----------------//

void CEditorLevel::SaveTile()
{
	// open a file name
	OPENFILENAME ofn = {};

	//파일 저장 시 창이 뜨게 하는 코드
	wstring strTileFolderPath = CPathMgr::GetInst()->GetContentPath();
	strTileFolderPath += L"tile\\";

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetSaveFileName(&ofn))
		return;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"wb");

	// 타일 개로 세로 개수 저장
	UINT iTileXCount = GetTileXCount();
	UINT iTileYCount = GetTileYCount();

	fwrite(&iTileXCount, sizeof(UINT), 1, pFile);
	fwrite(&iTileYCount, sizeof(UINT), 1, pFile);



	// 각각의 타일 정보 저장
	const vector<CObj*>& vecTile = GetLayer(LAYER::TILE);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile);
}

void CEditorLevel::LoadTile()
{
	// open a file name
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = CPathMgr::GetInst()->GetContentPath();
	strTileFolderPath += L"tile\\";

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetOpenFileName(&ofn))
		return;


	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"rb");

	// 타일 개로 세로 개수 읽기
	UINT iTileXCount = 0, iTileYCount = 0;

	fread(&iTileXCount, sizeof(UINT), 1, pFile);
	fread(&iTileYCount, sizeof(UINT), 1, pFile);

	// 읽은 개수에 맞게 다시 타일 배치
	CreateTile(iTileXCount, iTileYCount);

	// 배치한 각각의 타일들을 데이터 읽도록
	const vector<CObj*>& vecTile = GetLayer(LAYER::TILE);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Load(pFile);
	}

	fclose(pFile);
}
//----------------Platform----------------//
void CEditorLevel::SavePlatform() {
	// open a file name
	OPENFILENAME ofn = {};

	//파일 저장 시 창이 뜨게 하는 코드
	wstring strTileFolderPath = CPathMgr::GetInst()->GetContentPath();
	strTileFolderPath += L"platform\\";

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"Platform\0*.platform\0ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetSaveFileName(&ofn))
		return;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"wb");

	const vector<CObj*>& vecPlatform = GetLayer(LAYER::PLATFORM);

	// Platform개수 저장
	int PlatformCount = (int)vecPlatform.size();
	fwprintf_s(pFile, L"[PLATFORM_COUNT]\n");
	fwprintf_s(pFile, L"%d\n", PlatformCount);
	//fwrite(&PlatformCount, sizeof(int), 1, pFile);
	
	// 각각의 타일 정보 저장
	//const vector<CObj*>& vecPlatform = GetLayer(LAYER::PLATFORM);
	for (size_t i = 0; i < vecPlatform.size(); ++i)
	{
		((CPlatform*)vecPlatform[i])->Save(pFile);
	}

	fclose(pFile);
}

void CEditorLevel::LoadPlatform() {
	m_ICurPlatform = 0;
	// open a file name
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = CPathMgr::GetInst()->GetContentPath();
	strTileFolderPath += L"platform\\";

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"Platform\0*.platform\0ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetOpenFileName(&ofn))
		return;


	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"rb");

	//플랫폼 개수 읽기
	int platformCount = 0;
	wchar_t szBuffer[256] = {};
	fwscanf_s(pFile, L"%s", szBuffer, 256);
	if (!wcscmp(szBuffer, L"[PLATFORM_COUNT]"))
	{
		fwscanf_s(pFile, L"%d", &platformCount);
	}
		

	// 읽은 개수에 맞게 다시 플랫폼 배치
	CreatePlatform(platformCount);
	

	// 배치한 각각의 플랫폼의 데이터 읽도록
	const vector<CObj*>& vecTile = GetLayer(LAYER::PLATFORM);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CPlatform*)vecTile[i])->Load(pFile, (int)i);
	}
	if (vecTile.begin() != vecTile.end()) {
		((CPlatform*)vecTile[0])->SetChosen(true);
	}
	
	fclose(pFile);
}

void CEditorLevel::SaveWall()
{
	// open a file name
	OPENFILENAME ofn = {};

	//파일 저장 시 창이 뜨게 하는 코드
	wstring strTileFolderPath = CPathMgr::GetInst()->GetContentPath();
	strTileFolderPath += L"wall\\";

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"Wall\0*.wall\0ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetSaveFileName(&ofn))
		return;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"wb");

	const vector<CObj*>& vecWall = GetLayer(LAYER::WALL);

	// Wall개수 저장
	int PlatformCount = (int)vecWall.size();
	fwprintf_s(pFile, L"[WALL_COUNT]\n");
	fwprintf_s(pFile, L"%d\n", PlatformCount);
	//fwrite(&PlatformCount, sizeof(int), 1, pFile);

	// 각각의 타일 정보 저장
	//const vector<CObj*>& vecPlatform = GetLayer(LAYER::PLATFORM);
	for (size_t i = 0; i < vecWall.size(); ++i)
	{
		((CWall*)vecWall[i])->Save(pFile);
	}

	fclose(pFile);
}

void CEditorLevel::LoadWall()
{
	m_ICurWall = 0;
	// open a file name
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = CPathMgr::GetInst()->GetContentPath();
	strTileFolderPath += L"wall\\";

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"Wall\0*.wall\0ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetOpenFileName(&ofn))
		return;


	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"rb");

	//플랫폼 개수 읽기
	int wallCount = 0;
	wchar_t szBuffer[256] = {};
	fwscanf_s(pFile, L"%s", szBuffer, 256);
	if (!wcscmp(szBuffer, L"[WALL_COUNT]"))
	{
		fwscanf_s(pFile, L"%d", &wallCount);
	}


	// 읽은 개수에 맞게 다시 플랫폼 배치
	CreateWall(wallCount);

	// 배치한 각각의 플랫폼의 데이터 읽도록
	const vector<CObj*>& vecWall = GetLayer(LAYER::WALL);
	for (size_t i = 0; i < vecWall.size(); ++i)
	{
		((CWall*)vecWall[i])->Load(pFile, (int)i);
	}
	if (vecWall.begin() != vecWall.end()) {
		((CWall*)vecWall[0])->SetChosen(true);
	}

	fclose(pFile);
}

void CEditorLevel::SaveCeiling()
{
	// open a file name
	OPENFILENAME ofn = {};

	//파일 저장 시 창이 뜨게 하는 코드
	wstring strTileFolderPath = CPathMgr::GetInst()->GetContentPath();
	strTileFolderPath += L"ceiling\\";

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"Ceiling\0*.ceiling\0ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetSaveFileName(&ofn))
		return;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"wb");

	const vector<CObj*>& vecCeiling = GetLayer(LAYER::CEILING);

	// Ceiling개수 저장
	int CeilingCount = (int)vecCeiling.size();
	fwprintf_s(pFile, L"[CEILING_COUNT]\n");
	fwprintf_s(pFile, L"%d\n", CeilingCount);
	//fwrite(&PlatformCount, sizeof(int), 1, pFile);

	// 각각의 타일 정보 저장
	//const vector<CObj*>& vecPlatform = GetLayer(LAYER::PLATFORM);
	for (size_t i = 0; i < vecCeiling.size(); ++i)
	{
		((CCeiling*)vecCeiling[i])->Save(pFile);
	}

	fclose(pFile);
}

void CEditorLevel::LoadCeiling()
{
	m_ICurCeiling = 0;
	// open a file name
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = CPathMgr::GetInst()->GetContentPath();
	strTileFolderPath += L"ceiling\\";

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"Ceiling\0*.ceiling\0ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetOpenFileName(&ofn))
		return;


	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"rb");

	//플랫폼 개수 읽기
	int ceilingCount = 0;
	wchar_t szBuffer[256] = {};
	fwscanf_s(pFile, L"%s", szBuffer, 256);
	if (!wcscmp(szBuffer, L"[CEILING_COUNT]"))
	{
		fwscanf_s(pFile, L"%d", &ceilingCount);
	}


	// 읽은 개수에 맞게 다시 플랫폼 배치
	CreateCeiling(ceilingCount);


	// 배치한 각각의 플랫폼의 데이터 읽도록
	const vector<CObj*>& vecCeiling = GetLayer(LAYER::CEILING);
	for (size_t i = 0; i < vecCeiling.size(); ++i)
	{
		((CCeiling*)vecCeiling[i])->Load(pFile, (int)i);
	}
	if (vecCeiling.begin() != vecCeiling.end()) {
		((CCeiling*)vecCeiling[0])->SetChosen(true);
	}

	fclose(pFile);
}

void CEditorLevel::SaveMonster() {

}

void CEditorLevel::LoadMonster() {

}




// ======================
// Tile Count Dialog Proc
// ======================
INT_PTR CALLBACK TileCount(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);


	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			// Edit Control 에 입력된 숫자를 받아온다.
			
			int iTileXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, true);
			int iTileYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, true);

			if (!(iTileXCount && iTileYCount))
			{
				MessageBox(nullptr, L"타일 개수를 지정하세요", L"타일 생성 오류", MB_OK);
				return (INT_PTR)TRUE;
			}

			// 지정된 수치로 타일을 새로 생성시킨다.
			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
			pCurLevel->CreateTile(iTileXCount, iTileYCount);

			// 각 타일에다가 사용할 아틀라스 이미지와, 이미지 인덱스를 세팅해준다.
			CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"TileAtlas", L"texture\\TILE.bmp");

			const vector<CObj*>& vecTile = pCurLevel->GetLayer(LAYER::TILE);
			for (size_t i = 0; i < vecTile.size(); ++i)
			{
				((CTile*)vecTile[i])->SetAtlas(pTex);
				((CTile*)vecTile[i])->SetImgIdx(0);
			}
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK PlatformEdit(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);


	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			int XSize = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, true);
			int YSize = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, true);
			if (!(XSize && YSize))
			{
				MessageBox(nullptr, L"Platform사이즈를 지정하세요", L"Platform 설정 오류", MB_OK);
				return (INT_PTR)TRUE;
			}
			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
			const vector<CObj*>& vecPlatform = pCurLevel->GetLayer(LAYER::PLATFORM);
			if (vecPlatform.begin() == vecPlatform.end()) {
				break;
			}
			EDITOR_MODE m_eMode = ((CEditorLevel*)pCurLevel)->ReturnMode();
			if (m_eMode == EDITOR_MODE::PLATFORM) {
				// Edit Control 에 입력된 숫자를 받아온다.
				int curplat = ((CEditorLevel*)pCurLevel)->ReturnCurPlatform();
				
				((CPlatform*)vecPlatform[curplat])->GetCollider()->SetScale(Vec2((float)XSize, (float)YSize));
				
			}
			
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK PlatformPosChange(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);


	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			int XSize = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, true);
			int YSize = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, true);
			if (!(XSize && YSize))
			{
				MessageBox(nullptr, L"Platform위치를 지정하세요", L"Platform 설정 오류", MB_OK);
				return (INT_PTR)TRUE;
			}
			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
			const vector<CObj*>& vecPlatform = pCurLevel->GetLayer(LAYER::PLATFORM);
			if (vecPlatform.begin() == vecPlatform.end()) {
				break;
			}
			EDITOR_MODE m_eMode = ((CEditorLevel*)pCurLevel)->ReturnMode();
			if (m_eMode == EDITOR_MODE::PLATFORM) {
				// Edit Control 에 입력된 숫자를 받아온다.
				int curplat = ((CEditorLevel*)pCurLevel)->ReturnCurPlatform();

				((CPlatform*)vecPlatform[curplat])->SetPos(Vec2((float)XSize, (float)YSize));

			}

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK WallEdit(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);


	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			int XSize = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, true);
			int YSize = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, true);
			if (!(XSize && YSize))
			{
				MessageBox(nullptr, L"Wall사이즈를 지정하세요", L"Wall 설정 오류", MB_OK);
				return (INT_PTR)TRUE;
			}
			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
			const vector<CObj*>& vecWall = pCurLevel->GetLayer(LAYER::WALL);
			if (vecWall.begin() == vecWall.end()) {
				break;
			}
			EDITOR_MODE m_eMode = ((CEditorLevel*)pCurLevel)->ReturnMode();
			if (m_eMode == EDITOR_MODE::WALL) {
				// Edit Control 에 입력된 숫자를 받아온다.
				int curWall = ((CEditorLevel*)pCurLevel)->ReturnCurWall();

				((CPlatform*)vecWall[curWall])->GetCollider()->SetScale(Vec2((float)XSize, (float)YSize));

			}

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK WallPosChange(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);


	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			int XSize = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, true);
			int YSize = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, true);
			if (!(XSize && YSize))
			{
				MessageBox(nullptr, L"Wall위치를 지정하세요", L"Wall 설정 오류", MB_OK);
				return (INT_PTR)TRUE;
			}
			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
			const vector<CObj*>& vecWall = pCurLevel->GetLayer(LAYER::WALL);
			if (vecWall.begin() == vecWall.end()) {
				break;
			}
			EDITOR_MODE m_eMode = ((CEditorLevel*)pCurLevel)->ReturnMode();
			if (m_eMode == EDITOR_MODE::WALL) {
				// Edit Control 에 입력된 숫자를 받아온다.
				int curwall = ((CEditorLevel*)pCurLevel)->ReturnCurWall();

				((CPlatform*)vecWall[curwall])->SetPos(Vec2((float)XSize, (float)YSize));

			}

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK CeilingEdit(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);


	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			int XSize = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, true);
			int YSize = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, true);
			if (!(XSize && YSize))
			{
				MessageBox(nullptr, L"Ceiling사이즈를 지정하세요", L"Ceiling 설정 오류", MB_OK);
				return (INT_PTR)TRUE;
			}
			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
			const vector<CObj*>& vecCeiling = pCurLevel->GetLayer(LAYER::CEILING);
			if (vecCeiling.begin() == vecCeiling.end()) {
				break;
			}
			EDITOR_MODE m_eMode = ((CEditorLevel*)pCurLevel)->ReturnMode();
			if (m_eMode == EDITOR_MODE::CEILING) {
				// Edit Control 에 입력된 숫자를 받아온다.
				int curplat = ((CEditorLevel*)pCurLevel)->ReturnCurCeiling();

				((CCeiling*)vecCeiling[curplat])->GetCollider()->SetScale(Vec2((float)XSize, (float)YSize));

			}

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK CeilingPosChange(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);


	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			int XSize = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, true);
			int YSize = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, true);
			if (!(XSize && YSize))
			{
				MessageBox(nullptr, L"Ceiling위치를 지정하세요", L"Ceiling 설정 오류", MB_OK);
				return (INT_PTR)TRUE;
			}
			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
			const vector<CObj*>& vecCeiling = pCurLevel->GetLayer(LAYER::CEILING);
			if (vecCeiling.begin() == vecCeiling.end()) {
				break;
			}
			EDITOR_MODE m_eMode = ((CEditorLevel*)pCurLevel)->ReturnMode();
			if (m_eMode == EDITOR_MODE::CEILING) {
				// Edit Control 에 입력된 숫자를 받아온다.
				int curplat = ((CEditorLevel*)pCurLevel)->ReturnCurCeiling();

				((CCeiling*)vecCeiling[curplat])->SetPos(Vec2((float)XSize, (float)YSize));

			}

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}