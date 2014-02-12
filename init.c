void init_vm (machine_state *m) {
  // set instruction pointer to 0
  m->regs[EIP] = 0;

  // "turn VM on"
  m->running = 1;

  // initialize stack
  StackInit(&m->stack, VM_STACK_HEIGHT);
}
