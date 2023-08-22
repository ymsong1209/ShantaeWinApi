#pragma once
#include "CObj.h"
class CLevelChangeInteract :
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
    virtual void render(HDC _dc);
public:
    void LevelChange();
public:
    CLONE(CLevelChangeInteract);

public:
    //_vSpawnPos, _vSize
    CLevelChangeInteract(LEVEL_TYPE _layer, Vec2 _vSize);
    ~CLevelChangeInteract();
};

