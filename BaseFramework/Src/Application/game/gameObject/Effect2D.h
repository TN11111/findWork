#pragma once

#include"GameObject.h"

class Effect2D : public GameObject
{
public:
	Effect2D() {}
	~Effect2D() { Release(); }

	void Init() override;
	void Update() override;
	void Draw() override;
	void DrawEffect() override;
	void Draw2() override;

	void SetTexture(const std::string& string) {m_poly.SetTexture(GameResourceFactory.GetTexture(string));}

	void ChangeTexture(float angleZ = 0.0f, float x = 1.0f, float y = 1.0f, Math::Vector4 color = kWhiteColor) 
	{
		m_angleZ = angleZ;
		m_poly.Init(x, y, color); 
	}

	void SetAnimation(int splitX, int splitY, float speed = 1.0f,bool loop = false);

private:
	void Release();

	KdSquarePolygon m_poly;
	std::shared_ptr<KdTexture> m_spTexture;

	float m_animSpd = 0.0f;
	bool m_loopFlg = false;

	int m_lifeSpan = -1;

	float m_angleZ = 0.0f;
};