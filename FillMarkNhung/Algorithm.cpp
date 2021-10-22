#include "pch.h"
#include "Algorithm.h"
#include <regex>


#define libxl_sample
#ifdef libxl_sample

#include <iostream>
#include "libxl.h"
#include <string>
#include "LevenshteinDistance.h"

using namespace libxl;

int main1()
{
	libxl::Book* pbook = xlCreateBook();
	pbook->setKey(L"Halil Kural", L"windows-2723210a07c4e90162b26966a8jcdboe");//set cdkey	

	/*if (pbook->load(L"excel_file_name.xls")){*/

	libxl::Sheet * sheetread = pbook->addSheet(L"Nhung Nhung");
	sheetread->writeStr(3, 3, L"Yêu Nhung Nhung");
	sheetread->writeNum(4, 3, 3000);
	sheetread->writeNum(5, 3, 2000);

	//save excel
	if (pbook->save(L"yeu_nhung_nhung.xls")){
		::ShellExecute(NULL, L"open", L"yeu_nhung_nhung.xls", NULL, NULL, SW_SHOW);
	}
	else{
		std::cout << pbook->errorMessage() << std::endl;
	}
	pbook->release();
	/*}*/

	return 0;
}

int createStudentListSample(const TCHAR* filepath, int numScore)
{
	libxl::Book* pbook = xlCreateXMLBook();
	pbook->setKey(L"Halil Kural", L"windows-2723210a07c4e90162b26966a8jcdboe");//set cdkey

	libxl::Font* textFont = pbook->addFont();
	textFont->setSize(13);
	textFont->setName(L"Times New Roman");
	textFont->setBold(true);

	libxl::Format* textFormat = pbook->addFormat();
	textFormat->setFont(textFont);
	textFormat->setAlignH(libxl::ALIGNH_CENTER);

	libxl::Sheet * sheetread = pbook->addSheet(L"DS_HOCSINH");
	sheetread->writeStr(0, 0, L"STT", textFormat);
	sheetread->writeStr(0, 1, L"Họ", textFormat);
	sheetread->writeStr(0, 2, L"Tên", textFormat);

	for (int i = 0; i < numScore; i++)
	{
		std::wstring temp(L"DIEM_");
		temp += std::to_wstring(i + 1);
		const TCHAR* sheetName = temp.c_str();
		libxl::Sheet* sheet1 = pbook->addSheet(sheetName);
		//sheet1->writeStr(0, 0, L"STT", textFormat);
		sheet1->writeStr(0, 0, L"Họ và tên", textFormat);
		sheet1->writeStr(0, 1, L"Điểm", textFormat);
		sheetread->writeStr(0, i+3, sheetName, textFormat);
	}
	//sheetread->writeStr(1, 3, L"Họ và tên", textFormat);

	std::wstring temp(filepath);
	if (pbook->save(temp.c_str())) {
		::ShellExecute(NULL, L"open", temp.c_str(), NULL, NULL, SW_SHOW);
	}
	else {
		std::cout << pbook->errorMessage() << std::endl;
	}

	pbook->release();

	return 0;
}

int matchScore(std::vector<Student>& studentList, std::vector<std::vector<Score>>& scoreList, Book* book)
{
	double threshold = 0.85;

	libxl::Font* textFont = book->addFont();
	textFont->setSize(11);
	textFont->setName(L"Calibri");
	textFont->setBold(true);

	libxl::Format* textFormat = book->addFormat();
	textFormat->setFont(textFont);

	Format* formatError1 = book->addFormat();
	formatError1->setFillPattern(FILLPATTERN_SOLID);
	formatError1->setPatternForegroundColor(COLOR_RED);
	formatError1->setFont(textFont);

	Format* formatError2 = book->addFormat();
	formatError2->setFillPattern(FILLPATTERN_SOLID);
	formatError2->setPatternForegroundColor(COLOR_BLUE);
	formatError2->setFont(textFont);


	for (int i = 0; i < scoreList.size(); i++)
	{
		std::vector<Score> scoreListTmp = scoreList[i];
		std::vector<int> scoreListErrorTmp;
		Sheet* sheet = book->getSheet(i+1);

		for (int j = 0; j < scoreListTmp.size(); j++)
		{
			std::wstring nickname = scoreListTmp[j].nickname;
			float scoreTemporary = scoreListTmp[j].scoreTemporary;
			double maxRatio = 0;
			int maxK = -1;
			for (int k = 0; k < studentList.size(); k++)
			{
				double ratio = levenshteinRatio(nickname, studentList[k].name);
				if (ratio > maxRatio)
				{
					maxRatio = ratio;
					maxK = k;
					scoreListTmp[j].matchID = studentList[k].id;
				}
			}
			if (maxRatio > threshold)
			{
				if (studentList[maxK].scoreList[i] == -1)
				{
					studentList[maxK].scoreList[i] = scoreTemporary;
				}
				else if (studentList[maxK].scoreList[i] == -2)
				{

				}
				else
				{
					studentList[maxK].scoreList[i] = -2;
					scoreListErrorTmp.push_back(scoreListTmp[j].id);
					sheet->writeStr(scoreListTmp[j].id, 2, L"DUPLICATE", formatError1);
				}
			}
			else
			{
				scoreListErrorTmp.push_back(scoreListTmp[j].id);
				sheet->writeStr(scoreListTmp[j].id, 2, L"NOT FOUND", formatError2);
			}
#ifdef _DEBUG
			sheet->writeStr(scoreListTmp[j].id, 4, studentList[maxK].name.c_str(), textFormat);
			sheet->writeNum(scoreListTmp[j].id, 5, maxRatio, textFormat);
#endif
		}
		//scoreListError.push_back(scoreListErrorTmp);
	}
	return 0;
}

int exportScore(std::vector<Student>& studentList, std::vector<std::vector<int>>& scoreListError, Sheet* sheet, int numScore, libxl::Format* textFormat, libxl::Format* formatError)
{
	if (sheet)
	{
		for (int i = 0; i < studentList.size(); i++)
		{
			for (int j = 0; j < numScore; j++)
			{
				float val = studentList[i].scoreList[j];
				if (val >=0)
				{
					sheet->writeNum(i+1, j+3, val, textFormat);
				}
				else if (val == -2)
				{
					sheet->writeBlank(i + 1, j + 3, formatError);
				}
			}
		}
	}
	return 0;
}

int importScore(const TCHAR* filepath, const TCHAR* fileOutPut, int numScore)
{
	std::vector<Student> studentList;
	std::vector<std::vector<Score>> scoreList;
	std::vector<int> studentListError;
	std::vector<std::vector<int>> scoreListError;
	libxl::Book* book = xlCreateXMLBook();
	book->setKey(L"Halil Kural", L"windows-2723210a07c4e90162b26966a8jcdboe");//set cdkey
	if (book->load(filepath))
	{
		//Sheet DS_HOCSINH
		Sheet* sheet = book->getSheet(0);
		if (sheet)
		{
			for (int row = 1; row < sheet->lastRow(); ++row)
			{
				if (sheet->cellType(row, 1) == CELLTYPE_STRING && sheet->cellType(row, 2) == CELLTYPE_STRING && sheet->cellType(row, 0) == CELLTYPE_NUMBER)
				{
					const wchar_t* s1 = sheet->readStr(row, 1);
					std::wstring ws1(s1);
					const wchar_t* s2 = sheet->readStr(row, 2);
					std::wstring ws2(s2);
					int id = sheet->readNum(row, 0);
					ws1 = ws1 + L" " + ws2;
					Student student;
					student.id = row;
					student.name = ws1;
					for (int i = 1; i < book->sheetCount(); ++i)
					{
						student.scoreList.push_back(-1);
					}
					studentList.push_back(student);
				}
			}
		}
		else
		{
			book->release();
			return 1;
		}

		//Import score tabs
		for (int i = 1; i < book->sheetCount(); ++i)
		{
			std::vector<Score> scoreListTmp;
			Sheet* sheet = book->getSheet(i);
			if (sheet)
			{
				for (int row = 1; row < sheet->lastRow(); ++row)
				{
					if (sheet->cellType(row, 1) == CELLTYPE_NUMBER && sheet->cellType(row, 0) == CELLTYPE_STRING)
					{
						//int id = sheet->readNum(row, 0);
						const wchar_t* s1 = sheet->readStr(row, 0);
						std::wstring nickname(s1);
						float scoreTemp = sheet->readNum(row, 1);
						Score score = {row, nickname, scoreTemp};
						scoreListTmp.push_back(score);
					}
				}
			}
			else
			{
				book->release();
				return 1;
			}
			scoreList.push_back(scoreListTmp);
		}

	}
	else
	{
		book->release();
		return 1;
	}

	libxl::Font* textFont = book->addFont();
	textFont->setSize(13);
	textFont->setName(L"Times New Roman");

	libxl::Format* textFormat = book->addFormat();
	textFormat->setFont(textFont);
	textFormat->setAlignH(libxl::ALIGNH_RIGHT);

	Format* formatError1 = book->addFormat();
	formatError1->setFillPattern(FILLPATTERN_SOLID);
	formatError1->setPatternForegroundColor(COLOR_RED);

	matchScore(studentList, scoreList, book);
	exportScore(studentList, scoreListError, book->getSheet(0), book->sheetCount()-1, textFormat, formatError1);

	if (book->save(fileOutPut)) {
		//::ShellExecute(NULL, L"open", fileOutPut, NULL, NULL, SW_SHOW);
	}
	else {
		book->release();
		return 1;
	}

	book->release();
	return 0;
}

#endif