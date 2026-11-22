/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 고장 대응의 상태 기계의 구현.
 */
#include "reaction.h"

void reaction_init(reaction_t *r)
{
    r->state = REACTION_NORMAL;
}

reaction_state_t reaction_state(const reaction_t *r)
{
    /* SWR-25: 알 수 없는 값은 가장 안전한 상태로 본다.
     * 변수가 망가졌을 때 "정상"으로 읽히는 길을 두지 않는다 */
    if ((r->state != REACTION_NORMAL) && (r->state != REACTION_LIMP) && (r->state != REACTION_ZERO)) {
        return REACTION_CUT;
    }
    return r->state;
}

void reaction_raise(reaction_t *r, reaction_state_t wanted)
{
    reaction_state_t now = reaction_state(r);

    /* SWR-25: 상태는 안전한 쪽으로만 바뀐다 */
    if ((wanted != REACTION_NORMAL) && (wanted != REACTION_LIMP) && (wanted != REACTION_ZERO)) {
        r->state = REACTION_CUT;
    } else if (wanted > now) {
        r->state = wanted;
    } else {
        r->state = now;
    }
}

torque_t reaction_torque_cap(reaction_state_t state)
{
    if (state == REACTION_NORMAL) {
        return TORQUE_MAX;
    }
    if (state == REACTION_LIMP) {
        return LIMP_TORQUE_CAP;
    }
    return 0;
}

bool reaction_enable(reaction_state_t state)
{
    return (state == REACTION_NORMAL) || (state == REACTION_LIMP) || (state == REACTION_ZERO);
}

uint8_t reaction_warning(reaction_state_t state)
{
    if (state == REACTION_NORMAL) {
        return WARNING_NONE;
    }
    if (state == REACTION_LIMP) {
        return WARNING_AMBER;
    }
    return WARNING_RED;
}

torque_t reaction_app_limit(reaction_state_t state)
{
    /* SWR-24: 줄여 감 상태에서 기능은 35 Nm를 넘게 요구하지 않는다 */
    return (state == REACTION_LIMP) ? LIMP_APP_TORQUE : TORQUE_MAX;
}
