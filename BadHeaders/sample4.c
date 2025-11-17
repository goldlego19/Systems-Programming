//will header.h be included more than once? no if it has fileguards
//Note that multiple inclusions of standard headers like stdio.h
//will not be included more than once due to their own internal guards.
#include "header.h"
#include "header.h"
#include <stdio.h>
int main(void) {
	test();
	printf("Testing stdio.h");
	return 0;
}
