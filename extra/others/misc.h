#pragma once

#include <sys/types.h>
#ifdef _WIN32
#include <Windows.h>
#include <strsafe.h>
#else
#include "dirent.h"
#endif
#include <time.h>
#include <string>
#include <vector>

const std::string currentDateTime();

std::string replace(std::string source_str, std::string substr, std::string new_substr);

void GetFileNameFromDir(std::string strDir, std::vector<std::string>& vFileDirList);

std::vector<std::string> get_files(std::string &img_folder, std::string img_list_file);

std::string trim(std::string str);

std::vector<double> parseStr(std::string inStr);

bool pathExist(std::string dir);

int Rand(int num);