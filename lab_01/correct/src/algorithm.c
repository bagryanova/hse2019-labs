#include <stdio.h>
#include "io.h"
#include "algorithm.h"
#include "util.h"

int doComputation(int a, float b) {
    int c = max(a, (int)b);
    logDebug('d');
    return c;
}
