#include "pch.h"
#include "CPlayerInfo.h"



CPlayerInfo::CPlayerInfo()
	: m_Eanim(PLAYER_ANIM::NONE)
	, m_Edir(PLAYER_DIR::NONE)
	, m_Estate(PLAYER_STATE::NONE)
	, m_iHP(2)
	, m_iMaxHp(8)
	, m_iWhipDmg(5)
	, m_iScimitarDmg(4)
	, m_iPistolDmg(1)
	, m_iWhipExtraDmg(4)
	, m_iScimitarExtraDmg(3)
	, m_iPistolExtraDmg(1)
	, m_iMoney(456)
	, m_iSquidHeart(4)
	, m_iMeat(5)
	, m_iMonsterMilk(5)
	, m_iPikeBall(5)
	, m_bSpawnChange(false)
	, m_vSpawnPos{}
{

}
CPlayerInfo::~CPlayerInfo() {
   
}
