#pragma once

#include"GameObject.h"

class FPSCamera;
class TPSCamera;

class player :public GameObject
{
public:
	player();
	~player();

	void Init() override;
	void Update() override;

	const std::shared_ptr<TPSCamera> GetCamera() const { return m_spCamera; }
	std::shared_ptr<TPSCamera> WorkCamera() { return m_spCamera; }
	
	const Math::Vector3 GetPos() const override { return m_worldPos; }
	const Math::Vector3 GetRot() const { return m_worldRot; }

	void SetPos(const Math::Vector3& pos)override 
	{
		m_prevPos = pos;
		m_worldPos = pos; 

	}

	//クラスＩDを返す
	const GameObject::ClassID GetClassID() const override
	{
		return GameObject::ClassID::ePlayer;
	}

private:
	void Release();

	static const float s_limitOfStepHeight;

	void UpdateMove(Math::Vector3& dstMove);
	void UpdateRot(const Math::Vector3& srcMove);

	//当たり判定
	void UpdateCollsion();

	void UpdateWorldMatrix();

	void ShotArrow();

	//キャラの移動と回転を個別に変数にする
	Math::Vector3 m_worldPos;
	Math::Vector3 m_worldRot;
	Math::Vector3 m_prevPos;

	std::shared_ptr<TPSCamera> m_spCamera = nullptr;

	KdAnimator m_animetor;

	bool m_canShot = true;

	//垂直方向の移動
	float m_verticalMovement = 0.0f;

	bool m_jumpFlg = false;

	//staticはインスタンスが複製されてもメモリを共有する

};