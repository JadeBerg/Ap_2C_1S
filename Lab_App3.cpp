//+===================================================================
// File Lab_App3.cpp
	// Ветвящаяся программа
	// Вариант 15
	// Эта программа вычисляет условное арифметическое выражение 
	//	{ (3*a-5)/b, a>b }
	// Х = < -4, a=b >
	//	{ (a^3+b)/a, a<b }
	// где a=a/(15+2), b=b/(15+3)
	//
	// (C) Струна В.Р., 2020
	//-===================================================================
#include <stdio.h>
#include <locale.h>
#include <math.h>
#define	VAR	15
long int a, a1, b, b1, x, x_a; 	
int err; // Ошибка в выражении на С
int err_a ; // Ошибка в выражении на асcемблере
int main()
{
	setlocale(LC_ALL, "Rus");
	printf("\n\t(C) Струна В.Р., 2020");
	for (;;)
	{
		printf("\n\tВычислить выражение:");
		printf("\n\t    { (3*a-5)/b, a<b }");
		printf("\n\tХ = <   -4,      a=b >");
		printf("\n\t    { (a^3+b)/a, a>b }");
		printf("\n\tгде a=a/17, b=b/18");
		printf("\nПожалуйста, введите целые числа A: ");
		scanf_s("%li", &a);
		printf("\nПожалуйста, введите целые числа B: ");
		scanf_s("%li", &b);
//=============================== C ==================================
	// Разделить исходные переменные
		err = 0;
		a1 = a/(VAR+2);
		b1 = b/(VAR + 3);
	// Вычислить выражение 
	// (a==b)?
		if (a1 == b1)
			x = -4;
	// (a<b)?
		if (a1 < b1)
			{
				if (b1 == 0)
					err = 1;
				else
					x = (3 * a1 - 5) / b1;
			}
	// (a>b)?
		if (a1 > b1)
			{
				if (a1 == 0)
					err = 1;
				else
					x = (pow(a1,3)+b1)/a1;
			};
//============================ Assembler =============================
		_asm {
			// err_a = 0 - нет ошибок
			mov err_a, 0
			// Разделить исходные переменные на знаменатель VAR 
			//a1 = a / VAR + 2
			mov ebx, VAR + 2
			mov eax, a
			cdq
			idiv ebx
			mov esi, eax
		}
		_asm{
			//b1 = b / VAR + 3
			mov ebx, VAR + 3
			mov eax, b
			cdq
			idiv ebx
			mov edi, eax
		}
		_asm {
			// Вычислить выражение 
			// if (a1==b1)
			cmp esi, edi
			je Equal
			jl Less
		Greater :
			// if (a1==0) err_a = 1
			test esi, esi
			je Error
			// else x = (pow(a1,3)+b1)/a1;
			mov eax, esi
			imul eax, eax
			jno P1
			mov err_a, 2
			jmp End
		P1:
			imul eax, esi
			jno P2
			mov err_a, 2
			jmp End
		P2:
			add eax, edi
			jno P3
			mov err_a, 2
			jmp End
		P3:
			cdq
			idiv esi
			jmp Save
		Equal :
			// x = -4
			mov eax, 4
			neg eax
			jmp Save
		Less:
			// if (b1==0) err_a = 1
			test edi,edi
			je Error
			// else x = (3 * a1 - 5) / b1;
			mov eax,esi
			imul eax, 3
			sub eax,5
			cdq
			idiv edi
			jmp Save
		Save:
			// eax -> x 
			mov x_a, eax
		    jmp End
		Error:
			inc err_a
		End:
		}
	// Вывод результатов if (err)
		if (err == 1)
			printf("***( C )*** Ошибка: попытка деления на 0\n");
		else if (err_a == 2)
			printf("Ошибка: переполнение\n");
		else
		    printf("Результат ( C ): %li\n", x);
		if (err_a == 1)
			printf("***(Asm)*** Ошибка: попытка деления на 0\n");
		else if (err_a == 2)
			printf("Ошибка: переполнение\n");
		else
			printf("Результат (Asm): %li\n", x_a);
	}
	return 0;
}