#include "MyImplUnionFind.h"
#include <memory>
#include <vector>

struct CMyImplUnionFind::SImplementation{
    struct SNode{
        std::shared_ptr<SNode> DParent;
        TElementID DID;
    };

    std::vector<std::shared_ptr<SNode> > DElements;


    bool IsValidElementID(TElementID element) const{
        return element < DElements.size();
    }

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
        if(!IsValidElementID(a) || !IsValidElementID(b)){
            return false;
        }
        
        auto AGroup = Find(a);
        auto BGroup = Find(b);
        if(AGroup != BGroup){
            DElements[BGroup]->DParent = DElements[AGroup];
            return true;
        }
        return false;
        
    }
    
    TGroupID Find(TElementID a) const{
        if(!IsValidElementID(a)){
            return InvalidGroupID;
        }
        auto CurrentNode = DElements[a];
        while(CurrentNode->DParent){
            CurrentNode = CurrentNode->DParent;
        }
        return CurrentNode->DID;
    }

    bool Connected(TElementID a, TElementID b){
        auto AGroup = Find(a);
        auto BGroup = Find(b);
        return AGroup != InvalidGroupID && AGroup == BGroup;
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

