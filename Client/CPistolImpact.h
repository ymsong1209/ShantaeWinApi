#pragma once
#include "CObj.h"
class CPistolImpact :
    public CObj
{
private:
    PLAYER_DIR      m_EDir;
public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    
public:
    CLONE(CPistolImpact);
public:
    CPistolImpact(PLAYER_DIR _dir);
    ~CPistolImpact();
};

