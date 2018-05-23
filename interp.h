#ifndef INTERP_H
#define INTERP_H

#include "ast.h"
#include "env.h"

int eval(env_t *env, const expression_t *expr);
void interpret(env_t *env, const command_t *cmd);

#endif
