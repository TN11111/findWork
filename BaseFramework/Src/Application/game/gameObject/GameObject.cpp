#include"GameObject.h"


void GameObject::Draw()
{
	SHADER->m_standardShader.DrawModel(m_modelWork, m_mWorld);
}

void GameObject::Draw2()
{
}

bool GameObject::CheckCollisionBump(const SphereInfo& info, BumpResult& result)
    {

	Math::Vector3 selfPos = GetPos() + m_bumpSphereInfo.m_pos;

	//自分と相手の座標
	Math::Vector3  betweenVec = info.m_pos - m_mWorld.Translation();

	//2キャラの間の距離
	float distanceSqr = betweenVec.LengthSquared();

	float hitRadius = m_bumpSphereInfo.m_radius + info.m_radius;

	result.m_isHit = (distanceSqr <= (hitRadius * hitRadius));

	if (result.m_isHit)
	{
		result.m_pushVec = betweenVec;
		result.m_pushVec.Normalize();

		float distance = std::sqrtf(distanceSqr);
		result.m_pushVec *= hitRadius - distance;
	}

	return result.m_isHit;
}

bool GameObject::CheckCollisionBump(const RayInfo& info, BumpResult& result)
{
	float mindist = FLT_MAX;

	KdRayResult rayResult;

	for (UINT i = 0; i < m_modelWork.GetDataNodes().size(); ++i)
	{
		const KdModelData::Node& dataNode = m_modelWork.GetDataNodes()[i];

		if (!dataNode.m_spMesh) { return result.m_isHit; }

		const KdModelWork::Node& workNode = m_modelWork.GetNodes()[i];

		KdRayToMesh(info.m_pos, info.m_dir, info.m_radius, *(dataNode.m_spMesh.get()), workNode.m_worldTransform * m_mWorld, &rayResult);

		if (rayResult.m_hit&&rayResult.m_distance < mindist)
		{
			result.m_isHit = rayResult.m_hit;
			result.m_pushVec = info.m_dir * (rayResult.m_distance - info.m_radius);

			mindist = rayResult.m_distance;
		}
	}
		return result.m_isHit;
}

bool GameObject::CheakTexture(const std::shared_ptr<KdTexture> Tex,RayInfo& info, BumpResult& result)
{
	float mindist = FLT_MAX;

	KdRayResult rayResult;

	POINT mousePos;
	GetCursorPos(&mousePos);

	Math::Viewport vp;
	D3D.GetViewport(vp);

	Math::Vector2 nowPos(mousePos.x - (vp.width * 0.5f), (mousePos.y - (vp.height * 0.5f)));

	Math::Vector3 cameraPos = GameInstance.GetCamera()->GetCameraMatrix().Translation();

	Math::Vector3 localNearPos;
	GameInstance.GetCamera()->ConvertScreenToWorld(nowPos, localNearPos);

	RayInfo rayInfo(cameraPos, localNearPos - cameraPos, 1000);

	if (rayResult.m_hit && rayResult.m_distance < mindist)
	{
		result.m_isHit = rayResult.m_hit;
		result.m_pushVec = info.m_dir * (rayResult.m_distance - info.m_radius);

		mindist = rayResult.m_distance;
	}
	return result.m_isHit;

	return false;
}
