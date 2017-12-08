//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @Outline: 独立4輪ステアの出力値を計算する
// @Author: Ryoga Sato
// @Description: 
// 三角関数を用いた計算を行い、なめらかな移動を実現する
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _STEERING_
#define _STEERING_

#include <Arduino.h>
#include "Universal.hpp"

class Steering
{
public:
    void calculate(int _velocityVector[3], int maxOutputRate, int _pwm[4], int _arg[4]);
private:
};

#endif