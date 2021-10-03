#include "Time.h"

void Time::Init()
{
    timer = 100;
    cnt = 60;

    firstSec = 0;
    secondSec = 0;
    thirdSec = 0;

    m_FTexture = GameResourceFactory.GetTexture("Date/Textures/number/num.png");
    m_STexture = GameResourceFactory.GetTexture("Date/Textures/number/num.png");
    m_TTexture = GameResourceFactory.GetTexture("Date/Textures/number/num.png");
}

void Time::Update()
{
    cnt--;

    if (cnt <= 0)
    {
        timer--;
        cnt = 60;
    }

    //3桁目の数値
    thirdSec = timer / 100;

    //２桁目の数値
    secondSec = timer / 10;
    if (secondSec >= 10)
    {
        secondSec -= 10;
    }
    //１桁目の数値
    firstSec = timer - (thirdSec * 100) - (secondSec * 10);

    if (timer <= 0)
    {
        GameSystem::GetInstance().RequestChangeScene("Result");
    }
}

void Time::Draw2()
{
    UpdateRect(firstSec);
    SHADER->m_spriteShader.DrawTex(m_TTexture.get(), -300, 280, 64, 128, &rect);

    UpdateRect(secondSec);
    SHADER->m_spriteShader.DrawTex(m_STexture.get(), -400, 280, 64, 128, &rect);

    UpdateRect(thirdSec);
    SHADER->m_spriteShader.DrawTex(m_FTexture.get(), -500, 280, 64, 128, &rect);
   // SHADER->m_spriteShader.DrawTex(m_FTexture.get(), -460, 280, Math::Rectangle(firstSec * width,0.f,32.f,64.f));
}

void Time::Reset()
{
    timer = 120;
    cnt = 60;

    firstSec = 0;
    secondSec = 0;
    thirdSec = 0;
}

void Time::Release()
{
}
