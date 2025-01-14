# libboxmuller

For instructions on building, formatting, testing, etc, see [`README.dev.md`](README.dev.md).

## Libraries

- `boxmuller`: Normally distributed random number generation.

## `man` pages

- `boxmuller.3`

## Example

```c
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
```

## Acknowledgements

_This project was initialized using [Copier](https://pypi.org/project/copier)
and the [Copier template for C projects](https://github.com/jspaaks/copier-template-for-c-projects)._
