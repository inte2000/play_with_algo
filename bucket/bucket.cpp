// bucket.cpp 
//

#include "stdafx.h"
#include <vector>
#include <list>
#include <string>
#include <map>
#include <set>
#include <unordered_set>
#include <utility>
#include "bucket_state.h"
#include <functional>
#include <algorithm>

int b_capicity[BUCKETS_COUNT] = { 8, 5, 3 };
int b_init[BUCKETS_COUNT] = { 8, 0, 0 };
int b_final[BUCKETS_COUNT] = { 4, 4, 0 };

double sd = 200.9;



bool IsProcessedState(const std::deque<BucketsState>& states, const BucketsState& newState)
{
    auto it = find_if(states.begin(), states.end(), 
        [&newState](const BucketsState& item) {return (item.operator==(newState)); });

    return (it != states.end());
}

void PrintResult(const std::deque<BucketsState>& states)
{
    std::cout << "Find Result : " << std::endl;
    for (auto& x : states)
    {
        x.PrintStates();
    }
    std::cout << std::endl << std::endl;
}


bool IsFinalState(const BucketsState& state)
{
    for (int i = 0; i < BUCKETS_COUNT; ++i)
    {
        if (state.GetBucket(i).GetWater() != b_final[i])
            return false;
    }

    return true;
}

std::vector<std::pair<int, int>> action_table = { {0, 1}, {0, 2}, {1, 0}, {1, 2}, {2, 0}, {2, 1} };

void SearchState(std::deque<BucketsState>& states)
{
    BucketsState current = states.back(); /*每次都从当前状态开始*/
    if(IsFinalState(current)) //判断是否到达4,4,0状态
    {
        PrintResult(states); //输出一组结果
        return;
    }

    for (const auto& act : action_table)
    {
        BucketsState next;
        /*从from到to倒水，如果成功，next返回倒水后的状态*/
        if (current.TakeAction(act.first, act.second, next))
        {
            if (!IsProcessedState(states, next))
            {
                states.push_back(next);
                SearchState(states); //从新的位置继续搜索
                states.pop_back();
            }
        }
    }
}

class FindName
{
public:
    FindName(const std::string& match) { m_match = match; }
    bool operator() (const std::string& item)
    {
        return (m_match == item);
    }
private:
    std::string m_match;
};


bool IsSameString(const std::string& str1, std::string str2)
{
    return (str1 == str2);
}


int main(int argc, char* argv[])
{
    int (*arr)[5] = new int[4][5];
    arr[2][3] = 56;

    std::list<std::string> strList = { "Tom", "Jim", "Jack", "Miss Fang" };
    std::list<std::string>::iterator it = std::find(strList.begin(), strList.end(), std::string("Jack"));

    FindName findJack("Jack");
    auto it2 = std::find_if(strList.begin(), strList.end(), findJack);
    auto it3 = std::find_if(strList.begin(), strList.end(), FindName("Jack"));

    std::string match = "Jack";
    auto it4 = std::find_if(strList.begin(), strList.end(),
        [&match](const std::string& item) {return (item == match); });

    auto it5 = std::find_if(strList.begin(), strList.end(),
        [](const std::string& item) {return (item == std::string("Jack")); });

    auto it6 = std::find_if(strList.begin(), strList.end(), std::bind1st(std::ptr_fun(IsSameString), "Jack"));

    std::vector<int> intArray = { 10, 20, 30, 40, 50 };

    //可以这样遍历
    for (int x : intArray)
    {
        std::cout << x << std::endl;
    }

    int value = intArray.at(2); //value = 30
    intArray.at(2) = 31; //第三个元素从30变成31

    //也可以这样遍历
    for (std::size_t i = 0; i < intArray.size(); i++)
    {
        std::cout << intArray[i] << std::endl;
    }

    value = intArray[3]; //value = 40
    intArray[3] = 41; //第四个元素从40变成41
    intArray.insert(intArray.begin() + 3, 31);

    std::unordered_set<int> intSet = { 2, 3, 5, 6, 7, 9, 11 };
    intSet.insert(12); //添加元素12
    intSet.erase(6); //删除元素6
    int count = intSet.size(); //获取集合元素的个数
    intSet.clear();  //请空集合元素
    if (!intSet.empty())  //判断集合元素是否为空
    {
        //...
    }

    std::unordered_set<int>::iterator it7 = intSet.find(9);
    if (it7 != intSet.end())
    {
        //...
    }

    std::map<std::string, int> siMap;

    siMap["Tom"] = 32;  //如果key为Tom的entry存在，则将其value设置为32，如果不存在，则添加一个entry("Tom", 32)
    siMap.insert({"Jack", 56}); //添加一个entry
    siMap.insert(std::make_pair("Mark", 43));  //又一种添加entry的方法
    int value2 = siMap.at("Tom");  //value = 32
    siMap.at("Jack") = 51; //entry{"Jack", 56}修改成entry{"Jack", 51}
    int count2 = siMap.size(); //获取entry的条目个数
    if (!siMap.empty())
    {
        //map不为空
    }
    siMap.erase("Mark");  //删除entry{"Mark", 43}
    std::map<std::string, int>::iterator it8 = siMap.find("Jack");
    if (it8 != siMap.end())
    {
        //找到entry{“Jack”， 51}
    }
    siMap.clear();  //删除全部entry

    /*
    std::list<std::string>::iterator it;
    for (it = strList.begin(); it != strList.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    */
    for (auto x : strList)
    {
        std::cout << x << std::endl;
    }
    [](int x, int y) -> int { return x + y; };
    std::string title = "This is ";
    [&title](const std::string& x) {std::cout << title << x << std::endl; };
    std::map<int, double> mid;

    std::deque<BucketsState> states;
    BucketsState init = { { b_capicity[0], b_init[0] },
                         { b_capicity[1], b_init[1] },
                         { b_capicity[2], b_init[2] } };

    states.push_back(init); //插入初始状态
    SearchState(states);  //从初始状态开始搜索

    assert(states.size() == 1); /*穷举结束后states应该还是只有一个初始状态*/

    return 0;
}
