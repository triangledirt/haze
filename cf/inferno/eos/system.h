#ifndef cf_inferno_eos_system_h
#define cf_inferno_eos_system_h

#include "cf/inferno/eos/tools.h"
#include "cf/inferno/search/isearch.h"
#include "cf/inferno/search/tools.h"

void *cf_inferno_eos_system_create(cf_inferno_core_score_solution_f score_solution,
    cf_inferno_core_goal_t goal, void *context,
    cf_x_case_array_t *initial_solutions, cf_x_core_log_t *log);

void cf_inferno_eos_system_destroy(void *system_object);

cf_inferno_box_system_t *cf_inferno_eos_system_get_box(cf_inferno_eos_system_t *system);

void *cf_inferno_eos_system_get_context(cf_inferno_eos_system_t *system);

cf_inferno_core_goal_t cf_inferno_eos_system_get_goal(cf_inferno_eos_system_t *system);

cf_x_core_log_t *cf_inferno_eos_system_get_log(cf_inferno_eos_system_t *system);

cf_inferno_core_score_solution_f cf_inferno_eos_system_get_score_solution
(cf_inferno_eos_system_t *system);

cf_x_case_array_t *cf_inferno_eos_system_get_solutions_copy(void *system_object,
    unsigned short max_solution_count);

void cf_inferno_eos_system_init_isearch(cf_inferno_search_isearch_t *isearch);

void cf_inferno_eos_system_search(void *system_object);

#endif
