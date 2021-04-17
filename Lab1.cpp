//+===================================================================
// File Lab_1.c
// Линейная арифметическая программа
// Вариант 15
// Эта программа проверяет арифметическое тождество
//  (a+b)(c+d) = ac+bc+ad+bd,
// где a=a/17, b=b/18, c=c/19, d=d/20
//
// Для этого вычисляют значение левой и правой частей этого тождества
// на С и на ассемблере
//
// (C) Струна В.Р., 2020
//-===================================================================

#include <stdio.h>
#include <locale.h>
#define   DENOM  15
long int  a, b, c, d;
long int a1, b1, c1, d1;
long int right, left, right_a, left_a;
int err, err1;

int main() {
	setlocale(LC_ALL, "Rus");
	printf("\n\t\t(C) Струна В.Р., 2020");
	for (;;) {
		printf("\n\tПроверить тождество (a+b)(c+d) = ac+bc+ad+bd");
		printf("\n\tгде a=a/17, b=b/18, c=c/19, d=d/20");
		printf("\nПожалуйста, введите целое число a : ");
		scanf_s("%li", &a);
		printf("Пожалуйста, введите целое число b : ");
		scanf_s("%li", &b);
		printf("Пожалуйста, введите целое число c : ");
		scanf_s("%li", &c);
		printf("Пожалуйста, введите целое число d : ");
		scanf_s("%li", &d);
		//=============================== C ==================================
		//Разделить исходные переменные
		a1 = a / (DENOM + 2);
		b1 = b / (DENOM + 3);
		c1 = c / (DENOM + 4);
		d1 = d / (DENOM + 5);
		// Вычислить выражение
		right = (a1 + b1) * (c1 + d1);
		left = a1 * c1 + b1 * c1 + a1 * d1 + b1 * d1;
		//============================ Assembler =============================
		//Объявить константу для ассемблера
		//__asm{   DENOM_A    EQU  15      };
		// err=0; Нет ошибок
		__asm {   mov    err, 0        };
		// Разделить исходные переменные на знаменатель DENOM
		_asm {
			// a1=a/DENOM+2
			mov    ebx, DENOM + 2
			mov    eax, a
			cdq
			idiv   ebx
			mov    esi, eax};
		_asm {
			// b1=b/DENOM+3
			mov    ebx, DENOM + 3
			mov    eax, b
			cdq
			idiv   ebx
			mov    edi, eax};
		_asm {// c1=c/DENOM+4
			mov    ebx, DENOM + 4
			mov    eax, c
			cdq
			idiv   ebx
			mov    ecx, eax};
		_asm {// d1=d/DENOM+5
			mov    ebx, DENOM + 5
			mov    eax, d
			cdq
			idiv   ebx
			mov    ebx, eax };
		_asm {
			// Вычислить левую часть тождества
			// (a+b)(c+d)  --> left_a
			// Вычислить выражение
			mov eax, esi
			add eax, edi
			mov edx, ecx
			add edx, ebx
			imul eax, edx
			jno    L1
			mov err, 1
			jmp R1
L1 :
			mov left_a, eax
				// Вычислить правую часть тождества
				// ac+bc+ad+bd --> right_a
R1 :
			mov eax, esi
				imul eax, ecx
				jno    R2
				mov err1, 1
				jmp End
R2 :
			mov edx, edi
				imul edx, ecx
				jno    R3
				mov err1, 1
				jmp End
R3 :
			add eax, edx
				jno    R4
				mov err1, 1
				jmp End
R4 :
			mov edx, esi
				imul edx, ebx
				jno    R5
				mov err1, 1
				jmp End
R5 :
			add eax, edx
				jno    R6
				mov err1, 1
				jmp End
R6 :
			mov edx, edi
				imul edx, ebx
				jno    R7
				mov err1, 1
				jmp End
R7 :
			add eax, edx
				jno    End
				mov err1, 1
				jmp End
End :
			mov right_a, eax
		};

		// Вывод результатов
		if (err)
			printf("\n***(Asm)*** Ошибка в левой части выражения");
		else {
			printf("\nЛевая часть тождества ( C ): %li", left);
			printf("\nПравая часть тождества( С ): %li", right);
			printf("\nЛевая часть тождества (Asm): %li", left_a);
			printf("\nПравая часть тождества(Asm): %li\n", right_a);
		}
		if (err1)
			printf("\n***(Asm)*** Ошибка в правой части выражения");
		else {
			printf("\nЛевая часть тождества ( C ): %li", left);
			printf("\nПравая часть тождества( С ): %li", right);
			printf("\nЛевая часть тождества (Asm): %li", left_a);
			printf("\nПравая часть тождества(Asm): %li\n", right_a);
		}
	}
	return 0;
}