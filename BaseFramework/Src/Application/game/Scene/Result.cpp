#include "Result.h"

void Result::Init()
{
	m_Texture = GameResourceFactory.GetTexture("Date/Textures/Result.png");
	m_modelWork.SetModel(GameResourceFactory.GetModelData("Date/Models/Room/Room.gltf"));
}

void Result::Update()
{
}

void Result::DrawEffect()
{
	SHADER->m_effectShader.DrawModel(m_modelWork, m_mWorld);
}

void Result::Draw2()
{
	SHADER->m_spriteShader.DrawTex(m_Texture.get(), 0, 0);
}

void Result::Release()
{
}
