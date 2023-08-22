#pragma once
#include "CObj.h"
class CMonster;
class CMonsterBullet :
    public CObj
{
private:
    CMonster*   m_pOwner;
    float       m_fSpeed;
    float       m_fDegree;
    float       m_fTime;
    int         m_iDmg;

private:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    virtual void BeginOverlap(CCollider* _pOther) override;
public:
    int ReturnDmg() { return m_iDmg; }

public:
    CLONE(CMonsterBullet);
public:
    CMonsterBullet(CMonster* _pOwner, float _mfDegree);
    ~CMonsterBullet();
};

