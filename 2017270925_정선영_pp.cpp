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
	stack[strlen(stack) - 1] = NULL; //���� stack�� top�� �ִ� nonterminal �����ϰ�

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
	cin >> input; //�Է¹��� str
	char stack[MAX] = { '$', 'S' }; //stack, 
	int ptable[2][4] = { {1,2, 0, 0}, {0, 0, 4, 3} }; //�Ľ����̺�
	char parse[4]; //�Ľ�

	int j = 0;
	while (1) {

		char top = seek(stack); //1. stack�� top ���캸��
		if (top == 'a' || top == 'b' || top == 'c' || top == 'd') //stack�� top�� terminal �� ��
		{
			if (top == input[j]) //top�� �����ִ� �Է� �ɹ��� ������ pop!!
			{
				input[j] = NULL; //���� �����ִ°� null�� ä�� �������ν� pop�Ѵٰ� ����
				pop(stack); //stack�� top�� pop!!
				j++;
			}
			else //stack�� top�� terminal�̰�, ���� �ִ� �Է� �ɹ��� terminal�ε�, ���� �ٸ��� push.....? �򰥸�
			{
				push(stack, input[j]);
			}
		}
		else if (top == 'A' || top == 'S') //stack�� top�� nonterminal�� ������
		{
			if ((top == 'A') && (input[j] == 'a'))
			{
				rule(stack, ptable[0][0]);//������Ģ 1��
				parse[strlen(parse) - 1] = '1';
			}
			else if ((top == 'A') && (input[j] == 'b'))
			{

				rule(stack, ptable[0][1]);
				parse[strlen(parse) - 1] = '2';
			} //������Ģ 2��
			else if ((top == 'A') && (input[j] == 'c'))
			{
				rule(stack, ptable[1][2]);
				parse[strlen(parse) - 1] = '3';
			} //������Ģ 3��(����� ���� ������Ģ)
			else if ((top == 'A') && (input[j] == 'd'))
				rule(stack, ptable[1][3]); //������Ģ 0��(����� ���� ������Ģ)
			else if ((top == 'S') && (input[j] == 'a'))
				rule(stack, ptable[0][0]);//������Ģ 0��(����� ���� ������Ģ)
			else if ((top == 'S') && (input[j] == 'b'))
				rule(stack, ptable[0][1]);//������Ģ 0��(����� ���� ������Ģ)
			else if ((top == 'S') && (input[j] == 'c'))
				rule(stack, ptable[0][2]);//������Ģ 3��(����� ���� ������Ģ)
			else if ((top == 'S') && (input[j] == 'd'))
			{
				rule(stack, ptable[0][3]);//������Ģ 4��(����� ���� ������Ģ)
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