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

using namespace Harlinn;

namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };


}
TEST_CASE("MathVector4FloatTests / AddTest1", "[math][MathVector4FloatTests]")
{
    using Vector = Math::Vector<float, 4>;

    Vector v1( 1.0f, 2.0f, 3.f, 1.0f );
    Vector v2( 1.0f, 2.0f, 3.f, 1.0f );
    Vector v3 = v1 + v2 + v1 + v2 + v1 + v2;

    bool xAsExpected = v3.x == 6.f;
    bool yAsExpected = v3.y == 12.f;
    bool zAsExpected = v3.z == 18.f;
    bool wAsExpected = v3.w == 6.f;

    CHECK(xAsExpected);
    CHECK(yAsExpected);
    CHECK(zAsExpected);
    CHECK(wAsExpected);
}
TEST_CASE("MathVector4FloatTests / SubTest1", "[math][MathVector4FloatTests]")
{
    using Vector = Math::Vector<float, 4>;

    Vector v1( 6.0f, 12.0f, 7.f, 6.0f );
    Vector v2( 1.0f, 2.0f, 1.f, 1.0f );
    Vector v3 = v1 - v2 - v2 - v2 - v2 - v2;

    bool xAsExpected = v3.x == 1.f;
    bool yAsExpected = v3.y == 2.f;
    bool zAsExpected = v3.z == 2.f;
    bool wAsExpected = v3.w == 1.f;

    CHECK(xAsExpected);
    CHECK(yAsExpected);
    CHECK(zAsExpected);
    CHECK(wAsExpected);
}
TEST_CASE("MathVector4FloatTests / MulTest1", "[math][MathVector4FloatTests]")
{
    using Vector = Math::Vector<float, 4>;

    Vector v1( 2.0f, 3.0f, 4.f, 2.0f );
    Vector v2( 2.0f, 3.0f, 4.f, 2.0f );
    Vector v3 = v1 * v2;

    bool xAsExpected = v3.x == 4.f;
    bool yAsExpected = v3.y == 9.f;
    bool zAsExpected = v3.z == 16.f;
    bool wAsExpected = v3.w == 4.f;

    CHECK(xAsExpected);
    CHECK(yAsExpected);
    CHECK(zAsExpected);
    CHECK(wAsExpected);
}
TEST_CASE("MathVector4FloatTests / MulTest2", "[math][MathVector4FloatTests]")
{
    using Vector = Math::Vector<float, 4>;

    Vector v1( 2.0f, 3.0f, 4.f, 2.0f );
    Vector v2( 2.0f, 3.0f, 4.f, 2.0f );
    Vector v3 = v1 * v2 * 2.f;

    bool xAsExpected = v3.x == 8.f;
    bool yAsExpected = v3.y == 18.f;
    bool zAsExpected = v3.z == 32.f;
    bool wAsExpected = v3.w == 8.f;

    CHECK(xAsExpected);
    CHECK(yAsExpected);
    CHECK(zAsExpected);
    CHECK(wAsExpected);
}
TEST_CASE("MathVector4FloatTests / MulTest3", "[math][MathVector4FloatTests]")
{
    using Vector = Math::Vector<float, 4>;

    Vector v1( 2.0f, 3.0f, 4.f, 2.0f );
    Vector v3 = v1 * 2.f;

    bool xAsExpected = v3.x == 4.f;
    bool yAsExpected = v3.y == 6.f;
    bool zAsExpected = v3.z == 8.f;
    bool wAsExpected = v3.w == 4.f;

    CHECK(xAsExpected);
    CHECK(yAsExpected);
    CHECK(zAsExpected);
    CHECK(wAsExpected);
}
TEST_CASE("MathVector4FloatTests / MulTest4", "[math][MathVector4FloatTests]")
{
    using Vector = Math::Vector<float, 4>;

    Vector v1( 2.0f, 3.0f, 4.f, 2.0f );
    Vector v3 = 2.f * v1;

    bool xAsExpected = v3.x == 4.f;
    bool yAsExpected = v3.y == 6.f;
    bool zAsExpected = v3.z == 8.f;
    bool wAsExpected = v3.w == 4.f;

    CHECK(xAsExpected);
    CHECK(yAsExpected);
    CHECK(zAsExpected);
    CHECK(wAsExpected);
}
TEST_CASE("MathVector4FloatTests / DivTest1", "[math][MathVector4FloatTests]")
{
    using Vector = Math::Vector<float, 4>;

    Vector v1( 4.0f, 9.0f, 12.f, 4.0f );
    Vector v2( 2.0f, 3.0f, 4.f, 2.0f );
    Vector v3 = v1 / v2;

    bool xAsExpected = v3.x == 2.f;
    bool yAsExpected = v3.y == 3.f;
    bool zAsExpected = v3.z == 3.f;
    bool wAsExpected = v3.w == 2.f;

    CHECK(xAsExpected);
    CHECK(yAsExpected);
    CHECK(zAsExpected);
    CHECK(wAsExpected);
}
TEST_CASE("MathVector4FloatTests / DivTest2", "[math][MathVector4FloatTests]")
{
    using Vector = Math::Vector<float, 4>;

    Vector v1( 4.0f, 6.0f, 8.f, 4.0f );

    Vector v3 = v1 / 2.f;

    bool xAsExpected = v3.x == 2.f;
    bool yAsExpected = v3.y == 3.f;
    bool zAsExpected = v3.z == 4.f;
    bool wAsExpected = v3.w == 2.f;

    CHECK(xAsExpected);
    CHECK(yAsExpected);
    CHECK(zAsExpected);
    CHECK(wAsExpected);
}
TEST_CASE("MathVector4FloatTests / OuterProductTest", "[math][MathVector4FloatTests]")
{
    Vector4f a( 5, 4, 3, 2 );
    Vector4f b( 3, 5, 7, 9 );
    SquareMatrix<float, 4> m = OuterProduct( a, b );
    Vector4f r1 = m[ 0 ];
    Vector4f r2 = m[ 1 ];
    Vector4f r3 = m[ 2 ];
    Vector4f r4 = m[ 3 ];


    Vector4f expectedR1( 15, 25, 35, 45 );
    Vector4f expectedR2( 12, 20, 28, 36 );
    Vector4f expectedR3( 9, 15, 21, 27 );
    Vector4f expectedR4( 6, 10, 14,	18 );



    CHECK(r1 == expectedR1);
    CHECK(r2 == expectedR2);
    CHECK(r3 == expectedR3);
    CHECK(r4 == expectedR4);
}
