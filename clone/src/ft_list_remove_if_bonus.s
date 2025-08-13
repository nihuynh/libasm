; File: ft_list_remove_if.s
; File Created: 12/02/2025 20:25
; Author: Nicolas Huynh at (nico.huynh@gmail.com)
; -----
; Copyright 2025 NH

%include "os_support.s"
extern OS_FN_PREFIX(free)
global OS_FN_PREFIX(ft_list_remove_if)

; r12 : head
; r13 : runner
; r14 : ref
; r15 : cmp fn
OS_FN_PREFIX(ft_list_remove_if):    ; rdi = **head, rsi = *data_ref, rdx = CMP, rcx = FREE_FN
    cmp     rdi, 0
    je      error
    cmp     dword [rdi], 0
    je      error
    cmp     rsi, 0
    je      error
    cmp     rdx, 0
    je      error
    cmp     rcx, 0
    je      error
    push    rdi
    push    rsi
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
; Remove node (check if it is the first)
    cmp     r13, [r12]      ; are we on the first node ?
    jne     next
    mov     r8, [r13 + 8]  ; Load node->next in r8
    mov     [r12], r8      ; Change head value to node->next
    jmp     freenode

next:
    mov     r8, [r13 + 8]   ; Load node->next in r8
    mov     [r12 + 8], r8   ; Change prevnode->next to node->next
freenode:
    mov     rdi, r13
    mov     r13, r8         ; node = node->next
    ; call    OS_FN_PREFIX(free) wrt ..plt
    call    OS_FN_PREFIX(free)
    jmp     loop

inc_loop:
    mov     r12, r13        ; Save current node in r12
    mov     r13, [r13 + 8]  ; node = node->next
    jmp     loop

end:
    pop     r15             ; Restore register values
    pop     r14
    pop     r13
    pop     r12
    pop     rbx
    pop     rsi
    pop     rdi
error:
    ret
