#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "[ERROR] to many or not enought args provided ! (%i)\n", argc);
		exit(1);
	}

	uint64_t iter = atoi(argv[1]);

	printf("%" PRIu64 "\n", iter);

	uint64_t multiple_of_three = 3;
	uint64_t multiple_of_five = 5;

	for (uint64_t i = 1; i <= iter; ++i)
	{
		if (i != multiple_of_three && i != multiple_of_five)
			printf("%" PRIu64, i);
		else
		{
			if (i == multiple_of_three)
			{
				printf("fizz");
				multiple_of_three += 3;
			}
			if (i == multiple_of_five)
			{
				printf("buzz");
				multiple_of_five += 5;
			}
		}

		printf("\n");
	}

	return 0;
}