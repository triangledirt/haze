#include <stdlib.h>
#include <time.h>
#include "sy_random.h"

void sy_start() {
  srandom(time(NULL));
  sy_random_start();
}
