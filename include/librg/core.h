// Copyright ReGuider Team, 2016-2017
//
#ifndef librg_core_h
#define librg_core_h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <librg/utils/linmath.h>

#include <ctime>
#include <string>
#include <map>
#include <array>
#include <vector>
#include <unordered_map>
#include <functional>

namespace librg
{
    /**
     * Modes librg can work with
     */
    enum mode_t {
        mode_server,        /* blocking server with own libuv loop */
        mode_client,        /* blocking client with own libuv loop */
        mode_server_manual, /* non-blocking server with run-once uv loop, manual core::tick() call required */
        mode_client_manual, /* non-blocking client with run-once uv loop, manual core::tick() call required */
    };

    struct config_t {
        // core
        uint16_t tick_rate;

        // streamer configuration
        hmm_vec3 world_size;

        // network configuration
        std::string ip;
        std::string password;
        uint16_t port;
        uint16_t max_connections;

        // backend network
        uint16_t platform_id;
        uint16_t proto_version;
        uint16_t build_version;
    };

    void core_initialize(mode_t mode);
    void core_terminate();

    namespace core
    {
        /**
         * Main entry point for framework
         * Starts all networking and other parts
         */
        void start(config_t config);

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
        void set_mode(mode_t mode);

        /**
         * Get current mode
         * @return
         */
        mode_t get_mode();

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
