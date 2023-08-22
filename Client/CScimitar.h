#pragma once
#include "CObj.h"

class CPlayer;
class CScimitar :
    public CObj
{
private:
    CPlayer* m_pOwner;
    float m_fTime;
    PLAYER_ANIM m_pAnim;
    PLAYER_STATE m_pState;
    int         m_iDmg;
    int     m_iExtraDmg;


public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    virtual void BeginOverlap(CCollider* _pOther) override;

    CPlayer* GetOwner() { return m_pOwner; }
    int ReturnScimitarDmg() { return m_iDmg; }
    int     ReturnScimitarExtraDmg() { return m_iExtraDmg; }
public:
    CLONE(CScimitar);
public:

    CScimitar(CPlayer* _pOwner);
    ~CScimitar();
};
