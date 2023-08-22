#pragma once
#include "CObj.h"
class CBathWoman :
    public CObj
{
  
private:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CLONE(CBathWoman);
public:
    CBathWoman();
    ~CBathWoman();
};

