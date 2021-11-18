#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define D double					//����
#define SIZE 40						//ũ��
#define SIZE_SQUARED SIZE * SIZE	//ũ���� ����
#define SEED_MIN 0					//seed �ּڰ�
#define SEED_MAX 10					//seed �ִ�
#define NUM_MAX	1000				//������ �ִ�

double least[2];
double largest[2];

D root(D num)
	{
		int IDV = -1; //Increase Decrease Variable ���� ����, 0�̸� ����, 1�̸� ����. ������ ��� ���ǿ� ������ Ȯ���Ѵ�.
		D m = 1; //a�� �� ����
		D a = 1; //�������� �� ����
		D aa; //a�� ����

		if (num == 0)
		{
			return 0;
		}

		for (int i = 0; i < SIZE_SQUARED; i++)
		{
			aa = a * a;
			if (aa == num)
			{
				break;
			}
			else if (aa > num)
			{
				if (!(IDV == 0))
				{
					m *= 0.1;
				}
				a -= m;
				IDV = 0;
			}
			else if (aa < num)
			{
				if (IDV == 0)
				{
					m *= 0.1;
				}
				a += m;
				IDV = 1;
			}
		}

		return a;
	}
	//��Ʈ �Լ�

D squared(D num)
	{
		return num * num;
	}
	//���� �Լ�

D sum_arr(D * arr, double size)
	{
		D num = 0;

		for (int i = 0; i < (int)size; i++)
		{
			num += arr[i];
		}

		return num;
	}
	//�迭�� ���� �Լ�

D* population(int seed)
	{
		D* arr = (D*)malloc(sizeof(D) * (SIZE_SQUARED + 1));//������. ������ ��Ҵ� size
		int a = 0;
		if (arr)
		{
			arr[SIZE_SQUARED] = 0;
		}

		srand(seed);//seed�� �ʱ�ȭ

		if (arr)//NULL üũ
		{
			for (int i = 0; i < SIZE_SQUARED; i++)//������ ���� ����
			{
				a = rand() % NUM_MAX;
				arr[i] = (double)a;
				arr[SIZE_SQUARED]++;
			}
		}

		return arr;
	}
	//������ ���� �Լ�

D standard_deviation(D * arr, double size, int seed)
	{
		D m = 0;//���
		D sigma_squared = 0;//�л�
		D sigma = 0;//ǥ�� ����

		m = sum_arr(arr, arr[(int)size]);
		m /= size;

		for (int i = 0; i < size; i++)
		{
			arr[i] -= m;
			arr[i] = squared(arr[i]);
		}

		sigma_squared = sum_arr(arr, arr[(int)size]);
		sigma_squared /= size;

		sigma = root(sigma_squared);

		
		printf("Seed : %d\n", seed);
		printf("��� = %.5lf\n", m);
		printf("�л� = %.5lf\n", sigma_squared);
		printf("ǥ�� ���� = %.5lf\n\n", sigma);
		
		if (sigma > largest[0]) { largest[0] = sigma; largest[1] = seed; }
		if (sigma < least[0]) { least[0] = sigma; least[1] = seed; }


		return sigma;
	}
	//ǥ�� ���� �Լ�

D standard_deviation_s(D* arr, double size)
{
	D m = 0;//���
	D sigma_squared = 0;//�л�
	D sigma = 0;//ǥ�� ����

	m = sum_arr(arr, arr[(int)size]);
	m /= size;

	for (int i = 0; i < size; i++)
	{
		arr[i] -= m;
		arr[i] = squared(arr[i]);
	}

	sigma_squared = sum_arr(arr, arr[(int)size]);
	sigma_squared /= size;

	sigma = root(sigma_squared);

	return sigma;
}

void main()
{
	D* sigma_arr = (D*)malloc(sizeof(D) * (SEED_MAX - SEED_MIN + 2));
	D* arr = NULL;
	D meta_standard_deviation = 0;
	D m_sigma = 0;//ǥ�� �������� ���

	least[0] = SIZE_SQUARED;

	if (sigma_arr)
	{
		sigma_arr[SEED_MAX - SEED_MIN + 1] = 0;

		printf("\n\n");
		for (int i = SEED_MIN; i <= SEED_MAX; i++)
		{
			arr = population(i);//������ ����
			sigma_arr[i - SEED_MIN] = standard_deviation(arr, arr[SIZE_SQUARED], i);//�������� ǥ�� ����
			//printf("%.10lf\n", sigma_arr[i - SEED_MIN]);//������ ǥ�� ���� ���
			sigma_arr[SEED_MAX - SEED_MIN + 1]++;
			//printf("In progress %d / %d\r", i - SEED_MIN + 1, SEED_MAX - SEED_MIN + 1);
			free(arr);
		}

		//system("cls");

		m_sigma = sum_arr(sigma_arr, sigma_arr[SEED_MAX - SEED_MIN + 1]);
		m_sigma /= sigma_arr[SEED_MAX - SEED_MIN + 1];

		meta_standard_deviation = standard_deviation_s(sigma_arr, sigma_arr[SEED_MAX - SEED_MIN + 1]);

		printf("\n\nSeed : %d ~ %d\n", SEED_MIN, SEED_MAX);
		printf("ǥ�� ������ ��� = %.10lf\n", m_sigma);
		printf("��Ÿ ǥ�� ���� = %.10lf\n", meta_standard_deviation);
		printf("ǥ�� ������ �ּڰ� = %.10lf, Seed : %.lf\n", least[0], least[1]);
		printf("ǥ�� ������ �ִ� = %.10lf, Seed : %.lf\n", largest[0], largest[1]);
	}

	free(sigma_arr);
}