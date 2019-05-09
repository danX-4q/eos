/**
 *  @file
 *  @copyright defined in eos/LICENSE
 */
#include <eosio/safechain_client_plugin/safechain_client_plugin.hpp>
#include <eosio/chain/exceptions.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <fstream>

namespace eosio {

   class safechain_client_plugin_impl {
      public:
        safechain_client_plugin_impl();
        ~safechain_client_plugin_impl();

      public:
        std::unique_ptr<http_client> rpc_client;
        string                       rpc_address;
        string                       rpc_user;
        string                       rpc_password;
   };

   safechain_client_plugin_impl::safechain_client_plugin_impl():
      rpc_client( new http_client() ) {
   }
   safechain_client_plugin_impl::~safechain_client_plugin_impl(){}

   ////////////////////////////////////////////////////////

   static safechain_client_plugin_impl *my_impl;

   ////////////////////////////////////////////////////////

   safechain_client_plugin::safechain_client_plugin():
      my( new safechain_client_plugin_impl ) {
      my_impl = my.get();
   }
   safechain_client_plugin::~safechain_client_plugin(){}

   void safechain_client_plugin::set_program_options(options_description&, options_description& cfg) {
      cfg.add_options()
         ("safed-rpc-server-address", bpo::value<string>()->default_value( "http://127.0.0.1:4465" ), "The public endpoint of a safed node to connect to.")
         ("safed-rpc-user", bpo::value<string>()->default_value( "rpcuser" ), ".")
         ("safed-rpc-password", bpo::value<string>()->default_value( "rpcpass" ), ".")
         ;
   }

   void safechain_client_plugin::plugin_initialize(const variables_map& options) {
      chain_plugin* chain_plug = app().find_plugin<chain_plugin>();
      chain::controller& chain = chain_plug->chain();
      chain.set_safechain_client(this);
      try {
         my->rpc_address = options.at( "safed-rpc-server-address" ).as<string>();
         my->rpc_user = options.at( "safed-rpc-user" ).as<string>();
         my->rpc_password = options.at( "safed-rpc-password" ).as<string>();
         idump((my->rpc_address)(my->rpc_user)(my->rpc_password));
         
      } FC_LOG_AND_RETHROW()
   }

   void safechain_client_plugin::plugin_startup() {

   }

   void safechain_client_plugin::plugin_shutdown() {

   }

}
