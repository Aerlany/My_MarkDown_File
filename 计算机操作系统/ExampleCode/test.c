#include <stdio.h>

typedef struct tyname {
  int id;
  char *name;
} tyname;

int main() {

  char name[] = "as a child";
  tyname a = {1};
  a.name = name;
  printf("%d", a.id);
  printf("%s", a.name);
  return 0;
}
