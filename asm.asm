extern printf
extern scanf
SECTION .DATA
__lit_0: db "%d %d %d",0
__lit_1: db "%d",0
__lit_2: db "heyy",10,0
__lit_3: db "%d %d ",10,"%d %d %d",10,10,10,0
SECTION .TEXT
global main
main:
push rbp
mov rbp,rsp
sub rsp,0x20
mov rdi,__lit_0
lea rsi,[rbp-0x4]
lea rdx,[rbp-0x8]
lea rcx,[rbp-0xc]
mov rax,0
call scanf
__loop_0start: nop
mov edx,[rbp-0x8]
mov ecx,2
cmp edx,ecx
je __loop_0end
mov rdi,__lit_1
lea rsi,[rbp-0x8]
mov rax,0
call scanf
mov rdi,__lit_2
mov rax,0
call printf
jmp __loop_0start
__loop_0end: nop
mov rdi,__lit_3
mov rsi,[rbp-0x4]
mov rdx,[rbp-0x8]
mov rcx,3
mov r8d,4
mov r9d,5
mov rax,0
call printf
mov rax, [rbp-0x8]
leave
ret
