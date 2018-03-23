
#ifndef CONFIG_H
#define CONFIG_H
#include <map>
#include <string>
#include <vector>

//#define EXPORT_DLL_MODE


#ifdef EXPORT_DLL_MODE
class __declspec(dllexport) Config
#else
class Config
#endif
{
public:

	/**
	* @brief  Config :
	* @Param bool notfoundCreate : if this is set to true,
	it will create a new key-value pair when it cannot found a key
	* @return  :
	*/
	Config(bool notfoundCreate = false);
	~Config();
	/** *****************  core APIs *****************  **/
	int load(const char* pConfigName);
	int save(const char* pConfigName);
	std::string get(std::string key, std::string def = "");
	void set(std::string key, std::string val = "");


	/** *****************  advanced APIs *****************  **/
	// for get from config cache 
	int getInt(std::string key, int def = 0);
	double getDouble(std::string key, double def = 0.0);
	std::string getStr(std::string key, std::string def = "");
	int getDouble2D(std::string key, double &d1, double &d2);
	std::vector<double> getDoubleVector(std::string key);
	std::vector<double> getDoubleVectorEx(std::string key);

	std::vector<std::string> getStringVector(std::string key);
	std::vector<std::string> getAllKeys();
	std::vector<int> getIntVector(std::string key);
	const std::map<std::string, std::string>getAllData();

	// for set to config cache 
	void setInt(std::string key, int val = 0);
	void setDouble(std::string key, double val = 0.0);
	void setStr(std::string key, std::string val = "");

	void setIntVector(std::string key, const std::vector<int>& data);
	void setDoubleVector(std::string key, const std::vector<double>& data);
	void setDoubleVectorEx(std::string key, std::vector<double>  dVec);

	void setStringVector(std::string key, const std::vector<std::string>& data);
	// convert the current data (data only, no comments) to 
	// operator std::map<std::string, std::string>();
public:
	// here I add some useful string handle tools for us to handle the string 
	static std::string to_string2(const double val, const int n = 6);
	static std::string trim(std::string str);
	static int split(const std::string& str, std::vector<std::string>& ret_, std::string sep = ",");
    void print();

private:
	//std::map<std::string, std::string>   data;
	//std::map<std::string, std::string>   comment_data;
	typedef struct {
		std::string key;
		std::string val;
		std::string comment_data;
	} KeyVal;
	std::vector<KeyVal> data; 
	int load(std::istream & in_stream);
	int save(std::ostream & out_stream);

	std::string remarks;
	bool notfoundCreate;

};


#endif // CONFIG_H
