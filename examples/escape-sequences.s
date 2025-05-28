/*
 * This program demonstrates how HyperCPU can handle ANSI escape sequences [1].
 * They can be used for displaying a colorful text or moving a cursor.
 * String literals are used — see hello-world.s for details.
 *
 * Written by Ivan Movchan <ivan.movchan.07@gmail.com> in 2025.
 *
 * [1] https://en.wikipedia.org/wiki/ANSI_escape_code
 */

data:
  .b8 "\e[1;37m";
  .b8 "#       #                                          #######  ########  #       #\n";
  .b8 "#       #                                         #       # #       # #       #\n";
  .b8 "#       # #       # ########   #######  # ######  #         #       # #       #\n";
  .b8 "#       # #       # #       # #       # ##      # #         #       # #       #\n";
  .b8 "######### #       # #       # #       # #         #         ########  #       #\n";
  .b8 "#       # #       # #       # ########  #         #         #         #       #\n";
  .b8 "#       # #       # #       # #         #         #         #         #       #\n";
  .b8 "#       # #       # #       # #       # #         #       # #         #       #\n";
  .b8 "#       #  ######## ########   #######  #          #######  #          ####### \n";
  .b8 "                  # #\n";
  .b8 "                  # #\n";
  .b8 "          #       # #\n";
  .b8 "           #######  #\n\n";
  .b8 "                      https://hypercpu-project.github.io/                      \n";
  .b8 "\e[0m";
  .b8 0u0;

.attr(entry) main:
  mov x1, data;

loop:
  mov xlll2, [x1];
  cmp xlll2, 0u0;
  jme end;
  write xlll0, xlll2;
  inc x1;
  jmp loop;

end:
  halt;
