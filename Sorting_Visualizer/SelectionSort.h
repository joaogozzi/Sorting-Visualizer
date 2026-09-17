#pragma once
#include "SortingAlgorithm.h"

class SelectionSort : public SortingAlgorithm
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
	std::vector<Element>* mVec = nullptr;

	int mLow = 0;
	int mHigh = 0;

	int mCurrent = 0;
	int mSearchIndex = 0;
	int mMinIndex = 0;

	bool mFinished = false;

	uint64_t mComparisons = 0;
	uint64_t mSwaps = 0;
};