#pragma once
#include "CObj.h"

class CPlayer;
class CWhip :
    public CObj
{
private:
    CPlayer* m_pOwner;
    float   m_fTime;
    int     m_iDmg;
    int     m_iExtraDmg;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    virtual void BeginOverlap(CCollider* _pOther) override;

    CPlayer* GetOwner() { return m_pOwner; }
    int     ReturnWhipDmg() { return m_iDmg; }
    int     ReturnWhipExtraDmg() { return m_iExtraDmg; }
public:
    CLONE(CWhip);
public:

    CWhip(CPlayer* _pOwner);
    ~CWhip();
};

