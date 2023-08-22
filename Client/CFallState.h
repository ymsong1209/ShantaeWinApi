#pragma once
#include "CState.h"
class CFallState :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CFallState);

public:
    CFallState();
    ~CFallState();
};

