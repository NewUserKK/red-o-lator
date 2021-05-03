# red-o-lator

Emulator for GCN GPUs

## Configuration

### ICD-Loader

Project does not provide bundled OpenCL ICD loader so you should install it on your own.

Example of such loader is https://github.com/khronosgroup/opencl-icd-loader

Then you should create .icd file in /etc/OpenCL/vendors with path to driver library.

TODO: make it automated and cross-platform.

### CLion

#### clang-format

Project uses google-style clang-format.

To make use of it, you need to install ClangFormatIJ plugin and change format options to clang-format at the right
bottom corner.