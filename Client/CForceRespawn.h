#pragma once
#include "CObj.h"
class CForceRespawn :
    public CObj
{
private:
    Vec2    m_vSpawnPos;
    Vec2    m_vSize;

private:
    virtual void tick();
    virtual void BeginOverlap(CCollider* _pOther);
    virtual void OnOverlap(CCollider* _pOther);
    virtual void render(HDC _dc);

public:
    CLONE(CForceRespawn);

public:
    //_vSpawnPos, _vSize
    CForceRespawn(Vec2 _vSpawnPos, Vec2 _vSize);
    ~CForceRespawn();
};

