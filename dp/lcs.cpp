// lcs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cassert>
#include <string>
#include <iostream>

const int MAX_STRING_LEN = 32;

typedef struct
{
    int d;
    int r;
}DPLCS;

int InitializeDpLcs(const std::string& str1, const std::string& str2, DPLCS dp[MAX_STRING_LEN][MAX_STRING_LEN])
{
    std::string::size_type i,j;
    
    for(i = 1; i <= str1.length(); i++)
        dp[i][0].d = 0;
    for(j = 1; j <= str2.length(); j++)
        dp[0][j].d = 0;

    for(i = 1; i <= str1.length(); i++)
    {
        for(j = 1; j <= str2.length(); j++)
        {
            if((str1[i - 1] == str2[j - 1]))
            {
                dp[i][j].d = dp[i - 1][j - 1].d + 1; 
                dp[i][j].r = 1;
            }
            else
            {
                if( dp[i - 1][j].d >= dp[i][j - 1].d )
                {
                    dp[i][j].d = dp[i - 1][j].d;
                    dp[i][j].r = 2;
                }
                else
                {
                    dp[i][j].d = dp[i][j - 1].d;
                    dp[i][j].r = 3;
                }            
            }
        }
    }

    return dp[str1.length()][str2.length()].d;
}

void GetLcs(DPLCS dp[MAX_STRING_LEN][MAX_STRING_LEN], int i, int j, const std::string& str1, std::string& lcs)
{
    if((i == 0) || (j == 0)) 
        return;

    if(dp[i][j].r == 1)
    {
        GetLcs(dp, i - 1, j - 1, str1, lcs);
        lcs += str1[i - 1];
    }
    else
    {
        if(dp[i][j].r == 2)
            GetLcs(dp, i - 1, j, str1, lcs);
        else
            GetLcs(dp, i, j - 1, str1, lcs);
    }
}

void PrintDpResult(int m, int n, DPLCS dp[MAX_STRING_LEN][MAX_STRING_LEN])
{
    for(int i = 0; i <= m; i++)
    {
        for(int j = 0; j <= n; j++)
        {
            std::cout << "d=" << dp[i][j].d << " r=" << dp[i][j].r << "   ";
        }
        std::cout << std::endl << std::endl;
    }
}


/*注意：source和target字符串的长度不能超过d矩阵的限制*/
void DpLCS(const std::string& str1, const std::string& str2, std::string& lcs)
{
    DPLCS dplcs[MAX_STRING_LEN][MAX_STRING_LEN] = { 0 };

    int lcsLen = InitializeDpLcs(str1, str2, dplcs);
    PrintDpResult(str1.length(), str2.length(), dplcs);
    GetLcs(dplcs, str1.length(), str2.length(), str1, lcs);
}

std::string GetLongestString(const std::string& str1, const std::string& str2, const std::string& str3)
{
    if(str1.length() > str2.length())
    {
        return (str1.length() > str3.length()) ? str1 : str3;
    }
    else
    {
        return (str2.length() > str3.length()) ? str2 : str3;
    }
}

void RecursionLCS(const std::string& str1, const std::string& str2, std::string& lcs)
{
    if(str1.length() == 0 || str2.length() == 0)
        return;

    if(str1[0] == str2[0])
    {
        lcs += str1[0];
        RecursionLCS(str1.substr(1), str2.substr(1), lcs);
    }
    else
    {
        std::string strTmp1,strTmp2,strTmp3;

        RecursionLCS(str1.substr(1), str2, strTmp1);  //尝试删除str1
        RecursionLCS(str1, str2.substr(1), strTmp2);  //尝试删除str2
        RecursionLCS(str1.substr(1), str2.substr(1), strTmp3); //尝试同时删除str1和str2
        lcs += GetLongestString(strTmp1, strTmp2, strTmp3); 
    }
}

void testRecursionLCS()
{
    std::string str1 = "abcdea";
    std::string str2 = "aebcda";
    std::string lcs;

    RecursionLCS(str1, str2, lcs);
    assert(lcs.compare("abcda") == 0);

    str1 = "abcdeaasdfgk";
    str2 = "aebcdasdfgj";
    lcs.clear();
    RecursionLCS(str1, str2, lcs);
    assert(lcs.compare("abcdasdfg") == 0);
}

void testDpLCS()
{
    std::string str1 = "abcdea";
    std::string str2 = "aebcda";
    std::string lcs;

    DpLCS(str1, str2, lcs);
    assert(lcs.compare("abcda") == 0);

    str1 = "abcdeaasdfgk";
    str2 = "aebcdasdfgj";
    lcs.clear();
    DpLCS(str1, str2, lcs);
    assert(lcs.compare("abcdasdfg") == 0);
}

int main(int argc, char* argv[])
{
    testRecursionLCS();
    testDpLCS();
	return 0;
}

