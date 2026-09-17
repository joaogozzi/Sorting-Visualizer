#pragma once
#include "SortingAlgorithm.h"
#include <vector>

class BucketSort : public SortingAlgorithm
{
public:
    void Start(std::vector<Element>& vec) override;
    void Step() override;

    bool IsFinished() const override;

    uint64_t GetComparisons() const override;
    uint64_t GetSwaps() const override;

    const char* GetName() const override;

private:
    std::vector<Element>* mVec = nullptr;
    std::vector<std::vector<Element>> mBuckets;

    int mCurrentBucket = 0;
    int mCurrentElement = 0;

    int mWriteIndex = 0;

    int mMaxValue = 0;

    bool mCreatingBuckets = true;
    bool mWriting = false;
    bool mFinished = false;

    uint64_t mComparisons = 0;
    uint64_t mSwaps = 0;
};