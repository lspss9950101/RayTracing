#include <basic/common.h>
#include <basic/hittable.h>
#include <basic/camera.h>
#include <hittable/sphere.h>
#include <hittable/hittable_list.h>
#include <hittable/hollow_sphere.h>
#include <hittable/moving_sphere.h>
#include <material/lambertian.h>
#include <material/metal.h>
#include <material/dielectric.h>

#include <thread_pool/thread_pool.h>
#include <cstdlib>
#include <iostream>
#include <fstream>

color ray_color(const ray &r, const hittable &world, int depth=20) {
    if(depth <= 0) return color({0,0,0});

    hit_record rec;
    if(world.hit(r, 0.0001, common::inf, rec)) {
        ray scattered;
        color attenuation;
        if(rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);

        return color({0,0,0});
    }

    vec3 unit_direction = r.direction().unit();
    auto t = 0.5*(unit_direction[1] + 1.0);
    return interpolate(1-t, color({0.5,0.7,1.0}), color({1,1,1}));
}

hittable_list random_scene() {
    hittable_list world;

    auto ground_mat = make_shared<lambertian>(color({0.5,0.5,0.5}));
    world.add(make_shared<sphere>(point3({0, -1000, 0}), 1000, ground_mat));

    for(int i = -11; i < 11; i++) {
        for(int j = -11; j < 11; j++) {
            auto random_mat = common::random();
            point3 center({i+0.9*common::random(), 0.2, j+0.9*common::random()});

            if((center - point3({4, 0.2, 0})).length() > 0.9) {
                shared_ptr<material> sphere_mat;

                if(random_mat < 0.7) {
                    auto albedo = color::random() * color::random();
                    auto center_end = center + vec3({0, common::random(0, 0.5), 0});
                    sphere_mat = make_shared<lambertian>(albedo);
                    world.add(make_shared<moving_sphere>(center, center_end, 0, 0.3, 0.2, sphere_mat));
                } else if(random_mat < 0.8) {
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = common::random(0, 1);
                    sphere_mat = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_mat));
                } else if(random_mat < 0.9) {
                    sphere_mat = make_shared<dielectric>(1.3);
                    world.add(make_shared<sphere>(center, 0.2, sphere_mat));
                } else {
                    sphere_mat = make_shared<dielectric>(1.3);
                    world.add(make_shared<hollow_sphere>(center, 0.2, 0.05, sphere_mat));
                }
            }
        }
    }

    auto dielectric_mat = make_shared<dielectric>(2);
    world.add(make_shared<hollow_sphere>(point3({4, 1, 0}), 1, 0.1, dielectric_mat));

    auto metal_mat = make_shared<metal>(color({0.2, 0.2, 0.6}), 0.1);
    world.add(make_shared<sphere>(point3({0, 1, 0}), 0.3, metal_mat));
    world.add(make_shared<sphere>(point3({0, 1, 0}), 1, dielectric_mat));

    auto lambertian_mat = make_shared<lambertian>(color({0.8, 0.5, 0.5}));
    world.add(make_shared<sphere>(point3({-4, 1, 0}), 1, lambertian_mat));

    return world;
}

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);

    std::fstream file;
    file.open("image.ppm", std::ios::out);

    const double aspect_ratio = 16 / 9.L;
    const int image_width = argc > 1 ? atoi(argv[1]) : 600;
    const int image_height = image_width / aspect_ratio;
    const int samples_per_pixel = argc > 2 ? atoi(argv[2]) : 100;
    const int max_depth = 50;

    auto world = random_scene();
    shared_ptr<hittable> world_ptr = make_shared<hittable_list>(world);

    point3 lookfrom({13, 2, 5});
    point3 lookat({0, 0.5, 0});
    vec3 vup({0, 1, 0});
    auto dist_to_focus = 10;
    auto aperture = 0.1;
    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus, 0, 0.3);

    thread_pool pool(10, ray_color);

    file << "P3\n" << image_width << " " << image_height << "\n255\n";
    std::cerr << "Outputing image " << image_width << 'x' << image_height << " samples per pixel: " << samples_per_pixel << "\n";
    
    shared_ptr<color[]> shaded(new color[image_height * image_width]);
    for(int i = image_height-1; i >= 0; i--) {
        std::cerr << "\rScanlines Remaining: " << i << ' ' << std::flush;
        for(int j = 0; j < image_width; j++) {
            for(int k = 0; k < samples_per_pixel; k++) {
                auto u = (j + common::random()) / (image_width + 1);
                auto v = (i + common::random()) / (image_height + 1);
                ray r = cam.get_ray(u, v);
                pool.push_task(r, world_ptr, max_depth, i * image_width + j, shaded);
            }
        }
    }

    pool.join();

    for(int i = image_height-1; i >= 0; i--)
        for(int j = 0; j < image_width; j++)
            write_color(file, shaded[i * image_width + j], samples_per_pixel);
    file << std::flush;
    std::cerr << "\nDone\n";

    return 0;
}