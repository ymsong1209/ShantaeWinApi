#pragma once
#include "CItem.h"
class CSound;
class CHeart :
    public CItem
{

private:
    float       m_fTime;
    float       m_fRatio;
    float       m_fDir;
    CSound* m_sound;
private:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    virtual void BeginOverlap(CCollider* _pOther) override;

public:
    CLONE(CHeart);
public:
    CHeart();
    ~CHeart();

};

