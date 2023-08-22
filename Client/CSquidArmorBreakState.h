#pragma once
#include "CState.h"
class CSquidArmorBreakState :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CSquidArmorBreakState);

public:
    CSquidArmorBreakState();
    ~CSquidArmorBreakState();
};

