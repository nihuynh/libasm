; File: ft_list_sort.s
; File Created: 12/02/2025 20:25
; Author: Nicolas Huynh at (nico.huynh@gmail.com)
; -----
; Description: <Desc of the file goal(s)>
; Copyright 2025 NH

%ifidn __OUTPUT_FORMAT__, macho64
    %define LIST_SORT_LABEL      _ft_list_sort
%elifidn __OUTPUT_FORMAT__, elf64
    %define LIST_SORT_LABEL      ft_list_sort
%endif

global LIST_SORT_LABEL
LIST_SORT_LABEL:       ; rdi = ?, rsi = ?, rdx = ? (t_list **alst, int (*cmp_res)(void *res1, void *res2))
    ret
