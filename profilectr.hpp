#include <eosio/eosio.hpp>
#include <eosio/print.hpp>
#include <ctime>
#include <vector>

using namespace eosio;

// Constants
const uint64_t MAX_IMG_SIZE = 400;
const uint64_t MAX_ABOUTME_SIZE = 300;
const uint64_t MIN_ABOUTME_SIZE = 3;
const uint64_t MAX_LANG_CODE_SIZE = 7;
const uint64_t MIN_LANG_CODE_SIZE = 2;
const uint64_t MAX_PLATFORM_SIZE = 20;
const uint64_t MIN_PLATFORM_SIZE = 4;
const uint64_t MAX_COUNTRY_SIZE = 4;
const uint64_t MIN_COUNTRY_SIZE = 1;
const uint64_t MAX_DISPLAY_NAME_SIZE = 30;
const uint64_t MIN_DISPLAY_NAME_SIZE = 3;

typedef struct address{
    std::string city;
    std::string state;
    std::string country;
} address_t;

typedef struct language{
    std::string lang_code;
    int level; // 0-3
} language_t;

typedef struct platform{
    std::string platform;
    std::string url;
} platform_t;

class [[eosio::contract("profilectr")]] profilectr: public eosio::contract {
public:
    
    profilectr( name receiver, name code, datastream<const char*> ds ) : contract(receiver, code, ds) {}
    
    // ABI FUNCTIONS
    [[eosio::action]]
    void userinsert(name user,
                std::string display_name,
                std::string about_me,
                address_t location,
                std::string img,
                std::vector<language_t> languages,
                std::vector<platform_t> platforms);
   
};

