#pragma once
#include "SortingAlgorithm.h"

#include "BubbleSort.h"
#include "InsertionSort.h"
#include "SelectionSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "BucketSort.h"
#include "HeapSort.h"
#include "IntroSort.h"
#include <raylib.h>
#include <memory>
#include <vector>

enum class AlgorithmType
{
	Bubble = 0,
	Insertion,
	Selection,
	Merge,
	Quick,
	Bucket,
	Heap,
	Intro
};

class Visualizer
{
public:
	void Main();
	void Start();
	void Update(float deltaTime);

	void Draw();
	void Randomize();
	void TogglePause();

private:
	const int mScreenWidth = 1280;
	const int mScreenHeight = 720;
	const int mElementCount = 100;
	int mBarWidth = 0;

	std::vector<Element> mVec;
	std::vector<Element> mOriginalVec;

	std::unique_ptr<SortingAlgorithm> mAlgorithm;

	AlgorithmType mCurrentAlgorithm = AlgorithmType::Bubble;

	float mStepTimer = 0.0f;
	float mStepDelay = 0.05f;

	float mSortingTime = 0.0f;
	bool mSortingStarted = false;

	int mGreenIndex = 0;
	float mGreenTimer = 0.0f;
	float mGreenDelay = 0.01f;
	bool mFinishingAnimation = false;

	bool mPaused = false;

	void GenerateArray();

	void UpdateAlgorithm(float deltaTime);

	void DrawArray();
	void DrawUI();

	void CreateAlgorithm();

	void SelectAlgorithm(AlgorithmType type);

	void UpdateFinishingAnimation(float deltaTime);

	const char* GetAlgorithmName(AlgorithmType type) const;
};