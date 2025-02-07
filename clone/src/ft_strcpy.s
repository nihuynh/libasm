%ifidn __OUTPUT_FORMAT__, macho64
    %define STRCPY_LABEL    _ft_strcpy
%elifidn __OUTPUT_FORMAT__, elf64
    %define STRCPY_LABEL    ft_strcpy
%endif

global STRCPY_LABEL
STRCPY_LABEL:      ; rdi = dst, rsi = src
    xor     rcx, rcx    ; reset the counter

runloop:
    mov     al, byte [rsi + rcx]    ; store byte of src
    mov     byte [rdi + rcx], al    ; write the byte to dest
    cmp     al, 0                   ; check if the last char was a null-char
    je      end
    inc     rcx
    jmp     runloop

end:
    mov     rax, rdi
    ret