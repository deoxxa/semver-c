CFLAGS += -Wall -Werror -I./include

all: prepare semver-dump

prepare:
	mkdir -p ./obj

obj/semver.o: src/semver.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c src/semver.c -o obj/semver.o

obj/semver-dump.o: src/semver-dump.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c src/semver-dump.c -o obj/semver-dump.o

semver-dump: obj/semver-dump.o obj/semver.o
	$(CC) $(CFLAGS) -o semver-dump obj/semver-dump.o obj/semver.o

clean:
	rm -rf semver-dump obj
