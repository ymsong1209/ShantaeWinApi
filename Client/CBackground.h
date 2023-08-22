#pragma once
#include "CObj.h"
class CBackground :
    public CObj
{
private:
    CTexture*       m_pAtlas;

    Vec2            m_vSize;

public:

    virtual void tick();
    virtual void render(HDC _dc);
    Vec2 ReturnSize() { return m_vSize; }
public:
    CLONE(CBackground);

public:
    CBackground(CTexture* m_pAtlas, Vec2 _vSize);
    ~CBackground();
};

