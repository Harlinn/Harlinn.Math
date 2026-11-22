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
TEST_CASE("LineTests / LineDistanceTest1", "[math][LineTests]")
{
    Point3f lineOrigin( 0.f, 0.f, -3.f );
    Vector3f lineDirection( Normalize( Vector3f( 2.5f, 2.5f, 2.5f ) ) );
    Point3f point( 1.f, 1.f, 1.f );

    Line3f line( lineOrigin, lineDirection );

    auto distanceResult = Distance( point, line );

    auto distance = distanceResult.Distance( );
    Point3f closestPoint = distanceResult.ClosestPoint( );
    auto distanceFromOrigin = distanceResult.DistanceFromOrigin( );

    CHECK(closestPoint.x == 2.f);
    CHECK(closestPoint.y == 2.f);
    CHECK(closestPoint.z == -1.f);
}
TEST_CASE("LineTests / LineDistanceTest2", "[math][LineTests]")
{
    Point3f A( 4, 2, 1 );
    Point3f B( 1, 0, 1 );
    Point3f C( 1, 2, 0 );

    Line3f line( B, C );

    auto distanceResult = Distance( A, line );

    auto distance = distanceResult.Distance( );
    Point3f closestPoint = distanceResult.ClosestPoint( );
    auto distanceFromOrigin = distanceResult.DistanceFromOrigin( );

    auto expectedX = 1.f;
    auto expectedY = 8.f / 5.f;
    auto expectedZ = 1.f / 5.f;

    CHECK(closestPoint.x == expectedX);
    CHECK(closestPoint.y == expectedY);
    CHECK((closestPoint.z) == Catch::Approx(expectedZ).epsilon((0.001f) / 100.0));
}
TEST_CASE("LineTests / LineDistanceTest3", "[math][LineTests]")
{
    Point3f A( -1, -2, -2 );
    Point3f B( 1, 1, 1 );
    Point3f C( 1, 2, 2 );
    Point3f D( 1, 2, 0 );

    Line3f line1( A, B );
    Line3f line2( C, D );
    auto distanceResult = Distance( line1, line2 );

    auto distance = distanceResult.Distance( );
    Point3f closestPoint1 = distanceResult.ClosestPoint1( );
    Point3f closestPoint2 = distanceResult.ClosestPoint2( );

    CHECK(distance == 0.554700255f);
    
    CHECK(closestPoint1.x == 1.46153855f);
    CHECK(closestPoint1.y == 1.69230771f);
    CHECK(closestPoint1.z == 1.69230771f);

    CHECK(closestPoint2.x == 1.00000000f);
    CHECK(closestPoint2.y == 2.00000000f);
    CHECK(closestPoint2.z == 1.69230759f);

}
TEST_CASE("LineTests / LineDistanceTest4", "[math][LineTests]")
{
    Point3f A( 0, 0, 0 );
    Point3f B( 1, 2, 3 );
    Point3f C( 1, 1, 1 );
    Point3f D( 2, 3, 5 );

    Line3f line1( A, B );
    Line3f line2( C, D );
    auto distanceResult = Distance( line1, line2 );

    auto distance = distanceResult.Distance( );
    Point3f closestPoint1 = distanceResult.ClosestPoint1( );
    Point3f closestPoint2 = distanceResult.ClosestPoint2( );

    auto expectedDistance = Sqrt( 5.f ) / 5.f;

    CHECK(distance == expectedDistance);

    CHECK(closestPoint1.x == 1.40000772f);
    CHECK(closestPoint1.y == 2.80001545f);
    CHECK(closestPoint1.z == 4.20002317f);

    CHECK(closestPoint2.x == 1.80000710f);
    CHECK(closestPoint2.y == 2.60001421f);
    CHECK(closestPoint2.z == 4.20002842f);

}
