%ifidn __OUTPUT_FORMAT__, macho64
    %define LIST_PUSH_FRONT_LABEL      _ft_list_PUSH_FRONT
%elifidn __OUTPUT_FORMAT__, elf64
    %define LIST_PUSH_FRONT_LABEL      ft_list_PUSH_FRONT
%endif

global LIST_PUSH_FRONT_LABEL
LIST_PUSH_FRONT_LABEL:       ; rdi = ?, rsi = ?, rdx = ?
    ret