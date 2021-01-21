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
        std::vector<shared_ptr<hittable>>& objects();

        virtual bool hit(const ray &r, DATA_TYPE t_min, DATA_TYPE t_max, hit_record &rec) const override;
        virtual bool bounding_box(DATA_TYPE time0, DATA_TYPE time1, aabb &output_box) const override;
        virtual DATA_TYPE pdf_value(const vec3 &origin, const vec3 &dir) const override;
        virtual vec3 random(const vec3 &origon) const override;
};