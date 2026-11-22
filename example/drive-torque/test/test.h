/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 작은 test 틀. 바깥의 framework를 받지 않으려고 직접 만들었다.
 * 이 틀은 qualification되지 않았다.
 */
#ifndef TEST_H
#define TEST_H

#include <stdio.h>

extern int test_checks;   /* 실행한 검사의 수 */
extern int test_failures; /* 실패한 검사의 수 */

#define CHECK(cond)                                                          \
    do {                                                                     \
        test_checks++;                                                       \
        if (!(cond)) {                                                       \
            test_failures++;                                                 \
            printf("  실패 %s:%d: %s\n", __FILE__, __LINE__, #cond);          \
        }                                                                    \
    } while (0)

#define CHECK_EQ(actual, expected)                                           \
    do {                                                                     \
        long test_a_ = (long)(actual);                                       \
        long test_e_ = (long)(expected);                                     \
        test_checks++;                                                       \
        if (test_a_ != test_e_) {                                            \
            test_failures++;                                                 \
            printf("  실패 %s:%d: %s = %ld, 기대한 값 %ld\n", __FILE__,       \
                   __LINE__, #actual, test_a_, test_e_);                     \
        }                                                                    \
    } while (0)

typedef struct {
    const char *id;   /* test case의 ID. "TC-" 뒤에 번호를 붙인다 */
    const char *name; /* 무엇을 보는가 */
    void (*run)(void);
} test_case_t;

/* 목록의 test를 모두 돌리고 실패한 검사의 수를 돌려준다 */
int test_run_all(const test_case_t *cases, int count);

#endif
