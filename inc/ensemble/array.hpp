/* License: MIT. See LICENSE in root directory. */

/**
 * \date 2020/07/01
 */

#pragma once

#include <string>

namespace Ensemble
{

template<typename T>
class Array
{
protected:

    T* m_pData = nullptr;

    uint m_Allocated = 0;

    uint m_Count = 0;

    uint m_GrowBy = 0x20;

public:

    Array() = default;

    Array(uint initialSize, uint growBy);

    ~Array();

public:

    static
    T* CreateArray(uint newArraySize);

    static
    void DisposeArray(T* pData, uint count, uint allocated);

    static
    void AddElements(T const* pSrc, T* pDest, uint count);

    static
    void MoveElements(T* pSrc, T* pDest, uint count);

    static
    void RemoveElements(T* pData, uint count);

    static
    void CreateEmptyElements(T* pData, uint count);

public:

    inline
    uint Count()
    { return m_Count; }

    T& operator[](uint index) const;

    void Append(T const& item);

    bool CheckForGrowth(uint addCount);

    bool CheckForInsertionGrowth(uint insertPoint, uint addCount);

    void ExpandCapacityBy(uint minNeeded);

    uint GetExpandedSize(uint additionalNeeded);

    void EnsureCapacity(uint newCapacity);

    T* AppendNew();

    void ResizeArray(uint newSize);

    void SwapElements(uint index1, uint index2);

    int Find(T const& item, uint startPos = 0);

    void Insert(T const* item, uint index = 0);

    bool Remove(T const& item);

    void RemoveAt(uint index);

    void RemoveLast();

    void ShiftElementsUp(uint index, uint count);

    void ShiftElementsDown(uint index, uint count);
};

template
class Array<std::string>;

} // namespace Ensemble
