#pragma once
#include "CObj.h"
class CSquidBaron;
class CSquidBaron_ElecSmall :
    public CObj
{
private:
    CSquidBaron* m_pOwner;
    CTexture*   m_pAtlas_L;
    CTexture*   m_pAtlas_R;
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
    CLONE(CSquidBaron_ElecSmall);
public:
    CSquidBaron_ElecSmall(CSquidBaron* _pOwner, float _fDegree);
    ~CSquidBaron_ElecSmall();
};

