CC=g++
CCFLAGS='-g' # debug symbols
# assign ARCHIVE to archives/final-`date -I`.tar.gz; doing it this way evaluates immediately instead of lazily
ARCHIVE!= printf 'archives/extra-all-%s.tar.gz' `date -I`

all: 2/ex2 3/ex3 4/ex4

2/ex2:
	make -C 2 ex2

3/ex3:
	make -C 3 ex3

4/ex4:
	make -C 4 ex4

archives:
	mkdir archives

# this is a phony in case you've updated programs and want to update the archive
$(ARCHIVE): archives
	tar -cvzf $(ARCHIVE) makefile README 2 3 4 
 
# prevents these from not running if a file with their name exists
# ex try running `touch clean && make clean`, it will still work
# without, above command would say "target up to date", even though it's not what you want
.PHONY: clean clobber backup over all tasks $(ARCHIVE)

# in case anyone wants this to be on multiple lines (for stylistic reasons):
# don't. it breaks make.
clean:
	for dir in 2 3 4; do make -C $$dir clean; done

clobber: clean
	for dir in 2 3 4; do make -C $$dir clobber; done
	rm -rf archives

backup: $(ARCHIVE)
 
over: clean all

# '@' means don't echo command when it's executed
tasks:
	@echo all backup clean over
