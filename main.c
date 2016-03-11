#include <stdlib.h>
#include <stdio.h>
#include "./core/include/hardware.h"
#include "sem.h"

#define CORE_STATUS 0x80
#define CORE_ID 0x126
#define CORE_IRQMAPPER 0x82
#define CORE_NCORE 8
#define TIMER_IRQ 2
#define TIMER_ALARM 0xF8
#define TIMER_PARAM 0xF4
#define CORE_LOCK 0x98
#define CORE_UNLOCK 0x99

void producteur(void *arg);
void consommateur(void *arg);

void producteur(void *args) {
  int i = 1;
  while (i<1<<18) {
      printf("Le produit numéro %i a été confectionné par le coeur %i\n", i, _in(CORE_ID));
    printf("Le produit numéro %i est disponible par le coeur %i\n", i, _in(CORE_ID));
    i++;
  }
}

void consommateur(void *args) {
  int i = 1;
  while (i<1<<18) {
    printf("Le produit numéro %i a été pris sur le coeur %i\n", i, _in(CORE_ID));
    printf("Le produit numéro %i a été utilisé sur le coeur %i\n", i, _in(CORE_ID));
    i++;
  }
}

void countByCore(){
    _mask(1);
    /*int i;
    printf("\nThe current core is the number : %d\n", _in(CORE_ID));
    while(1){
	if(_in(CORE_LOCK) ==1){
	    printf("[%d", _in(CORE_ID));
	    for(i=0;i<(1<<20);i++);
	    printf("-%d]", _in(CORE_ID));
	    _out(CORE_UNLOCK,0xFFFF);
	    for(i=0;i<(1<<20);i++);
	}
	}*/
  while(1) {
    /*create the context for all the fonctions*/
    create_ctx(16384, producteur, NULL);
    create_ctx(16384, consommateur, NULL);

    /*start the schedule*/
    start_sched();
    printf("je suis revenu dans le main\n");
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


    /*call the function to count and print the actual core*/
    IRQVECTOR[0] = countByCore;
    
    /*set the 8th core*/
    _out(CORE_STATUS,255);
    
    /*active IRQ for all the unpair core*/
    for(i=1;i<=CORE_NCORE;i++){
	/*if(i%2 != 0)*/
	    _out(CORE_IRQMAPPER + i, 1 << TIMER_IRQ);
    }

    /*active the IRQ_TIMER*/
    IRQVECTOR[TIMER_IRQ] = handler;
    _out(TIMER_PARAM,128+64+32+8); /* reset + alarm on + 8 tick / alarm */
    _out(TIMER_ALARM,0xFFFFFFFE);  /* alarm at next tick (at 0xFFFFFFFF) */

    while(1){}

    return 1;
}
