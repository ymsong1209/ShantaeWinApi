#pragma once
#include "CObj.h"
class CTexture;
class CPotParticle :
    public CObj
{
private:
    CTexture* m_pAtlas;
    int       m_iParticleNum;
    Vec2      m_vSize;
    Vec2      m_vLeftTop;
    float     m_fTime;
    bool      m_bFade;
private:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;

public:
    CLONE(CPotParticle);
public:
    CPotParticle(int _particleNum);
    ~CPotParticle();
};

