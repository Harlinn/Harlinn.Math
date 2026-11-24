#include "test_support.h"

#include <array>
#include <cmath>
#include <limits>
#include <span>

namespace
{
    template<typename T>
    void CheckScalarUtilities( )
    {
        using namespace Harlinn::Math;
        const T pi = std::acos( T( -1 ) );
        const T nan = std::numeric_limits<T>::quiet_NaN( );
        const T infinity = std::numeric_limits<T>::infinity( );
        const T tolerance = T( 16 ) * std::numeric_limits<T>::epsilon( );
        const auto close = [tolerance]( T actual, T expected )
        {
            CHECK( std::abs( actual - expected ) <= tolerance * std::max( T( 1 ), std::abs( expected ) ) );
        };
        CAPTURE( sizeof( T ) );
        CHECK( SinXOverX( T( 0 ) ) == T( 1 ) );
        close( SinXOverX( T( 0.5 ) ), std::sin( T( 0.5 ) ) / T( 0.5 ) );
        CHECK( Sinc( T( 0 ) ) == T( 1 ) );
        close( Sinc( T( 0.5 ) ), T( 2 ) / pi );
        CHECK( WindowedSinc( T( 2 ), T( 1 ), T( 2 ) ) == T( 0 ) );
        close( WindowedSinc( T( 0.5 ), T( 1 ), T( 2 ) ), ( T( 2 ) / pi ) * ( std::sin( pi / T( 4 ) ) / ( pi / T( 4 ) ) ) );
        CHECK( Mod( T( -5 ), T( 3 ) ) == T( -2 ) );
        close( Radians( T( 180 ) ), pi );
        close( Degrees( pi ), T( 180 ) );
        CHECK( SmoothStep( T( -1 ), T( 0 ), T( 1 ) ) == T( 0 ) );
        CHECK( SmoothStep( T( 0.5 ), T( 0 ), T( 1 ) ) == T( 0.5 ) );
        CHECK( SmoothStep( T( 2 ), T( 0 ), T( 1 ) ) == T( 1 ) );
        CHECK( SmoothStep( T( 0 ), T( 1 ), T( 1 ) ) == T( 0 ) );
        CHECK( SmoothStep( T( 1 ), T( 1 ), T( 1 ) ) == T( 1 ) );
        CHECK( SafeSqrt( T( -1 ) ) == T( 0 ) );
        CHECK( SafeSqrt( T( 4 ) ) == T( 2 ) );
        CHECK( std::isnan( SafeSqrt( nan ) ) );
        CHECK( std::isnan( SqrtAdjustDown( T( -1 ) ) ) );
        CHECK( Sqr( T( -3 ) ) == T( 9 ) );
        CHECK( FastPow<0>( T( 2 ) ) == T( 1 ) );
        CHECK( FastPow<3>( T( -2 ) ) == T( -8 ) );
        CHECK( FastPow<-3>( T( 2 ) ) == T( 0.125 ) );
        CHECK( EvaluatePolynomial( T( 2 ), T( 3 ), T( 4 ), T( 5 ) ) == T( 31 ) );
        close( SafeASin( T( 2 ) ), pi / T( 2 ) );
        close( SafeACos( T( -2 ) ), pi );
        CHECK( std::isnan( SafeASin( nan ) ) );
        CHECK( std::isnan( SafeACos( nan ) ) );
        CHECK( NextFloatUp( T( 0 ) ) == std::nextafter( T( 0 ), infinity ) );
        CHECK( NextFloatDown( T( 0 ) ) == std::nextafter( T( 0 ), -infinity ) );
        CHECK( Gamma<T>( 0 ) == T( 0 ) );
        CHECK( Gamma<T>( 1 ) > T( 0 ) );
        CHECK( FDim( T( 2 ), T( 3 ) ) == T( 0 ) );
        CHECK( FDim( T( 3 ), T( 2 ) ) == T( 1 ) );
        CHECK( std::isnan( FDim( nan, T( 2 ) ) ) );
        CHECK( LogB( T( 8 ) ) == T( 3 ) );
        CHECK( ILogB( T( 8 ) ) == 3 );
        CHECK( LogB( std::numeric_limits<T>::denorm_min( ) ) == T( std::numeric_limits<T>::min_exponent - std::numeric_limits<T>::digits ) );
    }

    template<typename T>
    void CheckAdjustedArithmetic( )
    {
        using namespace Harlinn::Math;
        const T inf = std::numeric_limits<T>::infinity( );
        const auto up = [inf]( T x ) { return std::nextafter( x, inf ); };
        const auto down = [inf]( T x ) { return std::nextafter( x, -inf ); };
        CHECK( AddAdjustUp( T( 1 ), T( 2 ) ) == up( T( 3 ) ) );
        CHECK( AddAdjustDown( T( 1 ), T( 2 ) ) == down( T( 3 ) ) );
        CHECK( SubAdjustUp( T( 1 ), T( 2 ) ) == up( T( -1 ) ) );
        CHECK( SubAdjustDown( T( 1 ), T( 2 ) ) == down( T( -1 ) ) );
        CHECK( MulAdjustUp( T( 2 ), T( 3 ) ) == up( T( 6 ) ) );
        CHECK( MulAdjustDown( T( 2 ), T( 3 ) ) == down( T( 6 ) ) );
        CHECK( DivAdjustUp( T( 6 ), T( 2 ) ) == up( T( 3 ) ) );
        CHECK( DivAdjustDown( T( 6 ), T( 2 ) ) == down( T( 3 ) ) );
        CHECK( SqrtAdjustUp( T( 4 ) ) == up( T( 2 ) ) );
        CHECK( SqrtAdjustDown( T( 4 ) ) == down( T( 2 ) ) );
        CHECK( SqrtAdjustDown( T( 0 ) ) == T( 0 ) );
        CHECK( FMAAdjustUp( T( 2 ), T( 3 ), T( 4 ) ) == up( T( 10 ) ) );
        CHECK( FMAAdjustDown( T( 2 ), T( 3 ), T( 4 ) ) == down( T( 10 ) ) );
    }

    template<typename T>
    void CheckQuadratic( )
    {
        using namespace Harlinn::Math;
        T low = T( 99 ), high = T( 99 );
        REQUIRE( Quadratic( T( 1 ), T( -3 ), T( 2 ), &low, &high ) );
        CHECK( low == T( 1 ) );
        CHECK( high == T( 2 ) );
        REQUIRE( Quadratic( T( 1 ), T( 0 ), T( 0 ), &low, &high ) );
        CHECK( low == T( 0 ) );
        CHECK( high == T( 0 ) );
        REQUIRE( Quadratic( T( 0 ), T( 2 ), T( -4 ), &low, &high ) );
        CHECK( low == T( 2 ) );
        CHECK( high == T( 2 ) );
        low = high = T( 99 );
        CHECK_FALSE( Quadratic( T( 1 ), T( 0 ), T( 1 ), &low, &high ) );
        CHECK( low == T( 99 ) );
        CHECK( high == T( 99 ) );
        CHECK_FALSE( Quadratic( T( 0 ), T( 0 ), T( 1 ), &low, &high ) );
    }

    template<typename T>
    void CheckDistributionsAndCompensation( )
    {
        using namespace Harlinn::Math;
        const T pi = std::acos( T( -1 ) );
        const T relativeTolerance = std::is_same_v<T, float> ? T( 0.001 ) : T( 1e-12 );
        const auto close = [relativeTolerance]( T actual, T expected )
        {
            CHECK( std::abs( actual - expected ) <= relativeTolerance * std::max( T( 1 ), std::abs( expected ) ) );
        };
        close( Gaussian( T( 0 ), T( 0 ), T( 1 ) ), T( 1 ) / std::sqrt( T( 2 ) * pi ) );
        close( Gaussian( T( 1 ), T( 0 ), T( 1 ) ), std::exp( T( -0.5 ) ) / std::sqrt( T( 2 ) * pi ) );
        close( GaussianIntegral( T( -1 ), T( 1 ), T( 0 ), T( 1 ) ), std::erf( T( 1 ) / std::sqrt( T( 2 ) ) ) );
        close( Logistic( T( 0 ), T( 2 ) ), T( 0.125 ) );
        close( Logistic( T( 1 ), T( 2 ) ), Logistic( T( -1 ), T( 2 ) ) );
        close( LogisticCDF( T( 0 ), T( 2 ) ), T( 0.5 ) );
        close( LogisticCDF( T( 1 ), T( 2 ) ) + LogisticCDF( T( -1 ), T( 2 ) ), T( 1 ) );
        close( TrimmedLogistic( T( 0 ), T( 1 ), T( -1 ), T( 1 ) ), T( 0.25 ) / ( T( 2 ) / ( T( 1 ) + std::exp( T( -1 ) ) ) - T( 1 ) ) );
        const auto sum = TwoSum( T( 1 ), std::numeric_limits<T>::epsilon( ) / T( 2 ) );
        CHECK( sum.v == T( 1 ) );
        CHECK( sum.err == std::numeric_limits<T>::epsilon( ) / T( 2 ) );
        const T a = T( 1 ) + std::numeric_limits<T>::epsilon( );
        const auto product = TwoProd( a, a );
        CHECK( product.v == a * a );
        CHECK( product.err == std::fma( a, a, -product.v ) );
        CHECK( DifferenceOfProducts( T( 2 ), T( 3 ), T( 4 ), T( 5 ) ) == T( -14 ) );
        CHECK( SumOfProducts( T( 2 ), T( 3 ), T( 4 ), T( 5 ) ) == T( 26 ) );
        CHECK( InnerProduct( T( 2 ), T( 3 ), T( 4 ), T( 5 ) ) == T( 26 ) );
    }

    template<typename T>
    void CheckIntervals( )
    {
        using namespace Harlinn::Math;
        const Interval<T> a( T( -2 ), T( 3 ) );
        const Interval<T> b( T( 4 ), T( 5 ) );
        CHECK( InRange( T( 0 ), a ) );
        CHECK_FALSE( InRange( T( 4 ), a ) );
        CHECK_FALSE( InRange( a, b ) );
        CHECK( InRange( T( -10 ), a * b ) );
        CHECK( InRange( T( 15 ), a * b ) );
        CHECK( InRange( T( 0 ), Sqr( a ) ) );
        CHECK( InRange( T( 9 ), Sqr( a ) ) );
        CHECK( InRange( T( -0.5 ), a / b ) );
        CHECK( InRange( T( 0.75 ), a / b ) );
        const auto unbounded = b / a;
        CHECK( unbounded.LowerBound( ) == -std::numeric_limits<T>::infinity( ) );
        CHECK( unbounded.UpperBound( ) == std::numeric_limits<T>::infinity( ) );
        const auto errorBounds = Interval<T>::FromValueAndError( T( 1 ), T( -0.5 ) );
        CHECK( InRange( T( 0.5 ), errorBounds ) );
        CHECK( InRange( T( 1.5 ), errorBounds ) );
    }

    template<typename T>
    void CheckIntervalOverloads( )
    {
        using namespace Harlinn::Math;
        const Interval<T> a( T( -2 ), T( 3 ) ), b( T( 4 ), T( 5 ) );
        const auto contains = []( const Interval<T>& interval, T low, T high )
        {
            CHECK( InRange( low, interval ) );
            CHECK( InRange( high, interval ) );
        };
        contains( a + b, T( 2 ), T( 8 ) );
        contains( a - b, T( -7 ), T( -1 ) );
        contains( T( 2 ) + a, T( 0 ), T( 5 ) );
        contains( a + T( 2 ), T( 0 ), T( 5 ) );
        contains( T( 2 ) - a, T( -1 ), T( 4 ) );
        contains( a - T( 2 ), T( -4 ), T( 1 ) );
        contains( T( -2 ) * a, T( -6 ), T( 4 ) );
        contains( a * T( -2 ), T( -6 ), T( 4 ) );
        contains( T( -4 ) / b, T( -1 ), T( -0.8 ) );
        contains( a / T( -2 ), T( -1.5 ), T( 1 ) );
        auto quotient = b;
        quotient /= T( 0 );
        CHECK( quotient.LowerBound( ) == -std::numeric_limits<T>::infinity( ) );
        CHECK( quotient.UpperBound( ) == std::numeric_limits<T>::infinity( ) );
        CHECK( Floor( a ) == T( -2 ) );
        CHECK( floor( a ) == T( -2 ) );
        CHECK( Ceil( b ) == T( 5 ) );
        CHECK( ceil( b ) == T( 5 ) );
        CHECK( Min( a, b ) == T( -2 ) );
        CHECK( min( a, b ) == T( -2 ) );
        CHECK( Max( a, b ) == T( 5 ) );
        CHECK( max( a, b ) == T( 5 ) );
        contains( Sqrt( b ), T( 2 ), std::sqrt( T( 5 ) ) );
        contains( sqrt( b ), T( 2 ), std::sqrt( T( 5 ) ) );
        contains( Abs( a ), T( 0 ), T( 3 ) );
        contains( abs( a ), T( 0 ), T( 3 ) );
        contains( FMA( a, b, b ), T( -6 ), T( 20 ) );
        contains( DifferenceOfProducts( a, b, b, b ), T( -35 ), T( -1 ) );
        contains( SumOfProducts( a, b, b, b ), T( 6 ), T( 40 ) );
        contains( MulPow2( a, T( -2 ) ), T( -6 ), T( 4 ) );
        contains( MulPow2( T( -2 ), a ), T( -6 ), T( 4 ) );
        const T denormal = std::numeric_limits<T>::denorm_min( );
        const auto underflow = MulPow2( Interval<T>( denormal ), T( 0.5 ) );
        CHECK( underflow.LowerBound( ) <= T( 0 ) );
        CHECK( underflow.UpperBound( ) >= denormal );
        contains( SumSquares( a ), T( 0 ), T( 9 ) );
        contains( SumSquares( a, b ), T( 16 ), T( 34 ) );
        Interval<T> root0, root1;
        REQUIRE( Quadratic( Interval<T>( T( 1 ) ), Interval<T>( T( -3 ) ), Interval<T>( T( 2 ) ), &root0, &root1 ) );
        CHECK( InRange( T( 1 ), root0 ) );
        CHECK( InRange( T( 2 ), root1 ) );
    }

    template<typename T>
    void CheckIntervalTrigonometry( )
    {
        using namespace Harlinn::Math;
        const T pi = std::acos( T( -1 ) );
        const std::array<Interval<T>, 8> inputs{
            Interval<T>( T( -1 ), T( -0.5 ) ), Interval<T>( T( -2 ), T( -1 ) ),
            Interval<T>( T( 0 ), T( 2 ) ), Interval<T>( T( 3 ), T( 5 ) ),
            Interval<T>( T( -8 ), T( -6 ) ), Interval<T>( T( 6 ), T( 8 ) ),
            Interval<T>( -T( 4 ) * pi, T( 4 ) * pi ), Interval<T>( T( 100 ), T( 101 ) ) };
        for ( const auto& input : inputs )
        {
            CAPTURE( sizeof( T ), input.LowerBound( ), input.UpperBound( ) );
            const auto s = Sin( input ), c = Cos( input );
            Interval<T> combinedS, combinedC;
            SinCos( input, &combinedS, &combinedC );
            for ( int n = 0; n <= 64; ++n )
            {
                const T x = input.LowerBound( ) + ( input.UpperBound( ) - input.LowerBound( ) ) * T( n ) / T( 64 );
                CHECK( InRange( std::sin( x ), s ) );
                CHECK( InRange( std::cos( x ), c ) );
                CHECK( InRange( std::sin( x ), combinedS ) );
                CHECK( InRange( std::cos( x ), combinedC ) );
            }
        }
        const auto arc = ACos( Interval<T>( T( -0.5 ), T( 0.5 ) ) );
        CHECK( InRange( std::acos( T( -0.5 ) ), arc ) );
        CHECK( InRange( std::acos( T( 0.5 ) ), arc ) );
        const T nan = std::numeric_limits<T>::quiet_NaN( );
        const auto invalidSine = Sin( Interval<T>( nan ) );
        const auto invalidCosine = Cos( Interval<T>( nan ) );
        CHECK( std::isnan( invalidSine.LowerBound( ) ) );
        CHECK( std::isnan( invalidSine.UpperBound( ) ) );
        CHECK( std::isnan( invalidCosine.LowerBound( ) ) );
        CHECK( std::isnan( invalidCosine.UpperBound( ) ) );
    }
}

TEST_CASE( "Scalar math utility values and domains", "[math][scalar][coverage]" )
{
    CheckScalarUtilities<float>( );
    CheckScalarUtilities<double>( );
}

TEST_CASE( "Adjusted scalar operations enclose exact results", "[math][scalar][coverage]" )
{
    CheckAdjustedArithmetic<float>( );
    CheckAdjustedArithmetic<double>( );
}

TEST_CASE( "Quadratic roots include zero and degenerate cases", "[math][scalar][coverage]" )
{
    CheckQuadratic<float>( );
    CheckQuadratic<double>( );
}

TEST_CASE( "Products and interval search cover their boundary cases", "[math][scalar][coverage]" )
{
    using namespace Harlinn::Math;
    constexpr std::array<int, 3> values{ 2, -3, 4 };
    constexpr std::array<int, 0> empty{};
    STATIC_REQUIRE( Multiply( std::span( values ) ) == -24 );
    STATIC_REQUIRE( Multiply( std::span( empty ) ) == 1 );
    STATIC_REQUIRE( EvaluatePolynomial( 2, 3, 4, 5 ) == 31 );
    STATIC_REQUIRE( FastPow<-3>( 2.0 ) == 0.125 );
    STATIC_REQUIRE( IsNaN( SafeSqrt( std::numeric_limits<double>::quiet_NaN( ) ) ) );
    STATIC_REQUIRE( [] { double a = 1, b = 1; return Quadratic( 1.0, 0.0, 0.0, &a, &b ) && a == 0.0 && b == 0.0; }( ) );
    CHECK( FindInterval( 2, []( size_t ) { return true; } ) == 0 );
    CHECK( FindInterval( 5, []( size_t i ) { return i < 3; } ) == 2 );
    CHECK( FindInterval( 5, []( size_t ) { return false; } ) == 0 );
    CHECK( FindInterval( 5, []( size_t ) { return true; } ) == 3 );
    CHECK( Lerp2( 0.25, 2.0, 6.0 ) == 3.0 );
    CHECK( Lerp2( 2.0, 2.0, 6.0 ) == 10.0 );
    STATIC_REQUIRE( Lerp( 2.0, 6.0, 0.25f ) == 3.0 );
    STATIC_REQUIRE( Lerp( 2, 6, 0.25 ) == 3.0 );
    const double maximum = std::numeric_limits<double>::max( );
    CHECK( Lerp( maximum, maximum, 2.0 ) == maximum );
    CHECK( Lerp( -maximum, maximum, 0.5 ) == 0.0 );
    CHECK( Lerp( 2.0, 6.0, 0.0 ) == 2.0 );
    CHECK( Lerp( 2.0, 6.0, 1.0 ) == 6.0 );
    CHECK( Lerp( 2.0, 6.0, 2.0 ) == 10.0 );
    CHECK( std::isnan( Lerp( 2.0, 6.0, std::numeric_limits<double>::quiet_NaN( ) ) ) );
    CHECK( IsPowerOf4( 1 ) );
    CHECK( IsPowerOf4( 16 ) );
    CHECK_FALSE( IsPowerOf4( 8 ) );
    CHECK( RoundUpPow2( Harlinn::Common::Int32( 5 ) ) == 8 );
    CHECK( RoundUpPow4( 5 ) == 16 );
    CHECK( Log2Int( Harlinn::Common::UInt32( 17 ) ) == 4 );
    CHECK( Log4Int( Harlinn::Common::UInt32( 17 ) ) == 2 );
}

TEST_CASE( "FastExp handles nonfinite and extreme arguments", "[math][scalar][coverage]" )
{
    using Harlinn::Math::FastExp;
    const float infinity = std::numeric_limits<float>::infinity( );
    const float nan = std::numeric_limits<float>::quiet_NaN( );
    STATIC_REQUIRE( FastExp( 0.f ) == 1.f );
    CHECK( std::isnan( FastExp( nan ) ) );
    CHECK( FastExp( infinity ) == infinity );
    CHECK( FastExp( -infinity ) == 0.f );
    CHECK( FastExp( std::numeric_limits<float>::max( ) ) == infinity );
    CHECK( FastExp( std::numeric_limits<float>::lowest( ) ) == 0.f );
    for ( const float x : { -10.f, -1.f, 0.f, 1.f, 10.f } )
    {
        CAPTURE( x );
        CHECK( std::abs( FastExp( x ) / std::exp( x ) - 1.f ) < 0.001f );
    }
}

TEST_CASE( "Distribution and compensated arithmetic identities", "[math][scalar][coverage]" )
{
    CheckDistributionsAndCompensation<float>( );
    CheckDistributionsAndCompensation<double>( );
}

TEST_CASE( "Interval arithmetic encloses sampled endpoints", "[math][scalar][coverage]" )
{
    CheckIntervals<float>( );
    CheckIntervals<double>( );
}

TEST_CASE( "Interval overloads enclose independently computed results", "[math][interval][coverage]" )
{
    CheckIntervalOverloads<float>( );
    CheckIntervalOverloads<double>( );
}

TEST_CASE( "Interval trigonometry encloses periodic values", "[math][interval][coverage]" )
{
    CheckIntervalTrigonometry<float>( );
    CheckIntervalTrigonometry<double>( );
}

TEST_CASE( "Newton bisection locates bracketed roots", "[math][scalar][coverage]" )
{
    using Harlinn::Math::NewtonBisection;
    const auto quadratic = []( double x ) { return std::pair{ x * x - 2.0, 2.0 * x }; };
    const auto root = NewtonBisection( 0.0, 2.0, quadratic, 1e-12, 1e-12 );
    CHECK( std::abs( root - std::sqrt( 2.0 ) ) < 1e-10 );
    const auto linear = []( double x ) { return std::pair{ x - 1.0, 1.0 }; };
    CHECK( NewtonBisection( 1.0, 3.0, linear ) == 1.0 );
    CHECK( NewtonBisection( -1.0, 1.0, linear ) == 1.0 );
}

TEST_CASE( "Half precision special values and bit round trips", "[math][half][coverage]" )
{
    using Harlinn::Math::Half;
    const auto nan = Half::FromBits( 0x7e00 );
    CHECK_FALSE( nan == nan );
    CHECK( nan != nan );
    CHECK( nan.NextUp( ).Bits( ) == nan.Bits( ) );
    CHECK( nan.NextDown( ).Bits( ) == nan.Bits( ) );
    CHECK( Half::FromBits( Half::NegativeZero ) == Half::FromBits( Half::PositiveZero ) );
    CHECK( Half::FromBits( Half::NegativeZero ).NextUp( ).Bits( ) == 1 );
    CHECK( Half::FromBits( Half::PositiveZero ).NextDown( ).Bits( ) == 0x8001 );
    CHECK( Half( 1.f + 0x1p-11f ).Bits( ) == 0x3c00 );
    CHECK( Half( 1.f + 3.f * 0x1p-11f ).Bits( ) == 0x3c02 );
    CHECK( Half( 1.0 + 0x1p-11 + 0x1p-30 ).Bits( ) == 0x3c01 );
    CHECK( Half( 1.0 + 0x1p-11 - 0x1p-30 ).Bits( ) == 0x3c00 );
    for ( unsigned bits = 0; bits < 0x7bff; ++bits )
    {
        const float lower = static_cast<float>( Half::FromBits( static_cast<Harlinn::Common::UInt16>( bits ) ) );
        const float upper = static_cast<float>( Half::FromBits( static_cast<Harlinn::Common::UInt16>( bits + 1 ) ) );
        const float midpoint = lower + ( upper - lower ) * 0.5f;
        const auto expected = static_cast<Harlinn::Common::UInt16>( bits + ( bits & 1u ) );
        CAPTURE( bits );
        CHECK( Half( midpoint ).Bits( ) == expected );
        CHECK( Half( -midpoint ).Bits( ) == ( expected | 0x8000u ) );
        CHECK( Half( static_cast<double>( midpoint ) ).Bits( ) == expected );
        CHECK( Half( -static_cast<double>( midpoint ) ).Bits( ) == ( expected | 0x8000u ) );
    }
    for ( unsigned bits = 0; bits <= 0xffff; ++bits )
    {
        const auto half = Half::FromBits( static_cast<Harlinn::Common::UInt16>( bits ) );
        if ( !half.IsNaN( ) )
        {
            CAPTURE( bits );
            CHECK( Half( static_cast<float>( half ) ).Bits( ) == half.Bits( ) );
        }
    }
}
