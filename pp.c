#include "ast.h"
#include "pretty.h"
#include "parser.tab.h"
#include <stdio.h>

int main() {
  const command_t *cmd;
  if (yyparse(&cmd)) {
    fprintf(stderr, "Some error occurred while parsing\n");
  } else {
    pretty_printer_t pp = { stdout, 0, 0 };
    pretty_print_command_t(&pp, cmd);
  }
}
