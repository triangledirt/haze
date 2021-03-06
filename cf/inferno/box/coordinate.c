#include "cf/inferno/box/coordinate.h"
#include "cf/x/core/standard.h"

void cf_inferno_box_coordinate_copy(cf_inferno_box_coordinate_t *destination,
    cf_inferno_box_coordinate_t *source)
{
  assert(destination);
  assert(source);

  destination->x = source->x;
  destination->y = source->y;
  destination->z = source->z;
}

void cf_inferno_box_coordinate_free(cf_inferno_box_coordinate_t *coordinate) {}

void cf_inferno_box_coordinate_init_with_coordinate(cf_inferno_box_coordinate_t *coordinate,
    cf_inferno_box_coordinate_t *initial_coordinate)
{
  assert(coordinate);

  coordinate->x = initial_coordinate->x;
  coordinate->y = initial_coordinate->y;
  coordinate->z = initial_coordinate->z;
}

void cf_inferno_box_coordinate_init_with_random(cf_inferno_box_coordinate_t *coordinate,
    cf_inferno_box_coordinate_t *dimension_coordinate)
{
  assert(coordinate);
  assert(dimension_coordinate);

  coordinate->x = random() % dimension_coordinate->x;
  coordinate->y = random() % dimension_coordinate->y;
  coordinate->z = random() % dimension_coordinate->z;
}

void cf_inferno_box_coordinate_init_with_xyz(cf_inferno_box_coordinate_t *coordinate,
    unsigned short x, unsigned short y, unsigned short z)
{
  assert(coordinate);

  coordinate->x = x;
  coordinate->y = y;
  coordinate->z = z;
}
