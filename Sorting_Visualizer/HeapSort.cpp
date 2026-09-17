#include "HeapSort.h"
#include <algorithm>

void HeapSort::Start(std::vector<Element>& vec)
{
	StartRange(vec, 0, vec.size() - 1);
}

void HeapSort::StartRange(std::vector<Element>& vec, int low, int high)
{
	mVec = &vec;

	mLow = low;
	mHigh = high;

	mHeapSize = high - low + 1;

	mBuildRoot = mHeapSize / 2 - 1;

	mRoot = 0;
	mLargest = 0;
	mChildStage = 0;

	mBuildingHeap = true;
	mHeapifying = false;
	mFinished = false;

	mComparisons = 0;
	mSwaps = 0;

	ResetColors(*mVec);

	if (mHeapSize <= 1)
		mFinished = true;
}

void HeapSort::StartHeapify(int root)
{
	mRoot = root;
	mLargest = root;
	mChildStage = 0;
	mHeapifying = true;
}

void HeapSort::Step()
{
	if (mFinished || mVec == nullptr)
		return;

	ResetColors(*mVec);

	if (mBuildingHeap)
	{
		if (!mHeapifying)
		{
			if (mBuildRoot < 0)
			{
				mBuildingHeap = false;
				mHeapSize = mHigh - mLow + 1;
				return;
			}

			StartHeapify(mBuildRoot);
			mBuildRoot--;

			return;
		}
	}

	if (mHeapifying)
	{
		int left = 2 * mRoot + 1;
		int right = 2 * mRoot + 2;
		int rootIndex = mLow + mRoot;

		if (mChildStage == 0)
		{
			(*mVec)[rootIndex].color = BLUE;

			if (left < mHeapSize)
			{
				int leftIndex = mLow + left;

				(*mVec)[leftIndex].color = RED;

				mComparisons++;

				if ((*mVec)[leftIndex].value > (*mVec)[mLow + mLargest].value)
					mLargest = left;
			}

			mChildStage = 1;
			return;
		}

		if (mChildStage == 1)
		{
			(*mVec)[rootIndex].color = BLUE;

			if (right < mHeapSize)
			{
				int rightIndex = mLow + right;

				(*mVec)[rightIndex].color = RED;
				mComparisons++;

				if ((*mVec)[rightIndex].value > (*mVec)[mLow + mLargest].value)
					mLargest = right;
			}

			mChildStage = 2;
			return;
		}

		if (mLargest != mRoot)
		{
			std::swap((*mVec)[mLow + mRoot], (*mVec)[mLow + mLargest]);
			mSwaps++;
			StartHeapify(mLargest);

			return;
		}

		mHeapifying = false;
		return;
	}

	if (mHeapSize <= 1)
	{
		mFinished = true;
		return;
	}

	int lastIndex = mLow + mHeapSize - 1;

	std::swap((*mVec)[mLow], (*mVec)[lastIndex]);
	mSwaps++;
	mHeapSize--;

	StartHeapify(0);
}

bool HeapSort::IsFinished() const
{
	return mFinished;
}

uint64_t HeapSort::GetComparisons() const
{
	return mComparisons;
}

uint64_t HeapSort::GetSwaps() const
{
	return mSwaps;
}

const char* HeapSort::GetName() const
{
	return "Heap Sort";
}