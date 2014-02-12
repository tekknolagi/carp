void init_vm (machine_state *ms) {
  // set program counter to 0
  m->pc = 0;

  // "turn VM on"
  m->running = 1;

  // initialize stack
  StackInit(&m->stack, VM_STACK_HEIGHT);
}
