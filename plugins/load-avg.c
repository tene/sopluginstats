#include "ponystats.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

fact_list_t *read_load () {
    fact_list_t *l = new_fact_list();
    int fd = open("/proc/loadavg", O_RDONLY);
    char buf[15];
    memset(buf,0,sizeof(buf));
    read(fd, buf, 14);
    fact_list_append(l,"1m",strtok(buf," "));
    fact_list_append(l,"5m",strtok(NULL," "));
    fact_list_append(l,"15m",strtok(NULL," "));
    return l;
}

fact_meta_list_t *read_meta() {
    fact_meta_list_t *l = new_fact_meta_list();
    fact_meta_list_append(l,"load","System Load Average",&read_load);
    return(l);
}


