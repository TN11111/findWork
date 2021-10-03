#pragma once
#include"../gameObject/GameObject.h"

class Title : public GameObject
{
public:
	Title() {}
	~Title() { Release(); }

	void Init() override;
	void Update() override;
	void Draw() override {}
	void DrawEffect() override;
	void Draw2() override;

	void SetTexture(const std::string& string) { m_poly.SetTexture(GameResourceFactory.GetTexture(string)); }

private:
	void Release();

	KdSquarePolygon m_poly;
	std::shared_ptr<KdTexture> m_Texture;

};