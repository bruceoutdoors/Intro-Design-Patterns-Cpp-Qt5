//start
#include <cstring>

bool test = false;
bool verbose = false;

void processFile(char* filename) {
//end
  if (test) { /* Do a test on FileName. */
  }
  else { /* Do the other thing. */
  }
    
  if (verbose)  { /* Output lots of detail. */
  }
  else { /* Produce brief output. */
  }
//start
}

/*
  @param argc - the number of arguments
  @param argv - an array of argument strings
*/
int main (int argc, char* argv[]) {
  // recall that argv[0] holds the name of the executable.
  for (int i=1; i < argc; ++i) { /* First process the switches. */

     if (strcmp(argv[i], "-v")==0) {
        verbose = true;
     }
     if (strcmp(argv[i], "-t") ==0) {
        test = true;
     }
  }
  for (int i=1; i < argc; ++i) { /* Make a second pass
                   to operate on the non-switched arguments. */
     if (argv[i][0] != '-') 
        processFile(argv[i]);
  }
}
//end

