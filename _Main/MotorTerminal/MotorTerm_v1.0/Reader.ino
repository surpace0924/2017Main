//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @Outline: 受信処理
// @Date: 2017/10/21
// @Author: Ryoga Sato
// @Version: 1.0
// @Description: 
// ボーレートは57600bps
// @Update:
// @TODO:
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool recieveData()
{
    unsigned long startTime = millis();

    while (millis() - startTime < SERIAL_TIMEOUT)
    {
        if (Serial.read() == OST)
        {
            startTime = millis();

            // 受信待機
            while (!Serial.available())
            if (millis() - startTime > SERIAL_TIMEOUT)
                return false;

        // データ長を取得
        rcvData[0] = Serial.read();

        while (Serial.available() < 33)
            if (millis() - startTime > SERIAL_TIMEOUT)
                return false;

            // データ長だけデータを受け付ける
            // 同時にデータの排他的論理総和を取る


            int bufSum = 0;
            for (int i = 1; i <= 31; i++)
            {
                rcvData[i] = Serial.read();
                bufSum ^= rcvData[i];
            }

            Serial.println(rcvData[0]);
            
            // 必要なデータが送られてきた直後にはチェックサムが送られてくるので取得
            int checkSum = Serial.read();

            // データの排他的論理総和とチェックサムが一致するかを確認
            // チェックサムが255の場合は代わりに254が送られてくるのでそれにも対応
            if (((checkSum ^ bufSum) == 0) || ((checkSum ^ bufSum - 1) == 0))
            {
                // 一致 グローバル変数に書き込む
                for (int i = 0; i <= 16; i++) {
                    type[i] = (rcvData[i*2]&0b00000100)>>2;
                    if (type[i*2] == 0)
                    {
                        state[i] = rcvData[i*2];
                        pwm[i] = rcvData[i*2+1];
                    }
                    else
                    {
                        arg[i] = (rcvData[i*2]&0b00000011);
                        arg[i] += rcvData[i*2+1];
                    }
                }
                
                return true;
            }
            else
            {
                // 不一致 falseで返す
                return false;
            }
        }
    }
    return false;
}