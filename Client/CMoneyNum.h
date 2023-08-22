#pragma once
#include "CObj.h"
class CTexture;
class CMoneyNum :
    public CObj
{
private:
    CTexture* m_pAtlas;
    int         m_iNum;
    Vec2        m_vSize;
    Vec2        m_vLeftTop;
    Vec2        m_vSpace;
public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
public:
    Vec2 ReturnSize() { return m_vSize; }
public:
    CLONE(CMoneyNum);
public:
    CMoneyNum(int _iNum);
    ~CMoneyNum();
};

