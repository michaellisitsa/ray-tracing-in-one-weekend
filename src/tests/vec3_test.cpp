#include "../headers/vec3.h"
#include "../../test/catch.hpp"

TEST_CASE("vec3 addition")
{
    vec3 v1 = vec3(1, 1, 1);
    vec3 v2 = vec3(1, 2, 3);
    vec3 v3 = v1 + v2;
    REQUIRE(v3.x() == 2);
}
