#pragma once
#include "CObj.h"
class CSquidBaron;
class CSquidBaronDeath :
    public CObj
{
private:
    CTexture* m_pAtlas;
    int       m_iExplosionCount;
    float     m_fTime;
    Vec2      m_vScale;
    bool      m_bIntensify;
public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;


public:
    CLONE(CSquidBaronDeath);
public:

    CSquidBaronDeath();
    ~CSquidBaronDeath();

};

