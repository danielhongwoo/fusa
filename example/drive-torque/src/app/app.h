/*
 * 기능: 운전자의 입력에서 토크 요구를 만든다.
 * safety goal SG-01에 대해서는 이 모듈에 안전 요구사항을 주지 않았다.
 * 이 모듈이 틀려도 SG-01을 어기지 않게 하는 것은 감시와 출력 단계의 일이다.
 *
 * 그 말이 성립하려면 조건이 둘 있다 (docs/technical-safety-concept.md 3절).
 *   1. 정상인 이 모듈의 토크 요구는 감시의 허용 토크를 넘지 않는다.
 *   2. 허용 토크와 정상인 이 모듈의 토크 요구의 차이는 SG-01의 한계보다 작다.
 * 그래서 이 모듈은 토크를 페달 위치에 비례하게 내고, 속도에 따라 줄이지 않는다.
 * 같은 이유로 이 모듈은 감시가 모르는 상태를 갖지 않는다. 갖고 있는 상태는 지난 주기의 토크 하나다.
 *
 * SG-02에 대해서는 이 모듈이 요구사항을 받는다 (SWR-26). 위의 조건 1이 그것이다.
 * 이 모듈이 어기면 SG-01은 지켜지지만 (감시가 깎는다), 고장이 없는데 구동력을 잃는다.
 */
#ifndef APP_H
#define APP_H

#include "types.h"

typedef struct {
    torque_t prev; /* 지난 주기의 토크 요구 */
} app_t;

void app_init(app_t *st);

/* 한 주기의 토크 요구를 계산한다. pedal은 입력 검사를 거친 안전한 페달 값이다 */
torque_t app_step(app_t *st, permille_t pedal, bool brake, gear_t gear, torque_t limit);

#endif
