#include"gameSystem.h"

#include"../main.h"

#include"gameObject/StageMap.h"
#include"gameObject/player.h"
#include"gameObject/enemy.h"
#include"Camera/FPSCamera.h"
#include"Camera/TPSCamera.h"
#include"gameObject/arrow.h"
#include"gameObject/GameObject.h"
#include"gameObject/Effect2D.h"
#include"Scene/Title.h"
#include"Scene/Result.h"
#include"Scene/Select.h"
#include"gameObject/Time.h"
#include"gameObject/Window.h"

void GameSystem::Init()
{
	srand(timeGetTime());

	level = 1;

	InitTitle();
}

void GameSystem::Update()
{
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		if (MessageBoxA(APP.m_window.GetWndHandle(), "ゲームを終了しますか?", "確認",
			MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES)
		{
			APP.End();
		}
		SetCursorPos(FPSCamera::s_fixMousePos.x, FPSCamera::s_fixMousePos.y);
	}

	if (GetAsyncKeyState(VK_SPACE)){
		if (!button)
		{
			button = true;
			 chenge = true;
		}
	}
	else
	{
		button = false;
	}

	if (m_nowScene == "Title")
	{
		if (chenge)
		{
			RequestChangeScene("Select");
		}
	}

	if (m_nowScene == "Select")
	{
		for (std::shared_ptr<GameObject>& pObject : m_spObject)
		{
			pObject->Update();
		}

		if (GetAsyncKeyState(VK_TAB))
		{
			RequestChangeScene("Title");
		}
	}

	if (m_nowScene == "Game")
	{
		//オブジェクトクラスの更新
		for (std::shared_ptr<GameObject>& pObject : m_spObject)
		{
			pObject->Update();
		}

		//弾を消すための処理
		std::list < std::shared_ptr<GameObject> > ::iterator objItr = m_spObject.begin();
		while (objItr != m_spObject.end())
		{
			//弾のフラグが落ちたら
			if (!(*objItr)->IsAlive())
			{
				objItr->reset();

				//配列を消す
				objItr = m_spObject.erase(objItr);

				continue;
			}
			++objItr;
		}

		if (enemyNum <= 0)
		{
			RequestChangeScene("Result");
		}

		if (GetAsyncKeyState(VK_TAB))
		{
			RequestChangeScene("Title");
		}
	}

	if (m_nowScene == "Result")
	{
		if (chenge)
		{
			RequestChangeScene("Title");
		}
	}

	ChangeScene();
}

void GameSystem::Draw()
{

	//カメラの情報をシェーダーに渡す
	if (m_spCamera)
	{
		m_spCamera->SetToShader();
	}

	//ゲームオブジェクト(不透明物)の描画
	SHADER->m_standardShader.SetToDevice();

	//範囲for ver
	for (std::shared_ptr<GameObject>& pObject : m_spObject)
	{
		pObject->Draw();
	}
	
	//ゲームオブジェクト(透明物)の描画
	SHADER->m_effectShader.SetToDevice();

	D3D.WorkDevContext()->OMSetDepthStencilState(SHADER->m_ds_ZEnable_ZWriteDisable, 0);
	D3D.WorkDevContext()->RSSetState(SHADER->m_rs_CullNone);

	//SHADER->m_effectShader.DrawModel(m_sky, m_skyMat);  //空の描画

	for (std::shared_ptr<GameObject>& pObject : m_spObject)
	{
		pObject->DrawEffect();
	}

	D3D.WorkDevContext()->OMSetDepthStencilState(SHADER->m_ds_ZEnable_ZWriteEnable, 0);
	D3D.WorkDevContext()->RSSetState(SHADER->m_rs_CullBack);

	//2Dテクスチャ描画
	SHADER->m_spriteShader.Begin();

	SHADER->m_spriteShader.SetMatrix(Math::Matrix::Identity);

	for (std::shared_ptr<GameObject>& pObject : m_spObject)
	{
		pObject->Draw2();
	}

	SHADER->m_spriteShader.End();

}

void GameSystem::RequestChangeScene(const std::string& name)
{
	m_isRepuestChangeScene = true;
	m_nextSceneName = name;
	chenge = false;
}

const std::shared_ptr<KdCamera> GameSystem::GetCamera() const
{
	return m_spCamera;
}

void GameSystem::Release()
{
	m_spObject.clear();

	m_spCamera = nullptr;
}

void GameSystem::ChangeScene()
{
	if (!m_isRepuestChangeScene) { return; }

	if (m_nextSceneName == "Title")
	{
		InitTitle();
	}
	else if (m_nextSceneName == "Select")
	{
		InitSelect();
	}
	else if (m_nextSceneName == "Game")
	{
		InitGame();
	}
	else if (m_nextSceneName == "Result")
	{
		InitResult();
	}

	m_isRepuestChangeScene = false;
}

void GameSystem::InitTitle()
{
	Release();

	//空を拡大させる
	m_skyMat = m_skyMat.CreateScale(1.0f);//空の拡縮の設定

	std::shared_ptr<Title> spTitle = std::make_shared<Title>();
	spTitle->Init();
	AddObject(spTitle);

	//プレイヤーオブジェクトのインスタンス
	if (!m_spCamera)
	{
		Math::Matrix trans = Math::Matrix::CreateTranslation(0,10.f,0);
		
		m_spCamera = std::make_shared<TPSCamera>();
		SetCamera(m_spCamera);

		m_spCamera->SetProjectionMatrix(60.0f);

		m_spCamera->SetCameraMatrix(trans);
	}

	m_nowScene = "Title";

}

void GameSystem::InitSelect()
{
	Release();

	//空を拡大させる
	m_skyMat = m_skyMat.CreateScale(1.0f);//空の拡縮の設定

	std::shared_ptr<Select> spSelect = std::make_shared<Select>();
	spSelect->Init();
	AddObject(spSelect);

	//プレイヤーオブジェクトのインスタンス
	if (!m_spCamera)
	{
		Math::Matrix trans = Math::Matrix::CreateTranslation(0, 10.f, 0);

		m_spCamera = std::make_shared<TPSCamera>();
		SetCamera(m_spCamera);

		m_spCamera->SetProjectionMatrix(60.0f);

		m_spCamera->SetCameraMatrix(trans);
	}

	m_nowScene = "Select";
}

void GameSystem::InitGame()
{
	Release();

	//カメラの移動
	DirectX::SimpleMath::Matrix cPos;
	cPos = cPos.CreateTranslation({ 0.0f,1.0f,0.0f });

	DirectX::SimpleMath::Matrix cRot;
	cRot = cRot.CreateRotationX(DirectX::XMConvertToRadians(0.0f));

	cPos = cRot*cPos;

	std::shared_ptr<StageMap> spStage = std::make_shared<StageMap>();
	spStage->Init();
	AddObject(spStage);

	//プレイヤーオブジェクトのインスタンス化
	std::shared_ptr<player> spPlayer = std::make_shared<player>();
	spPlayer->Init();
	spPlayer->SetBel(m_setBil);
	AddObject(spPlayer);
	
	for (enemyNum = 0; enemyNum < level * 15; enemyNum++)
	{
		std::shared_ptr<Enemy> spEnemy = std::make_shared<Enemy>();


		spEnemy->Init();
		spEnemy->StartPos(rand() % 50 - 25, rand() % 30, rand() % 50 - 25);

		AddObject(spEnemy);
	}

	std::shared_ptr<Effect2D> spEffect = std::make_shared<Effect2D>();
	spEffect->Init();
	spEffect->SetAnimation(5, 5);
	AddObject(spEffect);

	std::shared_ptr<Window> spWindow = std::make_shared<Window>();
	spWindow->Init();
	spWindow->SetTarget(spPlayer);
	AddObject(spWindow);

	std::shared_ptr<Time> spTime = std::make_shared<Time>();
	spTime->Init();
	AddObject(spTime);

	m_nowScene = "Game";
}

void GameSystem::InitResult()
{
	Release();

	std::shared_ptr<Result> spResult = std::make_shared<Result>();
	spResult->Init();
	AddObject(spResult);

	if (!m_spCamera)
	{
		Math::Matrix trans = Math::Matrix::CreateTranslation(0, 10.f, 0);

		m_spCamera = std::make_shared<TPSCamera>();
		SetCamera(m_spCamera);

		m_spCamera->SetProjectionMatrix(60.0f);

		m_spCamera->SetCameraMatrix(trans);
	}
	m_nowScene = "Result";
}
