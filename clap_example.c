#include <stdio.h>
#include "clap.h"

int main(int argc, char **argv) {
  clap_parser parser = clap_parser_init(argc, argv, (clap_parser_opts) {0});
  clap_arg_add(&parser, (clap_arg){
      .name = "dimensions",
      .alias = 'd',
      .description = "Dimensions of the image",
    });
  clap_arg_add(&parser, (clap_arg){
      .name = "format",
      .alias = 'f',
      .description = "Image format to output",
    });
  clap_arg_add(&parser, (clap_arg){
      .name = "invert",
      .alias = 'i',
      .description = "Whether or not to invert the image colours",
      .default_value = CLAP_FLAG_FALSE,
      .options = CLAP_ARG_FLAG | CLAP_ARG_OPTIONAL
    });

  if(!clap_parse(&parser)) {
    clap_print_err(parser);
    return -1;
  }

  const char *dims = clap_get(parser, "dimensions");
  const char *format = clap_get(parser, "format");
  const char *invert = clap_get(parser, "invert");

  printf("Outputting image with dimensions: %s\n", dims);
  printf("And format: %s\n", format);
  if (invert == CLAP_FLAG_TRUE) {
    printf("And inverting image\n");
  }
  
  clap_destroy(&parser);
}
