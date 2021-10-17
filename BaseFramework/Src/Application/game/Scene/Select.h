#pragma once
#include"../gameObject/GameObject.h"

class player;

enum Menu //メニュー
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

	bool MouseToTexture(std::shared_ptr<KdTexture> Tex, Math::Vector2 Pos,Math::Vector3 Mouse);

	void click( bool flg) 
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			if (!flg) { flg = true; }
		}
		else
		{
			flg = false;
		}
	}

	void LevelSelect();
	void UpdateMenu();
	void UpdateBel();
	void Upgrade();

private:
	Menu select; //メニューの切り替え
	Menu cursor; //

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

	std::shared_ptr<KdTexture> m_TFrame;
	Math::Rectangle rFrame;

	std::shared_ptr<KdTexture> m_TChange;
	Math::Rectangle rChange;

	std::shared_ptr<KdTexture> m_TUpgrade;
	Math::Rectangle rUpgrade;

	std::shared_ptr<KdTexture> m_THom;
	Math::Rectangle rHom;

	std::string txt = "";

	int lev = 1;
	bool menuChange = false;

	bool changeLevel = false;

	Math::Vector2 nowPos;

	Math::Vector3 localNearPos;

	Math::Rectangle rect;



};