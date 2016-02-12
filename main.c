#include <stdlib.h>
#include <stdio.h>
#include "./core/include/hardware.h"

void countByCore(){
    int i;
    printf("The current core is the number : %d\n", _in(0x126));
    for(i=0;i<(1<<20);i++){}
}

int main() {
    int tab_core;
    if(init_hardware("./core/etc/core.ini") == 0) {
        fprintf(stderr, "Error in core initialization\n");
	exit(EXIT_FAILURE);
    }
   
    _out(0x80,2 & 0xFF);
    tab_core = _in(0x80);
    printf("%d\n", tab_core);

    IRQVECTOR[0] = countByCore();

    return 1;
}
