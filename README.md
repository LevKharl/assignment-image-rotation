# Image Rotation Tool

A modular C-based utility for rotating BMP images by 90 degrees counter-clockwise. This project emphasizes clean architecture and format extensibility, initially targeting 24-bit BMP files.

## Task Overview

This tool transforms BMP images via command-line execution:

```bash
./image-transformer <source-image> <transformed-image>
```

The program is organized into well-isolated modules for maintainability and scalability.

### Architecture

🧩 Internal Format Module
Defines the core image structure:

struct image {
  uint64_t width, height;
  struct pixel* data;
};
Responsibilities include creation, deinitialization, and internal memory management. This module is unaware of file formats or transformations.

Format Modules (e.g., BMP)
Each format is handled in its own module, supporting both reading and writing using the struct image abstraction. For BMP, begin with:

enum read_status  {
  READ_OK = 0,
  READ_INVALID_SIGNATURE,
  READ_INVALID_BITS,
  READ_INVALID_HEADER
};

enum read_status from_bmp(FILE* in, struct image* img);

enum write_status  {
  WRITE_OK = 0,
  WRITE_ERROR
};

enum write_status to_bmp(FILE* out, struct image const* img);
These functions do not open/close files — that responsibility lies elsewhere, allowing greater flexibility and testability.
🔄 Transformation Modules
Each transformation is isolated in a standalone module. The core rotation function:

struct image rotate(struct image const source);
These modules only interact with the internal image format, independent of I/O handling.

🛠 Utility Modules
General-purpose helpers (file handling, string utilities, error messages) are grouped in utility modules (e.g., util.c). Their purpose is to simplify core module logic and error handling.

BMP Format Notes

The BMP header is defined using __attribute__((packed)) (GCC/Clang) or #pragma pack(push, 1) (MSVC).
Pixel format: Each pixel is 3 bytes (struct pixel { uint8_t b, g, r; };)
Padding: If a row isn’t a multiple of 4 bytes, it is padded with garbage bytes up to the nearest multiple of 4.
Building the Project

Ensure you have make >= 4.0 and clang installed.

🔧 Basic Build
make
Builds the binary at build/image-transformer.

🧪 Run Tests
make -k test
Or run an individual test:

make -k test-<test_name>
🧼 Clean
make clean
Removes build artifacts.

Static and Dynamic Analysis

✅ Static Checks
Run clang-tidy analysis with:

make check
Modify rules via clang-tidy-checks.txt or CLANG_TIDY_CHECKS=....

🧪 Sanitizers
Build with one of the following:

make SANITIZER=asan — AddressSanitizer
make SANITIZER=lsan — LeakSanitizer
make SANITIZER=msan — MemorySanitizer
make SANITIZER=usan — UndefinedBehaviorSanitizer
make SANITIZER=none — No sanitizers (default)
make SANITIZER=all — Build all sanitizer variants
Outputs are stored in build/<sanitizer-name>/.

Docker Support

A pre-configured Docker container can be used to replicate the CI test environment. It supports:

make check
make -k test SANITIZER=all
Style and Submission

Follow C coding style guidelines
Modularize thoughtfully to support additional formats and transformations.
Submit via pull request. See instructions for guidance.
