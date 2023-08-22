#pragma once
#include "CState.h"
class CSquidAttackState :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CSquidAttackState);

public:
    CSquidAttackState();
    ~CSquidAttackState();
};

