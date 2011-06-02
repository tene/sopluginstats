#include "ponystats.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/vfs.h>

fact_list_t *read_df () {
    fact_list_t *l = new_fact_list();
    FILE *mounts = fopen("/etc/mtab", "r");
    char buf[512];
    struct statfs fsbuf;
    memset(buf,0,sizeof(buf));
    while (fgets(buf, sizeof(buf), mounts)) {
        char *source = strtok(buf, " ");
        char *path = strtok(NULL, " ");
        char sizebuf[64];
        statfs(path, &fsbuf);
        fsblkcnt_t free_blocks = fsbuf.f_bfree;
        snprintf(sizebuf, sizeof(sizebuf), "%lu", free_blocks);
        fact_list_append(l,path,sizebuf);
    }
    fclose(mounts);
    return l;
}

fact_meta_list_t *read_meta() {
    fact_meta_list_t *l = new_fact_meta_list();
    fact_meta_list_append(l,"disk-usage","Disk Free Blocks",&read_df);
    return(l);
}


