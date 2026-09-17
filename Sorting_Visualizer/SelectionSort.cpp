#include "SelectionSort.h"
#include "SelectionSort.h"
#include <algorithm>

void SelectionSort::Start(std::vector<Element>& vec)
{
	StartRange(vec, 0, vec.size() - 1);
}

void SelectionSort::StartRange(std::vector<Element>& vec, int low, int high)
{
	mVec = &vec;

	mLow = low;
	mHigh = high;

	mCurrent = low;
	mSearchIndex = low + 1;
	mMinIndex = low;

	mFinished = false;

	mComparisons = 0;
	mSwaps = 0;

	ResetColors(*mVec);

	if (mLow >= mHigh)
		mFinished = true;
}

void SelectionSort::Step()
{
	if (mFinished || mVec == nullptr)
		return;

	ResetColors(*mVec);

	if (mCurrent >= mHigh)
	{
		mFinished = true;
		return;
	}

	if (mSearchIndex <= mHigh)
	{
		(*mVec)[mCurrent].color = BLUE;
		(*mVec)[mSearchIndex].color = RED;

		mComparisons++;

		if ((*mVec)[mSearchIndex].value < (*mVec)[mMinIndex].value)
		{
			mMinIndex = mSearchIndex;
		}

		mSearchIndex++;
		return;
	}

	if (mMinIndex != mCurrent)
	{
		std::swap((*mVec)[mCurrent], (*mVec)[mMinIndex]);
		mSwaps++;
	}

	mCurrent++;
	mSearchIndex = mCurrent + 1;
	mMinIndex = mCurrent;
}

bool SelectionSort::IsFinished() const
{
	return mFinished;
}

uint64_t SelectionSort::GetComparisons() const
{
	return mComparisons;
}

uint64_t SelectionSort::GetSwaps() const
{
	return mSwaps;
}

const char* SelectionSort::GetName() const
{
	return "Selection Sort";
}