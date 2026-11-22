#include "test_support.h"

/*
   Copyright 2024-2026 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

using namespace Harlinn::Math;
namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };


}
TEST_CASE("SegmentTests / SegmentDistanceTest1", "[math][SegmentTests]")
{
    Point3f A( 4, 2, 1 );
    Point3f B( 1, 0, 1 );
    Point3f C( 1, 2, 0 );

    Segment3<float> segment( B, C );

    auto distanceResult = Distance( A, segment );

    auto distance = distanceResult.Distance( );
    Point3f closestPoint = distanceResult.ClosestPoint( );
    auto fraction = distanceResult.Fraction( );

    auto expectedX = 1.f;
    auto expectedY = 8.f / 5.f;
    auto expectedZ = 1.f / 5.f;

    CHECK(closestPoint.x == expectedX);
    CHECK(closestPoint.y == expectedY);
    CHECK((closestPoint.z) == Catch::Approx(expectedZ).epsilon((0.001f) / 100.0));
}
TEST_CASE("SegmentTests / SegmentDistanceTest2", "[math][SegmentTests]")
{
    Point3f A( 2, 3, 6 );
    Point3f B( 1, 2, 1 );
    Point3f C( 1, 2, 5 );

    Segment3<float> segment( B, C );

    auto distanceResult = Distance( A, segment );

    auto distance = distanceResult.Distance( );
    Point3f closestPoint = distanceResult.ClosestPoint( );
    auto fraction = distanceResult.Fraction( );
    CHECK(closestPoint == C);
}
