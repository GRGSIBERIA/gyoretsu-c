/**
 * @file libraries.c
 * @brief ���C�u�����{�̂̃v���O�����R�[�h
 * @author �|���l��(GRGSIBERIA)
 */
#include "gyoretsu-c.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

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
				dest->_mat[i][j] += A->_mat[i][k] * B->_mat[k][j];
			}
		}
	}

	return dest;
}