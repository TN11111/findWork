#pragma once

//球体の当たり判定情報
struct SphereInfo
{
	//引数なしのコンストラクタ
	SphereInfo() = default;

	//引数付きコンストラクタ
	SphereInfo(const Math::Vector3& pos, float radius):
		m_pos(pos),
		m_radius(radius) {}

	
	Math::Vector3 m_pos;
	float m_radius = 1.0f;
};

struct BumpResult
{
	bool m_isHit = false;
	Math::Vector3 m_pushVec;
};

struct RayInfo
{
	RayInfo() {}

	RayInfo(const Math::Vector3& pos, Math::Vector3& dir, float radius) :
		m_pos(pos),
		m_dir(dir),
		m_radius(radius) {m_dir.Normalize();}

	 Math::Vector3 m_pos;
	 Math::Vector3 m_dir;
	float m_radius = 1.0f;
};

class GameObject
{
public:
	enum ClassID
	{
		eBase,
		eStage,
		ePlayer,
		eEnemy
	};

	GameObject() {}
	virtual ~GameObject() { Release(); }

	virtual void Init() {}
	virtual void Update(){}

	virtual void Draw();
	virtual void DrawEffect() {}
	virtual void Draw2();

	void Destroy() { m_isAlive = false; }

	virtual void SetPos(const Math::Vector3& pos) { m_mWorld.Translation(pos); }


	virtual const Math::Vector3 GetPos() const { return m_mWorld.Translation(); }

	virtual const GameObject::ClassID GetClassID() const { return GameObject::eBase; }

	bool IsAlive() { return m_isAlive; }

	//物体同士の判定

	//info:相手のレイ情報
	//result:当たったか及び押し返すベクトル
	//戻り値:当たったかどうか
	virtual bool CheckCollisionBump(const SphereInfo& info, BumpResult& result);
	bool CheckCollisionBump(const RayInfo& info, BumpResult& result);

	
protected:
	KdModelWork m_modelWork;

	Math::Matrix m_mWorld;

	bool m_isAlive;

	//キャラクタの球情報
	SphereInfo m_bumpSphereInfo;

private:
	void Release() {}

};