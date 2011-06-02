#include "ponystats.h"
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <fnmatch.h>
#include <dlfcn.h>

int main(int argc, char **argv) {
    DIR *pd = opendir("./plugins/");
    struct dirent *item;
    while ((item = readdir(pd))) {
        if (fnmatch("*.so",item->d_name,0) == 0) {
            char filename[256];
            snprintf(filename, sizeof(filename), "./plugins/%s", item->d_name);
            printf("loading %s\n", filename);
            void *handle = dlopen(filename, RTLD_LAZY);
            read_meta_func_t rm = dlsym(handle, "read_meta");

            fact_meta_list_t *l = rm();
            fact_meta_list_dump(l);
            free_fact_meta_list(l);
            dlclose(handle);
        }
    }
    closedir(pd);
    return(0);
}
