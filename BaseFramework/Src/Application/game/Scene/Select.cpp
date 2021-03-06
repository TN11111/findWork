#include "Select.h"

#include"../gameObject/player.h"

void Select::Init()
{
	select = menu;
	cursor = ready;

	Pos = { 0,150 };

	m_TNumber = GameResourceFactory.GetTexture("Date/Textures/number/num.png");
	m_LTexture = GameResourceFactory.GetTexture("Date/Textures/text/LEVEL.png");

	m_TReady = GameResourceFactory.GetTexture("Date/Textures/select/Ready.png");
	rReady = {0,256,512,256};

	m_TBel = GameResourceFactory.GetTexture("Date/Textures/select/belonging.png");
	rBel = {0,256,512,256};

	m_TCor = GameResourceFactory.GetTexture("Date/Textures/select/cursor.png");
	rCor = { 0,64,64,64 };
	cPosY = -100;

	m_TFrame = GameResourceFactory.GetTexture("Date/Textures/select/upgradeFrame.png");
	rFrame = { 0,720,447,720 };

	m_THom = GameResourceFactory.GetTexture("Date/Textures/text/homing.png");
	rHom = { 0,112,447,112 };

	m_TChange = GameResourceFactory.GetTexture("Date/Textures/select/change.png");

	m_TUpgrade = GameResourceFactory.GetTexture("Date/Textures/select/upgrade.png");

	m_modelWork.SetModel(GameResourceFactory.GetModelData("Date/Models/Room/Room.gltf"));
}

void Select::Update()
{
	MouseMove();

	switch (select)
	{
	case menu:
		UpdateMenu();
		break;

	case ready:
		LevelSelect();
		break;

	case belonging:
		UpdateBel();
		break;

	case equipment:

		break;

	case upgrade:
		Upgrade();
		break;

	default:
		break;
	}
}

void Select::Draw2()
{
	Math::Rectangle Rect = { 0,128,512,128 };
	switch (select)
	{
	case menu:
		SHADER->m_spriteShader.DrawTex(m_TCor.get(), -600, cPosY, 64, 64, &rCor);

		SHADER->m_spriteShader.DrawTex(m_TReady.get(), -400, -100, 256, 128, &rReady);

		SHADER->m_spriteShader.DrawTex(m_TBel.get(), -400, -250, 256, 128, &rBel);
		break;

	case ready:
		UpdateRect(lev);
		SHADER->m_spriteShader.DrawTex(m_TNumber.get(), (int)Pos.x, (int)Pos.y, 64, 128, &rect);
		
		SHADER->m_spriteShader.DrawTex(m_LTexture.get(), 0, 250, 512, 128, &Rect);
		break;

	case belonging:
		SHADER->m_spriteShader.DrawTex(m_TCor.get(), -600, cPosY, 64, 64, &rCor);

		SHADER->m_spriteShader.DrawTex(m_TChange.get(), -400, -100, 256, 128, &rReady);

		SHADER->m_spriteShader.DrawTex(m_TUpgrade.get(), -400, -250, 256, 128, &rBel);

		SHADER->m_spriteShader.DrawTex(m_TFrame.get(), 300, 0, 447, 720, &rFrame);
		break;

	case equipment:
		break;

	case upgrade:
		SHADER->m_spriteShader.DrawTex(m_TFrame.get(), 300, 0, 447, 720, &rFrame);

		if (txt != "homing")
		{
			SHADER->m_spriteShader.DrawTex(m_THom.get(), 400, 250, 447, 112, &rHom);
		}
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

	Math::Viewport vp;
	D3D.GetViewport(vp);

	Math::Vector2 nowPos(mousePos.x - (vp.width * 0.5f), (mousePos.y - (vp.height * 0.5f)));

	Math::Vector3 cameraPos = GameInstance.GetCamera()->GetCameraMatrix().Translation();

	GameInstance.GetCamera()->ConvertScreenToWorld(nowPos, localNearPos);


}

bool Select::MouseToTexture(std::shared_ptr<KdTexture> Tex,Math::Vector2 Pos, Math::Vector3 Mouse)
{
	Math::Vector3 texPos;
	GameInstance.GetCamera()->ConvertScreenToWorld(Pos, texPos);

	float posY = -Mouse.y - (texPos.y -120);
	float posX = Mouse.x - texPos.x;

	float H = (float)Tex.get()->GetHeight()/1.3;
	float W = (float)Tex.get()->GetWidth()/1.3;


	if (posY <= H && posY >= -H && posX >= -W && posX <= W )
	{
		return true;
	}

	return false;
}

void Select::LevelSelect()
{

	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (changeLevel)
		{
			lev++;
			GameSystem::GetInstance().LevelSet(lev);	
		}
		changeLevel = false;
	}
	else if (GetAsyncKeyState(VK_LEFT))
	{
		if (changeLevel)
		{
			lev--;
			GameSystem::GetInstance().LevelSet(lev);	
		}
		changeLevel = false;
	}
	else { changeLevel = true; }


	if (menuChange) 
	{
		GameInstance.RequestChangeScene("Game"); 

		menuChange = false;
	}

	if (GetAsyncKeyState(VK_RBUTTON))
	{
		if (menuChange)
		{
			select = menu;
		}
	}

}

void Select::UpdateMenu()
{
	bool menu = false;

	click(menu);

	switch (cursor)
	{
	case ready:
		cPosY = -100;
			
		if (MouseToTexture(m_TBel, Math::Vector2{ -400,-250 }, localNearPos))
		{
			cursor = belonging;
		}

		if (MouseToTexture(m_TReady, Math::Vector2{ -400,-100 }, localNearPos))
		{
			if (menu)
			{
				select = ready;	
			}
		}

		break;

	case belonging:
		cPosY = -250;

		if (MouseToTexture(m_TReady, Math::Vector2{ -400,-100 }, localNearPos))
		{
			cursor = ready;
		}

		if (MouseToTexture(m_TBel, Math::Vector2{ -400,-250 }, localNearPos))
		{
			if (menu)
			{
				select = belonging;
			}
		}
		break;
	default:
		break;
	}
}

void Select::UpdateBel()
{
	bool bel;
	click(bel);

	switch (cursor)
	{
	case belonging:
		cPosY = -100;

		if (MouseToTexture(m_TUpgrade, Math::Vector2{ -400,-250 }, localNearPos))
		{
			cursor = upgrade;
		}

		if (MouseToTexture(m_TChange, Math::Vector2{ -400,-100 }, localNearPos))
		{
			if (bel)
			{
				select = menu;
			}
		}
		if (GetAsyncKeyState(VK_RBUTTON))
		{
			if (bel)
			{
				select = menu;
			}
		}
		
		break;

	case upgrade:
		cPosY = -250;
		if (GetAsyncKeyState(VK_RBUTTON))
		{
			if (bel)
			{
				select = menu;
			}
		}

		if (MouseToTexture(m_TChange, Math::Vector2{ -400,-100 }, localNearPos))
		{
			cursor = belonging;
		}

		if (MouseToTexture(m_TUpgrade, Math::Vector2{ -400,-250 }, localNearPos))
		{
			if (bel)
			{
				select = upgrade;
			}
		}
		
		break;
	default:
		break;
	}
}

void Select::Upgrade()
{
	bool grade = false;
	click(grade);

	if (GetAsyncKeyState(VK_RBUTTON))
	{
		if (grade)
		{
			cursor = ready;
			select = menu;
		}
	}
	else { menuChange = true; }

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (MouseToTexture(m_THom, Math::Vector2{ 400,250 }, localNearPos))
		{
			GameInstance.GetInstance().SetBuild("homing");
			txt = "homing";
		}
	}

	
}

void Select::Release()
{
}
