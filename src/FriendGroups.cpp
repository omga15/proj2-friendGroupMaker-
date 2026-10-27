#include "FriendGroups.h"
#include "MyImplUnionFind.h"
#include "BinaryTreeMap.h"
#include <iostream>


struct CFriendGroups::SImplementation{
    // Your Implementation here
    CMyImplUnionFind DUnionFind;
    CBinaryTreeMap<TName,CUnionFind::TElementID> DNameToID;

    CUnionFind::TElementID GetElementID(const TName &name, bool create = false){
        CUnionFind::TElementID ElementID = CUnionFind::InvalidGroupID;
        if(!DNameToID.Find(name,ElementID) && create){
            ElementID = DUnionFind.AddElement();
            DNameToID.Add(name,ElementID);
        }
        return ElementID;
    }

    bool SameFriendGroup(const TConnection &connection) noexcept{ // checks friend in tree if connected
        auto FirstName = std::get<0>(connection);
        auto SecondName = std::get<1>(connection);
        auto FirstElementID = GetElementID(FirstName);
        auto SecondElementID = GetElementID(SecondName);
        
        return DUnionFind.Connected(FirstElementID,SecondElementID);
    }

    void AddFriendship(const TConnection &friendship) noexcept{ //adds friend by searching the tuple
        auto FirstName = std::get<0>(friendship);
        auto SecondName = std::get<1>(friendship);
        auto FirstElementID = GetElementID(FirstName,true);
        auto SecondElementID = GetElementID(SecondName,true);
        DUnionFind.Union(FirstElementID,SecondElementID);
    }

    std::vector<TConnection> FriendshipsForSingleGroup() noexcept{
        std::vector<TConnection> groups;
        std::vector<bool> RootSeen(DUnionFind.Size(), false);// tracks prev roots
        bool HavePrev = false; 
        TName PrevName;
        // Need to have key(name) and value(id) 
        DNameToID.ForEach ([&](const TName &name, CUnionFind::TElementID id){
            auto root = DUnionFind.Find(id);
            if(RootSeen[root]){
                return; // there is a similar root
            }
            RootSeen[root] = true;
            
            if(HavePrev){  // checking to make sure there's a prev Name to make connection
                groups.push_back(TConnection(PrevName,name));
            }   
            PrevName = name;
            HavePrev = true;

        });
        return groups;
    }
};

CFriendGroups::CFriendGroups(){
    DImplementation = std::make_unique<SImplementation>();
}

CFriendGroups::~CFriendGroups(){
    
}

bool CFriendGroups::SameFriendGroup(const TConnection &connection) noexcept{
    return DImplementation->SameFriendGroup(connection);
}

void CFriendGroups::AddFriendship(const TConnection &friendship) noexcept{
    DImplementation->AddFriendship(friendship);
}

std::vector<CFriendGroups::TConnection> CFriendGroups::FriendshipsForSingleGroup() noexcept{
    return DImplementation->FriendshipsForSingleGroup();
}