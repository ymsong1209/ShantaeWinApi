#pragma once
class GameInstance
{
private:
	bool m_bShowCollide;

public:
	SINGLE(GameInstance)
public:
	void SetShowCollide(bool _collide) { m_bShowCollide = _collide; }
	bool GetShowCollide() { return m_bShowCollide; }

	void tick();
};

