#include <stdio.h>
#include "clap.h"

int main(int argc, char **argv) {
  clap_parser parser = clap_parser_init(argc, argv, (clap_parser_opts) {
      .desc = "An example program to demonstrate some features of the library"
    });
  
  clap_arg_add(&parser, (clap_arg) {b
      .description = "In file path",
      .options = CLAP_ARG_UNNAMED,
    });

  clap_arg_add(&parser, (clap_arg) {
      .description = "Out file path",
      .options = CLAP_ARG_UNNAMED | CLAP_ARG_OPTIONAL,
    });

  clap_arg_add(&parser, (clap_arg) {
      .name = "lex",
      .alias = 'l',
      .description = "Whether to lex the file",
      .default_value = CLAP_FLAG_FALSE,
      .options = CLAP_ARG_FLAG | CLAP_ARG_OPTIONAL
    });

  clap_arg_add(&parser, (clap_arg) {
      .name = "parse",
      .alias = 'p',
      .description = "Whether to parse the file",
      .default_value = CLAP_FLAG_FALSE,
      .options = CLAP_ARG_FLAG | CLAP_ARG_OPTIONAL
    });

  clap_arg_add(&parser, (clap_arg) {
      .name = "compile",
      .alias = 'c',
      .description = "Whether to compile the file",
      .default_value = CLAP_FLAG_FALSE,
      .options = CLAP_ARG_FLAG | CLAP_ARG_OPTIONAL
    });
  

  if(!clap_parse(&parser)) {
    clap_print_err(parser);
    clap_destroy(&parser);
    return -1;
  }

  const char *inf = clap_get_unnamed(parser, 0);
  const char *outf = clap_get_unnamed(parser, 1);
  if (!outf) { outf = "STD_OUT"; }
  const char *lex = clap_get(parser, "lex");
  const char *parse = clap_get(parser, "parse");
  const char *compile = clap_get(parser, "compile");

  printf("Reading from:  %s\n",  inf);
  printf("Outputting to: %s\n", outf);
  if (lex) {
    printf("Lexing...\n");
  }
  if (parse) {
    printf("Parsing...\n");
  }
  if (compile) {
    printf("Compiling...\n");
  }
  printf("Done\n");
  
  clap_destroy(&parser);
}
