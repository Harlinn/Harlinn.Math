#include <catch2/catch_test_macros.hpp>
#include <harlinn/math/VectorMath.h>

#include <cfenv>
#include <cfloat>
#include <cmath>
#include <cstdint>
#include <limits>
#include <span>
#include <vector>

static_assert( Harlinn::Common::ConstantRange<const std::vector<int>> );
static_assert( Harlinn::Common::ConstantRange<std::span<const int>> );
static_assert( !Harlinn::Common::ConstantRange<std::vector<int>> );
static_assert( !Harlinn::Common::ConstantRange<std::span<int>> );
static_assert( !Harlinn::Common::ConstantRange<int> );
static_assert( Harlinn::Math::Internal::AngleBetween3( 1.0, 0.0, 0.0, 2.0, 0.0, 0.0 ) == 0.0 );

namespace
{
    template<typename T>
    void CheckAngleBetween3( )
    {
        using Vector = Harlinn::Math::Vector<T, 3>;
        using Tuple = Harlinn::Math::Tuple3<Vector, T>;
        using Simd = typename Vector::Simd;
        const T tolerance = T( 32 ) * std::numeric_limits<T>::epsilon( );
        const auto check = [tolerance]( const Vector& a, const Vector& b, T expected )
        {
            const Simd sa( a ), sb( b );
            const Tuple& ta = a;
            const Tuple& tb = b;
            const auto checkValue = [tolerance, expected]( T actual )
            {
                if ( std::isnan( expected ) )
                {
                    CHECK( std::isnan( actual ) );
                }
                else
                {
                    CHECK( std::abs( actual - expected ) <= tolerance * std::abs( expected ) );
                }
            };
            checkValue( ScalarAngleBetween( a, b ) );
            checkValue( ScalarAngleBetween( sa, sb ) );
            checkValue( ScalarAngleBetween( sa, b ) );
            checkValue( ScalarAngleBetween( a, sb ) );
            const Vector vv( AngleBetween( a, b ) );
            const Vector vs( AngleBetween( a, sb ) );
            const Vector sv( AngleBetween( sa, b ) );
            const Vector ss( AngleBetween( sa, sb ) );
            const auto tt = AngleBetween( ta, tb );
            for ( const auto& result : { vv, vs, sv, ss } )
            {
                checkValue( result.x );
                checkValue( result.y );
                checkValue( result.z );
            }
            checkValue( tt.x );
            checkValue( tt.y );
            checkValue( tt.z );
        };
        const T pi = static_cast<T>( std::acos( -1.0 ) );
        const T max = std::numeric_limits<T>::max( );
        const T minimum = std::numeric_limits<T>::min( );
        const T tinyAngle = T( 1e-30 );
        const T nan = std::numeric_limits<T>::quiet_NaN( );
        const T infinity = std::numeric_limits<T>::infinity( );
        check( Vector( 2, 2, 2 ), Vector( 2, 0, 2 ), static_cast<T>( std::atan2( 1.0, std::sqrt( 2.0 ) ) ) );
        check( Vector( 1, 0, 0 ), Vector( 2, 0, 0 ), T( 0 ) );
        check( Vector( 1, 0, 0 ), Vector( -2, 0, 0 ), pi );
        check( Vector( 1, 0, 0 ), Vector( 0, 2, 0 ), pi / T( 2 ) );
        check( Vector( 1, 0, 0 ), Vector( 1, tinyAngle, 0 ), static_cast<T>( std::atan2( static_cast<double>( tinyAngle ), 1.0 ) ) );
        check( Vector( max, max, 0 ), Vector( 0, minimum, 0 ), pi / T( 4 ) );
        check( Vector( minimum, minimum, 0 ), Vector( max, 0, 0 ), pi / T( 4 ) );
        check( Vector( 0, 0, 0 ), Vector( 1, 0, 0 ), nan );
        check( Vector( 1, 0, 0 ), Vector( 0, 0, 0 ), nan );
        check( Vector( infinity, 0, 0 ), Vector( 1, 0, 0 ), nan );
        check( Vector( 1, 0, 0 ), Vector( nan, 0, 0 ), nan );
    }

    template<typename T>
    void CheckQuaternionScalarOperations( )
    {
        using Q = Harlinn::Math::Quaternion<T>;
        const Q q( T( 1 ), T( -2 ), T( 3 ), T( 4 ) );
        const typename Q::Simd simd( q );
        const auto check = []( const Q& actual, const Q& expected )
        {
            for ( size_t i = 0; i < 4; ++i )
            {
                CHECK( std::abs( actual[i] - expected[i] ) <= T( 8 ) * std::numeric_limits<T>::epsilon( ) );
            }
        };
        check( Q( T( 3 ) - q ), Q( T( -1 ), T( 2 ), T( -3 ), T( -1 ) ) );
        check( Q( T( 3 ) - simd ), Q( T( -1 ), T( 2 ), T( -3 ), T( -1 ) ) );
        const Q expected( T( -0.1 ), T( 0.2 ), T( -0.3 ), T( 0.4 ) );
        check( Q( T( 3 ) / q ), expected );
        check( Q( T( 3 ) / simd ), expected );
        check( Q( T( 4 ) / Q( T( 0 ), T( 0 ), T( 0 ), T( 2 ) ) ), Q( T( 0 ), T( 0 ), T( 0 ), T( 2 ) ) );
        const T maximum = std::numeric_limits<T>::max( );
        const T minimum = std::numeric_limits<T>::min( );
        const T subnormal = std::numeric_limits<T>::denorm_min( );
        const Q half( T( -0.5 ), T( -0.5 ), T( 0 ), T( 0 ) );
        check( Q( maximum / Q( maximum, maximum, T( 0 ), T( 0 ) ) ), half );
        check( Q( minimum / Q( minimum, minimum, T( 0 ), T( 0 ) ) ), half );
        check( Q( subnormal / Q( subnormal, T( 0 ), T( 0 ), T( 0 ) ) ), Q( T( -1 ), T( 0 ), T( 0 ), T( 0 ) ) );
        const Q zeroResult( T( 1 ) / Q( T( 0 ), T( 0 ), T( 0 ), T( 0 ) ) );
        for ( size_t i = 0; i < 4; ++i )
        {
            CHECK( std::isnan( zeroResult[i] ) );
        }
    }

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

TEST_CASE("Three-dimensional angles are independent of vector magnitude", "[math][angle]")
{
    CheckAngleBetween3<float>( );
    CheckAngleBetween3<double>( );
}

TEST_CASE("Real and quaternion arithmetic follows quaternion algebra", "[math][quaternion]")
{
    CheckQuaternionScalarOperations<float>( );
    CheckQuaternionScalarOperations<double>( );
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

TEST_CASE("SquareMatrix 2x2 SIMD conversions accept unaligned input", "[math][matrix]")
{
    using Matrix = Harlinn::Math::SquareMatrix<float, 2>;
    using Simd = Matrix::Simd;
    struct alignas( 16 ) Inputs
    {
        float padding;
        Matrix matrix;
        Simd::ArrayType array;
        float rows[2][2];
    };
    Inputs input{ 0.f, Matrix( 1.f, 2.f, 3.f, 4.f ), {{{ 1.f, 2.f }, { 3.f, 4.f }}}, {{ 1.f, 2.f }, { 3.f, 4.f }} };
    REQUIRE( reinterpret_cast<std::uintptr_t>( &input.matrix[0][0] ) % 16 != 0 );
    REQUIRE( reinterpret_cast<std::uintptr_t>( &input.array[0][0] ) % 16 != 0 );
    REQUIRE( reinterpret_cast<std::uintptr_t>( &input.rows[0][0] ) % 16 != 0 );

    const auto check = []( const Simd& simd )
    {
        const auto result = Simd::ToMatrix( simd );
        CHECK( result[0][0] == 1.f );
        CHECK( result[0][1] == 2.f );
        CHECK( result[1][0] == 3.f );
        CHECK( result[1][1] == 4.f );
    };
    check( Simd( input.matrix ) );
    check( Simd( input.array ) );
    check( Simd( Simd::ToSimd( input.array ) ) );
    check( Simd( Simd::ToSimd( input.rows ) ) );
}
