#include <iostream>
#include <math.h>
#include <curand_kernel.h>
#include <stdio.h>

#define checkCudaErrors(val) check_cuda( (val), #val, __FILE__, __LINE__ )

void check_cuda(cudaError_t result, char const *const func, const char *const file, int const line) {
    if (result) {
        std::cerr << "CUDA error = " << static_cast<unsigned int>(result) << " at " <<
            file << ":" << line << " '" << func << "' \n";
        // Make sure we call CUDA Device Reset before exiting
        cudaDeviceReset();
        exit(99);
    }
}

__device__ int fact(int f)
{
  if (f == 0)
    return 1;
  else
    return f * fact(f - 1);
}

__global__
void execFunction(int f, int *val) {
	val[0] = fact(10);
}

int main(void)
{
	int f = 2;
	int *d_val;
	int *val = (int *)malloc(sizeof(int) * 10);
	checkCudaErrors(cudaMalloc((void**)&d_val, sizeof(int) * 10));
	execFunction<<<1, 1>>>(f, d_val);
	checkCudaErrors(cudaGetLastError());
	checkCudaErrors(cudaDeviceSynchronize());
	cudaMemcpy(val, d_val, sizeof(int) * 10, cudaMemcpyDeviceToHost);
	std::cout << *val;
}