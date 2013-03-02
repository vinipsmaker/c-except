#include <stdio.h>

#include "cexcept.h"

#ifndef USE
#define USE 0
#endif

#ifndef A
#define A 1
#endif

#ifndef B
#define B 1
#endif

#ifndef C
#define C 1
#endif

int divide(int a, int b, THROW_ARGS); // throw const char *
int divide_wrapper(int a, int b, THROW_ARGS); // throw const char *
int divide3(int a, int b, int c, THROW_ARGS); // throw const char *

int main()
{
  TRY()
    printf("%i\n",
#if USE == 0
      divide(A, B, TRY_ARGS())
#elif USE == 1
      divide_wrapper(A, B, TRY_ARGS())
#else
      divide3(A, B, C, TRY_ARGS())
#endif
    );
  CATCH(const char *, stre,)
    printf("Error: %s\n", stre);
  CATCHANY()
    printf("Unknow exception throw\n"
           "This shouldn't happen\n");
  ENDTRY()
  return 0;
}

// you are free to put or not a semicolon after the THROW statement
// i strongly recommend you do it to maintain the code concise
int divide(int a, int b, THROW_NAMED_ARGS())
{
  if (b)
    return a / b;
  else
    THROW(const char *, "Not a number",)
}

// if there is only one context, you are free to use or not a named arg
int divide_wrapper(int a, int b, THROW_NAMED_ARGS(/*_rethrow*/))
{
  return divide(a, b, TRY_ARGS(/*_rethrow*/));
}

// if there are more than one context,
// you need to name at least n - 1 of the args,
// where n is the number of contexts
int divide3(int a, int b, int c, THROW_NAMED_ARGS(_main))
{
  TRY(_local)
    return divide(divide(a, b, TRY_ARGS(_local)), c, TRY_ARGS(_local));
  CATCH(const char *, e, _local)
    THROW(const char *, e, _main)
  ENDTRY(_local)
}
