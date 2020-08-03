#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <windows.h> // ���� �ð� ���

using namespace std ;

#define NUM 128  // Ascii code ���

void makeSkip(char *p, int M, int skip[]) // skip �迭 ����
{
	for( int i = 0 ; i < NUM ; i++ ) // skip �迭�� ������ ���̷� ���� (���Ŀ� ���� ���ڿ��� ���� �ִ��� �ǳ� �ٱ� ����)
	{
		skip[i] = M ;
	}

	for( int i = 0 ; i < M ; i++ ) // pattern���� �����ϴ� ���ڿ��� ����
	{
		skip[(int)p[i]] = M - i - 1 ; // pattern�� ���̿��� index��ŭ �� ���� ������ �����Ͽ� skip �迭 ����
	}
}

int BM(char *p, char *t) // ���� ã��
{
	int i, j, k = 0 ;
	int M = strlen(p) ; // ���� ����
	int N = strlen(t) ; // �ؽ�Ʈ ����
	int skip[NUM] ;

	makeSkip(p, M, skip) ; // skip �迭 ����

	for( i = M - 1, j = M - 1 ; j >= 0 ; i--, j-- )
	{
		while( t[i] != p[j] ) // �ؽ�Ʈ�� ���� ����ġ
		{
			k = skip[(int)t[i]] ; // ����ġ �ߴ� ���� �ؽ�Ʈ ���ڿ� �ش��ϴ� index -> skip �迭���� ã�� �� ��ȯ
			
			if( M - j > k ) // M - j �� k�� �� (�� ū ���� i�� ������)
			{
				i = i + M - j ; // M - j�� ũ�ٸ� �� ���� ������
			}else
			{
				i = i + k ; // k�� ũ�ٸ� �� ���� ������
			}

			if (i >= N) // �ؽ�Ʈ ���̸� �Ѵ´ٸ�
			{
				return N ; // �ؽ�Ʈ ���� ��ȯ
			}

			j = M - 1 ;    // j�� �ٽ� ������ �� ������ (���̾� ����� �ڿ��� ���� ��)
		}
	}
	
	return i + 1 ; // ã�� ��� ��ȯ
}

int main()
{
	cout << "12141680 BM" << endl ;

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
		w = BM(p, t + i) ; // ���̾� ����� ���� �߻��� ��ġ -> w�� ����
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