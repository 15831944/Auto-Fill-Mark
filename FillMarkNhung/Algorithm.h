#pragma once
struct Student
{
	int id;
	std::wstring name;
	std::vector<float> scoreList;
};

int createStudentListSample(const TCHAR* filepath, int numScore);