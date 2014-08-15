# TODO

In no particular order:

* Fix annoying warning about storing char pointer in `long long` array.
* Make a Carp compiler.
* Re-implement the ht as an actual hashtable. In progress. Adding linear probing.
  * See branch `new_ht_impl`.
* Read Carp files as lines instead of whole files.
* Write tests for:
  1. DONE: stack
  2. DONE: ht
  3. Instructions
  4. Tokenizer
  5. Lexer
  6. DONE: Registers
* Have API never exit, but pass up error codes.
* Add way to pass data section so that DBS and DBG can be used in Carp code
  * Something like in the `c/data.c` example
* Use data[] array (mem) for strings and then use addresses - don't store string pointers in program array
