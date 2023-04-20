// pragma solidity ^0.8.0;

// contract StringStore {
//     address owner;
//     string storedString;
    
//     constructor() {
//         owner = msg.sender;
//     }
    
//     function getString() public view returns (string memory) {
//         return storedString;
//     }
    
//     function setString(string memory newString) public {
//         require(msg.sender == owner, "Only the owner can set the string");
//         storedString = newString;
//     }
// }



#include <eosio/eosio.hpp>

using namespace eosio;

class [[eosio::contract("stringstore")]] stringstore : public contract {
  public:
    stringstore(name receiver, name code,  datastream<const char*> ds) :
        contract(receiver, code, ds),
        stored_string(receiver, receiver.value) {
        }

    [[eosio::action]] 
    void getstring() {
        auto itr = stored_string.find(get_self().value);
        check(itr != stored_string.end(), "String not found");
        print(itr->value);
        
    }
    
    [[eosio::action]]
    void setstring(std::string newString) {
        require_auth(get_self());
        auto itr = stored_string.find(get_self().value);
        if (itr == stored_string.end()) {
            stored_string.emplace(get_self(), [&](auto& s) {
                s.owner = get_self();
                s.value = newString;
            });
        } else {
            stored_string.modify(itr, get_self(), [&](auto& s) {
                s.value = newString;
            });
        }
    }
  private:
    // uint8_t myamount;
    struct [[eosio::table]] string_data {
        name owner;
        std::string value;

        uint64_t primary_key() const { return owner.value; }
    };

    typedef eosio::multi_index<"strings"_n, string_data> string_table;

    string_table stored_string;
};


