/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * sim 쪽의 메시지 만들기와 검사의 구현.
 */
#include "frame_sim.h"

static uint8_t table[256];
static bool table_ready = false;

/* CRC-8 (다항식 0x1D)의 표를 만든다 */
static void make_table(void)
{
    for (unsigned i = 0u; i < 256u; i++) {
        unsigned c = i;
        for (int bit = 0; bit < 8; bit++) {
            c = ((c & 0x80u) != 0u) ? (((c << 1) ^ 0x1Du) & 0xFFu) : ((c << 1) & 0xFFu);
        }
        table[i] = (uint8_t)c;
    }
    table_ready = true;
}

static uint8_t crc_of(unsigned data_id, unsigned counter, int32_t value)
{
    uint32_t v = (uint32_t)value;
    unsigned bytes[6] = { data_id & 0xFFu, counter & 0xFFu, v & 0xFFu, (v >> 8) & 0xFFu,
                          (v >> 16) & 0xFFu, (v >> 24) & 0xFFu };
    unsigned crc = 0xFFu;

    if (!table_ready) {
        make_table();
    }
    for (int i = 0; i < 6; i++) {
        crc = table[(crc ^ bytes[i]) & 0xFFu];
    }
    return (uint8_t)(crc ^ 0xFFu);
}

void frame_sim_make(frame_t *frame, unsigned data_id, unsigned counter, int32_t value)
{
    frame->value = value;
    frame->counter = (uint8_t)(counter & 15u);
    frame->crc = crc_of(data_id, counter & 15u, value);
}

bool frame_sim_crc_ok(const frame_t *frame, unsigned data_id)
{
    return frame->crc == crc_of(data_id, frame->counter, frame->value);
}
