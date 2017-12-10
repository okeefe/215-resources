CC=g++
CCFLAGS=-g -Wall -Wpedantic
# assign ARCHIVE to archives/final-`date -I`.tar.gz; doing it this way evaluates immediately
ARCHIVE!= printf 'archives/ex4-%s.tar.gz' `date -I`

$(ARCHIVE): archives
	tar -cvzf $(ARCHIVE) makefile README ex4.cpp

ex4: ex4.cpp
	$(CC) $(CCFLAGS) -o ex4 ex4.cpp

ex4.s: ex4.cpp
	$(CC) $(CCFLAGS) -S ex4.cpp

archives:
	mkdir archives

.PHONY: clean clobber backup assembly tasks

assembly: ex4.s

clean:
	rm -f ex4.s ex4

clobber: clean
	rm -rf archives

backup: $(ARCHIVE)

tasks: assembly clean clobber backup
