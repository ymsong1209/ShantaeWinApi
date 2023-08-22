#pragma once
#include "CItem.h"

class CSound;
class CPot :
    public CItem
{
private:
    CSound* m_sSound;
    //0 : heart, 1: Gem(size 1)
    int m_iItemNum;
private:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    virtual void BeginOverlap(CCollider* _pOther) override;

public:
    CLONE(CPot);
public:
    CPot();
    ~CPot();
};

