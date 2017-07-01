#include <omp.h>
#include <iostream>
#include <stdlib.h>

int main(){
	double result[99][100],time;
	#pragma openmp parallel for private(j) schedule(static) 
		for(int i=0 ;i < 99; i++){
			if(i==0) time=omp_get_wtime();
			for(int j=i+1; j< 100; j++){
				result[i][j]=0.0;
			}
		}
			std::cout<<(omp_get_wtime()-time)<<std::endl;

}
