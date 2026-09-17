#pragma once
#include "SortingAlgorithm.h"
#include <vector>
#include <stack>

class MergeSort : public SortingAlgorithm
{
public:
    void Start(std::vector<Element>& vec) override;
    void Step() override;

    bool IsFinished() const override;

    uint64_t GetComparisons() const override;
    uint64_t GetSwaps() const override;

    const char* GetName() const override;

private:
    struct Range
    {
        int low;
        int high;
    };

    std::vector<Element>* mVec = nullptr;
    std::stack<Range> mRanges;
    std::vector<Element> mTemp;

    int mLow = 0;
    int mHigh = 0;

    int mMid = 0;

    int mLeft = 0;
    int mRight = 0;

    int mWrite = 0;

    bool mSplitting = true;
    bool mMerging = false;

    bool mFinished = false;

    uint64_t mComparisons = 0;
    uint64_t mSwaps = 0;
};