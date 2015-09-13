#include "scene.h"
#include "rendering.h"

namespace scenimp {

    scene::scene(SDL_Renderer* r)
    : renderer_(r) {
        root_ = &new_group();

    }

    scene::~scene() {
    }

    group& scene::new_group(group* parent, int z) {
        group* s = group_pool_.malloc();
        attach(s, parent,z);
        return *s;
    }

    sprite& scene::new_sprite(group* parent, int z) {
        sprite* s = sprite_pool_.malloc();
        attach(s, parent, z);
        return *s;
    }

    void scene::attach(node* child, group* parent, int z) {
        if (nullptr == parent) {
            parent = root_;
        }
        parent->children_.insert(node_in_group(child, z));
        child->parent_ = parent;
    }

    void scene::delete_sprite(sprite* s) {
        detach(s);
        sprite_pool_.free(s);
    }

    void scene::delete_group(group* g) {
        detach(g);
        group_pool_.free(g);
    }

    void scene::detach(node* child) {
        child->parent_->children_.erase(child);
    }

    void scene::render() {
        rendering r(renderer_);
        root_->render(r);
    }

}
