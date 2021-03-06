#include "ast.h"
#include "interp.h"
#include "parser.tab.h"
#include <stdio.h>

int main() {
  const command_t *cmd;
  if (yyparse(&cmd)) {
    fprintf(stderr, "Some error occurred while parsing\n");
  } else {
    env_t *env = empty_env();
    interpret(env, cmd);
    print_env(env);
    free_env(env);
  }
}
