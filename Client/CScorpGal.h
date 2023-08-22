#pragma once
#include "CMonster.h"
class CSound;
class CScorpGal :
    public CMonster
{
private:
    float   m_fAttackCoolTime;
    float   m_fPatrolCoolTime;
    float   m_fIdleCoolTime;
    bool    m_bWasPatrollingLeft;
    bool    m_bHasAttacked;
    CSound* m_sPatrol;
    CSound* m_sBlockSound;
public:
    void LoadScorpGalAnimation();

private:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void idle_enter() override;
    virtual void idle_exit() override;
    virtual void trace_enter() override;
    virtual void walk() override;
    virtual void trace_changeAnim() override;
    //virtual void trace_exit() override;
    virtual void attack_enter() override;
    virtual void attack() override;
    virtual void attack_exit() override;
    virtual void block() override;
    virtual void block_enter() override;
    virtual void block_exit() override;
    virtual void hit() override;
    virtual void hit_exit() override;
    virtual void dead_enter() override;
public:
    CLONE(CScorpGal);
public:
    CScorpGal();
    ~CScorpGal();
};

