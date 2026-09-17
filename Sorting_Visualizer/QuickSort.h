#pragma once
#include "SortingAlgorithm.h"
#include <stack>

class QuickSort : public SortingAlgorithm
{
public:
	void Start(std::vector<Element>& vec) override;
	void StartRange(std::vector<Element>& vec, int low, int high);
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

	int mLow = 0;
	int mHigh = 0;

	int mI = 0;
	int mJ = 0;
	int mPivotIndex = 0;

	int mPivotValue = 0;

	bool mPartitioning = false;
	bool mFinished = false;

	uint64_t mComparisons = 0;
	uint64_t mSwaps = 0;
};