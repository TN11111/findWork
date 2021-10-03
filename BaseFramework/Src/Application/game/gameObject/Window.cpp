#include "Window.h"
#include"enemy.h"
#include"../GameNumber.h"

void Window::Init()
{
	m_modelWork.SetModel(GameResourceFactory.GetModelData("Date/Models/Robot/kahun.gltf"));

	SetPos(Math::Vector3(0.0f, 5.0f, 0.0f));
}

void Window::Update()
{

	/*for (enemyNum = 0; enemyNum < level * 15; enemyNum++)
	{
		std::shared_ptr<Enemy> spEnemy = std::make_shared<Enemy>();

		spEnemy->Init();
		spEnemy->StartPos(rand() % 50 - 25, rand() % 30, rand() % 50 - 25);
	}*/

	//ウイルスが移動する
	UpdateMove(MoveSpd);
	UpdateRot();

	MoveSpd += 0.5f;
	if (MoveSpd > 0) { MoveSpd = 0; }

	//ワールド行列の作成
	//移動
	Math::Matrix trans;
	//回転
	Math::Matrix rot;

	trans = Math::Matrix::CreateTranslation(m_worldPos);

	rot = Math::Matrix::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(m_worldRot.y),
		DirectX::XMConvertToRadians(m_worldRot.x),
		DirectX::XMConvertToRadians(m_worldRot.z));

	//合成
	m_mWorld = rot * trans;

	m_bumpSphereInfo.m_radius = 0.5f;
}

void Window::UpdateMove(float move)
{
	if (m_wpTarget.expired()) { return; }

	std::shared_ptr<const GameObject>spTarget = m_wpTarget.lock();

	//ターゲットに向かうベクトル
	Math::Vector3 targetDir = spTarget->GetPos() - m_worldPos;

	float targetDistSpl = targetDir.LengthSquared();

	if (targetDistSpl > m_stopDist * m_stopDist)
	{
		//向いている方向に進む
		Math::Vector3 vMove = m_mWorld.Backward();
		vMove.Normalize();

		vMove *= 0.1;

		m_worldPos += vMove;
	}
}

void Window::UpdateRot()
{
	if (m_wpTarget.expired()) { return; }

	//今向いている方向
	Math::Vector3 nowDir = m_mWorld.Backward();

	//ターゲット（プレイヤー）への方向
	std::shared_ptr<const GameObject> spTarget = m_wpTarget.lock();

	Math::Vector3 targetDir =
		spTarget->GetPos() - m_worldPos;

	//ターゲットに徐々に回転する処理
	nowDir.Normalize();
	targetDir.Normalize();

	float nowAng = atan2(nowDir.x, nowDir.z);
	nowAng = DirectX::XMConvertToDegrees(nowAng);

	float targetAng = atan2(targetDir.x, targetDir.z);
	targetAng = DirectX::XMConvertToDegrees(targetAng);

	float betweenAng = targetAng - nowAng;

	if (betweenAng > 180)
	{
		betweenAng += -360;
	}
	else if (betweenAng < -180)
	{
		betweenAng += 360;
	}

	float rotAng = std::clamp(betweenAng, -2.0f, 2.0f);

	m_worldRot.y += rotAng;
}