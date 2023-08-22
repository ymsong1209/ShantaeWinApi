#pragma once
#include "CMonster.h"
class CCactus :
    public CMonster
{
private:
    float   m_fAttackCoolTime;
public:
    void LoadCactusAnimation();

private:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void idle_enter() override;
    virtual void walk() override;
    virtual void idle_exit() override;
    virtual void attack_enter() override;
    virtual void attack() override;
    virtual void attack_exit() override;
    virtual void hit() override;
    virtual void hit_exit() override;
    virtual void fall_enter() override;
    virtual void fall() override;
    virtual void fall_exit() override;
    virtual void land_enter() override;
    virtual void land() override;
    virtual void land_exit() override;
    virtual void dead() override;
public:
    CLONE(CCactus);
public:
    CCactus();
    ~CCactus();
};

