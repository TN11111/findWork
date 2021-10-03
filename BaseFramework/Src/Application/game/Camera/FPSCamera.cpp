#include"FPSCamera.h"

const POINT FPSCamera::s_fixMousePos = { 640,360 };

void FPSCamera::Init()
{
	SetCursorPos(s_fixMousePos.x, s_fixMousePos.y);
}

void FPSCamera::Update()
{
	POINT nowPos;
	GetCursorPos(&nowPos);

	POINT mouseMove;
	mouseMove.x = nowPos.x - s_fixMousePos.x;
	mouseMove.y = nowPos.y - s_fixMousePos.y;

	SetCursorPos(s_fixMousePos.x, s_fixMousePos.y);

	//カメラの回転
	m_degAngle.x += mouseMove.y * 0.25f;
	m_degAngle.y += mouseMove.x * 0.25f;

	//カメラの角度を制御する（制限をつける）
	m_degAngle.x = std::clamp(m_degAngle.x,m_minAngleX,m_maxAngleX);

}

const DirectX::SimpleMath::Matrix FPSCamera::GetRotMatrix()
{
	return DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(
	DirectX::XMConvertToRadians(m_degAngle.y),
	DirectX::XMConvertToRadians(m_degAngle.x),
	DirectX::XMConvertToRadians(m_degAngle.z));
}

const DirectX::SimpleMath::Matrix FPSCamera::GetRotYMatrix()
{
	return Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_degAngle.y));
}

void FPSCamera::SetCameraMatrix(const DirectX::SimpleMath::Matrix& mWorld)
{
	DirectX::SimpleMath::Matrix trans;
	trans = trans.CreateTranslation(m_localPos);

	DirectX::SimpleMath::Matrix rot;
	rot = GetRotMatrix();

	KdCamera::SetCameraMatrix(rot * trans * mWorld);
}
