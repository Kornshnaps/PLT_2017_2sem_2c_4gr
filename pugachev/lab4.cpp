#include <iostream>
#include <fstream>

using namespace std;

int scanfile(FILE *&fin)
{
	int s = 0, i = 10;
	int k = fgetc(fin);
	while ( (k != EOF)&& k!=' '&&k!=','&&k!='\n')
	{
		 
		s = s*i + (k - '0');
		k = fgetc(fin);
	}
	return s;
}

void printmatr(int** a, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << a[i][j] << ' ';
		cout << endl;
	}
	cout << endl;
};


void cheapway(int**a, int n, int& cheap, int summ, int city, int end, bool*& prev)
{

	int coast = a[city][city];
	prev[city] = 1;
	if (city != end)
		for (int j = 0; j < n; j++)
			if (a[city][j] != 0 && !prev[j])
			{
				//prev[j] = 1;
 				cheapway(a, n, cheap, summ + coast, j, end, prev);
			}
	if (city==end&&((summ < cheap) || (cheap == -1)))
			cheap = summ;

	
	prev[city] = 0;
};

void main()
{
	FILE* fin = fopen("Text4lab.txt", "r");
	int n = scanfile(fin);

	int** a = new int*[n];
	for (int i = 0; i < n; i++) a[i] = new int[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) a[i][j] = 0;


	for (int i = 0; i < n; i++)
	{
		a[i][i] = scanfile(fin);
	}
	
	
	int m = scanfile(fin);
	int i = 0, j = 0,k=0;
	while (k < m)
	{
		i = scanfile(fin)-1;
		j = scanfile(fin)-1;
		a[i][j] = a[j][i] = 1;
		k++;
	}
	fclose(fin);
	
	printmatr(a, n);
	
	int cheap=-1;
	
	bool* prev = new bool[n];
	for (int i = 0; i < n; i++) {
		 prev[i] = 0;
	}
	int begin , end ;
	cout << "Enter the first end the last cities\n";
	cin >> begin >> end;
	cheapway(a, n, cheap, 0, --begin,--end, prev);
	cout << cheap << endl;
	fclose(fin);
	system("pause");
}