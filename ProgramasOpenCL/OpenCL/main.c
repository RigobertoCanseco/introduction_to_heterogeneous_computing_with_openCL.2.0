///*/*
///*
//
//#include "timing.h"
//#include "cl-helper.h"
//
//
//
//
//int main(int argc, char **argv)
//{
//  if (argc != 3)
//  {
//    fprintf(stderr, "need two arguments!\n");
//    abort();
//  }
//
//  const cl_long n = atol(argv[1]);
//  const int ntrips = atoi(argv[2]);
//
//  cl_context ctx;
//  cl_command_queue queue;
//  create_context_on(CHOOSE_INTERACTIVELY, CHOOSE_INTERACTIVELY, 0, &ctx, &queue, 0);
//
//  print_device_info_from_queue(queue);
//
//  // --------------------------------------------------------------------------
//  // load kernels 
//  // --------------------------------------------------------------------------
//  char *knl_text = read_file("vec-add-soln.cl");
//  cl_kernel knl = kernel_from_string(ctx, knl_text, "sum", NULL);
//  free(knl_text);
//
//  // --------------------------------------------------------------------------
//  // allocate and initialize CPU memory
//  // --------------------------------------------------------------------------
//  float *a = (float *) malloc(sizeof(float) * n);
//  if (!a) { perror("alloc x"); abort(); }
//  float *b = (float *) malloc(sizeof(float) * n);
//  if (!b) { perror("alloc y"); abort(); }
//  float *c = (float *) malloc(sizeof(float) * n);
//  if (!c) { perror("alloc z"); abort(); }
//size_t i = 0;
//  for (i = 0; i < n; ++i)
//  {
//    a[i] = i;
//    b[i] = 2*i;
//  }
//
//  // --------------------------------------------------------------------------
//  // allocate device memory
//  // --------------------------------------------------------------------------
//  cl_int status;
//  cl_mem buf_a = clCreateBuffer(ctx, CL_MEM_READ_WRITE, 
//      sizeof(float) * n, 0, &status);
//  CHECK_CL_ERROR(status, "clCreateBuffer");
//
//  cl_mem buf_b = clCreateBuffer(ctx, CL_MEM_READ_WRITE,
//      sizeof(float) * n, 0, &status);
//  CHECK_CL_ERROR(status, "clCreateBuffer");
//
//  cl_mem buf_c = clCreateBuffer(ctx, CL_MEM_READ_WRITE,
//      sizeof(float) * n, 0, &status);
//  CHECK_CL_ERROR(status, "clCreateBuffer");
//
//  // --------------------------------------------------------------------------
//  // transfer to device
//  // --------------------------------------------------------------------------
//  CALL_CL_GUARDED(clEnqueueWriteBuffer, (
//        queue, buf_a, /*blocking*/ CL_TRUE, /*offset*/ 0,
//        n * sizeof(float), a,
//        0, NULL, NULL));
//
//  CALL_CL_GUARDED(clEnqueueWriteBuffer, (
//        queue, buf_b, /*blocking*/ CL_TRUE, /*offset*/ 0,
//        n * sizeof(float), b,
//        0, NULL, NULL));
//
//  // --------------------------------------------------------------------------
//  // run code on device
//  // --------------------------------------------------------------------------
//
//  CALL_CL_GUARDED(clFinish, (queue));
//
//  timestamp_type time1, time2;
//  get_timestamp(&time1);
//int trip = 0;
//  for (trip = 0; trip < ntrips; ++trip)
//  {
//    SET_4_KERNEL_ARGS(knl, buf_a, buf_b, buf_c, n);
//    size_t ldim[] = { 32 };
//    size_t gdim[] = { ((n + ldim[0] - 1)/ldim[0])*ldim[0] };
//    CALL_CL_GUARDED(clEnqueueNDRangeKernel,
//        (queue, knl,
//         /*dimensions*/ 1, NULL, gdim, ldim,
//         0, NULL, NULL));
//  }
//
//  CALL_CL_GUARDED(clFinish, (queue));
//
//  get_timestamp(&time2);
//  double elapsed = timestamp_diff_in_seconds(time1,time2)/ntrips;
//  printf("%f s\n", elapsed);
//  printf("%f GB/s\n",
//      3*n*sizeof(float)/1e9/elapsed);
//
//  // --------------------------------------------------------------------------
//  // transfer back & check
//  // --------------------------------------------------------------------------
//  CALL_CL_GUARDED(clEnqueueReadBuffer, (
//        queue, buf_c, /*blocking*/ CL_TRUE, /*offset*/ 0,
//        n * sizeof(float), c,
//        0, NULL, NULL));
//   size_t j = 0;
//  for (j = 0; j < n; ++j)
//    if (c[j] != 3*j)
//    {
//      printf("BAD %ld %f %f!\n", j, c[j], c[j] - 3*j);
//      abort();
//    }
//  puts("GOOD");
//
//  // --------------------------------------------------------------------------
//  // clean up
//  // --------------------------------------------------------------------------
//  CALL_CL_GUARDED(clReleaseMemObject, (buf_a));
//  CALL_CL_GUARDED(clReleaseMemObject, (buf_b));
//  CALL_CL_GUARDED(clReleaseMemObject, (buf_c));
//  CALL_CL_GUARDED(clReleaseKernel, (knl));
//  CALL_CL_GUARDED(clReleaseCommandQueue, (queue));
//  CALL_CL_GUARDED(clReleaseContext, (ctx));
//
//  return 0;
//}
//*/*/*/


    #include <stdio.h>
    #include <stdlib.h>
     
    #ifdef __APPLE__
    #include <OpenCL/opencl.h>
    #else
    #include <CL/cl.h>
    #endif
     
    #define MEM_SIZE (128)
    #define MAX_SOURCE_SIZE (0x100000)
     
    int main()
    {
    cl_device_id device_id = NULL;
    cl_context context = NULL;
    cl_command_queue command_queue = NULL;
    cl_mem memobj = NULL;
    cl_program program = NULL;
    cl_kernel kernel = NULL;
    cl_platform_id platform_id = NULL;
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret;
     
    char string[MEM_SIZE];
     
    FILE *fp;
    char fileName[] = "./hello.cl";
    char *source_str;
    size_t source_size;
     
    /* Load the source code containing the kernel*/
    fp = fopen(fileName, "r");
    if (!fp) {
    fprintf(stderr, "Failed to load kernel.\n");
    exit(1);
    }
    source_str = (char*)malloc(MAX_SOURCE_SIZE);
    source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
    fclose(fp);
     
    /* Get Platform and Device Info */
    ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
     
    /* Create OpenCL context */
    context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
     
    /* Create Command Queue */
    command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
     
    /* Create Memory Buffer */
    memobj = clCreateBuffer(context, CL_MEM_READ_WRITE,MEM_SIZE * sizeof(char), NULL, &ret);
     
    /* Create Kernel Program from the source */
    program = clCreateProgramWithSource(context, 1, (const char **)&source_str,
    (const size_t *)&source_size, &ret);
     
    /* Build Kernel Program */
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
     
    /* Create OpenCL Kernel */
    kernel = clCreateKernel(program, "hello", &ret);
     
    /* Set OpenCL Kernel Parameters */
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memobj);
     
    /* Execute OpenCL Kernel */
    ret = clEnqueueTask(command_queue, kernel, 0, NULL,NULL);
     
    /* Copy results from the memory buffer */
    ret = clEnqueueReadBuffer(command_queue, memobj, CL_TRUE, 0,
    MEM_SIZE * sizeof(char),string, 0, NULL, NULL);
     
    /* Display Result */
    puts(string);
     
    /* Finalization */
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(memobj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);
     
    free(source_str);
     
    return 0;
    }