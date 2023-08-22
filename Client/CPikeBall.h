#pragma once
#include "CObj.h"
class CPlayer;
class CPikeBall :
    public CObj
{
private:
    float           m_fTime;
    float           m_fSpeed;
    int             m_iDamage;
    CPlayer*        m_pOwner;
    float           m_fDistance;
    CTexture*       m_pAtlas;

    virtual void tick() override;
    virtual void render(HDC _dc) override;
public:

    int ReturnPikeBallDmg() { return m_iDamage; }
public:
    CLONE(CPikeBall);
public:
    CPikeBall(CPlayer* _pOwner);
    ~CPikeBall();
};

