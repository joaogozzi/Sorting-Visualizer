#pragma once
#include <vector>
#include <cstdint>
#include "Element.h"

class SortingAlgorithm
{
public:
    virtual ~SortingAlgorithm() = default;

    virtual void Start(std::vector<Element>& vec) = 0;
    virtual void Step() = 0;

    virtual bool IsFinished() const = 0;

    virtual uint64_t GetComparisons() const = 0;
    virtual uint64_t GetSwaps() const = 0;

    virtual const char* GetName() const = 0;

protected:
    void ResetColors(std::vector<Element>& vec)
    {
        for (Element& element : vec)
        {
            element.color = WHITE;
        }
    }
};