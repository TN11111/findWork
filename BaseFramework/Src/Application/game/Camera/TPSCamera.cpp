#include "TPSCamera.h"

void TPSCamera::SetCameraMatrix(const DirectX::SimpleMath::Matrix& mWorld)
{
	DirectX::SimpleMath::Matrix gazeTrans;
	gazeTrans = gazeTrans.CreateTranslation({m_localGazepos});

	Math::Matrix localPos;
	localPos = Math::Matrix::CreateTranslation(m_localPos);

	Math::Matrix rot;
	rot = GetRotMatrix();

	KdCamera::SetCameraMatrix(localPos*rot* gazeTrans* mWorld);
}


