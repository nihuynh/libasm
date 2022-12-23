strcpy:
    push ebp            ; Save base pointer
    mov ebp, esp        ; Set base pointer
    mov edx, [ebp + 12] ; Load address of dest buffer
    cmp edx, 0          ; Check for null pointer
    je null_pointer     ; Jump if edx is null
    mov esi, [ebp + 16] ; Load address of src string
    cmp esi, 0          ; Check for null pointer
    je null_pointer     ; Jump if esi is null
    mov ecx, [ebp + 8]  ; Load length of src string
    cmp edx, esi        ; Check if src and dest overlap
    je copy_done        ; Jump if src and dest overlap
    cmp edx, esi        ; Check if src is before dest
    jb src_before_dest  ; Jump if src is before dest
    add esi, ecx        ; Point to end of src string
    add edx, ecx        ; Point to end of dest buffer
    std                 ; Set direction flag for backwards copy
    rep movsb           ; Copy src string to dest buffer
    cld                 ; Clear direction flag
    jmp copy_done       ; Jump to done label
src_before_dest:
    rep movsb           ; Copy src string to dest buffer
copy_done:
    pop ebp             ; Restore base pointer
    ret                 ; Return to caller
null_pointer:
    xor eax, eax        ; Clear eax register
    pop ebp             ; Restore base pointer
    ret                 ; Return to caller