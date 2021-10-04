#pragma once
#include"../gameObject/GameObject.h"

enum Menu
{
	menu,
	ready,
	belonging,//装備
	equipment,//所持品
	upgrade,//強化
};

class Select : public GameObject
{
public:
	Select() {}
	~Select() {}

	void Init() override;
	void Update()override;
	void Draw2()override;
	void DrawEffect()override;

	Math::Rectangle UpdateRect(int lev) { return rect = { (33 * lev), 64, 32, 64 }; }

	void MouseMove();

	bool MouseToTexture(std::shared_ptr<KdTexture> Tex, Math::Vector2 Pos,Math::Vector2 Mouse);

	void LevelSelect();
	void UpdateMenu();

private:
	Menu select;
	Menu cursor;

	void Release();

	std::shared_ptr<KdTexture> m_TNumber;
	Math::Vector2 Pos;

	std::shared_ptr<KdTexture> m_LTexture;

	std::shared_ptr<KdTexture> m_TReady;
	Math::Rectangle rReady;

	std::shared_ptr<KdTexture> m_TBel;
	Math::Rectangle rBel;

	std::shared_ptr<KdTexture> m_TCor;
	Math::Rectangle rCor;
	float cPosY;

	int lev = 1;
	bool flg = false;

	Math::Vector2 nowPos;

	Math::Rectangle rect;



};