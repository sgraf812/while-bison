#include "ast.h"
#include <stdlib.h>
#include <string.h>

inline const expression_t *new_expression_t(const expression_t expr) {
  expression_t *ret = malloc(sizeof(expression_t));
  memcpy(ret, &expr, sizeof(expression_t));
  return ret;
}

inline const command_t *new_command_t(command_t cmd) {
  command_t *ret = malloc(sizeof(command_t));
  memcpy(ret, &cmd, sizeof(command_t));
  return ret;
}

const expression_t *new_literal(int i) {
  return new_expression_t((expression_t) { .kind = LITERAL, { .lit = i } });
}

const expression_t *new_identifier(const char *id) {
  return new_expression_t((expression_t) { ID, { .id = id } });
}

const expression_t *new_unop(unop_t op, const expression_t *child){
  return new_expression_t((expression_t) { UNOP, { .unop = { op, child } } });
}

const expression_t *new_binop(binop_t op, const expression_t *l, const expression_t *r){
  return new_expression_t ((expression_t) { BINOP, { .binop = { op, { l, r } } } });
}

const command_t *new_if(const expression_t *cond, const command_t *then, const command_t *else_){
  return new_command_t((command_t) { IF, { .if_ = { cond, then, else_ } } });
}

const command_t *new_while(const expression_t *cond, const command_t *body){
  return new_command_t((command_t) { WHILE, { .while_ = { cond, body } } });
}

const command_t *new_sequence(const command_t *cmd1, const command_t *cmd2){
  return new_command_t((command_t) { SEQUENCE, { .sequence = { cmd1, cmd2 } } });
}

const command_t *new_skip() {
  const static command_t skip = { SKIP };
  return &skip;
}

const command_t *new_assignment(const char *id, const expression_t *rhs){
  return new_command_t ((command_t) { ASSIGN, { .assign = { id, rhs } } });
}

