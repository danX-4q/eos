/**
 *  @file
 *  @copyright defined in eos/LICENSE
 */
#include <eosio/safechain_client_plugin/safechain_client_plugin.hpp>
#include <eosio/chain/safechain_client.hpp>
#include <eosio/chain/exceptions.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <fstream>

namespace eosio {
   static appbase::abstract_plugin& _plugin = app().register_plugin<safechain_client_plugin>();

   class safechain_client_plugin_impl {
      public:
        safechain_client_plugin_impl();
        ~safechain_client_plugin_impl();

      public:
         eosio::chain::safechain_client::config       conf;
   };

   safechain_client_plugin_impl::safechain_client_plugin_impl(){}
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
         ("safechain-mock-static-success", bpo::value<bool>()->default_value( false ), ".")
         ("safechain-mock-static-failed", bpo::value<bool>()->default_value( false ), ".")
         ("safechain-mock-dynamic-failed", bpo::value<bool>()->default_value( false ), ".")
         ("safechain-mock-before-dynamic-failed-retry", bpo::value<uint32_t>()->default_value( 3 ), ".");
   }

   void safechain_client_plugin::plugin_initialize(const variables_map& options) {
      try {
         my->conf.rpc_address = options.at( "safed-rpc-server-address" ).as<string>();
         my->conf.rpc_user = options.at( "safed-rpc-user" ).as<string>();
         my->conf.rpc_password = options.at( "safed-rpc-password" ).as<string>();
         ilog("safed rpc: address=${a}, user=${u}, password=${p}",
               ("a",my->conf.rpc_address)("u",my->conf.rpc_user)("p",my->conf.rpc_password));
         
         my->conf.mock_static_success = options.at( "safechain-mock-static-success" ).as<bool>();
         my->conf.mock_static_failed = options.at( "safechain-mock-static-failed" ).as<bool>();
         my->conf.mock_dynamic_failed = options.at( "safechain-mock-dynamic-failed" ).as<bool>();
         my->conf.mock_before_dynamic_failed_retry = options.at( "safechain-mock-before-dynamic-failed-retry" ).as<uint32_t>();
         ilog("safechain mock info: mock_static_success=${mss}, mock_static_failed=${msf}, mock_dynamic_failed=${mdf}, mock_before_dynamic_failed_retry=${mbdfr}",
               ("mss", my->conf.mock_static_success) ("msf", my->conf.mock_static_failed)
               ("mdf", my->conf.mock_dynamic_failed) ("mbdfr", my->conf.mock_before_dynamic_failed_retry)
               );
         
         chain_plugin* chain_plug = app().find_plugin<chain_plugin>();
         chain::controller& chain = chain_plug->chain();
         chain.safechain_client_instance()->set_config(my->conf);

      } FC_LOG_AND_RETHROW()
   }

   void safechain_client_plugin::plugin_startup() {

   }

   void safechain_client_plugin::plugin_shutdown() {

   }
}
