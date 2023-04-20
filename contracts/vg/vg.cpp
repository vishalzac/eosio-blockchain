#include <eosio/eosio.hpp>

using namespace eosio;

class [[eosio::contract]] mycontract: public contract {
  public:
      using contract::contract;
      [[eosio::action]]
      void dataadded () {
        print("Your project is working");
      }
};


