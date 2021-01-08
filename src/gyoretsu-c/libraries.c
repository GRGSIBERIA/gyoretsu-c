/**
 * @file libraries.c
 * @brief ���C�u�����{�̂̃v���O�����R�[�h
 * @author �|���l��(GRGSIBERIA)
 */
#include "gyoretsu-c.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/**
 * row��column�����Ă��Ȃ����`�F�b�N����
 */
void OverCheck(Matrix* X, int row, int column)
{
	assert(X->_numofColumns > column && X->_numofRows > row);
}

double GetElem(Matrix* X, int row, int column)
{
	if (X && X->_mat)
	{	// C6011�̌Ăяo���K���NULL�`�F�b�N���Ȃ��ƃ_��
		OverCheck(X, row, column);
		return X->_mat[X->_numofRows * row + column];
	}

	// ����A���܂��|�C���^����ł�
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
		assert(0);	// �|�C���^����ł��
	}
}


Matrix* CreateMatrix(int numofRows, int numofColumns)
{
	Matrix* mat;
	int matsize;
	matsize = numofRows * numofColumns * sizeof(double);
	mat = (Matrix*)malloc(sizeof(Matrix));

	if (mat)
	{	// C6011�̌Ăяo���K���NULL�`�F�b�N���s��Ȃ���΂Ȃ�Ȃ�
		mat->_numofColumns = numofColumns;
		mat->_numofRows = numofRows;
		mat->_mat = (double*)malloc(matsize);

		if (mat->_mat)
		{	// C6011�̌Ăяo���K��
			memset(mat->_mat, 0, matsize);
		}
		else
		{
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

	// �����s��ł��邱�Ƃ�ۏ؂���
	columns = columns < rows ? columns : rows;
	rows = columns > rows ? rows : columns;
	n = columns;

	// �����s��łȂ���Όx�����o��
	assert(rows == columns);

	// ���ʂ̂��߂̍s��𐶐�����
	dest = CreateMatrix(rows, columns);

	// �s��̈�ʉ�������
	for (i = 0; i < rows; ++i)
	{
		for (j = 0; j < columns; ++j)
		{
			for (k = 0; k < n; ++k)
			{
				dest->_mat[i * rows + j] += A->_mat[i * rows + k] * B->_mat[k * rows + j];
			}
		}
	}

	return dest;
}