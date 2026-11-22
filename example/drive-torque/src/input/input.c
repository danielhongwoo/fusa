/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 입력 읽기: 주기마다 한 번 HAL에서 입력을 읽어 구조체 하나에 담는다.
 */
#include "input.h"

#include "hal.h"

void input_read(inputs_t *in)
{
    in->apps1_mv = hal_adc_read_mv(HAL_ADC_APPS1);
    in->apps2_mv = hal_adc_read_mv(HAL_ADC_APPS2);
    in->brake = hal_brake_pressed();
    in->gear = hal_gear_read();
    if ((in->gear != GEAR_P) && (in->gear != GEAR_R) && (in->gear != GEAR_D)) {
        in->gear = GEAR_N; /* 알 수 없는 값은 N으로 본다 */
    }
}
