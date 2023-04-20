#include <eosio/eosio.hpp>
using namespace eosio;

//:: means to go inside that function like eosio.contract
//pulic mean what ever we are eriting inside this testingfirst can be accessible
// to anyone outside class testing
//contract is function of eosio that we are inheriting from above 
class [[eosio::contract("testingFirst")]] testingFirst :public contract{
    public:
        using contract::contract
        [[eosio::action]]
            void hello() {
            print("Hello, World!");
        }

        [[eosio::action]]
            void dataEnter(name yourName){
                print("hi", yourName);
        }
    p
}