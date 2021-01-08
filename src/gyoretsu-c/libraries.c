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
void OverCheck(Matrix* X, int row, int column)
{
	assert(X->_numofColumns > column && X->_numofRows > row);
}

double GetElem(Matrix* X, int row, int column)
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

void SetElem(Matrix* X, int row, int column, double val)
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


Matrix* CreateMatrix(int numofRows, int numofColumns)
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

Matrix* MulMatrix(Matrix* A, Matrix* B)
{
	int i, j, k;
	int rows, columns, n;
	Matrix* dest;
	
	columns = A->_numofColumns < B->_numofColumns ? A->_numofColumns : B->_numofColumns;
	rows = A->_numofRows < B->_numofRows ? A->_numofRows : B->_numofRows;

	// 正方行列であることを保証する
	columns = columns < rows ? columns : rows;
	rows = columns > rows ? rows : columns;
	n = columns < rows ? columns : rows;

	// 正方行列でなければ警告を出す
	assert(rows == columns);

	// 結果のための行列を生成する
	dest = CreateMatrix(n, n);

	// 行列の一般化した解
	for (i = 0; i < dest->_numofRows; ++i)
	{
		for (j = 0; j < dest->_numofColumns; ++j)
		{
			for (k = 0; k < n; ++k)
			{
				dest->_mat[i * rows + j] += A->_mat[i * rows + k] * B->_mat[k * rows + j];
			}
		}
	}

	return dest;
}