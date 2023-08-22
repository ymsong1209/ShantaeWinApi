#pragma once
#include "CState.h"
class CSquidArmorUpState :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CSquidArmorUpState);

public:
    CSquidArmorUpState();
    ~CSquidArmorUpState();
};

