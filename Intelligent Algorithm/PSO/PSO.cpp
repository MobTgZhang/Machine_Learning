#pragma once
#include "PSO.h"
#include<iostream>
using std::cout;
using std::endl;
#include<string>
#include<sstream>
using std::string;
using std::stringstream;
string toString(vector<size_t> arr) {
	string line = "";
	stringstream ss;
	string tmp;
	for (size_t k = 0; k < arr.size(); k++) {
		ss << arr[k];
		tmp = ss.str();
		ss.str("");
		line = line + tmp + " ";
	}
	return line;
}
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
		pt.idl = PSO::BuildRandomSequence(citys_num);//��ʼ�������λ����Ϣ
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
//���ɻ���������
vector<PSO::exchangeSeq> PSO::BuildBasicExchangeSeq(vector<size_t>seq1, vector<size_t>seq2) {
	vector<exchangeSeq>Seq;
	vector<size_t> sq = seq2;
	PSO::exchangeSeq q;
	size_t i, j;
	for (i = 0; i < seq1.size()-1; i++) {
		for (j = i; j < seq1.size() && sq[j] != seq1[i]; j++);
		q.ei = i;
		q.ej = j;
		if (i == j) continue;
		size_t tp = sq[i];
		sq[i] = sq[j];
		sq[j] = tp;
		Seq.push_back(q);
	}
	return Seq;
}
//���ɵȼۼ�
vector<PSO::exchangeSeq> PSO::computeEquivalentSet(vector<PSO::exchangeSeq> sq1, vector<PSO::exchangeSeq> sq2) {
	vector<size_t> seq1, seq2;
	size_t citys_num = sq1.size();
	for (size_t i = 0; i < citys_num; i++) seq1.push_back(i);
	seq2 = seq1;
	computeNextPos(seq1, sq1);
	computeNextPos(seq1, sq2);
	return this->BuildBasicExchangeSeq(seq1,seq2);
}
//���ݵ�ǰ�������һ���⣬Ҳ����һ��λ��
void PSO::computeNextPos(vector<size_t>&id1, vector<PSO::exchangeSeq>&v){
	for (size_t i = 0; i < v.size(); i++) {
		size_t tp = id1[v[i].ei];
		id1[v[i].ei] = id1[v[i].ej];
		id1[v[i].ej] = tp;
	}
}
//���ݵ�ǰ���ӵ���Ϣ����������ٶ�
void PSO::computeNewVelocity(PSO::particle& pl) {
	//��ÿһ����������ٶ���Ϣ
	vector<PSO::exchangeSeq> Pid = BuildBasicExchangeSeq(pl.pbest.sbest,pl.idl);
	//ȫ�ָ��¸�����Ϣ
	vector<PSO::exchangeSeq> Pgd = BuildBasicExchangeSeq(gbest.sbest, pl.idl);
	vector<PSO::exchangeSeq> tp = pl.velocity;
	//���ɶ�Ӧ�ĵȼۼ�
	tp = this->computeEquivalentSet(tp,Pid);
	pl.velocity = this->computeEquivalentSet(tp, Pgd);
}


//ÿһ�����������е��ƶ�����
void PSO::Movement(vector<vector<double> >citys_distance) {
	size_t tp = 0;
	for (size_t i = 0; i < this->particleSwarm.size(); i++) {
		cout << toString(particleSwarm[i].idl) << endl;
		this->computeNextPos(this->particleSwarm[i].idl, particleSwarm[i].velocity);
		cout << toString(particleSwarm[i].idl) << endl;
		
		system("pause");
		this->computeNewVelocity(this->particleSwarm[i]);
		
		if (this->particleSwarm[i].pbest.path_length > PSO::GetPathLength(citys_distance, this->particleSwarm[i].idl)) {
			this->particleSwarm[i].pbest.path_length = PSO::GetPathLength(citys_distance, this->particleSwarm[i].idl);
			
			
			this->particleSwarm[i].pbest.sbest = this->particleSwarm[i].idl;
		}
		
		if (this->particleSwarm[i].pbest.path_length < this->gbest.path_length) {
			gbest.path_length = this->particleSwarm[i].pbest.path_length;
			tp = i;
		}
	}
	gbest.sbest = this->particleSwarm[tp].idl;
}
//���ӽ����ƶ�
void PSO::Move(vector<vector<double> >citys_distance) {
	for (size_t t= 0; t < this->genMax; t++) {
		this->Movement(citys_distance);
		cout << "Best length: " << this->gbest.path_length<<endl;
	}
}