#ifndef PRETTY_H
#define PRETTY_H

#include <stdio.h>
#include "ast.h"

typedef struct pretty_printer_t {
  FILE *f;
  int indent;
  int col;
} pretty_printer_t;

void pretty_print_command_t(pretty_printer_t *p, const command_t *cmd);
void pretty_print_expression_t(pretty_printer_t *p, const expression_t *expr);

#endif
