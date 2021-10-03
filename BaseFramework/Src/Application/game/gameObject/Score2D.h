#pragma once
#include"GameObject.h"

class Score : public GameObject
{
public:
	Score() {}
	~Score() {}

	void Init() override;
	void Update() override;
	void Draw() override;
	void Draw2() override;
	void DrawEffect() override;

private:
	void Relese();

	std::shared_ptr<KdTexture> m_Texture;

};