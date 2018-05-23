#include "ast.h"
#include "pretty.h"
#include <stdarg.h>

static void format(pretty_printer_t *p, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  p->col += vfprintf(p->f, fmt, args);
  va_end(args);
}

static void format_newline(pretty_printer_t *p) {
  int dest = 2*p->indent;
  if (p->col > dest) {
    format(p, "\n");
    p->col = 0;
  }
  if (p->col < dest) {
    format(p, "%*s", dest - p->col, "");
  }
}

static void command(pretty_printer_t *p, const command_t *cmd) {
  switch (cmd->kind) {
    case SKIP:
      break;
    case ASSIGN:
      format_newline(p);
      format(p, "%s := ", cmd->assign.id);
      pretty_print_expression_t(p, cmd->assign.rhs);
      break;
    case SEQUENCE:
      command(p, cmd->sequence.cmd1);
      command(p, cmd->sequence.cmd2);
      break;
    case IF:
      format_newline(p);
      format(p, "if ");
      pretty_print_expression_t(p, cmd->if_.cond);
      format(p, " {");

      p->indent++;
      command(p, cmd->if_.then);
      p->indent--;

      format_newline(p);
      format(p, "} else {");

      p->indent++;
      command(p, cmd->if_.else_);
      p->indent--;

      format_newline(p);
      format(p, "}");
      break;
    case WHILE:
      format_newline(p);
      format(p, "while ");
      pretty_print_expression_t(p, cmd->if_.cond);
      format(p, " {");

      p->indent++;
      command(p, cmd->if_.then);
      p->indent--;

      format_newline(p);
      format(p, "}");
      break;
  }
}

void pretty_print_command_t(pretty_printer_t *p, const command_t *cmd) {
  command(p, cmd);
  format_newline(p);
}

static const char *binop(binop_t op) {
  switch (op) {
    case ADD: return "+";
    case SUB: return "-";
    case MUL: return "*";
    case AND: return "&&";
    case EQ:  return "=";
    case LEQ: return "<=";
  }
}

void pretty_print_expression_t(pretty_printer_t *p, const expression_t *expr) {
  /* Sorry for parentheses */
  switch (expr->kind) {
    case UNOP:
      format(p, "!(");
      pretty_print_expression_t(p, expr->unop.child);
      format(p, ")");
      break;
    case BINOP:
      format(p, "(");
      pretty_print_expression_t(p, expr->binop.children[0]);
      format(p, " %s ", binop(expr->binop.op));
      pretty_print_expression_t(p, expr->binop.children[1]);
      format(p, ")");
      break;
    case LITERAL:
      format(p, "%d", expr->lit);
      break;
    case ID:
      format(p, "%s", expr->id);
      break;
  }
}
