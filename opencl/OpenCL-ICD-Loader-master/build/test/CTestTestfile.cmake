# CMake generated Testfile for 
# Source directory: /home/regoeco/Documentos/introduction_to_heterogeneous_computing_with_openCL.2.0/opencl/OpenCL-ICD-Loader-master/test
# Build directory: /home/regoeco/Documentos/introduction_to_heterogeneous_computing_with_openCL.2.0/opencl/OpenCL-ICD-Loader-master/build/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(OPENCL_ICD_LOADER_TEST "/home/regoeco/Documentos/introduction_to_heterogeneous_computing_with_openCL.2.0/opencl/OpenCL-ICD-Loader-master/build/bin/icd_loader_test")
subdirs(platform)
subdirs(driver_stub)
subdirs(loader_test)
