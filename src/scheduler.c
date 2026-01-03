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
    uint8_t ready;
    uint8_t running;   
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
        task_table[i].running     = 0;
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
    if (priority > 10)
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
void scheduler_tick(void)
{
    uint8_t i;


    if (task_count == 0)
    {
        return;
    }

    for (i = 0; i < task_count; i++)
    {
        if (task_table[i].active)
        {
            if (task_table[i].remaining_ms > SCHEDULER_TICK_MS)
            {
                task_table[i].remaining_ms -= SCHEDULER_TICK_MS;
            }
            else
            {
                task_table[i].remaining_ms = 0;
                task_table[i].ready = 1;
            }
        }
    }
}
//=================================================================================
void scheduler_run(void)
{
    uint8_t i;
    int selected = -1;
    uint8_t highest_priority = 0xFF;

    if (task_count == 0)
    {
        return;
    }



    /* Find highest-priority ready task */
    for (i = 0; i < task_count; i++)
    {
        if (task_table[i].active && task_table[i].ready)
        {
            if (task_table[i].priority < highest_priority)
            {
                highest_priority = task_table[i].priority;
                selected = i;
            }
        }
    }

    /* Execute selected task */
    if (selected >= 0)
    {
        if (task_table[selected].running == 0)
        {
            task_table[selected].running = 1;

            task_table[selected].task_fn();

            task_table[selected].running = 0;

            /* Re-arm periodic task */
            task_table[selected].remaining_ms =
                task_table[selected].period_ms;

            task_table[selected].ready = 0;
        }
    }

}
