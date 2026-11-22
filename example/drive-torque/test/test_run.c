/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 작은 test 틀의 구현.
 */
#include "test.h"

int test_checks = 0;
int test_failures = 0;

int test_run_all(const test_case_t *cases, int count)
{
    for (int i = 0; i < count; i++) {
        int before = test_failures;
        cases[i].run();
        printf("%s  %s  %s\n", (test_failures == before) ? "통과" : "실패", cases[i].id,
               cases[i].name);
    }
    printf("test %d개, 검사 %d개, 실패 %d개\n", count, test_checks, test_failures);
    return test_failures;
}
