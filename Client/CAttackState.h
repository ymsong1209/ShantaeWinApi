#pragma once
#include "CState.h"
class CAttackState :
    public CState
{

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CAttackState);

public:
    CAttackState();
    ~CAttackState();

};

