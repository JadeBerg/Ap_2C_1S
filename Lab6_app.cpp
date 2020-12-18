//+===================================================================
// Lab_6_Ap.cc
// �������� ������� �����
//
// ��� ��������� ����������� ������� ������ � ������ ����������� �����
 //
// (C) ������ �.�., 2020
//
// ������� ������:
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
// �������� ������:
// ������� ����� ����������� �����, ������� �������� ��������� ������� ������
//	31----+-----+-----+-----+--------0
//	! mod ! r_m ! kop ! cond ! range ! value 	
//	+-----+-----+-----+-----+--------+
//	  2	     6	   12	 10      2
//-===================================================================
#include <iostream>
#include <locale.h>
#include <iomanip>
using namespace std;

unsigned char mod, r_m, mod_a, r_m_a, range_a, range;
unsigned short kop, cond, kop_a, cond_a;
unsigned long value, value_a;
unsigned short tmp;
int main()
{
	setlocale(LC_ALL, "Rus");
	cout << "\n\t\t(C) ������ �.�., 2020"
		<< "\n\t\t���������� ������� �����"
		<< "\n\t��������� ������� ������, ������������ � ����� ������,"
		<< "\n\t\t� 32-������� ����� ����� Value";
	for (;;)
	{
		cout << "\n����������, ������� 1 16-� ����� ��� range (��������, 1):";
		cin >> hex >> tmp;
		range = tmp;
		cout << "����������, ������� 3 16-� ����� ��� cond (��������, 14e):";
		cin >> cond;
		cout << "����������, ������� 3 16-� ����� ��� kop (��������, 8e7):";
		cin >> kop;
		cout << "����������, ������� 2 16-� ����� ��� r_m (��������, 9db):";
		cin >> hex >> tmp;
		r_m = tmp;
		cout << "����������, ������� 1 16-�� ����� ��� mod (��������,5):";
		cin >> hex >> tmp;
		mod = tmp;


		// ������� ����� �������� ����� ��� �������� �� ����������
		mod_a = mod;
		r_m_a = r_m;
		kop_a = kop;
		cond_a = cond;
		range_a = range;
		//=============================== C ==================================
		// �������� ������� ���� � ������ �������� �����
		range &= 0x3; // �������� ��� ���� � �����, ����� 2 ������� (1-0)
		cond &= 0x3ff; // �������� ��� ���� � �����, ����� 10 ������� (11-2)
		kop &= 0xfff; // �������� ��� ���� � �����, ����� 12 ������� (23-12)
		r_m &= 0x3f; // �������� ��� ���� � �����, ����� 6 ������� (29-24)
		mod &= 0x3; // �������� ��� ���� � �����, ����� 2 ������� (31-30)
		// ���������� ������ ������� ���� � �������������� ������ Value
		value = mod; // ���������� ���� mod � value
		value = (value << 6) | r_m; // ���������� ���� r_m � value
		value = (value << 12) | kop; // ���������� ���� kop � value
		value = (value << 10) | cond; // ���������� ���� cond � value
		value = (value << 2) | range; // ���������� ���� range � value
	 //============================ Assembler =============================
	 // ��������� ������� ������
		__asm {
			// �������� ������� ���� � ������ �������� �����
			and range_a, 0x3
			and cond_a, 0x3ff
			and kop_a, 0xfff
			and r_m_a, 0x3f
			and mod_a, 0x3
			xor eax, eax
			// ���������� ���� mod � value
			or al, mod_a
			shl eax, 6
			// ���������� ���� r_m � value
			or al, r_m_a
			shl eax, 12
			// ���������� ���� kop � value
			or ax, kop_a
			shl eax, 10
			// ���������� ���� cond � value
			or ax, cond_a
			shl eax, 2
			// ���������� ���� range � value
			or al, range_a
			mov value_a, eax
		};
		// ��������� ����� �����������
		cout << hex
			<< "�������������� ����������� ����� (C++): " << value
			<< "\n�������������� ����������� ����� (Asm): " << value_a
			<< endl;
	};
	return 0;
}