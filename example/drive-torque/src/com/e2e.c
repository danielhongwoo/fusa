/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 통신의 보호와 검사의 구현.
 */
#include "e2e.h"

void e2e_tx_init(e2e_tx_t *st)
{
    st->counter = 0u;
}

void e2e_rx_init(e2e_rx_t *st)
{
    st->last_counter = 0u;
    st->synced = false;
    st->ok = false;
}

uint8_t e2e_crc8(const uint8_t *data, uint8_t len)
{
    /* 계산은 부호 없는 32 bit로 하고 끝에 한 번만 8 bit로 좁힌다.
     * uint8_t로 계산하면 식 안에서 int (부호 있는 형)로 넓어져, 밀기와 bit 연산이 부호 있는 값에 걸린다 */
    uint32_t crc = 0xFFu;

    for (uint8_t i = 0u; i < len; i++) {
        crc ^= data[i];
        for (uint8_t bit = 0u; bit < 8u; bit++) {
            if ((crc & 0x80u) != 0u) {
                crc = ((crc << 1u) & 0xFFu) ^ 0x1Du;
            } else {
                crc = (crc << 1u) & 0xFFu;
            }
        }
    }
    return (uint8_t)(crc ^ 0xFFu);
}

/* 부호 있는 값을 전송하는 32 bit (2의 보수)로 편다.
 * 음수를 부호 없는 형으로 바로 바꾸지 않는다. 그 변환의 결과는 C 규격이 정해 두었지만,
 * 값이 달라지는 변환을 쓰지 않아야 그런 변환을 찾는 도구의 경고를 끄지 않고 둘 수 있다 */
static uint32_t to_wire(int32_t value)
{
    return (value >= 0) ? (uint32_t)value : (0xFFFFFFFFu - (uint32_t)(-(value + 1)));
}

/* data ID, counter, 값 (낮은 byte부터)의 여섯 byte에 대한 CRC */
static uint8_t frame_crc(uint8_t data_id, uint8_t counter, int32_t value)
{
    uint32_t v = to_wire(value);
    uint8_t bytes[6];

    bytes[0] = data_id;
    bytes[1] = counter;
    bytes[2] = (uint8_t)(v & 0xFFu);
    bytes[3] = (uint8_t)((v >> 8u) & 0xFFu);
    bytes[4] = (uint8_t)((v >> 16u) & 0xFFu);
    bytes[5] = (uint8_t)((v >> 24u) & 0xFFu);
    return e2e_crc8(bytes, 6u);
}

void e2e_protect(e2e_tx_t *st, uint8_t data_id, int32_t value, frame_t *frame)
{
    /* SWR-17: counter는 메시지마다 1 오르고 15 다음에 0으로 돈다 */
    uint8_t counter = (uint8_t)(st->counter & E2E_COUNTER_MASK);

    frame->value = value;
    frame->counter = counter;
    frame->crc = frame_crc(data_id, counter, value);
    st->counter = (uint8_t)((counter + 1u) & E2E_COUNTER_MASK);
}

bool e2e_check(e2e_rx_t *st, uint8_t data_id, const frame_t *frame, bool seen, bool fresh, time_ms_t age_ms)
{
    /* SWR-18: 받은 적이 없거나 새 메시지가 너무 오래 없으면 무효다 */
    if (!seen || (age_ms > E2E_TIMEOUT_MS)) {
        st->ok = false;
        return false;
    }
    /* 새 메시지가 없으면 지난 판정이 그대로다 */
    if (fresh) {
        if (frame->crc != frame_crc(data_id, frame->counter, frame->value)) {
            /* 값이나 counter가 바뀌었거나, 다른 종류의 메시지다 */
            st->ok = false;
        } else {
            /* 지난 counter에서 몇 앞섰는가 (0-15). 16u를 더해 뺄셈이 음수가 되지 않고 식이 부호 없는 계산이 되게 한다.
             * 작은 정수형은 식 안에서 int로 넓어지므로, 그대로 빼면 음수에 bit 연산이 걸린다. 결과는 더하지 않아도 같다 */
            uint8_t step = (uint8_t)(((frame->counter & E2E_COUNTER_MASK) + 16u
                                      - (st->last_counter & E2E_COUNTER_MASK)) & E2E_COUNTER_MASK);
            /* 처음 받은 메시지는 견줄 것이 없으므로 받아들인다.
             * 그 뒤로는 counter가 1에서 3까지 앞서야 한다. 0이면 같은 메시지의 되풀이다 */
            st->ok = !st->synced || ((step >= 1u) && (step <= E2E_MAX_STEP));
            st->last_counter = frame->counter;
            st->synced = true;
        }
    }
    return st->ok;
}
