#include "Visualizer.h"
#include "BubbleSort.h"
#include <raylib.h>
#include <algorithm>
#include <cstdlib>
#include <time.h>
#include <string>

void Visualizer::Main()
{
	Start();

	InitWindow(mScreenWidth, mScreenHeight, "Sorting Visualizer");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		float deltaTime = GetFrameTime();

		BeginDrawing();
		ClearBackground(BLACK);

		Update(deltaTime);
		Draw();

		EndDrawing();
	}
}

void Visualizer::Start()
{
	srand(time(0));

	GenerateArray();

	CreateAlgorithm();
}

void Visualizer::Update(float deltaTime)
{
	// --------------------------------------------------------
	// Algorithm selection
	// --------------------------------------------------------

	if (IsKeyPressed(KEY_ONE))
	{
		SelectAlgorithm(AlgorithmType::Bubble);
	}

	if (IsKeyPressed(KEY_TWO))
	{
		SelectAlgorithm(AlgorithmType::Insertion);
	}

	if (IsKeyPressed(KEY_THREE))
	{
		SelectAlgorithm(AlgorithmType::Selection);
	}

	if (IsKeyPressed(KEY_FOUR))
	{
		SelectAlgorithm(AlgorithmType::Merge);
	}

	if (IsKeyPressed(KEY_FIVE))
	{
		SelectAlgorithm(AlgorithmType::Quick);
	}

	if (IsKeyPressed(KEY_SIX))
	{
		SelectAlgorithm(AlgorithmType::Bucket);
	}

	if (IsKeyPressed(KEY_SEVEN))
	{
		SelectAlgorithm(AlgorithmType::Heap);
	}

	if (IsKeyPressed(KEY_EIGHT))
	{
		SelectAlgorithm(AlgorithmType::Intro);
	}

	if (IsKeyPressed(KEY_SPACE))
	{
		TogglePause();
	}

	if (IsKeyPressed(KEY_R))
	{
		Randomize();
	}

	if (IsKeyPressed(KEY_UP))
	{
		mStepDelay -= 0.01f;

		if (mStepDelay < 0.005f)
			mStepDelay = 0.005f;
	}

	if (IsKeyPressed(KEY_DOWN))
	{
		// Slower
		mStepDelay += 0.01f;

		if (mStepDelay > 0.100f)
			mStepDelay = 0.100f;
	}

	UpdateAlgorithm(deltaTime);
}

void Visualizer::Draw()
{
	DrawArray();
	DrawUI();
}

void Visualizer::Randomize()
{
	GenerateArray();

	mAlgorithm->Start(mVec);

	mStepTimer = 0.0f;

	mSortingTime = 0.0f;
	mSortingStarted = false;

	mGreenIndex = 0;
	mGreenTimer = 0.0f;
	mFinishingAnimation = false;

	mPaused = false;
}

void Visualizer::TogglePause()
{
	mPaused = !mPaused;
}

void Visualizer::GenerateArray()
{
	mVec.clear();
	mVec.reserve(mElementCount);

	for (int i = 0; i < mElementCount; i++)
	{
		mVec.push_back(GetRandomValue(20, 500));
	}

	mOriginalVec = mVec;
}

void Visualizer::UpdateAlgorithm(float deltaTime)
{
	if (mFinishingAnimation)
	{
		UpdateFinishingAnimation(deltaTime);
		return;
	}

	if (mPaused)
		return;

	if (mAlgorithm->IsFinished())
	{
		mFinishingAnimation = true;
		mGreenIndex = 0;
		mGreenTimer = 0.0f;

		return;
	}

	mSortingStarted = true;
	mSortingTime += deltaTime;
	mStepTimer += deltaTime;

	if (mStepTimer >= mStepDelay)
	{
		mStepTimer = 0.0f;
		mAlgorithm->Step();
	}

	if (mAlgorithm->IsFinished())
	{
		mSortingStarted = false;

		mFinishingAnimation = true;
		mGreenIndex = 0;
		mGreenTimer = 0.0f;
	}
}

void Visualizer::DrawArray()
{
	float barWidth = static_cast<float>(mScreenWidth) / static_cast<float>(mElementCount);

	const float bottomMargin = 100.0f;

	for (int i = 0; i < mElementCount; i++)
	{
		float value = static_cast<float>(mVec[i].value);

		Rectangle bar;
		bar.x = i * barWidth;
		bar.y = static_cast<float>(mScreenHeight) - bottomMargin - value;
		bar.width = barWidth - 1;
		bar.height = value;

		DrawRectangleRec(bar, mVec[i].color);
	}
}

void Visualizer::DrawUI()
{
	int fontSizeS = 16;
	int fontSizeB = 20;

	// Background information
	DrawRectangle(0, mScreenHeight - 100, mScreenWidth, 100, DARKGRAY);

	// Current algorithm
	DrawText(TextFormat("Algorithm: %s", mAlgorithm->GetName()), 20, mScreenHeight - 90, fontSizeB, WHITE);

	// Statistics - Left column
	DrawText(TextFormat("Comparisons: %llu", mAlgorithm->GetComparisons()), 20, mScreenHeight - 60, fontSizeS, WHITE);
	DrawText(TextFormat("Swaps: %llu", mAlgorithm->GetSwaps()), 20, mScreenHeight - 35, 16, WHITE);

	// Statistics - Middle column
	DrawText(TextFormat("Elements: %d", mElementCount), 290, mScreenHeight - 60, fontSizeS, WHITE);
	DrawText(TextFormat("Delay: %.3f", mStepDelay), 290, mScreenHeight - 35, fontSizeS, WHITE);
	DrawText(TextFormat("Time: %.3f s", mSortingTime), 290, mScreenHeight - 85, fontSizeS, WHITE);

	// Pause status
	const char* status = mPaused ? "PAUSED" : mAlgorithm->IsFinished() ? "FINISHED" : "RUNNING";

	DrawText(status, 425, mScreenHeight - 60, fontSizeB, mPaused ? YELLOW : GREEN);

	// Controls
	DrawText("1-8: Algorithm", 550, mScreenHeight - 80, fontSizeS, WHITE);
	DrawText("SPACE: Pause", 550, mScreenHeight - 55, fontSizeS, WHITE);
	DrawText("R: Randomize", 550, mScreenHeight - 30, fontSizeS, WHITE);
	DrawText("UP/DOWN: Speed", 700, mScreenHeight - 80, fontSizeS, WHITE);

	// Algorithm menu
	int menuX = 900;
	int menuY = mScreenHeight - 85;

	const int columnWidth = 170;
	const int rowHeight = 20;

	for (int i = 0; i < 8; i++)
	{
		AlgorithmType type = static_cast<AlgorithmType>(i);

		int column = i / 4;
		int row = i % 4;

		int x = menuX + column * columnWidth;
		int y = menuY + row * rowHeight;

		Color textColor = type == mCurrentAlgorithm ? YELLOW : LIGHTGRAY;

		DrawText(TextFormat("%d - %s", i + 1, GetAlgorithmName(type)), x, y, fontSizeS, textColor);
	}
}

void Visualizer::CreateAlgorithm()
{
	switch (mCurrentAlgorithm)
	{
	case AlgorithmType::Bubble:
		mAlgorithm = std::make_unique<BubbleSort>();
		break;

	case AlgorithmType::Insertion:
		mAlgorithm = std::make_unique<InsertionSort>();
		break;

	case AlgorithmType::Selection:
		mAlgorithm = std::make_unique<SelectionSort>();
		break;

	case AlgorithmType::Merge:
		mAlgorithm = std::make_unique<MergeSort>();
		break;

	case AlgorithmType::Quick:
		mAlgorithm = std::make_unique<QuickSort>();
		break;

	case AlgorithmType::Bucket:
		mAlgorithm = std::make_unique<BucketSort>();
		break;

	case AlgorithmType::Heap:
		mAlgorithm = std::make_unique<HeapSort>();
		break;

	case AlgorithmType::Intro:
		mAlgorithm = std::make_unique<IntroSort>();
		break;
	}

	mAlgorithm->Start(mVec);
	mStepTimer = 0.0f;
}

void Visualizer::SelectAlgorithm(AlgorithmType type)
{
	mCurrentAlgorithm = type;
	mVec = mOriginalVec;

	mSortingTime = 0.0f;
	mSortingStarted = false;

	mGreenIndex = 0;
	mGreenTimer = 0.0f;
	mFinishingAnimation = false;

	mStepTimer = 0.0f;
	mPaused = false;

	CreateAlgorithm();
}

void Visualizer::UpdateFinishingAnimation(float deltaTime)
{
	if (!mFinishingAnimation)
		return;

	mGreenTimer += deltaTime;

	if (mGreenTimer >= mGreenDelay)
	{
		mGreenTimer = 0.0f;

		if (mGreenIndex < mElementCount)
		{
			mVec[mGreenIndex].color = GREEN;
			mGreenIndex++;
		}
		else
		{
			mFinishingAnimation = false;
		}
	}
}

const char* Visualizer::GetAlgorithmName(AlgorithmType type) const
{
	switch (type)
	{
	case AlgorithmType::Bubble:
		return "Bubble Sort";

	case AlgorithmType::Insertion:
		return "Insertion Sort";

	case AlgorithmType::Selection:
		return "Selection Sort";

	case AlgorithmType::Merge:
		return "Merge Sort";

	case AlgorithmType::Quick:
		return "Quick Sort";

	case AlgorithmType::Bucket:
		return "Bucket Sort";

	case AlgorithmType::Heap:
		return "Heap Sort";

	case AlgorithmType::Intro:
		return "Intro Sort";
	}

	return "Unknown";
}