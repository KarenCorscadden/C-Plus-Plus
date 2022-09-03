# A makefile is overkill a project of this size, but you'll need to know about this soon enough.
# Variables are handy for making global changes to the makefile (e.g. -g flag)
CPP = g++
CPPFLAGS = -Wall -Wextra -pedantic -std=c++2a -Ofast

# First target is always the default if you just run "make".
cs19_counting_sort_demo: main.o cs19_counting_sort.o
	$(CPP) $(CPPFLAGS) -o cs19_counting_sort_demo main.o cs19_counting_sort.o
# Builds the object file containing our main function
main.o: main.cpp
	$(CPP) $(CPPFLAGS) -c main.cpp
# Builds the object file containing class cs19::PrimeGenerator
cs19_counting_sort.o: cs19_counting_sort.h cs19_counting_sort.cpp
	$(CPP) $(CPPFLAGS) -c cs19_counting_sort.cpp
# Removes all compiled object files and the executables
clean:
	rm -f ./*.o ./cs19_counting_sort_demo