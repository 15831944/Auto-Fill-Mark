#include "pch.h"
#include "LevenshteinDistance.h"
#include <regex>
#include <string>
#include <vector>



std::string ws2s(const std::wstring& ws)
{
    const std::locale locale("");
	typedef std::codecvt<wchar_t, char, std::mbstate_t> converter_type;
	const converter_type& converter = std::use_facet<converter_type>(locale);
	std::vector<char> to(ws.length() * converter.max_length());
	std::mbstate_t state;
	const wchar_t* from_next;
	char* to_next;
	const converter_type::result result = converter.out(state, ws.data(), ws.data() + ws.length(), from_next, &to[0], &to[0] + to.size(), to_next);
	std::string s(&to[0], to_next);
	return s;
}
int minDis(std::string s1, std::string s2, int n, int m, std::vector<std::vector<int>>& dp) {

	// If any string is empty,
	// return the remaining characters of other string

	if (n == 0)    return m;

	if (m == 0)    return n;


	// To check if the recursive tree
	// for given n & m has already been executed

	if (dp[n][m] != -1)    return dp[n][m];


	// If characters are equal, execute 
	// recursive function for n-1, m-1

	if (s1[n - 1] == s2[m - 1]) {
		if (dp[n - 1][m - 1] == -1) {
			return dp[n][m] = minDis(s1, s2, n - 1, m - 1, dp);
		}
		else
			return dp[n][m] = dp[n - 1][m - 1];
	}


	// If characters are nt equal, we need to

	// find the minimum cost out of all 3 operations.

	else {
		int m1, m2, m3;        // temp variables   

		if (dp[n - 1][m] != -1) {
			m1 = dp[n - 1][m];
		}
		else {
			m1 = minDis(s1, s2, n - 1, m, dp);
		}

		if (dp[n][m - 1] != -1) {
			m2 = dp[n][m - 1];
		}
		else {
			m2 = minDis(s1, s2, n, m - 1, dp);
		}

		if (dp[n - 1][m - 1] != -1) {
			m3 = dp[n - 1][m - 1];
		}
		else {
			m3 = minDis(s1, s2, n - 1, m - 1, dp);
		}
		return dp[n][m] = 1 + min(m1, min(m2, m3));
	}

}

std::wstring RemoveVietnameseTone(const std::wstring& text) {
	std::wstring result(text);
	result = std::regex_replace(result, std::wregex(L"à|á|ạ|ả|ã|â|ầ|ấ|ậ|ẩ|ẫ|ă|ằ|ắ|ặ|ẳ|ẵ|/g"), L"a");
	result = std::regex_replace(result, std::wregex(L"À|Á|Ạ|Ả|Ã|Â|Ầ|Ấ|Ậ|Ẩ|Ẫ|Ă|Ằ|Ắ|Ặ|Ẳ|Ẵ|/g"), L"A");
	result = std::regex_replace(result, std::wregex(L"è|é|ẹ|ẻ|ẽ|ê|ề|ế|ệ|ể|ễ|/g"), L"e");
	result = std::regex_replace(result, std::wregex(L"È|É|Ẹ|Ẻ|Ẽ|Ê|Ề|Ế|Ệ|Ể|Ễ|/g"), L"E");
	result = std::regex_replace(result, std::wregex(L"ì|í|ị|ỉ|ĩ|/g"), L"i");
	result = std::regex_replace(result, std::wregex(L"Ì|Í|Ị|Ỉ|Ĩ|/g"), L"I");
	result = std::regex_replace(result, std::wregex(L"ò|ó|ọ|ỏ|õ|ô|ồ|ố|ộ|ổ|ỗ|ơ|ờ|ớ|ợ|ở|ỡ|/g"), L"o");
	result = std::regex_replace(result, std::wregex(L"Ò|Ó|Ọ|Ỏ|Õ|Ô|Ồ|Ố|Ộ|Ổ|Ỗ|Ơ|Ờ|Ớ|Ợ|Ở|Ỡ|/g"), L"O");
	result = std::regex_replace(result, std::wregex(L"ù|ú|ụ|ủ|ũ|ư|ừ|ứ|ự|ử|ữ|/g"), L"u");
	result = std::regex_replace(result, std::wregex(L"Ù|Ú|Ụ|Ủ|Ũ|Ư|Ừ|Ứ|Ự|Ử|Ữ|/g"), L"U");
	result = std::regex_replace(result, std::wregex(L"ỳ|ý|ỵ|ỷ|ỹ|/g"), L"y");
	result = std::regex_replace(result, std::wregex(L"Ỳ|Ý|Ỵ|Ỷ|Ỹ|/g"), L"y");
	result = std::regex_replace(result, std::wregex(L"đ"), L"d");
	result = std::regex_replace(result, std::wregex(L"Đ"), L"D");
	//Remove space
	result = std::regex_replace(result, std::wregex(L" "), L"");
	return result;
}

void eraseAllSubStr(std::string & mainStr, const std::string & toErase)
{
    size_t pos = std::string::npos;
    // Search for the substring in string in a loop untill nothing is found
    while ((pos  = mainStr.find(toErase) )!= std::string::npos)
    {
        // If found then erase it from string
        mainStr.erase(pos, toErase.length());
    }
}


double levenshteinRatio(std::wstring s1, std::wstring s2)
{

	std::wstring s1Temp, s2Temp;
	s1Temp = RemoveVietnameseTone(s1);
	s2Temp = RemoveVietnameseTone(s2);
	// To lower
	std::transform(s1Temp.begin(), s1Temp.end(), s1Temp.begin(), ::tolower);
	std::transform(s2Temp.begin(), s2Temp.end(), s2Temp.begin(), ::tolower);
	
	std::string s11 = ws2s(s1Temp);
	std::string s21 = ws2s(s2Temp);
	s11.erase(remove_if(s11.begin(), s11.end(), [](char c) { return !isalpha(c); } ), s11.end());
	s21.erase(remove_if(s21.begin(), s21.end(), [](char c) { return !isalpha(c); } ), s21.end());

	eraseAllSubStr(s21, "lop");
	
	//std::cout << s11 << std::endl;
	//std::cout << s21 << std::endl;

	int n = s11.length(), m = s21.length();

	std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, -1));
	size_t lsum = n + m;
	if (lsum == 0) {
		return 1;
	}
	
	
	int distance = minDis(s11, s21, n, m, dp);
	return ((double)lsum - distance) / (lsum);
}


double levenshteinRatio(CString cs1, CString cs2)
{
	std::wstring s1(cs1);
	std::wstring s2(cs2);
	return levenshteinRatio(s1, s2);
}