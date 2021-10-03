#include "Select.h"

void Select::Init()
{
	select = menu;

	Pos = { 0,150 };

	m_TNumber = GameResourceFactory.GetTexture("Date/Textures/number/num.png");
	m_LTexture = GameResourceFactory.GetTexture("Date/Textures/LEVEL.png");

	m_TReady = GameResourceFactory.GetTexture("Date/Textures/Ready.png");
	rReady = {0,256,512,256};

	m_TBel = GameResourceFactory.GetTexture("Date/Textures/装備.png");
	rBel = {0,256,512,256};

	m_modelWork.SetModel(GameResourceFactory.GetModelData("Date/Models/Room/Room.gltf"));
}

void Select::Update()
{
	switch (select)
	{
	case menu:


		
		break;

	case level:
		LevelSelect();
		break;

	case belonging:

		break;

	case equipment:

		break;

	case upgrade:

		break;

	default:
		break;
	}
	

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (!MouseToTexture(m_TNumber, Pos, nowPos))
		{
			GameInstance.RequestChangeScene("Game");
		}
	}
}

void Select::Draw2()
{
	Math::Rectangle Rect = { 0,128,512,128 };
	switch (menu)
	{
	case menu:

		SHADER->m_spriteShader.DrawTex(m_TReady.get(), -400, -100, 256, 128, &rReady);

		SHADER->m_spriteShader.DrawTex(m_TBel.get(), -400, -250, 256, 128, &rBel);
		break;
	case level:
		UpdateRect(lev);
		SHADER->m_spriteShader.DrawTex(m_TNumber.get(), (int)Pos.x, (int)Pos.y, 64, 128, &rect);

		
		SHADER->m_spriteShader.DrawTex(m_LTexture.get(), 0, 250, 512, 128, &Rect);
		break;

	case belonging:
		break;

	case equipment:
		break;

	case upgrade:
		break;

	default:
		break;
	}

}

void Select::DrawEffect()
{
	SHADER->m_effectShader.DrawModel(m_modelWork, m_mWorld);
}

void Select::MouseMove()
{
	POINT mousePos;
	GetCursorPos(&mousePos);

	POINT mouseMove;
	mouseMove.x = mousePos.x;
	mouseMove.y = mousePos.y;

	nowPos = { (float)mouseMove.x ,(float)mouseMove.y };
}

bool Select::MouseToTexture(std::shared_ptr<KdTexture> Tex,Math::Vector2 Pos, Math::Vector2 Mouse)
{
	float posY = Mouse.y - Pos.y;
	float posX = Mouse.x - Pos.x;

	float H = (float)Tex.get()->GetHeight();
	float W = (float)Tex.get()->GetWidth();


	if (posX <= W || posY <= H || posX >= -W || posY >= -H)
	{
		return true;
	}

	return false;
}

void Select::LevelSelect()
{
	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (!flg)
		{
			lev++;
			GameSystem::GetInstance().LevelSet(lev);
		}
		flg = true;
	}
	else if (GetAsyncKeyState(VK_LEFT))
	{
		if (!flg)
		{
			lev--;
			GameSystem::GetInstance().LevelSet(lev);
		}
		flg = true;
	}
	else
	{
		flg = false;
	}
}

void Select::Release()
{
}
