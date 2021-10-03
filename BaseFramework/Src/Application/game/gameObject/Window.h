#pragma once
#include"GameObject.h"

class Window : public GameObject
{
public:
	Window() {}
	~Window() {}

	void Init()override;
	void Update()override;

	void SetTarget(std::shared_ptr<const GameObject> pTarget)
	{
		m_wpTarget = pTarget;
	}

	void SetModel(std::string name) { m_modelWork.SetModel(GameResourceFactory.GetModelData(name)); }

private:
	void Release() {}
	void UpdateMove(float move);
	void UpdateRot();

	//キャラの移動と回転を個別に変数にする
	Math::Vector3 m_worldPos;
	Math::Vector3 m_worldRot;

	std::weak_ptr<const GameObject> m_wpTarget;

	int enemyNum;

	int level = 1;

	float MoveSpd = -0.7f;

	float m_stopDist = 1.0f;

};