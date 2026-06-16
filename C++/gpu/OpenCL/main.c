// main.c
#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1024

const char* kernelSource =
"__kernel void vec_add(__global const float* A, __global const float* B, __global float* C) {"
"    int i = get_global_id(0);"
"    C[i] = A[i] + B[i];"
"}";

int main() {
    float *A = (float*)malloc(sizeof(float) * SIZE);
    float *B = (float*)malloc(sizeof(float) * SIZE);
    float *C = (float*)malloc(sizeof(float) * SIZE);

    for (int i = 0; i < SIZE; i++) {
        A[i] = i;
        B[i] = i * 2;
    }

    cl_int err;

    // 1. Get platform
    cl_platform_id platform;
   err = clGetPlatformIDs(1, &platform, NULL);
   if (err != CL_SUCCESS) {
    	printf("No OpenCL platform found\n");
    	return 1;
   }

    // 2. Get device
    cl_device_id device;
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, NULL);
    if (err != CL_SUCCESS) {
    	printf("No OpenCL device found (GPU/CPU)\n");
    	return 1;
    }

    // 3. Create context
    cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);

    // 4. Create command queue
    cl_command_queue queue = clCreateCommandQueue(context, device, 0, NULL);

    // 5. Create buffers
    cl_mem bufA = clCreateBuffer(context, CL_MEM_READ_ONLY, SIZE*sizeof(float), NULL, NULL);
    cl_mem bufB = clCreateBuffer(context, CL_MEM_READ_ONLY, SIZE*sizeof(float), NULL, NULL);
    cl_mem bufC = clCreateBuffer(context, CL_MEM_WRITE_ONLY, SIZE*sizeof(float), NULL, NULL);

    clEnqueueWriteBuffer(queue, bufA, CL_TRUE, 0, SIZE*sizeof(float), A, 0, NULL, NULL);
    clEnqueueWriteBuffer(queue, bufB, CL_TRUE, 0, SIZE*sizeof(float), B, 0, NULL, NULL);

    // 6. Build program
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSource, NULL, NULL);
    clBuildProgram(program, 1, &device, NULL, NULL, NULL);

    // 7. Create kernel
    cl_kernel kernel = clCreateKernel(program, "vec_add", NULL);

    // 8. Set arguments
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &bufA);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &bufB);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &bufC);

    // 9. Execute kernel
    size_t globalSize = SIZE;
    clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);

    // 10. Read result
    clEnqueueReadBuffer(queue, bufC, CL_TRUE, 0, SIZE*sizeof(float), C, 0, NULL, NULL);

    // Print a few results
    for (int i = 0; i < 10; i++) {
        printf("%f + %f = %f\n", A[i], B[i], C[i]);
    }

    // Cleanup
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseMemObject(bufA);
    clReleaseMemObject(bufB);
    clReleaseMemObject(bufC);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

    free(A);
    free(B);
    free(C);

    return 0;
}
