#pragma once
#include "CEntity.h"
class CObj;

class CLevel :
    public CEntity
{
private:
    vector<CObj*>   m_arrLayer[(UINT)LAYER::END];
    vector<CObj*>   m_vecTile;  // 화면안에 들어오는 타일

    UINT            m_iTileXCount;
    UINT            m_iTileYCount;
public:
    UINT GetTileXCount() { return m_iTileXCount; }
    UINT GetTileYCount() { return m_iTileYCount; }
public:
    virtual void init() = 0;
    virtual void tick();
    virtual void final_tick();
    virtual void render(HDC _dc);

    virtual void Enter() = 0;   // 레벨에 진입할 때 호출 됨
    virtual void Exit() = 0;    // 레벨을 벗어날 때 호출 됨

public:
    void AddObject(CObj* _pObj, LAYER _Layer) { m_arrLayer[(UINT)_Layer].push_back(_pObj); }
    const vector<CObj*>& GetLayer(LAYER _layer) { return m_arrLayer[(UINT)_layer]; }
    
    void DeleteAllObject();
    void ReleaseIsChosen();
    void DeleteObject(LAYER _eLayer);
    void CreateTile(UINT _X, UINT _Y);
    void CreatePlatform(int _platformcount);
    void CreateWall(int _WallCount);
    void CreateCeiling(int _CeilingCount);

    void SetFocusedUI(CObj* _pUI);

public:
    void LoadBackground(const wstring& _strKey, const wstring& _strRelativePath, Vec2 _vSize);
    void LoadPlatform(const wstring& _strRelativePath);
    void LoadWall(const wstring& _strRelativePath);
    void LoadCeiling(const wstring& _strRelativePath);
private:
    void FindTileScreen();
public:
    CLONE_DEACTIVATE(CLevel);
public:
    CLevel();
    virtual ~CLevel();
};

