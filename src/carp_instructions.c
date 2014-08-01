#include "carp_machine.h"

definstr (HALT) {
  carp_vm_exit(m, m->code[++m->regs[CARP_EIP]]);
}

definstr (NOP) {
  ;
}

definstr (LOADI) {
  long long reg = m->code[++m->regs[CARP_EIP]];
  long long val = m->code[++m->regs[CARP_EIP]];
  m->regs[reg] = val;
}

definstr (MOV) {
  long long dst = m->code[++m->regs[CARP_EIP]],
    src = m->code[++m->regs[CARP_EIP]];
  m->regs[dst] = m->regs[src];
}

definstr (ADDI) {
  long long b, a;
  if (carp_stack_pop(&m->stack, &b) == -1) {
    fprintf(stderr, CARP_STACK_EMPTY);
    carp_vm_exit(m, 1);
  }

  if (carp_stack_pop(&m->stack, &a) == -1) {
    fprintf(stderr, CARP_STACK_EMPTY);
    carp_vm_exit(m, 1);
  }

  carp_stack_push(&m->stack, a + b);
}

definstr (SUBI) {
  long long b, a;
  if (carp_stack_pop(&m->stack, &b) == -1) {
    fprintf(stderr, CARP_STACK_EMPTY);
    carp_vm_exit(m, 1);
  }
  if (carp_stack_pop(&m->stack, &a) == -1) {
    fprintf(stderr, CARP_STACK_EMPTY);
    carp_vm_exit(m, 1);
  }
  carp_stack_push(&m->stack, a - b);
}

definstr (MULI) {
  long long b, a; 
  if (carp_stack_pop(&m->stack, &b) == -1) {
    fprintf(stderr, CARP_STACK_EMPTY);
    carp_vm_exit(m, 1);
  }

  if (carp_stack_pop(&m->stack, &a) == -1) {
    fprintf(stderr, CARP_STACK_EMPTY);
    carp_vm_exit(m, 1);
  }

  carp_stack_push(&m->stack, a * b);
}

definstr (INCR) {
  long long reg = m->code[++m->regs[CARP_EIP]];
  m->regs[reg]++;
}

definstr (DECR) {
  long long reg = m->code[++m->regs[CARP_EIP]];
  m->regs[reg]--;
}

definstr (INCI) {
  long long a;
  if (carp_stack_pop(&m->stack, &a) == -1) {
    fprintf(stderr, CARP_STACK_EMPTY);
    carp_vm_exit(m, 1);
  }
  carp_stack_push(&m->stack, a + 1);
}

definstr (DECI) {
  long long a;
  if (carp_stack_pop(&m->stack, &a) == -1) {
    fprintf(stderr, CARP_STACK_EMPTY);
    carp_vm_exit(m, 1);
  }
  carp_stack_push(&m->stack, a - 1);
}

definstr (PUSHR) {
  long long reg = m->code[++m->regs[CARP_EIP]];
  long long a = m->regs[reg];
  int status = carp_stack_push(&m->stack, a);
  if (status == -1) {
    fprintf(stderr, CARP_STACK_NO_MEM);
    carp_vm_exit(m, 1);
  }
}

definstr (PUSHI) {
  long long a = m->code[++m->regs[CARP_EIP]];
  int status = carp_stack_push(&m->stack, a);
  if (status == -1) {
    fprintf(stderr, CARP_STACK_NO_MEM);
    carp_vm_exit(m, 1);
  }
}

definstr (POPI) {
  long long val;
  if (carp_stack_pop(&m->stack, &val) == -1) {
    fprintf(stderr, CARP_STACK_EMPTY);
    carp_vm_exit(m, 1);
  }

  m->regs[CARP_GBG] = val;
}

definstr (CMP) {
  carp_instr_POPI(m);
  long long b = m->regs[CARP_GBG];
  carp_instr_POPI(m);
  long long a = m->regs[CARP_GBG];

  m->regs[CARP_EAX] = a - b;
}

definstr (JZ) {
  // zero
  if (!m->regs[CARP_EAX])
    m->regs[CARP_EIP] = m->code[++m->regs[CARP_EIP]];
}

definstr (RJZ) {
  // zero
  if (!m->regs[CARP_EAX])
    m->regs[CARP_EIP] += m->code[m->regs[CARP_EIP] + 1];
}

definstr (JNZ) {
  // not zero
  if (m->regs[CARP_EAX])
    m->regs[CARP_EIP] = m->code[++m->regs[CARP_EIP]];
}

definstr (RJNZ) {
  // not zero
  if (m->regs[CARP_EAX])
    m->regs[CARP_EIP] += m->code[m->regs[CARP_EIP] + 1];
}

definstr (JMP) {
  m->regs[CARP_EIP] = m->code[++m->regs[CARP_EIP]];
}

definstr (RJMP) {
  m->regs[CARP_EIP] += m->code[m->regs[CARP_EIP] + 1];
}

definstr (DBS) {
  char *key = (char *) m->code[++m->regs[CARP_EIP]];
  long long val = m->code[++m->regs[CARP_EIP]];
  carp_ht *res = carp_ht_set(&m->vars, key, val);
  if (res == NULL) {
    fprintf(stderr, CARP_HT_NO_MEM);
    carp_vm_exit(m, 1);
  }
}

definstr (DBG) {
  char *key = (char *) m->code[++m->regs[CARP_EIP]];
  carp_ht *res = carp_ht_get(&m->vars, key);
  if (res == NULL) {
    fprintf(stderr, CARP_HT_DNE);
    carp_vm_exit(m, 1);
  }

  m->regs[CARP_EAX] = res->value;
}


definstr (LBL) {
  char *key = (char *) m->code[++m->regs[CARP_EIP]];
  long long val = ++m->regs[CARP_EIP];
  carp_ht *res = carp_ht_set(&m->labels, key, val);
  if (res == NULL) {
    fprintf(stderr, CARP_HT_NO_MEM);
    carp_vm_exit(m, 1);
  }
}

definstr (CALL) {
  /*char *key = (char *) m->code[++m->regs[CARP_EIP]];
  carp_ht *res = carp_ht_get(&m->labels, key);
  if (res == NULL) {
    fprintf(stderr, CARP_HT_DNE);
    carp_vm_exit(m, 1);
    }*/

  long long nargs = m->code[++m->regs[CARP_EIP]];
  int status;
  status = carp_stack_push(&m->stack, nargs);
  if (status == -1) {
    fprintf(stderr, CARP_STACK_NO_MEM);
    carp_vm_exit(m, 1);
  }

  status = carp_stack_push(&m->stack, m->regs[CARP_EFP]);
  if (status == -1) {
    fprintf(stderr, CARP_STACK_NO_MEM);
    carp_vm_exit(m, 1);
  }

  status = carp_stack_push(&m->stack, m->regs[CARP_EIP]);
  if (status == -1) {
    fprintf(stderr, CARP_STACK_NO_MEM);
    carp_vm_exit(m, 1);
  }

  m->regs[CARP_EFP] = m->regs[CARP_ESP];
  m->regs[CARP_EIP] = m->regs[CARP_EIP] + 2; // res->value;
}

definstr (RET) {
  long long rvalue;

  if (carp_stack_pop(&m->stack, &rvalue) == -1) {
    fprintf(stderr, CARP_STACK_EMPTY);
    carp_vm_exit(m, 1);
  }

  long long state;

  m->regs[CARP_ESP] = m->regs[CARP_EFP];

  if (carp_stack_pop(&m->stack, &state) == -1) {
    fprintf(stderr, CARP_STACK_EMPTY);
    carp_vm_exit(m, 1);
  }
  m->regs[CARP_EIP] = state;

  if (carp_stack_pop(&m->stack, &state) == -1) {
    fprintf(stderr, CARP_STACK_EMPTY);
    carp_vm_exit(m, 1);
  }
  m->regs[CARP_EFP] = state;

  if (carp_stack_pop(&m->stack, &state) == -1) {
    fprintf(stderr, CARP_STACK_EMPTY);
    carp_vm_exit(m, 1);
  }

  long long nargs = state;
  m->regs[CARP_ESP] -= nargs;

  state = carp_stack_push(&m->stack, rvalue);
  if (state == -1) {
    fprintf(stderr, CARP_STACK_NO_MEM);
    carp_vm_exit(m, 1);
  }
}

definstr (PREG) {
  int reg = m->code[++m->regs[CARP_EIP]];
  printf("%lld\n", m->regs[reg]);
}

definstr (PTOP) {
  long long val;

  if (carp_stack_peek(&m->stack, &val) == -1) {
    fprintf(stderr, CARP_STACK_EMPTY);
    carp_vm_exit(m, 1);
  }

  printf("%lld\n", val);
}
