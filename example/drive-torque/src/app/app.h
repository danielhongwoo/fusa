/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 기능: 운전자의 입력에서 토크 요구를 만든다.
 * safety goal SG-01에 대해서는 이 모듈에 안전 요구사항을 주지 않았다.
 * 이 모듈이 틀려도 SG-01을 어기지 않게 하는 것은 감시와 출력 단계의 일이다.
 */
#ifndef APP_H
#define APP_H

#include "types.h"

typedef struct {
    torque_t prev;       /* 지난 주기의 토크 요구 */
    bool brake_override; /* 제동 우선이 걸려 있는가 */
} app_t;

void app_init(app_t *st);

/* 한 주기의 토크 요구를 계산한다. pedal은 입력 검사를 거친 안전한 페달 값이다 */
torque_t app_step(app_t *st, permille_t pedal, bool brake, gear_t gear,
                  bool speed_valid, speed_t speed);

#endif
