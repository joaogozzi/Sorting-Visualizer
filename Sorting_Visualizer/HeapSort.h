#pragma once
#include "SortingAlgorithm.h"

class HeapSort : public SortingAlgorithm
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

	int mHeapSize = 0;

	int mBuildRoot = 0;

	int mRoot = 0;
	int mLargest = 0;

	int mChildStage = 0;

	bool mBuildingHeap = true;
	bool mHeapifying = false;
	bool mFinished = false;

	uint64_t mComparisons = 0;
	uint64_t mSwaps = 0;

	void StartHeapify(int root);
};