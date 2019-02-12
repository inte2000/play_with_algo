// max_match.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>

typedef struct
{
    int max_len;
    std::map<int, std::vector<std::wstring>> words;
}WORD_DICT;

void InitDict(WORD_DICT& dict)
{
    std::vector<std::wstring> w1 = { L"我", L"是", L"有", L"市", L"江", L"大", L"桥"};
    std::vector<std::wstring> w2 = { L"南京", L"意思", L"市长", L"计算", L"编程", L"长江", L"大桥" };
    std::vector<std::wstring> w3 = { L"南京市", L"计算机", L"江大桥" };
    std::vector<std::wstring> w4 = { L"高科西路", L"喜马拉雅", L"人民广场" };
    std::vector<std::wstring> w5 = { L"人民大会堂", L"沪上新闻台" };

    dict.max_len = 5;
    dict.words[1] = w1;
    dict.words[2] = w2;
    dict.words[3] = w3;
    dict.words[4] = w4;
    dict.words[5] = w5;
}

//张三是上海市人大代表

bool LookupDict(const WORD_DICT& dict, std::wstring& word)
{
    int length = word.length(); //根据词长选择对应的词集
    for (auto& ws : dict.words.at(length))
    {
        if (ws.compare(word) == 0)
        {
            return true;
        }
    }

    return false;
}

std::pair<bool, std::wstring> MatchWord(std::wstring& s2, const WORD_DICT& dict)
{
    while (!s2.empty())
    {
        if (LookupDict(dict, s2)) //查词典
        {
            return { true, s2 };
        }
        else
        {
            s2.pop_back(); //从s2中删除最后一个字
        }
    }

    //s2都空了也没匹配到词？可能是词典有问题
    return { false, L"" };
}

bool MaxMatching(const std::wstring& sentence, const WORD_DICT& dict, std::vector<std::wstring>& words)
{
    std::wstring s1 = sentence;

    while (!s1.empty())
    {
        int s2_len = (s1.length() > dict.max_len) ? dict.max_len : s1.length();
        std::wstring s2 = s1.substr(0, s2_len);
        auto mr = MatchWord(s2, dict);
        if (!mr.first)
        {
            return false;
        }

        words.push_back(mr.second);
        s1 = s1.substr(mr.second.length());
    }

    return true;
}

std::pair<bool, std::wstring> ReverseMatchWord(std::wstring& s2, const WORD_DICT& dict)
{
    while (!s2.empty())
    {
        if (LookupDict(dict, s2)) //查词典
        {
            return{ true, s2 };
        }
        else
        {
            s2 = s2.substr(1); //从s2中删除第一个字
        }
    }

    //s2都空了也没匹配到词？可能是词典有问题
    return{ false, L"" };
}

bool ReverseMaxMatching(const std::wstring& sentence, const WORD_DICT& dict, std::vector<std::wstring>& words)
{
    std::wstring s1 = sentence;

    while (!s1.empty())
    {
        int s2_pos = (s1.length() > dict.max_len) ? s1.length() - dict.max_len : 0;
        std::wstring s2 = s1.substr(s2_pos);
        auto mr = ReverseMatchWord(s2, dict);
        if (!mr.first)
        {
            return false;
        }

        words.push_back(mr.second);
        s1 = s1.substr(0, s1.length() - mr.second.length());
    }

    return true;
}

int main()
{
    std::wcout.imbue(std::locale("chs"));

    WORD_DICT dict;

    InitDict(dict);

    std::wstring sentence = L"计算机编程有意思";
    std::vector<std::wstring> words;
    if (MaxMatching(sentence, dict, words))
    {
        for (auto& str : words)
        {
            std::wcout << str << L"/";
        }

        std::wcout << std::endl;
    }

    words.clear();
    if (ReverseMaxMatching(sentence, dict, words))
    {
        for (auto& str : words)
        {
            std::wcout << str << L"/";
        }

        std::wcout << std::endl;
    }

    std::wstring sentence2 = L"南京市长江大桥";
    words.clear();
    if (MaxMatching(sentence2, dict, words))
    {
        for (auto& str : words)
        {
            std::wcout << str << L"/";
        }

        std::wcout << std::endl;
    }

    words.clear();
    if (ReverseMaxMatching(sentence2, dict, words))
    {
        for (auto& str : words)
        {
            std::wcout << str << L"/";
        }

        std::wcout << std::endl;
    }

    return 0;
}


#if 0
void CppReverse()
{
    std::string test_string = "我是猪";

    std::cout.imbue(std::locale("chs"));
    std::reverse(test_string.begin(), test_string.end());
    std::cout << test_string << std::endl;
}

void CppReverse2()
{
    std::wstring test_string = L"我是猪";
    //std::wcout << test_string << std::endl;

    std::wcout.imbue(std::locale("chs"));
    std::reverse(test_string.begin(), test_string.end());
    std::wcout << test_string << std::endl;
}

#include <cstring>
void CReverse()
{
    char s[] = "我是猪";

    char *locName = setlocale(LC_ALL, "");

    printf("%s\n", s);
    strrev(s);
    printf("%s\n", s);
}

#endif
