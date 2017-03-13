#include <librg/network.h>
#include <librg/core/shared.h>

#include <librg/network/server/connection.hpp>
#include <librg/network/client/connection.hpp>

using namespace librg;

void librg::network_initialize()
{
    network::data.peer = RakNet::RakPeerInterface::GetInstance();

    // reset all registry to nulls
    for (int i = 0; i < network::PACKET_LIMIT; ++i) {
        network::handlers[i] = nullptr;
    }

    if (core::is_server()) {
        network::handlers[ID_NEW_INCOMING_CONNECTION]    = network::server_new_incoming_connection;
        network::handlers[ID_CONNECTION_LOST]            = network::server_disconnect;
        network::handlers[ID_DISCONNECTION_NOTIFICATION] = network::server_disconnect;
        network::handlers[MessageID::CONNECTION_INIT]    = network::server_connect;
    }

    if (core::is_client()) {
        network::handlers[ID_REMOTE_DISCONNECTION_NOTIFICATION] = network::client_remote_disconnect;
        network::handlers[ID_REMOTE_CONNECTION_LOST]            = network::client_remote_connectionlost;
        network::handlers[ID_REMOTE_NEW_INCOMING_CONNECTION]    = network::client_remote_newincoming;
        network::handlers[ID_NEW_INCOMING_CONNECTION]           = network::client_new_incoming_connection;
        network::handlers[ID_NO_FREE_INCOMING_CONNECTIONS]      = network::client_no_free_incoming_connections;
        network::handlers[ID_DISCONNECTION_NOTIFICATION]        = network::client_disconnect_notification;
        network::handlers[ID_CONNECTION_LOST]                   = network::client_connection_lost;
        network::handlers[ID_CONNECTION_REQUEST_ACCEPTED]       = network::client_connection_request_accepted;
        network::handlers[MessageID::CONNECTION_ACCEPTED]       = network::cleint_connection_success;
    }

    if (core::is_server()) {
        network::server(27010);
    }

    // if (core::is_client()) {
    //     core::log("hello client");
    // }
}

/**
 * Storage for handlers
 */
network::handler_t network::handlers;

/**
 * Storage for network data
 */
network::data_t network::data;

/**
 * Storage for current clients
 */
std::map<RakNet::RakNetGUID, network::client_t> network::clients;
