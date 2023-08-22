#pragma once
#include "CState.h"
class CSquidPhase2State :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CSquidPhase2State);

public:
    CSquidPhase2State();
    ~CSquidPhase2State();
};

