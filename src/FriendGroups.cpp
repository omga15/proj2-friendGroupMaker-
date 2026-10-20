#include "FriendGroups.h"

struct CFriendGroups::SImplementation{
    // Your Implementation here
    bool SameFriendGroup(const TConnection &connection){
        return false;
    }
    void AddFriendship(const TConnection &friendship){

    }
    std::vector<CFriendGroups::TConnection> FriendshipsForSingleGroup(){

    }
};

CFriendGroups::CFriendGroups(){
    DImplementation = std::make_unique<SImplementation>();
}

CFriendGroups::~CFriendGroups(){
    
}

bool CFriendGroups::SameFriendGroup(const TConnection &connection) noexcept{
    DImplementation->SameFriendGroup(connection);
}

void CFriendGroups::AddFriendship(const TConnection &friendship) noexcept{
    DImplementation->AddFriendship(friendship);
}

std::vector<CFriendGroups::TConnection> CFriendGroups::FriendshipsForSingleGroup() noexcept{
    DImplementation->FriendshipsForSingleGroup();
}