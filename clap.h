#ifndef CLAP_H_
#define CLAP_H_

#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define _stringify(a) #a
#define stringify(a) _stringify(a)

typedef struct {
  size_t argc;
  char **argv;
  size_t offset;
} clap_t;

typedef enum {
  CLAP_RESULT_OK,
  CLAP_RESULT_FAILED_CONVERSION,
  CLAP_RESULT_END_OF_ARGUMENTS,
  CLAP_RESULT_COUNT,
  CLAP_RESULT_FLAG_NOT_FOUND,
  CLAP_RESULT_FLAG_NO_VALUE,
} clap_result_t;

clap_t clap_new(size_t, char **);

clap_result_t clap_chop(clap_t *);

clap_result_t clap_chop_string(clap_t *, char **val);

clap_result_t clap_chop_int(clap_t *, int *val);

// TODO: IS THIS BETTER THAN -1 FOR NOT FOUND?
bool clap_find_index(clap_t *, const char *, size_t *);
clap_result_t clap_find_flag_value(clap_t *, const char *, char **);

#endif // CLAP_H_
#ifdef CLAP_IMPLEMENTATION

clap_t clap_new(size_t argc, char **argv) {
  return (clap_t){
      .argc = argc,
      .argv = argv,
      .offset = 0,
  };
}

clap_result_t clap_chop(clap_t *clap) {
  return ++(clap->offset) < clap->argc ? CLAP_RESULT_OK
                                       : CLAP_RESULT_END_OF_ARGUMENTS;
}

clap_result_t clap_chop_string(clap_t *clap, char **val) {
  if (clap->offset >= clap->argc) {
    return CLAP_RESULT_END_OF_ARGUMENTS;
    // assert(false && "OUT OF RANGE"); // FIXME: THIS IS BAD BEHAVIOUR PROBABLY
  }
  *val = clap->argv[clap->offset++];
  return CLAP_RESULT_OK;
}

// TODO: ADD ERROR CHECKING OF SOME SORT
clap_result_t clap_chop_int(clap_t *clap, int *val) {
  char *str;
  clap_result_t res;
  if ((res = clap_chop_string(clap, &str)) != CLAP_RESULT_OK) {
    return res;
  }
  char *endptr;
  int v = strtol(str, &endptr, 10);
  if (errno != 0) {
    clap->offset--;
    return CLAP_RESULT_FAILED_CONVERSION;
  } else if (*endptr != '\0') {
    clap->offset--;
    return CLAP_RESULT_FAILED_CONVERSION;
  }
  *val = v;
  return CLAP_RESULT_OK;
}

bool clap_find_index(clap_t *clap, const char *val, size_t *out_idx) {
  for (size_t i = 0; i < clap->argc; ++i) {
    if (strcmp(val, clap->argv[i]) == 0) {
      *out_idx = i;
      return true;
    }
  }
  return false;
}

clap_result_t clap_find_flag_value(clap_t *clap, const char *val, char **out_pair) {
    size_t idx = 0;
    if (!clap_find_index(clap, val, &idx)) {
        return CLAP_RESULT_FLAG_NOT_FOUND;
    }
    if (idx >= clap->argc - 1) {
        return CLAP_RESULT_FLAG_NO_VALUE;
    }
    *out_pair = clap->argv[idx + 1];

    return CLAP_RESULT_OK;
}

#endif // CLAP_IMPLEMENTATION
