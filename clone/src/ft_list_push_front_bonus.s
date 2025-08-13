; File: ft_list_push_front.s
; File Created: 12/02/2025 20:25
; Author: Nicolas Huynh at (nico.huynh@gmail.com)
; -----
; Copyright 2025 NH

%include "os_support.s"
extern OS_FN_PREFIX(malloc)
global OS_FN_PREFIX(ft_list_push_front)

OS_FN_PREFIX(ft_list_push_front):   ; rdi = **head rsi = *data
    cmp     rdi, 0          ; Check if the **head is NULL
    je      end
    cmp     rsi, 0          ; Check if the *data is NULL
    je      end
    push    rdi             ; Store **head
    push    rsi             ; Store *data
    mov     rdi, 16         ; 16 for the 2 ptr
    ; call    OS_FN_PREFIX(malloc) wrt ..plt
    call    OS_FN_PREFIX(malloc)
    pop     rsi
    pop     rdi
    cmp     rax, 0          ; Check if malloc has failed
    je      end
    mov     [rax], rsi      ; Link *data to node.data
    mov     r8, [rdi]       ; Save *head to r8
    mov     [rax + 8], r8   ; Link *head to node.next
    mov     [rdi], rax      ; Change head value to *elt
end:
    ret
