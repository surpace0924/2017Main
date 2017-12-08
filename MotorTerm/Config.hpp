//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @Outline: 設定処理
// @Author: Ryoga Sato
// @Description:
//  制御対象のモータと使用するMDの選択を行う処理
//  このファイル以外は管理者の許可なく書き換えるのは禁止する
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _CONFIG_
#define _CONFIG_
// 使用するモータの番号を入力（ステアの場合は先頭の要素を使用）
const int USE_MOTOR[2] = {0, 1};

// 使用する機構
// #define _USE_MECANUM_
#define _USE_STEERING_

// 使用するセンサ
//#define _USE_POTENTIOMETER_
// #define _USE_ENCODER_

#endif
