/******************************************************************************
 * @file    scheduler.c
 * @project Lightweight Embedded Scheduler
 * @author  Vivek Patel
 * @brief   Core scheduler implementation
 *
 * @details
 * Implements the internal task table, scheduling logic, and execution flow
 * for a cooperative scheduler. Tasks are executed based on time and priority
 * without preemption.
 *
 * This file contains no hardware-specific code and can be reused across
 * multiple embedded platforms.
 *
 * @version 1.0
 * @date    2025-12-20
 *
 * @license MIT
 ******************************************************************************/

#include "scheduler.h"

/* Implementation starts here */

/* Task control block */
typedef struct
{
    scheduler_task_fn_t task_fn;
    uint32_t period_ms;
    uint32_t remaining_ms;
    uint8_t priority;
    uint8_t active;
} scheduler_task_t;

/* Task table */
static scheduler_task_t task_table[SCHEDULER_MAX_TASKS];
static uint8_t task_count = 0;
//=================================================================================
void scheduler_init(void)
{
    uint8_t i;

    for (i = 0; i < SCHEDULER_MAX_TASKS; i++)
    {
        task_table[i].task_fn      = 0;
        task_table[i].period_ms   = 0;
        task_table[i].remaining_ms = 0;
        task_table[i].priority    = 0;
        task_table[i].active      = 0;
    }

    task_count = 0;
}
//=================================================================================
int scheduler_add_task(scheduler_task_fn_t task_fn,
                       uint32_t period_ms,
                       uint8_t priority)
{
    if (task_fn == 0)
    {
        return -1;
    }

    if (period_ms == 0)
    {
        return -1;
    }

    if (task_count >= SCHEDULER_MAX_TASKS)
    {
        return -1;
    }

    task_table[task_count].task_fn      = task_fn;
    task_table[task_count].period_ms   = period_ms;
    task_table[task_count].remaining_ms = period_ms;
    task_table[task_count].priority    = priority;
    task_table[task_count].active      = 1;

    task_count++;

    return (task_count - 1); /* Return task ID */
}
//=================================================================================
