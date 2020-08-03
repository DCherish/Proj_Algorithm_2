#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <windows.h> // ���� �ð� ���

using namespace std ;

int* makeNext(char *p, int M) // next �迭 ����
{
	int *next = new int[M] ;

	for( int i = 0 ; i < M ; i++ ) // next �迭 �ʱ�ȭ
	{
		next[i] = 0 ; // 0���� �ʱ�ȭ
	}

	for( int i = 0 ; i < M ; i++ )
	{
		next[0] = -1 ; // next[0] = -1 (����)

		for( int i = 0, j = -1 ; i < M - 1 ; i++, j++ )
		{
			if( j != -1 )
			{
				if( p[i] == p[j] )
				{
					next[i] = next[j] ; // ������ ���� ���� ��ġ ����
				}else
				{
					next[i] = j ; // ������ ���� ���� ��ġ ����
				}

				while( j >= 0 && p[i] != p[j] ) // ������ �ٸ��ٸ�
				{
					j = next[j] ; // j = next[j]�� �̵�
				}
			}
		}
	}

	return next ;
}

int KMP(char *p, char *t, int M, int N) // KMP (���ڿ� ��)
{
	int i = 0 ;
	int j = 0 ;
	int *next = makeNext(p, M) ; // next �迭 ����

	for( i = 0 ; i < N ; i++ )
	{
		while( j >= 0 && t[i] != p[j] && j != M ) // ���ϰ� �ؽ�Ʈ�� �ٸ��ٸ� (������ while�� ���� ����)
		{
			j = next[j] ; // j = next[j]�� �̵�
		}

		j++ ; // j�� ����

		if( j == M ) // ������ �߰��ߴٸ�																																																																						
		{
			break ; // break
		}
	}

	if( j == M ) // ������ �߰��ߴٸ�
	{
		return (i - M + 1) ; // �� ��ġ�� return
	}
	else // �߰����� ���ߴٸ�
		return i ; // ���� �ؽ�Ʈ�� ���̷� return 
}


int main()
{
	cout << "12141680 KMP" << endl ;

	ifstream file("RFCDDDD.txt") ; // �ؽ�Ʈ ���� open

	string text ;
	string pattern ;

	LARGE_INTEGER BeginTime, EndTime, Frequency ; // ���� �ð� ����
	double Time ; // ���� �ð� ����

	int M, N, w, b = 0, i = 0 ;

	while (!file.eof()) // ������ ������
	{
		string _line;
		getline(file, _line) ; // �� �� �پ� ����
		text.append(_line) ; // �� ���� text�� �߰�
		text.append("\n") ; // text �� �ٲ�
	}

	cout << "pattern : " ;
	getline(cin, pattern) ; // ������ �Է�

	M = pattern.length() ; // ������ ���� 
	N = text.length() ; // �ؽ�Ʈ�� ����

	char* t = new char[N + 1] ;
	char* p = new char[M + 1] ;

	strcpy_s(t, N + 1, text.c_str()) ; // text�� t�� �� ���ھ� ����
	strcpy_s(p, M + 1, pattern.c_str()) ; // pattern�� p�� �� ���ھ� ����

	QueryPerformanceFrequency(&Frequency) ;
	QueryPerformanceCounter(&BeginTime) ; // �ð� ���� ����

	for(;;)
	{
		w = KMP(p, t + i, M, N) ; // KMP�� ���� �߻��� ��ġ -> w�� ����
		w = w + b ; // w�� ��ġ�� ���� ���� �߻��� ������ ���� ������ ��
		i = w + M ; // ���� �߻��� �� + ���� ���� -> �� ��ġ���� �ٽ� �����ؾ���
		if( i <= N ) // �ؽ�Ʈ�� ���̸� �Ѿ� �� �� ����
		{
			cout << "Pattern, Where ? : " << w << endl ; // ���� ��ġ ���
		}else
		{
			break ;
		}
		b = i ; // �߻� �ߴ� �� ��ġ�� ���� (���� ���� ��� �� ���)
	}

	QueryPerformanceCounter(&EndTime) ; // ���� ����
	cout << "Pattern Finish" << endl ;
	Time = (double)(EndTime.QuadPart - BeginTime.QuadPart) / Frequency.QuadPart ; // ���� �ð�

	cout << "Elapsed Time : " << Time << "ms" << endl ; // ���� �ð� ���

	return 0 ;
}