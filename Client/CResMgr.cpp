#include "pch.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CSound.h"

CResMgr::CResMgr() {

}
CResMgr::~CResMgr() {
    map<wstring, CTexture*>::iterator iter = m_mapTex.begin();
    for (; iter != m_mapTex.end(); ++iter) {
        DEL(iter->second);
    }
    map<wstring, CSound*>::iterator iter_sound = m_mapSounds.begin();
    for (; iter_sound != m_mapSounds.end(); ++iter_sound)
    {
        DEL(iter_sound->second);
    }
}

void CResMgr::init()
{
    CResMgr::GetInst()->LoadTexture(L"Shantae_L", L"texture\\player\\Shantae_original_L.bmp");
    CResMgr::GetInst()->LoadTexture(L"Shantae_R", L"texture\\player\\Shantae_original_R.bmp");
    CResMgr::GetInst()->LoadTexture(L"Heart", L"texture\\fx\\heart.bmp");
    CResMgr::GetInst()->LoadTexture(L"Objects", L"texture\\objects\\Objects.bmp");
    CResMgr::GetInst()->LoadTexture(L"Gems", L"texture\\objects\\Gems.bmp");
    CResMgr::GetInst()->LoadTexture(L"fx_L", L"texture\\fx\\fx_L.bmp");
    CResMgr::GetInst()->LoadTexture(L"fx_R", L"texture\\fx\\fx_R.bmp");
    CResMgr::GetInst()->LoadTexture(L"poison", L"texture\\fx\\poison.bmp");
    CResMgr::GetInst()->LoadTexture(L"number2", L"texture\\fx\\number2.bmp");
    CResMgr::GetInst()->LoadTexture(L"Money", L"texture\\fx\\Money.bmp");
    CResMgr::GetInst()->LoadTexture(L"numbers", L"texture\\fx\\number.bmp");
    CResMgr::GetInst()->LoadTexture(L"number3", L"texture\\fx\\number3.bmp");
    CResMgr::GetInst()->LoadTexture(L"ItemPortrait", L"texture\\fx\\ItemPortrait.bmp");
    //------------BackGround-------------//
    CResMgr::GetInst()->LoadTexture(L"outskirts_enlarge", L"texture\\background\\fixed\\enhanced\\outskirts_enlarge.bmp");
    CResMgr::GetInst()->LoadTexture(L"outskirts2_enlarge", L"texture\\background\\fixed\\enhanced\\outskirts2_enlarge.bmp");
    CResMgr::GetInst()->LoadTexture(L"maze", L"texture\\background\\fixed\\enhanced\\maze.bmp");
    CResMgr::GetInst()->LoadTexture(L"maze2", L"texture\\background\\fixed\\enhanced\\maze2.bmp");
    CResMgr::GetInst()->LoadTexture(L"boss", L"texture\\background\\fixed\\enhanced\\boss.bmp");
    CResMgr::GetInst()->LoadTexture(L"SquidSmith", L"texture\\background\\fixed\\enhanced\\SquidSmith.bmp");
    CResMgr::GetInst()->LoadTexture(L"onsen", L"texture\\background\\fixed\\enhanced\\onsen.bmp");
    CResMgr::GetInst()->LoadTexture(L"StartScreen", L"texture\\SplashScreens\\StartScreen.bmp");
    CResMgr::GetInst()->LoadTexture(L"Logo", L"texture\\SplashScreens\\logo.bmp");
   
    CResMgr::GetInst()->LoadTexture(L"boss-1", L"texture\\background\\fixed\\boss-1.bmp");
    CResMgr::GetInst()->LoadTexture(L"town", L"texture\\background\\fixed\\enhanced\\town.bmp");
    //----------Monster-------------------//
    CResMgr::GetInst()->LoadTexture(L"Bat_L", L"texture\\monster\\Bat_L.bmp");
    CResMgr::GetInst()->LoadTexture(L"Bat_R", L"texture\\monster\\Bat_R.bmp");
    CResMgr::GetInst()->LoadTexture(L"Scarecrow_L", L"texture\\monster\\Scarecrow_L.bmp");
    CResMgr::GetInst()->LoadTexture(L"Scarecrow_R", L"texture\\monster\\Scarecrow_R.bmp");
    CResMgr::GetInst()->LoadTexture(L"Cactus_L", L"texture\\monster\\Cactus_L.bmp");
    CResMgr::GetInst()->LoadTexture(L"Cactus_R", L"texture\\monster\\Cactus_R.bmp");
    CResMgr::GetInst()->LoadTexture(L"ScorpGal_L", L"texture\\monster\\ScorpGal_L.bmp");
    CResMgr::GetInst()->LoadTexture(L"ScorpGal_R", L"texture\\monster\\ScorpGal_R.bmp");
    CResMgr::GetInst()->LoadTexture(L"SquidBaron_L", L"texture\\monster\\SquidBaron_L.bmp");
    CResMgr::GetInst()->LoadTexture(L"SquidBaron_R", L"texture\\monster\\SquidBaron_R.bmp");
    //---------Npc----------------------//
    CResMgr::GetInst()->LoadTexture(L"SquidSmith_Npc", L"texture\\npc\\SquidSmith.bmp");
    CResMgr::GetInst()->LoadTexture(L"BathWoman_npc", L"texture\\npc\\BathWoman.bmp");
    //----------------------------------------------------------------------------------------------//
    //-----------PlayerSound--------------//
    CResMgr::GetInst()->LoadSound(L"Attack_01", L"sound\\player\\vo_s_attack_01 [1].wav");
    CResMgr::GetInst()->LoadSound(L"Attack_02", L"sound\\player\\vo_s_attack_02 [1].wav");
    CResMgr::GetInst()->LoadSound(L"pistol", L"sound\\player\\player_risky_shoot_pistol.wav");
    CResMgr::GetInst()->LoadSound(L"pistol_impact", L"sound\\player\\player_risky_pistol_impact.wav");
    CResMgr::GetInst()->LoadSound(L"Attack_eat_this_1", L"sound\\player\\vo_s_attack_eat_this_01 [1].wav");
    CResMgr::GetInst()->LoadSound(L"Attack_eat_this_2", L"sound\\player\\vo_s_attack_eat_this_02 [1].wav");
    CResMgr::GetInst()->LoadSound(L"Scimitar", L"sound\\player\\object_starfish_fire.wav");
    CResMgr::GetInst()->LoadSound(L"Hat_Init", L"sound\\player\\cloth.wav");
    CResMgr::GetInst()->LoadSound(L"Whip_01", L"sound\\player\\player_hair_whip_normal.wav");
    CResMgr::GetInst()->LoadSound(L"Whip_02", L"sound\\player\\player_hair_whip_normal_02.wav");
    CResMgr::GetInst()->LoadSound(L"Whip_03", L"sound\\player\\player_hair_whip_normal_03.wav");
    CResMgr::GetInst()->LoadSound(L"Jump_01", L"sound\\player\\vo_s_jump_01 [1].wav");
    CResMgr::GetInst()->LoadSound(L"Jump_02", L"sound\\player\\vo_s_jump_02 [1].wav");
    CResMgr::GetInst()->LoadSound(L"Jump_03", L"sound\\player\\vo_s_jump_05 [1].wav");
    CResMgr::GetInst()->LoadSound(L"Hit_Air", L"sound\\player\\vo_s_hurt_05 [1].wav");
    CResMgr::GetInst()->LoadSound(L"Hit_Ground", L"sound\\player\\vo_s_hurt_02 [1].wav");
    CResMgr::GetInst()->LoadSound(L"Hit_Duck", L"sound\\player\\vo_s_hurt_03 [1].wav");
    CResMgr::GetInst()->LoadSound(L"Getup", L"sound\\player\\vo_s_land_05 [1].wav");
    CResMgr::GetInst()->LoadSound(L"eat", L"sound\\player\\vo_s_eat_05 [1].wav");
    CResMgr::GetInst()->LoadSound(L"drink", L"sound\\player\\vo_s_drink_03 [1].wav");
    CResMgr::GetInst()->LoadSound(L"pikeball", L"sound\\player\\vo_a_pike_ball_01 [1].wav");
    CResMgr::GetInst()->LoadSound(L"vo_a_monster_milk_01", L"sound\\player\\vo_a_monster_milk_01 [1].wav");
    CResMgr::GetInst()->LoadSound(L"PowerUp", L"sound\\player\\vo_s_power_up_02 [1].wav");
    //-----------MonsterSound------------//
    CResMgr::GetInst()->LoadSound(L"bat_death", L"sound\\monster\\enemy_bat_death.wav");
    CResMgr::GetInst()->LoadSound(L"bat_wing1", L"sound\\monster\\enemy_bat_wing_flap_01.wav");
    CResMgr::GetInst()->LoadSound(L"bat_wing2", L"sound\\monster\\enemy_bat_wing_flap_02.wav");
    CResMgr::GetInst()->LoadSound(L"bat_wing3", L"sound\\monster\\enemy_bat_wing_flap_03.wav");
    CResMgr::GetInst()->LoadSound(L"cactus_death", L"sound\\monster\\enemy_cactus_gethit_death.wav");
    CResMgr::GetInst()->LoadSound(L"cactus_shoot", L"sound\\monster\\enemy_cactus_shootspikes.wav");
    CResMgr::GetInst()->LoadSound(L"scorpgal_die", L"sound\\monster\\scorpgal_die [1].wav");
    CResMgr::GetInst()->LoadSound(L"scorpgal_walk", L"sound\\monster\\enemey_crab_footstep_01.wav");
    CResMgr::GetInst()->LoadSound(L"scorpgal_attack", L"sound\\monster\\enemy_scropion_girl_attack_sword.wav");
    CResMgr::GetInst()->LoadSound(L"scorpgal_block", L"sound\\monster\\scorpgal_block.wav");
    CResMgr::GetInst()->LoadSound(L"scarecrow_shoot", L"sound\\monster\\enemy_mermaid_shoot_bubbles.wav");
    CResMgr::GetInst()->LoadSound(L"scarecrow_death", L"sound\\monster\\enemy_mermaid_gethit_death.wav");
    CResMgr::GetInst()->LoadSound(L"scarecrow_hit", L"sound\\monster\\enemy_global_gethit_01.wav");
    //----------BossSound---------//
    CResMgr::GetInst()->LoadSound(L"wallimpact", L"sound\\monster\\baron_wallimpact.wav");
    CResMgr::GetInst()->LoadSound(L"armorbreak", L"sound\\monster\\baron_armorbreak.wav");
    CResMgr::GetInst()->LoadSound(L"armorup", L"sound\\monster\\baron_armorup.wav");
    CResMgr::GetInst()->LoadSound(L"buildup", L"sound\\monster\\baron_buildup.wav");
    CResMgr::GetInst()->LoadSound(L"chew", L"sound\\monster\\baron_chew.wav");
    CResMgr::GetInst()->LoadSound(L"foodspawn", L"sound\\monster\\baron_foodspawn.wav");
    CResMgr::GetInst()->LoadSound(L"baronjump", L"sound\\monster\\baron_jump.wav");
    CResMgr::GetInst()->LoadSound(L"lightning", L"sound\\monster\\baron_lightning.wav");
    //----------BackGround--------------//
    CResMgr::GetInst()->LoadSound(L"Sequinisland", L"sound\\bgm\\Sequinisland.wav");
    CResMgr::GetInst()->LoadSound(L"SpittleMaze", L"sound\\bgm\\SpittleMaze.wav");
    CResMgr::GetInst()->LoadSound(L"Boss", L"sound\\bgm\\Boss.wav");
    CResMgr::GetInst()->LoadSound(L"Boss2", L"sound\\bgm\\Boss2.wav");
    CResMgr::GetInst()->LoadSound(L"Town", L"sound\\bgm\\ScuttleTown.wav");
    CResMgr::GetInst()->LoadSound(L"Shop", L"sound\\bgm\\Shop.wav");
    CResMgr::GetInst()->LoadSound(L"Title", L"sound\\bgm\\Title.wav");
    CResMgr::GetInst()->LoadSound(L"TitleAnnounce", L"sound\\player\\vo_f_title_announce [1].wav");
    //----------Fx----------------//
    CResMgr::GetInst()->LoadSound(L"Heart", L"sound\\fx\\pickup_heart_small.wav");
    CResMgr::GetInst()->LoadSound(L"Meat_Heal", L"sound\\fx\\pickup_heart_large.wav");
    CResMgr::GetInst()->LoadSound(L"Gem_Small", L"sound\\fx\\pickup_gem_small.wav");
    CResMgr::GetInst()->LoadSound(L"Gem_Mid", L"sound\\fx\\pickup_gem_mid.wav");
    CResMgr::GetInst()->LoadSound(L"Gem_Big", L"sound\\fx\\pickup_gem_big.wav");
    CResMgr::GetInst()->LoadSound(L"SquidHeart", L"sound\\fx\\pickup_heart_container.wav");
    CResMgr::GetInst()->LoadSound(L"Pot", L"sound\\fx\\object_pot_smash_small.wav");
    CResMgr::GetInst()->LoadSound(L"Gem_Bounce", L"sound\\fx\\pickup_coin_bounce_small.wav");
    CResMgr::GetInst()->LoadSound(L"Explosion1", L"sound\\fx\\explosion_popcorn_01.wav");
    CResMgr::GetInst()->LoadSound(L"Explosion2", L"sound\\fx\\explosion_popcorn_02.wav");
    CResMgr::GetInst()->LoadSound(L"Explosion3", L"sound\\fx\\explosion_popcorn_03.wav");
    CResMgr::GetInst()->LoadSound(L"menu_confirm", L"sound\\fx\\menu_confirm.wav");
    CResMgr::GetInst()->LoadSound(L"Stage_Clear", L"sound\\fx\\Clear.wav");
    
    
   
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{

    map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);
    if (iter == m_mapTex.end()) {
        return nullptr;
    }
    return iter->second;
  
}

CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
    CRes* pTexture = FindTexture(_strKey);
    if (nullptr != pTexture) { return (CTexture*)pTexture; }

    //PathMgr를 이용해서 최종  Texture 경로를 만든다.
    wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
    strFilePath += _strRelativePath;

    //텍스쳐 생성 및 로딩
    pTexture = new CTexture;
    pTexture->Load(strFilePath);
    pTexture->SetKey(_strKey);
    pTexture->SetRelativePath(_strRelativePath);

    m_mapTex.insert(make_pair(_strKey, (CTexture*)pTexture));
   
    return (CTexture*)pTexture;
}

CTexture* CResMgr::CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight)
{
    CTexture* pTexture = FindTexture(_strKey);

    if (nullptr != pTexture)
        return (CTexture*)pTexture;

    // 텍스쳐 생성 및 로딩
    pTexture = new CTexture;
    pTexture->Create(_iWidth, _iHeight);
    pTexture->SetKey(_strKey);

    // Map 에 저장
    m_mapTex.insert(make_pair(_strKey, pTexture));

    return pTexture;
}

CSound* CResMgr::FindSound(const wstring& _strKey)
{
    map<wstring, CSound*>::iterator iter = m_mapSounds.find(_strKey);
    if (iter == m_mapSounds.end())
    {
        return nullptr;
    }

    return iter->second;
}

CSound* CResMgr::LoadSound(const wstring& _strKey, const wstring& _strRelativePath)
{
    CRes* pSound = FindSound(_strKey);

    if (nullptr != pSound)
        return (CSound*)pSound;

    // PathMgr 를 이용해서 최종 Texture의 경로를 만든다.
    wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
    strFilePath += _strRelativePath;

    // 텍스쳐 생성 및 로딩
    pSound = new CSound;
    pSound->Load(strFilePath);
    pSound->SetKey(_strKey);
    pSound->SetRelativePath(_strRelativePath);

    // Map 에 저장
    m_mapSounds.insert(make_pair(_strKey, (CSound*)pSound));

    return (CSound*)pSound;
}
