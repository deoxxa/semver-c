CFLAGS += -Wall -Werror -pedantic

all: prepare semver-dump semver-sort

prepare:
	mkdir -p ./obj

obj/private.o: src/private.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c src/private.c -o obj/private.o

obj/component.o: src/component.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c src/component.c -o obj/component.o

obj/spec.o: src/spec.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c src/spec.c -o obj/spec.o
obj/semver-dump.o: src/semver-dump.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c src/semver-dump.c -o obj/semver-dump.o

obj/semver-sort.o: src/semver-sort.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c src/semver-sort.c -o obj/semver-sort.o

semver-dump: obj/semver-dump.o obj/spec.o obj/component.o
	$(CC) $(CFLAGS) -o semver-dump obj/semver-dump.o obj/spec.o obj/component.o

semver-sort: obj/semver-sort.o obj/spec.o obj/component.o
	$(CC) $(CFLAGS) -o semver-sort obj/semver-sort.o obj/spec.o obj/component.o

clean:
	rm -rf semver-dump semver-sort obj
