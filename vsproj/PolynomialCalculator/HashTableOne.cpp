#include "HashTableOne.h"
#include <stdexcept>
#include <functional>

template<typename K, typename T>
HashTableOne<K, T>::HashTableOne(size_t sz) : size(0), bufferSize(sz), sizeAllNonNullptr(0)
{
    table.resize(bufferSize);
}

template<typename K, typename T>
HashTableOne<K, T>::~HashTableOne() {}

template<typename K, typename T>
void HashTableOne<K, T>::addElement(const K& key, const T& pol)
{
    size_t index = hashFunction(key);
    for (auto& pair : table[index])
    {
        if (pair.first == key)
        {
            pair.second.data = pol;
            pair.second.deleted = false;
            return;
        }
    }
    table[index].emplace_back(key, Node{ pol, false });
    ++size;
    ++sizeAllNonNullptr;
}

template<typename K, typename T>
void HashTableOne<K, T>::deleteElement(const K& key)
{
    size_t index = hashFunction(key);
    for (auto& pair : table[index])
    {
        if (pair.first == key && !pair.second.deleted)
        {
            pair.second.deleted = true;
            --size;
            return;
        }
    }
}

template<typename K, typename T>
T& HashTableOne<K, T>::findElement(const K& key)
{
    size_t index = hashFunction(key);
    for (auto& pair : table[index])
    {
        if (pair.first == key && !pair.second.deleted)
        {
            return pair.second.data;
        }
    }
    throw std::runtime_error("Element not found");
}

template<typename K, typename T>
size_t HashTableOne<K, T>::hashFunction(const K& key) const
{
    return std::hash<K>{}(key) % bufferSize;
}