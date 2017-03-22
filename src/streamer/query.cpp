#include <librg/streamer.h>
#include <librg/components/streamable.h>

void librg::streamer::qtree_t::query(std::vector<entityx::Entity> &visible, aabb_t range)
{
    if (!boundary.intersects(range)) return;

    for (int i = 0; i < entities.size(); i++) {
        auto position = entities[i].component<transform_t>()->position;
        if (range.contains(position)) {
            visible.push_back(entities[i]);
        }
    }

    if (trees.size() == 0) return;

    for (auto &tree : trees) {
        tree.query(visible, range);
    }
}

auto librg::streamer::query(entityx::Entity entity)
{
    auto visible = std::vector<entityx::Entity>();

    auto streamable = entity.component<streamable_t>();
    if (!streamable) return visible;
    auto transform  = entity.component<transform_t>();

    auto range    = streamable->queryRange;
    auto position = transform->position;
    auto boundary = aabb_t(position, range);

    _root.query(visible, boundary);

    return visible;
}
