#pragma once
#ifndef MY_BUFFMANAGE_H
#define MY_BUFFMANAGE_H
#include <string>
#include <utility>
#include <string>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include "basicdata.h"


class BufferManager
{
private:
	const int MAXBLOCKNUM = 1024;
	struct Block* head;
	Block* tail;
	class File* fileHead;
	int number;
	Block* readnewblock(std::string FileName, int offset, Block* tmpTail);
	bool isFull();
public:
	BufferManager();
	~BufferManager();
	void flushoneblock(Block* bufferBlock);
	void flush();
	void deletebuff();
	Block* getblock(std::string FileName, int offset);
	std::pair<Block*, int> getnullblock(std::string filename);
	Block* createfile(std::string filename);
	void deleteBlock(std::string fileName, int offset);
	void deletefileblock(std::string filename);
};


#endif 