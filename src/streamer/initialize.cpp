#include <librg/streamer.h>
#include <librg/components/streamable.h>

librg::streamer::qtree_t librg::streamer::_root;

void librg::streamer_initialize()
{
    librg::_systems->add<entityx::deps::Dependency<streamable_t, transform_t>>();
}