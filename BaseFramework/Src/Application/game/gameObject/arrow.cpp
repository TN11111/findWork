#include "arrow.h"
#include"Effect2D.h"

void arrow::Init()
{
	m_modelWork.SetModel(GameResourceFactory.GetModelData("Date/Models/Arrow/bullet.gltf"));

	m_mWorld = Math::Matrix::CreateTranslation({ 0.0f,3.0f,-5.0f });

	m_lifeSpan = 300;
	
	m_bumpSphereInfo.m_radius = 0.5f;

	m_trail.SetTexture(GameResourceFactory.GetTexture("Date/Textures/Trail.png"));
	m_trail.SetPattern(KdTrailPolygon::Trail_Pattern::eBillboard);
	m_trail.SetWidth(0.3f);
}

void arrow::Update()
{
	if (--m_lifeSpan <= 0)
	{
		m_isAlive = false;
	}
	if (m_isStop) { return; }

	if (m_trail.GetNumPoints() > 30)
	{
		m_trail.DelPoint_Back();
	}

	m_prevPos = m_mWorld.Translation();

	UpdateRot();

	//向いている方向に進む
	UpdateMave();

	UpdateCollsion();

	m_trail.AddPoint(m_mWorld);
}

void arrow::DrawEffect()
{
	SHADER->m_effectShader.DrawTrailPolygon(m_trail);
}

void arrow::UpdateCollsion()
{
	const std::list<std::shared_ptr<GameObject>>& objects
		= GameSystem::GetInstance().GetObjects();

	for (const std::shared_ptr<GameObject>& spObject : objects)
	{
		if (spObject->GetClassID() != GameObject::eEnemy) { continue; }

		Math::Vector3 rayPos = m_prevPos;
		Math::Vector3 rayDir = GetPos() - m_prevPos;
		float length = rayDir.Length();

		SphereInfo sphereInfo(rayPos, 1.0f);
		BumpResult result;

		if (spObject->CheckCollisionBump(sphereInfo,result))
		{
			m_isAlive = false;

			spObject->Destroy();
			GameSystem::GetInstance().enemyHit();

			m_mWorld *= Math::Matrix::CreateTranslation(result.m_pushVec);

			std::shared_ptr<Effect2D> spEffect = std::make_shared<Effect2D>();

			spEffect->SetTexture("Date/Textures/Explosion.png");
			spEffect->ChangeTexture(3.0f,3.0f);

			spEffect->SetAnimation(5, 5);

			spEffect->SetPos(GetPos());

			GameInstance.AddObject(spEffect);
		}
	}
}

void arrow::Release()
{

}

void arrow::UpdateMave()
{
	Math::Vector3 vMove = m_mWorld.Backward();

	vMove.Normalize();

	vMove *= 1.f;

	Math::Matrix trans;
	Math::Matrix rot;

	trans = Math::Matrix::CreateTranslation(vMove);

	m_mWorld *= trans;
}

void arrow::UpdateRot()
{
	RotByGuide();
}

void arrow::RotByGuide()
{
	if (!m_isHit) { return; }

	//weak_ptr　の先が無効かどうか
	if (m_wpTarget.expired()) { return; }

	//weakの先を一時的に解放されなくする
	std::shared_ptr spTarget = m_wpTarget.lock();

	//自身の向いている方向
	Math::Vector3 nowDir = m_mWorld.Backward();

	Math::Vector3 targetDir = spTarget->GetPos() - m_mWorld.Translation();

	nowDir.Normalize();
	targetDir.Normalize();

	//自分の前方とターゲットへ向かう内積
	float dot = nowDir.Dot(targetDir);
	dot = std::clamp(dot, -1.0f, 1.0f);

	//２つベクトル内積値をacos（逆余弦）すると２辺間の角度が求まる
	float betweenRad = acos(dot);

	float rotMax = DirectX::XMConvertToRadians(3.0f);

	float rotRad = std::clamp(betweenRad, -rotMax, rotMax);

	//この軸を中心の回転する角度を求める
	Math::Vector3 rotAxis;

	//外積
	nowDir.Cross(targetDir, rotAxis);

	//完全に一致していたら回転しない
	if (!rotAxis.LengthSquared()) { return; }

	Math::Matrix rot;

	rot = Math::Matrix::CreateFromAxisAngle(rotAxis, rotRad);

	//移動行列が邪魔のためリセット
	Math::Vector3 pos = m_mWorld.Translation();
	m_mWorld.Translation({ 0.0f,0.0f,0.0f });

	m_mWorld *= rot;
	m_mWorld.Translation(pos);
}
