//+===================================================================
// File Lab_7.cpp
// Циклическая программа, работающая с массивом
// Вариант 15
// Находит длину последовательности подряд идущих отрицательных элементов массива.
// Длина масива и сам массив вводятся из файла in.txt
//
// (C) Струна В.Р., 2020
//-===================================================================
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#define MAX_LENGTH 100
long int arr[MAX_LENGTH], arr_a[MAX_LENGTH];
int len;
int main()
{
	setlocale(LC_ALL, "Rus");
	FILE* fin;
	errno_t err;
	printf("\n\t\t(C) Струна В.Р., 2020\n");
	// Открыть файл с исходными данными
	if ((fin = fopen("in.txt", "r")) == NULL)
	{
		printf("\nНевозможно открыть файл!!\n");
		exit(1);
	}
	for (;;)
	{
		int i, count = 0, maxCount = 0, count_a = 0, maxCount_a = 0;
		// Читать длину масива
		fscanf_s(fin, "%i\n", &len);
		// Если массив имеет ненулевую и допустимую длину, читать его
		if (len == 0 || len > 100) {
			printf("\t\tНедопустимая длина массива!\n");
			break;
		}
		// Копировать файл в массив
		for (i = 0; i < len; i++) 
			fscanf_s(fin, "%i", &arr[i]);
		// Сделать копию для ассемблера
		for (i = 0; i < len; i++) 
			arr_a[i] = arr[i];
		//=============================== C ==================================
		// Вывод исходного массива
		printf("\nИсходный масив имеет длину: %i\n", len);
		for (i = 0; i < len; i++) 
			printf("%8i", arr[i]);
		// Найти длину последовательности подряд идущих отрицательных элементов массива.
		for (i = 0; i < len; i++) {
			if (arr[i] < 0) {
				count++;
				if (count > maxCount)
					maxCount = count;
			}
			else
				count = 0;
			}
		// Вывод длины последовательности подряд идущих отрицательных элементов массива.
		printf("\nДлина последовательности подряд идущих отрицательных элементов массива ( C )\n");
		printf("%d", maxCount);
		//============================ Assembler =============================
__asm {
		mov ebx, count_a
        // for (i=0; i<len; i++)
        // i = 0
		xor esi, esi
		mov ecx, len
L0 :
        // проверка условия i<len
		cmp esi, ecx 
		jnl End
        // if(arr[i]<0) {
		cmp[arr_a + esi * 4], 0
		jl L1
		mov ebx,0
        //i++
		inc esi
		jmp L0
        //arr[i]<0
L1 :
        //count_a++;
		inc ebx
		inc esi
        // if (count_a > maxCount_a)
		cmp ebx, maxCount_a
		jg L2
		jmp L0
        //maxCount_a = count_a;
L2:
		mov maxCount_a, ebx
		jmp L0
End :
		};
		// Вывод результатов
		printf("\nДлина последовательности подряд идущих отрицательных элементов массива (Asm)\n");
		printf("%d", maxCount_a);
		printf("\n");
		break;
	}
	// Закрыть исходный файл
	fclose(fin);
	return 0;
}