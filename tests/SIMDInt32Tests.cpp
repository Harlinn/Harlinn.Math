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

namespace SIMD = Harlinn::Math::SIMD;

namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( )
        { }
        ~LocalFixture( )
        { }
    };

}
TEST_CASE("SIMDInt32Tests / Set1Test1", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 4>;
    auto rmm1 = Traits::Set( 1 );
    alignas( Traits::AlignAs ) std::array<int, 4> result;
    Traits::Store( result.data( ), rmm1 );

    CHECK(result[ 0 ] == 1);
    CHECK(result[ 1 ] == 0);
    CHECK(result[ 2 ] == 0);
    CHECK(result[ 3 ] == 0);
}
TEST_CASE("SIMDInt32Tests / Set1Test2", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 8>;
    auto rmm1 = Traits::Set( 1 );
    alignas( Traits::AlignAs ) std::array<int, 8> result;
    Traits::Store( result.data( ), rmm1 );

    CHECK(result[ 0 ] == 1);
    CHECK(result[ 1 ] == 0);
    CHECK(result[ 2 ] == 0);
    CHECK(result[ 3 ] == 0);
    CHECK(result[ 4 ] == 0);
    CHECK(result[ 5 ] == 0);
    CHECK(result[ 6 ] == 0);
    CHECK(result[ 7 ] == 0);
}
TEST_CASE("SIMDInt32Tests / Set2Test1", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 4>;
    auto rmm1 = Traits::Set( 2, 1 );
    alignas( Traits::AlignAs ) std::array<int, 4> result;
    Traits::Store( result.data( ), rmm1 );

    CHECK(result[ 0 ] == 1);
    CHECK(result[ 1 ] == 2);
    CHECK(result[ 2 ] == 0);
    CHECK(result[ 3 ] == 0);
}
TEST_CASE("SIMDInt32Tests / Set2Test2", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 8>;
    auto rmm1 = Traits::Set( 2, 1 );
    alignas( Traits::AlignAs ) std::array<int, 8> result;
    Traits::Store( result.data( ), rmm1 );

    CHECK(result[ 0 ] == 1);
    CHECK(result[ 1 ] == 2);
    CHECK(result[ 2 ] == 0);
    CHECK(result[ 3 ] == 0);
    CHECK(result[ 4 ] == 0);
    CHECK(result[ 5 ] == 0);
    CHECK(result[ 6 ] == 0);
    CHECK(result[ 7 ] == 0);
}
TEST_CASE("SIMDInt32Tests / Set3Test1", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 4>;
    auto rmm1 = Traits::Set( 3, 2, 1 );
    alignas( Traits::AlignAs ) std::array<int, 4> result;
    Traits::Store( result.data( ), rmm1 );

    CHECK(result[ 0 ] == 1);
    CHECK(result[ 1 ] == 2);
    CHECK(result[ 2 ] == 3);
    CHECK(result[ 3 ] == 0);
}
TEST_CASE("SIMDInt32Tests / Set3Test2", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 8>;
    auto rmm1 = Traits::Set( 3, 2, 1 );
    alignas( Traits::AlignAs ) std::array<int, 8> result;
    Traits::Store( result.data( ), rmm1 );

    CHECK(result[ 0 ] == 1);
    CHECK(result[ 1 ] == 2);
    CHECK(result[ 2 ] == 3);
    CHECK(result[ 3 ] == 0);
    CHECK(result[ 4 ] == 0);
    CHECK(result[ 5 ] == 0);
    CHECK(result[ 6 ] == 0);
    CHECK(result[ 7 ] == 0);
}
TEST_CASE("SIMDInt32Tests / Set4Test1", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 4>;
    auto rmm1 = Traits::Set( 4, 3, 2, 1 );
    alignas( Traits::AlignAs ) std::array<int, 4> result;
    Traits::Store( result.data( ), rmm1 );

    CHECK(result[ 0 ] == 1);
    CHECK(result[ 1 ] == 2);
    CHECK(result[ 2 ] == 3);
    CHECK(result[ 3 ] == 4);
}
TEST_CASE("SIMDInt32Tests / Set4Test2", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 8>;
    auto rmm1 = Traits::Set( 4, 3, 2, 1 );
    alignas( Traits::AlignAs ) std::array<int, 8> result;
    Traits::Store( result.data( ), rmm1 );

    CHECK(result[ 0 ] == 1);
    CHECK(result[ 1 ] == 2);
    CHECK(result[ 2 ] == 3);
    CHECK(result[ 3 ] == 4);
    CHECK(result[ 4 ] == 0);
    CHECK(result[ 5 ] == 0);
    CHECK(result[ 6 ] == 0);
    CHECK(result[ 7 ] == 0);
}
TEST_CASE("SIMDInt32Tests / Set5Test1", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 8>;
    auto rmm1 = Traits::Set( 5, 4, 3, 2, 1 );
    alignas( Traits::AlignAs ) std::array<int, 8> result;
    Traits::Store( result.data( ), rmm1 );

    CHECK(result[ 0 ] == 1);
    CHECK(result[ 1 ] == 2);
    CHECK(result[ 2 ] == 3);
    CHECK(result[ 3 ] == 4);
    CHECK(result[ 4 ] == 5);
    CHECK(result[ 5 ] == 0);
    CHECK(result[ 6 ] == 0);
    CHECK(result[ 7 ] == 0);
}
TEST_CASE("SIMDInt32Tests / Set6Test1", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 8>;
    auto rmm1 = Traits::Set( 6, 5, 4, 3, 2, 1 );
    alignas( Traits::AlignAs ) std::array<int, 8> result;
    Traits::Store( result.data( ), rmm1 );

    CHECK(result[ 0 ] == 1);
    CHECK(result[ 1 ] == 2);
    CHECK(result[ 2 ] == 3);
    CHECK(result[ 3 ] == 4);
    CHECK(result[ 4 ] == 5);
    CHECK(result[ 5 ] == 6);
    CHECK(result[ 6 ] == 0);
    CHECK(result[ 7 ] == 0);
}
TEST_CASE("SIMDInt32Tests / Set7Test1", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 8>;
    auto rmm1 = Traits::Set( 7, 6, 5, 4, 3, 2, 1 );
    alignas( Traits::AlignAs ) std::array<int, 8> result;
    Traits::Store( result.data( ), rmm1 );

    CHECK(result[ 0 ] == 1);
    CHECK(result[ 1 ] == 2);
    CHECK(result[ 2 ] == 3);
    CHECK(result[ 3 ] == 4);
    CHECK(result[ 4 ] == 5);
    CHECK(result[ 5 ] == 6);
    CHECK(result[ 6 ] == 7);
    CHECK(result[ 7 ] == 0);
}
TEST_CASE("SIMDInt32Tests / Set8Test1", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 8>;
    auto rmm1 = Traits::Set( 8, 7, 6, 5, 4, 3, 2, 1 );
    alignas( Traits::AlignAs ) std::array<int, 8> result;
    Traits::Store( result.data( ), rmm1 );

    CHECK(result[ 0 ] == 1);
    CHECK(result[ 1 ] == 2);
    CHECK(result[ 2 ] == 3);
    CHECK(result[ 3 ] == 4);
    CHECK(result[ 4 ] == 5);
    CHECK(result[ 5 ] == 6);
    CHECK(result[ 6 ] == 7);
    CHECK(result[ 7 ] == 8);
}
TEST_CASE("SIMDInt32Tests / SetXTest1", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 4>;
    auto rmm1 = Traits::Zero( );
    rmm1 = Traits::SetX( rmm1, 1 );
    alignas( Traits::AlignAs ) std::array<int, 4> result;
    Traits::Store( result.data( ), rmm1 );

    CHECK(result[ 0 ] == 1);
    CHECK(result[ 1 ] == 0);
    CHECK(result[ 2 ] == 0);
    CHECK(result[ 3 ] == 0);
}
TEST_CASE("SIMDInt32Tests / SetXTest2", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 8>;
    auto rmm1 = Traits::Zero( );
    rmm1 = Traits::SetX( rmm1, 1 );
    alignas( Traits::AlignAs ) std::array<int, 8> result;
    Traits::Store( result.data( ), rmm1 );

    CHECK(result[ 0 ] == 1);
    CHECK(result[ 1 ] == 0);
    CHECK(result[ 2 ] == 0);
    CHECK(result[ 3 ] == 0);
    CHECK(result[ 4 ] == 0);
    CHECK(result[ 5 ] == 0);
    CHECK(result[ 6 ] == 0);
    CHECK(result[ 7 ] == 0);
}
TEST_CASE("SIMDInt32Tests / SetYTest1", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 4>;
    auto rmm1 = Traits::Zero( );
    rmm1 = Traits::SetY( rmm1, 1 );
    alignas( Traits::AlignAs ) std::array<int, 4> result;
    Traits::Store( result.data( ), rmm1 );

    CHECK(result[ 0 ] == 0);
    CHECK(result[ 1 ] == 1);
    CHECK(result[ 2 ] == 0);
    CHECK(result[ 3 ] == 0);
}
TEST_CASE("SIMDInt32Tests / SetYTest2", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 8>;
    auto rmm1 = Traits::Zero( );
    rmm1 = Traits::SetY( rmm1, 1 );
    alignas( Traits::AlignAs ) std::array<int, 8> result;
    Traits::Store( result.data( ), rmm1 );

    CHECK(result[ 0 ] == 0);
    CHECK(result[ 1 ] == 1);
    CHECK(result[ 2 ] == 0);
    CHECK(result[ 3 ] == 0);
    CHECK(result[ 4 ] == 0);
    CHECK(result[ 5 ] == 0);
    CHECK(result[ 6 ] == 0);
    CHECK(result[ 7 ] == 0);
}
TEST_CASE("SIMDInt32Tests / SetZTest1", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 4>;
    auto rmm1 = Traits::Zero( );
    rmm1 = Traits::SetZ( rmm1, 1 );
    alignas( Traits::AlignAs ) std::array<int, 4> result;
    Traits::Store( result.data( ), rmm1 );

    CHECK(result[ 0 ] == 0);
    CHECK(result[ 1 ] == 0);
    CHECK(result[ 2 ] == 1);
    CHECK(result[ 3 ] == 0);
}
TEST_CASE("SIMDInt32Tests / SetZTest2", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 8>;
    auto rmm1 = Traits::Zero( );
    rmm1 = Traits::SetZ( rmm1, 1 );
    alignas( Traits::AlignAs ) std::array<int, 8> result;
    Traits::Store( result.data( ), rmm1 );

    CHECK(result[ 0 ] == 0);
    CHECK(result[ 1 ] == 0);
    CHECK(result[ 2 ] == 1);
    CHECK(result[ 3 ] == 0);
    CHECK(result[ 4 ] == 0);
    CHECK(result[ 5 ] == 0);
    CHECK(result[ 6 ] == 0);
    CHECK(result[ 7 ] == 0);
}
TEST_CASE("SIMDInt32Tests / SetWTest1", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 4>;
    auto rmm1 = Traits::Zero( );
    rmm1 = Traits::SetW( rmm1, 1 );
    alignas( Traits::AlignAs ) std::array<int, 4> result;
    Traits::Store( result.data( ), rmm1 );

    CHECK(result[ 0 ] == 0);
    CHECK(result[ 1 ] == 0);
    CHECK(result[ 2 ] == 0);
    CHECK(result[ 3 ] == 1);
}
TEST_CASE("SIMDInt32Tests / SetWTest2", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 8>;
    auto rmm1 = Traits::Zero( );
    rmm1 = Traits::SetW( rmm1, 1 );
    alignas( Traits::AlignAs ) std::array<int, 8> result;
    Traits::Store( result.data( ), rmm1 );

    CHECK(result[ 0 ] == 0);
    CHECK(result[ 1 ] == 0);
    CHECK(result[ 2 ] == 0);
    CHECK(result[ 3 ] == 1);
    CHECK(result[ 4 ] == 0);
    CHECK(result[ 5 ] == 0);
    CHECK(result[ 6 ] == 0);
    CHECK(result[ 7 ] == 0);
}
TEST_CASE("SIMDInt32Tests / Add1Test1", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 1>;
    auto rmm1 = Traits::Set( 1 );
    auto rmm2 = Traits::Set( 2 );
    auto rmm3 = Traits::Add( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result.size( ) == 1);
    CHECK(result[ 0 ] == 3);
}
TEST_CASE("SIMDInt32Tests / Add2Test1", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 2>;
    auto rmm1 = Traits::Set( 2, 1 );
    auto rmm2 = Traits::Set( 3, 2 );
    auto rmm3 = Traits::Add( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result.size( ) == 2);
    CHECK(result[ 0 ] == 3);
    CHECK(result[ 1 ] == 5);
}
TEST_CASE("SIMDInt32Tests / Add3Test1", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 3>;
    auto rmm1 = Traits::Set( 3, 2, 1 );
    auto rmm2 = Traits::Set( 4, 3, 2 );
    auto rmm3 = Traits::Add( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result.size( ) == 3);
    CHECK(result[ 0 ] == 3);
    CHECK(result[ 1 ] == 5);
    CHECK(result[ 2 ] == 7);
}
TEST_CASE("SIMDInt32Tests / Add4Test1", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 4>;
    auto rmm1 = Traits::Set( 4, 3, 2, 1 );
    auto rmm2 = Traits::Set( 5, 4, 3, 2 );
    auto rmm3 = Traits::Add( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result.size( ) == 4);
    CHECK(result[ 0 ] == 3);
    CHECK(result[ 1 ] == 5);
    CHECK(result[ 2 ] == 7);
    CHECK(result[ 3 ] == 9);
}
TEST_CASE("SIMDInt32Tests / Add5Test1", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 5>;
    auto rmm1 = Traits::Set( 5, 4, 3, 2, 1 );
    auto rmm2 = Traits::Set( 6, 5, 4, 3, 2 );
    auto rmm3 = Traits::Add( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result.size( ) == 5);
    CHECK(result[ 0 ] == 3);
    CHECK(result[ 1 ] == 5);
    CHECK(result[ 2 ] == 7);
    CHECK(result[ 3 ] == 9);
    CHECK(result[ 4 ] == 11);
}
TEST_CASE("SIMDInt32Tests / Add6Test1", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 6>;
    auto rmm1 = Traits::Set( 6, 5, 4, 3, 2, 1 );
    auto rmm2 = Traits::Set( 7, 6, 5, 4, 3, 2 );
    auto rmm3 = Traits::Add( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result.size( ) == 6);
    CHECK(result[ 0 ] == 3);
    CHECK(result[ 1 ] == 5);
    CHECK(result[ 2 ] == 7);
    CHECK(result[ 3 ] == 9);
    CHECK(result[ 4 ] == 11);
    CHECK(result[ 5 ] == 13);
}
TEST_CASE("SIMDInt32Tests / Add7Test1", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 7>;
    auto rmm1 = Traits::Set( 7, 6, 5, 4, 3, 2, 1 );
    auto rmm2 = Traits::Set( 8, 7, 6, 5, 4, 3, 2 );
    auto rmm3 = Traits::Add( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result.size( ) == 7);
    CHECK(result[ 0 ] == 3);
    CHECK(result[ 1 ] == 5);
    CHECK(result[ 2 ] == 7);
    CHECK(result[ 3 ] == 9);
    CHECK(result[ 4 ] == 11);
    CHECK(result[ 5 ] == 13);
    CHECK(result[ 6 ] == 15);
}
TEST_CASE("SIMDInt32Tests / Add8Test1", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 8>;
    auto rmm1 = Traits::Set( 8, 7, 6, 5, 4, 3, 2, 1 );
    auto rmm2 = Traits::Set( 9, 8, 7, 6, 5, 4, 3, 2 );
    auto rmm3 = Traits::Add( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result.size( ) == 8);
    CHECK(result[ 0 ] == 3);
    CHECK(result[ 1 ] == 5);
    CHECK(result[ 2 ] == 7);
    CHECK(result[ 3 ] == 9);
    CHECK(result[ 4 ] == 11);
    CHECK(result[ 5 ] == 13);
    CHECK(result[ 6 ] == 15);
    CHECK(result[ 7 ] == 17);
}
TEST_CASE("SIMDInt32Tests / HSum1Test1", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 1>;
    auto expected = -3.f;
    auto rmm1 = Traits::Set( expected );
    auto rmm2 = Traits::HSum( rmm1 );

    auto result = Traits::ToArray( rmm2 );

    CHECK(result[ 0 ] == expected);
}
TEST_CASE("SIMDInt32Tests / HSum2Test1", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 2>;
    auto expected = -3 + 5;
    auto rmm1 = Traits::Set( -3, 5 );
    auto rmm2 = Traits::HSum( rmm1 );

    auto result = Traits::ToArray( rmm2 );

    CHECK(result[ 0 ] == expected);
    CHECK(result[ 1 ] == expected);
}
TEST_CASE("SIMDInt32Tests / HSum3Test1", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 3>;
    auto rmm1 = Traits::Set( 7, 3, 1 );
    auto rmm2 = Traits::HSum( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    CHECK(result[ 0 ] == 11);
    CHECK(result[ 1 ] == 11);
    CHECK(result[ 2 ] == 11);
}
TEST_CASE("SIMDInt32Tests / HSum4Test1", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 4>;
    auto rmm1 = Traits::Set( 21, 7, 3, 1 );
    auto rmm2 = Traits::HSum( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    CHECK(result[ 0 ] == 32);
    CHECK(result[ 1 ] == 32);
    CHECK(result[ 2 ] == 32);
    CHECK(result[ 3 ] == 32);
}
TEST_CASE("SIMDInt32Tests / HSum5Test1", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 6>;
    auto rmm1 = Traits::Set( 33, 21, 7, 3, 1 );
    auto expected = 33 + 21 + 7 + 3 + 1;
    auto rmm2 = Traits::HSum( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    CHECK(result[ 0 ] == expected);
    CHECK(result[ 1 ] == expected);
    CHECK(result[ 2 ] == expected);
    CHECK(result[ 3 ] == expected);
    CHECK(result[ 4 ] == expected);
}
TEST_CASE("SIMDInt32Tests / HSum6Test1", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 6>;
    auto rmm1 = Traits::Set( 66, 33, 21, 7, 3, 1 );
    auto expected = 66 + 33 + 21 + 7 + 3 + 1;
    auto rmm2 = Traits::HSum( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    CHECK(result[ 0 ] == expected);
    CHECK(result[ 1 ] == expected);
    CHECK(result[ 2 ] == expected);
    CHECK(result[ 3 ] == expected);
    CHECK(result[ 4 ] == expected);
    CHECK(result[ 5 ] == expected);
}
TEST_CASE("SIMDInt32Tests / HSum7Test1", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 7>;
    auto rmm1 = Traits::Set( 133, 66, 33, 21, 7, 3, 1 );
    auto expected = 133 + 66 + 33 + 21 + 7 + 3 + 1;
    auto rmm2 = Traits::HSum( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    CHECK(result[ 0 ] == expected);
    CHECK(result[ 1 ] == expected);
    CHECK(result[ 2 ] == expected);
    CHECK(result[ 3 ] == expected);
    CHECK(result[ 4 ] == expected);
    CHECK(result[ 5 ] == expected);
    CHECK(result[ 6 ] == expected);
}
TEST_CASE("SIMDInt32Tests / HSum8Test1", "[math][SIMDInt32Tests]")
{
    using Traits = SIMD::Traits<int, 8>;
    auto rmm1 = Traits::Set( -234, 133, 66, 33, 21, 7, 3, 1 );
    auto expected = -234 + 133 + 66 + 33 + 21 + 7 + 3 + 1;
    auto rmm2 = Traits::HSum( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    CHECK(result[ 0 ] == expected);
    CHECK(result[ 1 ] == expected);
    CHECK(result[ 2 ] == expected);
    CHECK(result[ 3 ] == expected);
    CHECK(result[ 4 ] == expected);
    CHECK(result[ 5 ] == expected);
    CHECK(result[ 6 ] == expected);
    CHECK(result[ 7 ] == expected);
}
