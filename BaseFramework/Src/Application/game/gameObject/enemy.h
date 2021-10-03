#pragma once
#include"GameObject.h"


class Enemy : public GameObject
{
public:
	Enemy() {}
	~Enemy() {}

	void Init() override;
	void Update() override;

	void SetTarget(std::shared_ptr<const GameObject> pTarget) 
	{	m_wpTarget = pTarget;}

	void SetModel(std::string name) { m_modelWork.SetModel(GameResourceFactory.GetModelData(name)); }

	const Math::Vector3 GetPos() const override { return m_worldPos; }

	void StartPos(int posx, int posy, int posz) { m_worldPos.x = (float)posx; m_worldPos.y = (float)posy; m_worldPos.z = (float)posz; }

	//クラスＩDを返す
	const GameObject::ClassID GetClassID() const override
	{
		return GameObject::eEnemy;
	}

private:

	void UpdateMove(float move);
	void UpdateRot();

	void Release();

	//キャラの移動と回転を個別に変数にする
	Math::Vector3 m_worldPos;
	Math::Vector3 m_worldRot;

	std::weak_ptr<const GameObject> m_wpTarget;

	float m_stopDist = 5.0f;

	float MoveSpd = -0.7f;
};


