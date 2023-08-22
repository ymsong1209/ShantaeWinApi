#include "pch.h"
#include "GameInstance.h"
#include "CKeyMgr.h"

GameInstance::GameInstance()
	: m_bShowCollide(true)
{

}
GameInstance::~GameInstance() {

}

void GameInstance::tick() {
	if (IsTap(KEY::TAB)) {
		m_bShowCollide = !m_bShowCollide;
		//m_bRender = !m_bRender;
	}
}