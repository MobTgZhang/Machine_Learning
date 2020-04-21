
#pragma once
#include "PSO.h"
#include"util.h"
int main()
{
	string filename = "eil51.tsp";
	string root_path = "Data";
	download(root_path, filename);
	vector<proxy>OutData = getData(root_path + "\\" + filename);
	size_t popsize = 600;
	size_t genMax = 80;
	PSO model = PSO(popsize, genMax);
	//��ʼ������Ⱥ
	vector<vector<double> >citys_distance = PSO::CalculateDistance(OutData);
	model.InitialSwarm(citys_distance);
	//���ӽ����ƶ�
	model.Move(citys_distance);
	//��ӡ����
	model.print();
	system("pause");
	return 0;
}