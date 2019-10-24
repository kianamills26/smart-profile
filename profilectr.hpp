#include <eosio/eosio.hpp>
#include <eosio/print.hpp>
#include <ctime>
#include <vector>

using namespace eosio;

// Constants
const uint64_t MAX_IPFS_SIZE = 46;
const uint64_t MIN_IPFS_SIZE = 46;
const uint64_t MAX_LANG_CODE_SIZE = 7;
const uint64_t MIN_LANG_CODE_SIZE = 2;
const uint64_t MAX_PLATFORM_SIZE = 20;
const uint64_t MIN_PLATFORM_SIZE = 4;
const uint64_t MAX_COUNTRY_SIZE = 4;
const uint64_t MIN_COUNTRY_SIZE = 1;
const uint64_t MAX_DISPLAY_NAME_SIZE = 30;
const uint64_t MIN_DISPLAY_NAME_SIZE = 2;

typedef struct address{
    std::string city;
    std::string state;
    std::string country;
} addresst;

typedef struct language{
    std::string lang_code;
    int level; // 0-3
} languaget;

typedef struct platform{
    std::string platform;
    std::string url;
} platformt;

class [[eosio::contract("profile")]] profile: public eosio::contract {
public:
    
    using ipfshash_t = std::string;
    
    profile( name receiver, name code, datastream<const char*> ds ) : contract(receiver, code, ds) {}
    
    // ABI FUNCTIONS
    [[eosio::action]]
    void insert(name user,
                std::string display_name,
                ipfshash_t about_me,
                addresst location,
                ipfshash_t img,
                std::vector<languaget> languages,
                std::vector<platformt> platforms);
    
    [[eosio::action]]
    void erase(name user);

    [[eosio::action]]
    void notify(name user, std::string msg) {
        require_auth(get_self());
        require_recipient(user);
    }
    
private:
    // DATABASE SCHEMAS
    struct [[eosio::table]] user {
        name key;
        std::string display_name;
        ipfshash_t ipfs_about_me; //IPFS hash of About Me
        addresst location; // Struct of location
        ipfshash_t ipfs_img;  //IPFS hash of profile image
        std::vector<languaget> languages; // Struct of languages and level pairs
        std::vector<platformt> platforms; // Struct of platform and url pairs
        
        uint64_t primary_key() const { return key.value; }
        std::string get_name() const { return display_name; }
    };
  
    typedef eosio::multi_index<"profiletbl"_n, user > profile_index;
    
    void send_summary(name user, std::string message) {
        action(
               permission_level{get_self(), "active"_n },
               get_self(),
               "notify"_n,
               std::make_tuple(user, name{user}.to_string() + message )
               ).send();
    }
    
    
};

