/*
 * C
 *
 * Copyright 2021 MicroEJ Corp. All rights reserved.
 * This library is provided in source code for use, modification and test, subject to license terms.
 * Any modification of the source code will break MicroEJ Corp. warranties on the whole library.
 */

/**
 * @file
 * @brief LLMJVM implementation over Zephyr OS.
 * @author MicroEJ Developer Team
 * @version 1.0.1
 */

/* Includes ------------------------------------------------------------------*/

#include <zephyr.h>

#include "LLMJVM_impl.h"
#include "microej_time.h"
#include "microej.h"

/* Defines -------------------------------------------------------------------*/

/*
 * Useful macros and definitions
 */

/* Globals -------------------------------------------------------------------*/

/*
 * Shared variables
 */
/* Absolute time in ms at which timer will be launched */
static int64_t LLMJVM_zephyr_next_wake_up_time = INT64_MAX;

/* Timer for scheduling next alarm */
static struct k_timer LLMJVM_zephyr_wake_up_timer;

/* Binary semaphore to wakeup microJVM */
static struct k_sem LLMJVM_zephyr_semaphore;

/* Private functions ---------------------------------------------------------*/

static void wake_up_timer_callback(struct k_timer *timer);

static void wake_up_timer_callback(struct k_timer *timer) {
    if(&LLMJVM_zephyr_wake_up_timer == timer) {
        (void) LLMJVM_schedule();
    }
}

/* Public functions ----------------------------------------------------------*/

/*
 * Implementation of functions from LLMJVM_impl.h
 * and other helping functions.
 */

/* 
 * Creates the timer used to callback the LLMJVM_schedule() function.
 *  After its creation, the timer is idle. 
 */
int32_t LLMJVM_IMPL_initialize(void) {
	int32_t result;
	
    k_timer_init(&LLMJVM_zephyr_wake_up_timer, wake_up_timer_callback, NULL);

    int retcode = k_sem_init(&LLMJVM_zephyr_semaphore, 0U, 1U);
	if (0 == retcode) {
		result = LLMJVM_OK;
		
		microej_time_init();
	} else {
		result = LLMJVM_ERROR;
	}
    return result;
}

/* 
 * Once the task is started, save a handle to it.
 */
int32_t LLMJVM_IMPL_vmTaskStarted(void) {
    return LLMJVM_OK;
}

/* 
 * Schedules requests from the VM 
 */
int32_t LLMJVM_IMPL_scheduleRequest(int64_t absoluteTime) {
    int32_t result = LLMJVM_OK;
    int64_t currentTime = LLMJVM_IMPL_getCurrentTime(MICROEJ_TRUE);
    int64_t relativeTime = absoluteTime - currentTime;
    int64_t relativeTick = microej_time_time_to_tick(relativeTime);

    if(relativeTick <= 0) {
        LLMJVM_zephyr_next_wake_up_time = INT64_MAX;

        k_timer_stop(&LLMJVM_zephyr_wake_up_timer);

        result = LLMJVM_schedule();
    } else if((k_timer_status_get(&LLMJVM_zephyr_wake_up_timer) > 0U) 	|| 
	   (absoluteTime < LLMJVM_zephyr_next_wake_up_time) 		|| 
	   (LLMJVM_zephyr_next_wake_up_time <= currentTime)) {
        /* Save new alarm absolute time */
        LLMJVM_zephyr_next_wake_up_time = absoluteTime;

        /* Schedule the new alarm */
        k_timer_start(&LLMJVM_zephyr_wake_up_timer, K_MSEC(relativeTime), K_NO_WAIT);
    } else {
		/* else: there is a pending request that will occur before the new one -> do nothing */
	}
    return result;
}

/* 
 * Suspends the VM task if the pending flag is not set 
 */
int32_t LLMJVM_IMPL_idleVM(void) {
	int32_t result;
    if (k_sem_take(&LLMJVM_zephyr_semaphore, K_FOREVER) != 0) {
        result = LLMJVM_ERROR;
    } else {
		result = LLMJVM_OK;
	}
	return result;
}

/* 
 * Wakes up the VM task 
 */
int32_t LLMJVM_IMPL_wakeupVM(void) {
    k_sem_give(&LLMJVM_zephyr_semaphore);
	
    return LLMJVM_OK;
}

/* 
 * Clear the pending wake up flag and reset next wake up time 
 */
int32_t LLMJVM_IMPL_ackWakeup(void) {
    return LLMJVM_OK;
}

/* 
 * Gets the current task id 
 */
int32_t LLMJVM_IMPL_getCurrentTaskID(void) {
	// cppcheck-suppress [misra-c2012-11.4]
    return (int32_t) k_current_get();
}

/*
 * Sets application time
 */
void LLMJVM_IMPL_setApplicationTime(int64_t t) {
    microej_time_set_application_time(t);
}

/*
 * Gets the system or the application time in milliseconds
 */
int64_t LLMJVM_IMPL_getCurrentTime(uint8_t sys) {
    return microej_time_get_current_time(sys);
}

/*
 * Gets the current system time in nanoseconds
 */
int64_t LLMJVM_IMPL_getTimeNanos(void) {
    return microej_time_get_time_nanos();
}

/*
 * Shuts the system down
 */
int32_t LLMJVM_IMPL_shutdown(void) {
    return LLMJVM_OK;
}

