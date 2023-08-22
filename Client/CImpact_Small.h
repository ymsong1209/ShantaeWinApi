#pragma once
#include "CObj.h"
class CTexture;
class CImpact_Small :
    public CObj
{
private:
    CTexture* m_pAtlas;

private:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CLONE(CImpact_Small);
public:
    CImpact_Small();
    ~CImpact_Small();
};

