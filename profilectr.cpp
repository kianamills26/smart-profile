#include "profile.hpp"

using namespace eosio;

[[eosio::action]]
void profile::insert(name user, std::string display_name, ipfshash_t about_me, addresst location, ipfshash_t img, std::vector<languaget> languages, std::vector<platformt> platforms) {
    
    require_auth( user );

    // Check User already exists
    profile_index profiletbl(get_self(), _self.value);
    auto iterator = profiletbl.find(user.value);
    eosio::check(iterator == profiletbl.end(), "User already exists"); // Do we want to check for this ????

    // Argument Checks
    eosio::check( display_name.size() <= MAX_DISPLAY_NAME_SIZE, "display name is too long. MAX_DISPLAY_NAME_SIZE= 30");
    eosio::check( display_name.size() >= MIN_DISPLAY_NAME_SIZE, "display name must be at least 2 characters");
    eosio::check( about_me.size() <= MAX_IPFS_SIZE, "IPFS hash is too long. MAX_IPFS_SIZE=46");
    eosio::check( about_me.size() >= MIN_IPFS_SIZE, "IPFS hash is too short. MIN_IPFS_SIZE=46");
    eosio::check( img.size() <= MAX_IPFS_SIZE, "IPFS hash is too long. MAX_IPFS_SIZE=46");
    eosio::check( img.size() >= MIN_IPFS_SIZE, "IPFS hash is too short. MIN_IPFS_SIZE=46");
    eosio::check( location.country.size() <= MAX_COUNTRY_SIZE, "country code max size is 4 characters");
    eosio::check( location.country.size() >= MIN_COUNTRY_SIZE, "country code must be at least 1 character");
    // Check language codes
    for(int i=0; i<languages.size(); ++i) {
        eosio::check( languages[i].lang_code.size() <= MAX_LANG_CODE_SIZE, "lang code max size is 8 bytes");
        eosio::check( languages[i].lang_code.size() >= MIN_LANG_CODE_SIZE, "lang code must be at least 2 characters");
        eosio::check( languages[i].level >=0 && languages[i].level <= 3, "language level must be between 0 and 3");
    }
    // Check platforms
    for(int i=0; i<platforms.size(); ++i) {
        eosio::check( platforms[i].platform.size() <= MAX_PLATFORM_SIZE, "platform max size is 20 characters");
        eosio::check( platforms[i].platform.size() >= MIN_PLATFORM_SIZE, "platform size must be at least 4 characters");
    }
    
}



[[eosio::action]]
void profile::erase(name user) {
    require_auth(user);
    
    profile_index profiles( get_self(), _self.value);
    
    auto iterator = profiles.find(user.value);
    eosio::check(iterator != profiles.end(), "Record does not exist");
    // profiles.erase(iterator);
    // send_summary(user, " successfully erased record from profiles");
}




