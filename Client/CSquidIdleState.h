#pragma once
#include "CState.h"
class CSquidIdleState :
    public CState
{

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CSquidIdleState);

public:
    CSquidIdleState();
    ~CSquidIdleState();

};

