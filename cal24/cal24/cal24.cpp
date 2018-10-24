// cal24.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <utility>

typedef struct
{
    double num;
    std::string num_str;
}Number;


std::function<bool (const Number&, const Number&, Number&)> acops[] = 
{
    [](const Number& d1, const Number& d2, Number& dr) 
    { 
        dr.num = d1.num + d2.num; 
        dr.num_str = '(' + d1.num_str + '+' + d2.num_str + ')';
        return true; 
    },
    [](const Number& d1, const Number& d2, Number& dr) 
    { 
        dr.num = d1.num - d2.num;
        dr.num_str = '(' + d1.num_str + '-' + d2.num_str + ')';
        return true;
    },
    [](const Number& d1, const Number& d2, Number& dr) 
    {
        dr.num = d1.num * d2.num;
        dr.num_str = '(' + d1.num_str + '*' + d2.num_str + ')';
        return true;
    },
    [](const Number& d1, const Number& d2, Number& dr) 
    {
        if (d2.num == 0)
            return false;
        dr.num = d1.num / d2.num;
        dr.num_str = '(' + d1.num_str + '/' + d2.num_str + ')';
        return true;
    }
};

void Calc24(const std::vector<Number>& nums)
{
    std::size_t count = nums.size();
    if (count == 1) //当只有一个数时，说明计算完成，可以判断结果了
    {
        if (nums[0].num == 24)
        {
            std::cout << nums[0].num_str << " = " << nums[0].num << std::endl;
        }
        return;
    }

    //两重循环，从numbers中找两个数的组合
    for (std::size_t i = 0; i < count; i++)
    {
        for (std::size_t j = 0; j < count; j++)
        {
            if (i == j) //排除相同的情况
                continue;

            for (auto& op : acops) //对四种运算进行枚举
            {
                Number new_num;
                //运算可能失败，比如除数是0的情况，不再继续处理这个运算符，相当于剪枝效果
                if (op(nums[i], nums[j], new_num))
                {
                    std::vector<Number> sub_nums;//定义子问题
                    sub_nums.push_back(new_num);
                    //除了被选出来的两个数，将剩下的数加入子问题
                    for (std::size_t k = 0; k < count; k++) 
                    {
                        if ((k != i) && (k != j))
                        {
                            sub_nums.push_back(nums[k]);
                        }
                    }
                    Calc24(sub_nums); //解决子问题
                }
            }
        }
    }
}

int main()
{
    std::vector<Number> numbers = { { 3, "3" },{ 3, "3" },{ 7, "7" },{ 7, "7" } };
    //std::vector<Number> numbers = { { 1, "1" },{ 5, "5" },{ 5, "5" },{ 5, "5" } };
    //std::vector<Number> numbers = { { 1, "1" },{ 6, "6" },{ 8, "8" },{ 9, "9" } };
    //std::vector<Number> numbers = { { 2, "2" },{ 7, "7" },{ 6, "6" },{ 3, "3" } };

    Calc24(numbers);

    return 0;
}


std::vector<std::pair<int, int>> posArray = 
{
    { 0, 1 }, { 0, 2 }, { 0, 3 }, 
    { 1, 0 }, { 1, 2 }, { 1, 3 }, 
    { 2, 0 }, { 2, 1 }, { 2, 3 }, 
    { 3, 0 }, { 3, 1 }, { 3, 2 }
};

void sdsfdgdfh()
{
    std::vector<int> numArray = { 3, 3, 7 ,7 };
    for (auto& pos : posArray)
    {
        //第一个操作数是numArray[pos.first]
        //第二个操作数是numArray[pos.second]
        int sum = numArray[pos.first] + numArray[pos.second];
    }
}