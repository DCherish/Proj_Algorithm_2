#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <windows.h> // 실행 시간 계산

using namespace std ;

int* makeNext(char *p, int M) // next 배열 생성
{
	int *next = new int[M] ;

	for( int i = 0 ; i < M ; i++ ) // next 배열 초기화
	{
		next[i] = 0 ; // 0으로 초기화
	}

	for( int i = 0 ; i < M ; i++ )
	{
		next[0] = -1 ; // next[0] = -1 (고정)

		for( int i = 0, j = -1 ; i < M - 1 ; i++, j++ )
		{
			if( j != -1 )
			{
				if( p[i] == p[j] )
				{
					next[i] = next[j] ; // 개선된 유한 상태 장치 구현
				}else
				{
					next[i] = j ; // 개선된 유한 상태 장치 구현
				}

				while( j >= 0 && p[i] != p[j] ) // 패턴이 다르다면
				{
					j = next[j] ; // j = next[j]로 이동
				}
			}
		}
	}

	return next ;
}

int KMP(char *p, char *t, int M, int N) // KMP (문자열 비교)
{
	int i = 0 ;
	int j = 0 ;
	int *next = makeNext(p, M) ; // next 배열 생성

	for( i = 0 ; i < N ; i++ )
	{
		while( j >= 0 && t[i] != p[j] && j != M ) // 패턴과 텍스트가 다르다면 (같으면 while문 들어가지 않음)
		{
			j = next[j] ; // j = next[j]로 이동
		}

		j++ ; // j를 증가

		if( j == M ) // 패턴을 발견했다면																																																																						
		{
			break ; // break
		}
	}

	if( j == M ) // 패턴을 발견했다면
	{
		return (i - M + 1) ; // 그 위치를 return
	}
	else // 발견하지 못했다면
		return i ; // 원래 텍스트의 길이로 return 
}


int main()
{
	cout << "12141680 KMP" << endl ;

	ifstream file("RFCDDDD.txt") ; // 텍스트 파일 open

	string text ;
	string pattern ;

	LARGE_INTEGER BeginTime, EndTime, Frequency ; // 실행 시간 측정
	double Time ; // 실행 시간 측정

	int M, N, w, b = 0, i = 0 ;

	while (!file.eof()) // 파일의 끝까지
	{
		string _line;
		getline(file, _line) ; // 각 한 줄씩 읽음
		text.append(_line) ; // 한 줄을 text에 추가
		text.append("\n") ; // text 줄 바꿈
	}

	cout << "pattern : " ;
	getline(cin, pattern) ; // 패턴을 입력

	M = pattern.length() ; // 패턴의 길이 
	N = text.length() ; // 텍스트의 길이

	char* t = new char[N + 1] ;
	char* p = new char[M + 1] ;

	strcpy_s(t, N + 1, text.c_str()) ; // text를 t에 한 글자씩 복사
	strcpy_s(p, M + 1, pattern.c_str()) ; // pattern을 p에 한 글자씩 복사

	QueryPerformanceFrequency(&Frequency) ;
	QueryPerformanceCounter(&BeginTime) ; // 시간 측정 시작

	for(;;)
	{
		w = KMP(p, t + i, M, N) ; // KMP로 패턴 발생한 위치 -> w에 저장
		w = w + b ; // w의 위치는 전에 패턴 발생한 곳으로 부터 떨어진 곳
		i = w + M ; // 패턴 발생한 곳 + 패턴 길이 -> 그 위치에서 다시 시작해야함
		if( i <= N ) // 텍스트의 길이를 넘어 갈 수 없음
		{
			cout << "Pattern, Where ? : " << w << endl ; // 패턴 위치 출력
		}else
		{
			break ;
		}
		b = i ; // 발생 했던 곳 위치를 저장 (다음 패턴 장소 때 고려)
	}

	QueryPerformanceCounter(&EndTime) ; // 측정 종료
	cout << "Pattern Finish" << endl ;
	Time = (double)(EndTime.QuadPart - BeginTime.QuadPart) / Frequency.QuadPart ; // 실행 시간

	cout << "Elapsed Time : " << Time << "ms" << endl ; // 실행 시간 출력

	return 0 ;
}