#pragma once
#include "CState.h"
class CLandState :
    public CState
{

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CLandState);

public:
    CLandState();
    ~CLandState();
};

