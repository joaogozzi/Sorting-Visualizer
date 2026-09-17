#include "BucketSort.h"
#include <algorithm>

void BucketSort::Start(std::vector<Element>& vec)
{
	mVec = &vec;

	mBuckets.clear();
	mBuckets.resize(10);

	mCurrentBucket = 0;
	mCurrentElement = 0;

	mWriteIndex = 0;

	mMaxValue = 0;

	mCreatingBuckets = true;
	mWriting = false;
	mFinished = false;

	mComparisons = 0;
	mSwaps = 0;

	ResetColors(*mVec);

	if (mVec->empty())
	{
		mFinished = true;
		return;
	}

	for (const Element& element : *mVec)
	{
		if (element.value > mMaxValue)
			mMaxValue = element.value;
	}
}

void BucketSort::Step()
{
	if (mFinished || mVec == nullptr)
		return;

	ResetColors(*mVec);

	if (mCreatingBuckets)
	{
		if (mCurrentElement >= static_cast<int>(mVec->size()))
		{
			mCreatingBuckets = false;
			mWriting = true;

			mCurrentBucket = 0;
			mCurrentElement = 0;

			return;
		}

		Element& element = (*mVec)[mCurrentElement];
		element.color = BLUE;

		int bucketIndex = (element.value * 10) / (mMaxValue + 1);

		if (bucketIndex >= 10)
			bucketIndex = 9;

		mBuckets[bucketIndex].push_back(element);
		mCurrentElement++;

		return;
	}

	if (mWriting)
	{
		if (mCurrentBucket >= 10)
		{
			mFinished = true;
			return;
		}

		if (mCurrentElement == 0)
		{
			std::sort(mBuckets[mCurrentBucket].begin(), mBuckets[mCurrentBucket].end(), [](const Element& a, const Element& b)
				{
					return a.value < b.value;
				}
			);
		}

		if (mCurrentElement >= static_cast<int>(mBuckets[mCurrentBucket].size()))
		{
			mCurrentBucket++;
			mCurrentElement = 0;

			return;
		}

		if (mWriteIndex < static_cast<int>(mVec->size()))
		{
			(*mVec)[mWriteIndex] = mBuckets[mCurrentBucket][mCurrentElement];
			(*mVec)[mWriteIndex].color = RED;

			mWriteIndex++;
			mCurrentElement++;
		}
	}
}

bool BucketSort::IsFinished() const
{
	return mFinished;
}

uint64_t BucketSort::GetComparisons() const
{
	return mComparisons;
}

uint64_t BucketSort::GetSwaps() const
{
	return mSwaps;
}

const char* BucketSort::GetName() const
{
	return "Bucket Sort";
}