#pragma once
#include "CEntity.h"

class CAnimator;
class CTexture;

class CAnimation :
    public CEntity
{
private:
    CAnimator*          m_pAnimator;
    vector<tAnimFrm>    m_vecFrm;
    CTexture*           m_pAtlas;
    int                 m_iCurFrm;
    float               m_fAccTime;
    bool                m_bFinish;
   // bool                m_bPlayerPlay;

private:
    void init(const wstring& _strName, CTexture* _pAtlas, Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset, Vec2 _vSpace, int _iMaxFrmCount, int _line, int _FrmPerLine, float _fDuration);

public:
    void tick();
    void render(HDC _dc, bool _mAlphablend, bool _mFloorPlay);

public:
    bool IsFinish() { return m_bFinish; }
    void Reset()
    {
        m_bFinish = false;
        m_iCurFrm = 0;
        m_fAccTime = 0.f;
    }

    void Save(const wstring& _strRelativePath);
    void Load(const wstring& _strRelativePath);
    vector<tAnimFrm> ReturnVecFrm() { return m_vecFrm; }


public:
    CLONE(CAnimation);

public:
    CAnimation(CAnimator* _pAnimator);
    ~CAnimation();

    friend class CAnimator;
};

