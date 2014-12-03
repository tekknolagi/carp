# TODO

In no particular order:

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
* Make a Carp compiler.
* Figure out a better way for the tokenizer to exit cleanly on an empty file.
* Data:
  * Use data[] array (mem) for strings and then use addresses - don't store string pointers in program array
    * RAM/Heap of sorts
    * Sort of like hand-made pointers
  * Add way to pass data section so that DBS and DBG can be used in Carp code
    * Something like in the `c/data.c` example
  * Fix annoying warning about storing char pointer in `long long` array.
* Brainfuck compiler...
* `ldstr` method that reads string into memory and pushes address onto the stack
* Hash lookup for regs and instr names.
* Add bounds checking on LOAD/STORE, among others
* Increment IP after instruction fetched?
* Logical operators (AND, OR) and how to segment from bitwise operators
* Segment tests for stack ops into possibly separate machines... but definitely independent states somehow.
* Better way to track size of code for API

Other commentary that I am too lazy to bullet right now:

<pre>
>
> In the function carp_lex_lex(), the variable 'length' ends up
> being too small by 1.  It should be initialized to 0, not -1.
>
> Unused - function carp_vm_init();  in carp.c, variables 'opts'
> and 'this_option_optind'.   Also, 'opts' has fewer initializers
> than members.
>
> Style comment - where ever you picked up the habit of putting
> a space between a function name and the following parenthesis,
> unlearn it.  That style is good in some programming languages
> but C is not one of them.
>
</pre>
