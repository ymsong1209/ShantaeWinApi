#pragma once
#include "CItem.h"
class CSound;
class CSquidHeart :
    public CItem
{
private:
    CSound* m_sound;
private:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    virtual void BeginOverlap(CCollider* _pOther) override;

public:
    CLONE(CSquidHeart);
public:
    CSquidHeart();
    ~CSquidHeart();
};

