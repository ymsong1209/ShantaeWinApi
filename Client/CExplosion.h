#pragma once
#include "CObj.h"
class CTexture;
class CExplosion :
    public CObj
{
private:
    CTexture*   m_pAtlas;
    int         m_iSoundNum;

private:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CLONE(CExplosion);
public:
    CExplosion(int _SoundNum);
    ~CExplosion();
};

