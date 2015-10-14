#include "viewer.h"

#include <stdlib.h>

#include <unistd.h>

int main(void)
{
	parse();
	sleep(5);
	test_csfml();
	return (0);
}