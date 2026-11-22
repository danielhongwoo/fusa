/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 시나리오 실행기의 구현.
 */
#include "scenario.h"

#include <stddef.h>
#include <stdio.h>

#include "vcu.h"

int scenario_run(const scenario_t *sc, sample_t *log, int log_cap)
{
    plant_t plant;
    vcu_t vcu;
    int count = 0;
    int next_driver = 0;

    plant_init(&plant);
    hal_sim_init(&plant);
    vcu_init(&vcu);

    for (time_ms_t t = 0u; t < sc->duration_ms; t++) {
        /* 1. 운전자의 입력 */
        while ((next_driver < sc->driver_count) && (sc->driver[next_driver].t_ms <= t)) {
            plant.pedal = sc->driver[next_driver].pedal;
            plant.brake = sc->driver[next_driver].brake;
            plant.gear = sc->driver[next_driver].gear;
            next_driver++;
        }
        /* 2. fault */
        for (int i = 0; i < sc->fault_count; i++) {
            if (sc->faults[i].t_ms == t) {
                hal_sim_set_fault(sc->faults[i].fault, sc->faults[i].param);
            }
        }
        if (sc->on_tick != NULL) {
            sc->on_tick(t);
        }
        /* 3. 센서와 메시지 */
        hal_sim_step(t);
        /* 4. task table */
        for (int i = 0; i < vcu_task_count; i++) {
            if ((t % vcu_task_table[i].period_ms) == 0u) {
                vcu_task_table[i].run(&vcu);
            }
        }
        /* 5. plant */
        plant_step_1ms(&plant);
        /* 6. 기록 */
        if (count < log_cap) {
            sample_t *s = &log[count];
            s->t_ms = t;
            s->pedal = plant.pedal;
            s->brake = plant.brake;
            s->gear = plant.gear;
            s->apps1_mv = hal_adc_read_mv(HAL_ADC_APPS1);
            s->apps2_mv = hal_adc_read_mv(HAL_ADC_APPS2);
            s->torque_out = hal_sim_last_torque();
            s->enable = hal_sim_enable();
            s->warning = hal_sim_warning();
            s->diag = *hal_sim_diag();
            s->torque_act_nm = plant.torque_act_nm;
            s->speed_mps = plant.speed_mps;
            s->accel_mps2 = plant.accel_mps2;
            count++;
        }
    }
    return count;
}

int scenario_write_csv(const char *path, const sample_t *log, int count)
{
    FILE *f = fopen(path, "w");
    if (f == NULL) {
        return -1;
    }
    fprintf(f, "t_ms,pedal,brake,gear,apps1_mv,apps2_mv,pedal_safe,pedal_fault,"
               "torque_req,torque_allowed,torque_out,enable,latched,warning,"
               "torque_act_nm,speed_mps,accel_mps2\n");
    for (int i = 0; i < count; i++) {
        const sample_t *s = &log[i];
        fprintf(f, "%u,%.3f,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u,%.2f,%.3f,%.3f\n",
                (unsigned)s->t_ms, s->pedal, (int)s->brake, (int)s->gear,
                (int)s->apps1_mv, (int)s->apps2_mv, (int)s->diag.pedal_safe,
                (int)s->diag.pedal_fault, (int)s->diag.torque_req,
                (int)s->diag.torque_allowed, (int)s->torque_out, (int)s->enable,
                (int)s->diag.latched, (unsigned)s->warning, s->torque_act_nm,
                s->speed_mps, s->accel_mps2);
    }
    return (fclose(f) == 0) ? 0 : -1;
}
