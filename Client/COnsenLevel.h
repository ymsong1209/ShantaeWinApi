#pragma once
#include "CLevel.h"
class CSound;
class COnsenLevel :
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
    COnsenLevel();
    ~COnsenLevel();
};

