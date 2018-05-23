#include "env.h"
#include <stdlib.h>
#include <string.h>


env_t *empty_env() {
  env_t *ret = malloc(sizeof(env_t));
  ret->entries = NULL;
  return ret;
}

static void free_entry(entry_t *entry) {
  if (entry) {
    free_entry(entry->next);
    free(entry);
  }
}

void free_env(env_t *env) {
  free_entry(env->entries);
  free(env);
}

int read_env(const env_t *env, const char *id) {
  const entry_t *cur = env->entries;
  while (cur) {
    if (strcmp(cur->id, id) == 0) {
      return cur->val;
    }
    cur = cur->next;
  }
  return 0;
}

void write_env(env_t *env, const char *id, int val) {
  entry_t *cur = env->entries;
  while (cur) {
    if (strcmp(cur->id, id) == 0) {
      cur->val = val;
      return;
    }
    cur = cur->next;
  }

  entry_t *entry = malloc(sizeof(entry_t));
  entry->next = env->entries;
  entry->id = id;
  entry->val = val;

  env->entries = entry;

  return;
}

void print_env(const env_t *env) {
  const entry_t *cur = env->entries;
  while (cur) {
    printf("%s := %d\n", cur->id, cur->val);
    cur = cur->next;
  }
}
