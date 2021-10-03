#include"Title.h"

void Title::Init()
{
	m_Texture = GameResourceFactory.GetTexture("Date/Textures/Title.png");
	m_modelWork.SetModel(GameResourceFactory.GetModelData("Date/Models/Room/Room.gltf"));
}
void Title::Update()
{

}

void Title::DrawEffect()
{
	SHADER->m_effectShader.DrawModel(m_modelWork, m_mWorld);
}

void Title::Draw2()
{
	SHADER->m_spriteShader.DrawTex(m_Texture.get(), 0, 0);
}
void Title::Release()
{

}