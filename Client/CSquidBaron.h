#pragma once
#include "CMonster.h"
class CSquidBaron :
    public CMonster
{
private:
    float     m_fBuildUpCooltime;
    CTexture* SquidBaron_L;
    CTexture* SquidBaron_R;
public:
    void LoadSquidBaronAnimation();

private:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    virtual void BeginOverlap(CCollider* _pOther) override;
    
public:

    void  SetBuildUpCooltime(float _time) { m_fBuildUpCooltime = _time; }
    float ReturnBuildUpCooltime() { return m_fBuildUpCooltime; }
public:
    CLONE(CSquidBaron);
public:
    CSquidBaron();
    ~CSquidBaron();

};

