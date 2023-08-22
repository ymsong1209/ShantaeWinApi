#pragma once
#include "CObj.h"
class CPlayer;

class CPistol :
    public CObj
{
private:
    CPlayer* m_pOwner;
    float m_fSpeed;
    float m_fDegree;
    float m_fTime;
    int         m_iDmg;
    int      m_iExtraDmg;
    

public:
    void SetSpeed(float _f) { m_fSpeed = _f; }
    void SetDir(float _fDegree) { m_fDegree = _fDegree; };
public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    virtual void BeginOverlap(CCollider* _pOther) override;
    int     ReturnPistolDmg() { return m_iDmg; }
    int     ReturnPistolExtraDmg() { return m_iExtraDmg; }
public:
    CLONE(CPistol);
public:
    CPistol(CPlayer* _pOwner);
    ~CPistol();
};

