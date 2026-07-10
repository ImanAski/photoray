#include <stdio.h>
#include "phoray.h"


int main() {
  if (parse_scene("tests/example.phoray")) {
    puts("Parse OK");
  } else {
    puts("Parse FAILED");
  }

  return 0;
}
