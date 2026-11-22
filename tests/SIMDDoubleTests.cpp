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

namespace SIMD = Harlinn::Math::SIMD;

namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };

}
TEST_CASE("SIMDDoubleTests / Set1Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 2>;
    auto rmm1 = Traits::Set( 1 );
    alignas( Traits::AlignAs ) std::array<double, 2> result;
    Traits::Store( result.data( ), rmm1 );
    
    CHECK(result[ 0 ] == 1.0);
    CHECK(result[ 1 ] == 0.0);
}
TEST_CASE("SIMDDoubleTests / Set1Test2", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 4>;
    auto rmm1 = Traits::Set( 1 );
    alignas( Traits::AlignAs ) std::array<double, 4> result;
    Traits::Store( result.data( ), rmm1 );

    CHECK(result[ 0 ] == 1.0);
    CHECK(result[ 1 ] == 0.0);
    CHECK(result[ 2 ] == 0.0);
    CHECK(result[ 3 ] == 0.0);
}
TEST_CASE("SIMDDoubleTests / Set2Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 2>;
    auto rmm1 = Traits::Set( 2, 1 );
    alignas( Traits::AlignAs ) std::array<double, 2> result;
    Traits::Store( result.data( ), rmm1 );

    CHECK(result[ 0 ] == 1.0);
    CHECK(result[ 1 ] == 2.0);
}
TEST_CASE("SIMDDoubleTests / Set2Test2", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 4>;
    auto rmm1 = Traits::Set( 2, 1 );
    alignas( Traits::AlignAs ) std::array<double, 4> result;
    Traits::Store( result.data( ), rmm1 );

    CHECK(result[ 0 ] == 1.0);
    CHECK(result[ 1 ] == 2.0);
    CHECK(result[ 2 ] == 0.0);
    CHECK(result[ 3 ] == 0.0);
}
TEST_CASE("SIMDDoubleTests / Set3Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 4>;
    auto rmm1 = Traits::Set( 3, 2, 1 );
    alignas( Traits::AlignAs ) std::array<double, 4> result;
    Traits::Store( result.data( ), rmm1 );

    CHECK(result[ 0 ] == 1.0);
    CHECK(result[ 1 ] == 2.0);
    CHECK(result[ 2 ] == 3.0);
    CHECK(result[ 3 ] == 0.0);
}
TEST_CASE("SIMDDoubleTests / Set4Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 4>;
    auto rmm1 = Traits::Set( 4, 3, 2, 1 );
    alignas( Traits::AlignAs ) std::array<double, 4> result;
    Traits::Store( result.data( ), rmm1 );

    CHECK(result[ 0 ] == 1.0);
    CHECK(result[ 1 ] == 2.0);
    CHECK(result[ 2 ] == 3.0);
    CHECK(result[ 3 ] == 4.0);
}
TEST_CASE("SIMDDoubleTests / HorizontalMin1Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 1>;
    auto rmm1 = Traits::Set( -3 );
    auto minValue = Traits::HorizontalMin( rmm1 );

    CHECK(minValue == -3.f);
}
TEST_CASE("SIMDDoubleTests / HorizontalMin2Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 2>;
    auto rmm1 = Traits::Set( -3, 1 );
    auto minValue = Traits::HorizontalMin( rmm1 );

    CHECK(minValue == -3.f);
}
TEST_CASE("SIMDDoubleTests / HorizontalMin3Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 3>;
    auto rmm1 = Traits::Set( -3, 100, 1 );
    auto minValue = Traits::HorizontalMin( rmm1 );

    CHECK(minValue == -3.f);
}
TEST_CASE("SIMDDoubleTests / HorizontalMin4Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 4>;
    auto rmm1 = Traits::Set( -3, 0, 100, 1 );
    auto minValue = Traits::HorizontalMin( rmm1 );

    CHECK(minValue == -3.f);
}
TEST_CASE("SIMDDoubleTests / HorizontalMax1Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 1>;
    auto rmm1 = Traits::Set( -3 );
    auto maxValue = Traits::HorizontalMax( rmm1 );

    CHECK(maxValue == -3.f);
}
TEST_CASE("SIMDDoubleTests / HorizontalMax2Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 2>;
    auto rmm1 = Traits::Set( -3, 1 );
    auto maxValue = Traits::HorizontalMax( rmm1 );

    CHECK(maxValue == 1.f);
}
TEST_CASE("SIMDDoubleTests / HorizontalMax3Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 3>;
    auto rmm1 = Traits::Set( -3, 100, 1 );
    auto maxValue = Traits::HorizontalMax( rmm1 );

    CHECK(maxValue == 100.f);
}
TEST_CASE("SIMDDoubleTests / HorizontalMax4Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 4>;
    auto rmm1 = Traits::Set( 101, -40, 100, 1 );
    auto maxValue = Traits::HorizontalMax( rmm1 );

    CHECK(maxValue == 101.f);
}
TEST_CASE("SIMDDoubleTests / HSum1Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 1>;
    auto expected = -3.f;
    auto rmm1 = Traits::Set( expected );
    auto rmm2 = Traits::HSum( rmm1 );

    auto result = Traits::ToArray( rmm2 );

    CHECK(result[ 0 ] == expected);
}
TEST_CASE("SIMDDoubleTests / HSum2Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 2>;
    auto expected = -3.f + 5;
    auto rmm1 = Traits::Set( -3.f, 5.f );
    auto rmm2 = Traits::HSum( rmm1 );

    auto result = Traits::ToArray( rmm2 );

    CHECK(result[ 0 ] == expected);
    CHECK(result[ 1 ] == expected);
}
TEST_CASE("SIMDDoubleTests / HSum3Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 3>;
    auto rmm1 = Traits::Set( 7, 3, 1 );
    auto rmm2 = Traits::HSum( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    CHECK(result[ 0 ] == 11.0);
    CHECK(result[ 1 ] == 11.0);
    CHECK(result[ 2 ] == 11.0);
}
TEST_CASE("SIMDDoubleTests / HSum4Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 4>;
    auto rmm1 = Traits::Set( 21, 7, 3, 1 );
    auto rmm2 = Traits::HSum( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    CHECK(result[ 0 ] == 32.0);
    CHECK(result[ 1 ] == 32.0);
    CHECK(result[ 2 ] == 32.0);
    CHECK(result[ 3 ] == 32.0);
}
TEST_CASE("SIMDDoubleTests / Equal1Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 1>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1 } );
    ArrayType arg2( { 1 } );
    ArrayType arg3( { -1 } );

    
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Load( arg3 );
    auto equal = Traits::AllEqual( rmm1, rmm2 );

    CHECK(equal);

    equal = Traits::AllEqual( rmm1, rmm3 );

    CHECK(equal == false);
}
TEST_CASE("SIMDDoubleTests / Equal2Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 2>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1, 2 } );
    ArrayType arg2( { 1, 2 } );
    ArrayType arg3( { -1, 2 } );


    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Load( arg3 );
    auto equal = Traits::AllEqual( rmm1, rmm2 );

    CHECK(equal);

    equal = Traits::AllEqual( rmm1, rmm3 );

    CHECK(equal == false);
}
TEST_CASE("SIMDDoubleTests / Equal3Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 3>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1, 2, 3 } );
    ArrayType arg2( { 1, 2, 3 } );
    ArrayType arg3( { -1, 2, 3 } );


    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Load( arg3 );
    auto equal = Traits::AllEqual( rmm1, rmm2 );

    CHECK(equal);

    equal = Traits::AllEqual( rmm1, rmm3 );

    CHECK(equal == false);
}
TEST_CASE("SIMDDoubleTests / Equal4Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 4>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1, 2, 3, 4 } );
    ArrayType arg2( { 1, 2, 3, 4 } );
    ArrayType arg3( { -1, 2, 3, 4 } );


    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Load( arg3 );
    auto equal = Traits::AllEqual( rmm1, rmm2 );

    CHECK(equal);

    equal = Traits::AllEqual( rmm1, rmm3 );

    CHECK(equal == false);
}
TEST_CASE("SIMDDoubleTests / Add1Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 1>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1 } );
    ArrayType arg2( { 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] + arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Add( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result == expected);
}
TEST_CASE("SIMDDoubleTests / Add2Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 2>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 3, 1 } );
    ArrayType arg2( { 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] + arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Add( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result == expected);
}
TEST_CASE("SIMDDoubleTests / Add3Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 3>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 5, 3, 1 } );
    ArrayType arg2( { 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] + arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Add( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result == expected);
}
TEST_CASE("SIMDDoubleTests / Add4Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 4>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 7, 5, 3, 1 } );
    ArrayType arg2( { 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] + arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Add( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result == expected);
}
TEST_CASE("SIMDDoubleTests / Sub1Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 1>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1 } );
    ArrayType arg2( { 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] - arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Sub( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result == expected);
}
TEST_CASE("SIMDDoubleTests / Sub2Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 2>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 3, 1 } );
    ArrayType arg2( { 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] - arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Sub( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result == expected);
}
TEST_CASE("SIMDDoubleTests / Sub3Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 3>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 5, 3, 1 } );
    ArrayType arg2( { 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] - arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Sub( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result == expected);
}
TEST_CASE("SIMDDoubleTests / Sub4Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 4>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 7, 5, 3, 1 } );
    ArrayType arg2( { 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] - arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Sub( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result == expected);
}
TEST_CASE("SIMDDoubleTests / Mul1Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 1>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1 } );
    ArrayType arg2( { 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] * arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Mul( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result == expected);
}
TEST_CASE("SIMDDoubleTests / Mul2Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 2>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 3, 1 } );
    ArrayType arg2( { 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] * arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Mul( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result == expected);
}
TEST_CASE("SIMDDoubleTests / Mul3Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 3>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 5, 3, 1 } );
    ArrayType arg2( { 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] * arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Mul( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result == expected);
}
TEST_CASE("SIMDDoubleTests / Mul4Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 4>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 7, 5, 3, 1 } );
    ArrayType arg2( { 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] * arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Mul( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result == expected);
}
TEST_CASE("SIMDDoubleTests / Div1Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 1>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1 } );
    ArrayType arg2( { 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] / arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Div( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result == expected);
}
TEST_CASE("SIMDDoubleTests / Div2Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 2>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 3, 1 } );
    ArrayType arg2( { 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] / arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Div( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result == expected);
}
TEST_CASE("SIMDDoubleTests / Div3Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 3>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 5, 3, 1 } );
    ArrayType arg2( { 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] / arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Div( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result == expected);
}
TEST_CASE("SIMDDoubleTests / Div4Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 4>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 7, 5, 3, 1 } );
    ArrayType arg2( { 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] / arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Div( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result == expected);
}
TEST_CASE("SIMDDoubleTests / AddSub1Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 1>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1 } );
    ArrayType arg2( { 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = i % 2 ? arg1[ i ] + arg2[ i ] : arg1[ i ] - arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::AddSub( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result == expected);
}
TEST_CASE("SIMDDoubleTests / AddSub2Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 2>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 3, 1 } );
    ArrayType arg2( { 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = i % 2 ? arg1[ i ] + arg2[ i ] : arg1[ i ] - arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::AddSub( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result == expected);
}
TEST_CASE("SIMDDoubleTests / AddSub3Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 3>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 5, 3, 1 } );
    ArrayType arg2( { 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = i % 2 ? arg1[ i ] + arg2[ i ] : arg1[ i ] - arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::AddSub( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result == expected);
}
TEST_CASE("SIMDDoubleTests / AddSub4Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 4>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 7, 5, 3, 1 } );
    ArrayType arg2( { 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = i % 2 ? arg1[ i ] + arg2[ i ] : arg1[ i ] - arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::AddSub( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result == expected);
}
TEST_CASE("SIMDDoubleTests / Abs1Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 1>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1 } );
    ArrayType expected{ 1 };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm3 = Traits::Abs( rmm1 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result == expected);
}
TEST_CASE("SIMDDoubleTests / Abs2Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 2>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ) } );
    ArrayType expected{ 1, 0 };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm3 = Traits::Abs( rmm1 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result == expected);
}
TEST_CASE("SIMDDoubleTests / Abs3Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 3>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity( ) } );
    ArrayType expected{ 1, 0, std::numeric_limits<typename Traits::Type>::infinity( ) };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm3 = Traits::Abs( rmm1 );

    auto result = Traits::ToArray( rmm3 );
    for ( size_t i = 0; i < expected.size( ); i++ )
    {
        if ( Math::IsNaN( result[ i ] ) )
        {
            CHECK(Math::IsNaN( expected[ i ] ));
        }
        else
        {
            CHECK(result[ i ] == expected[ i ]);
        }
    }
}
TEST_CASE("SIMDDoubleTests / Abs4Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 4>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ) } );
    ArrayType expected{ 1, 0, std::numeric_limits<typename Traits::Type>::infinity( ),std::numeric_limits<typename Traits::Type>::quiet_NaN( ) };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm3 = Traits::Abs( rmm1 );

    auto result = Traits::ToArray( rmm3 );
    for ( size_t i = 0; i < expected.size( ); i++ )
    {
        if ( Math::IsNaN( result[ i ] ) )
        {
            CHECK(Math::IsNaN( expected[ i ] ));
        }
        else
        {
            CHECK(result[ i ] == expected[ i ]);
        }
    }
}
TEST_CASE("SIMDDoubleTests / Min1Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 1>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1 } );
    ArrayType arg2( { 1 } );
    ArrayType expected{ -1 };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Min( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result == expected);
}
TEST_CASE("SIMDDoubleTests / Min2Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 2>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ) } );
    ArrayType arg2( { -1, ( 0.f ) } );
    ArrayType expected{ -1, -0.f };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Min( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result == expected);
}
TEST_CASE("SIMDDoubleTests / Min3Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 3>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity( ) } );
    ArrayType arg2( { -1, ( 0.f ), std::numeric_limits<typename Traits::Type>::infinity( ) } );
    ArrayType expected{ -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity( ) };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Min( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );
    for ( size_t i = 0; i < expected.size( ); i++ )
    {
        if ( Math::IsNaN( result[ i ] ) )
        {
            CHECK(Math::IsNaN( expected[ i ] ));
        }
        else
        {
            CHECK(result[ i ] == expected[ i ]);
        }
    }
}
TEST_CASE("SIMDDoubleTests / Min4Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 4>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ) } );
    ArrayType arg2( { 1, ( 0.f ), std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ) } );
    ArrayType expected{ -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity( ),std::numeric_limits<typename Traits::Type>::quiet_NaN( ) };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Min( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );
    for ( size_t i = 0; i < expected.size( ); i++ )
    {
        if ( Math::IsNaN( result[ i ] ) )
        {
            CHECK(Math::IsNaN( expected[ i ] ));
        }
        else
        {
            CHECK(result[ i ] == expected[ i ]);
        }
    }
}
TEST_CASE("SIMDDoubleTests / Max1Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 1>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1 } );
    ArrayType arg2( { 1 } );
    ArrayType expected{ 1 };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Max( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result == expected);
}
TEST_CASE("SIMDDoubleTests / Max2Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 2>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ) } );
    ArrayType arg2( { 1, ( 0.f ) } );
    ArrayType expected{ 1, 0.f };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Max( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    CHECK(result == expected);
}
TEST_CASE("SIMDDoubleTests / Max3Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 3>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity( ) } );
    ArrayType arg2( { 1, ( 0.f ), std::numeric_limits<typename Traits::Type>::infinity( ) } );
    ArrayType expected{ 1, ( 0.f ), std::numeric_limits<typename Traits::Type>::infinity( ) };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Max( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );
    for ( size_t i = 0; i < expected.size( ); i++ )
    {
        if ( Math::IsNaN( result[ i ] ) )
        {
            CHECK(Math::IsNaN( expected[ i ] ));
        }
        else
        {
            CHECK(result[ i ] == expected[ i ]);
        }
    }
}
TEST_CASE("SIMDDoubleTests / Max4Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 4>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ) } );
    ArrayType arg2( { 1, ( 0.f ), std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ) } );
    ArrayType expected{ 1, ( 0.f ), std::numeric_limits<typename Traits::Type>::infinity( ),std::numeric_limits<typename Traits::Type>::quiet_NaN( ) };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Max( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );
    for ( size_t i = 0; i < expected.size( ); i++ )
    {
        if ( Math::IsNaN( result[ i ] ) )
        {
            CHECK(Math::IsNaN( expected[ i ] ));
        }
        else
        {
            CHECK(result[ i ] == expected[ i ]);
        }
    }
}
TEST_CASE("SIMDDoubleTests / Lerp1Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 1>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 12 } );
    ArrayType arg2( { 0 } );
    ArrayType arg3( { 0.5 } );
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Load( arg3 );
    auto rmm4 = Traits::Lerp( rmm1, rmm2, rmm3 );

    auto result = Traits::ToArray( rmm4 );

    for ( size_t i = 0; i < result.size( ); i++ )
    {
        auto val = std::lerp( arg1[ i ], arg2[ i ], arg3[ i ] );
        if ( Math::IsNaN( result[ i ] ) )
        {
            CHECK(Math::IsNaN( val ));
        }
        else
        {
            CHECK(result[ i ] == val);
        }
    }
}
TEST_CASE("SIMDDoubleTests / Lerp2Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 2>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 12, 0 } );
    ArrayType arg2( { 0, 12 } );
    ArrayType arg3( { 0.5, 1 } );
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Load( arg3 );
    auto rmm4 = Traits::Lerp( rmm1, rmm2, rmm3 );

    auto result = Traits::ToArray( rmm4 );

    for ( size_t i = 0; i < result.size( ); i++ )
    {
        auto val = std::lerp( arg1[ i ], arg2[ i ], arg3[ i ] );
        if ( Math::IsNaN( result[ i ] ) )
        {
            CHECK(Math::IsNaN( val ));
        }
        else
        {
            CHECK(result[ i ] == val);
        }
    }
}
TEST_CASE("SIMDDoubleTests / Lerp3Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 3>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 12, 5, 12 } );
    ArrayType arg2( { 34, 12, 3 } );
    ArrayType arg3( { 0.5, 1.5, .5f } );
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Load( arg3 );
    auto rmm4 = Traits::Lerp( rmm1, rmm2, rmm3 );

    auto result = Traits::ToArray( rmm4 );

    for ( size_t i = 0; i < result.size( ); i++ )
    {
        auto val = std::lerp( arg1[ i ], arg2[ i ], arg3[ i ] );
        if ( Math::IsNaN( result[ i ] ) )
        {
            CHECK(Math::IsNaN( val ));
        }
        else
        {
            CHECK(result[ i ] == val);
        }
    }
}
TEST_CASE("SIMDDoubleTests / Lerp4Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 4>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 12, 5, 12, 5 } );
    ArrayType arg2( { 34, 12, 3, -4 } );
    ArrayType arg3( { 0.5, 1.5, .5f, -0.5f } );
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Load( arg3 );
    auto rmm4 = Traits::Lerp( rmm1, rmm2, rmm3 );

    auto result = Traits::ToArray( rmm4 );

    for ( size_t i = 0; i < result.size( ); i++ )
    {
        auto val = std::lerp( arg1[ i ], arg2[ i ], arg3[ i ] );
        if ( Math::IsNaN( result[ i ] ) )
        {
            CHECK(Math::IsNaN( val ));
        }
        else
        {
            CHECK(result[ i ] == val);
        }
    }
}
TEST_CASE("SIMDDoubleTests / HasNaN1Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 1>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { NaN } );
    ArrayType arg2( { 1 } );

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto hasNaN = Traits::HasNaN( rmm1 );
    auto hasNotNaN = Traits::HasNaN( rmm2 ) == false;


    CHECK(hasNaN);
    CHECK(hasNotNaN);
}
TEST_CASE("SIMDDoubleTests / HasNaN2Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 2>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 2, NaN } );
    ArrayType arg2( { 2, 1 } );

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto hasNaN = Traits::HasNaN( rmm1 );
    auto hasNotNaN = Traits::HasNaN( rmm2 ) == false;


    CHECK(hasNaN);
    CHECK(hasNotNaN);
}
TEST_CASE("SIMDDoubleTests / HasNaN3Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 3>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 3, 2, NaN } );
    ArrayType arg2( { 3, 2, 1 } );

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto hasNaN = Traits::HasNaN( rmm1 );
    auto hasNotNaN = Traits::HasNaN( rmm2 ) == false;


    CHECK(hasNaN);
    CHECK(hasNotNaN);
}
TEST_CASE("SIMDDoubleTests / HasNaN4Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 4>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 4, 3, 2, NaN } );
    ArrayType arg2( { 4, 3, 2, 1 } );

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto hasNaN = Traits::HasNaN( rmm1 );
    auto hasNotNaN = Traits::HasNaN( rmm2 ) == false;

    CHECK(hasNaN);
    CHECK(hasNotNaN);
}
TEST_CASE("SIMDDoubleTests / HProd1Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 1>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 2.0 } );
    auto one = static_cast< Type >( 1 );
    Type value = one;
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        value *= arg1[ i ];
    }
    ArrayType expected;
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = value;
    }

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::HProd( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    CHECK(result == expected);
}
TEST_CASE("SIMDDoubleTests / HProd2Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 2>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 2.0, 3.1 } );
    auto one = static_cast< Type >( 1 );
    Type value = one;
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        value *= arg1[ i ];
    }
    ArrayType expected;
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = value;
    }

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::HProd( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    CHECK(result == expected);
}
TEST_CASE("SIMDDoubleTests / HProd3Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 3>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 2.0, 3.1, -1.7 } );
    auto one = static_cast< Type >( 1 );
    Type value = one;
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        value *= arg1[ i ];
    }
    ArrayType expected;
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = value;
    }

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::HProd( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    CHECK(result == expected);
}
TEST_CASE("SIMDDoubleTests / HProd4Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 4>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 2.0, 3.1, -1.7, -3.9 } );
    auto one = static_cast< Type >( 1 );
    Type value = one;
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        value *= arg1[ i ];
    }
    ArrayType expected;
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = value;
    }

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::HProd( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        CHECK((expected[ i ]) == Catch::Approx(result[ i ]).epsilon((0.001f) / 100.0));
    }
}
TEST_CASE("SIMDDoubleTests / At1Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 1>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1.f } );
    auto expected = Traits::Fill( 1.f );
    auto rmm1 = Traits::Load( arg1 );
    auto rmmAt = Traits::At<0>( rmm1 );
    auto equal = Traits::AllEqual( rmmAt, expected );
    CHECK(equal);
}
TEST_CASE("SIMDDoubleTests / At2Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 2>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1.f, 2.f } );
    auto expected1 = SIMD::Traits<double, 2>::Fill( 1.f );
    auto expected2 = SIMD::Traits<double, 2>::Fill( 2.f );
    auto rmm1 = Traits::Load( arg1 );
    auto rmmAt = Traits::At<0>( rmm1 );
    auto equal = Traits::AllEqual( rmmAt, expected1 );
    CHECK(equal);

    rmmAt = Traits::At<1>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected2 );
    CHECK(equal);
}
TEST_CASE("SIMDDoubleTests / At3Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 3>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1.f, 2.f, 3.f } );
    auto expected1 = SIMD::Traits<double, 4>::Fill( 1.f );
    auto expected2 = SIMD::Traits<double, 4>::Fill( 2.f );
    auto expected3 = SIMD::Traits<double, 4>::Fill( 3.f );
    auto rmm1 = Traits::Load( arg1 );
    auto rmmAt = Traits::At<0>( rmm1 );
    auto equal = Traits::AllEqual( rmmAt, expected1 );
    CHECK(equal);

    rmmAt = Traits::At<1>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected2 );
    CHECK(equal);

    rmmAt = Traits::At<2>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected3 );
    CHECK(equal);
}
TEST_CASE("SIMDDoubleTests / At4Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 4>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1.f, 2.f, 3.f, 4.f } );
    auto expected1 = SIMD::Traits<double, 4>::Fill( 1.f );
    auto expected2 = SIMD::Traits<double, 4>::Fill( 2.f );
    auto expected3 = SIMD::Traits<double, 4>::Fill( 3.f );
    auto expected4 = SIMD::Traits<double, 4>::Fill( 4.f );
    auto rmm1 = Traits::Load( arg1 );
    auto rmmAt = Traits::At<0>( rmm1 );
    auto equal = Traits::AllEqual( rmmAt, expected1 );
    CHECK(equal);

    rmmAt = Traits::At<1>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected2 );
    CHECK(equal);

    rmmAt = Traits::At<2>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected3 );
    CHECK(equal);

    rmmAt = Traits::At<3>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected4 );
    CHECK(equal);
}
TEST_CASE("SIMDDoubleTests / Extract1Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 1>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1.f } );
    auto expected = 1.f;
    auto rmm1 = Traits::Load( arg1 );
    auto extracted = Traits::Extract<0>( rmm1 );
    auto equal = expected == extracted;
    CHECK(equal);
}
TEST_CASE("SIMDDoubleTests / Extract2Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 2>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1.f, 2.f } );
    auto expected1 = 1.f;
    auto expected2 = 2.f;
    auto rmm1 = Traits::Load( arg1 );
    auto extracted = Traits::Extract<0>( rmm1 );
    auto equal = expected1 == extracted;
    CHECK(equal);

    extracted = Traits::Extract<1>( rmm1 );
    equal = expected2 == extracted;
    CHECK(equal);
}
TEST_CASE("SIMDDoubleTests / Extract3Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 3>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1.f, 2.f, 3.f } );
    auto expected1 = 1.f;
    auto expected2 = 2.f;
    auto expected3 = 3.f;
    auto rmm1 = Traits::Load( arg1 );
    auto extracted = Traits::Extract<0>( rmm1 );
    auto equal = expected1 == extracted;
    CHECK(equal);

    extracted = Traits::Extract<1>( rmm1 );
    equal = expected2 == extracted;
    CHECK(equal);

    extracted = Traits::Extract<2>( rmm1 );
    equal = expected3 == extracted;
    CHECK(equal);
}
TEST_CASE("SIMDDoubleTests / Extract4Test1", "[math][SIMDDoubleTests]")
{
    using Traits = SIMD::Traits<double, 4>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1.f, 2.f, 3.f, 4.f } );
    auto expected1 = 1.f;
    auto expected2 = 2.f;
    auto expected3 = 3.f;
    auto expected4 = 4.f;
    auto rmm1 = Traits::Load( arg1 );
    auto extracted = Traits::Extract<0>( rmm1 );
    auto equal = expected1 == extracted;
    CHECK(equal);

    extracted = Traits::Extract<1>( rmm1 );
    equal = expected2 == extracted;
    CHECK(equal);

    extracted = Traits::Extract<2>( rmm1 );
    equal = expected3 == extracted;
    CHECK(equal);

    extracted = Traits::Extract<3>( rmm1 );
    equal = expected4 == extracted;
    CHECK(equal);
}
