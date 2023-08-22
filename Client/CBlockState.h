#pragma once
#include "CState.h"
class CBlockState :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CBlockState);

public:
    CBlockState();
    ~CBlockState();
};

