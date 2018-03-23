#include "misc.h"
#include <iostream>
#include <fstream>
#include  <io.h>

using namespace std;

const std::string currentDateTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d-%H-%M-%S", &tstruct);

    return buf;
}

std::string replace(std::string source_str, std::string substr, std::string new_substr)
{
    std::string out = source_str;
    int inx;
    while (true) {
        inx = out.find(substr);
        if (inx == out.npos) {
            break;
        }
        out.replace(inx, substr.size(), new_substr);
    }
    return out;
}

void GetFileNameFromDir(std::string strDir, std::vector<std::string>& vFileDirList)
{
#ifdef _WIN32
    WIN32_FIND_DATAA ffd;
    //LARGE_INTEGER filesize;
    std::string szDir;
    //size_t length_of_arg;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    DWORD dwError = 0;


    szDir = strDir + "\\*";
    hFind = FindFirstFileA(szDir.c_str(), &ffd);

    if (INVALID_HANDLE_VALUE == hFind)
    {
        cout << "get file name error" << endl;
        return;
    }
    do
    {
        if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            std::string filename = ffd.cFileName;//(const char*)
            std::string filedir = filename;
            vFileDirList.push_back(filedir);
        }
    } while (FindNextFileA(hFind, &ffd) != 0);


    dwError = GetLastError();
    if (dwError != ERROR_NO_MORE_FILES)
    {
        cout << "FindFirstFile error" << endl;
        return;
    }
    FindClose(hFind);
#else
    DIR* dir;
    struct dirent* ptr;
    dir = opendir(strDir.c_str());
    while ((ptr = readdir(dir)) != NULL)
    {
        string path = string(ptr->d_name);
        vFileDirList.push_back(path);
    }
    closedir(dir);
    //sort(vFileDirList.begin(), vFileDirList.end());
#endif
}

vector<string> get_files(string &img_folder, string img_list_file)
{
    vector<string> files;
    //if (GetFileAttributesA(img_folder.c_str()) == FILE_ATTRIBUTE_DIRECTORY)
if(1)    
{
        // check the image list file
        ifstream fs;
        fs.open(img_list_file);
        if (fs.is_open())
        {
            while (!fs.eof())
            {
                string fln;
                fs >> fln;
                files.push_back(fln);
            }
            fs.close();
        }
        else
        {
            GetFileNameFromDir(img_folder, files);
        }
    }
    else
    {
        files.push_back(img_folder);
    }
    return files;
}


string trim(string str) {
	int k = 0, N = (int)str.length();
	int st = 0, ed = N - 1;

	while (k < N && str[k++] == ' ');
	st = k - 1;
	k = N - 1;
	while (k > 0 && str[k--] == ' ');
	ed = k + 1;

	if (st >= 0 && st< N && ed > st) {
		string out = str.substr(st, ed - st + 1);
		return out;
	}
	else {
		return str;
	}
}

int split(const string& str, vector<string>& ret_, string sep = ",") {
	if (str.empty())
	{
		return 0;
	}

	string tmp;
	string::size_type pos_begin = str.find_first_not_of(sep);
	string::size_type comma_pos = 0;

	while (pos_begin != string::npos)
	{
		comma_pos = str.find(sep, pos_begin);
		if (comma_pos != string::npos)
		{
			tmp = str.substr(pos_begin, comma_pos - pos_begin);
			pos_begin = comma_pos + sep.length();
		}
		else
		{
			tmp = str.substr(pos_begin);
			pos_begin = comma_pos;
		}

		if (!tmp.empty())
		{
			ret_.push_back(tmp);
			tmp.clear();
		}
	}
	return 0;
}

std::vector<double> parseStr(std::string inStr) {
	std::vector<double> result;
	string valstr = inStr;
	if (valstr.length() == 0) {
		return result;
	}
	valstr = trim(valstr);
	vector<string> strlist;
	split(valstr, strlist, ",");
	if (strlist.size() == 1) {
		split(valstr, strlist, " ");
	}
	char *end = NULL;
	for (int i = 0; i < strlist.size(); i++) {
		string double_val = trim(strlist[i]);
		try {
			double d = strtod(double_val.c_str(), &end);
			if (end) {
				result.push_back(d);
			}
		}
		catch (void*) {

		}
	}
}

bool pathExist(string dir) {
	if (_access(dir.c_str(), 0) == -1) {
		return false;
	}
	return true;
}

int Rand(int num) {
	if (num <= 0)
		return 0;
	else {
		int rand_value = rand() % num;
		return rand_value;
	}
	return 0;
}
