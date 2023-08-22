#pragma once
#include "CObj.h"
#include "CMonster.h"
class CSound;
class CScareCrowVomit :
    public CObj
{
private:
    CMonster*   m_pOwner;
    float       m_fSpeed;
    float       m_fDegree;
    float       m_fTime;
    int         m_iDmg;
    CSound* m_sound;

private:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    virtual void BeginOverlap(CCollider* _pOther) override;
public:
    int ReturnDmg() { return m_iDmg; }

public:
    CLONE(CScareCrowVomit);
public:
    CScareCrowVomit(CMonster* _pOwner);
    ~CScareCrowVomit();
};

