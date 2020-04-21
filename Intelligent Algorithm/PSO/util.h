#pragma once
#ifndef UTIL_H
#define UTIL_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <urlmon.h>
#include <fileapi.h>
#include <vector>
#pragma comment(lib, "urlmon.lib")
#include"PSO.h"

using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::getline;
using std::vector;
using std::stringstream;


//���������ļ�����
void download(string root_path, string filename) {
	//�жϸ�Ŀ¼�Ƿ���ڣ����������򴴽���Ŀ¼
	string url = "http://elib.zib.de/pub/mp-testdata/tsp/tsplib/tsp/";
	string data_path = root_path + "\\" + filename;
	DWORD dwAttribute = GetFileAttributes(root_path.c_str());
	if (dwAttribute == 0XFFFFFFFF) {
		//0XFFFFFFFF��ʾ�ļ��в�����,�����ļ���
		CreateDirectory(root_path.c_str(), NULL);
		//��ʼ�����ļ����������ļ�
		url = url + filename;
		DWORD status = URLDownloadToFile(NULL, url.c_str(), data_path.c_str(), 0, 0);
		if (status == S_OK) {
			cout << "Successfully download file: " << data_path << endl;
		}
		else {
			string message = "Download file: " + data_path + " failed!";
			throw message.c_str();
		}
	}
	else {
		//�鿴�ļ��Ƿ����
		dwAttribute = GetFileAttributes(data_path.c_str());
		if (dwAttribute == 0XFFFFFFFF) {
			//��ʼ�����ļ����������ļ�
			url = url + filename;
			DWORD status = URLDownloadToFile(NULL, url.c_str(), data_path.c_str(), 0, 0);
			if (status == S_OK) {
				cout << "Successfully download file: " << data_path << endl;
			}
			else {
				string message = "Download file: " + data_path + " failed!";
				throw message.c_str();
			}

		}
		else {
			cout << "The file: " << data_path << " exisits!" << endl;
		}
	}
}
// �������ݻ�ȡ������������ȡ�ļ��еĳ���������Ϣ
vector<proxy> getData(string filename) {
	ifstream infile(filename);
	
	vector<proxy> citys_math;
	//���ļ�������ȡÿһ�е�������
	string  line; //��������ÿһ��
	bool NumFlag = false;
	while (getline(infile, line)) {
		if (line.find("NODE_COORD_SECTION") != line.npos) {
			NumFlag = true;
		}
		else if(line.find("EOF") != line.npos) {
			break;
		}
		else if (NumFlag) {
			double index;
			double x_index;
			double y_index;
			stringstream stream;
			stream << line;
			stream >> index >> x_index >> y_index;
			proxy tmp;
			tmp.x_index = x_index;
			tmp.y_index = y_index;
			citys_math.push_back(tmp);
		}
		else {
			
		}
	}
	return citys_math;
}
#endif