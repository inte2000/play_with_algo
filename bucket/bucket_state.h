// bucket_state.h : 
//

#ifndef __BUCKET_STATE_H__
#define __BUCKET_STATE_H__

#include <initializer_list>

const int BUCKETS_COUNT = 3;

typedef struct
{
    int from;
    int to;
    int water;
}ACTION;

class Bucket
{
public:
    Bucket(int capicity, int water = 0) { m_capicity = capicity; m_water = water; }
    bool IsFull() const { return (m_capicity == m_water); }
    bool HasWater() const { return (m_water > 0); }
    int GetSpace() const { return (m_capicity - m_water); }
    int GetWater() const { return m_water; }
    void AddWater(int water);
    void DumpWater(int water);
protected:
    int m_water;
    int m_capicity;
};


class BucketsState
{
public:
    BucketsState(const std::initializer_list<Bucket>& il);
    BucketsState() {};
    void PrintStates() const;
    bool operator == (const BucketsState& state) const;
    bool TakeAction(int from, int to, BucketsState& next);
    Bucket& GetBucket(int index) { return m_buckets[index]; }
    const Bucket& GetBucket(int index) const { return m_buckets[index]; }
protected:
    void SetAction(int w, int f, int t);

    std::vector<Bucket> m_buckets;
    ACTION m_curAction;
};

#endif //__BUCKET_STATE_H__
