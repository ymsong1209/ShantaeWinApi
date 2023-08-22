#pragma once
#include "CObj.h"
class CTexture;
class CPlayer;
class CMoneyUI :
    public CObj
{
private:
    CTexture* m_pAtlas;
    CPlayer* m_pOwner;
    Vec2        m_vSize;
public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
public:
    Vec2 ReturnSize() { return m_vSize; }
public:
    CLONE(CMoneyUI);
public:
    CMoneyUI(CPlayer* _pOwner);
    ~CMoneyUI();
};

