/**
 * @file gyoretsu-c.h
 * @brief 行列計算ライブラリ
 * @author 竹渕瑛一(GRGSIBERIA)
 */
#pragma once

/**
 * 行列構造体
 */
typedef struct _Matrix {
	int _numofColumns;	//! 列数
	int _numofRows;		//! 行数
	double* _mat;		//! 行列本体
} Matrix;

/**
 * @fn
 * 行列構造体の生成
 * @brief Matrixのコンストラクタ
 * @param numofRows 行数
 * @param numofColumns 列数
 * @return 行列へのポインタ
 * @detail
 * 行列構造体を関数で生成する
 * 内部的にmallocを呼び出しているので、勝手にMatrix構造体をmallocしてはいけない
 */
Matrix* CreateMatrix(int numofRows, int numofColumns);

/**
 * @fn
 * 行列構造体の解放
 * @brief Matrixのデストラクタ
 * @param mat 行列のポインタ
 * @return matのアドレス、通常は0が戻る
 */
void* DisposeMatrix(Matrix* mat);

/**
 * @fn
 * 行列同士の積、互いに行列が異なるならば、最小単位の正方行列を返す
 * @brief 行列同士の積
 * @param A 行列A
 * @param B 行列B
 * @returns 答えを格納する行列
 */
Matrix* MulMatrix(Matrix* A, Matrix* B);

/**
 * @fn
 * 行列の要素を取得する
 * @brief 要素のGETアクセサ
 * @param X 対象の行列
 * @param row 行
 * @param column 列
 */
double GetElem(Matrix* X, int row, int column);

/**
 * @fn
 * 行列の要素を設定する
 * @brief 要素のSETアクセサ
 * @param X 対象の行列
 * @param row 行
 * @param column 列
 */
void SetElem(Matrix* X, int row, int column, double val);