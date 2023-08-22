#pragma once
#include "CComponent.h"
class CAnimation;
class CTexture;

class CAnimator :
    public CComponent
{
private:
    map<wstring, CAnimation*>       m_mapAnim;
    CAnimation*                      m_pCurAnim;
    bool                            m_bRepeat;
    bool                            m_bAlphablend;
    //중심이 바닥인가?
    bool                            m_bFloorPlay;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;




public:
    void Play(const wstring& _strName, bool _bRepeat);
    void Play(int _Animnum, bool _bRepeat);
    void SetFloorPlay(bool _mbFloorPlay) { m_bFloorPlay = _mbFloorPlay; }
    void SetAlphablend(bool _mbAlphablend) { m_bAlphablend =_mbAlphablend; }
    void CreateAnimation(const wstring& _strName, CTexture* _pAtlas, Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset, Vec2 _vSpace, int _iMaxFrmCount, int _iline, int _iFrmPerLine, float _fDuration);
    CAnimation* FindAnimation(const wstring& _strName);
    CAnimation* LoadAnimation(const wstring& _strRelativePath);
    bool AnimationFinish(const wstring& _strName);
    void AnimationReset(const wstring& _strName);

public:
    CLONE(CAnimator);
public:
    CAnimator(CObj* _pOwner);
    CAnimator(const CAnimator& _other);
    ~CAnimator();
};

