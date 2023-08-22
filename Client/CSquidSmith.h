#pragma once
#include "CObj.h"
class CSquidSmith :
    public CObj
{
private:
    CTexture* m_pAtlas;
    bool      m_bForge;
private:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    virtual void OnOverlap(CCollider* _pOther) override;
public:
    void Slam();
    bool ReturnForge() { return m_bForge; }

public:
    CLONE(CSquidSmith);
public:
    CSquidSmith();
    ~CSquidSmith();
};

