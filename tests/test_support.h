#pragma once

#include <harlinn/math/VectorMath.h>
#include <harlinn/math/Primitives.h>
#include <harlinn/math/Distance.h>
#include <harlinn/math/Transformations.h>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <numeric>
#include <random>
#include <type_traits>
#include <utility>

namespace HarlinnMathTest
{
    template<typename First, typename Second>
    bool EqualImpl( const First& first, const Second& second, double epsilon, bool relative = false )
    {
        if constexpr ( std::is_arithmetic_v<First> && std::is_arithmetic_v<Second> )
        {
            using Common = std::common_type_t<First, Second>;
            const auto firstValue = static_cast<Common>( first );
            const auto secondValue = static_cast<Common>( second );
            if constexpr ( std::is_floating_point_v<Common> )
            {
                if ( std::isnan( firstValue ) || std::isnan( secondValue ) )
                {
                    return std::isnan( firstValue ) && std::isnan( secondValue );
                }
                if ( std::isinf( firstValue ) || std::isinf( secondValue ) )
                {
                    return firstValue == secondValue;
                }
                const auto difference = std::abs( firstValue - secondValue );
                if ( relative )
                {
                    const auto scale = std::max( std::abs( firstValue ), std::abs( secondValue ) );
                    return scale == 0 ? difference <= epsilon : difference / scale <= epsilon;
                }
                return difference <= epsilon;
            }
            else
            {
                return firstValue == secondValue;
            }
        }
        else if constexpr ( requires { first.first; first.second; second.first; second.second; } )
        {
            return EqualImpl( first.first, second.first, epsilon, relative ) && EqualImpl( first.second, second.second, epsilon, relative );
        }
        else if constexpr ( requires { first.size( ); first[ size_t{} ]; } )
        {
            if ( first.size( ) != second.size( ) )
            {
                return false;
            }
            for ( size_t i = 0; i < first.size( ); ++i )
            {
                if ( !EqualImpl( first[ i ], second[ i ], epsilon, relative ) )
                {
                    return false;
                }
            }
            return true;
        }
        else if constexpr ( requires { first.x; first.y; first.z; first.w; } )
        {
            return EqualImpl( first.x, second.x, epsilon, relative ) && EqualImpl( first.y, second.y, epsilon, relative ) &&
                EqualImpl( first.z, second.z, epsilon, relative ) && EqualImpl( first.w, second.w, epsilon, relative );
        }
        else if constexpr ( requires { first.x; first.y; first.z; } )
        {
            return EqualImpl( first.x, second.x, epsilon, relative ) && EqualImpl( first.y, second.y, epsilon, relative ) &&
                EqualImpl( first.z, second.z, epsilon, relative );
        }
        else if constexpr ( requires { first.x; first.y; } )
        {
            return EqualImpl( first.x, second.x, epsilon, relative ) && EqualImpl( first.y, second.y, epsilon, relative );
        }
        else if constexpr ( requires { first.x( ); first.y( ); first.z( ); first.w( ); } )
        {
            return EqualImpl( first.x( ), second.x( ), epsilon, relative ) && EqualImpl( first.y( ), second.y( ), epsilon, relative ) &&
                EqualImpl( first.z( ), second.z( ), epsilon, relative ) && EqualImpl( first.w( ), second.w( ), epsilon, relative );
        }
        else if constexpr ( requires { first.x( ); first.y( ); first.z( ); } )
        {
            return EqualImpl( first.x( ), second.x( ), epsilon, relative ) && EqualImpl( first.y( ), second.y( ), epsilon, relative ) &&
                EqualImpl( first.z( ), second.z( ), epsilon, relative );
        }
        else if constexpr ( requires { first.x( ); first.y( ); } )
        {
            return EqualImpl( first.x( ), second.x( ), epsilon, relative ) && EqualImpl( first.y( ), second.y( ), epsilon, relative );
        }
        else
        {
            return first == second;
        }
    }

    template<typename T>
    bool Equal( const T& first, const T& second, double epsilon = 0.0001 )
    {
        return EqualImpl( first, second, epsilon );
    }

    template<typename First, typename Second>
    bool Equal( const First& first, const Second& second, double epsilon = 0.0001 )
    {
        return EqualImpl( first, second, epsilon );
    }

    template<typename First, typename Second>
    bool Near( const First& first, const Second& second, double epsilon )
    {
        return EqualImpl( first, second, epsilon, true );
    }

    template<typename T>
    double Deviation( T first, T second )
    {
        const auto difference = std::abs( static_cast<double>( first ) - static_cast<double>( second ) );
        const auto scale = std::max( std::abs( static_cast<double>( first ) ), std::abs( static_cast<double>( second ) ) );
        return scale == 0.0 ? difference : difference / scale;
    }
}

namespace Test
{
    using HarlinnMathTest::Deviation;

    namespace Generators
    {
        template<typename T, size_t Count>
        class RandomGenerator
        {
            std::mt19937_64 engine_{ 0x4841524c494e4eULL + Count };
            T minimum_ = static_cast<T>( -10000 );
            T maximum_ = static_cast<T>( 10000 );
        public:
            RandomGenerator( ) = default;
            RandomGenerator( T minimum, T maximum ) : minimum_( minimum ), maximum_( maximum ) { }

            T operator()( )
            {
                std::uniform_real_distribution<T> distribution( minimum_, maximum_ );
                return distribution( engine_ );
            }
        };

        template<typename T>
        class RangeGenerator
        {
            T minimum_;
            T maximum_;
            size_t index_ = 0;
        public:
            RangeGenerator( T minimum, T maximum ) : minimum_( minimum ), maximum_( maximum ) { }

            T operator()( )
            {
                constexpr size_t Samples = 4096;
                const auto fraction = static_cast<T>( index_++ % Samples ) / static_cast<T>( Samples - 1 );
                return minimum_ * ( static_cast<T>( 1 ) - fraction ) + maximum_ * fraction;
            }
        };
    }

    class NumericTest
    {
    public:
        explicit NumericTest( const char* ) { }

        template<typename Generator, typename Expected, typename Actual,
            typename T = decltype( std::declval<Generator&>()() )>
        bool Run( Generator& generator, Expected expected, Actual actual, std::initializer_list<long double> boundaryValues = { } )
        {
            for ( size_t i = 0; i < 4096; ++i )
            {
                const auto value = generator( );
                if ( !HarlinnMathTest::Near( expected( value ), actual( value ), 1e-5 ) )
                {
                    return false;
                }
            }
            for ( const auto boundaryValue : boundaryValues )
            {
                const auto value = static_cast<T>( boundaryValue );
                if ( !HarlinnMathTest::Near( expected( value ), actual( value ), 1e-5 ) )
                {
                    return false;
                }
            }
            return true;
        }
    };
}

using namespace Harlinn;
using namespace Harlinn::Math;

template<typename T, size_t Count>
using RandomGenerator = Test::Generators::RandomGenerator<T, Count>;

template<typename... Args>
void PrintLn( const char* message, Args&&... )
{
    std::cerr << message << '\n';
}

template<typename... Args>
void PrintLn( const wchar_t* message, Args&&... )
{
    std::wcerr << message << L'\n';
}

using HarlinnMathTest::Equal;
using HarlinnMathTest::Deviation;
