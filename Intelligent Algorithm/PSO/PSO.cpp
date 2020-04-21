#pragma once
#include "PSO.h"
#include<iostream>
using std::cout;
using std::endl;
//��������
PSO::~PSO() {

}
# include<ctime>
#include<cstdlib>
// ����һ��·���ĳ���
double PSO::GetPathLength(vector<vector<double> >&citys_distance, const vector<size_t>&path_seq) {
	double path_length = 0;
	size_t citys_num = citys_distance.size();
	for (size_t pos = 1; pos < citys_num; pos++) {
		path_length += citys_distance[path_seq[pos-1]][pos];
	}
	path_length += citys_distance[path_seq[citys_num-1]][0];
	return path_length;
}
//������������
vector<vector<double> > PSO::CalculateDistance(vector<proxy>& citys_mat) {
	vector<vector<double> > citys_distance;
	//��ȡ�����еĸ�����Ϣ
	unsigned int citys_num = citys_mat.size();
	//��ʼ���������
	for (size_t k = 0; k < citys_num; k++) {
		citys_distance.push_back(vector<double>());
		for (size_t j = 0; j < citys_num; j++) {
			citys_distance[k].push_back(sqrt(pow(citys_mat[k].x_index - citys_mat[j].x_index, 2) + pow(citys_mat[k].y_index - citys_mat[j].y_index, 2)));
		}
	}
	return citys_distance;
}

//�������������Ϣ
vector<size_t> PSO:: BuildRandomSequence(size_t length) {
	vector<size_t> vc;
	for (size_t i = 0; i < length; i++) vc.push_back(i);
	for (size_t i = length - 1; i > 0; i--) {
		size_t x = rand() % (i + 1);
		size_t tmp = vc[i];
		vc[i] = vc[x];
		vc[x] = tmp;
	}
	return vc;
}


//��ʼ������Ⱥ
void PSO::InitialSwarm(vector<vector<double> >&citys_distance) {
	size_t tp = 0;
	particle pt;////�������ӵ�ǰ���ٶ��Լ�λ�ú���õ�λ����Ϣ
	exchangeSeq exSeq;//λ�õĽ�����
	double shortlen = MAX_DIS;//��С�ĳ���
	size_t citys_num= citys_distance.size();
	srand((unsigned)time(NULL));
	for (size_t i = 0; i < this->popsize; i++) {
		pt.idl = PSO::BuildRandomSequence(citys_num);
		pt.pbest.sbest = pt.idl;
		pt.pbest.path_length = PSO::GetPathLength(citys_distance,pt.pbest.sbest);
		for (size_t j = 0; j < citys_num; j++) {
			//�������������
			exSeq.ei = rand() % citys_num;
			exSeq.ej = rand() % citys_num;
			pt.velocity.push_back(exSeq);
		}
		this->particleSwarm.push_back(pt);
		if (shortlen > pt.pbest.path_length) {
			//������С�ĳ���
			shortlen = pt.pbest.path_length;
			tp = i;
		}
	}
	this->gbest = this->particleSwarm[tp].pbest;
}
//��ӡ������������·���;�����Ϣ
void PSO::print() {
	cout << "��̵ľ���Ϊ: " << this->gbest.path_length << endl;
	cout << "��̵�·����ϢΪ: ";
	for (size_t i = 0; i < gbest.sbest.size(); i++) {
		cout << gbest.sbest[i] << "\t";
	}
	cout << gbest.sbest[0] << endl;
}