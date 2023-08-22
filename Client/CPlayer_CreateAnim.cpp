#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CEventMgr.h"
#include "CTexture.h"
#include "CResMgr.h"

#include "CMissile.h"
#include "CCollider.h"

#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidbody.h"

void CPlayer::CreateAnimation()
{
// Image ·Îµù

pShantaeTex = CResMgr::GetInst()->LoadTexture(L"Shantae_L", L"texture\\player\\Shantae_original_L.bmp");
pShantaeTex_R = CResMgr::GetInst()->LoadTexture(L"Shantae_R", L"texture\\player\\Shantae_original_R.bmp");


//GetAnimator()->CreateAnimation(L"Standing_Idle", pShantaeTex, Vec2(6.f, 30.f), Vec2(144.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 7, 1, 7, 0.1f);
//GetAnimator()->FindAnimation(L"Standing_Idle")->Save(L"animation\\player\\Standing_Idle.anim");
//GetAnimator()->CreateAnimation(L"Standing_Idle_R", pShantaeTex_R, Vec2(6.f, 30.f), Vec2(144.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 7, 1, 7, 0.1f);
//GetAnimator()->FindAnimation(L"Standing_Idle_R")->Save(L"animation\\player\\Standing_Idle_R.anim");
//
//GetAnimator()->CreateAnimation(L"Standing_Idle_Full", pShantaeTex, Vec2(6.f, 207.f), Vec2(180.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 12.f), 16, 2, 12, 0.1f);
//GetAnimator()->FindAnimation(L"Standing_Idle_Full")->Save(L"animation\\player\\Standing_Idle_Full.anim");
//GetAnimator()->CreateAnimation(L"Standing_Idle_Full_R", pShantaeTex_R, Vec2(6.f, 207.f), Vec2(180.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 12.f), 16, 2, 12, 0.1f);
//GetAnimator()->FindAnimation(L"Standing_Idle_Full_R")->Save(L"animation\\player\\Standing_Idle_Full_R.anim");
//
//GetAnimator()->CreateAnimation(L"Standing_Idle_Long", pShantaeTex, Vec2(6.f, 531.f), Vec2(216.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 24, 2, 12, 0.1f);
//GetAnimator()->FindAnimation(L"Standing_Idle_Long")->Save(L"animation\\player\\Standing_Idle_Long.anim");
//GetAnimator()->CreateAnimation(L"Standing_Idle_Long_R", pShantaeTex_R, Vec2(6.f, 531.f), Vec2(216.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 24, 2, 12, 0.1f);
//GetAnimator()->FindAnimation(L"Standing_Idle_Long_R")->Save(L"animation\\player\\Standing_Idle_Long_R.anim");
//
//GetAnimator()->CreateAnimation(L"Time_Out_Pants", pShantaeTex, Vec2(6.f, 843.f), Vec2(144.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 12.f), 17, 2, 12, 0.1f);
//GetAnimator()->FindAnimation(L"Time_Out_Pants")->Save(L"animation\\player\\Time_Out_Pants.anim");
//GetAnimator()->CreateAnimation(L"Time_Out_Pants_R", pShantaeTex_R, Vec2(6.f, 843.f), Vec2(144.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 12.f), 17, 2, 12, 0.1f);
//GetAnimator()->FindAnimation(L"Time_Out_Pants_R")->Save(L"animation\\player\\Time_Out_Pants_R.anim");
//
//GetAnimator()->CreateAnimation(L"Time_Out_Top", pShantaeTex, Vec2(6.f, 1167.f), Vec2(144.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 12.f), 13, 1, 13, 0.1f);
//GetAnimator()->FindAnimation(L"Time_Out_Top")->Save(L"animation\\player\\Time_Out_Top.anim");
//GetAnimator()->CreateAnimation(L"Time_Out_Top_R", pShantaeTex_R, Vec2(6.f, 1167.f), Vec2(144.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 12.f), 13, 1, 13, 0.1f);
//GetAnimator()->FindAnimation(L"Time_Out_Top_R")->Save(L"animation\\player\\Time_Out_Top_R.anim");
//
//GetAnimator()->CreateAnimation(L"Time_Out_Vest", pShantaeTex, Vec2(6.f, 1344.f), Vec2(144.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 12.f), 13, 1, 13, 0.1f);
//GetAnimator()->FindAnimation(L"Time_Out_Vest")->Save(L"animation\\player\\Time_Out_Vest.anim");
//GetAnimator()->CreateAnimation(L"Time_Out_Vest_R", pShantaeTex, Vec2(6.f, 1344.f), Vec2(144.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 12.f), 13, 1, 13, 0.1f);
//GetAnimator()->FindAnimation(L"Time_Out_Vest_R")->Save(L"animation\\player\\Time_Out_Vest_R.anim");
//
//GetAnimator()->CreateAnimation(L"Depressed_Idle", pShantaeTex, Vec2(6.f, 1521.f), Vec2(126.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 12, 1, 12, 0.1f);
//GetAnimator()->FindAnimation(L"Depressed_Idle")->Save(L"animation\\player\\Depressed_Idle.anim");
//GetAnimator()->CreateAnimation(L"Depressed_Idle_R", pShantaeTex_R, Vec2(6.f, 1521.f), Vec2(126.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 12, 1, 12, 0.1f);
//GetAnimator()->FindAnimation(L"Depressed_Idle_R")->Save(L"animation\\player\\Depressed_Idle_R.anim");
//
//GetAnimator()->CreateAnimation(L"Exp_Angry", pShantaeTex, Vec2(6.f, 1701.f), Vec2(144.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 8, 1, 8, 0.1f);
//GetAnimator()->FindAnimation(L"Exp_Angry")->Save(L"animation\\player\\Exp_Angry.anim");
//GetAnimator()->CreateAnimation(L"Exp_Angry_R", pShantaeTex_R, Vec2(6.f, 1701.f), Vec2(144.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 8, 1, 8, 0.1f);
//GetAnimator()->FindAnimation(L"Exp_Angry_R")->Save(L"animation\\player\\Exp_Angry_R.anim");
//
//GetAnimator()->CreateAnimation(L"Exp_Cheer", pShantaeTex, Vec2(6.f, 1878.f), Vec2(162.f, 147.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 8, 1, 8, 0.1f);
//GetAnimator()->FindAnimation(L"Exp_Cheer")->Save(L"animation\\player\\Exp_Cheer.anim");
//GetAnimator()->CreateAnimation(L"Exp_Cheer_R", pShantaeTex, Vec2(6.f, 1878.f), Vec2(162.f, 147.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 8, 1, 8, 0.1f);
//GetAnimator()->FindAnimation(L"Exp_Cheer_R")->Save(L"animation\\player\\Exp_Cheer_R.anim");
//
//GetAnimator()->CreateAnimation(L"Exp_Shocked", pShantaeTex, Vec2(6.f, 2067.f), Vec2(144.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 2, 1, 2, 0.1f);
//GetAnimator()->FindAnimation(L"Exp_Shocked")->Save(L"animation\\player\\Exp_Shocked.anim");
//GetAnimator()->CreateAnimation(L"Exp_Shocked_R", pShantaeTex_R, Vec2(6.f, 2067.f), Vec2(144.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 2, 1, 2, 0.1f);
//GetAnimator()->FindAnimation(L"Exp_Shocked_R")->Save(L"animation\\player\\Exp_Shocked_R.anim");
//
//GetAnimator()->CreateAnimation(L"Walk", pShantaeTex, Vec2(6.f, 2244.f), Vec2(162.f, 147.f), Vec2(0.f, 0.f), Vec2(6.f, 15.f), 18, 2, 12, 0.05f);
//GetAnimator()->FindAnimation(L"Walk")->Save(L"animation\\player\\Walk.anim");
//GetAnimator()->CreateAnimation(L"Walk_R", pShantaeTex_R, Vec2(6.f, 2244.f), Vec2(162.f, 147.f), Vec2(0.f, 0.f), Vec2(6.f, 15.f), 18, 2, 12, 0.05f);
//GetAnimator()->FindAnimation(L"Walk_R")->Save(L"animation\\player\\Walk_R.anim");
//
//GetAnimator()->CreateAnimation(L"Walk_Stop", pShantaeTex, Vec2(6.f, 2592.f), Vec2(180.f, 147.f), Vec2(0.f, 0.f), Vec2(6.f, 15.f), 10, 1, 10, 0.08f);
//GetAnimator()->FindAnimation(L"Walk_Stop")->Save(L"animation\\player\\Walk_Stop.anim");
//GetAnimator()->CreateAnimation(L"Walk_Stop_R", pShantaeTex_R, Vec2(6.f, 2592.f), Vec2(180.f, 147.f), Vec2(0.f, 0.f), Vec2(6.f, 15.f), 10, 1, 10, 0.08f);
//GetAnimator()->FindAnimation(L"Walk_Stop_R")->Save(L"animation\\player\\Walk_Stop_R.anim");
//
//GetAnimator()->CreateAnimation(L"Run", pShantaeTex, Vec2(6.f, 2781.f), Vec2(234.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 12.f), 16, 2, 12, 0.025f);
//GetAnimator()->FindAnimation(L"Run")->Save(L"animation\\player\\Run.anim");
//GetAnimator()->CreateAnimation(L"Run_R", pShantaeTex_R, Vec2(6.f, 2781.f), Vec2(234.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 12.f), 16, 2, 12, 0.025f);
//GetAnimator()->FindAnimation(L"Run_R")->Save(L"animation\\player\\Run_R.anim");
//
//GetAnimator()->CreateAnimation(L"Run_Stop", pShantaeTex, Vec2(6.f, 3117.f), Vec2(234.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 11, 1, 11, 0.08f);
//GetAnimator()->FindAnimation(L"Run_Stop")->Save(L"animation\\player\\Run_Stop.anim");
//GetAnimator()->CreateAnimation(L"Run_Stop_R", pShantaeTex_R, Vec2(6.f, 3117.f), Vec2(234.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 11, 1, 11, 0.08f);
//GetAnimator()->FindAnimation(L"Run_Stop_R")->Save(L"animation\\player\\Run_Stop_R.anim");
//
//GetAnimator()->CreateAnimation(L"Run_Boost", pShantaeTex, Vec2(6.f, 3300.f), Vec2(270.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 5, 1, 5, 0.1f);
//GetAnimator()->FindAnimation(L"Run_Boost")->Save(L"animation\\player\\Run_Boost.anim");
//GetAnimator()->CreateAnimation(L"Run_Boost_R", pShantaeTex_R, Vec2(6.f, 3300.f), Vec2(270.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 5, 1, 5, 0.1f);
//GetAnimator()->FindAnimation(L"Run_Boost_R")->Save(L"animation\\player\\Run_Boost_R.anim");
//
//GetAnimator()->CreateAnimation(L"Slide", pShantaeTex, Vec2(6.f, 3471.f), Vec2(234.f, 129.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 4, 1, 4, 0.1f);
//GetAnimator()->FindAnimation(L"Slide")->Save(L"animation\\player\\Slide.anim");
//GetAnimator()->CreateAnimation(L"Slide_R", pShantaeTex_R, Vec2(6.f, 3471.f), Vec2(234.f, 129.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 4, 1, 4, 0.1f);
//GetAnimator()->FindAnimation(L"Slide_R")->Save(L"animation\\player\\Slide_R.anim");
//
//GetAnimator()->CreateAnimation(L"Jump", pShantaeTex, Vec2(6.f, 3636.f), Vec2(126.f, 150.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 4, 1, 4, 0.025f);
//GetAnimator()->FindAnimation(L"Jump")->Save(L"animation\\player\\Jump.anim");
//GetAnimator()->CreateAnimation(L"Jump_R", pShantaeTex_R, Vec2(6.f, 3636.f), Vec2(126.f, 150.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 4, 1, 4, 0.025f);
//GetAnimator()->FindAnimation(L"Jump_R")->Save(L"animation\\player\\Jump_R.anim");
//
//GetAnimator()->CreateAnimation(L"Jump_Tuck", pShantaeTex, Vec2(6.f, 3825.f), Vec2(126.f, 147.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 4, 1, 4, 0.05f);
//GetAnimator()->FindAnimation(L"Jump_Tuck")->Save(L"animation\\player\\Jump_Tuck.anim");
//GetAnimator()->CreateAnimation(L"Jump_Tuck_R", pShantaeTex_R, Vec2(6.f, 3825.f), Vec2(126.f, 147.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 4, 1, 4, 0.05f);
//GetAnimator()->FindAnimation(L"Jump_Tuck_R")->Save(L"animation\\player\\Jump_Tuck_R.anim");
//
//GetAnimator()->CreateAnimation(L"Fall", pShantaeTex, Vec2(6.f, 4014.f), Vec2(144.f, 198.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 4, 1, 4, 0.1f);
//GetAnimator()->FindAnimation(L"Fall")->Save(L"animation\\player\\Fall.anim");
//GetAnimator()->CreateAnimation(L"Fall_R", pShantaeTex_R, Vec2(6.f, 4014.f), Vec2(144.f, 198.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 4, 1, 4, 0.1f);
//GetAnimator()->FindAnimation(L"Fall_R")->Save(L"animation\\player\\Fall_R.anim");
//
//GetAnimator()->CreateAnimation(L"Land", pShantaeTex, Vec2(6.f, 4269.f), Vec2(180.f, 141.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 6, 1, 6, 0.05f);
//GetAnimator()->FindAnimation(L"Land")->Save(L"animation\\player\\Land.anim");
//GetAnimator()->CreateAnimation(L"Land_R", pShantaeTex_R, Vec2(6.f, 4269.f), Vec2(180.f, 141.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 6, 1, 6, 0.05f);
//GetAnimator()->FindAnimation(L"Land_R")->Save(L"animation\\player\\Land_R.anim");
//
//GetAnimator()->CreateAnimation(L"Duck", pShantaeTex, Vec2(6.f, 4452.f), Vec2(144.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 7, 1, 7, 0.03f);
//GetAnimator()->FindAnimation(L"Duck")->Save(L"animation\\player\\Duck.anim");
//GetAnimator()->CreateAnimation(L"Duck_R", pShantaeTex_R, Vec2(6.f, 4452.f), Vec2(144.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 7, 1, 7, 0.03f);
//GetAnimator()->FindAnimation(L"Duck_R")->Save(L"animation\\player\\Duck_R.anim");
//
//GetAnimator()->CreateAnimation(L"Duck_Idle", pShantaeTex, Vec2(6.f, 4629.f), Vec2(126.f, 87.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 10, 1, 10, 0.1f);
//GetAnimator()->FindAnimation(L"Duck_Idle")->Save(L"animation\\player\\Duck_Idle.anim");
//GetAnimator()->CreateAnimation(L"Duck_Idle_R", pShantaeTex_R, Vec2(6.f, 4629.f), Vec2(126.f, 87.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 10, 1, 10, 0.1f);
//GetAnimator()->FindAnimation(L"Duck_Idle_R")->Save(L"animation\\player\\Duck_Idle_R.anim");
//
//GetAnimator()->CreateAnimation(L"Duck_Get_Hit", pShantaeTex, Vec2(6.f, 4770.f), Vec2(180.f, 87.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 13, 1, 13, 0.1f);
//GetAnimator()->FindAnimation(L"Duck_Get_Hit")->Save(L"animation\\player\\Duck_Get_Hit.anim");
//GetAnimator()->CreateAnimation(L"Duck_Get_Hit_R", pShantaeTex_R, Vec2(6.f, 4770.f), Vec2(180.f, 87.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 13, 1, 13, 0.1f);
//GetAnimator()->FindAnimation(L"Duck_Get_Hit_R")->Save(L"animation\\player\\Duck_Get_Hit_R.anim");
//
//GetAnimator()->CreateAnimation(L"Duck_Get_Hit2", pShantaeTex, Vec2(6.f, 4899.f), Vec2(126.f, 99.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 7, 1, 7, 0.05f);
//GetAnimator()->FindAnimation(L"Duck_Get_Hit2")->Save(L"animation\\player\\Duck_Get_Hit2.anim");
//GetAnimator()->CreateAnimation(L"Duck_Get_Hit2_R", pShantaeTex_R, Vec2(6.f, 4899.f), Vec2(126.f, 99.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 7, 1, 7, 0.05f);
//GetAnimator()->FindAnimation(L"Duck_Get_Hit2_R")->Save(L"animation\\player\\Duck_Get_Hit2_R.anim");
//
//GetAnimator()->CreateAnimation(L"Duck_Whip", pShantaeTex, Vec2(6.f, 5040.f), Vec2(324.f, 99.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 8, 1, 8, 0.025f);
//GetAnimator()->FindAnimation(L"Duck_Whip")->Save(L"animation\\player\\Duck_Whip.anim");
//GetAnimator()->CreateAnimation(L"Duck_Whip_R", pShantaeTex_R, Vec2(6.f, 5040.f), Vec2(324.f, 99.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 8, 1, 8, 0.025f);
//GetAnimator()->FindAnimation(L"Duck_Whip_R")->Save(L"animation\\player\\Duck_Whip_R.anim");
//
//GetAnimator()->CreateAnimation(L"Crawl", pShantaeTex, Vec2(6.f, 5181.f), Vec2(162.f, 87.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 10, 1, 10, 0.1f);
//GetAnimator()->FindAnimation(L"Crawl")->Save(L"animation\\player\\Crawl.anim");
//GetAnimator()->CreateAnimation(L"Crawl_R", pShantaeTex_R, Vec2(6.f, 5181.f), Vec2(162.f, 87.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 10, 1, 10, 0.1f);
//GetAnimator()->FindAnimation(L"Crawl_R")->Save(L"animation\\player\\Crawl_R.anim");
//
//GetAnimator()->CreateAnimation(L"Getup", pShantaeTex, Vec2(6.f, 5310.f), Vec2(144.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 8, 1, 8, 0.1f);
//GetAnimator()->FindAnimation(L"Getup")->Save(L"animation\\player\\Getup.anim");
//GetAnimator()->CreateAnimation(L"Getup_R", pShantaeTex_R, Vec2(6.f, 5310.f), Vec2(144.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 8, 1, 8, 0.1f);
//GetAnimator()->FindAnimation(L"Getup_R")->Save(L"animation\\player\\Getup_R.anim");
//
//GetAnimator()->CreateAnimation(L"Standing_Whip", pShantaeTex, Vec2(6.f, 5487.f), Vec2(342.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 8, 1, 8, 0.05f);
//GetAnimator()->FindAnimation(L"Standing_Whip")->Save(L"animation\\player\\Standing_Whip.anim");
//GetAnimator()->CreateAnimation(L"Standing_Whip_R", pShantaeTex_R, Vec2(6.f, 5487.f), Vec2(342.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 8, 1, 8, 0.05f);
//GetAnimator()->FindAnimation(L"Standing_Whip_R")->Save(L"animation\\player\\Standing_Whip_R.anim");
//
//GetAnimator()->CreateAnimation(L"Standing_Whip_Long", pShantaeTex, Vec2(6.f, 5664.f), Vec2(402.f, 135.f), Vec2(0.f, 0.f), Vec2(0.f, 0.f), 12, 1, 12, 0.04f);
//GetAnimator()->FindAnimation(L"Standing_Whip_Long")->Save(L"animation\\player\\Standing_Whip_Long.anim");
//GetAnimator()->CreateAnimation(L"Standing_Whip_Long_R", pShantaeTex_R, Vec2(6.f, 5664.f), Vec2(402.f, 135.f), Vec2(0.f, 0.f), Vec2(0.f, 0.f), 12, 1, 12, 0.04f);
//GetAnimator()->FindAnimation(L"Standing_Whip_Long_R")->Save(L"animation\\player\\Standing_Whip_Long_R.anim");
//
//GetAnimator()->CreateAnimation(L"Jump_Whip", pShantaeTex, Vec2(6.f, 5847.f), Vec2(342.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 8, 1, 8, 0.05f);
//GetAnimator()->FindAnimation(L"Jump_Whip")->Save(L"animation\\player\\Jump_Whip.anim");
//GetAnimator()->CreateAnimation(L"Jump_Whip_R", pShantaeTex_R, Vec2(6.f, 5847.f), Vec2(342.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 8, 1, 8, 0.05f);
//GetAnimator()->FindAnimation(L"Jump_Whip_R")->Save(L"animation\\player\\Jump_Whip_R.anim");
//
//GetAnimator()->CreateAnimation(L"Enter", pShantaeTex, Vec2(6.f, 6018.f), Vec2(144.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 12.f), 39, 4, 12, 0.02f);
//GetAnimator()->FindAnimation(L"Enter")->Save(L"animation\\player\\Enter.anim");
//GetAnimator()->CreateAnimation(L"Enter_R", pShantaeTex_R, Vec2(6.f, 6018.f), Vec2(144.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 12.f), 39, 4, 12, 0.02f);
//GetAnimator()->FindAnimation(L"Enter_R")->Save(L"animation\\player\\Enter_R.anim");
////
//GetAnimator()->CreateAnimation(L"Exit", pShantaeTex, Vec2(6.f, 6649.f), Vec2(144.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 12.f), 24, 2, 12, 0.05f);
//GetAnimator()->FindAnimation(L"Exit")->Save(L"animation\\player\\Exit.anim");
//GetAnimator()->CreateAnimation(L"Exit_R", pShantaeTex_R, Vec2(6.f, 6649.f), Vec2(144.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 12.f), 24, 2, 12, 0.05f);
//GetAnimator()->FindAnimation(L"Exit_R")->Save(L"animation\\player\\Exit_R.anim");
//
//GetAnimator()->CreateAnimation(L"Eat", pShantaeTex, Vec2(6.f, 6984.f), Vec2(180.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 15.f), 21, 2, 12, 0.075f);
//GetAnimator()->FindAnimation(L"Eat")->Save(L"animation\\player\\Eat.anim");
//GetAnimator()->CreateAnimation(L"Eat_R", pShantaeTex_R, Vec2(6.f, 6984.f), Vec2(180.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 15.f), 21, 2, 12, 0.075f);
//GetAnimator()->FindAnimation(L"Eat_R")->Save(L"animation\\player\\Eat_R.anim");
//
//GetAnimator()->CreateAnimation(L"Drink", pShantaeTex, Vec2(6.f, 7314.f), Vec2(180.f, 150.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 20, 2, 12, 0.075f);
//GetAnimator()->FindAnimation(L"Drink")->Save(L"animation\\player\\Drink.anim");
//GetAnimator()->CreateAnimation(L"Drink_R", pShantaeTex_R, Vec2(6.f, 7314.f), Vec2(180.f, 150.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 20, 2, 12, 0.075f);
//GetAnimator()->FindAnimation(L"Drink_R")->Save(L"animation\\player\\Drink_R.anim");
//
//GetAnimator()->CreateAnimation(L"Dance", pShantaeTex, Vec2(6.f, 7656.f), Vec2(162.f, 141.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 16, 2, 12, 0.07f);
//GetAnimator()->FindAnimation(L"Dance")->Save(L"animation\\player\\Dance.anim");
//GetAnimator()->CreateAnimation(L"Dance_R", pShantaeTex_R, Vec2(6.f, 7656.f), Vec2(162.f, 141.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 16, 2, 12, 0.07f);
//GetAnimator()->FindAnimation(L"Dance_R")->Save(L"animation\\player\\Dance_R.anim");
//
//GetAnimator()->CreateAnimation(L"Twirl_Loop", pShantaeTex, Vec2(6.f, 7980.f), Vec2(144.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 12.f), 16, 2, 12, 0.05f);
//GetAnimator()->FindAnimation(L"Twirl_Loop")->Save(L"animation\\player\\Twirl_Loop.anim");
//GetAnimator()->CreateAnimation(L"Twirl_Loop_R", pShantaeTex_R, Vec2(6.f, 7980.f), Vec2(144.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 12.f), 16, 2, 12, 0.05f);
//GetAnimator()->FindAnimation(L"Twirl_Loop_R")->Save(L"animation\\player\\Twirl_Loop_R.anim");
//
//GetAnimator()->CreateAnimation(L"Rope_Idle", pShantaeTex, Vec2(6.f, 8304.f), Vec2(90.f, 120.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 4, 1, 4, 0.1f);
//GetAnimator()->FindAnimation(L"Rope_Idle")->Save(L"animation\\player\\Rope_Idle.anim");
//GetAnimator()->CreateAnimation(L"Rope_Idle_R", pShantaeTex_R, Vec2(6.f, 8304.f), Vec2(90.f, 120.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 4, 1, 4, 0.1f);
//GetAnimator()->FindAnimation(L"Rope_Idle_R")->Save(L"animation\\player\\Rope_Idle_R.anim");
//
//GetAnimator()->CreateAnimation(L"Rope_Climb_Normal", pShantaeTex, Vec2(6.f, 8469.f), Vec2(108.f, 129.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 12, 1, 12, 0.1f);
//GetAnimator()->FindAnimation(L"Rope_Climb_Normal")->Save(L"animation\\player\\Rope_Climb_Normal.anim");
//GetAnimator()->CreateAnimation(L"Rope_Climb_Normal_R", pShantaeTex_R, Vec2(6.f, 8469.f), Vec2(108.f, 129.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 12, 1, 12, 0.1f);
//GetAnimator()->FindAnimation(L"Rope_Climb_Normal_R")->Save(L"animation\\player\\Rope_Climb_Normal_R.anim");
//
//GetAnimator()->CreateAnimation(L"Rope_Down", pShantaeTex, Vec2(6.f, 8634.f), Vec2(108.f, 123.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 4, 1, 4, 0.1f);
//GetAnimator()->FindAnimation(L"Rope_Down")->Save(L"animation\\player\\Rope_Down.anim");
//GetAnimator()->CreateAnimation(L"Rope_Down_R", pShantaeTex_R, Vec2(6.f, 8634.f), Vec2(108.f, 123.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 4, 1, 4, 0.1f);
//GetAnimator()->FindAnimation(L"Rope_Down_R")->Save(L"animation\\player\\Rope_Down_R.anim");
//
//GetAnimator()->CreateAnimation(L"Hang_Idle", pShantaeTex, Vec2(6.f, 8793.f), Vec2(108.f, 141.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 4, 1, 4, 0.1f);
//GetAnimator()->FindAnimation(L"Hang_Idle")->Save(L"animation\\player\\Hang_Idle.anim");
//GetAnimator()->CreateAnimation(L"Hang_Idle_R", pShantaeTex_R, Vec2(6.f, 8793.f), Vec2(108.f, 141.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 4, 1, 4, 0.1f);
//GetAnimator()->FindAnimation(L"Hang_Idle_R")->Save(L"animation\\player\\Hang_Idle_R.anim");
//
//GetAnimator()->CreateAnimation(L"Hang_Flip_Up", pShantaeTex, Vec2(6.f, 8970.f), Vec2(144.f, 165.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 26, 3, 12, 0.04f);
//GetAnimator()->FindAnimation(L"Hang_Flip_Up")->Save(L"animation\\player\\Hang_Flip_Up.anim");
//GetAnimator()->CreateAnimation(L"Hang_Flip_Up_R", pShantaeTex_R, Vec2(6.f, 8970.f), Vec2(144.f, 165.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 26, 3, 12, 0.04f);
//GetAnimator()->FindAnimation(L"Hang_Flip_Up_R")->Save(L"animation\\player\\Hang_Flip_Up_R.anim");
//
//GetAnimator()->CreateAnimation(L"Swim_Tread_Water", pShantaeTex, Vec2(6.f, 9513.f), Vec2(180.f, 153.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 6, 1, 6, 0.1f);
//GetAnimator()->FindAnimation(L"Swim_Tread_Water")->Save(L"animation\\player\\Swim_Tread_Water.anim");
//
//GetAnimator()->CreateAnimation(L"Swim_Paddle", pShantaeTex, Vec2(6.f, 9702.f), Vec2(234.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 10, 1, 10, 0.1f);
//GetAnimator()->FindAnimation(L"Swim_Paddle")->Save(L"animation\\player\\Swim_Paddle.anim");
//
//GetAnimator()->CreateAnimation(L"Swim_Surface", pShantaeTex, Vec2(6.f, 9873.f), Vec2(216.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 10, 1, 10, 0.1f);
//GetAnimator()->FindAnimation(L"Swim_Surface")->Save(L"animation\\player\\Swim_Surface.anim");
//
//GetAnimator()->CreateAnimation(L"Heavy_Kick", pShantaeTex, Vec2(6.f, 10044.f), Vec2(288.f, 153.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 11, 1, 11, 0.05f);
//GetAnimator()->FindAnimation(L"Heavy_Kick")->Save(L"animation\\player\\Heavy_Kick.anim");
//
//GetAnimator()->CreateAnimation(L"Down_Thrust", pShantaeTex, Vec2(6.f, 10287.f), Vec2(144.f, 165.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 3, 1, 3, 0.08f);
//GetAnimator()->FindAnimation(L"Down_Thrust")->Save(L"animation\\player\\Down_Thrust.anim");
//GetAnimator()->CreateAnimation(L"Down_Thrust_R", pShantaeTex_R, Vec2(6.f, 10287.f), Vec2(144.f, 165.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 3, 1, 3, 0.08f);
//GetAnimator()->FindAnimation(L"Down_Thrust_R")->Save(L"animation\\player\\Down_Thrust_R.anim");
//
//GetAnimator()->CreateAnimation(L"BackDash", pShantaeTex, Vec2(6.f, 10491.f), Vec2(180.f, 153.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 11, 1, 11, 0.05f);
//GetAnimator()->FindAnimation(L"BackDash")->Save(L"animation\\player\\BackDash.anim");
//
//GetAnimator()->CreateAnimation(L"Hat_Init", pShantaeTex, Vec2(6.f, 10680.f), Vec2(252.f, 297.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 6, 1, 6, 0.1f);
//GetAnimator()->FindAnimation(L"Hat_Init")->Save(L"animation\\player\\Hat_Init.anim");
//GetAnimator()->CreateAnimation(L"Hat_Init_R", pShantaeTex_R, Vec2(6.f, 10680.f), Vec2(252.f, 297.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 6, 1, 6, 0.1f);
//GetAnimator()->FindAnimation(L"Hat_Init_R")->Save(L"animation\\player\\Hat_Init_R.anim");
//
//GetAnimator()->CreateAnimation(L"Hat_Glide", pShantaeTex, Vec2(6.f, 11013.f), Vec2(234.f, 234.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 8, 1, 8, 0.1f);
//GetAnimator()->FindAnimation(L"Hat_Glide")->Save(L"animation\\player\\Hat_Glide.anim");
//GetAnimator()->CreateAnimation(L"Hat_Glide_R", pShantaeTex_R, Vec2(6.f, 11013.f), Vec2(234.f, 234.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 8, 1, 8, 0.1f);
//GetAnimator()->FindAnimation(L"Hat_Glide_R")->Save(L"animation\\player\\Hat_Glide_R.anim");
//
//GetAnimator()->CreateAnimation(L"Hat_Remove", pShantaeTex, Vec2(6.f, 11286.f), Vec2(252.f, 297.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 6, 1, 6, 0.1f);
//GetAnimator()->FindAnimation(L"Hat_Remove")->Save(L"animation\\player\\Hat_Remove.anim");
//GetAnimator()->CreateAnimation(L"Hat_Remove_R", pShantaeTex_R, Vec2(6.f, 11286.f), Vec2(252.f, 297.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 6, 1, 6, 0.1f);
//GetAnimator()->FindAnimation(L"Hat_Remove_R")->Save(L"animation\\player\\Hat_Remove_R.anim");
//
//GetAnimator()->CreateAnimation(L"Cannon_Normal", pShantaeTex, Vec2(6.f, 11619.f), Vec2(198.f, 249.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 13, 1, 13, 0.1f);
//GetAnimator()->FindAnimation(L"Cannon_Normal")->Save(L"animation\\player\\Cannon_Normal.anim");
//GetAnimator()->CreateAnimation(L"Cannon_Normal_R", pShantaeTex_R, Vec2(6.f, 11619.f), Vec2(198.f, 249.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 13, 1, 13, 0.1f);
//GetAnimator()->FindAnimation(L"Cannon_Normal_R")->Save(L"animation\\player\\Cannon_Normal_R.anim");
//
//GetAnimator()->CreateAnimation(L"Pirate_Flare", pShantaeTex, Vec2(6.f, 11904.f), Vec2(288.f, 183.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 32, 3, 12, 0.1f);
//GetAnimator()->FindAnimation(L"Pirate_Flare")->Save(L"animation\\player\\Pirate_Flare.anim");
//GetAnimator()->CreateAnimation(L"Pirate_Flare_R", pShantaeTex_R, Vec2(6.f, 11904.f), Vec2(288.f, 183.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 32, 3, 12, 0.1f);
//GetAnimator()->FindAnimation(L"Pirate_Flare_R")->Save(L"animation\\player\\Pirate_Flare_R.anim");
//
//GetAnimator()->CreateAnimation(L"Pistol_Pullout", pShantaeTex, Vec2(6.f, 12501.f), Vec2(234.f, 123.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 5, 1, 5, 0.06f);
//GetAnimator()->FindAnimation(L"Pistol_Pullout")->Save(L"animation\\player\\Pistol_Pullout.anim");
//GetAnimator()->CreateAnimation(L"Pistol_Pullout_R", pShantaeTex_R, Vec2(6.f, 12501.f), Vec2(234.f, 123.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 5, 1, 5, 0.06f);
//GetAnimator()->FindAnimation(L"Pistol_Pullout_R")->Save(L"animation\\player\\Pistol_Pullout_R.anim");
//
//GetAnimator()->CreateAnimation(L"Pistol_Blast", pShantaeTex, Vec2(6.f, 12666.f), Vec2(216.f, 147.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 6, 1, 6, 0.07f);
//GetAnimator()->FindAnimation(L"Pistol_Blast")->Save(L"animation\\player\\Pistol_Blast.anim");
//GetAnimator()->CreateAnimation(L"Pistol_Blast_R", pShantaeTex_R, Vec2(6.f, 12666.f), Vec2(216.f, 147.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 6, 1, 6, 0.07f);
//GetAnimator()->FindAnimation(L"Pistol_Blast_R")->Save(L"animation\\player\\Pistol_Blast_R.anim");
//
//GetAnimator()->CreateAnimation(L"Pistol_Blast_Jump", pShantaeTex, Vec2(6.f, 12855.f), Vec2(234.f, 150.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 6, 1, 6, 0.07f);
//GetAnimator()->FindAnimation(L"Pistol_Blast_Jump")->Save(L"animation\\player\\Pistol_Blast_Jump.anim");
//GetAnimator()->CreateAnimation(L"Pistol_Blast_Jump_R", pShantaeTex_R, Vec2(6.f, 12855.f), Vec2(234.f, 150.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 6, 1, 6, 0.07f);
//GetAnimator()->FindAnimation(L"Pistol_Blast_Jump_R")->Save(L"animation\\player\\Pistol_Blast_Jump_R.anim");
//
//GetAnimator()->CreateAnimation(L"Boots_Run", pShantaeTex, Vec2(6.f, 13044.f), Vec2(288.f, 141.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 8, 1, 8, 0.075f);
//GetAnimator()->FindAnimation(L"Boots_Run")->Save(L"animation\\player\\Boots_Run.anim");
//
//GetAnimator()->CreateAnimation(L"Boots_Jump", pShantaeTex, Vec2(6.f, 13221.f), Vec2(126.f, 153.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 4, 1, 4, 0.075f);
//GetAnimator()->FindAnimation(L"Boots_Jump")->Save(L"animation\\player\\Boots_Jump.anim");
//
//GetAnimator()->CreateAnimation(L"Boots_Wall", pShantaeTex, Vec2(6.f, 13410.f), Vec2(198.f, 165.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 8, 1, 8, 0.075f);
//GetAnimator()->FindAnimation(L"Boots_Wall")->Save(L"animation\\player\\Boots_Wall.anim");
//
//GetAnimator()->CreateAnimation(L"Lamp_Dance", pShantaeTex, Vec2(6.f, 13611.f), Vec2(180.f, 165.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 16, 2, 12, 0.05f);
//GetAnimator()->FindAnimation(L"Lamp_Dance")->Save(L"animation\\player\\Lamp_Dance.anim");
//
//GetAnimator()->CreateAnimation(L"Lamp_Suck", pShantaeTex, Vec2(6.f, 13983.f), Vec2(198.f, 165.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 13, 1, 13, 0.075f);
//GetAnimator()->FindAnimation(L"Lamp_Suck")->Save(L"animation\\player\\Lamp_Suck.anim");
//
//GetAnimator()->CreateAnimation(L"Hurt", pShantaeTex, Vec2(6.f, 14184.f), Vec2(144.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 9, 1, 9, 0.075f);
//GetAnimator()->FindAnimation(L"Hurt")->Save(L"animation\\player\\Hurt.anim");
//GetAnimator()->CreateAnimation(L"Hurt_R", pShantaeTex_R, Vec2(6.f, 14184.f), Vec2(144.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 9, 1, 9, 0.075f);
//GetAnimator()->FindAnimation(L"Hurt_R")->Save(L"animation\\player\\Hurt_R.anim");
//
//GetAnimator()->CreateAnimation(L"Standing_Get_Hit", pShantaeTex, Vec2(6.f, 14361.f), Vec2(162.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 13, 1, 13, 0.075f);
//GetAnimator()->FindAnimation(L"Standing_Get_Hit")->Save(L"animation\\player\\Standing_Get_Hit.anim");
//GetAnimator()->CreateAnimation(L"Standing_Get_Hit_R", pShantaeTex_R, Vec2(6.f, 14361.f), Vec2(162.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 13, 1, 13, 0.075f);
//GetAnimator()->FindAnimation(L"Standing_Get_Hit_R")->Save(L"animation\\player\\Standing_Get_Hit_R.anim");
//
//GetAnimator()->CreateAnimation(L"Standup", pShantaeTex, Vec2(6.f, 14538.f), Vec2(144.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 3, 1, 3, 0.05f);
//GetAnimator()->FindAnimation(L"Standup")->Save(L"animation\\player\\Standup.anim");
//GetAnimator()->CreateAnimation(L"Standup_R", pShantaeTex_R, Vec2(6.f, 14538.f), Vec2(144.f, 135.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 3, 1, 3, 0.05f);
//GetAnimator()->FindAnimation(L"Standup_R")->Save(L"animation\\player\\Standup_R.anim");
//
//GetAnimator()->CreateAnimation(L"Knockdown", pShantaeTex, Vec2(6.f, 14715.f), Vec2(252.f, 147.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 25, 2, 13, 0.075f);
//GetAnimator()->FindAnimation(L"Knockdown")->Save(L"animation\\player\\Knockdown.anim");
//GetAnimator()->CreateAnimation(L"Knockdown_R", pShantaeTex_R, Vec2(6.f, 14715.f), Vec2(252.f, 147.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 25, 2, 13, 0.075f);
//GetAnimator()->FindAnimation(L"Knockdown_R")->Save(L"animation\\player\\Knockdown_R.anim");
//
//
//
//GetAnimator()->CreateAnimation(L"Die", pShantaeTex, Vec2(6.f, 15498.f), Vec2(180.f, 123.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 11, 1, 11, 0.1f);
//GetAnimator()->FindAnimation(L"Die")->Save(L"animation\\player\\Die.anim");
//GetAnimator()->CreateAnimation(L"Die_R", pShantaeTex_R, Vec2(6.f, 15498.f), Vec2(180.f, 123.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 11, 1, 11, 0.1f);
//GetAnimator()->FindAnimation(L"Die_R")->Save(L"animation\\player\\Die_R.anim");
//
//GetAnimator()->CreateAnimation(L"Wakeup", pShantaeTex, Vec2(6.f, 15663.f), Vec2(180.f, 123.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 10, 1, 10, 0.1f);
//GetAnimator()->FindAnimation(L"Wakeup")->Save(L"animation\\player\\Wakeup.anim");
//GetAnimator()->CreateAnimation(L"Wakeup_R", pShantaeTex_R, Vec2(6.f, 15663.f), Vec2(180.f, 123.f), Vec2(0.f, 0.f), Vec2(6.f, 6.f), 10, 1, 10, 0.1f);
//GetAnimator()->FindAnimation(L"Wakeup_R")->Save(L"animation\\player\\Wakeup_R.anim");

GetAnimator()->LoadAnimation(L"animation\\player\\Standing_Idle.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Standing_Idle_Full.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Standing_Idle_Long.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Time_Out_Pants.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Time_Out_Top.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Time_Out_Vest.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Depressed_Idle.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Exp_Angry.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Exp_Cheer.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Exp_Shocked.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Walk.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Walk_Stop.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Run.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Run_Stop.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Slide.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Jump.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Jump_Tuck.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Fall.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Land.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Duck.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Duck_Idle.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Duck_Get_Hit.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Duck_Get_Hit2.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Duck_Whip.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Crawl.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Getup.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Standing_Whip.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Standing_Whip_Long.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Jump_Whip.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Enter.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Exit.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Eat.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Drink.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Dance.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Twirl_Loop.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Rope_Idle.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Rope_Climb_Normal.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Rope_Down.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Hang_Idle.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Hang_Flip_Up.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Swim_Tread_Water.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Swim_Paddle.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Swim_Surface.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Heavy_Kick.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Down_Thrust.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\BackDash.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Hat_Init.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Hat_Glide.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Hat_Remove.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Cannon_Normal.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Pirate_Flare.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Pistol_Pullout.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Pistol_Blast.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Pistol_Blast_Jump.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Boots_Run.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Boots_Jump.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Boots_Wall.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Lamp_Dance.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Lamp_Suck.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Hurt.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Standing_Get_Hit.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Standup.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\KnockDown.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\KnockDown_1.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\KnockDown_2.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Die.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Wakeup.anim");


GetAnimator()->LoadAnimation(L"animation\\player\\Standing_Idle_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Standing_Idle_Full_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Standing_Idle_Long_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Time_Out_Pants_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Time_Out_Top_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Time_Out_Vest_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Depressed_Idle_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Exp_Angry_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Exp_Cheer_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Exp_Shocked_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Walk_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Walk_Stop_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Run_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Run_Stop_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Slide_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Jump_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Jump_Tuck_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Fall_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Land_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Duck_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Duck_Idle_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Duck_Get_Hit_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Duck_Get_Hit2_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Duck_Whip_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Crawl_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Getup_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Standing_Whip_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Standing_Whip_Long_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Jump_Whip_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Enter_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Exit_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Eat_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Drink_R.anim");

GetAnimator()->LoadAnimation(L"animation\\player\\Down_Thrust_R.anim");

GetAnimator()->LoadAnimation(L"animation\\player\\Hat_Init_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Hat_Glide_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Hat_Remove_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Cannon_Normal_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Pirate_Flare_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Pistol_Pullout_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Pistol_Blast_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Pistol_Blast_Jump_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Hurt_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Standing_Get_Hit_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Standup_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\KnockDown_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\KnockDown_R_1.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\KnockDown_R_2.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Die_R.anim");
GetAnimator()->LoadAnimation(L"animation\\player\\Wakeup_R.anim");
}


