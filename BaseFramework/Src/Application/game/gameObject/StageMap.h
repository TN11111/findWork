#pragma once
#include"GameObject.h"

class StageMap : public GameObject
{
public:
	StageMap();    //コンストラクタ
	~StageMap();   //デストラクタ

	void Init() override;   //初期化
	void Update() override; //更新

	void DrawEffect() override;

	const GameObject::ClassID GetClassID() const override
	{
		return GameObject::ClassID::eStage;
	}

	bool CheckCollisionBump(const SphereInfo& info, BumpResult& result) override;

private:
	void Release();//解放
};