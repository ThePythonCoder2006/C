.LC0:
  .string "%i"
main:
  push rbx
.L2:
  sub ebx, 1
  mov edi, OFFSET FLAT:.LC0
  xor eax, eax
  mov esi, ebx
  call printf
  jmp .L2