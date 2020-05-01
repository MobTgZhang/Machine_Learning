#pragma once
#ifndef MATRIX_H
#define MATRIX_H
template<typename DataType>
class Matrix {
private:
	unsigned int RowLength;
	unsigned int ColumnLength;
	DataType** Matrix;
public:
	//���캯��
	Matrix();
	//ʵ�������������(���Ԫ��)
	Matrix<DataType> mul(Matrix<DataType>& mat);
	Matrix<DataType> mul(DataType value);
	//ʵ�������������(���Ԫ��)
	Matrix<DataType> add(Matrix<DataType>& mat);
	Matrix<DataType> add(DataType value);
	//ʵ�������������(���Ԫ��)
	Matrix<DataType> sub(Matrix<DataType>& mat);
	Matrix<DataType> sub(DataType value);
	//ʵ�������������(���Ԫ��)
	Matrix<DataType> div(Matrix<DataType>& mat);
	Matrix<DataType> div(DataType value);
	//���������
	Matrix<DataType> operator +(Matrix<DataType>& mat) { return this->add(mat); }
	Matrix<DataType> operator +(DataType value) { return this->add(value); }
	Matrix<DataType> operator -(Matrix<DataType>& mat) { return this->sub(mat); }
	Matrix<DataType> operator -(DataType value) { return this->sub(value); }
	Matrix<DataType> operator *(Matrix<DataType>& mat) { return this->mul(mat); }
	Matrix<DataType> operator *(DataType value) { return this->mul(value); }
	Matrix<DataType> operator /(Matrix<DataType>& mat) { return this->div(mat); }
	Matrix<DataType> operator /(DataType value) { return this->div(value); }
	//��������
	~Matrix();
};
template<typename DataType>
Matrix<DataType>::Matrix(unsigned int RowLength, unsigned int ColumnLength) {
	for (unsigned int k = 0; k < RowLength; k++) {

	}
}
#endif
