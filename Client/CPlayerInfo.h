#pragma once

class CPlayerInfo 
{
public:
	SINGLE(CPlayerInfo);
private:
	PLAYER_ANIM		m_Eanim;
	PLAYER_DIR		m_Edir;
	PLAYER_STATE	m_Estate;
	int				m_iHP;
	int				m_iMaxHp;
	int				m_iWhipDmg;
	int				m_iPistolDmg;
	int				m_iScimitarDmg;
	int				m_iWhipExtraDmg;
	int				m_iPistolExtraDmg;
	int				m_iScimitarExtraDmg;
	int				m_iMoney;
	int				m_iSquidHeart;
	int				m_iMeat;
	int				m_iMonsterMilk;
	int				m_iPikeBall;
	bool			m_bSpawnChange;
	Vec2			m_vSpawnPos;

public:

	void SetAnim(PLAYER_ANIM _manim) { m_Eanim = _manim; }
	PLAYER_ANIM ReturnAnim() { return m_Eanim; }
		
	void SetDir(PLAYER_DIR _mDir) { m_Edir = _mDir; }
	PLAYER_DIR ReturnDir() { return m_Edir; }

	void SetState(PLAYER_STATE _mState) { m_Estate = _mState; }
	PLAYER_STATE ReturnState() { return m_Estate; }

	void SetHP(int _mHP) { m_iHP = _mHP; }
	int ReturnHP() { return m_iHP; }

	void SetMaxHP(int _mMaxHp) { m_iMaxHp = _mMaxHp; }
	int ReturnMaxHP() { return m_iMaxHp; }

	void SetWhipDmg(int _mAttack) { m_iWhipDmg = _mAttack; }
	int ReturnWhipDmg() { return m_iWhipDmg; }

	void SetPistolDmg(int _mAttack) { m_iPistolDmg = _mAttack; }
	int ReturnPistolDmg() { return m_iPistolDmg; }

	void SetScimitarDmg(int _mAttack) { m_iScimitarDmg = _mAttack; }
	int ReturnScimitarDmg() { return m_iScimitarDmg; }

	void SetWhipExtraDmg(int _mExtraDmg) { m_iWhipExtraDmg = _mExtraDmg; }
	int ReturnWhipExtraDmg() { return m_iWhipExtraDmg; }

	void SetPistolExtraDmg(int _mExtraDmg) { m_iPistolExtraDmg = _mExtraDmg; }
	int ReturnPistolExtraDmg() { return m_iPistolExtraDmg; }

	void SetScimitarExtraDmg(int _mExtraDmg) { m_iScimitarExtraDmg = _mExtraDmg; }
	int ReturnScimitarExtraDmg() { return m_iScimitarExtraDmg; }

	void SetMoney(int _mMoney) { m_iMoney = _mMoney; }
	int ReturnMoney() { return m_iMoney; }

	void SetSquidHeart(int _miHeart) { m_iSquidHeart = _miHeart; }
	int ReturnSquidHeart() { return m_iSquidHeart; }

	void SetMonsterMilk(int _mMilk) { m_iMonsterMilk = _mMilk; }
	int ReturnMonsterMilk() { return m_iMonsterMilk; }

	void SetPikeBall(int _mPikeBall) { m_iPikeBall = _mPikeBall; }
	int ReturnPikeBall() { return m_iPikeBall; }

	void SetMeat(int _mMeat) { m_iMeat = _mMeat; }
	int ReturnMeat() { return m_iMeat; }

	void SetSpawnChange(bool _Change) { m_bSpawnChange = _Change; }
	bool ReturnSpawnChange() { return m_bSpawnChange; }

	void SetSpawnPos(Vec2 _vPos) { m_vSpawnPos = _vPos; }
	Vec2 ReturnSpawnPos() { return m_vSpawnPos; }

};

