#include "IntroSort.h"
#include <cmath>

void IntroSort::Start(std::vector<Element>& vec)
{
	mVec = &vec;

	while (!mRanges.empty())
		mRanges.pop();

	mCurrentSort = nullptr;

	mFinished = false;

	mComparisons = 0;
	mSwaps = 0;

	mPreviousComparisons = 0;
	mPreviousSwaps = 0;

	for (Element& element : *mVec)
		element.color = WHITE;

	int size = mVec->size();

	if (size <= 1)
	{
		mFinished = true;
		return;
	}

	int maxDepth = 2 * std::log2(size);

	mRanges.push({ 0, size - 1, maxDepth });
}

void IntroSort::StartNextRange()
{
	if (mRanges.empty())
	{
		mCurrentSort = nullptr;
		mFinished = true;

		return;
	}

	Range range = mRanges.top();

	mRanges.pop();

	int size = range.high - range.low + 1;

	if (size <= INSERTION_THRESHOLD)
	{
		mInsertionSort.StartRange(*mVec, range.low, range.high);
		mCurrentSort = &mInsertionSort;

		return;
	}

	if (range.depth <= 0)
	{
		mHeapSort.StartRange(*mVec, range.low, range.high);
		mCurrentSort = &mHeapSort;

		return;
	}

	mQuickSort.StartRange(*mVec, range.low, range.high);

	mCurrentSort = &mQuickSort;
}

void IntroSort::AddStatistics()
{
	if (mCurrentSort == nullptr)
		return;

	uint64_t currentComparisons = mCurrentSort->GetComparisons();

	uint64_t currentSwaps = mCurrentSort->GetSwaps();

	mComparisons += currentComparisons - mPreviousComparisons;

	mSwaps += currentSwaps - mPreviousSwaps;

	mPreviousComparisons = currentComparisons;

	mPreviousSwaps = currentSwaps;
}

void IntroSort::Step()
{
	if (mFinished || mVec == nullptr)
		return;

	if (mCurrentSort == nullptr)
	{
		StartNextRange();

		if (mFinished)
			return;

		mPreviousComparisons = 0;
		mPreviousSwaps = 0;

		return;
	}

	mCurrentSort->Step();

	AddStatistics();

	if (mCurrentSort->IsFinished())
	{
		mCurrentSort = nullptr;
	}
}

bool IntroSort::IsFinished() const
{
	return mFinished;
}

uint64_t IntroSort::GetComparisons() const
{
	return mComparisons;
}

uint64_t IntroSort::GetSwaps() const
{
	return mSwaps;
}

const char* IntroSort::GetName() const
{
	return "Intro Sort";
}