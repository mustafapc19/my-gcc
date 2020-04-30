extern printf
extern scanf
SECTION .DATA
__lit_0: db "%d %d",0
SECTION .TEXT
global main
main:
push rbp
mov rbp,rsp
sub rsp,0x10
mov eax,3
mov [rbp-0x4],eax
mov rdi,__lit_0
mov rsi,[rbp-0x4]
mov rdx,1
mov rax,0
call printf
mov rax, [rbp-0x4]
leave
ret
