#pragma once
#include "CState.h"
class CSquidBuildUpState :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CSquidBuildUpState);

public:
    CSquidBuildUpState();
    ~CSquidBuildUpState();
};

