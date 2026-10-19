#include "Map.h"
#include "BinaryTreeMap.h"
#include <memory>


template <typename T>
struct SMapFactory;

template<typename K, typename V>
struct SMapFactory<CBinaryTreeMap<K,V> > {
    static std::unique_ptr<CMap<K,V>> Create(){
        return std::make_unique<CBinaryTreeMap<K,V>>();
    }
};
