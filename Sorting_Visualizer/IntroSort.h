#pragma once
#include "SortingAlgorithm.h"
#include "InsertionSort.h"
#include "QuickSort.h"
#include "HeapSort.h"
#include <stack>

class IntroSort : public SortingAlgorithm
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
		int depth;
	};

	std::vector<Element>* mVec = nullptr;

	std::stack<Range> mRanges;

	InsertionSort mInsertionSort;
	QuickSort mQuickSort;
	HeapSort mHeapSort;

	SortingAlgorithm* mCurrentSort = nullptr;

	bool mFinished = false;

	uint64_t mComparisons = 0;
	uint64_t mSwaps = 0;

	uint64_t mPreviousComparisons = 0;
	uint64_t mPreviousSwaps = 0;

	static constexpr int INSERTION_THRESHOLD = 16;

	void StartNextRange();

	void AddStatistics();
};