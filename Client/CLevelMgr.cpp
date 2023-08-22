#include "pch.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CDebugLevel.h"
#include "CStartLevel.h"
#include "CStage01Level.h"
#include "CStage02Level.h"
#include "CStage03Level.h"
#include "CTownLevel.h"
#include "COnsenLevel.h"
#include "CSquidSmithLevel.h"
#include "CBossLevel.h"
#include "CEditorLevel.h"
#include "CGalaga.h"


CLevelMgr::CLevelMgr()
	: m_arrLevel{}
	, m_pCurLevel(nullptr)
	
{
	
}

CLevelMgr::~CLevelMgr()
{
	for (int i = 0; i < (int)LEVEL_TYPE::END; ++i)
	{
		DEL(m_arrLevel[i]);
	}
}

void CLevelMgr::init()
{
	// Level 생성
	m_arrLevel[(UINT)LEVEL_TYPE::DEBUG] = new CDebugLevel;
	m_arrLevel[(UINT)LEVEL_TYPE::START] = new CStartLevel;
	m_arrLevel[(UINT)LEVEL_TYPE::NORMAL_STAGE_01] = new CStage01Level;
	m_arrLevel[(UINT)LEVEL_TYPE::NORMAL_STAGE_02] = new CStage02Level;
	m_arrLevel[(UINT)LEVEL_TYPE::NORMAL_STAGE_03] = new CStage03Level;
	//m_arrLevel[(UINT)LEVEL_TYPE::NORMAL_STAGE_04] = new CStage03Level;
	m_arrLevel[(UINT)LEVEL_TYPE::TOWN] = new CTownLevel;
	m_arrLevel[(UINT)LEVEL_TYPE::ONSEN] = new COnsenLevel;
	m_arrLevel[(UINT)LEVEL_TYPE::SQUIDSMITH] = new CSquidSmithLevel;
	m_arrLevel[(UINT)LEVEL_TYPE::BOSS] = new CBossLevel;

	m_arrLevel[(UINT)LEVEL_TYPE::EDITOR] = new CEditorLevel;
	m_pCurLevel = m_arrLevel[(UINT)LEVEL_TYPE::START];
	m_pCurLevel->Enter();
}

void CLevelMgr::tick()
{
	m_pCurLevel->tick();
	m_pCurLevel->final_tick();
}


void CLevelMgr::render(HDC _dc)
{
	m_pCurLevel->render(_dc);
}

void CLevelMgr::ChangeLevel(LEVEL_TYPE _eNext)
{
	// 현재 레벨과 변경하려는 레벨이 동일 한 경우
	assert(m_pCurLevel != m_arrLevel[(UINT)_eNext]);

	// 현재 레벨을 벗어남
	m_pCurLevel->Exit();

	m_pCurLevel = m_arrLevel[(UINT)_eNext];

	m_pCurLevel->Enter();
}