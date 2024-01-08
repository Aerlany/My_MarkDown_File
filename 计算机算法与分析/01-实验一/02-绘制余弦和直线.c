#include <stdio.h>

#include <math.h>

void main()

{

  double y;

  int x, m, n, yy;

  for (yy = 0; yy <= 20; yy++)

  {

    y = 0.1 * yy;

    m = acos(1 - y) * 10;

    n = 45 * (y - 1) + 31;

    for (x = 0; x <= 62; x++) {

      if (x == m && x == n) {
        printf("+");
      }
      elseif(x == n) { printf("+"); }

      elseif(x == m || x == 62 - m) printf("*");

      else printf("");

      printf("\\n");
    }
  }
