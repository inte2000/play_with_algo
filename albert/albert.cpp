// albert.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cassert>

const int GROUPS_ITEMS = 5;
const int GROUPS_COUNT = 5;

const int COLOR_BLUE    = 0;
const int COLOR_RED     = 1;
const int COLOR_GREEN   = 2;
const int COLOR_YELLOW  = 3;
const int COLOR_WHITE   = 4;


const int NATION_NORWAY     = 0;
const int NATION_DANMARK    = 1;
const int NATION_SWEDEND    = 2;
const int NATION_ENGLAND    = 3;
const int NATION_GERMANY    = 4;


const int DRINK_TEA     = 0;
const int DRINK_WATER   = 1;
const int DRINK_COFFEE  = 2;
const int DRINK_BEER    = 3;
const int DRINK_MILK    = 4;

const int PET_HORSE   = 0;
const int PET_CAT     = 1;
const int PET_BIRD    = 2;
const int PET_FISH    = 3;
const int PET_DOG     = 4;

const int CIGARET_BLENDS      = 0;
const int CIGARET_DUNHILL     = 1;
const int CIGARET_PRINCE      = 2;
const int CIGARET_PALLMALL    = 3;
const int CIGARET_BLUEMASTER  = 4;

typedef enum 
{
    type_house = 0,
    type_nation = 1,
    type_drink = 2,
    type_pet = 3,
    type_cigaret = 4
}ITEM_TYPE;

const char *itemName[GROUPS_ITEMS] = { "房子", "国家", "饮料", "宠物", "烟"};
const char *valueName[GROUPS_ITEMS][GROUPS_COUNT] = 
{ 
    { "蓝色", "红色", "绿色", "黄色", "白色" },
    { "挪威", "丹麦", "瑞典", "英国", "德国" },
    { "茶", "水", "咖啡", "啤酒", "牛奶" },
    { "马", "猫", "鸟", "鱼", "狗" },
    { "Blends", "Dunhill", "Prince", "PallMall", "BlueMaster" }
};

typedef struct 
{
    ITEM_TYPE type;
    int value;
}ITEM;

typedef struct 
{
    ITEM_TYPE first_type;
    int first_val;
    ITEM_TYPE second_type;
    int second_val;
}BIND;

const BIND binds[] = 
{
    { type_house, COLOR_RED, type_nation, NATION_ENGLAND },
    { type_nation, NATION_SWEDEND, type_pet, PET_DOG },
    { type_nation, NATION_DANMARK, type_drink, DRINK_TEA },
    { type_house, COLOR_GREEN, type_drink, DRINK_COFFEE },
    { type_cigaret, CIGARET_PALLMALL, type_pet, PET_BIRD },
    { type_house, COLOR_YELLOW, type_cigaret, CIGARET_DUNHILL },
    { type_cigaret, CIGARET_BLUEMASTER, type_drink, DRINK_BEER },
    { type_nation, NATION_GERMANY, type_cigaret, CIGARET_PRINCE }
};

const int BINDS_COUNT = sizeof(binds) / sizeof(binds[0]);

typedef struct tagRelation
{
    ITEM_TYPE type;
    int val;
    ITEM_TYPE relation_type;
    int relation_val;
}RELATION;

const RELATION relations[] = 
{
    { type_cigaret, CIGARET_BLENDS, type_pet, PET_CAT },
    { type_pet, PET_HORSE, type_cigaret, CIGARET_DUNHILL },
    { type_nation, NATION_NORWAY, type_house, COLOR_BLUE },
    { type_cigaret, CIGARET_BLENDS, type_drink, DRINK_WATER }
};

const int RELATIONS_COUNT = sizeof(relations) / sizeof(relations[0]);
/*
typedef struct tagGroup
{
    ITEM items[GROUPS_ITEMS];
}GROUP;
*/
typedef struct 
{
    int itemValue[GROUPS_ITEMS];
}GROUP;


int GetGroupItemValue(GROUP *group, ITEM_TYPE type)
{
    return group->itemValue[type];
}

int FindGroupIdxByItem(GROUP *groups, ITEM_TYPE type, int value)
{
    for(int i = 0; i < GROUPS_COUNT; i++)
    {
        if(GetGroupItemValue(&groups[i], type) == value)
        {
            return i;
        }
    }

    return -1;
}

bool CheckGroupBind(GROUP *groups, int groupIdx, ITEM_TYPE type, int value)
{
    if(GetGroupItemValue(&groups[groupIdx], type) != value)
    {
        return false;
    }

    return true;
}

bool CheckAllGroupsBind(GROUP *groups, const BIND *binds)
{
    for(int i = 0; i < BINDS_COUNT; i++)
    {
        int grpIdx = FindGroupIdxByItem(groups, binds[i].first_type, binds[i].first_val);
        if(grpIdx != -1)
        {
            if(!CheckGroupBind(groups, grpIdx, binds[i].second_type, binds[i].second_val))
            {
                return false;
            }
        }
    }

    return true;
}

bool CheckGroupRelation(GROUP *groups, int groupIdx, ITEM_TYPE type, int value)
{
    if(groupIdx == 0)
    {
        if(GetGroupItemValue(&groups[groupIdx + 1], type) != value)
        {
            return false;
        }
    }
    else if(groupIdx == (GROUPS_COUNT - 1))
    {
        if(GetGroupItemValue(&groups[groupIdx - 1], type) != value)
        {
            return false;
        }
    }
    else
    {
        if( (GetGroupItemValue(&groups[groupIdx - 1], type) != value)
            && (GetGroupItemValue(&groups[groupIdx + 1], type) != value) )
        {
            return false;
        }
    }

    return true;
}

bool CheckAllGroupsRelation(GROUP *groups, const RELATION *relations)
{
    for(int i = 0; i < RELATIONS_COUNT; i++)
    {
        int grpIdx = FindGroupIdxByItem(groups, relations[i].type, relations[i].val);
        if(grpIdx != -1)
        {
            if(!CheckGroupRelation(groups, grpIdx, relations[i].relation_type, relations[i].relation_val))
            {
                return false;
            }
        }
    }

    return true;
}


void PrintGroupsNameTitle()
{
    for(int i = type_house; i <= type_cigaret; i++)
    {
        printf("%-15s", itemName[i]);
    }
    printf("\n");
}

void PrintSingleLineGroup(GROUP *group)
{
    for(int i = type_house; i <= type_cigaret; i++)
    {
        printf("%-15s", valueName[i][group->itemValue[i]]);
    }
    printf("\n");
}

void PrintAllGroupsResult(GROUP *groups, int groupCount)
{
    PrintGroupsNameTitle();
    for(int i = 0; i < groupCount; i++)
    {
        PrintSingleLineGroup(&groups[i]);
    }
    printf("\n");
}

static int cnt = 0;
void DoGroupsfinalCheck(GROUP *groups)
{
    cnt++;
    if((cnt % 1000000) == 0)
        printf("%d\n", cnt);

    if(CheckAllGroupsBind(groups, binds) && CheckAllGroupsRelation(groups, relations))
    {
        PrintAllGroupsResult(groups, GROUPS_COUNT);
    }
}

void ArrangePeopleCigert(GROUP *groups)
{
    /*这里没有可用规则*/
    for (int i = CIGARET_BLENDS; i <= CIGARET_BLUEMASTER; i++)
    {
        for (int j = CIGARET_BLENDS; j <= CIGARET_BLUEMASTER; j++)
        {
            if (j == i)
                continue;
            for (int k = CIGARET_BLENDS; k <= CIGARET_BLUEMASTER; k++)
            {
                if ((k == i) || (k == j))
                    continue;
                for (int p = CIGARET_BLENDS; p <= CIGARET_BLUEMASTER; p++)
                {
                    if ((p == i) || (p == j) || (p == k))
                        continue;

                    for (int q = CIGARET_BLENDS; q <= CIGARET_BLUEMASTER; q++)
                    {
                        if ((q == i) || (q == j) || (q == k) || (q == p))
                            continue;

                        groups[0].itemValue[type_cigaret] = i;
                        groups[1].itemValue[type_cigaret] = j;
                        groups[2].itemValue[type_cigaret] = k;
                        groups[3].itemValue[type_cigaret] = p;
                        groups[4].itemValue[type_cigaret] = q;

                        DoGroupsfinalCheck(groups);
                    }
                }
            }
        }
    }
}

void ArrangePeoplePet(GROUP *groups)
{
    /*这里没有可用规则*/
    for (int i = PET_HORSE; i <= PET_DOG; i++)
    {
        for (int j = PET_HORSE; j <= PET_DOG; j++)
        {
            if (j == i)
                continue;
            for (int k = PET_HORSE; k <= PET_DOG; k++)
            {
                if ((k == i) || (k == j))
                    continue;
                for (int p = PET_HORSE; p <= PET_DOG; p++)
                {
                    if ((p == i) || (p == j) || (p == k))
                        continue;

                    for (int q = PET_HORSE; q <= PET_DOG; q++)
                    {
                        if ((q == i) || (q == j) || (q == k) || (q == p))
                            continue;

                        groups[0].itemValue[type_pet] = i;
                        groups[1].itemValue[type_pet] = j;
                        groups[2].itemValue[type_pet] = k;
                        groups[3].itemValue[type_pet] = p;
                        groups[4].itemValue[type_pet] = q;

                        ArrangePeopleCigert(groups);
                    }
                }
            }
        }
    }
}

void ArrangePeopleDrinks(GROUP *groups)
{
    /*应用规则(8)：住在中间那个房子里的人喝牛奶；*/
    groups[2].itemValue[type_drink] = DRINK_MILK;

    for (int i = DRINK_TEA; i <= DRINK_BEER; i++)
    {
        for (int j = DRINK_TEA; j <= DRINK_BEER; j++)
        {
            if (j == i)
                continue;
            for (int k = DRINK_TEA; k <= DRINK_BEER; k++)
            {
                if ((k == i) || (k == j))
                    continue;
                for (int p = DRINK_TEA; p <= DRINK_BEER; p++)
                {
                    if ((p == i) || (p == j) || (p == k))
                        continue;

                    groups[0].itemValue[type_drink] = i;
                    groups[1].itemValue[type_drink] = j;
                    groups[3].itemValue[type_drink] = k;
                    groups[4].itemValue[type_drink] = p;

                    ArrangePeoplePet(groups);
                }
            }
        }
    }
}

void ArrangeHouseNations(GROUP *groups)
{
    /*应用规则(9)：挪威人住在第一个房子里面；*/
    groups[0].itemValue[type_nation] = NATION_NORWAY;

    for (int i = NATION_DANMARK; i <= NATION_GERMANY; i++)
    {
        for (int j = NATION_DANMARK; j <= NATION_GERMANY; j++)
        {
            if (j == i)
                continue;
            for (int k = NATION_DANMARK; k <= NATION_GERMANY; k++)
            {
                if ((k == i) || (k == j))
                    continue;
                for (int p = NATION_DANMARK; p <= NATION_GERMANY; p++)
                {
                    if ((p == i) || (p == j) || (p == k))
                        continue;

                    groups[1].itemValue[type_nation] = i;
                    groups[2].itemValue[type_nation] = j;
                    groups[3].itemValue[type_nation] = k;
                    groups[4].itemValue[type_nation] = p;

                    ArrangePeopleDrinks(groups);
                }
            }
        }
    }
}


/* 遍历房子颜色*/
void ArrangeHouseColors(GROUP *groups)
{
    for (int i = COLOR_BLUE; i <= COLOR_WHITE; i++)
    {
        for (int j = COLOR_BLUE; j <= COLOR_WHITE; j++)
        {
            if (j == i)
                continue;
            for (int k = COLOR_BLUE; k <= COLOR_WHITE; k++)
            {
                if ((k == i) || (k == j))
                    continue;
                for (int p = COLOR_BLUE; p <= COLOR_WHITE; p++)
                {
                    if ((p == i) || (p == j) || (p == k))
                        continue;

                    for (int q = COLOR_BLUE; q <= COLOR_WHITE; q++)
                    {
                        if ((q == i) || (q == j) || (q == k) || (q == p))
                            continue;

                        groups[0].itemValue[type_house] = i;
                        groups[1].itemValue[type_house] = j;
                        groups[2].itemValue[type_house] = k;
                        groups[3].itemValue[type_house] = p;
                        groups[4].itemValue[type_house] = q;
                        
                        for (int groupIdx = 0; groupIdx < (GROUPS_COUNT - 1); groupIdx++)
                        {
                            if ((groups[groupIdx].itemValue[type_house] == COLOR_GREEN)
                                && (groups[groupIdx + 1].itemValue[type_house] == COLOR_WHITE))
                            {
                                ArrangeHouseNations(groups);
                            }
                        }
                    }
                }
            }
        }
    }
}


int main(int argc, char* argv[])
{
    GROUP groups[GROUPS_COUNT] = { { 0 } };

    ArrangeHouseColors(groups);

	return 0;
}

void test_Checkfunctions()
{
    GROUP groups[GROUPS_COUNT] = 
    {
        {COLOR_YELLOW, NATION_NORWAY, DRINK_WATER, PET_CAT, CIGARET_DUNHILL},
        {COLOR_BLUE, NATION_DANMARK, DRINK_TEA, PET_HORSE, CIGARET_BLENDS},
        {COLOR_RED, NATION_ENGLAND, DRINK_MILK, PET_BIRD, CIGARET_PALLMALL},
        {COLOR_GREEN, NATION_GERMANY, DRINK_COFFEE, PET_FISH, CIGARET_PRINCE},
        {COLOR_WHITE, NATION_SWEDEND, DRINK_BEER, PET_DOG, CIGARET_BLUEMASTER}
    };
    assert(CheckAllGroupsBind(groups, binds));
    assert(CheckAllGroupsRelation(groups, relations));

    GROUP groups2[GROUPS_COUNT] = 
    {
        {COLOR_YELLOW, NATION_DANMARK, DRINK_WATER, PET_CAT, CIGARET_DUNHILL},
        {COLOR_BLUE, NATION_NORWAY, DRINK_TEA, PET_HORSE, CIGARET_BLENDS},
        {COLOR_RED, NATION_ENGLAND, DRINK_MILK, PET_BIRD, CIGARET_PALLMALL},
        {COLOR_GREEN, NATION_GERMANY, DRINK_COFFEE, PET_FISH, CIGARET_PRINCE},
        {COLOR_WHITE, NATION_SWEDEND, DRINK_BEER, PET_DOG, CIGARET_BLUEMASTER}
    };

    assert(!CheckAllGroupsBind(groups2, binds));
    assert(!CheckAllGroupsRelation(groups2, relations));

    GROUP groups3[GROUPS_COUNT] = 
    {
        {COLOR_YELLOW, NATION_NORWAY, DRINK_WATER, PET_CAT, CIGARET_DUNHILL},
        {COLOR_BLUE, NATION_DANMARK, DRINK_TEA, PET_BIRD, CIGARET_BLENDS},
        {COLOR_RED, NATION_ENGLAND, DRINK_MILK, PET_HORSE, CIGARET_PALLMALL},
        {COLOR_GREEN, NATION_GERMANY, DRINK_COFFEE, PET_FISH, CIGARET_PRINCE},
        {COLOR_WHITE, NATION_SWEDEND, DRINK_BEER, PET_DOG, CIGARET_BLUEMASTER}
    };

    assert(!CheckAllGroupsBind(groups3, binds));
    assert(!CheckAllGroupsRelation(groups3, relations));
}



/*

绿房子紧挨着白房子，在白房子的左边；

住在中间那个房子里的人喝牛奶；

挪威人住在第一个房子里面；

           国家           房子           宠物           饮料           香烟
           挪威           黄色             猫         矿泉水        Dunhill
           丹麦           蓝色             马             茶         Blends
           英国           红色             鸟           牛奶       PallMall
           德国           绿色             鱼           咖啡         Prince
           瑞典           白色             狗           啤酒     BlueMaster
*/ 






