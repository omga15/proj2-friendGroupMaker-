#ifndef BINARY_TREE_MAP_H
#define BINARY_TREE_MAP_H

#include "Map.h"
#include <memory>

template <class K, class V>    
class CBinaryTreeMap: public CMap<K,V>{
    private:
        struct SNode: public std::enable_shared_from_this<SNode>{
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

            std::shared_ptr<SNode> RemoveRightMost(K &key, V &val){
                if(DRight){
                    DRight = DRight->RemoveRightMost(key, val);
                    return this->shared_from_this();
                }
                else{
                    key = DKey;
                    val = DValue;
                    return DLeft;
                }
            }

            std::shared_ptr<SNode> RemoveLeftMost(K &key, V &val){
                if(DLeft){
                    DLeft = DLeft->RemoveLeftMost(key,val);
                    return this->shared_from_this();
                }
                else{
                    key = DKey;
                    val = DValue;
                    return DRight;
                }
            }


            bool Remove(const K &key, bool &removeme){
                if(key == DKey){
                    if(DLeft){
                        // Get the right most value of left subtree and remove
                        DLeft = DLeft->RemoveRightMost(DKey,DValue);
                    }
                    else if(DRight){
                        // Get the left most value of right subtree and remove
                        DRight = DRight->RemoveLeftMost(DKey,DValue);
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

            void ForEach(CMap<K,V>::TEntityFunction fun){ // function that goes through binary tree
                if(DLeft){
                    DLeft->ForEach(fun);
                }
                fun(DKey,DValue);
                if(DRight){
                    DRight->ForEach(fun);
                }
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
            if(DRoot){
                DRoot->ForEach(fun);
            }
        }
};

#endif