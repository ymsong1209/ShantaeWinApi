#include "pch.h"
#include "CItem.h"

CItem::CItem()
{

}

CItem::~CItem()
{
}

void CItem::tick()
{
	CObj::tick();
}

void CItem::render(HDC _dc)
{
	CObj::render(_dc);
}

void CItem::BeginOverlap(CCollider* _pOther)
{
}


