#include <stdio.h>
#include "algorithm.h"
#include "io.h"
#include "util.h"

int doComputation(int a, float b) {
    int c = max(a, (int)b);
    logDebug('d');
    return c;
}

int main() {
    int a = doComputation(5, 7.0);
    int b = 5;
    int c = max(a, b);
    logDebug('!');
    printf("Hello\n");
}
