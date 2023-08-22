#pragma once
#include "CObj.h"
class CDamage :
    public CObj
{
private:
    float   m_fTime;
    int     m_iDmg;
    bool    m_bExtraDmg;
    CTexture* m_pAtlas;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    int     ReturnDmg() { return m_iDmg; }

public:
    CLONE(CDamage);
public:

    CDamage(int _iDmg, bool _IsExtraDmg);
    ~CDamage();

};

