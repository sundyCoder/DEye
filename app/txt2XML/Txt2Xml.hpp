/************************************************************************
*  Author: Sundy
*  E-mail: sundycoder@gmail.com
*  Date:  Jan 09,2018
************************************************************************/
#include <opencv2/core/core.hpp>

#include "libxml/encoding.h"
#include "libxml/xmlwriter.h"
#include <string>
#include <iostream>

//#define MY_ENCODING "ISO-8859-1"
#define MY_ENCODING "US-ASCII"

using namespace std;

namespace txt2xml {

	class Txt2Xml {
	public:
	public:
		typedef struct
		{
			int xmin;
			int ymin;
			int xmax;
			int ymax;
		}bndbox;

		typedef struct
		{
			std::string m_strname;
			std::string m_strpose;
			std::string m_strcolor;
			int m_itruncated;
			int m_ioccluded;
			bndbox m_stbox;
			int m_idifficult;

		}object;

		Txt2Xml();
		~Txt2Xml();

		void Init(std::string filename, int iw,  int ih, int idepth);
		void Reset();
		void setObjectInfo(const Txt2Xml::object & _stobject);
		void writeTxt2XML(std::string ano_str);
		int parserXML(std::string _strAnnoFile, std::vector<object> &_vecObj);

	private:
		std::string  m_strTopDir = "";
		std::string m_strfolder = "VOC2007";
		std::string m_strfilename;

	protected:
		std::string m_strdatabase;
		std::string m_strannotation;
		std::string m_strimage;

		int m_iwidth;
		int m_iheight;
		int m_idepth;
		int m_segmented;

		std::vector<object> m_vecOject;
	}; 
	Txt2Xml::Txt2Xml() {
		m_strfolder = "GMA";

		m_strdatabase = "Defect Eye Database";
		m_strannotation = "DEye2018";
		m_strimage = "DEye";

		m_iwidth = 0;
		m_iheight = 0;
		m_idepth = 0;
		m_segmented = 0;
		m_strfilename = "";
	}

	Txt2Xml::~Txt2Xml() {
		if (!m_vecOject.empty()) {
			m_vecOject.clear();
		}
	}


	void Txt2Xml::Init(std::string _strfilename, int _iw, int _ih, int _idepth) {
		m_strfilename = _strfilename;
		m_iwidth = _iw;
		m_iheight = _ih;
		m_idepth = _idepth;
		if (!m_vecOject.empty()) {
			m_vecOject.clear();
		}
	}

	void Txt2Xml::Reset() {
		Init("", 0, 0, 0);
	}

	void Txt2Xml::setObjectInfo(const Txt2Xml::object & _stobject) {
		m_vecOject.push_back(_stobject);
	};

	void Txt2Xml::writeTxt2XML(std::string ano_str) {
		//string strSavePath = m_strTopDir + "\\" + m_strfolder + "\\Annotations\\" + m_strfilename + ".xml";
		string strSavePath = ano_str + "/" + m_strfilename.substr(0,m_strfilename.length() - 14) + ".xml";

		//添加换行符等，形成标准格式
		xmlKeepBlanksDefault(0);
		xmlIndentTreeOutput = 1;

		/************************************************************************/
		/* example form internet
		* */
		/************************************************************************/
#if 0
		//定义文档和节点指针
		xmlDocPtr doc = xmlNewDoc(BAD_CAST"1.0");
		xmlNodePtr root_node = xmlNewNode(NULL, BAD_CAST"root");

		//设置根节点
		xmlDocSetRootElement(doc, root_node);

		//在根节点中直接创建节点
		xmlNewTextChild(root_node, NULL, BAD_CAST "newNode1", BAD_CAST "newNode1 content");
		xmlNewTextChild(root_node, NULL, BAD_CAST "newNode2", BAD_CAST "newNode2 content");
		xmlNewTextChild(root_node, NULL, BAD_CAST "newNode3", BAD_CAST "newNode3 content");

		//创建一个节点，设置其内容和属性，然后加入根结点
		xmlNodePtr node = xmlNewNode(NULL, BAD_CAST"node2");
		xmlNodePtr content = xmlNewText(BAD_CAST"NODE CONTENT");
		xmlAddChild(root_node, node);
		xmlAddChild(node, content);
		xmlNewProp(node, BAD_CAST"attribute", BAD_CAST "yes");

		//创建一个儿子和孙子节点
		node = xmlNewNode(NULL, BAD_CAST "son");

		xmlAddChild(root_node, node);

		xmlNodePtr grandson = xmlNewNode(NULL, BAD_CAST "grandson");
		xmlAddChild(node, grandson);

		xmlAddChild(grandson, xmlNewText(BAD_CAST "This is a grandson node"));

		//存储xml文档
		int nRel = xmlSaveFormatFile(strSavePath.c_str(), doc, 1);
		//释放文档内节点动态申请的内存
		xmlFreeDoc(doc);
#endif

		//定义文档和节点指针
		xmlDocPtr doc = xmlNewDoc(NULL);
		xmlNodePtr root_node = xmlNewNode(NULL, BAD_CAST"annotation");
		//设置根节点
		xmlDocSetRootElement(doc, root_node);

		//在根节点中直接创建节点
		xmlNewTextChild(root_node, NULL, BAD_CAST "folder", BAD_CAST(m_strfolder.c_str()));
		xmlNewTextChild(root_node, NULL, BAD_CAST "filename", BAD_CAST(string(m_strfilename.substr(0,m_strfilename.length() - 9)).c_str()));
		xmlNewTextChild(root_node, NULL, BAD_CAST "segmented", BAD_CAST "0");

		//创建一个儿子和孙子节点
		xmlNodePtr node0 = xmlNewNode(NULL, BAD_CAST "source");
		xmlAddChild(root_node, node0);

		xmlNodePtr node00 = xmlNewNode(NULL, BAD_CAST "database");
		xmlAddChild(node0, node00);
		xmlAddChild(node00, xmlNewText(BAD_CAST(m_strdatabase.c_str())));

		node00 = xmlNewNode(NULL, BAD_CAST "annotation");
		xmlAddChild(node0, node00);
		xmlAddChild(node00, xmlNewText(BAD_CAST(m_strannotation.c_str())));

		node00 = xmlNewNode(NULL, BAD_CAST "image");
		xmlAddChild(node0, node00);
		xmlAddChild(node00, xmlNewText(BAD_CAST(m_strimage.c_str())));

		xmlNodePtr node1 = xmlNewNode(NULL, BAD_CAST "size");
		xmlAddChild(root_node, node1);
		xmlNewTextChild(node1, NULL, BAD_CAST "width", BAD_CAST(cv::format("%d", m_iwidth).c_str()));
		xmlNewTextChild(node1, NULL, BAD_CAST "height", BAD_CAST(cv::format("%d", m_iheight).c_str()));
		xmlNewTextChild(node1, NULL, BAD_CAST "depth", BAD_CAST(cv::format("%d", m_idepth).c_str()));

		int iobj = m_vecOject.size();
		for (int i = 0; i<iobj; i++)
		{
			xmlNodePtr node2 = xmlNewNode(NULL, BAD_CAST "object");
			xmlAddChild(root_node, node2);
			xmlNewTextChild(node2, NULL, BAD_CAST "name", BAD_CAST(m_vecOject[i].m_strname.c_str()));
			xmlNewTextChild(node2, NULL, BAD_CAST "pose", BAD_CAST(m_vecOject[i].m_strpose.c_str()));
			xmlNewTextChild(node2, NULL, BAD_CAST "truncated", BAD_CAST("0"));
			xmlNewTextChild(node2, NULL, BAD_CAST "occluded", BAD_CAST("0"));

			xmlNodePtr node20 = xmlNewNode(NULL, BAD_CAST "bndbox");
			xmlAddChild(node2, node20);

			xmlNewTextChild(node20, NULL, BAD_CAST "xmin", BAD_CAST(cv::format("%d", m_vecOject[i].m_stbox.xmin).c_str()));
			xmlNewTextChild(node20, NULL, BAD_CAST "ymin", BAD_CAST(cv::format("%d", m_vecOject[i].m_stbox.ymin).c_str()));
			xmlNewTextChild(node20, NULL, BAD_CAST "xmax", BAD_CAST(cv::format("%d", m_vecOject[i].m_stbox.xmax).c_str()));
			xmlNewTextChild(node20, NULL, BAD_CAST "ymax", BAD_CAST(cv::format("%d", m_vecOject[i].m_stbox.ymax).c_str()));

			xmlNewTextChild(node2, NULL, BAD_CAST "color", BAD_CAST(m_vecOject[i].m_strcolor.c_str()));
			xmlNewTextChild(node2, NULL, BAD_CAST "difficult", BAD_CAST(cv::format("%d", m_vecOject[i].m_idifficult).c_str()));

		}

		//存储xml文档
		int nRel = xmlSaveFormatFile(strSavePath.c_str(), doc, 1);
		//释放文档内节点动态申请的内存
		xmlFreeDoc(doc);
	}

	int Txt2Xml::parserXML(std::string _strAnnoFile, std::vector<object> &_vecObj) {
		xmlDocPtr doc;
		xmlNodePtr cur;
		doc = xmlParseFile(_strAnnoFile.c_str());
		if (doc == NULL) {
			return 0;
		}

		cur = xmlDocGetRootElement(doc);
		if (cur == NULL) {
			return 0;
		}

		//object obj;
		string strFilename;

		const xmlChar * rootname = cur->name;
		cur = cur->xmlChildrenNode;
		while (cur != NULL)
		{
			xmlNodePtr subsubject;
			if (!xmlStrcmp(cur->name, (const xmlChar*)"filename")) {
				char * value = (char *)xmlNodeGetContent(cur);
				strFilename = value;

			}
			if (!xmlStrcmp(cur->name, (const xmlChar*)"object"))
			{

				object obj;
				//obj.m_strname = strFilename;
				subsubject = cur->xmlChildrenNode;

				while (subsubject != NULL)
				{
					if (!xmlStrcmp(subsubject->name, (const xmlChar*)"bndbox"))
					{
						xmlNodePtr subsubject2;
						subsubject2 = subsubject->xmlChildrenNode;

						while (subsubject2 != NULL)
						{


							if (!xmlStrcmp(subsubject2->name, (const xmlChar*)"xmin"))
							{
								char * value = (char *)xmlNodeGetContent(subsubject2);
								obj.m_stbox.xmin = atoi(value);
								//sj.strGender = strvalue;
							}

							if (!xmlStrcmp(subsubject2->name, (const xmlChar*)"ymin"))
							{
								char * value = (char *)xmlNodeGetContent(subsubject2);
								obj.m_stbox.ymin = atoi(value);

							}

							if (!xmlStrcmp(subsubject2->name, (const xmlChar*)"xmax"))
							{
								char * value = (char *)xmlNodeGetContent(subsubject2);
								obj.m_stbox.xmax = atoi(value);
								//sj.strRace = strvalue;
							}

							if (!xmlStrcmp(subsubject2->name, (const xmlChar*)"ymax"))
							{
								char * value = (char *)xmlNodeGetContent(subsubject2);
								obj.m_stbox.ymax = atoi(value);
								//sj.strRace = strvalue;
							}

							subsubject2 = subsubject2->next;

						}

					}
					else if (!xmlStrcmp(subsubject->name, (const xmlChar*)"color"))
					{

					}
					else if (!xmlStrcmp(subsubject->name, (const xmlChar*)"name"))
					{
						char * value = (char *)xmlNodeGetContent(subsubject);
						obj.m_strname = value;

					}

					subsubject = subsubject->next;
					//subsubject = subsubject->next;
				}
				_vecObj.push_back(obj);

			}
			cur = cur->next;
		}

		return 1;
	}

	
}

