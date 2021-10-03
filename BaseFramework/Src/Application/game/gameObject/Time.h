#pragma once
#include"GameObject.h"

class Time : public GameObject
{
public:
	Time() {}
	~Time() {}

	void Init()override;
	void Update() override;
	void Draw() {};
	void Draw2() override;

	Math::Rectangle UpdateRect(int sec) { return rect = { (33 * sec), 64, 32, 64 }; }

	void Reset();

private:
	void Release();

	std::shared_ptr<KdTexture> m_FTexture;
	std::shared_ptr<KdTexture> m_STexture;
	std::shared_ptr<KdTexture> m_TTexture;

	Math::Rectangle rect;

	int width = 32;

	int timer;
	int cnt;

	int firstSec;
	int secondSec;
	int thirdSec;

};