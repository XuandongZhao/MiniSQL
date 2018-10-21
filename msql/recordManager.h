#pragma once
#ifndef MY_RECORDMANAGER_H
#define MY_RECORDMANAGER_H

#include <string>
#include <iostream>
#include "buffmanage.h"
#include "CatalogManager.h"
#include "Condition.h"
#include "AttriValue.h"
#include "bplus_tree.h"
#include <queue>
#include <cstdlib>
#include <map>
#include <unordered_map>
#include "recordManager.h"
#include <stdlib.h>
#include <stdio.h>


enum selectOrDelete { enum_sel, enum_del };

class position
{
public:
	int blocknum;
	int offset;
};

extern BufferManager m;

class RecordManager
{
public:
	typedef Block*pointer;
	RecordManager();
	~RecordManager();
	bool deletemap(TableNode &tablein);
	int Select(TableNode &tableIn, std::vector<AttriValue>*AttrSelected, std::vector<Condition>*ConditionApplied);
	bool Insert(TableNode &tableIn, std::vector<AttriValue>*ValueToInsert);
	bool selectop(TableNode& tablein, std::vector<AttriValue>*AttrSelected, std::vector<Condition>*ConditionAppied);
	int Delete(TableNode &tableIn, std::vector<Condition>*ConditionApplied);
private:
	std::string changekey(const std::string&keyin, int type);
	std::string getkey(char*record, int offset, int length);
	bool ConditionSatisfied(TableNode &tableIn, char* recordBegin, std::vector<Condition>* ConditionApplied);
	void DeleteInBTree(TableNode &tableIn, char* attriValBegin);
	int SelectRecordEachBlock(TableNode &tableIn, std::vector<AttriValue>*AttrSelected, std::vector<Condition>*ConditionApplied, pointer block, int rnum, int op);
	int GetRecordSize(TableNode &tableIn);
	int GetTypeSize(int type);
	bool ContentSatisfied(char* content, int type, Condition* condition);
	void PrintARecord(TableNode &tableIn, char* recordBegin, std::vector<AttriValue>* AttrSelected);
	void PrintContent(char * content, int type);
	std::string GetKeyString(std::vector<AttriValue>*ValueToInsert, int n);
	bool DeleteARecord(TableNode &tableIn, char* validBit);
	bool UpdateRecordNum(TableNode &tableIn, pointer block, int delete_amount);
	bool InsertInNullBlock(TableNode &tableIn, std::vector<AttriValue>*ValueToInsert);
	void UpdateBTree(TableNode &tableIn, std::string attrName, std::string attrValue, int blockOffset, int innerOffset);
	///   int GetInnerOffset(int i, int recordSize, std::vector<AttriValue>*ValueToInsert, int j);
	std::string GetTableName(std::string tableName);
	typedef std::map<std::string, std::queue<int> >Mymap;
	Mymap mymap;
};


#endif //NEWRECORDMANAGER_RECORDMANAGER_H
