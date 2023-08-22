#pragma once
#include "CState.h"
class CHitState :
    public CState
{
private:

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CHitState);

public:
    CHitState();
    ~CHitState();
};

