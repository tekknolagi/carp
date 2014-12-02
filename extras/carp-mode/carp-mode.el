;;; carp-mode --- Major mode for Carp
;;; Commentary:
;;; Code:

(setq carp-instructions
      '("halt" "nop" "loadr" "load" "store" "mov" "add" "sub" "mul"
        "mod" "shr" "shl" "not" "xor" "or" "and" "incr" "decr" "inc"
        "dec" "pushr" "push" "pop" "cmp" "lt" "gt" "jz" "rjz" "jnz"
        "rjnz" "jmp" "rjmp" "call" "ret" "preg" "ptop"))
(setq carp-registers
      '("r0" "r1" "r2" "r3" "r4" "r5" "r6" "r7" "r8" "r9"
        "ax" "bx" "cx" "dx" "rx"
        "ip" "sp" "fp" "gbg" "run" "ext"))

(setq carp-labels-regexp '("\\([a-zA-Z_]+[0-9]*\\):" . 1))
(setq carp-instructions-regexp (regexp-opt carp-instructions 'words))
(setq carp-registers-regexp (regexp-opt carp-registers 'words))
(setq carp-immediates-regexp "[\-\+]?[0-9]+")

(setq carp-instructions nil)
(setq carp-registers nil)

(setq carp-keywords
      `((,carp-labels-regexp . font-lock-function-name-face)
        (,carp-instructions-regexp . font-lock-builtin-face)
        (,carp-registers-regexp . font-lock-type-face)
        (,carp-immediates-regexp . font-lock-constant-face)))

(define-derived-mode carp-mode fundamental-mode
  (setq font-lock-defaults '((carp-keywords)))
  (setq mode-name "Carp"))

(provide 'carp-mode)
;;; carp-mode.el ends here
