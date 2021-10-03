#include"StageMap.h"

StageMap::StageMap()
{

}

StageMap::~StageMap()
{

}

void StageMap::Init()
{
	m_modelWork.SetModel(GameResourceFactory.GetModelData("Date/Models/Room/Room.gltf"));
}

void StageMap::Update()
{
	m_mWorld = m_mWorld.CreateScale(1.0f);
}

void StageMap::DrawEffect()
{
	SHADER->m_effectShader.DrawModel(m_modelWork, m_mWorld);
}

bool StageMap::CheckCollisionBump(const SphereInfo& info, BumpResult& result)
{
	//stageMapのメッシュと当たり判定
	for (UINT i = 0; i < m_modelWork.GetDataNodes().size(); ++i)
	{
		const KdModelData::Node dataNode = m_modelWork.GetDataNodes()[i];
		if (!dataNode.m_spMesh) { continue; }

		const KdModelWork::Node workNode = m_modelWork.GetNodes()[i];

		Math::Vector3 localPushedPos = {};

		if (KdSphereToMesh(info.m_pos, info.m_radius, *(dataNode.m_spMesh.get()), workNode.m_worldTransform * m_mWorld,localPushedPos))
		{
			result.m_isHit = true;

			result.m_pushVec += localPushedPos - info.m_pos;
		}

	}

	return result.m_isHit;
}

void StageMap::Release()
{

}
