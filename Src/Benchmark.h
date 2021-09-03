/**
 * @file Benchmark.h
 * @author Ali Mirghasemi (you@domain.com)
 * @brief This library use for calculate code performances
 * @version 0.1
 * @date 2021-01-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef _BENCHMARK_H_
#define _BENCHMARK_H_

#include <stdint.h>

/**
 * @brief user function that want calculate performances 
 */
typedef void (*Benchmark_TestCaseFn)(void);
/**
 * @brief you can edit 'Benchmark_Ticks' to uint64_t type for larger ticks
 */
typedef uint32_t Benchmark_Ticks;
/**
 * @brief User must write function for getting current ticks
 * @return Benchmark_Ticks
 */
typedef Benchmark_Ticks (*Benchmark_CurrentTicksFn)(void);
/**
 * @brief if user wanna have real and acuurate becnhamrk, must create start and stop timer functions
 */ 
typedef void (*Benchmark_StartTimerFn)(void);
/**
 * @brief if user wanna have real and acuurate becnhamrk, must create start and stop timer functions
 */ 
typedef void (*Benchmark_StopTimerFn)(void);
/**
 * @brief for using Benchmark library user must generate these function and fulfill abstract layer
 */
typedef struct {
    Benchmark_CurrentTicksFn  currentTicks;   /**< get current ticks of system produced by user driver */
    Benchmark_StartTimerFn    startTimer;     /**< start timer function, if set this param null library just use currentTicks */
    Benchmark_StopTimerFn     stopTimer;      /**< stop timer function, if set this param null library just use currentTicks */
} Benchmark_Driver;


void Benchmark_init(Benchmark_Driver* driver);

Benchmark_Ticks Benchmark_run(Benchmark_TestCaseFn testCase);
Benchmark_Ticks Benchmark_runMulti(Benchmark_TestCaseFn testCase, Benchmark_Ticks* times, uint8_t n);

Benchmark_Ticks Benchmark_delta(void);

#endif /* _BENCHMARK_H_ */
