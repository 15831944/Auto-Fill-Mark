#pragma once
#include <string>
#include <vector>
#include "libxl.h"

using namespace libxl;

#ifndef _WIN64
#define COMMERCIAL
#endif // _WIN32

#define VERSION L"v0.3.1"
struct Student
{
	int id;
	std::wstring name;
	std::vector<float> scoreList;
};

struct Score
{
	int id;
	std::wstring nickname;
	float scoreTemporary;
	int matchID = 0;
};

int createStudentListSample(const TCHAR* filepath, int numScore);


int importScore(const TCHAR* filepath, const TCHAR* fileOutPut, int threshold, int & completedPercentage);

int matchScore(std::vector<Student>& studentList, std::vector<std::vector<Score>>& scoreList, Book* book, int thresh, int & percentagePos, int totalImported);

int exportScore(std::vector<Student>& studentList, std::vector<std::vector<int>>& scoreListError, Sheet* sheet, int numScore, libxl::Format* textFormat, libxl::Format* formatError);
