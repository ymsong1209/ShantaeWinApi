#pragma once
#include "CLevel.h"

enum class EDITOR_MODE
{
    TILE,
    MONSTER,
    OBJECT,
    PLATFORM,
    WALL,
    CEILING,
    CAMERA,


    NONE,
};
enum class FIELD_OBJ {
    HEART,
    SQUID_HEART,
    GEM,
    NONE
};


class CEditorLevel :
    public CLevel
{
private:
    HMENU           m_hMenu;
    EDITOR_MODE     m_eMode;
    FIELD_OBJ       m_EObj;
    Vec2            m_vLeftTop;
    Vec2            m_vSize;
    int             m_ICurPlatform;
    int             m_ICurWall;
    int             m_ICurCeiling;
    int             m_ICurMonster;
    int             m_IMonsterNum;
    int             m_IMaxMonsterNum;
    Vec2            m_vMousePos1;
    Vec2            m_vMousePos2;
    bool            m_bMousePos1active;
    //map<wstring, CTexture*>       m_mapObj;


public:
    virtual void init() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

private:
    void update();
    void tile_update();
    void monster_update();
    void animation_save();
    void object_update();
    void wall_update();
    void platform_update();
    void ceiling_update();
    void CreateUI();
    void CreateObjectUI();

public:
    EDITOR_MODE ReturnMode() { return m_eMode; }
    int ReturnCurPlatform() { return m_ICurPlatform; }
    int ReturnCurWall() { return m_ICurWall; }
    int ReturnCurCeiling() { return m_ICurCeiling; }
    void SaveTile();
    void LoadTile();
    void SavePlatform();
    void LoadPlatform();
    void SaveWall();
    void LoadWall();
    void SaveCeiling();
    void LoadCeiling();
    void SaveMonster();
    void LoadMonster();

public:
    CEditorLevel();
    ~CEditorLevel();
};

