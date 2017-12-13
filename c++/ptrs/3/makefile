CC=g++
CCFLAGS=-g -Wall -Wpedantic
# assign ARCHIVE to archives/final-`date -I`.tar.gz; doing it this way evaluates immediately
ARCHIVE!= printf 'archives/ex3-%s.tar.gz' `date -I`

$(ARCHIVE): archives
	tar -cvzf $(ARCHIVE) makefile ex3.cpp README

archives:
	mkdir archives

ex3: ex3.cpp
	$(CC) $(CCFLAGS) -o ex3 ex3.cpp

ex3.s: ex3.cpp
	$(CC) $(CCFLAGS) -S ex3.cpp

.PHONY: clean clobber backup assembly tasks

assembly: ex3.s

clean:
	rm -f ex3

clobber: clean
	rm -rf archives

backup: $(ARCHIVE)

tasks: assembly clean clobber backup ex3
