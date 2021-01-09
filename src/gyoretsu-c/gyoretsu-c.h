/**
 * @file gyoretsu-c.h
 * @brief 行列計算ライブラリ
 * @author 竹渕瑛一(GRGSIBERIA)
 */
#pragma once

/**
 * @brief 行列構造体
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
Matrix* CreateMatrix(const int numofRows, const int numofColumns);

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
 * @returns 答えを格納する行列、新しくCreateされるため、Disposeしなければならない
 */
Matrix* MulMatrix(const Matrix* A, const Matrix* B);

/**
 * @fn
 * 行列の要素を取得する
 * @brief 要素のGETアクセサ
 * @param X 対象の行列
 * @param row 行
 * @param column 列
 */
double GetElem(const Matrix* X, const int row, const int column);

/**
 * @fn
 * 行列の要素を設定する
 * @brief 要素のSETアクセサ
 * @param X 対象の行列
 * @param row 行
 * @param column 列
 */
void SetElem(Matrix* X, const int row, const int column, const double val);

/**
 * @fn
 * 行列のランクを返す
 * @brief 行列のランクを求める
 * @param X ランクを求めたい行列
 * @returns ランク, ただし互いに最小となる最大の部分行列でランクの性質は満たさない
 */
int Rank(const Matrix* X);

/**
 * @fn
 * アダマール積の結果を返す
 * @brief 行列のアダマール積
 * @param A 行列A
 * @param B 行列B
 * @returns アダマール積の結果、行列のサイズが異なる場合、互いに最小の行列を返す
 */
Matrix* HadamardProduct(const Matrix* A, const Matrix* B);

/**
 * @fn
 * 行列の和を返す
 * @brief 行列の和
 * @param A 行列A
 * @param B 行列B
 * @param errorHandle 計算可能な行列かどうか結果を返す、デフォルトは0以外
 * @returns 行列の和、計算不可能である場合は0
 * @detail
 * 行列の和は互いに同じ大きさでなければ計算できない。
 */
Matrix* AddMatrix(const Matrix* A, const Matrix* B, int* errorHandle);