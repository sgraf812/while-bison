#include "interp.h"

void interpret(env_t *env, const command_t *cmd) {
  switch (cmd->kind) {
    case SKIP:
      return;
    case SEQUENCE:
      interpret(env, cmd->sequence.cmd1);
      interpret(env, cmd->sequence.cmd2);
      return;
    case ASSIGN:
      write_env(env, cmd->assign.id, eval(env, cmd->assign.rhs));
      return;
    case IF:
      if (eval(env, cmd->if_.cond)) {
	interpret(env, cmd->if_.then);
      } else {
	interpret(env, cmd->if_.else_);
      }
      return;
    case WHILE:
      while (eval(env, cmd->while_.cond)) {
	interpret(env, cmd->while_.body);
      }
      return;
  }
}

int eval(env_t *env, const expression_t *expr) {
  switch (expr->kind) {
    case LITERAL:
      return expr->lit;
    case ID:
      return read_env(env, expr->id);
    case UNOP:
      return !eval(env, expr->unop.child);
    case BINOP: {
      int l = eval(env, expr->binop.children[0]);
      int r = eval(env, expr->binop.children[1]);
      switch (expr->binop.op) {
	case ADD: return l + r;
	case SUB: return l - r;
	case MUL: return l * r;
	case AND: return l && r;
	case EQ:  return l == r;
	case LEQ: return l <= r;
      }
    }
  }
}
