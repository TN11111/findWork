#include"player.h"

#include"../gameSystem.h"

#include"../Camera/FPSCamera.h"
#include"../Camera/TPSCamera.h"
#include"arrow.h"

player::player()
{
}

player::~player()
{
	Release();
}

void player::Init()
{
	m_modelWork.SetModel(GameResourceFactory.GetModelData("Date/Models/Robot/-Ion.gltf"));

	m_spCamera = std::make_shared<TPSCamera>();

	//GameSystemにもカメラをシェアさせる
	GameSystem::GetInstance().SetCamera(m_spCamera);

	m_spCamera->Init();
	m_spCamera->SetClumpAngleX(-75.0f, 90.0f);
	m_spCamera->SetProjectionMatrix(60.0f);

	m_spCamera->SetLocalPos(Math::Vector3(0.0f, 1.0f, -3.0f));

	m_spCamera->SetLocalGazePosition(Math::Vector3(0.0f, 0.0f, 0.0f));

	m_bumpSphereInfo.m_radius = 0.5f;
	m_bumpSphereInfo.m_pos.y = 0.55f;
}

void player::Update()
{
	//垂直方向の移動量の追加
	m_prevPos = GetPos();

	Math::Vector3 vMove;

	UpdateMove(vMove);
	UpdateRot(vMove);

	UpdateCollsion();
	
	UpdateWorldMatrix();
	
	ShotArrow();

	if (m_spCamera)
	{
		m_spCamera->Update();

		Math::Matrix trans = Math::Matrix::CreateTranslation(m_worldPos);

		m_spCamera->SetCameraMatrix(trans);
	}

}

void player::Release()
{
	//KdSafeDelete(m_spCamera);

	m_spCamera.reset();
}

void player::UpdateMove(Math::Vector3& dstMove)
{
	float moveSpd = 0.8f;

	//Ｗキーで前進、Ｓキーで後退

	DirectX::SimpleMath::Vector3 moveVec;
	if (GetAsyncKeyState('W')) { moveVec.z += 1.0f; }
	if (GetAsyncKeyState('S')) { moveVec.z -= 1.0f; }
	if (GetAsyncKeyState('A')) { moveVec.x -= 1.0f; }
	if (GetAsyncKeyState('D')) { moveVec.x += 1.0f; }
	if (GetAsyncKeyState(VK_SHIFT)) { moveVec.y -= 1.0f; }
	if (GetAsyncKeyState(VK_SPACE)) { moveVec.y += 1.0f; }

	//正規化 : 長さを１にする
	moveVec.Normalize();

	moveVec *= moveSpd;

	//! カメラの回転を加味する
	//行列を使ってベクトルを変換する
	if (m_spCamera)
	{
		moveVec = moveVec.TransformNormal(moveVec, m_spCamera->GetRotMatrix());
	}

	m_worldPos += moveVec;

	dstMove = moveVec;
}

void player::UpdateRot(const Math::Vector3& srcMove)
{
	//if (srcMove.LengthSquared() == 0) { return; }

	POINT nowPos;
	GetCursorPos(&nowPos);

	//今向いている方向
	Math::Vector3 nowDir = m_mWorld.Backward();

	m_worldRot.x += nowPos.x;
	m_worldRot.y += nowPos.y;

	m_worldRot = m_spCamera->GetDegAngle();
}

void player::UpdateCollsion()
{

	for (const std::shared_ptr<GameObject>& spObject : GameSystem::GetInstance().GetObjects())
	{
		if (spObject->GetClassID() != GameObject::eEnemy &&
			spObject->GetClassID() != GameObject::eStage) { continue; }

		BumpResult bumpResult;

		SphereInfo sphereInfo(GetPos() + m_bumpSphereInfo.m_pos, m_bumpSphereInfo.m_radius);

		bool result = spObject->CheckCollisionBump(sphereInfo, bumpResult);
		if (result)
		{
			m_worldPos += bumpResult.m_pushVec;
		}
	}

	for (const std::shared_ptr<GameObject>& spObject : GameSystem::GetInstance().GetObjects())
	{
		if (spObject->GetClassID() != GameObject::eStage) { continue; }

		Math::Vector3 rayPos = m_prevPos;
		rayPos.y += 1.0f;

		RayInfo rayInfo(rayPos, Math::Vector3(1.0f, -2.0f, 1.0f), m_verticalMovement + 1.0f);

		BumpResult bumpResult;

		spObject->CheckCollisionBump(rayInfo, bumpResult);

		if (bumpResult.m_isHit)
		{
			m_worldPos += bumpResult.m_pushVec;
			m_verticalMovement= 0.0f;
			m_jumpFlg = false;
		}
		
	}
}

void player::UpdateWorldMatrix()
{
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

	m_mWorld = rot * trans;
}

void player::ShotArrow()
{
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (m_canShot)
		{
			//弾オブジェクトを生成、何発でも出せるように
			std::shared_ptr<arrow> pArrow = std::make_shared<arrow>();

			pArrow->Init();
			
			//エネミークラスを判別
			const std::list<std::shared_ptr<GameObject>>& objects
				= GameSystem::GetInstance().GetObjects();
			for (const std::shared_ptr<GameObject>& spObject : objects)
			{
				if (spObject->GetClassID() != GameObject::eEnemy) { continue; }

				if (m_nowBil == "homing")
				{
					pArrow->SetTarget(spObject);
					break;
				}
				else
				{
					pArrow->SetTarget(nullptr);
					break;
				}
			}

			////モデルからノードを探す
			//const KdModelWork::Node* pNode = m_modelWork.FindNode("Arm");

			////探したノードがあればその場所から発射する
			//if (pNode)
			//{
			//	pArrow->SetWorldMatrix(m_mWorld * pNode->m_worldTransform);
			//}
			pArrow->SetWorldMatrix(m_mWorld);

			//作成した弾を登録する
			GameSystem::GetInstance().AddObject(pArrow);

			m_canShot = false;
		}

	}
	else
	{
		m_canShot = true;
	}
}
