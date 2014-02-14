void init_vm (machine_state *m) {
  // set instruction pointer to 0
  for (int i = 0; i < NUM_REGS; i++) {
    m->regs[i] = 0;
  }

  // "turn VM on"
  m->running = FLAG_TRUE;

  // initialize stack
  stack_init(&m->stack, VM_STACK_HEIGHT);
}
