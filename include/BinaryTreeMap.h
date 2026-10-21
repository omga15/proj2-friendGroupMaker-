#ifndef BINARY_TREE_MAP_H
#define BINARY_TREE_MAP_H

#include "Map.h"
#include <memory>

template <class K, class V>    
class CBinaryTreeMap: public CMap<K,V>{
    private:
        struct SNode{
            K DKey;
            V DValue;
            std::shared_ptr<SNode> DLeft;
            std::shared_ptr<SNode> DRight;

            SNode(const K &key, V val){
                DKey = key;
                DValue = val;
            }

            bool Add(const K &key, V val){
                if(key == DKey){
                    return false;
                }
                if(key < DKey){
                    if(DLeft){
                        return DLeft->Add(key,val);
                    }
                    DLeft = std::make_shared<SNode>(key,val);
                    return true;
                }
                if(DRight){
                    return DRight->Add(key,val);
                }
                DRight = std::make_shared<SNode>(key,val);
                return true;
            }

            bool Find(const K &key, V &val) const{
                if(key == DKey){
                    val = DValue;
                    return true;
                }
                if(key < DKey){
                    if(DLeft){
                        return DLeft->Find(key,val);
                    }
                    return false;
                }
                if(DRight){
                    return DRight->Find(key,val);
                }
                return false;
            }
            // Need more work
            void GetMax(K &maxKey, V &maxVal){
                if(DRight){
                    DRight->GetMax(maxKey,maxVal);
                } else {
                    maxKey = DKey;
                    maxVal = DValue;
                }
            }

            void GetMin(K &minKey, V &minVal) {
                if (DLeft) {
                    DLeft->GetMin(minKey, minVal);
                } else {
                    minKey = DKey;
                    minVal = DValue;
                }
            }
            bool Remove(const K &key, bool &removeme){
                if(key == DKey){
                    if(DLeft){
                        // Get the right most value of left subtree and remove
                        K RMKey;
                        V RMValue;
                        DLeft-> GetMax(RMKey,RMValue);
                        DKey = RMKey;
                        DValue = RMValue;

                        if (DLeft->Remove(RMKey, removeme)) {
                            if (removeme) {
                                DLeft.reset();
                            }
                            removeme = false;
                        }
                    }
                    else if(DRight){
                        // Get the left most value of right subtree and remove
                        K LMKey;
                        V LMValue;
                        DRight-> GetMin(LMKey,LMValue);
                        DKey = LMKey;
                        DValue = LMValue;
                        if (DRight->Remove(LMKey, removeme)) {
                            if (removeme) {
                                DRight.reset();
                            }
                            removeme = false;
                        }
                    }
                    else{
                        // remove this node
                        removeme = true;
                    }
                    return true;
                }
                if(key < DKey){
                    if(DLeft){
                        if(DLeft->Remove(key,removeme)){
                            if(removeme){
                                DLeft.reset();
                            }
                            removeme = false;
                            return true;
                        }
                    }
                    return false;
                }
                if(DRight){
                    if(DRight->Remove(key,removeme)){
                        if(removeme){
                            DRight.reset();
                        }
                        removeme = false;
                        return true;
                    }
                }
                return false;
            }
        };
        std::shared_ptr<SNode> DRoot;
        std::size_t DSize;
    public:
        CBinaryTreeMap(){
            DSize = 0;
        }

        std::size_t Size() const override{
            return DSize;
        }

        bool Add(const K &key, V val) override{
            if(DRoot){
                if(!DRoot->Add(key,val)){
                    return false;
                }
            }
            else{
                DRoot = std::make_shared<SNode>(key,val);
            }
            DSize++;
            return true;
        }

        bool Remove(const K &key) override{
            if(DRoot){
                bool RemoveRoot = false;
                if(DRoot->Remove(key,RemoveRoot)){
                    if(RemoveRoot){
                        DRoot.reset();
                    }
                    DSize--;
                    return true;
                }
            }
            return false;
        }

        bool Find(const K &key, V &val) const override{
            if(DRoot){
                return DRoot->Find(key,val);
            }
            return false;
        }

        void ForEach(CMap<K,V>::TEntityFunction fun) override{
            // do soemthing with the friends that someone made
            K key;
            V value;
        }
};

#endif