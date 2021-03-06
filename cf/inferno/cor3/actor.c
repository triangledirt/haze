#include "cf/inferno/cor3/actor.h"
#include "cf/inferno/cor3/system.h"
#include "cf/inferno/core/constants.h"
#include "cf/inferno/core/goal.h"

#define ANARCHY_MODULUS 4

struct cf_inferno_cor3_actor_t {
  void *box_cell;
  unsigned char elements[4][4][4];
  cf_x_core_bitarray_t *solution;
  cf_inferno_cor3_system_t *system;
  double score;
  cf_x_core_bool_t score_is_valid;
};

static void dance(cf_inferno_cor3_actor_t *destination, cf_inferno_cor3_actor_t *source_a,
    cf_inferno_cor3_actor_t *source_b);

static cf_inferno_cor3_actor_t *find_best_nearby_excluding_me(cf_inferno_cor3_actor_t *actor);

static cf_inferno_cor3_actor_t *find_worst_nearby_including_me(cf_inferno_cor3_actor_t *actor);

static unsigned char get_element(cf_inferno_cor3_actor_t *actor, unsigned short x,
    unsigned short y, unsigned short z);

static double get_score(cf_inferno_cor3_actor_t *actor);

static unsigned short get_solution_index_from_element_coordinates
(unsigned short x, unsigned short y, unsigned short z);

static cf_x_core_bool_t in_range(unsigned short index, unsigned short cut,
    unsigned short direction);

static void set_element(cf_inferno_cor3_actor_t *actor, unsigned short x,
    unsigned short y, unsigned short z, unsigned char value);

void dance(cf_inferno_cor3_actor_t *destination, cf_inferno_cor3_actor_t *source_a,
    cf_inferno_cor3_actor_t *source_b)
{
  assert(destination);
  assert(source_a);
  assert(source_b);
  unsigned short cut_x;
  unsigned short cut_y;
  unsigned short cut_z;
  unsigned short direction_x;
  unsigned short direction_y;
  unsigned short direction_z;
  unsigned short x;
  unsigned short y;
  unsigned short z;
  unsigned char element;

  cut_x = random() % 5;
  cut_y = random() % 5;
  cut_z = random() % 5;

  direction_x = random() % 2;
  direction_y = random() % 2;
  direction_z = random() % 2;

  for (x = 0; x < 4; x++) {
    for (y = 0; y < 4; y++) {
      for (z = 0; z < 4; z++) {
        if (in_range(x, cut_x, direction_x)
            && in_range(y, cut_y, direction_y)
            && in_range(z, cut_z, direction_z)) {
          element = get_element(source_a, x, y, z);
        } else {
          element = get_element(source_b, x, y, z);
        }
        /*  TODO: make this a #define  */
        if (0 == (random() % 64)) {
          element = random() % 256;
        }
        set_element(destination, x, y, z, element);
      }
    }
  }
}

cf_inferno_cor3_actor_t *find_best_nearby_excluding_me(cf_inferno_cor3_actor_t *actor)
{
  assert(actor);
  cf_inferno_box_coordinate_t relative_coordinate;
  cf_inferno_cor3_actor_t *neighbor_actor;
  cf_inferno_cor3_actor_t *best_actor;
  double best_score;
  double neighbor_score;
  cf_inferno_core_goal_t goal;
  cf_inferno_box_system_t *box;

  best_score = 0.0;
  best_actor = NULL;

  goal = cf_inferno_cor3_system_get_goal(actor->system);
  box = cf_inferno_cor3_system_get_box(actor->system);

  for (relative_coordinate.x = 0;
       relative_coordinate.x < 3;
       relative_coordinate.x++) {
    for (relative_coordinate.y = 0;
         relative_coordinate.y < 3;
         relative_coordinate.y++) {
      for (relative_coordinate.z = 0;
           relative_coordinate.z < 3;
           relative_coordinate.z++) {
        if ((1 == relative_coordinate.x)
            && (1 == relative_coordinate.y)
            && (1 == relative_coordinate.z)) {
          continue;
        }
        neighbor_actor = cf_inferno_box_system_find_relative(box, actor,
            &relative_coordinate);
        neighbor_score = get_score(neighbor_actor);
        if (!best_actor) {
          best_actor = neighbor_actor;
          best_score = neighbor_score;
        } else {
          if (CF_INFERNO_CORE_GOAL_MAXIMIZE_SCORE == goal) {
            if (neighbor_score > best_score) {
              best_actor = neighbor_actor;
              best_score = neighbor_score;
            }
          } else {
            if (neighbor_score < best_score) {
              best_actor = neighbor_actor;
              best_score = neighbor_score;
            }
          }
        }
      }
    }
  }

  assert(best_actor);
  return best_actor;
}

cf_inferno_cor3_actor_t *find_worst_nearby_including_me(cf_inferno_cor3_actor_t *actor)
{
  assert(actor);
  cf_inferno_box_coordinate_t relative_coordinate;
  cf_inferno_cor3_actor_t *neighbor_actor;
  cf_inferno_cor3_actor_t *worst_actor;
  double worst_score;
  double neighbor_score;
  cf_inferno_core_goal_t goal;
  cf_inferno_box_system_t *box;

  worst_actor = NULL;
  worst_score = 0.0;

  goal = cf_inferno_cor3_system_get_goal(actor->system);
  box = cf_inferno_cor3_system_get_box(actor->system);

  for (relative_coordinate.x = 0;
       relative_coordinate.x < 3;
       relative_coordinate.x++) {
    for (relative_coordinate.y = 0;
         relative_coordinate.y < 3;
         relative_coordinate.y++) {
      for (relative_coordinate.z = 0;
           relative_coordinate.z < 3;
           relative_coordinate.z++) {
        neighbor_actor = cf_inferno_box_system_find_relative(box, actor,
            &relative_coordinate);
        neighbor_score = get_score(neighbor_actor);
        if (!worst_actor) {
          worst_actor = neighbor_actor;
          worst_score = neighbor_score;
        } else {
          if (CF_INFERNO_CORE_GOAL_MAXIMIZE_SCORE == goal) {
            if (neighbor_score < worst_score) {
              worst_actor = neighbor_actor;
              worst_score = neighbor_score;
            }
          } else {
            if (neighbor_score > worst_score) {
              worst_actor = neighbor_actor;
              worst_score = neighbor_score;
            }
          }
        }
      }
    }
  }

  assert(worst_actor);
  return worst_actor;
}

unsigned char get_element(cf_inferno_cor3_actor_t *actor, unsigned short x,
    unsigned short y, unsigned short z)
{
  assert(actor);
  assert(x <= 3);
  assert(y <= 3);
  assert(z <= 3);

  return actor->elements[x][y][z];
}

double get_score(cf_inferno_cor3_actor_t *actor)
{
  assert(actor);
  void *context;
  cf_inferno_core_score_solution_f score_solution;
  cf_x_core_log_t *log;

  if (!actor->score_is_valid) {
    context = cf_inferno_cor3_system_get_context(actor->system);
    score_solution = cf_inferno_cor3_system_get_score_solution(actor->system);
    if (score_solution(context, actor->solution, &actor->score)) {
      actor->score_is_valid = cf_x_core_bool_true;
    } else {
      log = cf_inferno_cor3_system_get_log(actor->system);
      cf_x_core_log_trace(log, "cor3", "score_solution");
    }
  }

  return actor->score;
}

unsigned short get_solution_index_from_element_coordinates(unsigned short x,
    unsigned short y, unsigned short z)
{
  return (x * 16) + (y * 4) + z;
}

void cf_inferno_cor3_actor_act(cf_inferno_cor3_actor_t *actor)
{
  assert(actor);
  cf_inferno_cor3_actor_t *best_other_actor;
  cf_inferno_cor3_actor_t *worst_actor;
  cf_inferno_box_system_t *box;

  box = cf_inferno_cor3_system_get_box(actor->system);

  best_other_actor = find_best_nearby_excluding_me(actor);
  cf_inferno_box_system_swap(box, actor, best_other_actor);

  worst_actor = find_worst_nearby_including_me(actor);
  if (0 == (random() % ANARCHY_MODULUS)) {
    dance(actor, best_other_actor, worst_actor);
  } else {
    dance(worst_actor, actor, best_other_actor);
  }

}

int cf_inferno_cor3_actor_compare_maximize(void *actor_a_void, void *actor_b_void)
{
  assert(actor_a_void);
  assert(actor_b_void);
  cf_inferno_cor3_actor_t **actor_a;
  cf_inferno_cor3_actor_t **actor_b;
  double actor_a_score;
  double actor_b_score;
  int compare_result;

  actor_a = (cf_inferno_cor3_actor_t **) actor_a_void;
  actor_b = (cf_inferno_cor3_actor_t **) actor_b_void;

  actor_a_score = get_score((cf_inferno_cor3_actor_t *) *actor_a);
  actor_b_score = get_score((cf_inferno_cor3_actor_t *) *actor_b);
  if (actor_a_score > actor_b_score) {
    compare_result = -1;
  } else if (actor_a_score < actor_b_score) {
    compare_result = 1;
  } else {
    compare_result = 0;
  }

  return compare_result;
}

int cf_inferno_cor3_actor_compare_minimize(void *actor_a_void, void *actor_b_void)
{
  assert(actor_a_void);
  assert(actor_b_void);
  cf_inferno_cor3_actor_t **actor_a;
  cf_inferno_cor3_actor_t **actor_b;
  double actor_a_score;
  double actor_b_score;
  int compare_result;

  actor_a = (cf_inferno_cor3_actor_t **) actor_a_void;
  actor_b = (cf_inferno_cor3_actor_t **) actor_b_void;

  actor_a_score = get_score((cf_inferno_cor3_actor_t *) *actor_a);
  actor_b_score = get_score((cf_inferno_cor3_actor_t *) *actor_b);
  if (actor_a_score < actor_b_score) {
    compare_result = -1;
  } else if (actor_a_score > actor_b_score) {
    compare_result = 1;
  } else {
    compare_result = 0;
  }

  return compare_result;
}

void *cf_inferno_cor3_actor_copy(void *actor_void)
{
  cf_x_core_trace_exit("TODO: implement");
  return NULL;
}

void *cf_inferno_cor3_actor_create(void *system_void, cf_x_core_bitarray_t *solution)
{
  assert(system_void);
  assert(solution);
  cf_inferno_cor3_actor_t *actor;
  unsigned short x;
  unsigned short y;
  unsigned short z;
  unsigned short i;
  cf_x_core_log_t *log;
  cf_inferno_cor3_system_t *system;

  system = system_void;

  log = cf_inferno_cor3_system_get_log(system);

  actor = malloc(sizeof *actor);
  if (actor) {
    actor->system = system;
    actor->score_is_valid = cf_x_core_bool_false;
    actor->box_cell = NULL;
    for (x = 0; x < 4; x++) {
      for (y = 0; y < 4; y++) {
        for (z = 0; z < 4; z++) {
          i = get_solution_index_from_element_coordinates(x, y, z);
          actor->elements[x][y][z] = cf_x_core_bitarray_get_bit(solution, i);
        }
      }
    }
    actor->solution = cf_x_core_bitarray_copy(solution);
    if (!actor->solution) {
      cf_x_core_log_trace(log, "cor3", "x_core_bitarray_copy");
      free(actor);
      actor = NULL;
    }
  } else {
    cf_x_core_log_trace(log, "cor3", "malloc");
  }

  return actor;
}

void *cf_inferno_cor3_actor_create_random(void *system_void)
{
  assert(system_void);
  cf_x_core_bitarray_t *bitarray;
  cf_inferno_cor3_actor_t *actor;
  cf_x_core_log_t *log;
  cf_inferno_cor3_system_t *system;

  system = system_void;

  bitarray = cf_x_core_bitarray_create_random(CF_INFERNO_CORE_SOLUTION_BIT_COUNT);
  if (bitarray) {
    actor = cf_inferno_cor3_actor_create(system, bitarray);
    if (!actor) {
      log = cf_inferno_cor3_system_get_log(system);
      cf_x_core_log_trace(log, "cor3", "inferno_cor3_actor_create");
    }
    cf_x_core_bitarray_destroy(bitarray);
  } else {
    actor = NULL;
    log = cf_inferno_cor3_system_get_log(system);
    cf_x_core_log_trace(log, "cor3", "x_core_bitarray_create_random");
  }

  return actor;
}

void cf_inferno_cor3_actor_destroy(void *actor_void)
{
  assert(actor_void);
  cf_inferno_cor3_actor_t *actor;

  actor = actor_void;

  cf_x_core_bitarray_destroy(actor->solution);
  free(actor);
}

void *cf_inferno_cor3_actor_get_box_cell(void *actor_void)
{
  assert(actor_void);
  cf_inferno_cor3_actor_t *actor;

  actor = actor_void;

  return actor->box_cell;
}

cf_x_core_bitarray_t *cf_inferno_cor3_actor_get_solution(void *actor_void)
{
  assert(actor_void);
  cf_inferno_cor3_actor_t *actor;

  actor = actor_void;

  return actor->solution;
}

void cf_inferno_cor3_actor_init_iactor(cf_inferno_core_iactor_t *iactor)
{
  cf_inferno_core_iactor_init(iactor, cf_inferno_cor3_actor_create,
      cf_inferno_cor3_actor_create_random, cf_inferno_cor3_actor_compare_minimize,
      cf_inferno_cor3_actor_copy, cf_inferno_cor3_actor_destroy, cf_inferno_cor3_actor_get_box_cell,
      cf_inferno_cor3_actor_set_box_cell);
}

void cf_inferno_cor3_actor_set_box_cell(void *actor_void, void *box_cell)
{
  assert(actor_void);
  cf_inferno_cor3_actor_t *actor;

  actor = actor_void;

  actor->box_cell = box_cell;
}

cf_x_core_bool_t in_range(unsigned short index, unsigned short cut,
    unsigned short direction)
{
  cf_x_core_bool_t in;

  if (direction) {
    if (index >= cut) {
      in = cf_x_core_bool_true;
    } else {
      in = cf_x_core_bool_false;
    }
  } else {
    if (index < cut) {
      in = cf_x_core_bool_true;
    } else {
      in = cf_x_core_bool_false;
    }
  }

  return in;
}

void set_element(cf_inferno_cor3_actor_t *actor, unsigned short x, unsigned short y,
    unsigned short z, unsigned char value)
{
  assert(actor);
  assert(x <= 3);
  assert(y <= 3);
  assert(z <= 3);
  unsigned short i;

  actor->elements[x][y][z] = value;

  i = get_solution_index_from_element_coordinates(x, y, z);
  cf_x_core_bitarray_set_bit(actor->solution, i, value);

  actor->score_is_valid = cf_x_core_bool_false;
}
