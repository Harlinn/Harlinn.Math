#include <catch2/catch_test_macros.hpp>
#include <harlinn/math/VectorMath.h>

#include <cfenv>
#include <cfloat>
#include <cmath>
#include <limits>
#include <span>
#include <vector>

static_assert( Harlinn::Common::ConstantRange<const std::vector<int>> );
static_assert( Harlinn::Common::ConstantRange<std::span<const int>> );
static_assert( !Harlinn::Common::ConstantRange<std::vector<int>> );
static_assert( !Harlinn::Common::ConstantRange<std::span<int>> );
static_assert( !Harlinn::Common::ConstantRange<int> );

namespace
{
    template<typename T, size_t N>
    void CheckSimdMemoryBounds( )
    {
        using Traits = Harlinn::Math::SIMD::Traits<T, N>;
        std::array<T, N + 2> data{};
        data.front( ) = T( -123 );
        data.back( ) = T( 456 );
        for ( size_t i = 0; i < N; ++i )
        {
            data[i + 1] = static_cast<T>( i + 1 );
        }
        const auto loaded = Traits::UnalignedLoad( data.data( ) + 1 );
        const auto values = Traits::ToArray( loaded );
        for ( size_t i = 0; i < N; ++i )
        {
            CHECK( values[i] == static_cast<T>( i + 1 ) );
        }
        Traits::Store( data.data( ) + 1, Traits::Fill( T( 42 ) ) );
        CHECK( data.front( ) == T( -123 ) );
        CHECK( data.back( ) == T( 456 ) );
        for ( size_t i = 0; i < N; ++i )
        {
            CHECK( data[i + 1] == T( 42 ) );
        }
    }

    template<typename T, size_t N>
    void CheckSimdLerp( )
    {
        using Traits = Harlinn::Math::SIMD::Traits<T, N>;
        using Array = typename Traits::ArrayType;
        const T maximum = std::numeric_limits<T>::max( );
        const T nan = std::numeric_limits<T>::quiet_NaN( );
        const auto check = []( T a, T b, T t, T expected )
        {
            const auto first = Traits::Fill( a );
            const auto second = Traits::Fill( b );
            const auto vectorResult = Traits::ToArray( Traits::Lerp( first, second, Traits::Fill( t ) ) );
            const auto scalarResult = Traits::ToArray( Traits::Lerp( first, second, t ) );
            for ( size_t i = 0; i < N; ++i )
            {
                if ( std::isnan( expected ) )
                {
                    CHECK( std::isnan( vectorResult[i] ) );
                    CHECK( std::isnan( scalarResult[i] ) );
                }
                else
                {
                    CHECK( vectorResult[i] == expected );
                    CHECK( scalarResult[i] == expected );
                }
            }
        };
        check( maximum, maximum, T( 2 ), maximum );
        check( -maximum, maximum, T( 0.5 ), T( 0 ) );
        std::feclearexcept( FE_ALL_EXCEPT );
        const auto sameSign = Traits::ToArray( Traits::Lerp( Traits::Fill( maximum ), Traits::Fill( maximum ), T( 2 ) ) );
        const auto sameSignExceptions = std::fetestexcept( FE_OVERFLOW | FE_INVALID );
        std::feclearexcept( FE_ALL_EXCEPT );
        const auto oppositeSign = Traits::ToArray( Traits::Lerp( Traits::Fill( -maximum ), Traits::Fill( maximum ), T( 0.5 ) ) );
        const auto oppositeSignExceptions = std::fetestexcept( FE_OVERFLOW | FE_INVALID );
        CAPTURE( N, sizeof( T ) );
        CHECK( sameSign[0] == maximum );
        CHECK( sameSignExceptions == 0 );
        CHECK( oppositeSign[0] == T( 0 ) );
        CHECK( oppositeSignExceptions == 0 );
        check( T( 3 ), T( 5 ), T( 0 ), T( 3 ) );
        check( T( 3 ), T( 5 ), T( 1 ), T( 5 ) );
        check( T( 3 ), T( 5 ), T( -1 ), T( 1 ) );        check( T( 3 ), T( 5 ), T( 2 ), T( 7 ) );
        check( T( 3 ), T( 5 ), nan, nan );

        Array factors{};
        for ( size_t i = 0; i < N; ++i )
        {
            factors[i] = static_cast<T>( i );
        }
        const auto mixed = Traits::ToArray( Traits::Lerp( Traits::Fill( T( 3 ) ), Traits::Fill( T( 5 ) ), Traits::Load( factors ) ) );
        for ( size_t i = 0; i < N; ++i )
        {
            CHECK( mixed[i] == T( 3 ) + T( 2 ) * factors[i] );
        }

        Array starts{}, ends{}, weights{};
        for ( size_t i = 0; i < N; ++i )
        {
            starts[i] = i % 2 == 0 ? -maximum : T( 3 );
            ends[i] = i % 2 == 0 ? maximum : T( 5 );
            weights[i] = i % 2 == 0 ? T( 0.5 ) : T( 2 );
        }
        const auto mixedBranches = Traits::ToArray( Traits::Lerp( Traits::Load( starts ), Traits::Load( ends ), Traits::Load( weights ) ) );
        for ( size_t i = 0; i < N; ++i )
        {
            CHECK( mixedBranches[i] == ( i % 2 == 0 ? T( 0 ) : T( 7 ) ) );
        }
    }
}

TEST_CASE("SIMD floating point loads and stores respect vector bounds", "[math][simd]")
{
    CheckSimdMemoryBounds<float, 1>( );
    CheckSimdMemoryBounds<float, 2>( );
    CheckSimdMemoryBounds<float, 3>( );
    CheckSimdMemoryBounds<float, 4>( );
    CheckSimdMemoryBounds<float, 5>( );
    CheckSimdMemoryBounds<float, 6>( );
    CheckSimdMemoryBounds<float, 7>( );
    CheckSimdMemoryBounds<float, 8>( );
    CheckSimdMemoryBounds<double, 1>( );
    CheckSimdMemoryBounds<double, 2>( );
    CheckSimdMemoryBounds<double, 3>( );
    CheckSimdMemoryBounds<double, 4>( );
}

TEST_CASE("SIMD three-element sum broadcasts one consistently rounded result", "[math][simd]")
{
    using Vector = Harlinn::Math::Vector<float, 3>;
    const Vector input( -5865740288.f, 5938396672.f, -73404312.f );
    const Vector result = Harlinn::Math::HSum( Vector::Simd( input ) );
    const float expected = ( input.x + input.y ) + input.z;
    CHECK( result.x == expected );
    CHECK( result.y == expected );
    CHECK( result.z == expected );
}

TEST_CASE("SIMD rounding uses nearest even for half-integers", "[math][simd]")
{
    using Vector = Harlinn::Math::Vector<float, 3>;
    const Vector result = Harlinn::Math::Round( Vector( 0.5f, 1.5f, -2.5f ) );
    CHECK( result.x == 0.f );
    CHECK( result.y == 2.f );
    CHECK( result.z == -2.f );
}

TEST_CASE("SIMD lerp handles extrapolation and endpoints", "[math][simd]")
{
    CheckSimdLerp<float, 1>( );
    CheckSimdLerp<float, 2>( );
    CheckSimdLerp<float, 3>( );
    CheckSimdLerp<float, 4>( );
    CheckSimdLerp<float, 5>( );
    CheckSimdLerp<float, 6>( );
    CheckSimdLerp<float, 7>( );
    CheckSimdLerp<float, 8>( );
    CheckSimdLerp<double, 1>( );
    CheckSimdLerp<double, 2>( );
    CheckSimdLerp<double, 3>( );
    CheckSimdLerp<double, 4>( );

    using Vector = Harlinn::Math::Vector<float, 3>;
    const Vector result = Harlinn::Math::Lerp( Vector( -5979795456.f ), Vector( -5979955712.f ), Vector( 8470938624.f ) );
    const float expected = -1357524808761344.f;
    CHECK( std::abs( ( result.x - expected ) / expected ) < 1e-6f );
    CHECK( std::abs( ( result.y - expected ) / expected ) < 1e-6f );
    CHECK( std::abs( ( result.z - expected ) / expected ) < 1e-6f );
}

#if defined(_WIN64) && LDBL_MANT_DIG == 64
TEST_CASE("OpenLibM x87 long double bit fields match the Windows representation", "[math][openlibm]")
{
    IEEEl2bits value{};
    value.e = -1.0L;

    REQUIRE( value.bits.manh == 0x80000000U );
    REQUIRE( value.bits.exp == 0x3fffU );
    REQUIRE( value.bits.sign == 1U );
    REQUIRE( value.xbits.expsign == 0xbfffU );
}
#endif

TEST_CASE("SquareMatrix array constructors copy values", "[math][matrix]")
{
    const float rows[2][2] = { { 1.0f, 2.0f }, { 3.0f, 4.0f } };
    const float values[4] = { 5.0f, 6.0f, 7.0f, 8.0f };

    const Harlinn::Math::SquareMatrix<float, 2> fromRows( rows );
    const Harlinn::Math::SquareMatrix<float, 2> fromValues( values );

    REQUIRE( fromRows[0][0] == 1.0f );
    REQUIRE( fromRows[1][1] == 4.0f );
    REQUIRE( fromValues[0][1] == 6.0f );
    REQUIRE( fromValues[1][0] == 7.0f );
}
