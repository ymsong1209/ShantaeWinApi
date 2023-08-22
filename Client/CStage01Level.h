#pragma once
#include "CLevel.h"
class CSound;
class CStage01Level :
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
    CStage01Level();
    ~CStage01Level();
};


