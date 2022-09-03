# A makefile is overkill a project of this size, but you'll need to know about this soon enough.
# Variables are handy for making global changes to the makefile (e.g. -g flag)
CPP = g++
CPPFLAGS = -Wall -Wextra -pedantic -std=c++2a -Ofast

# First target is always the default if you just run "make".
c_strings: cs19_c_strings_test.o cs19_c_strings.o
	$(CPP) $(CPPFLAGS) -o c_strings cs19_c_strings_test.o cs19_c_strings.o
# Builds the object file containing our main function
cs19_c_strings_test.o: cs19_c_strings_test.cpp
	$(CPP) $(CPPFLAGS) -c cs19_c_strings_test.cpp
# Builds the object file containing class cs19::PrimeGenerator
cs19_c_strings.o: cs19_c_strings.h cs19_c_strings.cpp
	$(CPP) $(CPPFLAGS) -c cs19_c_strings.cpp
# Removes all compiled object files and the "primes" executable
clean:
	rm -f ./*.o ./c_strings