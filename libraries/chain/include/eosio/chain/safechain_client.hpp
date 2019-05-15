#pragma once
#include <eosio/chain/types.hpp>

namespace eosio { namespace chain {

   class safechain_client {
      public:

         struct config {
            string                       rpc_address;
            string                       rpc_user;
            string                       rpc_password;

            bool                         mock_static_success;
            bool                         mock_static_failed;
            bool                         mock_dynamic_failed;
            uint32_t                     mock_before_dynamic_failed_retry;           
         };

         safechain_client();
         ~safechain_client();
      
         void set_config( const safechain_client::config& cfg );
         int get_txid_confirmations(const string txid, uint64_t& cfrms);

      private:
         std::unique_ptr<struct safechain_client_impl> my;
   };

} }  /// eosio::chain

FC_REFLECT( eosio::chain::safechain_client::config,
            (rpc_address)
            (rpc_user)
            (rpc_password)
            (mock_static_success)
            (mock_static_failed)
            (mock_dynamic_failed)
            (mock_before_dynamic_failed_retry)
          )
