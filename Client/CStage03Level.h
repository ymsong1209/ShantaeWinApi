#pragma once
#include "CLevel.h"
class CStage03Level :
    public CLevel
{
public:
    virtual void init() override;
    virtual void tick() override;

    virtual void Enter() override;
    virtual void Exit() override;


public:
    CStage03Level();
    ~CStage03Level();

};

