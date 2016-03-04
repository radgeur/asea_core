#include <stdlib.h>
#include <stdio.h>
#include "./core/include/hardware.h"

#define CORE_STATUS 0x80
#define CORE_ID 0x126
#define CORE_IRQMAPPER 0x82
#define CORE_NCORE 8
#define TIMER_IRQ 2
#define TIMER_ALARM 0xF8
#define TIMER_PARAM 0xF4
#define CORE_LOCK 0x98
#define CORE_UNLOCK 0x99

void countByCore(){
    int i;
    _mask(1);
    printf("\nThe current core is the number : %d\n", _in(CORE_ID));
    while(1){
	if(_in(CORE_LOCK) ==1){
	    printf("[%d", _in(CORE_ID));
	    for(i=0;i<(1<<20);i++);
	    printf("-%d]", _in(CORE_ID));
	    _out(CORE_UNLOCK,0xFFFF);
	    for(i=0;i<(1<<20);i++);
	}
    }
}

void handler(){
    printf("\nhello from core %d\n", _in(CORE_ID));
    _out(TIMER_ALARM, 0xFFFFFFFE);
}

int main() {
    int i;
    if(init_hardware("./core/etc/core.ini") == 0) {
        fprintf(stderr, "Error in core initialization\n");
	exit(EXIT_FAILURE);
    }

    /*call the functin to count and print the actual core*/
    IRQVECTOR[0] = countByCore;

    /*set the 8th core*/
    _out(CORE_STATUS,255);

    /*active IRQ for all the unpair core*/
    for(i=1;i<=CORE_NCORE;i++){
	if(i%2 != 0)
	    _out(CORE_IRQMAPPER + i, 1 << TIMER_IRQ);
    }

    /*active the IRQ_TIMER*/
    IRQVECTOR[TIMER_IRQ] = handler;
    _out(TIMER_PARAM,128+64+32+8); /* reset + alarm on + 8 tick / alarm */
    _out(TIMER_ALARM,0xFFFFFFFE);  /* alarm at next tick (at 0xFFFFFFFF) */

    while(1){}

    return 1;
}
