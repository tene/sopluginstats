#include "ponystats.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fact_list_dump(fact_list_t *l) {
    size_t count = l->count;
    for (int i = 0; i < count; i++) {
        fact_t item = l->items[i];
        printf("  %s => %s\n", item.key, item.val);
    }
}

void fact_meta_list_dump(fact_meta_list_t *l) {
    size_t count = l->count;
    for (int i = 0; i < count; i++) {
        fact_meta_t item = l->items[i];
        printf("name: %s\ndesc: %s\n", item.name, item.description);
        fact_list_t *il = item.read_facts();
        fact_list_dump(il);
        free_fact_list(il);
    }
}

fact_list_t *new_fact_list() {
    fact_list_t *l = malloc(sizeof(*l));
    memset(l, 0, sizeof(*l));
    return l;
}

void fact_list_append(fact_list_t *l, const char *key, const char *val) {
    l->count++;
    l->items = realloc(l->items, l->count * sizeof(*(l->items)));
    l->items[l->count-1].key = strdup(key);
    l->items[l->count-1].val = strdup(val);
}

fact_meta_list_t *new_fact_meta_list() {
    fact_meta_list_t *l = malloc(sizeof(*l));
    memset(l, 0, sizeof(*l));
    return l;
}

void fact_meta_list_append(fact_meta_list_t *l, const char *name, const char *description, read_fact_func_t rf) {
    l->count++;
    l->items = realloc(l->items, l->count * sizeof(*(l->items)));
    l->items[l->count-1].name = strdup(name);
    l->items[l->count-1].description = strdup(description);
    l->items[l->count-1].read_facts = rf;
}

void free_fact_list(fact_list_t *l) {
    for (int i = 0; i < l->count; i++) {
        free(l->items[i].key);
        free(l->items[i].val);
    }
    free(l->items);
    free(l);
}

void free_fact_meta_list(fact_meta_list_t *l) {
    for (int i = 0; i < l->count; i++) {
        free(l->items[i].name);
        free(l->items[i].description);
    }
    free(l->items);
    free(l);
}
