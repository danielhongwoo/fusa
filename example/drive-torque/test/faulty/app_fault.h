/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 결함이 있는 기능 모듈. test에서만 쓴다.
 * src/app/app.c 대신 link되어 같은 interface (app.h)를 구현한다.
 * 정상인 기능을 감싸고, 켜진 동안 그 결과를 틀리게 바꾼다.
 */
#ifndef APP_FAULT_H
#define APP_FAULT_H

#include "types.h"

typedef enum {
    APP_FAULT_NONE = 0, /* 정상인 기능 그대로 */
    APP_FAULT_OFFSET,   /* 토크 요구에 값을 더한다 (너무 큰 토크) */
    APP_FAULT_HALF      /* 토크 요구를 절반으로 줄인다 (모자란 토크) */
} app_fault_mode_t;

void app_fault_set(app_fault_mode_t mode, torque_t offset);

#endif
