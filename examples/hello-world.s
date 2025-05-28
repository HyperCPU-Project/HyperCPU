/*
 * This is another simple "Hello World" program written in HyperCPU assembly (hASM).
 * It writes a null-terminated string to the console using string literals and a little loop, then halts CPU.
 *
 * Before 0.4.5 version you could have to write a string char by char — see hello-world-legacy.s for details.
 *
 * Written by Ivan Movchan <ivan.movchan.07@gmail.com> in 2025.
 */

data:
  .b8 "Hello, world!\n";
  .b8 0u0;

.attr(entry) main:      // Program entry point.
  mov x1, data;

print:
  mov xlll2, [x1];
  cmp xlll2, 0u0;     // Is NULL (0u0)?
  jme print_end;      // Yes — go to finish.
  write xlll0, xlll2; // No — write data to console.
  inc x1;
  jmp print;

print_end:
  halt;
