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

using Constants = Math::Constants<float>;
using Quaternion = Math::Quaternion<float>;
using Q = Math::Quaternion<float>;

namespace
{
    

    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };

    inline bool Equal( const Q& q1, const Q& q2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 4; i++ )
        {
            auto v1 = q1[ i ];
            float v2 = q2[ i ];
            auto delta = v1 - v2;
            if ( !( std::abs( delta ) <= epsilon ) )
            {
                return false;
            }
        }
        return true;
    }

    template<size_t Count>
    inline bool Equal( const Math::Vector<float, Count>& q1, const Math::Vector<float, Count>& q2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < Count; i++ )
        {
            if ( !( std::abs( q1[ i ] - q2[ i ] ) <= epsilon ) )
            {
                return false;
            }
        }
        return true;
    }





}
TEST_CASE("QuaternionTests / AddTest1", "[math][QuaternionTests]")
{
    Q q1( 3.f, 3.f, 3.f, 3.f );
    Q q2( 2.f, 2.f, 2.f, 2.f );
    Q expected( 5.f, 5.f, 5.f, 5.f );

    Q result = q1 + q2;

    auto equal = Equal( result, expected );
    
    CHECK(equal);
}
TEST_CASE("QuaternionTests / SubtractTest1", "[math][QuaternionTests]")
{
    Q q1( 3.f, 3.f, 3.f, 3.f );
    Q q2( 2.f, 2.f, 2.f, 2.f );
    Q expected( 1.f, 1.f, 1.f, 1.f );

    Q result = q1 - q2;

    auto equal = Equal( result, expected );

    CHECK(equal);

}
TEST_CASE("QuaternionTests / AddScalarTest1", "[math][QuaternionTests]")
{
    Q q1( 1.f, 2.f, 3.f, 4.f );
    float v1 = 2.f;
    float v2 = 3.f;
    Q expected1( 1.f, 2.f, 3.f, 6.f );
    Q expected2( 1.f, 2.f, 3.f, 7.f );

    Q result1 = q1 + v1;
    Q result2 = v2 + q1;

    auto equal = Equal( result1, expected1 );

    CHECK(equal);

    equal = Equal( result2, expected2 );

    CHECK(equal);
}
TEST_CASE("QuaternionTests / SubtractScalarTest1", "[math][QuaternionTests]")
{
    Q q1( 1.f, 2.f, 3.f, 4.f );
    float v1 = 2.f;
    float v2 = 3.f;
    Q expected1( 1.f, 2.f, 3.f, 2.f );
    Q expected2( -1.f, -2.f, -3.f, -1.f );

    Q result1 = q1 - v1;
    Q result2 = v2 - q1;

    auto equal = Equal( result1, expected1 );

    CHECK(equal);

    equal = Equal( result2, expected2 );

    CHECK(equal);
}
TEST_CASE("QuaternionTests / MultiplyTest1", "[math][QuaternionTests]")
{
    Q q1( 2.f, 3.f, 4.f, 1.f );
    Q q2( 8.f, 7.f, 6.f, 9.f );
    Q expected( 36.f, 14.f, 52.f, -52.f );

    Q result = q1 * q2;

    auto equal = Equal( result, expected );

    CHECK(equal);
}
TEST_CASE("QuaternionTests / MultiplyTest2", "[math][QuaternionTests]")
{
    Q q1( -22.1869278f, -22.1869278f, -49.2577934f, 0.f );
    Q q2( 0.0632871166f, -0.303319544f, -0.0201944206f, 0.950570464f );
    Q expected( -6.59743977f, -17.5248032f, -54.9568787f, -6.32031488f );

    Q result = q1 * q2;

    auto equal = Equal( result, expected );

    CHECK(equal);
}
TEST_CASE("QuaternionTests / MultiplyScalarTest1", "[math][QuaternionTests]")
{
    Q q1( 1.f, 2.f, 3.f, 4.f );
    float v1 = 2.f;
    float v2 = 3.f;
    Q expected1( 2.f, 4.f, 6.f, 8.f );
    Q expected2( 3.f, 6.f, 9.f, 12.f );

    Q result1 = q1 * v1;
    Q result2 = v2 * q1;

    auto equal = Equal( result1, expected1 );

    CHECK(equal);

    equal = Equal( result2, expected2 );

    CHECK(equal);
}
TEST_CASE("QuaternionTests / DivisionScalarTest1", "[math][QuaternionTests]")
{
    Q q1( 1.f, 2.f, 3.f, 4.f );
    float v1 = 2.f;
    float v2 = 3.f;
    Q expected1( 1.f / 2.f, 2.f / 2.f, 3.f / 2.f, 4.f / 2.f );
    Q expected2( -0.1f, -0.2f, -0.3f, 0.4f );

    Q result1 = q1 / v1;
    Q result2 = v2 / q1;

    auto equal = Equal( result1, expected1 );

    CHECK(equal);

    equal = Equal( result2, expected2 );

    CHECK(equal);
    CHECK( Equal( Q( result2 * q1 ), Q( 0.f, 0.f, 0.f, v2 ) ) );
}
TEST_CASE("QuaternionTests / DotTest1", "[math][QuaternionTests]")
{
    Q q1( 2.f, 3.f, 4.f, 1.f );
    Q q2( 8.f, 7.f, 6.f, 9.f );

    Math::Vector<float, 4> expected( 70.f, 70.f, 70.f, 70.f );

    Math::Vector<float, 4> result = Math::Vector<float, 4>::Simd(Dot( q1, q2 ).simd);

    auto equal = Equal( result, expected );

    CHECK(equal);
}
TEST_CASE("QuaternionTests / LengthSquaredTest1", "[math][QuaternionTests]")
{
    Q q1( 2.f, 3.f, 4.f, 1.f );

    Math::Vector<float, 4> expected( 30.f, 30.f, 30.f, 30.f );

    Math::Vector<float, 4> result = Math::Vector<float, 4>::Simd( LengthSquared( q1 ).simd);

    auto equal = Equal( result, expected );

    CHECK(equal);
}
TEST_CASE("QuaternionTests / LengthTest1", "[math][QuaternionTests]")
{
    Q q1( 2.f, 3.f, 4.f, 1.f );

    Math::Vector<float, 4> expected( 5.47722578f, 5.47722578f, 5.47722578f, 5.47722578f );

    Math::Vector<float, 4> result = Math::Vector<float, 4>::Simd( Length( q1 ).simd );

    auto equal = Equal( result, expected );

    CHECK(equal);
}
TEST_CASE("QuaternionTests / ReciprocalLengthTest1", "[math][QuaternionTests]")
{
    Q q1( 2.f, 3.f, 4.f, 1.f );

    Math::Vector<float, 4> expected( 0.182574183f, 0.182574183f, 0.182574183f, 0.182574183f );

    Math::Vector<float, 4> result = Math::Vector<float, 4>::Simd( ReciprocalLength( q1 ).simd );

    auto equal = Equal( result, expected );

    CHECK(equal);
}
TEST_CASE("QuaternionTests / NormalizeTest1", "[math][QuaternionTests]")
{
    Q q1( 2.f, 3.f, 4.f, 1.f );

    Q expected( 0.365148365f, 0.547722518f, 0.730296731f, 0.182574183f );

    Q result = Normalize( q1 );

    auto equal = Equal( result, expected );

    CHECK(equal);
}
TEST_CASE("QuaternionTests / ConjugateTest1", "[math][QuaternionTests]")
{
    Q q1( 2.f, 3.f, 4.f, 1.f );

    Q expected( -2.f, -3.f, -4.f, 1.f );

    Q result = Conjugate( q1 );

    auto equal = Equal( result, expected );

    CHECK(equal);
}
TEST_CASE("QuaternionTests / InverseTest1", "[math][QuaternionTests]")
{
    Q q1( 2.f, 3.f, 4.f, 1.f );

    Q expected( -0.0666666701f, -0.100000001f, -0.133333340f, 0.0333333351f );

    Q result = Inverse( q1 );

    auto equal = Equal( result, expected );

    CHECK(equal);
}
TEST_CASE("QuaternionTests / SlerpTest1", "[math][QuaternionTests]")
{
    Q q1( 2.f, 3.f, 4.f, 1.f );
    Q q2( 8.f, 7.f, 6.f, 9.f );

    Q expected( 0.429141968f, 0.539775491f, 0.650409102f, 0.318508387f );

    auto q1n = Normalize( q1 );
    auto q2n = Normalize( q2 );

    Q result = Slerp( q1n, q2n, 0.3f );

    auto equal = Equal( result, expected );

    CHECK(equal);
}
TEST_CASE("QuaternionTests / Slerp follows the shortest arc", "[math][QuaternionTests]")
{
    const Q identity( 0.f, 0.f, 0.f, 1.f );
    const Q target( static_cast<float>( std::sin( std::acos( -1.0 ) / 3.0 ) ), 0.f, 0.f, 0.5f );
    const Q opposite( -target[ 0 ], -target[ 1 ], -target[ 2 ], -target[ 3 ] );
    const Q quarter( static_cast<float>( std::sin( std::acos( -1.0 ) / 12.0 ) ), 0.f, 0.f,
        static_cast<float>( std::cos( std::acos( -1.0 ) / 12.0 ) ) );
    CHECK( Equal( Q( Slerp( identity, target, 0.f ) ), identity ) );
    CHECK( Equal( Q( Slerp( identity, target, 1.f ) ), target ) );
    CHECK( Equal( Q( Slerp( identity, target, 0.25f ) ), quarter ) );
    CHECK( Equal( Q( Slerp( identity, opposite, 0.25f ) ), quarter ) );
    CHECK( Equal( Q( Slerp( identity, identity, 0.5f ) ), identity ) );
    const Math::Vector<float, 4> t( 0.25f, 0.25f, 0.25f, 0.25f );
    CHECK( Equal( Q( Slerp( identity, target, t ) ), quarter ) );
}
TEST_CASE("QuaternionTests / XMQuaternionRotateTest1", "[math][QuaternionTests]")
{
    Math::Vector<float, 3> vec( -22.186928, -22.186928, -49.257793 );
    Q rotation( -0.06328712, 0.30331954, 0.02019442, 0.95057046 );
    Math::Vector<float, 3> expected( -44.661453, -28.521133, -24.550959 );

    Math::Vector<float, 3> result = Math::Rotate( vec, rotation );

    auto equal = Equal( result, expected );

    CHECK(equal);

}




/*

*/
