#include<iostream>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
#define MAX 100
char left_parse[MAX] = { "" };

char seek(char stack[]) {
	return stack[strlen(stack) - 1];
}

void pop(char stack[]) {
	if (strlen(stack) == 0)
		exit(1);
	stack[strlen(stack)-1] = NULL;
}

void push(char stack[], char input) {
	stack[strlen(stack)] = input;
}

void rule(char stack[], int prulenumber) {
	stack[strlen(stack) - 1] = NULL; //먼저 stack의 top에 있는 nonterminal 제거하고

	switch (prulenumber) {
	case 1:
		strcat(stack, "Sa");
		strcat(left_parse, "1");
		break;
	case 2:
		strcat(stack, "Ab");
		strcat(left_parse, "2");
		break;
	case 3:
		strcat(stack, "d");
		strcat(left_parse, "3");
		break;
	case 4:
		strcat(stack, "Acc");
		strcat(left_parse, "4");
		break;
	case 0:
		break;
	}

}

int main() {
	cout << "Enter a sentence: ";
	char input[MAX];
	cin >> input; //입력받은 str
	char stack[MAX] = { '$', 'S' }; //stack, 
	int ptable[2][4] = { {1,2, 0, 0}, {0, 0, 4, 3} }; //파싱테이블
	char parse[4]; //파스

	int j = 0;
	while (1) {

		char top = seek(stack); //1. stack의 top 살펴보기
		if (top == 'a' || top == 'b' || top == 'c' || top == 'd') //stack의 top이 terminal 일 때
		{
			if (top == input[j]) //top과 보고있는 입력 심벌이 같으면 pop!!
			{
				input[j] = NULL; //현재 보고있는거 null값 채워 넣음으로써 pop한다고 생각
				pop(stack); //stack의 top을 pop!!
				j++;
			}
			else //stack의 top도 terminal이고, 보고 있는 입력 심벌도 terminal인데, 둘이 다르면 push.....? 헷갈림
			{
				push(stack, input[j]);
			}
		}
		else if (top == 'A' || top == 'S') //stack의 top에 nonterminal이 나오면
		{
			if ((top == 'A') && (input[j] == 'a'))
			{
				rule(stack, ptable[0][0]);//생성규칙 1번
				parse[strlen(parse) - 1] = '1';
			}
			else if ((top == 'A') && (input[j] == 'b'))
			{

				rule(stack, ptable[0][1]);
				parse[strlen(parse) - 1] = '2';
			} //생성규칙 2번
			else if ((top == 'A') && (input[j] == 'c'))
			{
				rule(stack, ptable[1][2]);
				parse[strlen(parse) - 1] = '3';
			} //생성규칙 3번(현재는 없는 생성규칙)
			else if ((top == 'A') && (input[j] == 'd'))
				rule(stack, ptable[1][3]); //생성규칙 0번(현재는 없는 생성규칙)
			else if ((top == 'S') && (input[j] == 'a'))
				rule(stack, ptable[0][0]);//생성규칙 0번(현재는 없는 생성규칙)
			else if ((top == 'S') && (input[j] == 'b'))
				rule(stack, ptable[0][1]);//생성규칙 0번(현재는 없는 생성규칙)
			else if ((top == 'S') && (input[j] == 'c'))
				rule(stack, ptable[0][2]);//생성규칙 3번(현재는 없는 생성규칙)
			else if ((top == 'S') && (input[j] == 'd'))
			{
				rule(stack, ptable[0][3]);//생성규칙 4번(현재는 없는 생성규칙)
				parse[strlen(parse) - 1] = '4';
			}
			else
			{
				cout << "Error!!" << endl;
				exit(1);
			}
		}
		else if (top == '$')
		{
			cout << "Accept!!" << endl;
			cout << "Left Parse: " << left_parse << endl;

			break;
		}
		else {
			cout << "Error!!" << endl;
			exit(1);
		}
	}	
}