#include "MergeSort.h"
#include "MergeSort.h"
#include <algorithm>

void MergeSort::Start(std::vector<Element>& vec)
{
	mVec = &vec;

	while (!mRanges.empty())
		mRanges.pop();

	mTemp.resize(vec.size());

	mComparisons = 0;
	mSwaps = 0;

	mSplitting = true;
	mMerging = false;
	mFinished = false;

	ResetColors(*mVec);

	if (vec.size() <= 1)
	{
		mFinished = true;
		return;
	}

	mRanges.push({ 0, static_cast<int>(vec.size()) - 1 });
}

void MergeSort::Step()
{
	if (mFinished || mVec == nullptr)
		return;

	ResetColors(*mVec);

	if (!mMerging)
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

		mMid = mLow + (mHigh - mLow) / 2;

		mRanges.push({ mLow, mMid });
		mRanges.push({ mMid + 1, mHigh });

		mLeft = mLow;
		mRight = mMid + 1;
		mWrite = mLow;

		mMerging = true;

		return;
	}

	if (mLeft <= mMid && mRight <= mHigh)
	{
		(*mVec)[mLeft].color = BLUE;
		(*mVec)[mRight].color = RED;

		mComparisons++;

		if ((*mVec)[mLeft].value <= (*mVec)[mRight].value)
		{
			mTemp[mWrite] = (*mVec)[mLeft];
			mLeft++;
		}
		else
		{
			mTemp[mWrite] = (*mVec)[mRight];
			mRight++;
		}

		mWrite++;
		return;
	}

	if (mLeft <= mMid)
	{
		(*mVec)[mLeft].color = BLUE;
		mTemp[mWrite] = (*mVec)[mLeft];

		mLeft++;
		mWrite++;

		return;
	}

	if (mRight <= mHigh)
	{
		(*mVec)[mRight].color = RED;
		mTemp[mWrite] = (*mVec)[mRight];

		mRight++;
		mWrite++;

		return;
	}

	for (int i = mLow; i <= mHigh; i++)
	{
		(*mVec)[i] = mTemp[i];
	}

	mMerging = false;
}

bool MergeSort::IsFinished() const
{
	return mFinished;
}

uint64_t MergeSort::GetComparisons() const
{
	return mComparisons;
}

uint64_t MergeSort::GetSwaps() const
{
	return mSwaps;
}

const char* MergeSort::GetName() const
{
	return "Merge Sort";
}
