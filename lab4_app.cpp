﻿//+===================================================================
// File lab4_app.cpp
// Распаковка битовых групп
	// Эта программа распаковывает битовые группы из целого беззнакового числа
	// (C) Струна В.Р., 2020
	//
	// Входные данные:
	// Длинное целое число, которое содержит несколько битовых групп 	
	//	31----+-----+-----+-----+--------0
	//	! mod ! r_m ! kop ! cond ! range ! value 	
    //	+-----+-----+-----+-----+--------+
	//	  2	     6	   12	 10      2
	//
	// Выходные данные:
	//	1----0------0	
	//	! 00 !	mod !	mod
	//	+----+------+	
	//	2
	//	11---2------0	
	//	! 00 !	r_m !	r_m
	//	+----+------+	
	//	6	
	//	23---12-----0	
	//	! 00 !	kop !	kop
	//	+----+------+	
	//	12
	//	29---24------0
	//	! 00 !	cond !	cond
	//	+----+-------+
	//	10
    // 	31---30-------0
	//	! 00 !	range !	range
	//	+----+-------+
    //  2
	//-===================================================================
	#include <iostream>
	#include <iomanip>
    #include <locale.h>
using namespace std;
unsigned long	value;
unsigned char mod, r_m, mod_a, r_m_a, range_a, range;
unsigned short kop, cond, kop_a, cond_a;
int main()
{
	setlocale(LC_ALL, "Rus");
	printf("\n\t\t(C) Струна В.Р., 2020");
	printf("\n\tРаспаковка битовых групп"); 
	for (;;)
		{
		printf("\n\tРаспаковать 32-битовое число Value");
		printf("\nПожалуйста, введите 8 16-ых цифр (например, 5a9db8e4) : ");
		scanf_s("%x", &value);
		//=============================== C ==================================
		// Выделить битовые группы из числа Value
		range = value & 0x3;// выделить 2 младших бита (1-0) из Value 	
		cond = (value >> 2) & 0x3ff;// выделить 10 битов (11-2) из Value 		
		kop = (value >> 12) & 0xfff;// выделить	12 битов (23-12) из Value 		
		r_m = (value >> 24) & 0x3f;// выделить 6 битов (29-24) из Value
		mod = (value >> 30) & 0x3;// выделить 2 бита (31-30) из Value 
		//============================ Assembler =============================
		// Выделить битоые группы из числа Value
		_asm{
		mov	eax,value
		// выделить 2 младших бита(1-0) из Value 
		mov	range_a,al
		and range_a,0x3
		shr	eax,2
		// выделить 10 битов (11-2)	из Value
		mov	cond_a,ax
		and cond_a,0x3ff
		shr	eax,10
		// выделить	12 битов (23-12) из Value
		mov kop_a,ax
		and kop_a,0xfff
		shr	eax,12
		// выделить	6 битов (29-24) из Value
		mov	r_m_a,al
		and r_m_a,0x3f
		shr	eax, 6
		// выделить	2 бита (31-30) из Value
		mov	mod_a, al
		and mod_a, 0x3
		};
		// Форматный вывод результатов 	
		cout << hex << "Битовая группа mod (C++): " << (int)mod
			<< "\nБитовая группа r_m (C++): " << (int)r_m
			<< "\nБитовая группа kop (C++): " << (int)kop
			<< "\nБитовая группа cond (C++): " << (int)cond
			<< "\nБитовая группа range (C++): " << (int)range
			<< "\nБитовая группа mod (Asm): " << (int)mod_a
			<< "\nБитовая группа r_m (Asm): " << (int)r_m_a
			<< "\nБитовая группа kop (Asm): " << (int)kop_a
			<< "\nБитовая группа cond (Asm): " << (int)cond_a
			<< "\nБитовая группа range (Asm): " << (int)range_a
			<< endl;
		};
	return 0;
	}
