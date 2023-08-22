#pragma once
#include "CState.h"
class CSquidDeadState :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CSquidDeadState);

public:
    CSquidDeadState();
    ~CSquidDeadState();
};

