﻿// Copyright ReGuider Team, 2016-2017
//
#ifndef librg_core_h
#define librg_core_h

    // TODO(inlife): remove this constants from code
    // make them runtime-level settings

    /**
     * Random number setting current game platform id
     * to prevent connections from different games/mods, in future
     */
    #ifndef NETWORK_PLATFORM_ID
    #define NETWORK_PLATFORM_ID 1
    #endif

    /**
     * Version of protocol, should be changed if major, incompatible changes are introduced
     */
    #ifndef NETWORK_PROTOCOL_VERSION
    #define NETWORK_PROTOCOL_VERSION 1
    #endif

    /**
     * version of build. server owner can decide,
     * should clients should be refused or allowed joining the game
     */
    #ifndef NETWORK_BUILD_VERSION
    #define NETWORK_BUILD_VERSION 1
    #endif


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <ctime>
#include <string>
#include <map>
#include <array>
#include <vector>
#include <unordered_map>
#include <functional>

namespace librg
{
    enum mode {
        mode_server,
        mode_client,
        mode_server_manual,
        mode_client_manual
    };

    void core_initialize(mode mode);
    void core_terminate();

    namespace core
    {
        /**
         * Main entry point for framework
         * Starts all networking and other parts
         * @param host
         * @param port
         */
        void start(std::string host, int port);

        /**
         * Should be used with *_manual mode
         * to manually trigger each tick operation
         */
        void tick();

        /**
         * Main log method
         */
        void log(const char* format, ...);

        /**
         * Main error method
         */
        void error(const char* format, ...);

        /**
         * Set a mode for (server/client)
         * @param mode default is server
         */
        void set_mode(mode mode);

        /**
         * Get current mode
         * @return
         */
        mode get_mode();

        /**
         * Check if current execution mode is server
         */
        static inline bool is_server() {
            return (get_mode() == mode_server || get_mode() == mode_server_manual);
        }

        /**
         * Check if current execution mode is client
         */
        static inline bool is_client() {
            return (get_mode() == mode_client || get_mode() == mode_client_manual);
        }

        /**
         * Check if we are running in manual mode
         */
        static inline bool is_manual() {
            return (get_mode() == mode_client_manual || get_mode() == mode_server_manual);
        }
    }
}

#endif // librg_core_h
