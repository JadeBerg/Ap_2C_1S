//+===================================================================
// File Lab_7.cpp
// ����������� ���������, ���������� � ��������
// ������� 15
// ������� ����� ������������������ ������ ������ ������������� ��������� �������.
// ����� ������ � ��� ������ �������� �� ����� in.txt
//
// (C) ������ �.�., 2020
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
	printf("\n\t\t(C) ������ �.�., 2020\n");
	// ������� ���� � ��������� �������
	if ((fin = fopen("in.txt", "r")) == NULL)
	{
		printf("\n���������� ������� ����!!\n");
		exit(1);
	}
	for (;;)
	{
		int i, count = 0, maxCount = 0, count_a = 0, maxCount_a = 0;
		// ������ ����� ������
		fscanf_s(fin, "%i\n", &len);
		// ���� ������ ����� ��������� � ���������� �����, ������ ���
		if (len == 0 || len > 100) {
			printf("\t\t������������ ����� �������!\n");
			break;
		}
		// ���������� ���� � ������
		for (i = 0; i < len; i++) 
			fscanf_s(fin, "%i", &arr[i]);
		// ������� ����� ��� ����������
		for (i = 0; i < len; i++) 
			arr_a[i] = arr[i];
		//=============================== C ==================================
		// ����� ��������� �������
		printf("\n�������� ����� ����� �����: %i\n", len);
		for (i = 0; i < len; i++) 
			printf("%8i", arr[i]);
		// ����� ����� ������������������ ������ ������ ������������� ��������� �������.
		for (i = 0; i < len; i++) {
			if (arr[i] < 0) {
				count++;
				if (count > maxCount)
					maxCount = count;
			}
			else
				count = 0;
			}
		// ����� ����� ������������������ ������ ������ ������������� ��������� �������.
		printf("\n����� ������������������ ������ ������ ������������� ��������� ������� ( C )\n");
		printf("%d", maxCount);
		//============================ Assembler =============================
__asm {
		mov ebx, count_a
        // for (i=0; i<len; i++)
        // i = 0
		xor esi, esi
		mov ecx, len
L0 :
        // �������� ������� i<len
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
		// ����� �����������
		printf("\n����� ������������������ ������ ������ ������������� ��������� ������� (Asm)\n");
		printf("%d", maxCount_a);
		printf("\n");
		break;
	}
	// ������� �������� ����
	fclose(fin);
	return 0;
}