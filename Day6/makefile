cc = g++  # use g++ compiler
path = ..
standard = c++17

flags = -std=$(standard)  # compile with standard
flags += -Wall  # compile with all warnings
flags += -pedantic  # even more warnings
flags += -I $(path)  # add parent to preprocessor include path
flags += -g  # include gdb instrumentation

link = $(cc) $(flags) -o  # final linked build to binary executable

compile = $(cc) $(flags) -c -o  # compilation to intermediary .o files

bin/day6.o : src/day6.cc
	$(compile) $@ $^

day6 : bin/day6.o
	$(link) $@ $^
	./day6 inputday6.txt

clean:
	rm -f bin/* day6*