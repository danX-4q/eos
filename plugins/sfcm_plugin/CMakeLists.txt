file(GLOB HEADERS "include/eosio/sfcm_plugin/*.hpp")
add_library( sfcm_plugin
             sfcm_plugin.cpp
             ${HEADERS} )

target_link_libraries( sfcm_plugin chain_plugin appbase fc )
target_include_directories( sfcm_plugin PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
