#pragma once
#include "CObj.h"
class CTexture;
class CHeartContainer :
    public CObj
{
private:
    CTexture* m_pAtlas;
    int         m_iHeartNum;
    Vec2        m_vSize;
    Vec2        m_vLeftTop;
public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    Vec2  ReturnSize() { return m_vSize; }
public:
    CLONE(CHeartContainer);
public:
    CHeartContainer(int _heartNum);
    ~CHeartContainer();
};

