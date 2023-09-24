; -----------------------------------------------------------------------------
; A 64-bit function that calculate the length of a string
; The function has prototype:
;
;   int ft_strlen(char *str)
; -----------------------------------------------------------------------------

    global  ft_strlen
    section .text

ft_strlen:
    push %ebp             ; Save base pointer
    mov %esp, %ebp        ; Set base pointer
    mov 8(%ebp), %edx     ; Get string argument
    xor %eax, %eax        ; Set length to 0

read:
    cmpb $0, (%edx)       ; Check if current character is null
    je done              ; If it is, we're done
    inc %eax              ; Otherwise, increment length
    inc %edx              ; and move to the next character
    jmp read             ; and repeat the loop

done:
    pop %ebp              ; Restore base pointer
    ret                   ; Return length
