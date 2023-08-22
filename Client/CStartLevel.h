#pragma once
#include "CLevel.h"
class CSound;
class CTitleSplash;
class CStartLevel :
    public CLevel
{
private:
    CSound* m_sbgm;
    float   m_fTime;
    bool    m_btick;
    bool    m_bCamera;
    
public:
    virtual void init() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
public:
    CStartLevel();
    ~CStartLevel();
};

