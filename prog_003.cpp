#include <stdio.h>
#include <omp.h>
using namespace std;

int d_main;
#pragma omp threadprivate(d_main)

int main()
{
    int maksCPU, maksThread;
    bool wParallel; //status wilayah parallel

    d_main = 2;
    maksCPU = omp_get_num_procs();
    maksThread = omp_get_max_threads();
    wParallel = omp_in_parallel();

    printf("Banyaknya CPU yang tersedia: %d\n", maksCPU);
    printf("Banyaknya thread yang tersedia: %d\n", maksThread);
    printf("Nilai pada wilayah parallel: %d\n", wParallel);

    if(!wParallel) printf("<< Dalam wilayah BUKAN PARALLEL >>\n");
    else
    printf("<< Ada dalam wilayah PARALLEL >>\n");

    //masuk ke wilayah parallel
    printf("\n Akan masuk ke wilayah parallel\n");

  #pragma omp parallel copyin(d_main)
    {
        wParallel = omp_in_parallel();
        printf("Nilai pada wilayah paralel : %d, banyaknya thread: %d\n", wParallel, omp_get_num_threads());
        printf("Nilai d_main dalam wilayah parallel, sebelum assign baru : %d\n", d_main);

        if(!wParallel) printf("<< Dalam wilayah BUKAN PARALLEL, thread: %d >>\n", omp_get_thread_num());
        else
        printf("<< Ada dalam wilayah PARALLEL thread: %d >>\n", omp_get_thread_num());

        d_main = 7;
        printf("Nilai d_main dalam wilayah parallel, sesudah assign baru : %d\n", d_main);
    }//akhir wilayah parallel

    printf("\nPosisi di luar wilayah(region) parallel\n");
    printf("Banyaknya thread yang tersedia: %d\n", omp_get_num_threads());
    printf("Nilai d_main: %d\n", d_main);
    return 0;
}
