#include "boxmuller/boxmuller.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (void) {
    // initialize randomization:
    srand(time(nullptr));

    // generate 7 numbers drawn from a normal distribution with
    // mean 100 and standard deviation 2
    constexpr size_t n = 7;
    const double mu = 100.;
    const double sigma = 2.;
    for (size_t i = 0; i < n; i++) {
        fprintf(stdout, "%6.2f\n", mu + sigma * boxmuller_randn());
    }
}
