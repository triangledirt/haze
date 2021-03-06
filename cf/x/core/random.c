#include "cf/x/core/standard.h"
#include "cf/x/core/random.h"

#define CF_X_CORE_RANDOM_01_PARAM 7
#define CF_X_CORE_RANDOM_01_SEEDS 25

double cf_x_core_random_01()
{
  return random() / (RAND_MAX + 1.0);
}

double cf_x_core_random_gaussian(double mean, double stddev)
{
  double x1;
  double x2;
  double w;
  double y1;
  double y2;
  double y;

  do {
    x1 = (2.0 * cf_x_core_random_01()) - 1.0;
    x2 = (2.0 * cf_x_core_random_01()) - 1.0;
    w = (x1 * x1) + (x2 * x2);
  } while (w >= 1.0);

  w = sqrt((-2.0 * log(w)) / w);
  y1 = x1 * w;
  y2 = x2 * w;

  y = ((random() % 2) == 0) ? y1 : y2;

  return (stddev * y) + (1.0 * mean);
}

unsigned long cf_x_core_random_poisson(double mean)
{
  unsigned long k;
  double l;
  double p;

  k = 0;
  p = 1.0;
  l = exp(mean * -1.0);

  do {
    k++;
    p *= cf_x_core_random_01();
  } while (p >= l);

  return k - 1;
}

unsigned long cf_x_core_random_unsigned_long(unsigned long range)
{
  return random() % range;
}
