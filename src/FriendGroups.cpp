#include "FriendGroups.h"

struct CFriendGroups::SImplementation{
    // Your Implementation here
};

CFriendGroups::CFriendGroups(){
    DImplementation = std::make_unique<SImplementation>();
}

CFriendGroups::~CFriendGroups(){
    
}

bool CFriendGroups::SameFriendGroup(const TConnection &connection) noexcept{

}

void CFriendGroups::AddFriendship(const TConnection &friendship) noexcept{

}

std::vector<CFriendGroups::TConnection> CFriendGroups::FriendshipsForSingleGroup() noexcept{

}