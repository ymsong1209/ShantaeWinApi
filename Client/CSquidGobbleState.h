#pragma once
#include "CState.h"
class CSquidGobbleState :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CSquidGobbleState);

public:
    CSquidGobbleState();
    ~CSquidGobbleState();
};

