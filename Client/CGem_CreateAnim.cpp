#include "pch.h"
#include "CGem.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CResMgr.h"


void CGem::CreateAnim()
{
	CTexture* Gem = CResMgr::GetInst()->LoadTexture(L"Gems", L"texture\\objects\\Gems.bmp");

	/*GetAnimator()->CreateAnimation(L"Gem_Blue_Large", Gem, Vec2(5.f, 25.f), Vec2(60.f, 42.f), Vec2(0.f, 0.f), Vec2(5.f, 0.f), 12, 1, 12, 0.1f);
	GetAnimator()->FindAnimation(L"Gem_Blue_Large")->Save(L"animation\\object\\Gem_Blue_Large.anim");
	GetAnimator()->CreateAnimation(L"Gem_Green_Large", Gem, Vec2(5.f, 100.f), Vec2(60.f, 42.f), Vec2(0.f, 0.f), Vec2(5.f, 0.f), 12, 1, 12, 0.1f);
	GetAnimator()->FindAnimation(L"Gem_Green_Large")->Save(L"animation\\object\\Gem_Green_Large.anim");
	GetAnimator()->CreateAnimation(L"Gem_Purple_Large", Gem, Vec2(5.f, 175.f), Vec2(60.f, 42.f), Vec2(0.f, 0.f), Vec2(5.f, 0.f), 12, 1, 12, 0.1f);
	GetAnimator()->FindAnimation(L"Gem_Purple_Large")->Save(L"animation\\object\\Gem_Purple_Large.anim");
	GetAnimator()->CreateAnimation(L"Gem_Red_Large", Gem, Vec2(5.f, 250.f), Vec2(60.f, 42.f), Vec2(0.f, 0.f), Vec2(5.f, 0.f), 12, 1, 12, 0.1f);
	GetAnimator()->FindAnimation(L"Gem_Red_Large")->Save(L"animation\\object\\Gem_Red_Large.anim");

	GetAnimator()->CreateAnimation(L"Gem_Blue_Mid", Gem, Vec2(5.f, 400.f), Vec2(30.f, 42.f), Vec2(0.f, 0.f), Vec2(5.f, 0.f), 12, 1, 12, 0.1f);
	GetAnimator()->FindAnimation(L"Gem_Blue_Mid")->Save(L"animation\\object\\Gem_Blue_Mid.anim");
	GetAnimator()->CreateAnimation(L"Gem_Green_Mid", Gem, Vec2(5.f, 475.f), Vec2(30.f, 42.f), Vec2(0.f, 0.f), Vec2(5.f, 0.f), 12, 1, 12, 0.1f);
	GetAnimator()->FindAnimation(L"Gem_Green_Mid")->Save(L"animation\\object\\Gem_Green_Mid.anim");
	GetAnimator()->CreateAnimation(L"Gem_Purple_Mid", Gem, Vec2(5.f, 550.f), Vec2(30.f, 42.f), Vec2(0.f, 0.f), Vec2(5.f, 0.f), 12, 1, 12, 0.1f);
	GetAnimator()->FindAnimation(L"Gem_Purple_Mid")->Save(L"animation\\object\\Gem_Purple_Mid.anim");
	GetAnimator()->CreateAnimation(L"Gem_Red_Mid", Gem, Vec2(5.f, 625.f), Vec2(30.f, 42.f), Vec2(0.f, 0.f), Vec2(5.f, 0.f), 12, 1, 12, 0.1f);
	GetAnimator()->FindAnimation(L"Gem_Red_Mid")->Save(L"animation\\object\\Gem_Red_Mid.anim");

	GetAnimator()->CreateAnimation(L"Gem_Blue_Small", Gem, Vec2(5.f, 775.f), Vec2(30.f, 32.f), Vec2(0.f, 0.f), Vec2(5.f, 0.f), 12, 1, 12, 0.1f);
	GetAnimator()->FindAnimation(L"Gem_Blue_Small")->Save(L"animation\\object\\Gem_Blue_Small.anim");
	GetAnimator()->CreateAnimation(L"Gem_Green_Small", Gem, Vec2(5.f, 845.f), Vec2(30.f, 32.f), Vec2(0.f, 0.f), Vec2(5.f, 0.f), 12, 1, 12, 0.1f);
	GetAnimator()->FindAnimation(L"Gem_Green_Small")->Save(L"animation\\object\\Gem_Green_Small.anim");
	GetAnimator()->CreateAnimation(L"Gem_Purple_Small", Gem, Vec2(5.f, 915.f), Vec2(30.f, 32.f), Vec2(0.f, 0.f), Vec2(5.f, 0.f), 12, 1, 12, 0.1f);
	GetAnimator()->FindAnimation(L"Gem_Purple_Small")->Save(L"animation\\object\\Gem_Purple_Small.anim");
	GetAnimator()->CreateAnimation(L"Gem_Red_Small", Gem, Vec2(5.f, 985.f), Vec2(30.f, 32.f), Vec2(0.f, 0.f), Vec2(5.f, 0.f), 12, 1, 12, 0.1f);
	GetAnimator()->FindAnimation(L"Gem_Red_Small")->Save(L"animation\\object\\Gem_Red_Small.anim");*/
	


	
	GetAnimator()->LoadAnimation(L"animation\\object\\Gem_Blue_Large.anim");
	GetAnimator()->LoadAnimation(L"animation\\object\\Gem_Green_Large.anim");
	GetAnimator()->LoadAnimation(L"animation\\object\\Gem_Purple_Large.anim");
	GetAnimator()->LoadAnimation(L"animation\\object\\Gem_Red_Large.anim");

	GetAnimator()->LoadAnimation(L"animation\\object\\Gem_Blue_Mid.anim");
	GetAnimator()->LoadAnimation(L"animation\\object\\Gem_Green_Mid.anim");
	GetAnimator()->LoadAnimation(L"animation\\object\\Gem_Purple_Mid.anim");
	GetAnimator()->LoadAnimation(L"animation\\object\\Gem_Red_Mid.anim");

	GetAnimator()->LoadAnimation(L"animation\\object\\Gem_Blue_Small.anim");
	GetAnimator()->LoadAnimation(L"animation\\object\\Gem_Green_Small.anim");
	GetAnimator()->LoadAnimation(L"animation\\object\\Gem_Purple_Small.anim");
	GetAnimator()->LoadAnimation(L"animation\\object\\Gem_Red_Small.anim");
}