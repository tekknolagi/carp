# TODO

In no particular order:

* Fix annoying warning about storing char pointer in `long long` array.
* Make a Carp compiler.
* Re-implement the ht as an actual hashtable. In progress. Adding linear probing.
  * See branch `new_ht_impl`.
* Read Carp files as lines instead of whole files.
* Write tests.
* Have API never exit, but pass up error codes.
* Take a look at `carp_stack_full` - it may be subject to off by one error.
* Make dedicated types for code (long long), bool (short int), etc.