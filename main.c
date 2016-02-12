#include <stdlib.h>
#include <stdio.h>
#include "./core/include/hardware.h"

#define CORE_STATUS 0x80
#define CORE_ID 0x126

void countByCore(){
    int i;
    printf("The current core is the number : %d\n", _in(CORE_ID));
    for(i=0;i<(1<<20);i++){}
    printf("The core %d is finish\n", _in(CORE_ID));
}

int main() {
    if(init_hardware("./core/etc/core.ini") == 0) {
        fprintf(stderr, "Error in core initialization\n");
	exit(EXIT_FAILURE);
    }

    IRQVECTOR[0] = countByCore;
    
    _out(CORE_STATUS,255);

    while(1){}

    return 1;
}
