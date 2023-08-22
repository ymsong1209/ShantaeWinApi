#pragma once
#include "CLevel.h"
class CStage02Level :
    public CLevel
{
public:
    virtual void init() override;
    virtual void tick() override;

    virtual void Enter() override;
    virtual void Exit() override;


public:
    CStage02Level();
    ~CStage02Level();
};

