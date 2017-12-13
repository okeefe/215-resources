CC = g++ -g -Wall -Wpedantic
JAVAC != which javac
# note: if using the (deprecated) gcj, these flags are invalid.
JAVACFLAGS = -g -Xlint:all -source 1.8 -target 1.8

TEST_ARCHIVE = testing/test.tar.gz
TEST_SCRIPT = test.sh

# ignore case
README != find -maxdepth 1 -iname readme 
MAKEFILE != find -maxdepth 1 -iname makefile

# program name here, proper capitalization, please
PROGRAM =

# doing it this way evaluates immediately instead of lazily
ARCHIVE != printf 'archives/$(PROGRAM)-%s.tar' `date -I`


# If working with C++

#SOURCE = $(PROGRAM).cpp
#COMPILED = $(PROGRAM)

#$(COMPILED): $(SOURCE)
#	$(CC) $(SOURCE)

#$(PROGRAM).s: $(SOURCE)
#	$(CC) -S $(SOURCE)

#assembly: $(PROGRAM).s



# If working with Java

#SOURCE = $(PROGRAM).java
#COMPILED = $(PROGRAM).class
#$(COMPILED): $(SOURCE)
#	$(JAVAC) $(JAVACFLAGS) $(SOURCE)

# nothing to do, class files are (in essence) assembly
# more info here: https://en.wikipedia.org/wiki/Java_bytecode
#assembly:


archives:
	mkdir archives

testing:
	mkdir testing

.PHONY: clean clobber backup tasks over test archive assembly

clean:
	rm -rf testing

clobber: clean
	rm -rf archives

$(ARCHIVE): archives $(MAKEFILE) $(README) $(SOURCE) # add more files here
	tar -cvf $(ARCHIVE) $(MAKEFILE) $(README) $(SOURCE)

# overwrites existing test archive
$(TEST_ARCHIVE): $(ARCHIVE) testing
	ln -f $(ARCHIVE) $(TEST_ARCHIVE)

$(TEST_SCRIPT): testing
	echo 'cd testing' > $(TEST_SCRIPT)
	echo 'tar -xf $(TEST_ARCHIVE)' >> $(TEST_SCRIPT)
	echo 'make' >> $(TEST_SCRIPT)
	echo 'make backup' >> $(TEST_SCRIPT)
	echo "cat $(README)" >> $(TEST_SCRIPT)
	./$(PROGRAM) | tee output1
	# add more tests here
	echo "make clean" >> $(TEST_SCRIPT)
	chmod u+x $(TEST_SCRIPT)


archive: $(ARCHIVE)

backup: $(ARCHIVE)
 
over: clean all

tasks:
	@echo backup clean clobber over test assembly

test: $(TEST_ARCHIVE) $(TEST_SCRIPT)
	./$(TEST_SCRIPT)

