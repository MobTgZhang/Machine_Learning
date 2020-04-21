#ifndef POS_H
#define POS_H
# pragma once
# include <vector>
# include <cmath>
# define MAX_DIS 1000000000
using std::vector;
//��ʾһ�����е�������Ϣ
typedef struct {
	double x_index;
	double y_index;
}proxy;
class PSO {
private:
	//���彻����
	typedef struct {
		size_t ei;
		size_t ej;
	}exchangeSeq;
	//��¼���ӵ�·����Ϣ
	typedef struct {
		vector<size_t> sbest;
		double path_length;
	}seqlen;
	//��¼���ӵ��ٶ��Լ���õ�λ����Ϣ
	typedef struct {
		vector<size_t> idl;// ���ӵĵ�ǰλ����Ϣ
		vector<exchangeSeq> velocity;//���ӵ�ǰ���ٶ���Ϣ
		seqlen pbest;//������õ�λ����Ϣ
	}particle;
	//��������Ĳ���
	size_t popsize;//��Ⱥ����
	size_t genMax;//��������Ĵ���
	//����ÿ�����������е�����λ����Ϣ��
	//�ٶ���Ϣ�Լ�ÿ��������ÿһ�����������е���õ�λ����Ϣ
	vector<particle> particleSwarm;
	seqlen gbest;//ȫ����õĳ�����Ϣ�Լ�λ����Ϣ
public:
	//���캯��
	PSO(size_t popsize, size_t genMax) {
		this->genMax = genMax;
		this->popsize = popsize;
	}
	//��ʼ������Ⱥ
	void InitialSwarm(vector<vector<double> >&citys_distance);
	//������������
	static vector<vector<double> > CalculateDistance(vector<proxy>& citys_mat);
	// ����һ��·���ĳ���
	static double GetPathLength(vector<vector<double> >&citys_distance, const vector<size_t>& path_seq);
	//�������������Ϣ
	static vector<size_t> BuildRandomSequence(size_t length);
	//��ӡ�����ӵ�·������̾�����Ϣ
	void print();

	

	//��������
	~PSO();
};
#endif // !POS_H