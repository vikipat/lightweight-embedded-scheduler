/******************************************************************************
 * @file    scheduler.h
 * @project Lightweight Embedded Scheduler
 * @author  Vivek Patel
 * @brief   Public API for a cooperative embedded task scheduler
 *
 * @details
 * This module provides a lightweight, cooperative scheduler intended for
 * resource-constrained embedded systems. It supports periodic task execution
 * using a fixed time tick without relying on an RTOS.
 *
 * Designed to be:
 * - Platform independent
 * - Deterministic
 * - Easy to integrate into legacy firmware
 *
 * @version 1.0
 * @date    2025-12-20
 *
 * @license MIT
 ******************************************************************************/

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>

/* Configuration */
#define SCHEDULER_MAX_TASKS   8
#define SCHEDULER_TICK_MS     10

typedef void (*scheduler_task_fn_t)(void);

/* API */
void scheduler_init(void);

int scheduler_add_task(scheduler_task_fn_t task_fn,
                       uint32_t period_ms,
                       uint8_t priority);

void scheduler_tick(void);
void scheduler_run(void);

#endif /* SCHEDULER_H */
