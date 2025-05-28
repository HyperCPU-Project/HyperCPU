/*
 * This program compares 2 values in x0 and x1 registers and displays a message depending on the result of comparison.
 *
 * Written by Ivan Movchan <ivan.movchan.07@gmail.com> in 2025.
 */

str_equal:
  .b8 "x0 = x1\n";
  .b8 0u0;

str_greater:
  .b8 "x0 > x1\n";
  .b8 0u0;

str_less:
  .b8 "x0 < x1\n";
  .b8 0u0;

.attr(entry) main:
  mov x0, 0u42;
  mov x1, 0x13;
  cmp x0, x1;
  jme is_equal;
  jmgr is_greater;
  jml is_less;

is_equal:
  mov x3, str_equal;
  jmp print;

is_greater:
  mov x3, str_greater;
  jmp print;

is_less:
  mov x3, str_less;
  jmp print;

print:
  mov xlll0, 0u0;
  mov xlll2, [x3];
  cmp xlll2, 0u0;
  jme print_end;
  write xlll0, xlll2;
  inc x3;
  jmp print;

print_end:
  halt;
