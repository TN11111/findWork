#pragma once
#include"GameObject.h"

class arrow : public GameObject
{
public:
	arrow() {}
	~arrow() {}

	void Init() override;
	void Update() override;

	void DrawEffect() override;

	void SetWorldMatrix(const Math::Matrix& world) { m_mWorld = world; }

	void SetTarget(std::shared_ptr<GameObject> spTarget) 
	{m_wpTarget = spTarget; }   // shader -> weakは代入可能

	void UpdateCollsion();

private:

	void Release();

	void UpdateMave();

	void UpdateRot();
	void RotByGuide();
	
	//weak_ptr（弱参照）:メモリの解放に関与しないポインター
	std::weak_ptr<const GameObject> m_wpTarget;

	int m_lifeSpan = 0;

	bool m_isStop = false;

	bool m_isHit = false;

	Math::Vector3 m_prevPos = {};

	KdTrailPolygon m_trail;
};