#pragma once
#include "CObj.h"
class CLevelChangeCollide :
    public CObj
{
private:
    LEVEL_TYPE   m_ELayer;
    Vec2    m_vSpawnPos;
    Vec2    m_vSize;
    float   m_fTime;
    bool    m_bLevelChange;

private:
    virtual void tick();
    virtual void BeginOverlap(CCollider* _pOther);
    virtual void OnOverlap(CCollider* _pOther);
    virtual void render(HDC _dc);

public:
    CLONE(CLevelChangeCollide);

public:
    //_vSpawnPos, _vSize
    CLevelChangeCollide(LEVEL_TYPE _layer, Vec2 _vSize);
    ~CLevelChangeCollide();
};

