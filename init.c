void init_vm (machine_state *mstate) {
  mstate->pc = 0;
  mstate->running = 1;
  StackInit(&mstate->stack, VM_STACK_HEIGHT);
}
