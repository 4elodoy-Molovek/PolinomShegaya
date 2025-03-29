#include "LinearListTable.h"
#include <stdexcept>

template<typename K, typename T>
LinearListTable<K, T>::LinearListTable(size_t sz) {}

template<typename K, typename T>
LinearListTable<K, T>::~LinearListTable() {}

template<typename K, typename T>
void LinearListTable<K, T>::addElement(const K& key, const T& pol)
{
    ListTableString<K, T> newNode{ key, pol };
    data.insertLast(newNode);
}

template<typename K, typename T>
void LinearListTable<K, T>::deleteElement(const K& key)
{
    for (size_t i = 0; i < data.size(); ++i)
    {
        if (data[i].key == key)
        {
            data.remove(i);
            return;
        }
    }
}

template<typename K, typename T>
T& LinearListTable<K, T>::findElement(const K& key)
{
    for (size_t i = 0; i < data.size(); ++i)
    {
        if (data[i].key == key)
        {
            return data[i].value;
        }
    }
    throw std::runtime_error("Element not found");
}
