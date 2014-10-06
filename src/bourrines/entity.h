#pragma once

#include <limits>
#include <boost/container/flat_set.hpp>

namespace bourrines {

    typedef std::size_t entity;
    const entity null_entity = std::numeric_limits<entity>::max();

    typedef boost::container::flat_set<entity> active_entity_list;

}