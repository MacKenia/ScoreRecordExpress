#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <cmath>

using namespace std;
struct score{
	char Cname[10];
	char Ename[5];
	int Score;
	bool operator==(const char *s){
		return !(strcmp(Ename,s));
	}
}example = {"","",0};

vector<score> scores;
vector<score>::iterator p;

int getn()
{
	int r, len;
	bool f = true;
	char tmp[10];
	cin >> tmp;
	len = strlen(tmp);
	for(int i = 0; i < len; i++)
	{
		if(!(tmp[i]>='0' && tmp[i] <= '9'))
		{
			cout << "输入有误请重新输入: " ;
			r = getn();
			f = false;
			break;
		}
	}
	if(f) for(int i = 0; i < len; i++)
	{
		r += (int)(tmp[i]-'0')*pow(10,len-i-1);
	}
	return r;
}

int show(score stut)
{ 
    cout << "����: " << stut.Cname << endl
    << "��ƴ: " << stut.Ename << endl
    << "�ɼ�: " << stut.Score << endl << endl;
    return 1;
}

int showRecord()
{
    for_each(scores.begin(),scores.end(),show);
    return 1;
}


void FirstLetter(int nCode, char& strRet);  
void GetFirstLetter(char* strName, char* strFirstLetter, int nLen)  
{
	int ucHigh, ucLow;  
	int nCode;
	char strRet;
	memset(strFirstLetter, 0, sizeof(nLen));
	int len = 0; 
	int nameLen = (int)strlen(strName);
	for(int i=0; i < nameLen; i += 2)
	{
		ucHigh = (int)(strName[i + 0] & 0xFF);
		ucLow = (int)(strName[i + 1] & 0xFF);
		nCode = (ucHigh - 0xa0) * 100 + ucLow - 0xa0;
		FirstLetter(nCode, strRet);
		strFirstLetter[len] = strRet;
		len ++;  
	}
	strFirstLetter[len] = '\0';  
}  
void FirstLetter(int nCode, char& strLetter)  
{  
	if(nCode >= 1601 && nCode < 1637) strLetter = 'A';
	if(nCode >= 1637 && nCode < 1833) strLetter = 'B';
	if(nCode >= 1833 && nCode < 2078) strLetter = 'C';
	if(nCode >= 2078 && nCode < 2274) strLetter = 'D';
	if(nCode >= 2274 && nCode < 2302) strLetter = 'E';
	if(nCode >= 2302 && nCode < 2433) strLetter = 'F';
	if(nCode >= 2433 && nCode < 2594) strLetter = 'G';
	if(nCode >= 2594 && nCode < 2787) strLetter = 'H';
	if(nCode >= 2787 && nCode < 3106) strLetter = 'J';
	if(nCode >= 3106 && nCode < 3212) strLetter = 'K';
	if(nCode >= 3212 && nCode < 3472) strLetter = 'L';
	if(nCode >= 3472 && nCode < 3635) strLetter = 'M';
	if(nCode >= 3635 && nCode < 3722) strLetter = 'N';
	if(nCode >= 3722 && nCode < 3730) strLetter = 'O';
	if(nCode >= 3730 && nCode < 3858) strLetter = 'P';
	if(nCode >= 3858 && nCode < 4027) strLetter = 'Q';
	if(nCode >= 4027 && nCode < 4086) strLetter = 'R';
	if(nCode >= 4086 && nCode < 4390) strLetter = 'S';
	if(nCode >= 4390 && nCode < 4558) strLetter = 'T';
	if(nCode >= 4558 && nCode < 4684) strLetter = 'W';
	if(nCode >= 4684 && nCode < 4925) strLetter = 'X';
	if(nCode >= 4925 && nCode < 5249) strLetter = 'Y';
	if(nCode >= 5249 && nCode < 5590) strLetter = 'Z';
	{
		//�뽫�Ż�����Ĵ���ŵ�����
		if(nCode == 7282||nCode == 8646) strLetter = 'X';
	}	
}

int main()
{
	fstream file;
	char pTemp[10], QR[5];
	char pTemp1[5];//���溺�ֵ�����ĸ
	cout << "�뽫��������name.txt�����˳�" << endl
	<< "���м�ƴ��ͬ��" << endl
	<<"���һ�������������м�������" << endl
	<<"�س��Լ���";
	cin.get();
	file.open("name.txt",ios::in);
	while(!file.eof())
	{
		if(file.fail()) break;
		file.getline(pTemp,10,'\n');
		GetFirstLetter(pTemp,pTemp1,5);
		strcpy(example.Cname,pTemp);
		strcpy(example.Ename, pTemp1);
		if(!(int)pTemp[0]) continue;
		scores.push_back(example);
	}
	file.close();
	showRecord();
	cout << "���ڿ�ʼ¼��ɼ������Դ�д�ķ�ʽ�����ƴ(���룡�˳���)��" << endl;
	if(!GetKeyState(VK_CAPITAL))
	{
		keybd_event(VK_CAPITAL,0,0,0);
		keybd_event(VK_CAPITAL,0,KEYEVENTF_KEYUP,0);
	}
	while(true)
	{
		int S;
		cout << "������ͬѧ�ļ�ƴ��";
		cin >> QR;
		if(QR[0] == '!') break;
		cin.ignore();
		p = find(scores.begin(),scores.end(),QR);
		while(strcmp(p->Ename,QR)) 
		{
			cout << "Ϊ�ҵ���ͬѧ����˶ԣ������������룺";
			cin >> QR;
			cin.ignore();
			p = find(scores.begin(),scores.end(),QR);
		}
		cout << "��ͬѧ������Ϊ: " << p->Cname << endl;
		cout << "������ɼ�: ";
		S = getn();
		p -> Score = S;
	}
	showRecord();
	file.open("score.txt",ios::out);
	for(p = scores.begin(); p != scores.end(); p++)
	{
		file << p->Score << endl;
	}
	file.close();
	if(GetKeyState(VK_CAPITAL))
	{
		keybd_event(VK_CAPITAL,0,0,0);
		keybd_event(VK_CAPITAL,0,KEYEVENTF_KEYUP,0);
	};
	return 0;
}
 
