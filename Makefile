headers = include/ponystats.h
plugins := $(patsubst %.c,%.so,$(wildcard plugins/*.c))
targets = lol src/ponystats.o $(plugins)

CFLAGS = -Iinclude -Wall -std=gnu99 -fPIC -g -ggdb

all: $(targets)
clean:
	rm -f $(targets) *.o */*.o *.so */*.so

plugins/%.so: plugins/%.c
	gcc -shared $(CFLAGS) $< src/ponystats.o -o $@


lol: $(headers) lol.c src/ponystats.o
	gcc $(CFLAGS) -ldl lol.c  src/ponystats.o -o lol

src/ponystats.o: $(headers) src/ponystats.c
	gcc $(CFLAGS) -shared -c src/ponystats.c -o src/ponystats.o
