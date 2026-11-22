/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 공통 형과 단위. 감시 쪽 계산은 모두 정수다.
 */
#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <stdint.h>

typedef int32_t torque_t;    /* 구동 토크, 단위 0.1 Nm. 양수는 전진 방향 */
typedef int32_t permille_t;  /* 페달 위치, 0 (놓음) - 1000 (끝까지 밟음) */
typedef int32_t speed_t;     /* 차량 속도, 단위 0.01 m/s */
typedef int32_t millivolt_t; /* 전압, 단위 mV */
typedef uint32_t time_ms_t;  /* 시간, 단위 ms */

typedef enum {
    GEAR_P = 0,
    GEAR_R = 1,
    GEAR_N = 2,
    GEAR_D = 3
} gear_t;

/* CAN으로 오가는 메시지 하나. 값에 counter와 CRC가 붙는다 (src/com/e2e.h) */
typedef struct {
    int32_t value;
    uint8_t counter;
    uint8_t crc;
} frame_t;

#define TORQUE_MAX      ((torque_t)2500)  /* 모터의 최대 토크: 250.0 Nm */
#define PEDAL_FULL      ((permille_t)1000)
#define CYCLE_MS        ((time_ms_t)10)   /* 제어 주기 */

#endif
