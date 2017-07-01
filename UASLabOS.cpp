#include <stdio.h>
#include <omp.h>
using namespace std;

#define NUM_OF_COLUMNS 6
#define NUM_OF_ROWS (3*(NUM_OF_COLUMNS - 1))

int whichThread[NUM_OF_ROWS][NUM_OF_COLUMNS];

void fillColumn(int j)
{
	int i;
	#pragma omp for
	for (i = 0; i < NUM_OF_ROWS; i++)
	whichThread[i][j] = omp_get_thread_num();
}
int main()
{
	int i, j;
	for (i = 0; i < NUM_OF_ROWS; i++)
	for (j = 0; j < NUM_OF_COLUMNS; j++)
	whichThread[i][j] = -1;

	#pragma omp parallel num_threads (NUM_OF_COLUMNS - 1)
	fillColumn(0);

	#pragma omp parallel for num_threads (NUM_OF_COLUMNS - 1)
	for (j = 1; j < NUM_OF_COLUMNS; j++)fillColumn(j);
	for (i = 0; i < NUM_OF_ROWS; i++)
	{
		for (j = 0; j < NUM_OF_COLUMNS; j++)
		printf(" %2d ", whichThread[i][j]);
		printf("\n");
}
return 0;
}
