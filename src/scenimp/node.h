#pragma once

#include <memory>
#include <boost/container/flat_set.hpp>

namespace scenimp {
    
    class group;

    class node: public std::enable_shared_from_this<node> {
    public:
        node();
        node(const node& orig) = delete;
        virtual ~node();
        
        void detach();

    private:
        std::weak_ptr<group> parent_;
        
        friend class group;
    };

    typedef boost::container::flat_set< std::shared_ptr<node> > node_list;

}


