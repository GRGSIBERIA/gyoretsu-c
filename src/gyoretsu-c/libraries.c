/**
 * @file libraries.c
 * @brief ライブラリ本体のプログラムコード
 * @author 竹渕瑛一(GRGSIBERIA)
 */
#include "gyoretsu-c.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/**
 * rowとcolumnが溢れていないかチェックする
 */
void OverCheck(const Matrix* X, const int row, const int column)
{
	assert(X->_numofColumns > column && X->_numofRows > row);
}

double GetElem(const Matrix* X, const int row, const int column)
{
	if (X && X->_mat)
	{	// C6011の呼び出し規約でNULLチェックしないとダメ
		OverCheck(X, row, column);
		return X->_mat[X->_numofRows * row + column];
	}

	// いや、おまえポインタ死んでる
	assert(0);

	return 0.0;
}

void SetElem(Matrix* X, const int row, const int column, const double val)
{
	if (X && X->_mat)
	{
		OverCheck(X, row, column);
		X->_mat[X->_numofRows * row + column] = val;
	}
	else
	{
		assert(0);	// ポインタ死んでるよ
	}
}

Matrix* CreateMatrix(const int numofRows, const int numofColumns)
{
	Matrix* mat;
	int matsize;
	matsize = numofRows * numofColumns * sizeof(double);
	mat = (Matrix*)malloc(sizeof(Matrix));

	if (mat)
	{	// C6011の呼び出し規約でNULLチェックを行わなければならない
		mat->_numofColumns = numofColumns;
		mat->_numofRows = numofRows;
		mat->_mat = (double*)malloc(matsize);

		if (mat->_mat)
		{	// C6011の呼び出し規約
			memset(mat->_mat, 0, matsize);
		}
		else
		{	// メモリ確保に失敗したかもしれない
			assert(mat->_mat);
		}
	}
	else
	{
		assert(mat);
	}

	return mat;
}

void* DisposeMatrix(Matrix* mat)
{
	if (mat)
	{
		free(mat->_mat);
		mat->_mat = 0;
		free(mat);
		mat = 0;
	}
	else
	{
		assert(mat);
	}
	return mat;
}

int Rank(const Matrix* X)
{
	return X->_numofRows < X->_numofColumns ? X->_numofRows : X->_numofColumns;
}

int GetNRank(const Matrix* A, const Matrix* B)
{
	int rows, columns, n;

	// 互いに最も小さなランクで計算する
	columns = A->_numofColumns < B->_numofColumns ? A->_numofColumns : B->_numofColumns;
	rows = A->_numofRows < B->_numofRows ? A->_numofRows : B->_numofRows;

	// 互いに最も小さい部分行列となる数字を返す
	columns = columns < rows ? columns : rows;
	rows = columns > rows ? rows : columns;
	return columns < rows ? columns : rows;
}

Matrix* MulMatrix(const Matrix* A, const Matrix* B)
{
	int i, j, k;
	int n;
	Matrix* dest;
	
	n = GetNRank(A, B);

	// 結果のための行列を生成する
	dest = CreateMatrix(n, n);

	// 行列の一般化した解
	for (i = 0; i < dest->_numofRows; ++i)
	{
		int row = i * dest->_numofRows;

		for (j = 0; j < dest->_numofColumns; ++j)
		{
			for (k = 0; k < n; ++k)
			{
				dest->_mat[row + j] += A->_mat[row + k] * B->_mat[k * dest->_numofRows + j];
			}
		}
	}

	return dest;
}

Matrix* HadamardProduct(const Matrix* A, const Matrix* B)
{
	int i, j;
	int n;
	Matrix* dest;

	n = GetNRank(A, B);

	dest = CreateMatrix(n, n);

	for (i = 0; i < dest->_numofRows; ++i)
	{
		int row = i * dest->_numofRows;

		for (j = 0; j < dest->_numofColumns; ++j)
		{
			int index = row + j;

			dest->_mat[index] = A->_mat[index] * B->_mat[index];
		}
	}

	return dest;
}