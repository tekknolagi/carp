# TODO

In no particular order:

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
  * DONE: ALU
  * Tokenizer
  * Lexer
* Bytecode format so it does not need to interpret Carp code on the fly
* Look-behind for lexer so that labels that follow call statements can be easily lexed.
  * DONE except make checking for call cleaner. flag? instruction enum?
* Make call with nargs actually do something useful. Shortcut for accessing params?
* Make a Carp compiler.
* Figure out a better way for the tokenizer to exit cleanly on an empty file.
* Data:
  * Use data[] array (mem) for strings and then use addresses - don't store string pointers in program array
    * Sort of like hand-made pointers
  * Add way to pass data section so that DBS and DBG can be used in Carp code
    * Something like in the `c/data.c` example
  * Fix annoying warning about storing char pointer in `long long` array.
* Brainfuck compiler...
* `ldstr` method that reads string into memory and pushes address onto the stack
* Hash lookup for regs and instr names.
