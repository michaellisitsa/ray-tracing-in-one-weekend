#include "../../test/catch.hpp"
#include "../headers/sphere.h"
#include "../headers/hittable_list.h"

TEST_CASE("sphere hit: hits something")
{
    sphere s = sphere(point3(0, 0, -1), 0.5);
    // Straight through the middle of the sphere
    ray r = ray(point3(0, 0, 0), vec3(0, 0, -1));
    hit_record rec;
    s.hit(r, rec);
    REQUIRE(rec.t > 0);
}

TEST_CASE("sphere hit: misses when shooting in wrong direction")
{
    sphere s = sphere(point3(0, 0, -1), 0.5);
    ray r = ray(point3(0, 0, 0), vec3(0, 0, 1));
    hit_record rec;
    s.hit(r, rec);
    REQUIRE(rec.t < 0);
}

TEST_CASE("sphere hit: misses when ball positioned away")
{
    sphere s = sphere(point3(0, -1, 0), 0.5);
    ray r = ray(point3(0, 0, 0), vec3(0, 0, -1));
    hit_record rec;
    s.hit(r, rec);
    REQUIRE(rec.t < 0);
}

TEST_CASE("sphere hit: strafes the ball")
{
    sphere s = sphere(point3(0, 0.5, -1), 0.5);
    ray r = ray(point3(0, 0, 0), vec3(0, 0, -1));
    hit_record rec;
    s.hit(r, rec);
    REQUIRE(rec.t >= 0);
}

TEST_CASE("sphere hit: Sets the correct surface normal direction")
{
    sphere s = sphere(point3(0, 0, -1), 0.5);
    ray r = ray(point3(0, 0, 0), vec3(0, 0, -1));
    hit_record rec;
    s.hit(r, rec);
    // Normal faces back up to the origin
    REQUIRE(rec.normal.z() == 1);
}

TEST_CASE("sphere hit: Sets the opposite surface normal direction when hit from inside")
{
    sphere s = sphere(point3(0, 0, -1), 0.5);
    ray r = ray(point3(0, 0, -1), vec3(0, 0, -1));
    hit_record rec;
    s.hit(r, rec);
    // Normal faces back up to the origin
    REQUIRE(rec.normal.z() == 1);
}

TEST_CASE("hittable_list.hit: Hits the nearest shape")
{
    sphere s1 = sphere(point3(0, 0, -2), 0.5);
    sphere s2 = sphere(point3(0, 0, -1), 0.5);
    hittable_list list;
    list.add(std::make_shared<sphere>(s1));
    list.add(std::make_shared<sphere>(s2));
    ray r = ray(point3(0, 0, 0), vec3(0, 0, -0.25));
    auto rec = hit_record();
    list.hit(r, rec);
    REQUIRE(rec.p.length() == 0.5);
}

TEST_CASE("hittable_list.hit: Hits the correct shape when the first shape is offset from ray")
{
    sphere s1 = sphere(point3(0, 0, -2), 0.5);
    sphere s2 = sphere(point3(1, 1, -1), 0.5);
    hittable_list list;
    list.add(std::make_shared<sphere>(s1));
    list.add(std::make_shared<sphere>(s2));
    ray r = ray(point3(0, 0, 0), vec3(0, 0, -0.25));
    auto rec = hit_record();
    list.hit(r, rec);
    REQUIRE(rec.p.length() == 1.5);
}

TEST_CASE("hittable_list.hit: Miss both objects")
{
    sphere s1 = sphere(point3(-1, -1, -1), 0.5);
    sphere s2 = sphere(point3(1, 1, -1), 0.5);
    hittable_list list;
    list.add(std::make_shared<sphere>(s1));
    list.add(std::make_shared<sphere>(s2));
    ray r = ray(point3(0, 0, 0), vec3(0, 0, -1));
    auto rec = hit_record();
    list.hit(r, rec);
    REQUIRE(rec.t <= 0);
    REQUIRE(rec.p.length() == 0);
}