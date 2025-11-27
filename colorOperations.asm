;крутой ассемблер уже заранее чувствителен к регистрам
;calling convencions - rdi , rsi , rdx, rcx

global AdjustColors
global GrayScale
global Blur
global Inversion

default rel

;uchar*array - rdi, int row - rsi, int col - rdx, value - rcx
; ARGB  --> B G R A

;calling convencions - rdi , rsi , rdx
; RDI - Byte picture stored as B G R A B G R A ...
;RSI - colors adjustments 0 - red, 1 - green, 2 - blue, 3 - opacity
;RDX - image size
AdjustColors
push rdi
push rsi
push rdx

mov rcx,rdx
shr rcx, 2
xor rdx, rdx

xor rax,rax
xor r8,r8
xor r9,r9
xor r10,r10
xor r11,r11
mov r8d,dword [rsi+8];blue
mov r9d,dword [rsi+4] ;green
mov r10d,dword [rsi] ;red
mov r11d,dword [rsi+12];opacity

adjcolors_loop:
    blue:
    mov eax,r8d
    call AdjustColorsHelper
    inc rdi
    green:
    mov eax,r9d
    call AdjustColorsHelper
    inc rdi
    red:
    mov eax,r10d
    call AdjustColorsHelper
    inc rdi
    opacity:
    mov eax,r11d
    call AdjustColorsHelper
    inc rdi
loop adjcolors_loop

pop rdx
pop rsi
pop rdi
ret

AdjustColorsHelper:
push rax
push rdx
cmp eax,0
jl ad_minus
    mov edx,255
    sub edx,eax ;maximum
    cmp byte [rdi],dl
    ja ad_cap
        add byte [rdi],al
        jmp ad_end
    ad_cap:
        mov byte [rdi],255
        jmp ad_end
ad_minus:
    neg eax
    mov edx,eax ;minumum
    cmp byte [rdi],dl
    jb ad_min
        sub byte [rdi],dl
        jmp ad_end
    ad_min:
        mov byte [rdi],0
        jmp ad_end
    ;neg eax
ad_end:
pop rdx
pop rax
ret


;uchar*array - rdi, uchar* - rsi, int row - rdx, col - rcx
GrayScale:
push rdi
push rsi
push rdx
push rcx

push rdi
push rsi
pop rdi
pop rsi

imul rcx,rdx ;picture size
shr rcx,2
xor rdx,rdx

xor r8,r8
xor r9,r9
xor r10,r10
xor r11,r11

gr_loop
mov r8b,byte [rdi] ;blue
inc rdi
mov r9b,byte [rdi] ; green
inc rdi
mov r10b,byte [rdi] ;red
inc rdi
inc rdi
;r11 stores result
cmp r8b,r9b
ja cmp_Blue_Red ;B>G
;B<G -  cmp green and red
cmp r9b,r10b
ja mov_in_G
jbe mov_in_R

cmp_Blue_Red:
cmp r8b,r10b
ja mov_in_B
jb mov_in_R


mov_in_B:
mov r11b,r8b
jmp gr_end
mov_in_G:
mov r11b,r9b
jmp gr_end
mov_in_R:
mov r11b,r10b
jmp gr_end

gr_end:
 mov byte [rsi],r11b
 inc rsi
 mov byte [rsi],r11b
 inc rsi
 mov byte [rsi],r11b
 inc rsi
 inc rsi
loop gr_loop

pop rcx
pop rdx
pop rsi
pop rdi
ret

;rsi - state array
;rdi - our array
;rdx - row
;rcx - col
Blur:
push rdi
push rsi
push rdx
push rcx
push rax
push rbx

mov rbx,rcx ;col
mov rax,rdx ;row

add rdi,rbx
add rsi,rbx

mov rcx,rax
sub rcx,2
blur_outer_loop:
push rcx
inc rdi
inc rsi
mov rcx,rbx
sub rcx,2
    blur_inner_loop:
    call Blur_helper
    inc rdi
    inc rsi
    loop blur_inner_loop
    inc rdi
    inc rsi
pop rcx
loop blur_outer_loop
pop rbx
pop rax
pop rcx
pop rdx
pop rsi
pop rdi
ret

;rdi - redacted array,rsi -  arrcopy(placed on the same spot)
;rbx - columns in row, rax - rows
;Need to write in byte rdi value left+right+top+bot/4
Blur_helper:
push r8
push rax
push rdx
push rsi

xor eax, eax    ; Временный регистр для чтения
xor r8,r8
movzx eax, byte [rsi - 4]   ; Читаем байт и расширяем до 32 бит
add r8d, eax                ; Прибавляем к сумме

movzx eax, byte [rsi + 4]
add r8d, eax

mov r9,rbx
imul r9,4 ; stride
push rsi
sub rsi,r9
movzx eax,byte [rsi] ; rbx должен быть равен ширине строки
add r8d, eax
pop rsi

push rsi
add rsi,r9
movzx eax, byte [rsi]
add r8d, eax
pop rsi

shr r8,2
mov byte [rdi],r8b

pop rsi
pop rdx
pop rax
pop r8
ret

;uchar*array - rdi, uchar* - rsi = not changed, int row - rdx, col - rcx
Inversion
push rdi
push rcx
push rdx
imul rcx,rdx ;size
xor rdx,rdx
inv_loop:
mov dl,255
sub dl,byte [rdi]
mov byte [rdi],dl
inc rdi
loop inv_loop

pop rdx
pop rcx
pop rdi
ret

