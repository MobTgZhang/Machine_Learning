#pragma once
#ifndef DNN_H
#define DNN_H
#include<vector>
#include "matrix.h"
class DNN {
private:
	std::vector<unsigned int>layers_list;
public:
	//���캯��
	DNN();
	//ǰ�򴫲�����

	//��������
	~DNN();
};
#endif // !DNN_H
#ifndef BP_NET_H
#define BP_NET_H
class BpNet {
private:
	unsigned int in_dim;
	unsigned int hid_dim;
	unsigned int out_dim;
	Matrix<double>WeightIn;
	Matrix<double>BaisIn;
	Matrix<double>WeightOut;
	Matrix<double>BaisOut;
public:
	//���캯��
	BpNet(unsigned int in_dim, unsigned int hid_dim, unsigned int out_dim);
	//ǰ�򴫲�����
	Matrix<double> forward(Matrix<double>&input);
	//���򴫲�����
	//�����ݶ�
	//��������
	~BpNet();
};
//���캯����ʵ�ֹ���
BpNet::BpNet(unsigned int in_dim, unsigned int hid_dim, unsigned int out_dim) {
	this->in_dim = in_dim;
	this->hid_dim = hid_dim;
	this->out_dim = out_dim;
	//��������ƫ��
	
}
#endif // !BP_NET_H

