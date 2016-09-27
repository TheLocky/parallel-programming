#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

int sleep(int code)
{
	getc(stdin);
	return code;
}

int main()
{
	clock_t ttime = clock();
	ifstream srcFile("matrix.dat");
	if (!srcFile.is_open()) {
		cout << "Can't open file.";
		return sleep(-1);
	}		

	int i, j, n, m;
	srcFile >> n;
	srcFile >> m;
	m++;

	float **matrix = new float *[n];
	for (i = 0; i < n; i++) {
		matrix[i] = new float[m];
		for (j = 0; j < m; j++) {
			srcFile >> matrix[i][j];
		}
	}


	auto *xx = new float[m];
	for (i = 0; i<n; i++)
	{
		auto tmp = matrix[i][i];
		for (j = n; j >= i; j--)
			matrix[i][j] /= tmp;
		for (j = i + 1; j<n; j++)
		{
			tmp = matrix[j][i];
			for (int k = n; k >= i; k--)
				matrix[j][k] -= tmp*matrix[i][k];
		}
	}

	xx[n - 1] = matrix[n - 1][n];
	for (i = n - 2; i >= 0; i--)
	{
		xx[i] = matrix[i][n];
		for (j = i + 1; j<n; j++) 
			xx[i] -= matrix[i][j] * xx[j];
	}

	ttime = clock() - ttime;

	for (i = 0; i<n; i++)
		cout << xx[i] << " ";
	cout << endl;
	cout << (float)ttime / CLOCKS_PER_SEC;

	delete[] matrix;
	delete xx;
	return sleep(0);
}