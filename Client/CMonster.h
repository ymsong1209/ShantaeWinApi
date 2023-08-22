#pragma once
#include "CObj.h"
class CTexture;
class CMonster :
    public CObj
{
private:

    CObj* m_pTarget;
    CTexture* m_pTex;
    Vec2        m_vSpawnPos;
protected:

    tMonsterInfo    m_tInfo;
public:

private:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    
public:
    Vec2 ReturnSpawnPos() { return m_vSpawnPos; }
    void SetSpawnPos(Vec2 _mvPos) { m_vSpawnPos = _mvPos; }
    virtual void BeginOverlap(CCollider* _pOther) override;
public:
    void SetTarget(CObj* _pPlayer) { m_pTarget = _pPlayer; }
    tMonsterInfo& GetMonInfo() { return m_tInfo; }
    virtual void idle_enter() {};
    virtual void idle() {};
    virtual void idle_changeAnim() {};
    virtual void idle_exit() {};
    virtual void trace_enter() {};
    virtual void walk() {};
    virtual void trace_changeAnim() {};
    virtual void trace_exit() {};
    virtual void attack_enter() {};
    virtual void attack() {};
    virtual void attack_exit() {};
    virtual void hit_enter() {};
    virtual void hit() {};
    virtual void hit_exit() {};
    virtual void land_enter() {};
    virtual void land() {};
    virtual void land_exit() {};
    virtual void block_enter() {};
    virtual void block() {};
    virtual void block_exit() {};
    virtual void fall_enter() {};
    virtual void fall() {};
    virtual void fall_exit() {};
    virtual void dead() {};
    virtual void dead_enter() {};


public:
    CLONE_DEACTIVATE(CMonster);
public:
    CMonster();
    ~CMonster();
};

