#include "profilectr.hpp"

using namespace eosio;

[[eosio::action]]
void profilectr::userinsert(name user, std::string display_name, std::string about_me, address_t location, std::string img, std::vector<language_t> languages, std::vector<platform_t> platforms) {
    
    require_auth( user );

    // Argument Checks
    eosio::check( display_name.size() <= MAX_DISPLAY_NAME_SIZE, "display name is too long. MAX_DISPLAY_NAME_SIZE= 30");
    eosio::check( display_name.size() >= MIN_DISPLAY_NAME_SIZE, "display name must be at least 2 characters");
    eosio::check( about_me.size() <= MAX_ABOUTME_SIZE, "'about me' is too long. MAX_IPFS_SIZE=46");
    eosio::check( img.size() <= MAX_IMG_SIZE, "Image is too large. MAX_IMG_SIZE = 400 characters");
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





