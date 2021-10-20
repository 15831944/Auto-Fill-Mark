#include "Algorithm.h"
#include "pch.h"

#define libxl_sample
#ifdef libxl_sample

#include <iostream>
#include "libxl.h"

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

int createStudentListSample(const TCHAR* filepath)
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
	sheetread->writeStr(0, 1, L"Họ và tên", textFormat);
	//sheetread->writeStr(1, 3, L"Họ và tên", textFormat);

	pbook->save(L"Bang_diem_NhungNhung.xlsx");

	pbook->release();

	return 0;
}

#endif