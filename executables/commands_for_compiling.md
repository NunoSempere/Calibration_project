If you have the .c (source code) and .h (headers) files, you can compile them, in Linux, using gcc / mingw
- gcc -g main.c datatypes.c datatypes.h extract_data.c extract_data.h analyze_data.c analyze_data.h print_data.c print_data.h constants.h -o main -lm : to produce a Linux main file.
- x86_64-w64-mingw32-gcc -g main.c datatypes.c datatypes.h extract_data.c extract_data.h analyze_data.c analyze_data.h print_data.c print_data.h constants.h -o calibration-windows-64-bit.exe -lm: Windows 32 bit.
- i686-w64-mingw32-gcc -g main.c datatypes.c datatypes.h extract_data.c extract_data.h analyze_data.c analyze_data.h print_data.c print_data.h constants.h -o calibration-windows-32-bit.exe -lm: Windows 64 bit.
