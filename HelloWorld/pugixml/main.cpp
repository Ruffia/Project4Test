#include <iostream>
#include <stdio.h>
#include <windows.h>
using namespace std;
#include "Scenario.h"

#include "pugixml.hpp"
#include "pugiconfig.hpp"
using namespace pugi;

bool ReadXml(const string& fileName)
{
	DWORD dwErr = 0;
	xml_document doc;
	if (!doc.load_file(fileName.c_str())) { //加载xml文件
		dwErr = GetLastError();
		cout << "load file faild"<< "Err = "<<dwErr;
		return false;
	}
	xml_node root = doc.child("root");  //根节点
	cout << "id:" << root.attribute("id").value() << endl;  //属性值

	xml_node node1 = root.child("node1");
	cout << "name:" << node1.attribute("name").value() << "  age:" <<
		node1.attribute("age").value() << "  weight:" << node1.attribute("weight").value() << endl;

	xml_node node2 = root.child("node2");

	for (auto node : node2.children()) {
		cout << "name:" << node.child("name").text().as_string() << endl;   //字符型
		cout << "age:" << node.child("age").text().as_int() << endl;        //整型
	}

	return true;
}

bool WriteXml(const string& fileName)
{
	xml_document doc;
	//xml声明部分
	xml_node declaration_node = doc.append_child(pugi::node_declaration);
	declaration_node.append_attribute("version") = "1.0";
	declaration_node.append_attribute("encoding") = "UTF-8";

	pugi::xml_node root = doc.append_child("root"); //根节点
	root.append_attribute("id") = "S1"; //根节点属性

	for (int i = 0; i < 3; ++i) {
		xml_node node = root.append_child("li");
		node.append_attribute("x") = i;
		node.append_attribute("y").set_value(i);
	}
	root.append_child("name").text().set("xiaohua");
	doc.save_file(fileName.c_str());

	return true;
}


bool WriteXml(const string& fileName, const Scenario& o)
{
	xml_document doc;
	//xml声明部分
	xml_node declaration_node = doc.append_child(pugi::node_declaration);
	declaration_node.append_attribute("version") = "1.0";
	declaration_node.append_attribute("encoding") = "UTF-8";

	pugi::xml_node root = doc.append_child("root"); //根节点
	//root.append_attribute("id") = "S1"; //根节点属性

	xml_node node = root.append_child("Settings");
	node.append_attribute("SampleName") = o.szSampleName;
	node.append_attribute("CreateTime") = o.szCreateTime;
	node.append_attribute("AuthorName") = o.szAuthorName;
	node.append_attribute("Description") = o.szDescription;

	{
		xml_node ChildNode = node.append_child("HVType");
		ChildNode.append_attribute("Value") = o.HVType;
		ChildNode.append_attribute("Unit") = "";
	}

	{
		xml_node ChildNode = node.append_child("HV");
		ChildNode.append_attribute("Value") = o.HV;
		ChildNode.append_attribute("Unit") = "V";
	}

	{
		xml_node ChildNode = node.append_child("Bias");
		ChildNode.append_attribute("Value") = o.Bias;
		ChildNode.append_attribute("Unit") = o.HVType == 1?"V":"mA";
	}

	{
		xml_node ChildNode = node.append_child("FilamentCurrent");
		ChildNode.append_attribute("Value") = o.FilamentCurrent;
		ChildNode.append_attribute("Unit") = "A";
	}


	{
		xml_node ChildNode = node.append_child("Contrast");
		ChildNode.append_attribute("Value") = o.Contrast;
		ChildNode.append_attribute("Unit") = "";
	}

	{
		xml_node ChildNode = node.append_child("Brightness");
		ChildNode.append_attribute("Value") = o.Brightness;
		ChildNode.append_attribute("Unit") = "";
	}


	{
		xml_node ChildNode = node.append_child("CondenserLens");
		ChildNode.append_attribute("Value") = o.CondenserLens;
		ChildNode.append_attribute("Unit") = "";
	}


	{
		xml_node ChildNode = node.append_child("ObjectiveLens");
		ChildNode.append_attribute("Value") = o.ObjectiveLens;
		ChildNode.append_attribute("Unit") = "";
	}


	{
		xml_node ChildNode = node.append_child("Magnifier");
		ChildNode.append_attribute("Value") = o.Magnifier;
		ChildNode.append_attribute("Unit") = "";
	}


	{
		xml_node ChildNode = node.append_child("BeemAlignmentX");
		ChildNode.append_attribute("Value") = o.BeemAlignmentX;
		ChildNode.append_attribute("Unit") = "";
	}


	{
		xml_node ChildNode = node.append_child("BeemAlignmentY");
		ChildNode.append_attribute("Value") = o.BeemAlignmentY;
		ChildNode.append_attribute("Unit") = "";
	}


	{
		xml_node ChildNode = node.append_child("StigmatorX");
		ChildNode.append_attribute("Value") = o.StigmatorX;
		ChildNode.append_attribute("Unit") = "";
	}


	{
		xml_node ChildNode = node.append_child("StigmatorY");
		ChildNode.append_attribute("Value") = o.StigmatorY;
		ChildNode.append_attribute("Unit") = "";
	}

	doc.save_file(fileName.c_str());
	return true;
}


bool Read2Scenario(const string& fileName, Scenario& o)
{
	DWORD dwErr = 0;
	xml_document doc;
	if (!doc.load_file(fileName.c_str())) { //加载xml文件
		dwErr = GetLastError();
		return false;
	}

	xml_node root = doc.child("root");  //根节点
	xml_node nodeSettings = root.child("Settings");

	sprintf_s(o.szSampleName,"%s",nodeSettings.attribute("SampleName").as_string(""));
	sprintf_s(o.szCreateTime,"%s",nodeSettings.attribute("CreateTime").as_string(""));
	sprintf_s(o.szAuthorName,"%s",nodeSettings.attribute("AuthorName").as_string(""));
	sprintf_s(o.szDescription,"%s",nodeSettings.attribute("Description").as_string(""));

	{
		xml_node ChildNode = nodeSettings.child("HVType");
		o.HVType = ChildNode.attribute("Value").as_double(0.0);
	}

	{
		xml_node ChildNode = nodeSettings.child("HV");
		o.HV = ChildNode.attribute("Value").as_double(0.0);
	}

	{
		xml_node ChildNode = nodeSettings.child("Bias");
		o.Bias = ChildNode.attribute("Value").as_double(0.0);
	}

	{
		xml_node ChildNode = nodeSettings.child("FilamentCurrent");
		o.FilamentCurrent = ChildNode.attribute("Value").as_double(0.0);
	}


	{
		xml_node ChildNode = nodeSettings.child("Contrast");
		o.Contrast = ChildNode.attribute("Value").as_double(0.0);
	}

	{
		xml_node ChildNode = nodeSettings.child("Brightness");
		o.Brightness = ChildNode.attribute("Value").as_double(0.0);
	}


	{
		xml_node ChildNode = nodeSettings.child("CondenserLens");
		o.CondenserLens = ChildNode.attribute("Value").as_double(0.0);
	}


	{
		xml_node ChildNode = nodeSettings.child("ObjectiveLens");
		o.ObjectiveLens = ChildNode.attribute("Value").as_double(0.0);
	}


	{
		xml_node ChildNode = nodeSettings.child("Magnifier");
		o.Magnifier = ChildNode.attribute("Value").as_double(0.0);
	}


	{
		xml_node ChildNode = nodeSettings.child("BeemAlignmentX");
		o.BeemAlignmentX = ChildNode.attribute("Value").as_double(0.0);
	}


	{
		xml_node ChildNode = nodeSettings.child("BeemAlignmentY");
		o.BeemAlignmentY = ChildNode.attribute("Value").as_double(0.0);
	}


	{
		xml_node ChildNode = nodeSettings.child("StigmatorX");
		o.StigmatorX = ChildNode.attribute("Value").as_double(0.0);
	}


	{
		xml_node ChildNode = nodeSettings.child("StigmatorY");
		o.StigmatorY = ChildNode.attribute("Value").as_double(0.0);
	}

	return true;
}



int main()
{
	char exeFullPath[255] = {0};
	GetModuleFileNameA(NULL,exeFullPath,MAX_PATH);
	char path[255] = {0};
	sprintf(path, "%s", exeFullPath);
	char *exd = strrchr(path, (int)'\\');
	if(exd != NULL)
		*exd = '\0';

	string sPath = path;

	string readFileName = sPath + "\\read.xml";
	ReadXml(readFileName);

	string writeFileName = sPath + "\\write.xml";
	WriteXml(writeFileName);

	{
		//Scenario o;
		//memcpy(o.szSampleName,"Sample01",256);
		//memcpy(o.szCreateTime,"2020-11-11 11:10:11",64);
		//memcpy(o.szAuthorName,"Ruffia",64);
		//memcpy(o.szDescription,"Save a scenario",256);
		//o.HVType = 0;
		//o.HV = 30000;
		//o.Bias = 80;
		//o.FilamentCurrent = 2.42;
		//o.BeemAlignmentX = 1025;
		//o.BeemAlignmentY = 2600;
		//o.Brightness = -1.25;
		//o.CondenserLens = 480;
		//o.ObjectiveLens = 400;
		//o.Contrast = 40;
		//o.Magnifier = 3441;
		//o.StigmatorX = 630;
		//o.StigmatorY = -1543;

		//string sTestFileName = sPath + "\\Test.xml";
		//WriteXml(sTestFileName,o);
	}


	{
		Scenario o;
		string sTestFileName = sPath + "\\Test.xml";
		Read2Scenario(sTestFileName,o);
	}

	return 0;
}
