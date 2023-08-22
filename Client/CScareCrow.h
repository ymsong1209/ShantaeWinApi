#pragma once
#include "CMonster.h"
class CScareCrow :
    public CMonster
{
private:
    float   m_fAttackCoolTime;
public:
    void LoadScareCrowAnimation();

private:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void idle_enter() override;
    virtual void idle() override;
    virtual void idle_exit() override;
    virtual void trace_enter() override;
    /*virtual void walk() override;*/
    virtual void trace_changeAnim() override;
    //virtual void trace_exit() override;
    virtual void attack_enter() override;
    virtual void attack() override;
    virtual void attack_exit() override;
    virtual void hit() override;
    virtual void hit_enter() override;
    virtual void hit_exit() override;
    virtual void dead() override;
public:
    CLONE(CScareCrow);
public:
    CScareCrow();
    ~CScareCrow();
};

