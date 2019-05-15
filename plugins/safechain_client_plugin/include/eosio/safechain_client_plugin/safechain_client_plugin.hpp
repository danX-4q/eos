/**
 *  @file
 *  @copyright defined in eos/LICENSE
 */
#pragma once
#include <appbase/application.hpp>
#include <eosio/chain_plugin/chain_plugin.hpp>
#include <fc/network/http/http_client.hpp>

namespace eosio {
   using namespace appbase;
   using fc::http_client;

   class safechain_client_plugin : public appbase::plugin<safechain_client_plugin>
   {
      public:
        safechain_client_plugin();
        virtual ~safechain_client_plugin();

        APPBASE_PLUGIN_REQUIRES((chain_plugin))
        virtual void set_program_options(options_description&, options_description& cfg) override;

        void plugin_initialize(const variables_map& options);
        void plugin_startup();
        void plugin_shutdown();

        bool get_mock_static_success();
        bool get_mock_static_failed();
        bool get_mock_dynamic_failed();
        uint32_t get_mock_before_dynamic_failed_retry();

      private:
        std::unique_ptr<class safechain_client_plugin_impl> my;
   };

}
