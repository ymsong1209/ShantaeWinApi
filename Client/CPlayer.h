#pragma once
#include "CObj.h"

class CTexture;

class CPlayer :
    public CObj
{
private:
    float           m_fSpeed;//속력(scalar)
    CTexture* pShantaeTex;
    CTexture* pShantaeTex_R;
    PLAYER_ANIM     m_EAnim;
    PLAYER_ANIM     m_EPrevAnim;
    PLAYER_DIR      m_EDir;
    PLAYER_DIR      m_EPrevDir;
    PLAYER_STATE    m_EState;
    PLAYER_STATE    m_EPrevState;
    float           m_fTime;
    int             m_iHP;
    int             m_iMaxHp;
    int             m_iWhipDmg;
    int             m_iPistolDmg;
    int             m_iScimitarDmg;
    int             m_iWhipExtraDmg;
    int             m_iPistolExtraDmg;
    int             m_iScimitarExtraDmg;
    int             m_iMeatCount;
    int             m_iMonsterMilkCount;
    int             m_iPikeBallCount;
    bool            m_bMonsterMilk;
    bool            m_bPikeBall;
    float           m_fExtraDmgTime;
    int             m_iMoney;
    int             m_iSquidHeart;
    float           m_fAttvoiceCooldown;
   
    bool            m_bInvincible;
    float           m_fInvincibleTime;
    // 일어서지 못하게 하는 bool
    bool            m_bForceDuck;
    // knockdown을 위한 bool값
    bool            m_bHitAir;
    // attack을 위한 bool값
    bool            m_bAttack;
    // 1tick 넘기기 위한 bool값
    bool            m_btick;
    // 카메라 고정, 카메라 자유
    bool            m_bCamerafollow;
    //강제 무적
    bool            m_bforceinvincible;
    
    bool            m_bSpawnChange;
    Vec2            m_vSpawnPos;
   
   
   
public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
   
    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;
    virtual void EndOverlap(CCollider* _pOther) override;
    

    void CreateAnimation();
    void CreateHeartContainer();
    void UpdateHeartContainer();
    void UpdateMoney();
    void UpdateItem();
    
    void SetAnim(PLAYER_ANIM _anim) { m_EAnim = _anim; }
    void SetbTick(bool _bool) { m_btick = _bool; }
    PLAYER_ANIM ReturnAnim() { return m_EAnim; }
    PLAYER_ANIM ReturnPrevAnim() { return m_EPrevAnim; }
    PLAYER_STATE ReturnState() { return m_EState; }
   
    void Update();
public:
    CLONE(CPlayer);
public:
    void SetSpeed(float _f){m_fSpeed = _f;}

    PLAYER_DIR ReturnDir() { return m_EDir; }

    void SetHP(int _mHP) { m_iHP = _mHP; }
    int ReturnHP() { return m_iHP; }

    void SetMaxHP(int _mMaxHp) { m_iMaxHp = _mMaxHp; }
    int ReturnMaxHP() { return m_iMaxHp; }

    void SetWhipDmg(int _mAttack) { m_iWhipDmg = _mAttack; }
    int ReturnWhipDmg() { return m_iWhipDmg; }

    void SetPistolDmg(int _mAttack) { m_iPistolDmg = _mAttack; }
    int ReturnPistolDmg() { return m_iPistolDmg; }

    void SetScimitar(int _mAttack) { m_iScimitarDmg = _mAttack; }
    int ReturScimitarDmg() { return m_iScimitarDmg; }

    bool ReturnIsMonsterMilk() { return m_bMonsterMilk; }
    bool ReturnIsPikeBall() { return m_bPikeBall; }
    void SetIsPikeBall(bool _mbPikeball) { m_bPikeBall = _mbPikeball; }

    void SetWhipExtraDmg(int _mAttack) { m_iWhipExtraDmg = _mAttack; }
    int ReturnWhipExtraDmg() { return m_iWhipExtraDmg; }

    void SetPistolExtraDmg(int _mAttack) { m_iPistolExtraDmg = _mAttack; }
    int ReturnPistolExtraDmg() { return m_iPistolExtraDmg; }

    void SetScimitarExtraDmg(int _mAttack) { m_iScimitarExtraDmg = _mAttack; }
    int ReturScimitarExtraDmg() { return m_iScimitarExtraDmg; }

    void SetForceDuck(bool _bForceDuck) { m_bForceDuck = _bForceDuck; }

    void SetMoney(int _mMoney) { m_iMoney = _mMoney; }
    int ReturnMoney() { return m_iMoney; }

    void SetSquidHeart(int _mSquidHeart) { m_iSquidHeart = _mSquidHeart; }
    int ReturnSquidHeart() { return m_iSquidHeart; }

    void SetCameraFollow(bool _follow) { m_bCamerafollow = _follow; }
    int ReturnCameraFollow() { return m_bCamerafollow; }

    void SetSpawnPos(Vec2 _vPos) { m_vSpawnPos = _vPos; }
    Vec2 ReturnSpawnPos() { return m_vSpawnPos; }

    void SetSpawnChange(bool _change) { m_bSpawnChange = _change; }
    bool ReturnSpawnChange() { return m_bSpawnChange; }
   
public:
    CPlayer();
    CPlayer(const CPlayer& _other);
    ~CPlayer();
};

