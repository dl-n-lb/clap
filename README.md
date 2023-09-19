# CLAP (C) Command Line Argument Processor
A lightweight argument processor for C in a header only format.
The full implementation is included by default, since most programs only parse arguments in main.

To use simply:
``` c
#include "clap.h"
```

If you want to exclude the implementation, you should define the macro:
``` c
#define CLAP_NO_IMPLEMENTATION
```

An example can be found in `clap_example.c` and `clap_example_two.c`. To run, simply compile with any standard C compiler, then run. For example:
``` shell
$ cc -o clap_example clap_example.c
$ ./clap_example --dimensions 1280x720 -f png
Outputting image with dimensions: 1280x720
And format: png

$ cc -o clap_example_two clap_example_two.c
$ ./clap_example_two file.txt -lpc
Reading from:  file.txt
Outputting to: STD_OUT
Lexing...
Parsing...
Compiling...
Done

$ ./clap_example_two file.txt -lpc out_file.txt
Reading from:  file.txt
Outputting to: out_file.txt
Lexing...
Parsing...
Compiling...
Done
```
