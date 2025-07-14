buffer:
  .b64 0u0; // x0 register.
  .b64 0u0; // x1 register.
  .b64 0u0; // x2 register.
  .b64 0u0; // x3 register.
  .b64 0u0; // NULL terminator.

.attr(entry) main:
  mov x0, 0x01;
  hid;
  mov [buffer], x0;
  mov [buffer], x1;
  mov [buffer], x2;
  mov [buffer], x3;
  halt;

