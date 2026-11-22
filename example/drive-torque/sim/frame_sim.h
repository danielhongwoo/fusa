/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * sim 쪽 (inverter, 제동 제어기)의 메시지 만들기와 검사.
 *
 * 제품의 코드 (src/com/e2e.c)를 부르지 않고 따로 썼다. CRC도 다른 방식 (표를 쓰는 방식)으로 계산한다.
 * 같은 코드를 양쪽에 쓰면 그 코드의 결함이 보내는 쪽과 받는 쪽에서 서로 맞아떨어져 드러나지 않는다.
 * 그래도 두 구현을 쓴 것은 같은 진행자다. 규칙을 잘못 이해했다면 둘이 같이 틀린다.
 */
#ifndef FRAME_SIM_H
#define FRAME_SIM_H

#include "types.h"

#define SIM_ID_TORQUE   33u
#define SIM_ID_SPEED    66u
#define SIM_ID_INVERTER 99u

/* 값에 counter와 CRC를 붙여 메시지를 만든다 */
void frame_sim_make(frame_t *frame, unsigned data_id, unsigned counter, int32_t value);

/* 메시지의 CRC가 그 종류 (data ID)의 것으로 맞는가 */
bool frame_sim_crc_ok(const frame_t *frame, unsigned data_id);

#endif
