; File: ft_list_sort.s
; File Created: 12/02/2025 20:25
; Author: Nicolas Huynh at (nico.huynh@gmail.com)
; -----
; Copyright 2025 NH

%include "os_support.s"
global OS_FN_PREFIX(ft_list_sort)

; r12 : head
; r13 : runner x
; r14 : runner y
; r15 : cmp fn
OS_FN_PREFIX(ft_list_sort): ; rdi = **head, rsi = fnptr
    cmp     rdi, 0
    je      error
    push    rdi             ; Saving register values to the stack
    push    rsi
    push    r12
    push    r13
    push    r14
    push    r15
    mov     r12, [rdi]      ; Save head *list node to r12
    mov     r15, rsi        ; Save fnptr to r15
    mov     r13, r12        ; Init r13 to first node
x_loop: ; change r13
    cmp     r13, 0
    je      end
    mov     r14, r13        ; Init r14 to current node
y_loop: ; change r14
    cmp     r13, r14
    je      inc_loop        ; Jump if we look at the same nodes
    mov     rdi, [r13]      ; Prepare for cmp
    mov     rsi, [r14]      ; Prepare for cmp
    call    r15             ; Call cmp fn
    cmp     eax, 0
    jle     inc_loop        ; Jump if no swap is needed
swap_val:
    mov     rdi, [r13]      ; Load *data of the x node
    mov     rsi, [r14]      ; Load *data of the y node
    mov     [r13], rsi      ; Swap data addresses
    mov     [r14], rdi      ; Swap data addresses
inc_loop:
    mov     r14, [r14 + 8]
    cmp     r14, 0
    jne     y_loop          ; Iterate & comparing with r13
    mov     r13, [r13 + 8]
    cmp     r13, 0
    jne     x_loop          ; Increment r13->next

end:
    pop     r15          ; Restore register values
    pop     r14
    pop     r13
    pop     r12
    pop     rsi
    pop     rdi
error:
    ret
