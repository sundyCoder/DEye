#include "config.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <math.h>
using namespace std;
//int split(const string& str, vector<string>& ret_, string sep = ",");

std::string Config::to_string2(const double val, const int n /* = 6 */){
	std::ostringstream out;
	int nn = n; 
	
	// make the precision number as soon as possible 
	int k = 0; 
	while (k<n){
		double scale_val = pow(10, k) * val; 
		int vali = scale_val;
		if (double(vali) == scale_val){
			nn = k; 
			break;
		}
		k++; 
	}
	out << std::fixed<<std::setprecision(nn) << val;
	return out.str();
}

void Config::print(){
	std::cout << "-----------------------------------"<< std::endl;
	for (auto & kv : data){
		if (kv.comment_data.length()){
			std::cout << kv.comment_data; 
		}
		else{
			//out << "\n";
		}
		std::cout << "  " + kv.key << "=" << kv.val << std::endl; 
	}
	std::cout << "-----------------------------------"<< std::endl;
}


string Config::trim(string str)
{


	int k = 0, N = (int)str.length();
	int st = 0, ed = N - 1;

	while (k < N && str[k++] == ' ');
	st = k - 1;
	k = N - 1;
	while (k > 0 && str[k--] == ' ');
	ed = k + 1;

	if (st >= 0 && st< N && ed > st){
		string out = str.substr(st, ed - st + 1);
		return out;
	}
	else{
		return str;
	}
	
	
}

Config::Config(bool notfoundCreate_) :notfoundCreate(notfoundCreate_)
{

}


Config::~Config()
{
}


int Config::load(const char* pConfigName)
{
	ifstream fio(pConfigName );
	if(!fio.is_open())
    {
		return -1;
	}
	
	return load(fio); 
}

int Config::load(std::istream & in_stream)
{
	string line;

	string comment = "";
	// read the remarks; 

	while (getline(in_stream, line) && line.size() > 0) {

		if (line.size() > 0 && line[0] == '#') {
			remarks += line + "\n";
		}

		if (line.size() > 0 && line[0] != '#' && line[0] != '[') {
			in_stream.seekg(in_stream.beg);  // there is a bug here !!! Please revise it as soon as posssible. Contact wilman for details! 
			break;
		}

		getline(in_stream, line);
	}
	// read the settings; 
	while (getline(in_stream, line))
	{
		// remove the enter char 
		if (line.size()>0 && line[line.size() - 1] == 13)
		{
			line = line.substr(0, line.size() - 1);
		}
		/* std::cout << "c:[" << line.substr(0, line.size()-1)<<"]"<<int(line[line.size()-1]) <<endl; */
		// parser
		if (line.length() > 2 && line[0] != '#' && line[0] != '[')
		{
			// read the key value; 
			int inx = (int)line.find_first_of('=');
			if (inx < 0) {
				//printf("Warning: un-support format!: \"%s\" \n", line.c_str());
				continue;
			}
			string key = line.substr(0, inx);
			key = trim(key);

			// convert to lower case 
			transform(key.begin(), key.end(), key.begin(), ::tolower);
			if (line.size() < inx + 2) {
				printf("warning: some key are not set properly.\"%s\" \n", key.c_str());
				// cout << "key:" << key << " line " << line <<endl; 
				continue;
			}
			string val = line.substr(inx + 1);
			val = trim(val);

			// storage to cache  
			/*
			data[key.c_str()] = val;
			if(comment.length() > 0){

			comment_data[key.c_str()] = comment;
			}
			comment = "";
			*/
			data.push_back({ key, val, comment });
			comment = "";
			//cout<<"line:"<<line << " k-v:"<<key<<"-" <<val<<endl;
		}
		else {
			comment += line + "\n"; // this line is a comment line, append the "\n" at the end; 
		}

	}
	return 0;
}

int Config::save(const char* pConfigName)
{

    ofstream out(pConfigName);
	if (!out){
		return -1;
	}

	return save(out); 
}

int Config::save(std::ostream & out)
{
	map<string, string>::iterator it;
	if (remarks.size() > 0){
		out << remarks << endl;
	}

	for (auto & kv : data){
		if (kv.comment_data.length()){
			out << kv.comment_data; 
		}
		else{
			//out << "\n";
		}
		out << kv.key << "=" << kv.val << std::endl; 
	}
	//for (it = data.begin(); it != data.end(); it++){
	//	string comment = comment_data[it->first];
	//	if (comment.length() > 0){
	//		out << comment;
	//	}
	//	else{
	//		//out << "\n";
	//	}
	//	out << it->first << "=" << it->second << std::endl; 
	//}
	return 0;
}
std::string Config::get(std::string key, std::string def){
	return getStr(key, def);
}
std::string Config::getStr(std::string key, std::string def)
{
	map<string,string>::iterator it;
	// to lower case 
	transform(key.begin(), key.end(), key.begin(), ::tolower);
	// get the value
	for (auto &kv : data){
		if (kv.key == key){
			string val = kv.val;
			// remove the ';' at the end of the string 
			if (val[val.size() - 1] == ';'){
				val = val.substr(0, val.size() - 1);
			}
			return val;
		}
	}
    {
		// not found the key 
		if (notfoundCreate){ setStr(key, def); }
		return def;
	}
}

int Config::getInt(std::string key,int def)
{
	string val = getStr(key);
	
	if (val.length() > 0)
	{
		int out = atoi(val.c_str());
		return out;
	}
	else
	{
		// not found the key 
		if (notfoundCreate){ setInt(key, def); }
		return def;
	}

}

double Config::getDouble(std::string key, double def)
{
	string val = getStr(key);
	if (val.length() > 0){
		char *end = NULL;
		double d = strtod(val.c_str(), &end);
		if (*end){
			return def;
		}
		return d;
	}
	else{
		// not found the key 
		if (notfoundCreate){ setDouble(key, def); }
		return def;
	}
   
}

void Config::setInt(std::string key, int val)
{
	long long lVal = val;
	if (!key.empty()){
		setStr(key, std::to_string(lVal));
	}
}



void Config::setDouble(std::string key, double val)
{
    if(!key.empty())
    {
        //std::stringstream ss;
        //ss << std::fixed << std::setprecision(15) << val;
		setStr(key, to_string2(val));
    }
}

void Config::setStr(std::string key, std::string val)
{
	if (!key.empty()){
		transform(key.begin(), key.end(), key.begin(), ::tolower);
		bool set_val = false;
		for (auto &kv : data){
			if (kv.key == key){
				kv.val = val; 
				set_val = true; 
				break; 
			}
		}
		if (!set_val){
			data.push_back({ key, val });
		}
	}  
}

std::vector<double> Config::getDoubleVector(std::string key)
{
	//std::vector<double> result;
	//vector<string> strlist;
	//strlist = getStringVector(key);
	//char *end = NULL;
	//for (int i = 0; i < strlist.size(); i++){
	//	string double_val = trim(strlist[i]);
	//	try{
	//		double d = strtod(double_val.c_str(), &end);
	//		if (end){
	//			result.push_back(d);
	//		}
	//	}
	//	catch (void*){

	//	}
	//}
	//return result; 
	return getDoubleVectorEx(key); 
}


std::vector<double> Config::getDoubleVectorEx(std::string key)
{
	std::vector<double> result;

	string valstr = "";
	valstr = getStr(key);
	if (valstr.length() == 0){
		return result;
	}
	valstr = trim(valstr);
    //printf("vec: %s\n" , valstr.c_str());
	// check if there is []; 
	if (valstr[0] == '['){
		valstr = valstr.substr(1);
	}
	if (valstr.size() > 0 && valstr[valstr.size() - 1] == ']'){
		valstr = valstr.substr(0, valstr.size() - 1);
	}
	vector<string> strlist;
	split(valstr, strlist);
    if (strlist.size() == 1) {
        split(valstr, strlist," ");
    }
	char *end = NULL;
	for (int i = 0; i < strlist.size(); i++){

		string double_val = trim(strlist[i]);
		try{
			double d = strtod(double_val.c_str(), &end);
			// debug code 
			//printf("%s is %.01f\n", double_val.c_str(), d);

			if (end){
				result.push_back(d);
			}
		}
		catch (void*){

		}
	}
	return result;
}

int Config::getDouble2D(std::string key, double &d1, double &d2)
{
	vector<double> arr = getDoubleVector(key);
	if (arr.size() >= 2){
		d1 = arr[0];
		d2 = arr[1]; 
		return 0; 
	}
	else{
		return -1; 
	}
}


std::vector<std::string> Config::getStringVector(std::string key)
{
	std::vector<std::string> result;
	string valstr = getStr(key);
	if (valstr.length() < 2){
		return result;
	}
	if (valstr[0] != '[' || valstr[valstr.length() - 1] != ']'){
		return result;
	}
	valstr = valstr.substr(1, valstr.length() - 2);
	split(valstr, result);
	return result;
}

const std::map<string, string> Config::getAllData()
{
	std::map<string, string> data_;
	for (auto&kv : data){
		data_[kv.key] = kv.val;
	}
	return data_; 
}

void Config::set(std::string key, std::string val /*= ""*/)
{
	setStr(key, val);
}

void Config::setIntVector(std::string key, const std::vector<int>&data)
{
	// prepare the val string 
	string val = "[";
	for (int i = 0; i < data.size(); i++){
		val += std::to_string(data.at(i)) + ",";
	}
	if (val[val.size() - 1] == ','){
		val[val.size() - 1] = ']';
	}
	else{
		val += "]";
	}
	setStr(key, val);
}

void Config::setDoubleVector(std::string key, const std::vector<double>& data)
{
	// prepare the val string 
	string val = "[";
	for (int i = 0; i < data.size(); i++){
		val += to_string2(data[i]) + ",";
	}
	if (val[val.size() - 1] == ','){
		val[val.size() - 1] = ']';
	}
	else{
		val += "]";
	}
	setStr(key, val);
}

void Config::setStringVector(std::string key, const std::vector<string>& data)
{
	string val = "[";
	for (int i = 0; i < data.size(); i++){
		val += data[i] + ",";
	}
	if (val[val.size() - 1] == ','){
		val[val.size() - 1] = ']';
	}
	else{
		val += "]";
	}
	setStr(key, val);
}

std::vector<std::string> Config::getAllKeys()
{
	vector<string> keys;
	for (auto &kv:data){
		keys.push_back(kv.key); 
	}
	return keys;
}

int Config::split(const string& str, vector<string>& ret_, string sep)
{
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

void Config::setDoubleVectorEx(std::string key, std::vector<double> dVec)
{

	if (!key.empty())
	{
		std::stringstream ss;

		for (int i = 0; i < dVec.size(); i++){
			if (i != 0) ss << ",";
			// ss << std::fixed << std::setprecision(15) << dVec[i];
			ss << to_string2(dVec[i]); 
		}

		setStr(key, ss.str());
	}
}
