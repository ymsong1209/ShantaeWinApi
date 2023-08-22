#pragma once
#include "CObj.h"
class CSound;
class CTexture;
class CTitleSplash :
    public CObj
{
private:
    CTexture*   m_pAtlas;
    float       m_fTime;
    CSound*     m_sound;
    bool        m_bTime;
    Vec2        m_vSize;
private:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
public:

    void transferlevel();


public:
    CLONE(CTitleSplash);
public:
    CTitleSplash();
    ~CTitleSplash();
};

