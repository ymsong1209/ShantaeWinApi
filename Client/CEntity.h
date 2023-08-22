#pragma once
class CEntity
{
private:
	static UINT g_iNextID;
private:
	wstring		m_strName;
	const UINT	m_id;
public:
	void SetName(const wstring& _str){m_strName = _str;}
	const wstring& GetName() { return m_strName; }
	UINT GetID() { return m_id; }
	//다른 언어에는 clone이라는 인터페이스가 있다.
	//일일히 복사 생성자를 수동으로 호출하는 것이 아니라
	//객체를 복사할때 clone만 호출하면 복사가 되도록 구현해보자
	virtual CEntity* Clone() = 0;
public:
	CEntity();
	CEntity(const CEntity& _Origin);
	virtual ~CEntity();
};

