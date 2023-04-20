// // SPDX-License-Identifier: MIT
// pragma solidity ^0.8.0;

// contract UserInfo {
//     struct User {
//         string name;
//         string phoneNumber;
//     }
    
//     mapping(address => User) private users;

//     function setUserInfo(string memory _name, string memory _phoneNumber) public {
//         users[msg.sender].name = _name;
//         users[msg.sender].phoneNumber = _phoneNumber;
//     }
    
//     function getUserInfoByAddress(address _userAddress) public view returns (string memory, string memory) {
//         User storage user = users[_userAddress];
//         return (user.name, user.phoneNumber);
//     }
// }

#include <eosio/eosio.hpp>

using namespace eosio;

class [[eosio::contract]] userInfo : public contract {
    public:
        using contract::contract;

        struct [[eosio::table]] user {
            name account;
            std::string name;
            std::string phone_number;

            uint64_t primary_key() const { return account.value; }
        };

        typedef eosio::multi_index<"users"_n, user> users_table;

        [[eosio::action]]
        void setuser(name account, std::string name, std::string phone_number) {
            require_auth(account);

            users_table users(get_self(), get_self().value);
            auto iterator = users.find(account.value);
            if (iterator == users.end()) {
                users.emplace(account, [&](auto& row) {
                    row.account = account;
                    row.name = name;
                    row.phone_number = phone_number;
                });
            } else {
                users.modify(iterator, account, [&](auto& row) {
                    row.name = name;
                    row.phone_number = phone_number;
                });
            }
        }
            
        [[eosio::action]]
        std::tuple<std::string, std::string> getuser(name account) {
            users_table users(get_self(), get_self().value);
            auto iterator = users.find(account.value);
            check(iterator != users.end(), "User does not exist");

            return std::make_tuple(iterator->name, iterator->phone_number);
        }
};
