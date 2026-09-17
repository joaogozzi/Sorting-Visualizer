#include "InsertionSort.h"

void InsertionSort::Start(std::vector<Element>& vec)
{
	StartRange(vec, 0, vec.size() - 1);
}

void InsertionSort::StartRange(std::vector<Element>& vec, int low, int high)
{
	mVec = &vec;

	mLow = low;
	mHigh = high;

	mCurrent = low + 1;
	mCompareIndex = -1;

	mKey = Element(0);

	mStarted = false;
	mFinished = false;

	mComparisons = 0;
	mSwaps = 0;

	ResetColors(*mVec);

	if (mLow >= mHigh)
	{
		mFinished = true;
	}
}

void InsertionSort::Step()
{
	if (mFinished || mVec == nullptr)
		return;

	ResetColors(*mVec);

	if (!mStarted)
	{
		if (mCurrent > mHigh)
		{
			mFinished = true;
			return;
		}

		mKey = (*mVec)[mCurrent];
		mCompareIndex = mCurrent - 1;
		mStarted = true;
		(*mVec)[mCurrent].color = BLUE;

		return;
	}

	if (mCompareIndex >= mLow)
	{
		(*mVec)[mCompareIndex].color = RED;

		if (mCompareIndex + 1 <= mHigh)
			(*mVec)[mCompareIndex + 1].color = BLUE;

		mComparisons++;

		if ((*mVec)[mCompareIndex].value > mKey.value)
		{
			(*mVec)[mCompareIndex + 1] = (*mVec)[mCompareIndex];

			mSwaps++;
			mCompareIndex--;
			return;
		}
	}

	(*mVec)[mCompareIndex + 1] = mKey;

	mCurrent++;
	mStarted = false;
}

bool InsertionSort::IsFinished() const
{
	return mFinished;
}

uint64_t InsertionSort::GetComparisons() const
{
	return mComparisons;
}

uint64_t InsertionSort::GetSwaps() const
{
	return mSwaps;
}

const char* InsertionSort::GetName() const
{
	return "Insertion Sort";
}