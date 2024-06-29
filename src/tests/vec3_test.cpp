#include "../headers/vec3.h"
#include "../../test/catch.hpp"

TEST_CASE("addition")
{
    vec3 v3 = vec3(1, 1, 1) + vec3(1, 2, 3);
    REQUIRE(v3.x() == 2);
}

TEST_CASE("negation")
{
    vec3 v1 = vec3(1, 2, -3);
    REQUIRE(-v1.x() == -1);
    REQUIRE(-v1.y() == -2);
    REQUIRE(-v1.z() == 3);
}

TEST_CASE("subtraction")
{
    vec3 v1 = vec3(1, 2, 3) - vec3(1, 1, 1);
    REQUIRE(v1.x() == 0);
    REQUIRE(v1.y() == 1);
    REQUIRE(v1.z() == 2);
}

TEST_CASE("indexing")
{
    vec3 v1 = vec3(1, 2, 3);
    REQUIRE(v1[0] == 1);
    REQUIRE(v1[2] == 3);
}

TEST_CASE("index assignment")
{
    vec3 v1 = vec3(1, 2, 3);
    v1[0] = 4;
    REQUIRE(v1[0] == 4);
}

TEST_CASE("chained addition assignment")
{
    vec3 v1 = vec3(1, 2, 3);
    vec3 v2 = vec3(1, 2, 3);
    vec3 v3 = vec3(1, 1, 1);
    v1 += v2 += v3;
    REQUIRE(v1.x() == 3);
    REQUIRE(v1.y() == 5);
    REQUIRE(v1.z() == 7);
    // v2 should be modified by anything to the right
    REQUIRE(v2.x() == 2);

    // v3 shouldn't be modified
    REQUIRE(v3.x() == 1);
}

TEST_CASE("chained division assignment")
{
    vec3 v1 = vec3(2, 4, 6);
    v1 /= 2;
    REQUIRE(v1.x() == 1);
}