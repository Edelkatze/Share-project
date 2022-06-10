#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct complex_number {
	int a;//Real Part
	int b;//Imagenary part
}CN;

typedef struct complex_numbers {
	CN cn1;
	CN cn2;
}CNs;

int CN_compare(CN z)
{
	int result = 0;//0�̸� 0, 1�̸� �Ǽ�, 2�� �����, 3�̸� ������� �ƴ� ���

	if (z.a && z.b == 0)
		result = 1;
	else if (z.a == 0 && z.b)
		result = 2;
	else if (z.a && z.b)
		result = 3;
	else{}

	return result;
}

void compare_print(CN z, int imaginary)
{
	if (z.b == 1) 
	{ 
		if (imaginary == 0) 
		{ 
			printf("%d", z.a); 
		}
	}
	else 
	{ 
		if (z.b) 
		{ 
			printf("(%d/%d)", z.a, z.b); 
		} 
	}
}

int greatest_common_divisor(int a, int b)
{
	int result = 1, i = 2;

	while (i < (a + b) / 2)
	{
		if (a % i == 0 && b % i == 0)
		{
			a /= i;
			b /= i;
			result *= i;

			i = 2;
		}
		i++;
	}
	return result;
}

CN fraction(int a, int b)
{
	int GCD = 0;//Greatest Common Divisor
	int minus_switch = 1;
	CN result = { a,b };

	if (a == 0)
	{
		result.b = 0;
		return result;
	}

	if (a < 0)
	{
		result.a = -result.a;
		minus_switch *= -1;
	}
	if (b < 0)
	{
		result.b = -result.b;
		minus_switch *= -1;
	}

	if (a % b == 0)
	{
		result.a /= result.b;
		result.b = 1;
	}
	else
	{
		GCD = greatest_common_divisor(result.a, result.b);

		result.a /= GCD;
		result.b /= GCD;
	}

	if (minus_switch == -1)
	{
		result.a *= -1;
	}


	return result;
}

//Complex Number Conjugate
CN CNC(CN z)
{
	z.b = -z.b;

	return z;
}

//Complex Number Multiple
CN CNM(CN z1, CN z2)
{
	return (CN) { z1.a * z2.a - z1.b * z2.b, z1.a * z2.b + z1.b * z2.a };
}

//Complex Number Division
CNs CND(CN z1, CN z2)
{
	CNs result = { {0,0}, {0,0} };
	CN numerator;
	CN denominator;

	if (z1.a == z2.a && z1.b == z2.b && z1.a)//���ڿ� �и� �����鼭 0�� �ƴ� ��
	{
		result.cn1.a = 1;
		result.cn1.b = 1;
		return result;
	}
	else if (z2.b == 0)//�и� �Ǽ��� ��
	{
		result.cn1 = fraction(z1.a, z2.a);
		result.cn2 = fraction(z1.b, z2.a);
	}
	else//�и� ����� ��
	{
		numerator = CNM(z1, CNC(z2));
		denominator = CNM(z2, CNC(z2));

		result.cn1 = fraction(numerator.a, denominator.a);
		result.cn2 = fraction(numerator.b, denominator.a);
	}

	return result;
}

//Complex Number Sum
CN CNS(CN z1, CN z2, int mode)
{
	CN z;

	if (mode == 0)
	{
		z.a = z1.a + z2.a;
		z.b = z1.b + z2.b;
	}
	else
	{
		z.a = z1.a - z2.a;
		z.b = z1.b - z2.b;
	}

	return z;
}

//Complex Number Squared
CN CNSq(CN z)
{
	CN result;

	result = CNM(z, z);

	return result;
}

//Complex Number Print
void CNP(CN z)
{
	int cnt = CN_compare(z);//complex number type

	switch (cnt)
	{
	case 0:
		printf("0");
		break;
	case 1:
		printf("%d", z.a);
		break;
	case 2:
		if (z.b == 1) { printf("i"); }
		else if (z.b == -1) { printf("-i"); }
		else { printf("%di", z.b); }
		break;
	case 3:
		if (z.b > 0)
		{
			if (z.b == 1) { printf("%d+i", z.a); }
			else { printf("%d+%di", z.a, z.b); }
		}
		else
		{
			if (z.b == -1) { printf("%d-i", z.a); }
			else { printf("%d%di", z.a, z.b); }
		}
		break;
	}

	printf("\n");
}

//Complex Numbers Print
void CNsP(CNs zz)
{
	if (zz.cn1.a < 0)
	{
		printf("-");
		zz.cn1.a *= -1;
	}
	compare_print(zz.cn1, 0);
	if (zz.cn2.a && zz.cn2.b)
	{
		if (zz.cn2.a > 0 && zz.cn2.a != 1) { printf("+"); }
		else if(zz.cn2.a < 0)
		{ 
			printf("-");
			zz.cn2.a *= -1;
		}
		compare_print(zz.cn2, 1);
		if (zz.cn2.a && zz.cn2.b) { printf("i"); }
	}

	printf("\n");
}

int main()
{
	CN z1 = { 0,0 };
	CN z2 = { 0,0 };
	
	printf("���Ҽ��� ���� | EdelKatze\n\n�� ���� ���Ҽ��� �Է��ϼ���\n#��, a+bi�� ���� �÷� �Է�\n#i�� ����� 0 �Ǵ� 1������ �������� �� ��\n____\n");

	scanf_s("%d %di", &z1.a, &z1.b);
	scanf_s("%d %di", &z2.a, &z2.b);

	printf("\n\n\n");
	printf("  ���� : ");
	CNP(CNS(z1, z2, 0));
	printf("  ���� : ");
	CNP(CNS(z1, z2, 1));
	printf("  ���� : ");
	CNP(CNM(z1, z2));
	printf("������ : ");
	CNsP(CND(z1, z2));
	printf("���� 1 : ");
	CNP(CNSq(z1));
	printf("     2 : ");
	CNP(CNSq(z2));
	printf("�ӷ� 1 : ");
	CNP(CNC(z1));
	printf("     2 : ");
	CNP(CNC(z2));

	/*
	
	CNS(CN z1, CN z2, int mode) : ���Ҽ� ����. mode�� 0�̸� ����, �ƴϸ� ������ �Ѵ�.
	
	CNM(CN z1, CN z2) : ���Ҽ� ����.

	CND(CN z1, CN z2) : ���Ҽ� ������. z1�� z2�� ������.
	
	CNSq(CN z) : ���Ҽ� ����.
	
	CNC(CN z) : �ӷ� ���Ҽ�.
	
	CNP(CN z) : ���Ҽ� ���. �Ǽ��ο� ������� ����� ������ ���� ���.
	
	CNsP(CNs zz) : ���Ҽ� ���. �Ǽ��ο� ������� ����� ���� or �м��� �� ���. CNs ����ü�� CND������ ��ȯ�ϹǷ� ������������ ����.
	
	*/

	system("pause");

	return 0;
}