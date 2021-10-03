#include "KdCamera.h"

// 射影行列の設定
void KdCamera::SetProjectionMatrix(float fov, float maxRange, float minRange, float aspectRatio)
{
	m_mProj = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(fov), aspectRatio, minRange, maxRange);
}

// カメラ行列・ビュー行列セット
void KdCamera::SetCameraMatrix(const DirectX::SimpleMath::Matrix& mCam)
{
	// カメラ行列セット
	m_mCam = mCam;

	// カメラ行列からビュー行列を算出
	m_mView = m_mCam.Invert();
}

// カメラ情報(ビュー・射影行列など)をシェーダへセット
void KdCamera::SetToShader() const
{
	// カメラ座標をセット
	SHADER->m_cb7_Camera.Work().CamPos = m_mCam.Translation();
	// ビュー行列をセット
	SHADER->m_cb7_Camera.Work().mView = m_mView;


	// 射影行列をセット
	SHADER->m_cb7_Camera.Work().mProj = m_mProj;

	// カメラ情報(ビュー行列、射影行列)を、シェーダの定数バッファへ書き込む
	SHADER->m_cb7_Camera.Write();
}

void KdCamera::ConvertScreenToWorld(const Math::Vector2& screenPos, Math::Vector3& result3DPos)
{
	Math::Viewport vp;
	D3D.GetViewport(vp);

	//逆ビューポート変換して射影座標にする
	Math::Matrix trans = Math::Matrix::CreateTranslation(
		screenPos.x / (vp.width * 0.5f),
		screenPos.y / (vp.height * 0.5f),
		1.0f);

	//逆射影行列変換してカメラから見た座標にする
	trans *= GetProjMatrix().Invert();

	//逆ビュー行列変換してワールド座標にする
	trans *= GetViewMatrix().Invert();

	trans._41 /= trans._44;
	trans._42 /= trans._44;
	trans._43 /= trans._44;

	result3DPos = trans.Translation();
}
