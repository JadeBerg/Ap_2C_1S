//+===================================================================
// File Lab5_app.cpp
// Вариант 15
//
// Эта программа вычисляет арифметическое выражение при помощи сдвигов 
//
// (C) Струна В.Р., 2020
//
// Входные данные:
// a = 55, b = 16
// Выходные данные:
//     Z = x*a/b 
//     V = y*a/b 
#include <iostream>
#include <locale.h>
#define a 55
#define b 16
typedef unsigned char byte;
unsigned long x, x_a, Z, Z_a;
long y, y_a, V, V_a;
int neg;
int err_a;
int main()
{
    for (;;) {
        neg = 0;
        err_a = 0;
        setlocale(LC_ALL, "rus");
        printf("Введите числа x: ");
        scanf_s("%lu", &x);
        printf("Введите числа y: ");
        scanf_s("%ld", &y);
        //=====================C===========================
        x_a = x;
        y_a = y;
        Z = x << (byte)6; 
        Z -= x << (byte)2; 
        Z -= x << (byte)2; 
        Z -= x << (byte)0; 
        Z = Z >> 4;
        if (y < 0) {
            y = -y;
            neg = 1;
        }
        V = y << (byte)6;
        V -= y << (byte)2;
        V -= y << (byte)2;
        V -= y << (byte)0;
        V = V >> 4;
        if (neg)
            V = -V;
        //=====================Assembler===========================
        _asm {
            mov err_a, 0
            mov ebx, 0
            xor eax, eax
            mov ecx, x_a
            mov eax, ecx
            mov edx, 0
            shl eax, 6
            jc Over1
            add edx, eax
            jc Over1
            mov eax, ecx
            shl eax, 2
            sub edx, eax
            mov eax, ecx
            shl eax, 2
            sub edx, eax
            mov eax, ecx
            shl eax, 0
            sub edx, eax
            shr edx, 4
            jmp End
            Over1 :
            mov err_a, 1
                End :
                mov ecx, edx
                mov Z_a, ecx;
        }
        _asm {
            mov ebx, 0
            xor eax, eax
            mov ecx, y_a
            cmp ecx, 0
            jns Not_neg
            xor ecx, 0ffffffffh
            inc ecx
            mov ebx, 1
            Not_neg :
            mov eax, ecx
                mov edx, 0
                sal eax, 6
                jo Over
                add edx, eax
                mov eax, ecx
                sal eax, 2
                sub edx, eax
                mov eax, ecx
                sal eax, 2
                sub edx, eax
                mov eax, ecx
                sal eax, 0
                sub edx, eax
                sar edx, 4
                mov ecx, edx
                jo Over
                jmp Finish
                Over :
            mov err_a, 1

                Finish :
                cmp ebx, 0
                je Ins_num
                xor ecx, 0ffffffffh
                inc ecx
                Ins_num :
            mov V_a, ecx;
        }
        if (err_a == 1)
            printf("Ошибка!!\n");
        else {
            printf("======C======\n Z: %lu\n V: %ld\n", Z, V);
            printf("======Assembler======\n Z_a: %lu\n V_a: %ld \n",Z_a, V_a);
        }
    }
}