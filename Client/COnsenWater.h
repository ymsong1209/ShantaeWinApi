#pragma once
#include "CObj.h"
class CSound;
class COnsenWater :
    public CObj
{
private:
    float       m_fTime;
    CSound* m_sound;
private:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;

public:
    CLONE(COnsenWater);
public:
    COnsenWater();
    ~COnsenWater();
};

