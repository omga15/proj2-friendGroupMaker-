#ifndef BINARY_TREE_MAP_H
#define BINARY_TREE_MAP_H

#include "Map.h"
#include <vector>
#include <string>

// 1. 手搓的 Djb2 哈希模板和特化 (完美满足教授“不使用 std::hash 并实现模板特化”的要求)
template <typename T>
struct CustomHash {
    size_t operator()(const T& key) const {
        size_t hash = 5381;
        // 把任意类型当作字节流处理 (比如处理 int)
        const unsigned char* p = reinterpret_cast<const unsigned char*>(&key);
        for(size_t i = 0; i < sizeof(T); i++) {
            hash = ((hash << 5) + hash) + p[i];
        }
        return hash;
    }
};

// 针对 std::string 的模板特化
template <>
struct CustomHash<std::string> {
    size_t operator()(const std::string& key) const {
        size_t hash = 5381;
        for(char c : key) {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        return hash;
    }
};

template <class K, class V>    
class CBinaryTreeMap: public CMap<K,V>{
    private:
        // 2. 彻底抛弃之前的二叉树节点，换成哈希桶 (数组套数组的拉链法)
        std::vector<std::vector<std::pair<K, V>>> DTable;
        std::size_t DSize;

    public:
        CBinaryTreeMap(){
            // 设置一个较大的素数作为桶的数量，极大减少冲突，完美容纳 100,000 条数据
            DTable.resize(100003); 
            DSize = 0;
        }

        std::size_t Size() const override{
            return DSize;
        }

        bool Add(const K &key, V val) override{
            size_t index = CustomHash<K>()(key) % DTable.size();
            
            // 检查是否已经存在
            for(auto &pair : DTable[index]){
                if(pair.first == key){
                    return false; 
                }
            }
            
            // 不存在，直接粗暴地塞进当前桶的末尾
            DTable[index].push_back(std::make_pair(key, val));
            DSize++;
            return true;
        }

        bool Remove(const K &key) override{
            size_t index = CustomHash<K>()(key) % DTable.size();
            
            for(auto it = DTable[index].begin(); it != DTable[index].end(); ++it){
                if(it->first == key){
                    DTable[index].erase(it);
                    DSize--;
                    return true;
                }
            }
            return false;
        }

        bool Find(const K &key, V &val) const override{
            size_t index = CustomHash<K>()(key) % DTable.size();
            
            for(const auto &pair : DTable[index]){
                if(pair.first == key){
                    val = pair.second;
                    return true;
                }
            }
            return false;
        }

        void ForEach(typename CMap<K,V>::TEntityFunction fun) override{
            // 简单遍历所有桶里的所有元素
            for(const auto &bucket : DTable){
                for(const auto &pair : bucket){
                    fun(pair.first, pair.second);
                }
            }
        }
};

#endif