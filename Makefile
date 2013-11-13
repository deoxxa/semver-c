CFLAGS += -Wall -Werror -pedantic

all: prepare bin/semver-dump bin/semver-sort bin/semver-range

prepare:
	mkdir obj
	mkdir bin

obj/private.o: src/private.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c src/private.c -o obj/private.o

obj/component.o: src/component.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c src/component.c -o obj/component.o

obj/spec.o: src/spec.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c src/spec.c -o obj/spec.o

obj/range.o: src/range.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c src/range.c -o obj/range.o

obj/semver-dump.o: src/semver-dump.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c src/semver-dump.c -o obj/semver-dump.o

obj/semver-sort.o: src/semver-sort.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c src/semver-sort.c -o obj/semver-sort.o

obj/semver-range.o: src/semver-range.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c src/semver-range.c -o obj/semver-range.o

bin/semver-dump: obj/semver-dump.o obj/private.o obj/spec.o obj/component.o
	$(CC) $(CFLAGS) -o bin/semver-dump obj/semver-dump.o obj/private.o obj/spec.o obj/component.o

bin/semver-sort: obj/semver-sort.o obj/private.o obj/spec.o obj/component.o
	$(CC) $(CFLAGS) -o bin/semver-sort obj/semver-sort.o obj/private.o obj/spec.o obj/component.o

bin/semver-range: obj/semver-range.o obj/private.o obj/spec.o obj/component.o obj/range.o
	$(CC) $(CFLAGS) -o bin/semver-range obj/semver-range.o obj/private.o obj/spec.o obj/component.o obj/range.o

clean:
	rm -rf bin obj
