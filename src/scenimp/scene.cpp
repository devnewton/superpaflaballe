#include "scene.h"
#include "rendering.h"

namespace scenimp {

    scene::scene() {
        root_ = &new_group();

    }

    scene::~scene() {
    }

    group& scene::new_group(group* parent) {
        group* s = group_pool_.malloc();
        attach(s, parent);
        return *s;
    }

    sprite& scene::new_sprite(group* parent) {
        sprite* s = sprite_pool_.malloc();
        attach(s, parent);
        return *s;
    }

    void scene::attach(node* child, group* parent) {
        if (nullptr == parent) {
            parent = root_;
        }
        parent->children_.insert(child);
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
        rendering r;
        root_->render(r);
    }

}
