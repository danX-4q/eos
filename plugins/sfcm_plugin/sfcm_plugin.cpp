/**
 *  @file
 *  @copyright defined in eos/LICENSE
 */
#include <eosio/sfcm_plugin/sfcm_plugin.hpp>
#include <eosio/chain/exceptions.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <fstream>
#include <fc/network/http/http_client.hpp>
#include <boost/asio/steady_timer.hpp>

namespace eosio {
   using fc::http_client;

   static appbase::abstract_plugin& _plugin = app().register_plugin<sfcm_plugin>();

   class sfcm_plugin_impl {
      public:
         sfcm_plugin_impl();
         ~sfcm_plugin_impl();

         void ticker();

      public:
         std::unique_ptr<http_client>  rpc_client;

         string                        rpc_url;
         string                        rpc_user;
         string                        rpc_password;

         unique_ptr<boost::asio::steady_timer>  monitor_timer;
         boost::asio::steady_timer::duration    keepalive_interval{std::chrono::seconds{20}};
   };

   sfcm_plugin_impl::sfcm_plugin_impl():
   rpc_client( new http_client() ) {
   }
   sfcm_plugin_impl::~sfcm_plugin_impl(){}

   void sfcm_plugin_impl::ticker() {
      monitor_timer->expires_from_now(keepalive_interval);
      monitor_timer->async_wait([this](boost::system::error_code ec) {
            ticker();
            if (ec) {
               wlog("Peer keepalive ticked sooner than expected: ${m}", ("m", ec.message()));
            }
            dlog("ha ha.");
         });
   }

   ////////////////////////////////////////////////////////

   static sfcm_plugin_impl *my_impl;

   ////////////////////////////////////////////////////////

   sfcm_plugin::sfcm_plugin():
      my( new sfcm_plugin_impl ) {
      my_impl = my.get();
   }
   sfcm_plugin::~sfcm_plugin(){}

   void sfcm_plugin::set_program_options(options_description&, options_description& cfg) {
      cfg.add_options()
         ("sfcm-rpc-url", bpo::value<string>()->default_value( "http://127.0.0.1:4465" ), "The public endpoint of a safed node to connect to.")
         ("sfcm-rpc-user", bpo::value<string>()->default_value( "rpcuser" ), ".")
         ("sfcm-rpc-password", bpo::value<string>()->default_value( "rpcpass" ), ".")
         ;
   }

   void sfcm_plugin::plugin_initialize(const variables_map& options) {
      try {
         my->rpc_url = options.at( "sfcm-rpc-url" ).as<string>();
         my->rpc_user = options.at( "sfcm-rpc-user" ).as<string>();
         my->rpc_password = options.at( "sfcm-rpc-password" ).as<string>();
         ilog("safed rpc: url=${a}, user=${u}, password=${p}",
               ("a",my->rpc_url)("u",my->rpc_user)("p",my->rpc_password));

         my->monitor_timer.reset( new boost::asio::steady_timer( app().get_io_service()));
         my->ticker();

      } FC_LOG_AND_RETHROW()
   }

   void sfcm_plugin::plugin_startup() {

   }

   void sfcm_plugin::plugin_shutdown() {

   }
}
