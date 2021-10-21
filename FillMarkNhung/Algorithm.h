#pragma once
#include <string>
#include <vector>
struct Student
{
	int id;
	std::wstring name;
	std::vector<float> scoreList;
};

struct Score
{
	std::wstring nickname;
	float scoreTemporary;
};

int createStudentListSample(const TCHAR* filepath, int numScore);

int importScore(const TCHAR* filepath, int numScore);
