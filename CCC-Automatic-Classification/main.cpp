#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
namespace fs = filesystem;
vector<string> segment;

int main(int argc, char* argv[])
{
	fs::path main_arr = argv[0];
	string main_name = main_arr.filename().string();
	string n_path = "./", root;
	fs::path dir_path("./");
	cout << "enter the root file\n";
	cin >> root; dir_path += root;

	for (auto &p : fs::directory_iterator(n_path)) 
	{
		if (p.path().extension().string() != ".cpp") continue;
		string s = p.path().filename().string(), str;
		for (auto& c : s)
		{
			if (c == ' ') segment.push_back(str), str.clear();
			else str += c;
		}
		segment.push_back(str);

		//������ccc ����cco ��ͳһ����Ϊothers
		transform(segment[0].begin(), segment[0].end(), segment[0].begin(), ::tolower);
		if (segment[0] != "ccc" && segment[0] != "cco")
		{
			dir_path = n_path + root + "/others";
			fs::create_directories(dir_path);
			string temp = n_path + s; //���ļ���ַ
			dir_path += '/' + temp; //���ļ���ַ
			fs::rename(n_path + s, dir_path);
			segment.clear();
			continue;
		}

		//�������ļ���
		if (segment[1][0] != '\'') segment[1].assign(0, '\'');
		dir_path = n_path + root + '/' + segment[1];
		fs::create_directories(dir_path);

		//�ƶ��ļ�
		string temp = n_path + s; //���ļ���ַ
		dir_path += '/' + temp; //���ļ���ַ
		fs::rename(n_path + s, dir_path);
		segment.clear();
	}

	for (auto sg : segment) cout << sg << endl;
	system("pause");
	return 0;
}