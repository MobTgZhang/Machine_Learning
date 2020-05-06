#pragma once
#ifndef VECTOR_H
#define VECTOR_H
#include<string>
#include<sstream>
template<typename DataType>
class Vector {
private:
	unsigned int Length;
	DataType* InnerVec;
public:
	//���캯��
	Vector(unsigned int Length);
	Vector(Vector<DataType>&mat);
	//��ȡ�����Ĵ�С
	unsigned int GetLength() { return this->Length;}
	//��ʾ�������Ԫ�����
	Vector<DataType> mul(Vector<DataType>& mat);
	Vector<DataType> mul(DataType value);
	//��ȡ�����е�ĳһ��Ԫ��
	DataType Get(unsigned int index);
	//���þ����е�ĳһ��Ԫ��
	void Set(DataType value, unsigned int index);
	//��ʾ�������Ԫ�����
	Vector<DataType> add(Vector<DataType>& mat);
	Vector<DataType> add(DataType value);
	//��ʾ���������Ԫ�����
	Vector<DataType> sub(Vector<DataType>& mat);
	Vector<DataType> sub(DataType value);
	//��ʾ���������Ԫ�����
	Vector<DataType> div(Vector<DataType>& mat);
	Vector<DataType> div(DataType value);
	//Vector ��Matrix�㲥
	Matrix<DataType> add(Matrix<DataType>& mat);
	Matrix<DataType> sub(Matrix<DataType>& mat);
	//���������
	Vector<DataType> operator +(Vector<DataType>& mat) { return this->add(mat); }
	Vector<DataType> operator +(DataType value) { return this->add(value); }
	Vector<DataType> operator -(Vector<DataType>& mat) { return this->sub(mat); }
	Vector<DataType> operator -(DataType value) { return this->sub(value); }
	Vector<DataType> operator *(Vector<DataType>& mat) { return this->mul(mat); }
	Vector<DataType> operator *(DataType value) { return this->mul(value); }
	Vector<DataType> operator /(Vector<DataType>& mat) { return this->div(mat); }
	Vector<DataType> operator /(DataType value) { return this->div(value); }
	//����������еĹ㲥����
	Matrix<DataType> operator +(Matrix<DataType>& mat) { return this->add(mat); }
	Matrix<DataType> operator -(Matrix<DataType>& mat) { return this->sub(mat); }
	//�������е�Ԫ��ת��Ϊ�ַ�����ʽ
	std::string toString();
	//��������
	~Vector();
};
//���캯��
template<typename DataType>
Vector<DataType>::Vector(unsigned int Length) {
	this->Length = Length;
	this->InnerVec = new DataType[Length];
}
template<typename DataType>
Vector<DataType>::Vector(Vector<DataType>&mat) {
	this->Length = mat.GetLength();
	this->InnerVec = new DataType[Length];
	for (unsigned int k = 0; k < mat.GetLength(); k++) {
		this->InnerVec[k] = mat.Get(k);
	}
}
//��������
template<typename DataType>
Vector<DataType>::~Vector() {
	delete[] this->InnerVec;
}
//��ȡ�����е�ĳһ��Ԫ��
template<typename DataType>
DataType Vector<DataType>::Get(unsigned int index) {
	return this->InnerVec[index];
}
//���þ����е�ĳһ��Ԫ��
template<typename DataType>
void Vector<DataType>::Set(DataType value, unsigned int index) {
	this->InnerVec[index] = value;
}
//��ʾ�������Ԫ�����
template<typename DataType>
Vector<DataType> Vector<DataType>::mul(Vector<DataType>& mat) {
	if (mat.GetLength() != this->GetLength()) {
		throw "The size don't match!";
	}
	Vector<DataType> resultMat(this->Length);
	for (unsigned int k = 0; k < this->Length; k++) {
		DataType value = this->InnerVec[k] * mat.Get(k);
		resultMat.Set(value, k);
	}
	return resultMat;
}
template<typename DataType>
Vector<DataType> Vector<DataType>::mul(DataType value) {
	Vector<DataType> resultMat(this->Length);
	for (unsigned int k = 0; k < this->Length; k++) {
		DataType val = this->InnerVec[k] * value;
		resultMat.Set(val, k);
	}
	return resultMat;
}

//��ʾ�������Ԫ�����
template<typename DataType>
Vector<DataType> Vector<DataType>::add(Vector<DataType>& mat) {
	if (mat.GetLength() != this->GetLength()) {
		throw "The size don't match!";
	}
	Vector<DataType> resultMat(this->Length);
	for (unsigned int k = 0; k < this->Length; k++) {
		DataType value = this->InnerVec[k] + mat.Get(k);
		resultMat.Set(value, k);
	}
	return resultMat;
}
template<typename DataType>
Vector<DataType> Vector<DataType>::add(DataType value) {
	Vector<DataType> resultMat(this->Length);
	for (unsigned int k = 0; k < this->Length; k++) {
		DataType val = this->InnerVec[k] + value;
		resultMat.Set(val, k);
	}
	return resultMat;
}
//��ʾ���������Ԫ�����
template<typename DataType>
Vector<DataType> Vector<DataType>::sub(Vector<DataType>& mat) {
	if (mat.GetLength() != this->GetLength()) {
		throw "The size don't match!";
	}
	Vector<DataType> resultMat(this->Length);
	for (unsigned int k = 0; k < this->Length; k++) {
		DataType value = this->InnerVec[k] - mat.Get(k);
		resultMat.Set(value, k);
	}
	return resultMat;
}
template<typename DataType>
Vector<DataType> Vector<DataType>::sub(DataType value) {
	Vector<DataType> resultMat(this->Length);
	for (unsigned int k = 0; k < this->Length; k++) {
		DataType val = this->InnerVec[k] - value;
		resultMat.Set(val, k);
	}
	return resultMat;
}
//��ʾ���������Ԫ�����
template<typename DataType>
Vector<DataType> Vector<DataType>::div(Vector<DataType>& mat) {
	if (mat.GetLength() != this->GetLength()) {
		throw "The size don't match!";
	}
	Vector<DataType> resultMat(this->Length);
	for (unsigned int k = 0; k < this->Length; k++) {
		DataType value = this->InnerVec[k] / mat.Get(k);
		resultMat.Set(value, k);
	}
	return resultMat;
}
template<typename DataType>
Vector<DataType> Vector<DataType>::div(DataType value) {
	Vector<DataType> resultMat(this->Length);
	for (unsigned int k = 0; k < this->Length; k++) {
		DataType val = this->InnerVec[k] / value;
		resultMat.Set(val, k);
	}
	return resultMat;
}
//Vector ��Matrix�㲥��ӻ������

template<typename DataType>
Matrix<DataType> Vector<DataType>::sub(Matrix<DataType>& mat) {
	if (mat.GetColumnLength() != this->Length) {
		throw "The size don't match!";
	}
	Matrix<DataType> Result(mat.size());
	for (unsigned int k = 0; k<this->mat.GetRowLength(); k++) {
		for (unsigned int j = 0; j<this->mat.GetColumnLength(); j++) {
			Result.Set(this->InnerMat[j] - mat.Get(k, j), k, j);
		}
	}
	return Result;
}
template<typename DataType>
Matrix<DataType> Vector<DataType>::add(Matrix<DataType>& mat) {
	if (mat.GetColumnLength() != this->Length) {
		throw "The size don't match!";
	}
	Matrix<DataType> Result(mat.size());
	for (unsigned int k = 0; k<this->mat.GetRowLength(); k++) {
		for (unsigned int j = 0; j<this->mat.GetColumnLength(); j++) {
			Result.Set(this->InnerMat[j] + mat.Get(k, j), k, j);
		}
	}
	return Result;
}
//�������е�Ԫ��ת��Ϊ�ַ�����ʽ
template<typename DataType>
std::string Vector<DataType>::toString() {
	unsigned int Length = this->Length;
	std::stringstream tmp_stream;
	tmp_stream.precision(4);  //����δ�ö����ʽ���������õ��Ǳ���4λ��Ч����
	std::string str_size;
	tmp_stream << "Size:[" << Length << "]";
	tmp_stream >> str_size;
	str_size = str_size + "\n";
	//ע������s_streamҪ����ַ���
	tmp_stream.clear();
	std::string str_mat = "";
	for (unsigned int k = 0; k<Length; k++) {
		tmp_stream << this->InnerVec[k];
		std::string line;
		tmp_stream >> line;
		str_mat = str_mat + line + "\t";
		tmp_stream.clear();
	}
	str_mat = str_mat + "\n";
	return str_mat + str_size;
}
#endif // !VECTOR_H


