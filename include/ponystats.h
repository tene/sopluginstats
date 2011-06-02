#include <stdlib.h>

typedef struct {
    char *key;
    char *val;
} fact_t;

typedef struct {
    size_t count;
    fact_t *items;
} fact_list_t;

typedef fact_list_t *(*read_fact_func_t)();

typedef struct {
    char *name;
    char *description;
    read_fact_func_t read_facts;
} fact_meta_t;

typedef struct {
    size_t count;
    fact_meta_t *items;
} fact_meta_list_t;

typedef fact_meta_list_t *(*read_meta_func_t)();

void fact_list_dump(fact_list_t *l);
void fact_meta_list_dump(fact_meta_list_t *l);

fact_list_t *new_fact_list();
void fact_list_append(fact_list_t *l, const char *key, const char *val);
void free_fact_list(fact_list_t *l);

fact_meta_list_t *new_fact_meta_list();
void fact_meta_list_append(fact_meta_list_t *l, const char *name, const char *desc, read_fact_func_t rf);
void free_fact_meta_list(fact_meta_list_t *l);
