file(GLOB HEADERS "include/eosio/safechain_client_plugin/*.hpp")
add_library( safechain_client_plugin
             safechain_client_plugin.cpp
             ${HEADERS} )

target_link_libraries( safechain_client_plugin chain_plugin appbase fc )
target_include_directories( safechain_client_plugin PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
