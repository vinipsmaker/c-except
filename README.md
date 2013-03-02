c-except
========

An exception system for C in a single header file

Some features:

* MIT license
* The full implementation is inside one header file, protected by define guards
* There are no global vars, so you can safely use it in parallel environments
* The exceptions are **NOT** integer-based, so you don't need to worry about
  integer collision
 * And you don't need to declare the exceptions you want to use
 * And the exceptions have type **AND** values
* You can use nested try-catch blocks and exceptions crossing function calls
 * If you have more than one context inside the same code block, you can name
   each context to kill the ambiguities
* The implementation isn't much intrusive
 * All ten "keywords" are macros and the only declared type has a name
   beginning with an underscore
 * You still can use goto to jump to outside of a try block
 * You don't need to initialize the lib or declare any global var

Some limitations:

* There is no unexpected_handler and terminate_handler
 * Every code that might throw exceptions must be inside a try block
* If you use goto to jump to a place inside a try catch, the behaviour is
  undefined
* It don't support typedefs (it recognizes "char*" and "char *" as different
  types)
* It doesn't implement RAII, so you must be very carefull to avoid resource
  leaking, but this is a C-related problem, not a problem with the
  implementation

See the sample.c file to see its usage.

This work is based in a post published at
[vol](http://www.vivaolinux.com.br/artigo/Tratamento-de-excecoes-na-linguagem-C/).
