#include "Benchmark.h"

/* private macros */

/* private variables */
static Benchmark_Driver* benchmarkDriver;
/* private functions */
static void Benchmark_empty(void);
static Benchmark_Ticks Benchmark_calculate(Benchmark_TestCaseFn testCase);

/**
 * @brief used for initialize Benchmark library, set driver
 * @param driver 
 */
void Benchmark_init(Benchmark_Driver* driver) {
    benchmarkDriver = driver;
}
/**
 * @brief used for calculate testCase performance just run one time
 * 
 * @param testCase function that we want run calculate performance
 * @return Benchmark_Ticks return ticks spended for testCase
 */
Benchmark_Ticks Benchmark_run(Benchmark_TestCaseFn testCase) {
    Benchmark_Ticks delta;
    Benchmark_Ticks testCaseTicks;
    /* calculate delta */
    delta = Benchmark_delta();
    /* calculate testCase Ticks */
    testCaseTicks = Benchmark_calculate(testCase);
    /* return actual ticks */
    return testCaseTicks - delta;
}
/**
 * @brief used for calculate testCase performance, run multiple time
 * 
 * @param testCase function that we want run calculate performance
 * @param times time spend for each run test
 * @param n number of times to run 
 * @return Benchmark_Ticks return average ticks of all runs
 */
Benchmark_Ticks Benchmark_runMulti(Benchmark_TestCaseFn testCase, Benchmark_Ticks* times, uint8_t n) {
    Benchmark_Ticks delta;
    Benchmark_Ticks testCaseTicks = 0;
    uint8_t i;
    /* calculate delta */
    delta = Benchmark_delta();
    /* calculate testCase Ticks */
    for (i = 0; i < n; i++) {
        times[i] = Benchmark_calculate(testCase) - delta;
        testCaseTicks += times[i];
    }
    /* calculate average ticks */
    testCaseTicks /= n;
    /* return actual ticks */
    return testCaseTicks;
}

/**
 * @brief this function calculate minimum ticks required for empty function and used for calculate
 * more accurate performance
 * @return Benchmark_Ticks return ticks spend on empty function
 */
Benchmark_Ticks Benchmark_delta(void) {
    return Benchmark_calculate(Benchmark_empty);
}

static Benchmark_Ticks Benchmark_calculate(Benchmark_TestCaseFn testCase) {
    /* check which mode must be use for this driver */
    if (benchmarkDriver->startTimer && benchmarkDriver->stopTimer) {
        /* calculate */
        benchmarkDriver->startTimer();
        testCase();
        benchmarkDriver->stopTimer();
        /* return delta */
        return benchmarkDriver->currentTicks();
    }
    else {
        Benchmark_Ticks startTime;
        Benchmark_Ticks stopTime;
        /* calculate delta */
        startTime = benchmarkDriver->currentTicks();
        testCase();
        stopTime = benchmarkDriver->currentTicks();
        /* return delta */
        return stopTime - startTime;
    }
}
static void Benchmark_empty(void) {
    /* Nothing to do */
}