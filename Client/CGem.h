#pragma once
#include "CItem.h"
class CSound;
class CGem :
    public CItem
{
private:

    int         m_iGemNum;
    //0 : big 1: mid 2 : small
    int         m_iGemSize;
    int         m_iGemValue;
    bool        m_btick;
    CSound* m_sBig;
    CSound* m_sMid;
    CSound* m_sSmall;
    CSound* m_sBounce;
    
private:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;

    void CreateAnim();
    void SetGemSize(int _miGemsize) { m_iGemSize = _miGemsize; }
public:
    CLONE(CGem);
public:
    CGem(int _iGemSize);
    ~CGem();


};

