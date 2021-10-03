#pragma once

#include"FPSCamera.h"

class TPSCamera : public FPSCamera
{
public: 
	TPSCamera() {};
	~TPSCamera() {};

	void SetCameraMatrix(const DirectX::SimpleMath::Matrix& mWorld) override;

	void SetLocalGazePosition(const DirectX::SimpleMath::Vector3& pos)
	{
		m_localGazepos = pos;
	}
private:
	DirectX::SimpleMath::Vector3 m_localGazepos;
};