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
TEST_CASE("MathVector2FloatTests / VectorTypeTest1", "[math][MathVector2FloatTests]")
{
    using Vector = Math::Vector<float, 2>;

    constexpr bool isVectorType1 = Math::VectorType<Vector>;
    constexpr bool isVectorType2 = Math::VectorType<Math::Normal3f>;
    constexpr bool isVectorType3 = Math::VectorType<Math::Point2f>;

    CHECK(isVectorType1);
    CHECK(isVectorType2 == false);
    CHECK(isVectorType3 == false);

    CHECK(sizeof( Vector ) == 8);

}
TEST_CASE("MathVector2FloatTests / AddTest1", "[math][MathVector2FloatTests]")
{
    using Vector = Math::Vector<float, 2>;

    Vector v1( 1.0f, 2.0f );
    Vector v2( 1.0f, 2.0f );
    Vector v3 = v1 + v2 + v1 + v2 + v1 + v2;

    bool xAsExpected = v3.x == 6.f;
    bool yAsExpected = v3.y == 12.f;

    CHECK(xAsExpected);
    CHECK(yAsExpected);
}
TEST_CASE("MathVector2FloatTests / SubTest1", "[math][MathVector2FloatTests]")
{
    using Vector = Math::Vector<float, 2>;

    Vector v1( 6.0f, 12.0f );
    Vector v2( 1.0f, 2.0f );
    Vector v3 = v1 - v2 - v2 - v2 - v2 - v2;

    bool xAsExpected = v3.x == 1.f;
    bool yAsExpected = v3.y == 2.f;

    CHECK(xAsExpected);
    CHECK(yAsExpected);
}
TEST_CASE("MathVector2FloatTests / MulTest1", "[math][MathVector2FloatTests]")
{
    using Vector = Math::Vector<float, 2>;

    Vector v1( 2.0f, 3.0f );
    Vector v2( 2.0f, 3.0f );
    Vector v3 = v1 * v2;

    bool xAsExpected = v3.x == 4.f;
    bool yAsExpected = v3.y == 9.f;

    CHECK(xAsExpected);
    CHECK(yAsExpected);
}
TEST_CASE("MathVector2FloatTests / MulTest2", "[math][MathVector2FloatTests]")
{
    using Vector = Math::Vector<float, 2>;

    Vector v1( 2.0f, 3.0f );
    Vector v2( 2.0f, 3.0f );
    Vector v3 = v1 * v2 * 2.f;

    bool xAsExpected = v3.x == 8.f;
    bool yAsExpected = v3.y == 18.f;

    CHECK(xAsExpected);
    CHECK(yAsExpected);
}
TEST_CASE("MathVector2FloatTests / MulTest3", "[math][MathVector2FloatTests]")
{
    using Vector = Math::Vector<float, 2>;

    Vector v1( 2.0f, 3.0f );
    Vector v3 = v1 * 2.f;

    bool xAsExpected = v3.x == 4.f;
    bool yAsExpected = v3.y == 6.f;

    CHECK(xAsExpected);
    CHECK(yAsExpected);
}
TEST_CASE("MathVector2FloatTests / MulTest4", "[math][MathVector2FloatTests]")
{
    using Vector = Math::Vector<float, 2>;

    Vector v1( 2.0f, 3.0f );
    Vector v3 = 2.f * v1;

    bool xAsExpected = v3.x == 4.f;
    bool yAsExpected = v3.y == 6.f;

    CHECK(xAsExpected);
    CHECK(yAsExpected);
}
TEST_CASE("MathVector2FloatTests / DivTest1", "[math][MathVector2FloatTests]")
{
    using Vector = Math::Vector<float, 2>;

    Vector v1( 4.0f, 9.0f );
    Vector v2( 2.0f, 3.0f );
    Vector v3 = v1 / v2;

    bool xAsExpected = v3.x == 2.f;
    bool yAsExpected = v3.y == 3.f;

    CHECK(xAsExpected);
    CHECK(yAsExpected);
}
TEST_CASE("MathVector2FloatTests / DivTest2", "[math][MathVector2FloatTests]")
{
    using Vector = Math::Vector<float, 2>;

    Vector v1( 4.0f, 6.0f );
    
    Vector v3 = v1 / 2.f;

    bool xAsExpected = v3.x == 2.f;
    bool yAsExpected = v3.y == 3.f;

    CHECK(xAsExpected);
    CHECK(yAsExpected);
}
TEST_CASE("MathVector2FloatTests / Basics", "[math][MathVector2FloatTests]")
{
    using Vector = Math::Vector<float, 2>;

    Vector vf( -1.f, 10.f );

    auto notEqual = vf != Vector( -1.f, 100.f );
    CHECK(notEqual);

    auto equal = Vector( -2.f, 20.f ) == vf + vf;
    CHECK(equal);

    equal = Vector( 0.f, 0.f ) == vf - vf;
    CHECK(equal);

    equal = Vector( -2.f, 20.f ) == vf * 2.f;
    CHECK(equal);

    equal = Vector( -2.f, 20.f ) == 2.f * vf;
    CHECK(equal);

    equal = Vector( -0.5f, 5.f ) == vf / 2.f;
    CHECK(equal);

    equal = Vector( 1.f, 10.f ) == Abs( vf );
    CHECK(equal);

    equal = vf == Ceil( Vector( -1.5f, 9.9f ) );
    CHECK(equal);

    equal = vf == Floor( Vector( -.5f, 10.01f ) );
    CHECK(equal);

    equal = Vector( -20.f, 10.f ) == Min( vf, Vector( -20.f, 20.f ) );
    CHECK(equal);

    equal = Vector( -1.f, 20.f ) == Max( vf, Vector( -20.f, 20.f ) );
    CHECK(equal);

    equal = -1.f == MinComponentValue( vf );
    CHECK(equal);

    equal = -10.f == MinComponentValue( -vf );
    CHECK(equal);

    equal = 10.f == MaxComponentValue( vf );
    CHECK(equal);

    equal = 1.f == MaxComponentValue( -vf );
    CHECK(equal);

    equal = 1 == MaxComponentIndex( vf );
    CHECK(equal);

    equal = 0 == MaxComponentIndex( -vf );
    CHECK(equal);

    equal = 0 == MinComponentIndex( vf );
    CHECK(equal);

    equal = 1 == MinComponentIndex( -vf );
    CHECK(equal);

    equal = vf == Permute<0b01'00>( vf );
    CHECK(equal);

    equal = Vector( 10, -1 ) == Permute<0b00'01>( vf );
    CHECK(equal);

    equal = Vector( 10, 10 ) == Permute<0b01'01>( vf );
    CHECK(equal);
}
TEST_CASE("MathVector2FloatTests / OuterProductTest", "[math][MathVector2FloatTests]")
{
    Vector2f a( 1, 2 );
    Vector2f b( 3, 4);
    SquareMatrix<float,2> m = OuterProduct( a, b );
    auto m00 = m[ 0 ][ 0 ];
    auto m01 = m[ 0 ][ 1 ];
    auto m10 = m[ 1 ][ 0 ];
    auto m11 = m[ 1 ][ 1 ];

    CHECK(m00 == 3);
    CHECK(m01 == 4);
    CHECK(m10 == 6);
    CHECK(m11 == 8);
}
