#pragma once
#include "CState.h"
class CSquidJumpState :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CSquidJumpState);

public:
    CSquidJumpState();
    ~CSquidJumpState();
};

