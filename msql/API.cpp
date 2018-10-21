#include "stdafx.h"
#include "API.h"
using namespace std;
bool API::selectrecord(const std::string&tablename, std::vector<std::string>*selectinfo, vector<Condition>*condition)
{
	if (!mc.ifTableExist(tablename))
	{
		cout << "The table you select does not exist!" << endl;
		return false;
	}

	TableNode&table = mc.getTableInfo(tablename);
	vector<AttriValue>attrsele;
	for (auto &i : table.AttributeList)
	{
		for (int j = 0; j < (*selectinfo).size(); ++j)
		{
			if ((*selectinfo)[j] == i.AtrributeName)
			{
				attrsele.push_back(i);
			}
		}
	}
	if ((*selectinfo).size() == 0)
	{
		for (auto &j : table.AttributeList)
		{
			(attrsele).push_back(j);
		}
	}
	return mr.selectop(table, &attrsele, condition);
	//return mr.Select(table, &attrsele, condition);
}
bool API::deleterecord(const std::string&tablename, vector<Condition>*condition)
{
	if (!mc.ifTableExist(tablename))
	{
		cout << "The table you delete record does not exist!" << endl;
		return false;
	}
	TableNode&table = mc.getTableInfo(tablename);
	vector<AttriValue>attrwithtree;
	for (auto &i : table.AttributeList)
	{
		if (i.isPrimary || i.isUnique)
		{
			for (int j = 0; j < (*condition).size(); ++j)
			{
				if (i.AtrributeName == (*condition)[j].attriName)
				{
					attrwithtree.push_back(i);
				}
			}
		}
	}

	int state = mr.Delete(table, condition);
	if (state == 2)
	{

		string tmpname=table.TableName;
		vector<AttriValue>tmpa;
		for (auto &i : table.AttributeList)
		{
			tmpa.push_back(i);
		}
		droptable(tmpname);
		createtable(tmpname,&tmpa);
		return 1;
	}
	else {
		return state;
	}
}
bool API::createtable(const std::string&tablename, vector<AttriValue>*valuein)
{
	if (mc.ifTableExist(tablename))
	{
		cout << "The table you create has already exist!" << endl;
		return false;
	}
	list<AttriValue>in;
	for (auto &i : *valuein)
	{
		in.push_back(i);
	}
	return mc.CreateTable(tablename, in);

}
bool API::droptable(const std::string&tablename)
{
	if (!mc.ifTableExist(tablename))
	{
		cout << "The table you delete does not exist!" << endl;
		return false;
	}
	TableNode m = mc.getTableInfo(tablename);
	mr.deletemap(m);
	return mc.deleteTable(tablename);
}
bool API::createindex(const std::string&indexname, const std::string&tablename, const std::string&atrrubename)
{
	if (!mc.ifTableExist(tablename))
	{
		cout << "The table you create index does not exist!" << endl;
		return false;
	}
	if (mc.ifIndexExist(indexname))
	{
		cout << "The index you create does already exist!" << endl;
		return false;
	}
	return mc.CreateIndex(mc.getTableInfo(tablename), indexname, atrrubename);
}
bool API::dropindex(const std::string&indexname)
{
	if (!mc.ifIndexExist(indexname))
	{
		cout << "The Index you delete does not exist!" << endl;
		return false;
	}
	return mc.deleteIndex(indexname);
}
bool API::insertrecord(const std::string&tablename, vector<std::string>*info)
{
	if (!mc.ifTableExist(tablename))
	{
		cout << "The table you insert into does not exist!" << endl;
		return false;
	}
	TableNode a = mc.getTableInfo(tablename);
	vector<AttriValue>infoinsert;
	int tablesz = a.AttributeList.size();
	int loc = -1;
	for (auto &i : a.AttributeList)
	{
		loc++;
		infoinsert.push_back(i);
		if (i.isPrimary && (*info)[loc].size() == 0)
		{
			cerr << "Null Primary key" << endl;
			return false;
		}
		//cout << (*info)[loc]<<(*info)[loc].size() << endl;
		if (i.type == 0)
		{
			infoinsert[loc].intVal = atoi((*info)[loc].c_str());
			//cout << "Int insert" << infoinsert[loc].intVal << endl;
			//system("pause");
		}
		else if (i.type == 1)
		{
			infoinsert[loc].FloatVal = atof((*info)[loc].c_str());
			//cout << "Float insert" << infoinsert[loc].FloatVal << endl;
			//system("pause");
		}
		else {
			infoinsert[loc].strVal = (*info)[loc];
		}
	}
	//system("pause");
	return mr.Insert(a, &infoinsert);
}
