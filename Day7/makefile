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

bin/day7.o : src/day7.cc
	$(compile) $@ $^

day7 : bin/day7.o
	$(link) $@ $^
	./day7 inputday7.txt

clean:
	rm -f bin/* day7*