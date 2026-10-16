#include "MyImplUnionFind.h"
#include <memory>
#include <vector>

struct CMyImplUnionFind::SImplementation{
    struct SNode{
        std::shared_ptr<SNode> DParent;
        TElementID DID;
    };

    std::vector<std::shared_ptr<SNode> > DElements;


    std::size_t Size() const{
        return DElements.size();
    }

    std::size_t GroupCount() const{
        std::size_t Count = 0;
        for(auto Element : DElements){
            if(!Element->DParent){
                Count++;
            }
        }
        return Count;
    }

    TElementID AddElement(){
        TElementID NewElementID = DElements.size();
        DElements.push_back(std::make_shared<SNode>());
        DElements.back()->DID = NewElementID;
        return NewElementID;
    }

    bool Union(TElementID a, TElementID b){
        
    }
    TGroupID Find(TElementID a) const{
        
    }

    bool Connected(TElementID a, TElementID b){
        
    }
};
CMyImplUnionFind::CMyImplUnionFind(){
    DImplementation = std::make_unique<SImplementation>();
}

CMyImplUnionFind::~CMyImplUnionFind(){

}

std::size_t CMyImplUnionFind::Size() const{
    return DImplementation->Size();
}

std::size_t CMyImplUnionFind::GroupCount() const{
    return DImplementation->GroupCount();
}

CUnionFind::TElementID CMyImplUnionFind::AddElement(){
    return DImplementation->AddElement();
}
bool CMyImplUnionFind::Union(TElementID a, TElementID b){
    return DImplementation->Union(a,b);
}

CUnionFind::TGroupID CMyImplUnionFind::Find(TElementID a) const{
    return DImplementation->Find(a);
}
bool CMyImplUnionFind::Connected(TElementID a, TElementID b){
    return DImplementation->Connected(a,b);
}

