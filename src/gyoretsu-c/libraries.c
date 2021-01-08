#include "gyoretsu-c.h"
#include <stdlib.h>
#include <assert.h>

Matrix* CreateMatrix(int numofRows, int numofColumns)
{
	Matrix* mat;
	mat = (Matrix*)malloc(sizeof(Matrix));

	if (mat)
	{	// C6011�̌Ăяo���K���NULL�`�F�b�N���s��Ȃ���΂Ȃ�Ȃ�
		mat->_numofColumns = numofColumns;
		mat->_numofRows = numofRows;
		mat->_mat = (double*)malloc(sizeof(double) * numofRows * numofColumns);

		if (!mat->_mat)
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

void MulMatrix(Matrix* dest, Matrix* A, Matrix* B)
{

}