#include <stdio.h>
#include <stdlib.h>

#include "jdvapi_basic.h"
#include "jdvapi_keyb.h"
#include "jdvapi_sync.h"

/**
 * JDVA#6 ON FAIT BOUGER UN POULPE
 */


void main(void)
{
	mode(1);
	printf("Hello World !");
	put_pixel1(20,20,2);
	while(1){}
}



