; File: ft_list_remove_if.s
; File Created: 12/02/2025 20:25
; Author: Nicolas Huynh at (nico.huynh@gmail.com)
; -----
; Copyright 2025 NH

%ifidn __OUTPUT_FORMAT__, macho64
    %define OS_FN_PREFIX(fn_call) _%+ fn_call
%elifidn __OUTPUT_FORMAT__, elf64
    %define OS_FN_PREFIX(fn_call) fn_call
%endif
; r12 - head
; r13 - runner
; r14 - ref
; r15 - cmp fn
global OS_FN_PREFIX(ft_list_remove_if)
OS_FN_PREFIX(ft_list_remove_if):    ; rdi = **head, rsi = *data_ref, rdx = CMP, rcx = FREE_FN
    cmp     rdi, 0
    je      err
    cmp     dword [rdi], 0
    je      err
    cmp     rsi, 0
    je      err
    cmp     rdx, 0
    je      err
    cmp     rcx, 0
    je      err
    push    rbx
    push    r12
    push    r13
    push    r14
    push    r15

    mov     r12, rdi        ; Save **head to r12
    mov     r13, [rdi]      ; Init r13 to first node
    mov     r14, rsi        ; Save ref to r14
    mov     r15, rdx        ; Save cmp_fn to r15
    mov     rbx, rcx        ; Save free_fn to rbx
    cmp     r13, 0
    je      end
loop:
    cmp     r13, 0
    je      end
    mov     rdi, [r13]      ; Prepare for cmp
    mov     rsi, r14        ; Prepare for cmp
    call    r15             ; Call cmp fn
    cmp     rax, 0
    jne     inc_loop        ; Jump if no swap is needed
remove_elt:
    mov     rdi, [r13]      ; Select *data to free
    call    rbx             ; Call free fn
; remove node (check if it is the first)
    cmp     r13, [r12] ; are we on the first node ?
    jne     next
    ; mov     [0x0], r12 ; crash plz
    mov     r13, [r13 + 8]  ; Save next node to r13
    mov     [r12], r13      ; Change head value to r13
    jmp     loop
next:
    mov     r8, [r13 + 8]   ; Load node->next in r8
    mov     [r12 + 8], r8   ; Change prevnode->next to r8
    ; maybe free the node here ??
inc_loop:
    mov     r12, r13
    mov     r13, [r13 + 8]
    jmp     loop
end:
    pop     r15         ; Load r15
    pop     r14         ; Load r14
    pop     r13         ; Load r13
    pop     r12         ; Load r12
    pop     rbx         ; Load rdx

err:
    ret
