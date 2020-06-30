/* License: MIT. See LICENSE in root directory. */

/**
 * \date 2020/07/01
 */

#include <cstring>

#include "../../inc/ensemble/array.hpp"

namespace Ensemble {

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
Array<T>::Array(uint initialSize, uint growBy)
    :
    m_GrowBy(growBy),
    m_Allocated(initialSize),
    m_pData(CreateArray(initialSize))
{
}

template<typename T>
Array<T>::~Array()
{
    DisposeArray(m_pData, m_Count, m_Allocated);
    m_pData = nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
T* Array<T>::CreateArray(uint newArraySize)
{
    if (newArraySize != 0)
    {
        return new T[newArraySize];
    }

    return nullptr;
}

template<typename T>
void Array<T>::DisposeArray(T* pData, uint count, uint allocated)
{
    if (pData != nullptr && allocated != 0)
    {
        if (count != 0)
        {
            RemoveElements(pData, count);
        }
        delete pData;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
void Array<T>::AddElements(T const* pSrc, T* pDest, uint count)
{
    if (pSrc != nullptr && pDest != nullptr && count != 0)
    {
        memcpy((char*)pDest, (char*)pSrc, sizeof(T) * count);
    }
}

template<typename T>
void Array<T>::MoveElements(T* pSrc, T* pDest, uint count)
{
    if (pSrc != nullptr && pDest != nullptr && count != 0)
    {
        memcpy((char*)pDest, (char*)pSrc, sizeof(T) * count);
    }
}

template<typename T>
void Array<T>::RemoveElements(T* pData, uint count)
{
    if (pData != nullptr)
    {
        for (int i = 0; i < count; ++i)
        {
            delete &pData[i];
        }
    }
}

template<typename T>
void Array<T>::CreateEmptyElements(T* pData, uint count)
{
    if (pData != nullptr)
    {
        for (int i = 0; i < count; ++i)
        {
            pData[i] = T();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
T& Array<T>::operator[](uint index) const
{
    return m_pData[index];
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
void Array<T>::Append(T const& item)
{
    if (CheckForGrowth(1))
    {
        AddElements(&item, &m_pData[m_Count++], 1);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
bool Array<T>::CheckForGrowth(uint addCount)
{
    if (m_Count + addCount > m_Allocated)
    {
        ExpandCapacityBy(m_Count + addCount - m_Allocated);
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
uint Array<T>::GetExpandedSize(uint additionalNeeded)
{
    if (additionalNeeded > 0)
    {
        auto tempGrowBy = m_GrowBy;
        if (m_GrowBy == 0)
        {
            tempGrowBy = 1;
        }
        auto tempAllocated = m_Allocated;
        auto v5 = tempAllocated + additionalNeeded;
        if (tempAllocated < 1)
        {
            tempAllocated = 1;
        }
        while (tempAllocated < v5)
        {
            tempAllocated *= 2;
        }

        return m_Allocated + tempGrowBy * ((tempGrowBy + additionalNeeded - 1) / tempGrowBy);
    }

    return m_Allocated;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
void Array<T>::ExpandCapacityBy(uint minNeeded)
{
    if (minNeeded > 0)
    {
        ResizeArray(GetExpandedSize(minNeeded));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
void Array<T>::EnsureCapacity(uint newCapacity)
{
    if (m_Allocated < newCapacity)
    {
        ResizeArray(newCapacity);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
int Array<T>::Find(T const& item, uint startPos)
{
//    unsigned char v9;
//    int v19 = 0;
//
//    if (m_Count != 0 && startPos < m_Count)
//    {
//        for (uint j = 0, i = startPos; i < m_Count; ++i, ++j)
//        {
//            auto pCurrData = &m_pData[i];
//            auto pCurrItem = item[j];
//            auto v7 = 4;
//            do
//            {
//                if (*pCurrData != *pCurrItem)
//                {
//                    break;
//                }
//                v7 -= 4;
//                ++pCurrItem;
//                ++pCurrData;
//                if (v7 < 4)
//                {
//                    LABEL_18:
//                    v19 = false;
//                    goto LABEL_19;
//                }
//            } while (v7 >= 4);
//
//            v9 = *(unsigned char*)pCurrData - *(unsigned char*)pCurrItem;
//            if (*(unsigned char*)pCurrData == *(unsigned char*)pCurrItem)
//            {
//                auto v10 = v7 - 1;
//                auto v11 = (char*)pCurrItem + 1;
//                auto v12 = (char*)pCurrData + 1;
//                if (!v10)
//                {
//                    goto LABEL_18;
//                }
//                v9 = *v12 - *v11;
//                if (*v12 == *v11)
//                {
//                    auto v13 = v10 - 1;
//                    auto v14 = v11 + 1;
//                    auto v15 = v12 + 1;
//                    if (!v13)
//                    {
//                        goto LABEL_18;
//                    }
//                    v9 = *v15 - *v14;
//                    if (*v15 == *v14)
//                    {
//                        auto v16 = v14 + 1;
//                        auto v17 = v15 + 1;
//                        if (v13 == 1)
//                        {
//                            goto LABEL_18;
//                        }
//                        auto v18 = *v16;
//                        v9 = *v17 - v18;
//                        if (*v17 == v18)
//                        {
//                            v19 = 0;
//                            break;
//                        }
//                    }
//                }
//            }
//            v19 = 1;
//            if (v9 <= 0)
//            {
//                v19 = -1;
//            }
//            LABEL_19:
//            if (v19 == 0)
//            {
//                break;
//            }
//        }
//    }

    return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
void Array<T>::ShiftElementsDown(uint index, uint count)
{
    if (count != 0)
    {
        auto i = index;
        if (index < m_Count && index >= count)
        {
            auto v7 = m_Count - index;
            if (v7 > count)
            {
                if (v7)
                {
                    while (true)
                    {
                        auto v8 = count < v7 ? count : v7;
                        MoveElements(&m_pData[i], &m_pData[i - count], v8);
                        i += v8;
                        v7 -= v8;
                        if (v7 == 0)
                        {
                            break;
                        }
                    }
                }
            }
            else
            {
                MoveElements(&m_pData[index], &m_pData[index - count], v7);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
void Array<T>::RemoveAt(uint index)
{
    if (index < m_Count)
    {
        if (RemoveElements(&m_pData[index], 1), index < m_Count - 1)
        {
            ShiftElementsDown(index + 1, 1);
        }
        m_Count--;
    }
}

template<typename T>
bool Array<T>::Remove(T const& item)
{
    auto index = Find(item);
    if (index != -1)
    {
        RemoveAt(index);

        return true;
    }

    return false;
}

template<typename T>
void Array<T>::RemoveLast()
{
    if (m_Count != 0)
    {
        RemoveAt(m_Count - 1);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
void Array<T>::ResizeArray(uint newSize)
{
    if (newSize != m_Allocated)
    {
        if (newSize != 0)
        {
            auto pNewData = CreateArray(newSize);
            auto pOldData = m_pData;

            if (m_pData != nullptr)
            {
                if (m_Count != 0)
                {
                    MoveElements(pOldData, pNewData, m_Count < newSize ? m_Count : newSize);
                    if (m_Count > newSize)
                    {
                        RemoveElements(&m_pData[newSize], m_Count - newSize);
                        m_Count = newSize;
                    }
                }
                DisposeArray(m_pData, 0, m_Allocated);
            }
            m_pData = pNewData;
            m_Allocated = newSize;
        }
        else
        {
            DisposeArray(m_pData, m_Count, m_Allocated);
            m_pData = 0;
            m_Count = 0;
            m_Allocated = 0;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
T* Array<T>::AppendNew()
{
#if 1
    if (m_Count + 1 > m_Allocated)
    {
        auto margin = m_Count - m_Allocated;
        if (margin + 1 != 0)
        {
            auto v5 = m_GrowBy == 0 ? 1 : m_GrowBy;
            ResizeArray(m_Allocated + v5 + margin - (v5 + margin) % v5);
        }
    }
    return &m_pData[++m_Count - 1];
#else
    if (CheckForGrowth(1))
    {
        CreateEmptyElements(&m_pData[m_Count++], 1);
    }

    return &m_pData[m_Count];
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
void Array<T>::SwapElements(uint index1, uint index2)
{
    if (index1 < m_Count && index2 < m_Count && index1 != index2)
    {
        EnsureCapacity(m_Count + 1);
        MoveElements(&m_pData[index1], &m_pData[m_Count], 1);
        MoveElements(&m_pData[index2], &m_pData[index1], 1);
        MoveElements(&m_pData[m_Count], &m_pData[index2], 1);
    }
}

} // namespace Ensemble
