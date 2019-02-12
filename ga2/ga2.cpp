// ga2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <functional>

double BinFunc(double x)
{
    return (-2.0*x*x + 5*x + 6);
}
//9.125
//[0, 3.0]



const int POPULATION_SIZE = 64;
const int MAX_GENERATIONS = 200;
const double P_XOVER = 0.8;
const double P_MUTATION = 0.15;


typedef struct GAType
{
    unsigned short gene;
    double fitness;
    double low;
    double high;
}GATYPE;

unsigned short GrayEncoding(unsigned short decimal)
{
    return decimal ^ (decimal >> 1);
}

unsigned short GrayDecoding(unsigned short gray)
{
    unsigned int decimal = gray;
    while (gray >>= 1)
        decimal ^= gray;

    return decimal;
}

unsigned short GetRandomGene()
{
    //产生随机数u，并映射到正整数0-65535范围上
    double u = (double)rand() / (RAND_MAX + 1) * 65536.0;
    //转换为格雷码
    unsigned short g = GrayEncoding((unsigned short)u);

    return g;
}

void EnvaluateFitness(GATYPE *pop)
{
    for(int i = 0; i < POPULATION_SIZE; i++)
    {
        unsigned short k = GrayDecoding(pop[i].gene);
        //根据编码值，得到[0.0, 3.0]区间上的x值
        double x = k * (pop[i].high - pop[i].low) / 65536.0 + pop[i].low;

        pop[i].fitness = BinFunc(x);
    }
}

int GetBestPopulation(GATYPE *pop)
{
    int best = 0;
    for(int i = 0; i < POPULATION_SIZE; i++)
    {
        if(pop[i].fitness > pop[best].fitness)
        {
            best = i;
        }
    }

    return best;
}

int GetWorstPopulation(GATYPE *pop)
{
    int worst = 0;
    for(int i = 0; i < POPULATION_SIZE; i++)
    {
        if(pop[i].fitness < pop[worst].fitness)
        {
            worst = i;
        }
    }

    return worst;
}

void Select(GATYPE *pop, GATYPE *next_pop)
{
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        int fm = (int)((double)rand() / (RAND_MAX + 1) * POPULATION_SIZE);
        int fn = (int)((double)rand() / (RAND_MAX + 1) * POPULATION_SIZE);
        if (pop[fm].fitness >= pop[fn].fitness)
        {
            next_pop[i] = pop[fm];
        }
        else
        {
            next_pop[i] = pop[fn];
        }
    }
}

unsigned short MakeMask(int sBit, int eBit)
{
    unsigned short mask = 0xFFFF;
    int keep = (eBit - sBit + 1);

    mask >>= (16 - keep);
    mask <<= (16 - eBit);

    return mask;
}

void ExchangeOver(GATYPE *pop, int first, int second)
{
    int ps = (int)((double)rand() / (RAND_MAX + 1) * 6 + 0.5);
    int pe = (int)((double)rand() / (RAND_MAX + 1) * 6 + 8.5);

    unsigned short mask = MakeMask(ps, pe);
    unsigned short revMask = ~mask;
    unsigned short temp1 = pop[first].gene & mask;
    unsigned short temp2 = pop[second].gene & mask;

    pop[first].gene &= revMask;
    pop[first].gene |= temp2;
    pop[second].gene &= revMask;
    pop[second].gene |= temp1;
}

void Crossover(GATYPE *pop)
{
    int first = -1;

    for(int i = 0; i < POPULATION_SIZE; i++)
    {
        double p = (double)rand() / (RAND_MAX + 1);
        if((p < P_XOVER) || (first >= 0))
        {
            if(first < 0)
            {
                first = i;
            }
            else
            {
                ExchangeOver(pop, first, i);
                first = -1;
            }
        }
    }
}

void ReverseBit(GATYPE *pop, int index, int bit)
{
    unsigned short mask = 0x0001 << (15 - bit);

    if(pop[index].gene & mask)
    {
        pop[index].gene &= ~mask;
    }
    else
    {
        pop[index].gene |= mask;
    }
}

void Mutation(GATYPE *pop)
{
    for(int i = 0; i < POPULATION_SIZE; i++)
    {
        double p = (double)rand() / (RAND_MAX + 1);
        if(p < P_MUTATION)
        {
            int bit = (int)((double)rand() / (RAND_MAX + 1) * 15);
            ReverseBit(pop, i, bit);
        }
    }
}

void Initialize(GATYPE *pop)
{
    for(int i = 0; i < POPULATION_SIZE; i++)
    {
        pop[i].low = 0.0;
        pop[i].high = 3.0;
        pop[i].gene = GetRandomGene();
        pop[i].fitness = 0.0;
    }
}

double DiffSquare(double value, double avg)
{
    return (value - avg) * (value - avg);
}

double CalcStandardDeviation(double *params, int count)
{
    assert(count > 0);

    double average = std::accumulate(params, params + count, 0.0) / count;
    std::vector<double> diffSq(count);
    std::transform(params, params + count, diffSq.begin(), 
                   std::bind2nd(std::ptr_fun(DiffSquare), average));
    
    double samvar = std::accumulate(diffSq.begin(), diffSq.end(), 0.0) / count;
    
    return std::sqrt(samvar);
}

const int TEST_ROUND = 500;

int main(int argc, char* argv[])
{
    srand((unsigned)time(NULL));

    GATYPE population[POPULATION_SIZE] = { 0 };
    double fitness[TEST_ROUND] = { 0.0 };
    for(int k = 0; k < TEST_ROUND; k++)
    {
        Initialize(population);

        GATYPE next_population[POPULATION_SIZE] = { 0 };
        for(int i = 0; i < MAX_GENERATIONS; i++)
        {
            EnvaluateFitness(population);
            Select(population, next_population);
            Crossover(next_population);
            Mutation(next_population);
            for (int j = 0; j < POPULATION_SIZE; j++)
            {
                population[j] = next_population[j];
            }
        }
        int best = GetBestPopulation(population);
        fitness[k] = population[best].fitness;
    }
    double sdv = CalcStandardDeviation(fitness, TEST_ROUND);
    double avgfitness = std::accumulate(fitness, fitness + TEST_ROUND, 0.0) / TEST_ROUND;


	return 0;
}

