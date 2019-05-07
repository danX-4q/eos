/**
 *  @file
 *  @copyright defined in eos/LICENSE
 */
#pragma once

#include <eosiolib/types.h>

#ifdef __cplusplus
extern "C" {
#endif

   /**
    * @defgroup safechainapi Safe-chain API
    * @ingroup contractdev
    * @brief Defines API for interactiving with safe-chain
    *
    *
    * wo~~~ by danX
    */

   /**
    * @defgroup safechaincapi Safe-chain C API
    * @ingroup safechaincapi
    * @brief Defines API for interactiving with safe-chain
    *
    * @{
    */

   /**
    *  Gets the confirmations of txid which has been occurred at safechain.
    *  @brief Gets the confirmations of txid which has been occurred at safechain.
    *  @param txid - pointer to txid, like "819ee164a9a6990de28089a76df30ee04e0f3c551df4990c24a5d1a822a978b4"
    *  @param txid_len - len of string `txid`
    *  @return confirmations of txid which has been occurred at safechain
    *
    *  Example:
    *
    *  @code
    *  uint64_t confirmations = 0;
    *  int ret = get_txid_confirmations(
    *                "819ee164a9a6990de28089a76df30ee04e0f3c551df4990c24a5d1a822a978b4", 
    *                64, confirmations);
    *  if(ret) {
    *    //success, and `confirmations` is meaningful
    *  }
    *  else {
    *    //failed, and `confirmations` is not meaningful
    *  }
    *  @endcode
    */
   int get_txid_confirmations(const char* txid, uint32_t txid_len, uint64_t& cfrms);


   /// @}
#ifdef __cplusplus
}
#endif
