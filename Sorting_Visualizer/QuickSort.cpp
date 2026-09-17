#include "QuickSort.h"
#include <algorithm>

void QuickSort::Start(std::vector<Element>& vec)
{
	StartRange(vec, 0, vec.size() - 1);
}

void QuickSort::StartRange(std::vector<Element>& vec, int low, int high)
{
	mVec = &vec;

	while (!mRanges.empty())
	{
		mRanges.pop();
	}

	mLow = low;
	mHigh = high;

	mPartitioning = false;
	mFinished = false;

	mComparisons = 0;
	mSwaps = 0;

	ResetColors(*mVec);

	if (low < high)
		mRanges.push({ low, high });
	else
		mFinished = true;
}

void QuickSort::Step()
{
	if (mFinished || mVec == nullptr)
		return;

	ResetColors(*mVec);

	if (!mPartitioning)
	{
		if (mRanges.empty())
		{
			mFinished = true;
			return;
		}

		Range range = mRanges.top();
		mRanges.pop();

		mLow = range.low;
		mHigh = range.high;

		if (mLow >= mHigh)
			return;

		mI = mLow - 1;
		mJ = mLow;

		mPivotIndex = mHigh;
		mPivotValue = (*mVec)[mPivotIndex].value;

		mPartitioning = true;
	}

	if (mJ < mHigh)
	{
		(*mVec)[mJ].color = BLUE;
		(*mVec)[mPivotIndex].color = RED;

		mComparisons++;

		if ((*mVec)[mJ].value < mPivotValue)
		{
			mI++;

			if (mI != mJ)
			{
				std::swap((*mVec)[mI], (*mVec)[mJ]);
				mSwaps++;
			}
		}

		mJ++;
		return;
	}

	int pivotFinalIndex = mI + 1;

	if (pivotFinalIndex != mHigh)
	{
		std::swap((*mVec)[pivotFinalIndex], (*mVec)[mHigh]);
		mSwaps++;
	}

	mPartitioning = false;

	if (mLow < pivotFinalIndex - 1)
	{
		mRanges.push({ mLow,            pivotFinalIndex - 1 });
	}

	if (pivotFinalIndex + 1 < mHigh)
	{
		mRanges.push({ pivotFinalIndex + 1,            mHigh });
	}
}

bool QuickSort::IsFinished() const
{
	return mFinished;
}

uint64_t QuickSort::GetComparisons() const
{
	return mComparisons;
}

uint64_t QuickSort::GetSwaps() const
{
	return mSwaps;
}

const char* QuickSort::GetName() const
{
	return "Quick Sort";
}