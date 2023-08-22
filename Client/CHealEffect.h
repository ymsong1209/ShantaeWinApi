#pragma once
#include "CObj.h"
class CHealEffect :
    public CObj
{
private:
    float   m_fTime;
    int     m_iHeal;
    CTexture* m_pAtlas;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    int     ReturnDmg() { return m_iHeal; }

public:
    CLONE(CHealEffect);
public:

    CHealEffect(int _Heal);
    ~CHealEffect();
};

