
#include <eosio/chain/safechain_client.hpp>
#include <fc/network/http/http_client.hpp>
#include <fc/io/json.hpp>
//#include <fc/scoped_exit.hpp>
//#include <fc/variant_object.hpp>

namespace eosio { namespace chain {
   using fc::http_client;

   struct safechain_client_impl {
      safechain_client::config            conf;
      std::unique_ptr<http_client>    rpc_client;

      safechain_client_impl()
      :rpc_client( new http_client() )
      {
      }
      ~safechain_client_impl(){}
   };

   safechain_client::safechain_client()
   :my(new safechain_client_impl)
   {
   }

   safechain_client::~safechain_client()
   {
   }

   void safechain_client::set_config( const safechain_client::config& cfg ) {
      my->conf = cfg;
   }

   int safechain_client::get_txid_confirmations(const string txid, uint64_t& cfrms) {
      cfrms = 334455;
      if ( my->conf.mock_static_success ) {
         ilog( "mss return 0" );
         return ( 0 );
      }
      if ( my->conf.mock_static_failed ) {
         ilog( "msf return 1" );
         return ( 1 );
      }
      if ( my->conf.mock_dynamic_failed ) {
         if ( my->conf.mock_before_dynamic_failed_retry == 0 ) {
            ilog( "mbdf return 2" );
            return ( 2 );
         }
         
         static uint32_t count = 0;
         ++count;
         if ( count == my->conf.mock_before_dynamic_failed_retry ) {
            count = 0;
            ilog( "mbdf return 3" );
            return ( 3 );
         } else {
            ilog( "mbdfr return 0" );
            return ( 0 );
         }
      }
      
      return ( 0 );
   }

} } /// eosio::chain
