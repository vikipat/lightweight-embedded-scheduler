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
