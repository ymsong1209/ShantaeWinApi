#pragma once
#include "CState.h"
class CDeadState :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CDeadState);

public:
    CDeadState();
    ~CDeadState();
};

