#ifndef AST_H
#define AST_H

typedef enum binop_t {
  EQ,
  LEQ,
  AND,
  ADD,
  SUB,
  MUL
} binop_t;

typedef enum unop_t {
  NOT
} unop_t;

typedef enum expression_kind_t {
  UNOP,
  BINOP,
  LITERAL,
  ID,
} expression_kind_t;

typedef struct expression_t {
  const expression_kind_t kind;
  const union {
    const char *id;
    int lit;
    struct {
      unop_t op;
      const struct expression_t *child;
    } unop;
    struct {
      binop_t op;
      const struct expression_t *children[2];
    } binop;
  };
} expression_t;

typedef enum command_kind_t {
  IF,
  WHILE,
  SEQUENCE,
  SKIP,
  ASSIGN
} command_kind_t;

typedef struct command_t {
  const command_kind_t kind;
  const union {
    struct {
      const expression_t *cond;
      const struct command_t *then;
      const struct command_t *else_;
    } if_;
    struct {
      const expression_t *cond;
      const struct command_t *body;
    } while_;
    struct {
      const struct command_t *cmd1;
      const struct command_t *cmd2;
    } sequence;
    struct {
      const char *id;
      const expression_t *rhs;
    } assign;
  };
} command_t;

const expression_t *new_literal(int i);
const expression_t *new_identifier(const char *id);
const expression_t *new_unop(unop_t op, const expression_t *child);
const expression_t *new_binop(binop_t op, const expression_t *l, const expression_t *r);

const command_t *new_if(const expression_t *cond, const command_t *then, const command_t *else_);
const command_t *new_while(const expression_t *cond, const command_t *body);
const command_t *new_sequence(const command_t *cmd1, const command_t *cmd2);
const command_t *new_skip();
const command_t *new_assignment(const char *id, const expression_t *rhs);

#endif
