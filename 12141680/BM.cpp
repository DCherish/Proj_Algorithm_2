#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <windows.h> // 실행 시간 계산

using namespace std ;

#define NUM 128  // Ascii code 계산

void makeSkip(char *p, int M, int skip[]) // skip 배열 생성
{
	for( int i = 0 ; i < NUM ; i++ ) // skip 배열을 패턴의 길이로 설정 (추후에 없던 문자열에 대해 최대한 건너 뛰기 위함)
	{
		skip[i] = M ;
	}

	for( int i = 0 ; i < M ; i++ ) // pattern내에 존재하는 문자열에 대해
	{
		skip[(int)p[i]] = M - i - 1 ; // pattern의 길이에서 index만큼 뺀 값을 각각에 저장하여 skip 배열 생성
	}
}

int BM(char *p, char *t) // 패턴 찾기
{
	int i, j, k = 0 ;
	int M = strlen(p) ; // 패턴 길이
	int N = strlen(t) ; // 텍스트 길이
	int skip[NUM] ;

	makeSkip(p, M, skip) ; // skip 배열 생성

	for( i = M - 1, j = M - 1 ; j >= 0 ; i--, j-- )
	{
		while( t[i] != p[j] ) // 텍스트와 패턴 불일치
		{
			k = skip[(int)t[i]] ; // 불일치 했던 곳의 텍스트 문자에 해당하는 index -> skip 배열에서 찾은 후 반환
			
			if( M - j > k ) // M - j 와 k를 비교 (더 큰 값을 i에 더해줌)
			{
				i = i + M - j ; // M - j가 크다면 이 값을 더해줌
			}else
			{
				i = i + k ; // k가 크다면 이 값을 더해줌
			}

			if (i >= N) // 텍스트 길이를 넘는다면
			{
				return N ; // 텍스트 길이 반환
			}

			j = M - 1 ;    // j는 다시 패턴의 맨 끝으로 (보이어 무어는 뒤에서 부터 비교)
		}
	}
	
	return i + 1 ; // 찾은 장소 반환
}

int main()
{
	cout << "12141680 BM" << endl ;

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
		w = BM(p, t + i) ; // 보이어 무어로 패턴 발생한 위치 -> w에 저장
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