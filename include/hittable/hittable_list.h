#pragma once

#include <basic/hittable.h>

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittable_list : public hittable {
    private:
        std::vector<shared_ptr<hittable>> objs;

    public:
        hittable_list();
        hittable_list(shared_ptr<hittable> obj);

        void clear();
        void add(shared_ptr<hittable> obj);

        virtual bool hit(const ray &r, DATA_TYPE t_min, DATA_TYPE t_max, hit_record &rec) const override;
};