#pragma once

class FPSCamera : public KdCamera
{
public:
	FPSCamera() {}
	~FPSCamera() {}

	//FPSカメラの初期化
	void Init();

	//FPSカメラの更新処理
	void Update();

	void SetLocalPos(DirectX::SimpleMath::Vector3& pos) { m_localPos = pos; }

	const DirectX::SimpleMath::Matrix GetRotMatrix();

	const DirectX::SimpleMath::Matrix GetRotYMatrix();

	void SetCameraMatrix(const DirectX::SimpleMath::Matrix& mWorld) override;

	static const POINT s_fixMousePos;

	void SetClumpAngleX(float minAng, float maxAng)
	{m_minAngleX = minAng; m_maxAngleX = maxAng; }

	const Math::Vector3& GetDegAngle() const { return m_degAngle; }

	const float& GetDegYAngle() const { return m_degAngle.y; }
	
protected:
	//視線用のローカル座標
	DirectX::SimpleMath::Vector3 m_localPos;

private:
	
	//各軸の回転情報
	DirectX::SimpleMath::Vector3 m_degAngle;
	
	float m_minAngleX = -FLT_MAX;
	float m_maxAngleX = FLT_MAX;

};