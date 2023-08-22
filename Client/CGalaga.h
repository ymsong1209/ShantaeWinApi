#pragma once
#include "CLevel.h"
class CGalaga :
    public CLevel
{
private:
    float   m_time;
public:
    virtual void init() override;
    virtual void tick() override;
    virtual void render(HDC _dc) override;
public:
    CGalaga();
    ~CGalaga();
};



