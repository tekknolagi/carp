void init_vm (machine_state *ms) {
  m->pc = 0;
  m->running = 1;
  StackInit(&m->stack, VM_STACK_HEIGHT);
}
