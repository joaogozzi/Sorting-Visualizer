#include "BubbleSort.h"

void BubbleSort::Start(std::vector<Element>& vec)
{
	StartRange(vec, 0, vec.size() - 1);
}

void BubbleSort::StartRange(std::vector<Element>& vec, int low, int high)
{
	mVec = &vec;

	mLow = low;
	mHigh = high;

	mCurrent = low;
	mEnd = high;

	mFinished = false;

	mComparisons = 0;
	mSwaps = 0;

	ResetColors(*mVec);

	if (mLow >= mHigh)
		mFinished = true;
}

void BubbleSort::Step()
{
	if (mFinished || mVec == nullptr)
		return;

	ResetColors(*mVec);

	if (mCurrent >= mEnd)
	{
		mCurrent = mLow;
		mEnd--;

		if (mEnd <= mLow)
		{
			mFinished = true;
			return;
		}
	}

	(*mVec)[mCurrent].color = BLUE;
	(*mVec)[mCurrent + 1].color = RED;

	mComparisons++;

	if ((*mVec)[mCurrent].value > (*mVec)[mCurrent + 1].value)
	{
		std::swap((*mVec)[mCurrent], (*mVec)[mCurrent + 1]);
		mSwaps++;
	}

	mCurrent++;
}

bool BubbleSort::IsFinished() const
{
	return mFinished;
}

const char* BubbleSort::GetName() const
{
	return "Bubble Sort";
}

uint64_t BubbleSort::GetComparisons() const
{
	return mComparisons;
}

uint64_t BubbleSort::GetSwaps() const
{
	return mSwaps;
}
