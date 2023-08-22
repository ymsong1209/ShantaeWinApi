#pragma once
#include "CObj.h"
class CTexture;
class CImpact_Big :
    public CObj
{
private:
    CTexture* m_pAtlas;

private:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CLONE(CImpact_Big);
public:
    CImpact_Big();
    ~CImpact_Big();
};

