/************************************************************************
*  Author: Sundy
*  E-mail: sundycoder@gmail.com
*  Date:  Jan 09,2018
************************************************************************/
#include "Txt2Xml.hpp"
#include "misc.h"
#include <fstream>

using namespace txt2xml;
using namespace std;


int main(int argc, char** argv) {
	if (argc < 2) {
		std::cout << "please input the right arguments!" << std::endl;
	}
	string txt_dir = argv[1];    // txt 目录名称
	string ano_str = argv[2];    // 存放XML文件目录

	auto files = get_files(txt_dir, "/file.txt");
	std::sort(files.begin(), files.end());
	int dataBlob = 0;
	string line_str = "";
	for (auto fln : files) {
		std::cout << "###"<<fln<<"###" << std::endl;
		Txt2Xml itTxt2Xml;
		string fln_path = txt_dir + fln;
		ifstream infile(fln_path);
		if (infile) {
			while (getline(infile, line_str)) {
				std::vector<double> vec_points = parseStr(line_str);
				int xmin = vec_points[0];
				int ymin = vec_points[1];
				int xmax = xmin + vec_points[2];
				int ymax = ymin + vec_points[3];
				int width = vec_points[2];
				int height = vec_points[3];
				std::cout << "[" << xmin << " " << ymin << " " << xmax << " " << ymax << "]" << std::endl;
				itTxt2Xml.Init(fln, 850, 1450, 3);

				Txt2Xml::object tempObj;
				tempObj.m_strname = "D";
				tempObj.m_strpose = "D";
				tempObj.m_itruncated = 1;
				tempObj.m_idifficult = 0;
				tempObj.m_strcolor = "gray";
				tempObj.m_stbox = { xmin, ymin, xmax, ymax };
				itTxt2Xml.setObjectInfo(tempObj);
			}
			itTxt2Xml.writeTxt2XML(ano_str);
		}
	}

	system("pause");
	return 0;
}