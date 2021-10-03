#include "Effect2D.h"

void Effect2D::Init()
{
	SetTexture("Date/Textures/Explosion.png");
	m_spTexture = GameResourceFactory.GetTexture("Date/Textures/Explosion.png");
}

void Effect2D::Update()
{
	//if (m_poly.IsAnimationEnd() || m_loopFlg) 
	//{
	//	if (--m_lifeSpan >= 0)
	//	{
	//		//m_isAlive = false;
	//		Destroy();
	//	}
	//}

	if (m_poly.IsAnimationEnd()) { return; }
	//if (m_poly.GetAnimationSize() <= 1) { return; }

	m_poly.Animation(m_animSpd, m_loopFlg);

	if (m_poly.IsAnimationEnd())
	{
		m_isAlive = false;
	}
}

void Effect2D::Draw()
{
}

void Effect2D::DrawEffect()
{	
	Math::Matrix mDraw;

	//行列の拡縮
	Math::Vector3 scale;
	scale.x = m_mWorld.Right().Length();
	scale.y = m_mWorld.Up().Length();
	scale.z = m_mWorld.Backward().Length();

	//それぞれの拡縮の合成
	mDraw = Math::Matrix::CreateScale(scale);

	//行列の回転
	std::shared_ptr<KdCamera> gameCam = GameInstance.GetCamera();

	if (gameCam)
	{
		Math::Matrix mCamInv = gameCam->GetCamera();
		mCamInv.Invert();

		mDraw *= mCamInv;
	}


	//行列の移動
	mDraw.Translation(m_mWorld.Translation());

	SHADER->m_effectShader.DrawSquarePolygon(m_poly,mDraw);

}
void Effect2D::Draw2()
{
}

void Effect2D::SetAnimation(int splitX, int splitY, float speed,bool loop)
{
	m_poly.SetAnimationInfo(splitX, splitY);

	m_animSpd = speed;
	m_loopFlg = loop;
}

void Effect2D::Release()
{
}

