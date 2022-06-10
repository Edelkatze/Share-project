#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>


typedef struct matrix {
	int** matrix;
	int row;
	int column;
}MAT;

typedef struct mm {
	MAT ma;
	MAT mb;
}MM;
MAT reseted_m;

int** matrix_setting(MAT mx);

MAT matrix_multiple(MAT ma, MAT mb)
{
	MAT mc;
	mc.row = ma.row;
	mc.column = mb.column;
	mc.matrix = matrix_setting(mc);

	for (int i = 0; i < mc.row; i++)
	{
		for (int j = 0; j < mc.column; j++)
		{
			for (int l = 0; l < mb.row; l++)
			{
				mc.matrix[i][j] += ma.matrix[i][l] * mb.matrix[l][j];
			}
		}
	}

	return mc;
}

MAT matrix_sum(MAT ma, MAT mb, int minus)
{
	MAT mc;
	mc.row = ma.row;
	mc.column = mb.column;
	mc.matrix = matrix_setting(mc);

	for (int i = 0; i < mc.row; i++)
	{
		for (int j = 0; j < mc.column; j++)
		{
			if (minus == 1)
			{
				mc.matrix[i][j] = ma.matrix[i][j] - mb.matrix[i][j];
			}
			else
			{
				mc.matrix[i][j] = ma.matrix[i][j] + mb.matrix[i][j];
			}
		}
	}

	return mc;
}

int** matrix_scala(MAT mx, int n)
{
	for (int i = 0; i < mx.row; i++)
	{
		for (int j = 0; j < mx.column; j++)
		{
			mx.matrix[i][j] *= n;//TODO �м��� ���ϱ� : %d/%d�� �޾Ƽ� ���ڴ� ��Ŀ� ���ϰ� ���ڴ� /%d�� ǥ��
		}//TODO mx�� �ٲ��� �ʰ� ���� ����Ͽ� ���ο� ��ķ� ��ȯ
	}

	return mx.matrix;
}

void matrix_input(MAT mx)
{
	for (int i = 0; i < mx.row; i++)
	{
		for (int j = 0; j < mx.column; j++)
		{
			scanf_s("%d", &mx.matrix[i][j]);
		}
	}
}

void matrix_print(MAT mx, char name)
{
	printf("\n\n\n%c���\n", name);
	for (int i = 0; i < mx.row; i++)
	{
		for (int j = 0; j < mx.column; j++)
		{
			printf("%d ", mx.matrix[i][j]);
		}
		printf("\n");
	}
}

int** matrix_setting(MAT mx)
{
	mx.matrix = malloc(sizeof(int*) * mx.row);

	//if (mx) { memset(mx, 0, sizeof(int)*mx.row); }
	if (mx.matrix)
	{
		memset(mx.matrix, 0, sizeof(int*) * mx.row);
		for (int i = 0; i < mx.row; i++)
		{
			*(mx.matrix + i) = malloc(sizeof(int) * mx.column);//TODO *(������ + i)�� ������[i] ���غ���
			memset(mx.matrix[i], 0, sizeof(int*) * mx.column);
		}
	}
	return mx.matrix;
}

MM create_matrix(MAT ma, MAT mb)
{
	MM result;
	printf("��� A�� ��� ���� ������ �Է��Ͻʽÿ�.\n");

	scanf_s("%d %d", &ma.row, &ma.column);

	printf("\n\n��� B�� ��� ���� ������ �Է��Ͻʽÿ�.\n");


	scanf_s("%d %d", &mb.row, &mb.column);

	ma.matrix = matrix_setting(ma);
	mb.matrix = matrix_setting(mb);

	printf("\n\n��� A�� ��Ҹ� �Է��Ͻʽÿ�.\n\n");
	matrix_input(ma);
	printf("\n\n��� B�� ��Ҹ� �Է��Ͻʽÿ�.\n\n");
	matrix_input(mb);

	system("cls");

	matrix_print(ma, 'A');
	matrix_print(mb, 'B');

	result.ma = ma;
	result.mb = mb;

	return result;
}

void main()
{
	MAT ma = reseted_m;
	MAT mb = reseted_m;//matrix A, B
	MAT mc = reseted_m;
	MM a;
	int sw = 1;
	char trash[50];

	while (sw)
	{
		printf("EdelKatze ��� ���� ���α׷� ver.1 _____ ���� ���� 2022.05.20\n\n\n\n\n");
		printf("[���α׷� ����]\n");
		printf("* ��� ������ �����ϱ� ��, �ݵ�� ���� ����� �������ֽʽÿ�.");
		if (ma.matrix)
		{
			printf("(���� ������)\n\n");
		}
		else
		{
			printf("\n\n");
		}

		printf("[0]����\n[1]��� ����");
		if (ma.matrix) { printf("(����� ����)"); }
		//printf("\n[2]��� �� ����\n[3]��� ���� ����\n[4]��� ��Į�� �� ����\n\n");
		printf("\n[2]��� �� ����\n[3]��� ���� ����\n\n");
		printf("�Է� : ");
		scanf_s("%d", &sw);
		system("cls");
		printf("\n\n\n");
		switch (sw)
		{
		case 1:
			a = create_matrix(ma, mb);
			ma = a.ma;
			mb = a.mb;
			system("pause");
			break;
		case 2:
			if (ma.column == mb.row)
			{
				matrix_print(ma, 'A');
				matrix_print(mb, 'B');
				mc = matrix_multiple(ma, mb);
				printf("\n\n��� ���");
				matrix_print(mc, 'C');
			}
			else
			{
				printf("��� �� ������ �Ϸ���\nù ��° ����� ���� ����\n�� ��° ����� ���� ���� ���ƾ� �մϴ�.");
			}

			system("pause");

			break;
		case 3:
			if (ma.column == mb.column && ma.row == mb.row)
			{
				printf("\n\n[1]��\n[2]��\n\n�Է� : ");
				scanf_s("%d", &sw);

				switch (sw)
				{
				case 1:
					matrix_print(ma, 'A');
					matrix_print(mb, 'B');
					mc = matrix_sum(ma, mb, 0);
					printf("\n\n��� ���");
					matrix_print(mc, 'C');
					break;
				case 2:
					matrix_print(ma, 'A');
					matrix_print(mb, 'B');
					mc = matrix_sum(ma, mb, 1);
					printf("\n\n��� ���");
					matrix_print(mc, 'C');
					break;
				}
			}
			else
			{
				printf("��� ���� ������ �Ϸ���\n�� ����� ��� ���� ���� ���ƾ� �մϴ�.");
			}

			system("pause");

			break;
			/*case 4:
				printf("\n\n� ��Ŀ� ��Į�� ���Ͻðڽ��ϱ�?\n\n[1]��� A\n[2]��� B\n\n\n�Է� : ");
				scanf_s("%d", &sw);
				int reply = 0;
				printf("\n\n� ��Į�� ���Ͻðڽ��ϱ�?(ver.1 : ��Į��� ���� �������� ����)\n\n�Է� : ");
				scanf_s("%d", &reply);
				switch (sw)
				{
				case 1:
					mc.matrix = matrix_scala(ma, reply);
					matrix_print(ma, 'A');
					printf("\n\n��Į�� : %d\n\n��� ���", reply);
					matrix_print(mc, 'C');
					break;
				case 2:
					mc.matrix = matrix_scala(mb, reply);
					matrix_print(mb, 'B');
					printf("\n\n��Į�� : %d\n\n��� ���", reply);
					matrix_print(mc, 'C');
					break;
				}

				printf("\n\n�������� ���ư����� �ƹ��ų� �Է��Ͻʽÿ�.\n\n");
				scanf_s("%s", trash, sizeof(trash));*/
		}
		system("cls");
	}

	for (int i = 0; i < ma.row; i++) { free(ma.matrix[i]); }
	for (int i = 0; i < mb.row; i++) { free(mb.matrix[i]); }
	free(ma.matrix);
	free(mb.matrix);
}