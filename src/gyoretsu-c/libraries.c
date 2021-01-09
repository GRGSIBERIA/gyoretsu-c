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

/**
 * @brief 行列の足し算
 */
void OperatorAdd(Matrix* dest, const Matrix* A, const Matrix* B, int index)
{
	dest->_mat[index] = A->_mat[index] + B->_mat[index];
}

/**
 * @brief 行列の引き算
 */
void OperatorSub(Matrix* dest, const Matrix* A, const Matrix* B, int index)
{
	dest->_mat[index] = A->_mat[index] - B->_mat[index];
}

/**
 * @brief 行列のアダマール積
 */
void OperatorHadamard(Matrix* dest, const Matrix* A, const Matrix* B, int index)
{
	dest->_mat[index] = A->_mat[index] * B->_mat[index];
}

/**
 * @fn
 * (A(i,j), (B(i,j)) -> C(i,j)となる組を関数化したもの
 * @brief 加減とアダマール積をカリー化したもの
 * @param A 行列A
 * @param B 行列B
 * @param errorHandle 値が0なら成功、非ゼロなら障害発生
 * @param op カリー化対象の関数ポインタ
 */
Matrix* CurryMatrixOperatorFunction(const Matrix* A, const Matrix* B, int* errorHandle, void (*op)(Matrix*, const Matrix*, const Matrix*, int))
{
	int i, j;
	Matrix* dest;

	if (errorHandle)
	{
		// 行列A, Bのサイズは一致しなければならない
		*errorHandle = A->_numofColumns == B->_numofColumns && A->_numofRows == B->_numofRows;
	}
	else
	{
		assert(0);	// エラーハンドルにアドレスが割り振られていない
		return 0;
	}

	if (*errorHandle)
	{
		dest = CreateMatrix(A->_numofRows, A->_numofColumns);
	}
	else
	{
		assert(0);	// エラーハンドルのデフォルト値は0以外
		return 0;
	}

	for (i = 0; i < A->_numofRows; ++i)
	{
		int row = A->_numofRows * i;

		for (j = 0; j < A->_numofColumns; ++j)
		{
			int index = row + j;
			op(dest, A, B, index);
		}
	}

	return dest;
}

Matrix* HadamardProduct(const Matrix* A, const Matrix* B, int* errorHandle)
{
	return CurryMatrixOperatorFunction(A, B, errorHandle, &OperatorHadamard);
}

Matrix* AddMatrix(const Matrix* A, const Matrix* B, int* errorHandle)
{
	return CurryMatrixOperatorFunction(A, B, errorHandle, &OperatorAdd);
}

Matrix* SubMatrix(const Matrix* A, const Matrix* B, int* errorHandle)
{
	return CurryMatrixOperatorFunction(A, B, errorHandle, &OperatorSub);
}