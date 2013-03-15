CFLAGS += -Wall -Werror -pedantic

all: prepare semver-dump semver-sort

prepare:
	mkdir -p ./obj

obj/semver.o: src/semver.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c src/semver.c -o obj/semver.o

obj/semver-dump.o: src/semver-dump.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c src/semver-dump.c -o obj/semver-dump.o

obj/semver-sort.o: src/semver-sort.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c src/semver-sort.c -o obj/semver-sort.o

semver-dump: obj/semver-dump.o obj/semver.o
	$(CC) $(CFLAGS) -o semver-dump obj/semver-dump.o obj/semver.o

semver-sort: obj/semver-sort.o obj/semver.o
	$(CC) $(CFLAGS) -o semver-sort obj/semver-sort.o obj/semver.o

clean:
	rm -rf semver-dump semver-sort obj
