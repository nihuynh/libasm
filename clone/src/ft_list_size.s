%ifidn __OUTPUT_FORMAT__, macho64
    %define LIST_SIZE_LABEL      _ft_list_size
%elifidn __OUTPUT_FORMAT__, elf64
    %define LIST_SIZE_LABEL      ft_list_size
%endif

global LIST_SIZE_LABEL
LIST_SIZE_LABEL:       ; rdi = ?, rsi = ?, rdx = ?
    ret
