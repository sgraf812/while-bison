#ifndef ENV_H
#define ENV_H

#include <stdio.h>
#include "ast.h"

typedef struct entry_t {
  const char *id;
  int val;
  struct entry_t *next;
} entry_t;

typedef struct env_t {
  entry_t *entries;
} env_t;

env_t *empty_env();
void free_env(env_t *env);
int read_env(const env_t *env, const char *id);
void write_env(env_t *env, const char *id, int val);
void print_env(const env_t *env);


#endif
