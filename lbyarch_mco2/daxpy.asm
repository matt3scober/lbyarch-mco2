section .text
bits 64
default rel
global DAXPYASM
DAXPYASM:
    ;write your code here

    ;DAXPYASM(int N, double A, double* X, double* Y, double* Z_ASM)
    ;N = rcx
    ;A = xmm1
    ;X = R8
    ;Y = R9
    ;Z = RBP+32

    push rbp
    mov rbp, rsp
    add rbp, 16
    mov r10, [rbp + 32]
    dec rcx
MULADD:
    test rcx, rcx
    jz END
    
    movsd xmm2, [r8] ;xmm2 = x
    movsd xmm3, [r9] ; xmm3 = y
    mulsd xmm2, xmm1 ;a * x = a
    vaddsd xmm0, xmm2, xmm3 ; a + y = a
    movsd [r10], xmm0 ; a = z_asm
    add r8, 8
    add r9, 8
    add r10, 8
    
    dec rcx
    JMP MULADD

END:
    pop rbp
    ret