#pragma once
#include "CObj.h"
class CScorpGal;
class CScorpGalAttack :
    public CObj
{
private:
    CScorpGal* m_pOwner;
    float   m_fTime;
    int     m_iDmg;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    //virtual void BeginOverlap(CCollider* _pOther) override;

    CScorpGal* GetOwner() { return m_pOwner; }
    int     ReturnDmg() { return m_iDmg; }
public:
    CLONE(CScorpGalAttack);
public:
    CScorpGalAttack(CScorpGal* _pOwner);
    ~CScorpGalAttack();
};

