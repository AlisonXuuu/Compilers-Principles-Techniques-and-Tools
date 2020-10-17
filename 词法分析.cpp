#include<stdio.h>
#include<string.h>
#include <iostream>
using namespace std;

char prog[80], token[8];
char ch;
int syn, p, m = 0, n, row, sum = 0;
char *rwtab[11] = { "break","default","else if","swtich","case","begin","if","then","while","do","end" };


void scaner()
{
	for (n = 0; n<8; n++) token[n] = NULL;
	ch = prog[p++];
	while (ch == ' ')
	{
		ch = prog[p];
		p++;
	}
	if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z'))  //可能是标示符或者变量名 
	{
		m = 0;
		while ((ch >= '0'&&ch <= '9') || (ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z'))
		{
			token[m++] = ch;
			ch = prog[p++];
		}
		token[m++] = '\0';
		p--;
		syn = 1;
		
		for (n = 0; n<11; n++)  //compare 
			if (strcmp(token, rwtab[n]) == 0)
			{
				syn = 3;
				break;
			}
	}
	else if ((ch >= '0'&&ch <= '9'))  //numbers 
	{
		{
			sum = 0;
			while ((ch >= '0'&&ch <= '9'))
			{
				sum = sum * 10 + ch - '0';
				ch = prog[p++];
			}
		}
		p--;
		syn = 2;
		if (sum>32767)
			syn = -1;
	}
	else switch (ch)   //other
	{
	case'<':m = 0; token[m++] = ch;
		ch = prog[p++];
		if (ch == '>')
		{
			syn = 4;
			token[m++] = ch;
		}
		else if (ch == '=')
		{
			syn = 4;
			token[m++] = ch;
		}
		else
		{
			syn = 4;
			p--;
		}
		break;
	case'>':m = 0; token[m++] = ch;
		ch = prog[p++];
		if (ch == '=')
		{
			syn = 4;
			token[m++] = ch;
		}
		else
		{
			syn = 4;
			p--;
		}
		break;
	case':':m = 0; token[m++] = ch;
		ch = prog[p++];
		if (ch == '=')
		{
			syn = 4;
			token[m++] = ch;
		}
		else
		{
			syn = 4;
			p--;
		}
		break;
	case'*':syn = 4; token[0] = ch; break;
	case'/':syn = 4; token[0] = ch; break;
	case'+':syn = 4; token[0] = ch; break;
	case'-':syn = 4; token[0] = ch; break;
	case'=':syn = 4; token[0] = ch; break;
	case';':syn = 5; token[0] = ch; break;
	case'(':syn = 5; token[0] = ch; break;
	case')':syn = 5; token[0] = ch; break;
	case'#':syn = 6; token[0] = ch; break;
	case'\n':syn = 5; break;
	default: syn = -1; break;
	}
}

int main()
{
	p = 0;
	row = 1;
	int a = 0;
	
	cout << "input: " << endl;
	do
	{
		cin.get(ch);
		prog[p++] = ch;
	} while (ch != '#');
	p = 0;
	do
	{
		scaner();
		switch (syn)
		{
		case 2: cout << "(" << syn << "," << sum << ")" << endl; break;
		case -1:{
		 cout << "Error in row " << row << "!" << endl; row++;}; break;
		case 6:break;
		case 1: {
			cout << "(" << syn << "," << a << ")" << endl;
			a++; }; break;
		default: cout << "(" << syn << "," << token << ")" << endl; break;
		}
	} while (syn != 6);

}


