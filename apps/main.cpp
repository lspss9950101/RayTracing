#include <basic/common.h>
#include <basic/hittable.h>
#include <basic/camera.h>
#include <hittable/sphere.h>
#include <hittable/hittable_list.h>
#include <hittable/hollow_sphere.h>
#include <hittable/moving_sphere.h>
#include <hittable/bvh.h>
#include <hittable/rect.h>
#include <hittable/box.h>
#include <hittable/translation.h>
#include <hittable/rotation.h>
#include <hittable/constant_medium.h>
#include <material/lambertian.h>
#include <material/metal.h>
#include <material/dielectric.h>
#include <material/diffuse_light.h>
#include <texture/checker_texture.h>
#include <texture/noise_texture.h>

#include <thread_pool/thread_pool.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>

color ray_color(const ray &r, const color &background, const hittable &world, int depth=20) {
    if(depth <= 0) return color({0,0,0});

    hit_record rec;
    if(!world.hit(r, 0.0001, common::inf, rec)) return background;

    ray scattered;
    color attenuation;
    color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

    if(!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        return emitted;
    
    return emitted + attenuation * ray_color(scattered, background, world, depth-1);
}

hittable_list random_scene() {
    hittable_list world;

    auto checker_tex = make_shared<checker_texture>(color({0.5, 0.5, 0.5}), color({0.3, 0.3, 0.8}));
    auto ground_mat = make_shared<lambertian>(checker_tex);
    world.add(make_shared<sphere>(point3({0, -1000, 0}), 1000, ground_mat));

    for(int i = -11; i < 11; i++) {
        for(int j = -11; j < 11; j++) {
            auto random_mat = common::random();
            point3 center({i+0.9*common::random(), 0.2, j+0.9*common::random()});

            if((center - point3({4, 0.2, 0})).length() > 0.9) {
                shared_ptr<material> sphere_mat;

                if(random_mat < 0.7) {
                    auto albedo = color::random() * color::random();
                    //auto center_end = center + vec3({0, common::random(0, 0.1), 0});
                    sphere_mat = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_mat));
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
    world.add(make_shared<sphere>(point3({0, 1, 0}), 0.8, metal_mat));
    world.add(make_shared<hollow_sphere>(point3({0, 1, 0}), 1, 0.1, dielectric_mat));

    auto lambertian_mat = make_shared<lambertian>(color({0.8, 0.5, 0.5}));
    world.add(make_shared<sphere>(point3({-4, 1, 0}), 1, lambertian_mat));

    return world;
}

hittable_list two_spheres() {
    hittable_list world;
    auto checker = make_shared<checker_texture>(color({0.5, 0.5, 0.5}), color({0.3, 0.3, 0.8}));
    world.add(make_shared<sphere>(point3({0, -10, 0}), 10, make_shared<lambertian>(checker)));
    world.add(make_shared<sphere>(point3({0, 10, 0}), 10, make_shared<lambertian>(checker)));
    return world;
}

hittable_list two_perlin_spheres() {
    hittable_list world;

    auto tex = make_shared<noise_texture>(4, color({1, 1, 1}));
    auto mat = make_shared<lambertian>(tex);
    world.add(make_shared<sphere>(point3({0, -1000, 0}), 1000, mat));
    world.add(make_shared<sphere>(point3({0, 2, 0}), 2, mat));
    return world;
}

hittable_list simple_light() {
    hittable_list world;

    auto per_tex = make_shared<noise_texture>(4, color({1, 1, 1}));
    auto mat = make_shared<lambertian>(per_tex);
    world.add(make_shared<sphere>(point3({0, -1000, 0}), 1000, mat));
    world.add(make_shared<sphere>(point3({0, 2, 0}), 2, mat));

    auto diff_light = make_shared<diffuse_light>(color({4, 4, 4}));
    world.add(make_shared<aarect<0, 1>>(3, 5, 1, 3, -2, diff_light));

    return world;
}

hittable_list cornell_box() {
    hittable_list world;

    auto red   = make_shared<lambertian>(color({.65, .05, .05}));
    auto white = make_shared<lambertian>(color({.73, .73, .73}));
    auto green = make_shared<lambertian>(color({.12, .45, .15}));
    auto light = make_shared<diffuse_light>(color({5, 5, 5}));

    world.add(make_shared<aarect<1, 2>>(-250, 250, 0, 500, -250, green));
    world.add(make_shared<aarect<1, 2>>(-250, 250, 0, 500, 250, red));
    world.add(make_shared<aarect<0, 2>>(-100, 100, 150, 350, 250, light));
    world.add(make_shared<aarect<0, 2>>(-250, 250, 0, 500, 250, white));
    world.add(make_shared<aarect<0, 2>>(-250, 250, 0, 500, -250, white));
    world.add(make_shared<aarect<0, 1>>(-250, 250, -250, 250, 500, white));
    //world.add(make_shared<aarect<0, 1>>(0, 555, 0, 555, 0, white));

    shared_ptr<hittable> box_l = make_shared<aabox>(point3({0, 0, 0}), point3({150, 300, 150}), white);
    box_l = make_shared<rotation<1>>(box_l, 15);
    box_l = make_shared<translation>(box_l, vec3({0, -250, 285}));
    world.add(box_l);

    shared_ptr<hittable> box_r = make_shared<aabox>(point3({0, 0, 0}), point3({150, 150, 150}), white);
    box_r = make_shared<rotation<1>>(box_r, -18);
    box_r = make_shared<translation>(box_r, vec3({-120, -250, 100}));
    world.add(box_r);

    return world;
}

hittable_list cornell_box_fog() {
    hittable_list world;

    auto red   = make_shared<lambertian>(color({.65, .05, .05}));
    auto white = make_shared<lambertian>(color({.73, .73, .73}));
    auto green = make_shared<lambertian>(color({.12, .45, .15}));
    auto light = make_shared<diffuse_light>(color({5, 5, 5}));

    world.add(make_shared<aarect<1, 2>>(-250, 250, 0, 500, -250, green));
    world.add(make_shared<aarect<1, 2>>(-250, 250, 0, 500, 250, red));
    world.add(make_shared<aarect<0, 2>>(-150, 150, 200, 400, 250, light));
    world.add(make_shared<aarect<0, 2>>(-250, 250, 0, 500, 250, white));
    world.add(make_shared<aarect<0, 2>>(-250, 250, 0, 500, -250, white));
    world.add(make_shared<aarect<0, 1>>(-250, 250, -250, 250, 500, white));
    //world.add(make_shared<aarect<0, 1>>(0, 555, 0, 555, 0, white));

    shared_ptr<hittable> box_l = make_shared<aabox>(point3({0, 0, 0}), point3({150, 300, 150}), white);
    box_l = make_shared<rotation<1>>(box_l, 15);
    box_l = make_shared<translation>(box_l, vec3({0, -250, 285}));
    world.add(make_shared<constant_medium>(box_l, 0.01, color({0, 0, 0})));

    shared_ptr<hittable> box_r = make_shared<aabox>(point3({0, 0, 0}), point3({150, 150, 150}), white);
    box_r = make_shared<rotation<1>>(box_r, -18);
    box_r = make_shared<translation>(box_r, vec3({-120, -250, 100}));
    world.add(make_shared<constant_medium>(box_r, 0.01, color({1, 1, 1})));

    return world;
}

hittable_list DNA_scene() {
    hittable_list floor_blocks;

    auto floor_mat = make_shared<lambertian>(color({0.48, 0.83, 0.53}));
    auto light_mat = make_shared<diffuse_light>(color({40, 40, 40}));
    for(int i = -20; i <= 20; i++)
        for(int j = -20; j <= 20; j++) {
            if(!i && !j) continue;
            float x0 = i * 100 - 50;
            float x1 = i * 100 + 50;
            float z0 = j * 100 - 50;
            float z1 = j * 100 + 50;
            float y0 = 0;
            float y1 = common::random(1, 101);
            floor_blocks.add(make_shared<aabox>(point3({x0, y0, z0}), point3({x1, y1, z1}), floor_mat));
        }
    auto floor_ptr = make_shared<bvh_node>(floor_blocks, 0, 0);

    hittable_list dna;
    auto dna_surf_mat = make_shared<dielectric>(1.5);
    for(float i = 0; i < 700; i+= 10) {
        auto dna_mat = make_shared<solid_color>(color({0.6, 0.6, 0.7 + i / 700.f * 0.2}));

        point3 p_({10 * cos(i * 0.02) - i * 0.1, 0, 10 * sin(i * 0.02)});
        point3 p0({40 * cos(i * 0.03), i, 40 * sin(i * 0.03)});
        point3 p1({-40 * cos(i * 0.03), i, -40 * sin(i * 0.03)});
        p0 += p_;
        p1 += p_;

        auto boundary = make_shared<sphere>(p0, 10, dna_surf_mat);
        dna.add(boundary);
        dna.add(make_shared<constant_medium>(boundary, 0.5, dna_mat));
        
        boundary = make_shared<sphere>(p1, 10, dna_surf_mat);
        dna.add(boundary);
        dna.add(make_shared<constant_medium>(boundary, 0.5, dna_mat));

        if((int)i % 20) continue;

        for(float j = 1 / 10.f; j < 1; j += 1 / 10.f) {
            point3 p = interpolate(j, p0, p1);
            boundary = make_shared<sphere>(p, 3, dna_surf_mat);
            dna.add(boundary);
            dna.add(make_shared<constant_medium>(boundary, 0.05, dna_mat));
        }
    }
    auto dna_ptr = make_shared<bvh_node>(dna, 0, 0);

    auto light_cover = make_shared<lambertian>(color({0.5, 0.5, 0.5}));
    hittable_list world;
    world.add(floor_ptr);
    world.add(dna_ptr);
    world.add(make_shared<aarect<0, 2>>(-200, 200, -200, 200, 1000, light_mat));
    world.add(make_shared<aarect<0, 1>>(-200, 200, 750, 1000, -200, light_cover));
    world.add(make_shared<aarect<0, 1>>(-200, 200, 750, 1000, 200, light_cover));
    world.add(make_shared<aarect<2, 1>>(-200, 200, 750, 1000, -200, light_cover));
    world.add(make_shared<aarect<2, 1>>(-200, 200, 750, 1000, 200, light_cover));

    return world;
}

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    auto start = std::chrono::steady_clock::now();

    std::fstream file;
    file.open("image.ppm", std::ios::out);

    double aspect_ratio = 16 / 9.L;

    hittable_list world;
    bvh_node world_bvh;

    point3 lookfrom;
    point3 lookat;
    double vfov = 40.0;
    double aperture = 0.0;
    vec3 vup({0, 1, 0});
    double dist_to_focus = 10;
    double time0 = 0;
    double time1 = 1.0;
    color background;

    switch(8) {
        case 1:
            world = random_scene();
            background = color({0.70, 0.80, 1.00});
            lookfrom = point3({13, 2, 3});
            lookat = point3({0, 0, 0});
            vfov = 20.0;
            aperture = 0.1;
            break;
        case 2:
            world = two_spheres();
            background = color({0.70, 0.80, 1.00});
            lookfrom = point3({13, 2, 3});
            lookat = point3({0, 0, 0});
            vfov = 20.0;
            break;
        case 3:
            world.add(make_shared<sphere>(point3({0, 0, 0}), 0.1, make_shared<lambertian>(color({0.5, 0.5, 0.5}))));
            background = color({0.70, 0.80, 1.00});
            lookfrom = point3({13, 2, 3});
            lookat = point3({0, 0, 0});
            vfov = 20.0;
            break;
        case 4:
            world = two_perlin_spheres();
            background = color({0.70, 0.80, 1.00});
            lookfrom = point3({13, 2, 3});
            lookat = point3({0, 0, 0});
            vfov = 20;
            break;
        case 5:
            world = simple_light();
            background = color({0, 0, 0});
            lookfrom = point3({26, 3, 6});
            lookat = point3({0, 2, 0});
            vfov = 20;
            break;
        case 6:
            world = cornell_box();
            aspect_ratio = 1;
            background = color({0, 0, 0});
            lookfrom = point3({0, 0, -600});
            lookat = point3({0, 0, 0});
            vfov = 40;
            break;
        case 7:
            world = cornell_box_fog();
            aspect_ratio = 1;
            background = color({0, 0, 0});
            lookfrom = point3({0, 0, -600});
            lookat = point3({0, 0, 0});
            vfov = 40;
            break;
        case 8:
            world = DNA_scene();
            aspect_ratio = 16 / 9.L;
            background = color({0, 0, 0});
            lookfrom = point3({100, 400, -800});
            lookat = point3({-50, 300, 0});
            vfov = 50;
            break;
        default:
            background = color({0, 0, 0});
            break;
    }

    const int image_width = argc > 1 ? atoi(argv[1]) : 600;
    const int image_height = image_width / aspect_ratio;
    const int samples_per_pixel = argc > 2 ? atoi(argv[2]) : 100;
    const int max_depth = argc > 3 ? atoi(argv[3]) : 50;

    world_bvh = bvh_node(world, time0, time1);
    shared_ptr<hittable> world_ptr = make_shared<bvh_node>(world_bvh);
    camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, time0, time1);
    cam.set_color_function(ray_color);
    auto cam_ptr = make_shared<camera>(cam);

    thread_pool pool(10, 100);
    pool.start();

    file << "P3\n" << image_width << " " << image_height << "\n255\n";
    std::cerr << "- Outputing image " << image_width << 'x' << image_height
              << "\n- Samples per pixel: " << samples_per_pixel
              << "\n- Max depth : " << max_depth << "\n" << std::endl;
    
    shared_ptr<color[]> shaded(new color[image_height * image_width]);
    for(int i = image_height-1; i >= 0; i--) {
        std::cerr << "\rTask Generation Remaining: " << i << ' ';
        for(int j = 0; j < image_width; j++) {
            thread_pool::task *new_task = new thread_pool::task({
                .x = j,
                .y = i,
                .depth = max_depth,
                .image_height = image_height,
                .image_width = image_width,
                .sample_per_pixel = samples_per_pixel,
                .world = world_ptr,
                .shaded = shaded,
                .cam = cam_ptr,
                .background = background
            });
            pool.push_task(new_task);
        }
    }

    pool.join(image_width);

    for(int i = image_height-1; i >= 0; i--)
        for(int j = 0; j < image_width; j++)
            write_color(file, shaded[i * image_width + j], samples_per_pixel);
    file << std::flush;
    std::cerr << "\nDone\n";

    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start);
    auto c = elapsed.count();
    std::ostringstream oss;
    oss << std::setw(3)
        << (c / 1000 / 60)
        << " minutes "
        << std::setfill('0')
        << std::setw(2)
        << (c / 1000) % 60
        << "."
        << std::setw(3)
        << c % 1000
        << " seconds";
    
    std::cerr << "Elapsed time : " << oss.str() << std::endl;

    return 0;
}