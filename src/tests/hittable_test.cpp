#include "../../test/catch.hpp"
#include "../headers/sphere.h"

TEST_CASE("hit: hits something")
{
    sphere s = sphere(point3(0, 0, -1), 0.5);
    // Straight through the middle of the sphere
    ray r = ray(point3(0, 0, 0), vec3(0, 0, -1));
    hit_record rec;
    s.hit(r, rec);
    REQUIRE(rec.t >= 0);
}

TEST_CASE("hit: misses when shooting in wrong direction")
{
    sphere s = sphere(point3(0, 0, -1), 0.5);
    ray r = ray(point3(0, 0, 0), vec3(0, 0, 1));
    hit_record rec;
    s.hit(r, rec);
    REQUIRE(rec.t < 0);
}

TEST_CASE("hit: misses when ball positioned away")
{
    sphere s = sphere(point3(0, -1, 0), 0.5);
    ray r = ray(point3(0, 0, 0), vec3(0, 0, -1));
    hit_record rec;
    s.hit(r, rec);
    REQUIRE(rec.t < 0);
}

TEST_CASE("hit: strafes the ball")
{
    sphere s = sphere(point3(0, 0.5, -1), 0.5);
    ray r = ray(point3(0, 0, 0), vec3(0, 0, -1));
    hit_record rec;
    s.hit(r, rec);
    REQUIRE(rec.t >= 0);
}

TEST_CASE("hit: Sets the correct surface normal direction")
{
    sphere s = sphere(point3(0, 0, -1), 0.5);
    ray r = ray(point3(0, 0, 0), vec3(0, 0, -1));
    hit_record rec;
    s.hit(r, rec);
    // Normal faces back up to the origin
    REQUIRE(rec.normal.z() == 1);
}

TEST_CASE("hit: Sets the opposite surface normal direction when hit from inside")
{
    sphere s = sphere(point3(0, 0, -1), 0.5);
    ray r = ray(point3(0, 0, -1), vec3(0, 0, -1));
    hit_record rec;
    s.hit(r, rec);
    // Normal faces back up to the origin
    REQUIRE(rec.normal.z() == 1);
}