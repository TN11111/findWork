#include "enemy.h"

#include"../gameSystem.h"

void Enemy::Init()
{
	m_modelWork.SetModel(GameResourceFactory.GetModelData("Date/Models/Robot/uvirus.gltf"));
}

void Enemy::Update()
{
	//ウイルスが移動する
	UpdateMove(MoveSpd);

	MoveSpd += 0.01f;
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

void Enemy::UpdateMove(float move)
{
	//向いている方向に進む
	Math::Vector3 vMove = m_mWorld.Backward();
	vMove.Normalize();

	vMove *= move;

	m_worldPos += vMove;
}

void Enemy::UpdateRot()
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

void Enemy::Release()
{
	m_wpTarget.reset();
}
