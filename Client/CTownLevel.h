#pragma once
#include "CLevel.h"
class CSound;
class CTownLevel :
    public CLevel
{
private:
    CSound* m_sbgm;
public:
    virtual void init() override;
    virtual void tick() override;

    virtual void Enter() override;
    virtual void Exit() override;


public:
    CTownLevel();
    ~CTownLevel();
};

