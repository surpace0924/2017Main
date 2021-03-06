#include "Weapon.hpp"

Arm::Arm(int pin)
{
    CYLINDER_PIN = pin;
}

void Arm::controlBySW(int SWVal1, int SWVal2)
{
    bool canMove = (SWVal1 == 0) ? true : false;
    bool needsAutoAttack = (SWVal2 != 2) ? true : false;

    // アームをもとに戻す必要があるかどうか
    static bool needsReturnArm = true;

    // もういちど自動攻撃処理を実行する必要があるか
    static bool needsComeback = false;
    if (canMove)
    {
        if (needsAutoAttack || needsComeback)
        {
            needsComeback = autoAttack(needsReturnArm, true);
            needsReturnArm = false;
        }
        else
        {
            up();
            needsReturnArm = true;
        }
        isAttacked = true;
    }
    else
    {
        if (needsAutoAttack || needsComeback)
        {
               needsComeback = autoAttack(needsReturnArm, false);
            needsReturnArm = false;
        }
        else
        {
            down();
            needsReturnArm = true;
        }
        isAttacked = false;
    }
}

// 戻り値はもう一度このメソッドをコールする必要があるかどうか
bool Arm::autoAttack(bool reset, bool isUpping)
{
    static bool _reset;
    _reset = reset;
    static unsigned long startTime = millis();
    if(isUpping)
    {
        if (reset)
            startTime = millis();
    
        if (millis() - startTime < 800)
            down();
        else if (millis() - startTime < 1600)
            up();
        else
        {
            // 一連の処理が終了
            startTime = millis();
            _reset = true;
            return false;
        }
    }
    else
    {
        if (reset)
            startTime = millis();

        if (millis() - startTime < 800)
            up();
        else if (millis() - startTime < 1600)
            down();
        else
        {
            // 一連の処理が終了
            startTime = millis();
            _reset = true;
            return false;
        }
    }

    return true;
}

void Arm::up()
{
    digitalWrite(CYLINDER_PIN, HIGH);
}

void Arm::down()
{
    digitalWrite(CYLINDER_PIN, LOW);
}

Burst::Burst(int cylinderPin, int rodPin)
{
    CYLINDER_PIN = cylinderPin;
    ROD_PIN = rodPin;
}

void Burst::controlBySW(int cylinderSW, int rodSW)
{
    if (cylinderSW == 2)
    {
        lift(true);
        if (rodSW == 2)
            expand(true);
        else
            expand(false);
    }
    else
    {
        lift(false);
        expand(false);
    }
}

void Burst::lift(bool needs)
{
    if (needs)
    {
        digitalWrite(CYLINDER_PIN, HIGH);
    }
    else
    {
        digitalWrite(CYLINDER_PIN, LOW);
    }
}

void Burst::expand(bool needs)
{
    if (needs)
    {
        digitalWrite(ROD_PIN, HIGH);
    }
    else
    {
        digitalWrite(ROD_PIN, LOW);
    }
}
