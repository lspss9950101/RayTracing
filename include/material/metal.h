#pragma once

#include <basic/common.h>
#include <basic/material.h>

class metal : public material {
    private:
        color albedo;
        DATA_TYPE fuzziness;

    public:
        metal(const color &albedo, const DATA_TYPE fuzziness = 0);
        
        virtual bool scatter(const ray &r_in, const hit_record &rec, scatter_record &srec) const override;
};