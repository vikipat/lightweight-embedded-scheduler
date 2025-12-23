/******************************************************************************
 * @file    main.c
 * @project Lightweight Embedded Scheduler
 * @author  Vivek Patel
 * @brief   Host-based example demonstrating scheduler usage
 *
 * @details
 * This example demonstrates how to use the lightweight embedded scheduler
 * in a host-based environment. A simulated 10 ms tick is used instead of
 * a hardware timer interrupt.
 *
 * This file is intended for demonstration and testing only.
 *
 * @version 1.0
 * @date    2025-12-20
 *
 * @license MIT
 ******************************************************************************/

#include "scheduler.h"
#include <stdio.h>

/* Example task functions */

static void task_high_priority(void)
{
    printf("High priority task executed\n");
}

static void task_low_priority(void)
{
    printf("Low priority task executed\n");
}

int main(void)
{
    /* Initialize scheduler */
    scheduler_init();

    /* Register tasks
     * Lower number = higher priority
     */
    scheduler_add_task(task_high_priority, 100, 0);
    scheduler_add_task(task_low_priority,  300, 2);

    /* Main loop */
    while (1)
    {
        /* Simulate 10 ms system tick */
        scheduler_tick();

        /* Run scheduler */
        scheduler_run();

        /* In real embedded systems, scheduler_tick() would be
         * called from a hardware timer ISR.
         */
    }

    /* Should never reach here */
    return 0;
}
