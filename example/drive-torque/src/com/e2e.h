/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 통신: 보내는 메시지에 보호를 붙이고, 받는 메시지를 검사한다.
 * 하드웨어를 부르지 않는다.
 *
 * 메시지마다 counter (0-15, 메시지마다 1 오른다)와 CRC를 싣는다.
 * data ID는 메시지의 종류마다 다른 값이다. 메시지에 싣지 않고 CRC의 계산에만 넣는다.
 * 그래서 다른 종류의 메시지가 잘못 들어오면 CRC가 맞지 않는다.
 *
 * 이 책의 단순한 구현이다. AUTOSAR의 E2E profile을 구현한 것이 아니다.
 */
#ifndef E2E_H
#define E2E_H

#include "types.h"

#define E2E_ID_TORQUE   ((uint8_t)33)  /* 토크 요구 (VCU -> inverter) */
#define E2E_ID_SPEED    ((uint8_t)66)  /* 차량 속도 (제동 제어기 -> VCU) */
#define E2E_ID_INVERTER ((uint8_t)99)  /* inverter의 상태 (inverter -> VCU) */

#define E2E_COUNTER_MASK ((uint8_t)15)        /* counter는 0-15를 돈다 */
#define E2E_MAX_STEP     ((uint8_t)3)         /* counter가 이만큼까지 앞서면 받아들인다 (메시지를 둘까지 잃음). 임시 값 */
#define E2E_TIMEOUT_MS   ((time_ms_t)50)      /* 이 시간 넘게 새 메시지가 없으면 무효다. 임시 값 */

/* 보내는 쪽의 상태 */
typedef struct {
    uint8_t counter; /* 다음에 실을 counter */
} e2e_tx_t;

/* 받는 쪽의 상태 */
typedef struct {
    uint8_t last_counter; /* 마지막으로 CRC가 맞은 메시지의 counter */
    bool synced;          /* CRC가 맞는 메시지를 한 번이라도 받았는가 */
    bool ok;              /* 마지막으로 받은 새 메시지가 검사를 통과했는가 */
} e2e_rx_t;

void e2e_tx_init(e2e_tx_t *st);
void e2e_rx_init(e2e_rx_t *st);

/* CRC-8 (다항식 0x1D, 처음 값 0xFF, 끝에 0xFF와 XOR) */
uint8_t e2e_crc8(const uint8_t *data, uint8_t len);

/* 보낼 메시지를 만든다: 값을 싣고, counter를 붙이고, CRC를 계산한다 */
void e2e_protect(e2e_tx_t *st, uint8_t data_id, int32_t value, frame_t *frame);

/*
 * 받은 메시지를 검사한다. 값이 유효하면 참이다. 거짓이면 frame의 값을 쓰면 안 된다.
 *   seen   한 번이라도 받았는가
 *   fresh  지난번에 검사한 뒤로 새 메시지를 받았는가
 *   age_ms 마지막으로 받은 뒤로 흐른 시간
 */
bool e2e_check(e2e_rx_t *st, uint8_t data_id, const frame_t *frame, bool seen, bool fresh, time_ms_t age_ms);

#endif
