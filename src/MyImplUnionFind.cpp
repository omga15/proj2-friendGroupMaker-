#include "MyImplUnionFind.h"
#include <memory>
#include <vector>

struct CMyImplUnionFind::SImplementation{
    
    mutable std::vector<TElementID> DParent;
    std::vector<std::size_t> DGroup;       // size of the group
    std::size_t Dcount;

    bool IsValidElementID(TElementID element) const{
        return element < DParent.size();
    }

    std::size_t Size() const{
        return DParent.size();
    }

    std::size_t GroupCount() const{
        return Dcount;
    }

    TElementID AddElement(){
        TElementID NewElementID = DParent.size();
        DParent.push_back(NewElementID);
        DGroup.push_back(1);
        Dcount++;
        return NewElementID;
    }

    bool Union(TElementID a, TElementID b){
        if(!IsValidElementID(a) || !IsValidElementID(b)){
            return false;
        }
        auto AGroup = Find(a);
        auto BGroup = Find(b);
        if(AGroup==BGroup){
            return false;
        }

        if(DGroup[AGroup] < DGroup[BGroup]){
            std::swap(AGroup,BGroup);
        } 
        DParent[BGroup] = AGroup;
        DGroup[AGroup] += DGroup[BGroup];
        --Dcount;
        return true;   
    }
    
    TGroupID Find(TElementID a) const{
        if(!IsValidElementID(a)){
            return InvalidGroupID;
        }
        TElementID root = a;
        while(root != DParent[root]){
            root = DParent[root];
        }
        while(a != root){
            TElementID next = DParent[a];
            DParent[a] = root;
            a = next;
        }
        return root;
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

