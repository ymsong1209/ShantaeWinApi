#pragma once
#include "CObj.h"
class CSquidBaron;
class CSquidBanner :
    public CObj
{
private:
    float           m_fSpeed;
  
    CSquidBaron*    m_pOwner;
    CTexture*       m_pAtlas;

    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CLONE(CSquidBanner);
public:
    CSquidBanner(CSquidBaron* _pOwner);
    ~CSquidBanner();
};

