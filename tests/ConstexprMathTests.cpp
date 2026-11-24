#include "test_support.h"

#include <catch2/matchers/catch_matchers_floating_point.hpp>

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
namespace OpenLibM = Harlinn::Math::Internal::OpenLibM;
namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };
}
TEST_CASE("ConstexprMathTests / FloatConstantsTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    // Verify basic constexpr float value classification properties.

    constexpr auto falseExpected1 = IsSameValue( C::Infinity, C::NegativeInfinity );
    CHECK(falseExpected1 == false);
    constexpr auto falseExpected2 = IsSameValue( C::NaN, C::NegativeNaN );
    CHECK(falseExpected2 == false);

    constexpr auto trueExpected1 = IsNaN( C::NaN );
    CHECK(trueExpected1);

    constexpr auto trueExpected2 = IsNaN( C::NegativeNaN );
    CHECK(trueExpected2);

    constexpr auto trueExpected3 = IsInf( C::Infinity );
    CHECK(trueExpected3);

    constexpr auto trueExpected4 = IsInf( C::NegativeInfinity );
    CHECK(trueExpected4);

    constexpr auto falseExpected3 = IsNaN( C::Max );
    CHECK(falseExpected3 == false);

    constexpr auto falseExpected4 = IsNaN( C::Min );
    CHECK(falseExpected4 == false);

    constexpr auto falseExpected5 = IsNaN( C::Lowest );
    CHECK(falseExpected5 == false);

    constexpr auto falseExpected6 = IsInf( C::Max );
    CHECK(falseExpected6 == false);

    constexpr auto falseExpected7 = IsInf( C::Min );
    CHECK(falseExpected7 == false);

    constexpr auto falseExpected8 = IsInf( C::Lowest );
    CHECK(falseExpected8 == false);


}
TEST_CASE("ConstexprMathTests / DoubleConstantsTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;

    // Verify basic constexpr double value classification properties.

    constexpr auto falseExpected1 = IsSameValue( C::Infinity, C::NegativeInfinity );
    CHECK(falseExpected1 == false);
    constexpr auto falseExpected2 = IsSameValue( C::NaN, C::NegativeNaN );
    CHECK(falseExpected2 == false);

    constexpr auto trueExpected1 = IsNaN( C::NaN );
    CHECK(trueExpected1);

    constexpr auto trueExpected2 = IsNaN( C::NegativeNaN );
    CHECK(trueExpected2);

    constexpr auto trueExpected3 = IsInf( C::Infinity );
    CHECK(trueExpected3);

    constexpr auto trueExpected4 = IsInf( C::NegativeInfinity );
    CHECK(trueExpected4);

    constexpr auto falseExpected3 = IsNaN( C::Max );
    CHECK(falseExpected3 == false);

    constexpr auto falseExpected4 = IsNaN( C::Min );
    CHECK(falseExpected4 == false);

    constexpr auto falseExpected5 = IsNaN( C::Lowest );
    CHECK(falseExpected5 == false);

    constexpr auto falseExpected6 = IsInf( C::Max );
    CHECK(falseExpected6 == false);

    constexpr auto falseExpected7 = IsInf( C::Min );
    CHECK(falseExpected7 == false);

    constexpr auto falseExpected8 = IsInf( C::Lowest );
    CHECK(falseExpected8 == false);

}
TEST_CASE("ConstexprMathTests / boolSignumTest1", "[math][ConstexprMathTests]")
{
    constexpr auto falseBoolVal = signum( static_cast< bool >( false ) );
    CHECK(falseBoolVal == false);
    constexpr auto trueBoolVal = signum( static_cast< bool >( true ) );
    CHECK(trueBoolVal == true);
}
TEST_CASE("ConstexprMathTests / SByteSignumTest1", "[math][ConstexprMathTests]")
{
    constexpr auto negativeValue = signum( static_cast< SByte >( -2 ) );
    CHECK(negativeValue == -1);
    constexpr auto zeroValue = signum( static_cast< SByte >( 0 ) );
    CHECK(zeroValue == 0);
    constexpr auto positiveValue = signum( static_cast< SByte >( 2 ) );
    CHECK(positiveValue == 1);
}
TEST_CASE("ConstexprMathTests / ByteSignumTest1", "[math][ConstexprMathTests]")
{
    constexpr auto positiveValue1 = signum( static_cast< Byte >( -2 ) );
    CHECK(positiveValue1 == 1);
    constexpr auto zeroValue = signum( static_cast< Byte >( 0 ) );
    CHECK(zeroValue == 0);
    constexpr auto positiveValue2 = signum( static_cast< Byte >( 2 ) );
    CHECK(positiveValue2 == 1);
}
TEST_CASE("ConstexprMathTests / Int16SignumTest1", "[math][ConstexprMathTests]")
{
    constexpr auto negativeValue = signum( static_cast< Int16 >( -2 ) );
    CHECK(negativeValue == -1);
    constexpr auto zeroValue = signum( static_cast< Int16 >( 0 ) );
    CHECK(zeroValue == 0);
    constexpr auto positiveValue = signum( static_cast< Int16 >( 2 ) );
    CHECK(positiveValue == 1);
}
TEST_CASE("ConstexprMathTests / UInt16SignumTest1", "[math][ConstexprMathTests]")
{
    constexpr auto positiveValue1 = signum( static_cast< UInt16 >( -2 ) );
    CHECK(positiveValue1 == 1);
    constexpr auto zeroValue = signum( static_cast< UInt16 >( 0 ) );
    CHECK(zeroValue == 0);
    constexpr auto positiveValue2 = signum( static_cast< UInt16 >( 2 ) );
    CHECK(positiveValue2 == 1);
}
TEST_CASE("ConstexprMathTests / Int32SignumTest1", "[math][ConstexprMathTests]")
{
    constexpr auto negativeValue = signum( static_cast< Int32 >( -2 ) );
    CHECK(negativeValue == -1);
    constexpr auto zeroValue = signum( static_cast< Int32 >( 0 ) );
    CHECK(zeroValue == 0);
    constexpr auto positiveValue = signum( static_cast< Int32 >( 2 ) );
    CHECK(positiveValue == 1);
}
TEST_CASE("ConstexprMathTests / UInt32SignumTest1", "[math][ConstexprMathTests]")
{
    constexpr auto positiveValue1 = signum( static_cast< UInt32 >( -2 ) );
    CHECK(positiveValue1 == 1);
    constexpr auto zeroValue = signum( static_cast< UInt32 >( 0 ) );
    CHECK(zeroValue == 0);
    constexpr auto positiveValue2 = signum( static_cast< UInt32 >( 2 ) );
    CHECK(positiveValue2 == 1);
}
TEST_CASE("ConstexprMathTests / Int64SignumTest1", "[math][ConstexprMathTests]")
{
    constexpr auto negativeValue = signum( static_cast< Int64 >( -2 ) );
    CHECK(negativeValue == -1);
    constexpr auto zeroValue = signum( static_cast< Int64 >( 0 ) );
    CHECK(zeroValue == 0);
    constexpr auto positiveValue = signum( static_cast< Int64 >( 2 ) );
    CHECK(positiveValue == 1);
}
TEST_CASE("ConstexprMathTests / UInt64SignumTest1", "[math][ConstexprMathTests]")
{
    constexpr auto positiveValue1 = signum( static_cast< UInt64 >( -2 ) );
    CHECK(positiveValue1 == 1);
    constexpr auto zeroValue = signum( static_cast< UInt64 >( 0 ) );
    CHECK(zeroValue == 0);
    constexpr auto positiveValue2 = signum( static_cast< UInt64 >( 2 ) );
    CHECK(positiveValue2 == 1);
}
TEST_CASE("ConstexprMathTests / wchar_tSignumTest1", "[math][ConstexprMathTests]")
{
    constexpr auto convertedNegative = static_cast< wchar_t >( -2 );
    constexpr auto convertedSign = signum( convertedNegative );
    constexpr auto expectedSign = std::is_signed_v<wchar_t> ? -1 : 1;
    static_assert( convertedSign == expectedSign );
    CHECK( convertedSign == expectedSign );

    constexpr auto lowestSign = signum( std::numeric_limits<wchar_t>::lowest( ) );
    constexpr auto expectedLowestSign = std::is_signed_v<wchar_t> ? -1 : 0;
    static_assert( lowestSign == expectedLowestSign );
    CHECK( lowestSign == expectedLowestSign );

    constexpr auto zeroValue = signum( static_cast< wchar_t >( 0 ) );
    static_assert( zeroValue == 0 );
    CHECK( zeroValue == 0 );
    constexpr auto positiveValue = signum( static_cast< wchar_t >( 2 ) );
    static_assert( positiveValue == 1 );
    CHECK( positiveValue == 1 );
    constexpr auto maximumSign = signum( std::numeric_limits<wchar_t>::max( ) );
    static_assert( maximumSign == 1 );
    CHECK( maximumSign == 1 );
}
TEST_CASE("ConstexprMathTests / SingleSignumTest1", "[math][ConstexprMathTests]")
{
    constexpr auto negativeValue = signum( static_cast< float >( -2 ) );
    CHECK(negativeValue == -1);
    constexpr auto zeroValue = signum( static_cast< float >( 0 ) );
    CHECK(zeroValue == 0);
    constexpr auto positiveValue = signum( static_cast< float >( 2 ) );
    CHECK(positiveValue == 1);
}
TEST_CASE("ConstexprMathTests / DoubleSignumTest1", "[math][ConstexprMathTests]")
{
    constexpr auto negativeValue = signum( static_cast< double >( -2 ) );
    CHECK(negativeValue == -1);
    constexpr auto zeroValue = signum( static_cast< double >( 0 ) );
    CHECK(zeroValue == 0);
    constexpr auto positiveValue = signum( static_cast< double >( 2 ) );
    CHECK(positiveValue == 1);
}
TEST_CASE("ConstexprMathTests / FloatNextAfterTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;
    constexpr auto result1 = NextAfter( C::Zero, C::Infinity );
    
    auto expected1 = std::nextafter( C::Zero, C::Infinity );
    CHECK(result1 == expected1);

    constexpr auto result2 = NextAfter( C::Zero, C::NegativeInfinity );
    auto expected2 = std::nextafter( C::Zero, C::NegativeInfinity );
    CHECK(result2 == expected2);

    constexpr auto result3 = NextAfter( C::Max, C::Infinity );
    auto expected3 = std::nextafter( C::Max, C::Infinity );
    CHECK(result3 == expected3);

    constexpr auto result4 = NextAfter( C::Max, C::NegativeInfinity );
    auto expected4 = std::nextafter( C::Max, C::NegativeInfinity );
    CHECK(result4 == expected4);

    constexpr auto result5 = NextAfter( C::Min, C::Infinity );
    auto expected5 = std::nextafter( C::Min, C::Infinity );
    CHECK(result5 == expected5);

    constexpr auto result6 = NextAfter( C::Min, C::NegativeInfinity );
    auto expected6 = std::nextafter( C::Min, C::NegativeInfinity );
    CHECK(result6 == expected6);

    constexpr auto result7 = NextAfter( C::Lowest, C::Infinity );
    auto expected7 = std::nextafter( C::Lowest, C::Infinity );
    CHECK(result7 == expected7);

    constexpr auto result8 = NextAfter( C::Lowest, C::NegativeInfinity );
    auto expected8 = std::nextafter( C::Lowest, C::NegativeInfinity );
    CHECK(result8 == expected8);
}
TEST_CASE("ConstexprMathTests / DoubleNextAfterTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;
    constexpr auto result1 = NextAfter( C::Zero, C::Infinity );
    auto expected1 = std::nextafter( C::Zero, C::Infinity );
    CHECK(result1 == expected1);

    constexpr auto result2 = NextAfter( C::Zero, C::NegativeInfinity );
    auto expected2 = std::nextafter( C::Zero, C::NegativeInfinity );
    CHECK(result2 == expected2);

    constexpr auto result3 = NextAfter( C::Max, C::Infinity );
    auto expected3 = std::nextafter( C::Max, C::Infinity );
    CHECK(result3 == expected3);

    constexpr auto result4 = NextAfter( C::Max, C::NegativeInfinity );
    auto expected4 = std::nextafter( C::Max, C::NegativeInfinity );
    CHECK(result4 == expected4);

    constexpr auto result5 = NextAfter( C::Min, C::Infinity );
    auto expected5 = std::nextafter( C::Min, C::Infinity );
    CHECK(result5 == expected5);

    constexpr auto result6 = NextAfter( C::Min, C::NegativeInfinity );
    static_assert( NextAfter( C::Min, C::NegativeInfinity ) != 0.0 );
    auto expected6 = std::nextafter( C::Min, C::NegativeInfinity );
    CHECK(result6 == expected6);

    constexpr auto result7 = NextAfter( C::Lowest, C::Infinity );
    auto expected7 = std::nextafter( C::Lowest, C::Infinity );
    CHECK(result7 == expected7);

    constexpr auto result8 = NextAfter( C::Lowest, C::NegativeInfinity );
    auto expected8 = std::nextafter( C::Lowest, C::NegativeInfinity );
    CHECK(result8 == expected8);

}
TEST_CASE("ConstexprMathTests / FloatSqrtTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;
    constexpr auto result1 = Sqrt( C::NaN );
    CHECK(IsNaN( result1 ));

    constexpr auto result2 = Sqrt( C::NegativeNaN );
    CHECK(IsNaN( result2 ));

    constexpr auto result3 = Sqrt( C::Infinity );
    CHECK(IsInf( result3 ));

    constexpr auto result4 = Sqrt( C::NegativeInfinity );
    CHECK(IsNaN( result4 ));

    constexpr auto result5 = Sqrt( -C::Min );
    CHECK(IsNaN( result5 ));

    constexpr auto result6 = Sqrt( C::Zero );
    CHECK(result6 == C::Zero);

    constexpr auto result7 = Sqrt( C::Min );
    auto expected7 = std::sqrt( C::Min );
    CHECK(result7 == expected7);

    constexpr auto result8 = Sqrt( C::Max );
    auto expected8 = std::sqrt( C::Max );
    CHECK(result8 == expected8);
}
TEST_CASE("ConstexprMathTests / DoubleSqrtTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;
    constexpr auto result1 = Sqrt( C::NaN );
    CHECK(IsNaN( result1 ));

    constexpr auto result2 = Sqrt( C::NegativeNaN );
    CHECK(IsNaN( result2 ));

    constexpr auto result3 = Sqrt( C::Infinity );
    CHECK(IsInf( result3 ));

    constexpr auto result4 = Sqrt( C::NegativeInfinity );
    CHECK(IsNaN( result4 ));

    constexpr auto result5 = Sqrt( -C::Min );
    CHECK(IsNaN( result5 ));

    constexpr auto result6 = Sqrt( C::Zero );
    CHECK(result6 == C::Zero);

    constexpr auto result7 = Sqrt( C::Min );
    auto expected7 = std::sqrt( C::Min );
    CHECK(result7 == expected7);

    constexpr auto result8 = Sqrt( C::Max );
    auto expected8 = std::sqrt( C::Max );
    CHECK(result8 == expected8);
}
TEST_CASE("ConstexprMathTests / FloatReciprocalSqrtTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;
    constexpr auto result1 = ReciprocalSqrt( C::NaN );
    CHECK(IsNaN( result1 ));

    constexpr auto result2 = ReciprocalSqrt( C::NegativeNaN );
    CHECK(IsNaN( result2 ));

    constexpr auto result3 = ReciprocalSqrt( C::Infinity );
    CHECK(result3 == C::Zero);

    constexpr auto result4 = ReciprocalSqrt( C::NegativeInfinity );
    CHECK(IsNaN( result4 ));

    constexpr auto result5 = ReciprocalSqrt( -C::Min );
    CHECK(IsNaN( result5 ));

    constexpr auto result6 = ReciprocalSqrt( C::Zero );
    CHECK(IsInf( result6 ));

    constexpr auto result7 = ReciprocalSqrt( C::Min );
    auto expected7 = C::One / std::sqrt( C::Min );
    CHECK(result7 == expected7);

    constexpr auto result8 = ReciprocalSqrt( C::Max );
    auto expected8 = C::One / std::sqrt( C::Max );
    CHECK(result8 == expected8);
}
TEST_CASE("ConstexprMathTests / DoubleReciprocalSqrtTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;
    constexpr auto result1 = ReciprocalSqrt( C::NaN );
    CHECK(IsNaN( result1 ));

    constexpr auto result2 = ReciprocalSqrt( C::NegativeNaN );
    CHECK(IsNaN( result2 ));

    constexpr auto result3 = ReciprocalSqrt( C::Infinity );
    CHECK(result3 == C::Zero);

    constexpr auto result4 = ReciprocalSqrt( C::NegativeInfinity );
    CHECK(IsNaN( result4 ));

    constexpr auto result5 = ReciprocalSqrt( -C::Min );
    CHECK(IsNaN( result5 ));

    constexpr auto result6 = ReciprocalSqrt( C::Zero );
    CHECK(IsInf( result6 ));

    constexpr auto result7 = ReciprocalSqrt( C::Min );
    auto expected7 = C::One / std::sqrt( C::Min );
    CHECK(result7 == expected7);

    constexpr auto result8 = ReciprocalSqrt( C::Max );
    auto expected8 = C::One / std::sqrt( C::Max );
    CHECK(result8 == expected8);
}
TEST_CASE("ConstexprMathTests / FloatCbrtTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;
    constexpr auto result1 = Cbrt( C::NaN );
    CHECK(IsNaN( result1 ));

    constexpr auto result2 = Cbrt( C::NegativeNaN );
    CHECK(IsNaN( result2 ));

    constexpr auto result3 = Cbrt( C::Infinity );
    CHECK(IsInf( result3 ));

    constexpr auto result4 = Cbrt( C::NegativeInfinity );
    auto expected4 = std::cbrt( C::NegativeInfinity );
    CHECK(result4 == expected4);

    constexpr auto result5 = Cbrt( -C::Min );
    auto expected5 = std::cbrt( -C::Min );
    CHECK(result5 == expected5);

    constexpr auto result6 = Cbrt( C::Zero );
    CHECK(result6 == C::Zero);

    constexpr auto result7 = Cbrt( C::Min );
    auto expected7 = std::cbrt( C::Min );
    CHECK(result7 == expected7);

    constexpr auto result8 = Cbrt( C::Max );
    auto expected8 = std::cbrt( C::Max );
    auto v = result8 / expected8;
    CHECK(AreNearlyEqual( v, 1.f ));
}
TEST_CASE("ConstexprMathTests / DoubleCbrtTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;
    constexpr auto result1 = Cbrt( C::NaN );
    CHECK(IsNaN( result1 ));

    constexpr auto result2 = Cbrt( C::NegativeNaN );
    CHECK(IsNaN( result2 ));

    constexpr auto result3 = Cbrt( C::Infinity );
    CHECK(IsInf( result3 ));

    constexpr auto result4 = Cbrt( C::NegativeInfinity );
    auto expected4 = std::cbrt( C::NegativeInfinity );
    CHECK(result4 == expected4);

    constexpr auto result5 = Cbrt( -C::Min );
    auto expected5 = std::cbrt( -C::Min );
    CHECK(AreNearlyEqual( result5, expected5 ));

    constexpr auto result6 = Cbrt( C::Zero );
    CHECK(result6 == C::Zero);

    constexpr auto result7 = Cbrt( C::Min );
    auto expected7 = std::cbrt( C::Min );
    CHECK(AreNearlyEqual( result7, expected7));

    constexpr auto result8 = Cbrt( C::Max );
    auto expected8 = std::cbrt( C::Max );
    auto v = result8 / expected8;
    CHECK(AreNearlyEqual( v, 1. ));
}
TEST_CASE("ConstexprMathTests / FloatNextDownTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;
    
    constexpr auto result1 = NextDown( C::NaN );
    CHECK(IsNaN( result1 ));

    constexpr auto result2 = NextDown( C::Infinity );
    constexpr auto expected2 = C::Max;
    CHECK(result2 == expected2);

    constexpr auto result3 = NextDown( C::Min );
    auto expected3 = std::nextafter( C::Min, 0.f );
    CHECK(result3 == expected3);

    constexpr auto result4 = NextDown( C::Zero );
    auto expected4 = std::nextafter( C::Zero, C::NegativeInfinity );
    CHECK(result4 == expected4);

    constexpr auto result5 = NextDown( C::Lowest );
    CHECK(IsInf( result5 ));
}
TEST_CASE("ConstexprMathTests / DoubleNextDownTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;

    constexpr auto result1 = NextDown( C::NaN );
    CHECK(IsNaN( result1 ));

    constexpr auto result2 = NextDown( C::Infinity );
    constexpr auto expected2 = C::Max;
    CHECK(result2 == expected2);

    constexpr auto result3 = NextDown( C::Min );
    auto expected3 = std::nextafter( C::Min, 0.f );
    CHECK(result3 == expected3);

    constexpr auto result4 = NextDown( C::Zero );
    auto expected4 = std::nextafter( C::Zero, C::NegativeInfinity );
    CHECK(result4 == expected4);

    constexpr auto result5 = NextDown( C::Lowest );
    CHECK(IsInf( result5 ));
}
TEST_CASE("ConstexprMathTests / FloatNextUpTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    constexpr auto result1 = NextUp( C::NaN );
    CHECK(IsNaN( result1 ));

    constexpr auto result2 = NextUp( C::NegativeInfinity );
    constexpr auto expected2 = C::Lowest;
    CHECK(result2 == expected2);

    constexpr auto result3 = NextUp( -C::Min );
    auto expected3 = std::nextafter( -C::Min, C::Zero );
    CHECK(result3 == expected3);

    constexpr auto result4 = NextUp( C::Zero );
    auto expected4 = std::nextafter( C::Zero, C::Infinity );
    CHECK(result4 == expected4);

    constexpr auto result5 = NextUp( C::Max );
    CHECK(IsInf( result5 ));
}
TEST_CASE("ConstexprMathTests / DoubleNextUpTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;

    constexpr auto result1 = NextUp( C::NaN );
    CHECK(IsNaN( result1 ));

    constexpr auto result2 = NextUp( C::NegativeInfinity );
    constexpr auto expected2 = C::Lowest;
    CHECK(result2 == expected2);

    constexpr auto result3 = NextUp( -C::Min );
    auto expected3 = std::nextafter( -C::Min, C::Zero );
    CHECK(result3 == expected3);

    constexpr auto result4 = NextUp( C::Zero );
    auto expected4 = std::nextafter( C::Zero, C::Infinity );
    CHECK(result4 == expected4);

    constexpr auto result5 = NextUp( C::Max );
    CHECK(IsInf( result5 ));
}
TEST_CASE("ConstexprMathTests / FloatIsSameValueTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    auto constexpr result1 = IsSameValue( C::NaN, C::NaN );
    CHECK(result1);
    auto constexpr result2 = IsSameValue( C::NegativeNaN, C::NegativeNaN );
    CHECK(result2);
    auto constexpr result3 = IsSameValue( C::sNaN, C::sNaN );
    CHECK(result3);
    auto constexpr result4 = IsSameValue( C::sNegativeNaN, C::sNegativeNaN );
    CHECK(result4);
    auto constexpr result5 = IsSameValue( C::NegativeInfinity, C::NegativeInfinity );
    CHECK(result5);
    auto constexpr result6 = IsSameValue( C::Lowest, C::Lowest );
    CHECK(result6);
    auto constexpr result7 = IsSameValue( -C::Min, -C::Min );
    CHECK(result7);
    auto constexpr result8 = IsSameValue( -C::DenormalMin, -C::DenormalMin );
    CHECK(result8);
    auto constexpr result9 = IsSameValue( -C::Zero, -C::Zero );
    CHECK(result9);
    auto constexpr result10 = IsSameValue( C::Zero, C::Zero );
    CHECK(result10);
    auto constexpr result11 = IsSameValue( C::DenormalMin, C::DenormalMin );
    CHECK(result11);
    auto constexpr result12 = IsSameValue( C::Min, C::Min );
    CHECK(result12);
    auto constexpr result13 = IsSameValue( C::Max, C::Max );
    CHECK(result13);
    auto constexpr result14 = IsSameValue( C::Infinity, C::Infinity );
    CHECK(result14);

    auto constexpr result15 = IsSameValue( C::NaN, C::sNaN );
    CHECK(result15);
    auto constexpr result16 = IsSameValue( C::NegativeNaN, C::NaN ) == false;
    CHECK(result16);
    auto constexpr result17 = IsSameValue( C::sNaN, C::sNegativeNaN ) == false;
    CHECK(result17);
    auto constexpr result18 = IsSameValue( C::Zero, -C::Zero ) == false;
    CHECK(result18);

}
TEST_CASE("ConstexprMathTests / DoubleIsSameValueTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;

    auto constexpr result1 = IsSameValue( C::NaN, C::NaN );
    CHECK(result1);
    auto constexpr result2 = IsSameValue( C::NegativeNaN, C::NegativeNaN );
    CHECK(result2);
    auto constexpr result3 = IsSameValue( C::sNaN, C::sNaN );
    CHECK(result3);
    auto constexpr result4 = IsSameValue( C::sNegativeNaN, C::sNegativeNaN );
    CHECK(result4);
    auto constexpr result5 = IsSameValue( C::NegativeInfinity, C::NegativeInfinity );
    CHECK(result5);
    auto constexpr result6 = IsSameValue( C::Lowest, C::Lowest );
    CHECK(result6);
    auto constexpr result7 = IsSameValue( -C::Min, -C::Min );
    CHECK(result7);
    auto constexpr result8 = IsSameValue( -C::DenormalMin, -C::DenormalMin );
    CHECK(result8);
    auto constexpr result9 = IsSameValue( -C::Zero, -C::Zero );
    CHECK(result9);
    auto constexpr result10 = IsSameValue( C::Zero, C::Zero );
    CHECK(result10);
    auto constexpr result11 = IsSameValue( C::DenormalMin, C::DenormalMin );
    CHECK(result11);
    auto constexpr result12 = IsSameValue( C::Min, C::Min );
    CHECK(result12);
    auto constexpr result13 = IsSameValue( C::Max, C::Max );
    CHECK(result13);
    auto constexpr result14 = IsSameValue( C::Infinity, C::Infinity );
    CHECK(result14);
}
TEST_CASE("ConstexprMathTests / FloatIsZeroTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    auto constexpr result1 = IsZero( C::NaN ) == false;
    CHECK(result1);
    auto constexpr result2 = IsZero( C::NegativeNaN ) == false;
    CHECK(result2);
    auto constexpr result3 = IsZero( C::sNaN ) == false;
    CHECK(result3);
    auto constexpr result4 = IsZero( C::sNegativeNaN ) == false;
    CHECK(result4);
    auto constexpr result5 = IsZero( C::NegativeInfinity ) == false;
    CHECK(result5);
    auto constexpr result6 = IsZero( C::Lowest ) == false;
    CHECK(result6);
    auto constexpr result7 = IsZero( -C::Min ) == false;
    CHECK(result7);
    auto constexpr result8 = IsZero( -C::DenormalMin ) == false;
    CHECK(result8);
    auto constexpr result9 = IsZero( -C::Zero );
    CHECK(result9);
    auto constexpr result10 = IsZero( C::Zero );
    CHECK(result10);
    auto constexpr result11 = IsZero( C::DenormalMin ) == false;
    CHECK(result11);
    auto constexpr result12 = IsZero( C::Min ) == false;
    CHECK(result12);
    auto constexpr result13 = IsZero( C::Max ) == false;
    CHECK(result13);
    auto constexpr result14 = IsZero( C::Infinity ) == false;
    CHECK(result14);
    auto constexpr result15 = IsZero( 0 );
    CHECK(result15);
}
TEST_CASE("ConstexprMathTests / DoubleIsZeroTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;

    auto constexpr result1 = IsZero( C::NaN ) == false;
    CHECK(result1);
    auto constexpr result2 = IsZero( C::NegativeNaN ) == false;
    CHECK(result2);
    auto constexpr result3 = IsZero( C::sNaN ) == false;
    CHECK(result3);
    auto constexpr result4 = IsZero( C::sNegativeNaN ) == false;
    CHECK(result4);
    auto constexpr result5 = IsZero( C::NegativeInfinity ) == false;
    CHECK(result5);
    auto constexpr result6 = IsZero( C::Lowest ) == false;
    CHECK(result6);
    auto constexpr result7 = IsZero( -C::Min ) == false;
    CHECK(result7);
    auto constexpr result8 = IsZero( -C::DenormalMin ) == false;
    CHECK(result8);
    auto constexpr result9 = IsZero( -C::Zero );
    CHECK(result9);
    auto constexpr result10 = IsZero( C::Zero );
    CHECK(result10);
    auto constexpr result11 = IsZero( C::DenormalMin ) == false;
    CHECK(result11);
    auto constexpr result12 = IsZero( C::Min ) == false;
    CHECK(result12);
    auto constexpr result13 = IsZero( C::Max ) == false;
    CHECK(result13);
    auto constexpr result14 = IsZero( C::Infinity ) == false;
    CHECK(result14);
    auto constexpr result15 = IsZero( 0 );
    CHECK(result15);
}
TEST_CASE("ConstexprMathTests / FloatIsNaNTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    auto constexpr result1 = IsNaN( C::NaN );
    CHECK(result1);
    auto constexpr result2 = IsNaN( C::NegativeNaN );
    CHECK(result2);
    auto constexpr result3 = IsNaN( C::sNaN );
    CHECK(result3);
    auto constexpr result4 = IsNaN( C::sNegativeNaN );
    CHECK(result4);
    auto constexpr result5 = IsNaN( C::NegativeInfinity ) == false;
    CHECK(result5);
    auto constexpr result6 = IsNaN( C::Lowest ) == false;
    CHECK(result6);
    auto constexpr result7 = IsNaN( -C::Min ) == false;
    CHECK(result7);
    auto constexpr result8 = IsNaN( -C::DenormalMin ) == false;
    CHECK(result8);
    auto constexpr result9 = IsNaN( -C::Zero ) == false;
    CHECK(result9);
    auto constexpr result10 = IsNaN( C::Zero ) == false;
    CHECK(result10);
    auto constexpr result11 = IsNaN( C::DenormalMin ) == false;
    CHECK(result11);
    auto constexpr result12 = IsNaN( C::Min ) == false;
    CHECK(result12);
    auto constexpr result13 = IsNaN( C::Max ) == false;
    CHECK(result13);
    auto constexpr result14 = IsNaN( C::Infinity ) == false;
    CHECK(result14);

    auto constexpr result15 = IsNaN( C::Max, C::NaN, C::Zero, 4, 0.3 );
    CHECK(result15);

}
TEST_CASE("ConstexprMathTests / DoubleIsNaNTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;

    auto constexpr result1 = IsNaN( C::NaN );
    CHECK(result1);
    auto constexpr result2 = IsNaN( C::NegativeNaN );
    CHECK(result2);
    auto constexpr result3 = IsNaN( C::sNaN );
    CHECK(result3);
    auto constexpr result4 = IsNaN( C::sNegativeNaN );
    CHECK(result4);
    auto constexpr result5 = IsNaN( C::NegativeInfinity ) == false;
    CHECK(result5);
    auto constexpr result6 = IsNaN( C::Lowest ) == false;
    CHECK(result6);
    auto constexpr result7 = IsNaN( -C::Min ) == false;
    CHECK(result7);
    auto constexpr result8 = IsNaN( -C::DenormalMin ) == false;
    CHECK(result8);
    auto constexpr result9 = IsNaN( -C::Zero ) == false;
    CHECK(result9);
    auto constexpr result10 = IsNaN( C::Zero ) == false;
    CHECK(result10);
    auto constexpr result11 = IsNaN( C::DenormalMin ) == false;
    CHECK(result11);
    auto constexpr result12 = IsNaN( C::Min ) == false;
    CHECK(result12);
    auto constexpr result13 = IsNaN( C::Max ) == false;
    CHECK(result13);
    auto constexpr result14 = IsNaN( C::Infinity ) == false;
    CHECK(result14);

    auto constexpr result15 = IsNaN( C::Max, C::NaN, C::Zero, 4, 0.3f );
    CHECK(result15);
}
TEST_CASE("ConstexprMathTests / FloatIsInfTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    auto constexpr result1 = IsInf( C::NaN ) == false;
    CHECK(result1);
    auto constexpr result2 = IsInf( C::NegativeNaN ) == false;
    CHECK(result2);
    auto constexpr result3 = IsInf( C::sNaN ) == false;
    CHECK(result3);
    auto constexpr result4 = IsInf( C::sNegativeNaN ) == false;
    CHECK(result4);
    auto constexpr result5 = IsInf( C::NegativeInfinity );
    CHECK(result5);
    auto constexpr result6 = IsInf( C::Lowest ) == false;
    CHECK(result6);
    auto constexpr result7 = IsInf( -C::Min ) == false;
    CHECK(result7);
    auto constexpr result8 = IsInf( -C::DenormalMin ) == false;
    CHECK(result8);
    auto constexpr result9 = IsInf( -C::Zero ) == false;
    CHECK(result9);
    auto constexpr result10 = IsInf( C::Zero ) == false;
    CHECK(result10);
    auto constexpr result11 = IsInf( C::DenormalMin ) == false;
    CHECK(result11);
    auto constexpr result12 = IsInf( C::Min ) == false;
    CHECK(result12);
    auto constexpr result13 = IsInf( C::Max ) == false;
    CHECK(result13);
    auto constexpr result14 = IsInf( C::Infinity );
    CHECK(result14);

    auto constexpr result15 = IsInf( C::Max, C::Infinity, C::Zero, 4, 0.3 );
    CHECK(result15);

}
TEST_CASE("ConstexprMathTests / DoubleIsInfTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;

    auto constexpr result1 = IsInf( C::NaN ) == false;
    CHECK(result1);
    auto constexpr result2 = IsInf( C::NegativeNaN ) == false;
    CHECK(result2);
    auto constexpr result3 = IsInf( C::sNaN ) == false;
    CHECK(result3);
    auto constexpr result4 = IsInf( C::sNegativeNaN ) == false;
    CHECK(result4);
    auto constexpr result5 = IsInf( C::NegativeInfinity );
    CHECK(result5);
    auto constexpr result6 = IsInf( C::Lowest ) == false;
    CHECK(result6);
    auto constexpr result7 = IsInf( -C::Min ) == false;
    CHECK(result7);
    auto constexpr result8 = IsInf( -C::DenormalMin ) == false;
    CHECK(result8);
    auto constexpr result9 = IsInf( -C::Zero ) == false;
    CHECK(result9);
    auto constexpr result10 = IsInf( C::Zero ) == false;
    CHECK(result10);
    auto constexpr result11 = IsInf( C::DenormalMin ) == false;
    CHECK(result11);
    auto constexpr result12 = IsInf( C::Min ) == false;
    CHECK(result12);
    auto constexpr result13 = IsInf( C::Max ) == false;
    CHECK(result13);
    auto constexpr result14 = IsInf( C::Infinity );
    CHECK(result14);

    auto constexpr result15 = IsInf( C::Max, C::Infinity, C::Zero, 4, 0.3 );
    CHECK(result15);

}
TEST_CASE("ConstexprMathTests / FloatIsFiniteTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    auto constexpr result1 = IsFinite( C::NaN ) == false;
    CHECK(result1);
    auto constexpr result2 = IsFinite( C::NegativeNaN ) == false;
    CHECK(result2);
    auto constexpr result3 = IsFinite( C::sNaN ) == false;
    CHECK(result3);
    auto constexpr result4 = IsFinite( C::sNegativeNaN ) == false;
    CHECK(result4);
    auto constexpr result5 = IsFinite( C::NegativeInfinity ) == false;
    CHECK(result5);
    auto constexpr result6 = IsFinite( C::Lowest );
    CHECK(result6);
    auto constexpr result7 = IsFinite( -C::Min );
    CHECK(result7);
    auto constexpr result8 = IsFinite( -C::DenormalMin );
    CHECK(result8);
    auto constexpr result9 = IsFinite( -C::Zero );
    CHECK(result9);
    auto constexpr result10 = IsFinite( C::Zero );
    CHECK(result10);
    auto constexpr result11 = IsFinite( C::DenormalMin );
    CHECK(result11);
    auto constexpr result12 = IsFinite( C::Min );
    CHECK(result12);
    auto constexpr result13 = IsFinite( C::Max );
    CHECK(result13);
    auto constexpr result14 = IsFinite( C::Infinity ) == false;
    CHECK(result14);

    auto constexpr result15 = IsFinite( C::Lowest, -C::Min );
    CHECK(result15);

    auto constexpr result16 = IsFinite( C::Lowest, -C::Min, -C::DenormalMin, -C::Zero, C::Zero, C::DenormalMin, C::Min, C::Max );
    CHECK(result16);

    auto constexpr result17 = IsFinite( C::Lowest, -C::Min, -C::DenormalMin, C::NaN, -C::Zero, C::Zero, C::DenormalMin, C::Min, C::Max ) == false;
    CHECK(result17);

    auto constexpr result18 = IsFinite( C::Lowest, 4 ,-C::Min, 0.3 );
    CHECK(result18);

    auto constexpr result19 = IsFinite( C::Lowest, C::NaN ) == false;
    CHECK(result19);
}
TEST_CASE("ConstexprMathTests / DoubleIsFiniteTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;

    auto constexpr result1 = IsFinite( C::NaN ) == false;
    CHECK(result1);
    auto constexpr result2 = IsFinite( C::NegativeNaN ) == false;
    CHECK(result2);
    auto constexpr result3 = IsFinite( C::sNaN ) == false;
    CHECK(result3);
    auto constexpr result4 = IsFinite( C::sNegativeNaN ) == false;
    CHECK(result4);
    auto constexpr result5 = IsFinite( C::NegativeInfinity ) == false;
    CHECK(result5);
    auto constexpr result6 = IsFinite( C::Lowest );
    CHECK(result6);
    auto constexpr result7 = IsFinite( -C::Min );
    CHECK(result7);
    auto constexpr result8 = IsFinite( -C::DenormalMin );
    CHECK(result8);
    auto constexpr result9 = IsFinite( -C::Zero );
    CHECK(result9);
    auto constexpr result10 = IsFinite( C::Zero );
    CHECK(result10);
    auto constexpr result11 = IsFinite( C::DenormalMin );
    CHECK(result11);
    auto constexpr result12 = IsFinite( C::Min );
    CHECK(result12);
    auto constexpr result13 = IsFinite( C::Max );
    CHECK(result13);
    auto constexpr result14 = IsFinite( C::Infinity ) == false;
    CHECK(result14);

    auto constexpr result15 = IsFinite( C::Lowest, -C::Min );
    CHECK(result15);

    auto constexpr result16 = IsFinite( C::Lowest, -C::Min, -C::DenormalMin, -C::Zero, C::Zero, C::DenormalMin, C::Min, C::Max );
    CHECK(result16);

    auto constexpr result17 = IsFinite( C::Lowest, -C::Min, -C::DenormalMin, C::NaN, -C::Zero, C::Zero, C::DenormalMin, C::Min, C::Max ) == false;
    CHECK(result17);

    auto constexpr result18 = IsFinite( C::Lowest, 4, -C::Min, 0.3f );
    CHECK(result18);

    auto constexpr result19 = IsFinite( C::Lowest, C::NaN ) == false;
    CHECK(result19);
}
TEST_CASE("ConstexprMathTests / FloatIsNormalTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    auto constexpr result1 = IsNormal( C::NaN ) == false;
    CHECK(result1);
    auto constexpr result2 = IsNormal( C::NegativeNaN ) == false;
    CHECK(result2);
    auto constexpr result3 = IsNormal( C::sNaN ) == false;
    CHECK(result3);
    auto constexpr result4 = IsNormal( C::sNegativeNaN ) == false;
    CHECK(result4);
    auto constexpr result5 = IsNormal( C::NegativeInfinity ) == false;
    CHECK(result5);
    auto constexpr result6 = IsNormal( C::Lowest );
    CHECK(result6);
    auto constexpr result7 = IsNormal( -C::Min );
    CHECK(result7);
    auto constexpr result8 = IsNormal( -C::DenormalMin ) == false;
    CHECK(result8);
    auto constexpr result9 = IsNormal( -C::Zero ) == false;
    CHECK(result9);
    auto constexpr result10 = IsNormal( C::Zero ) == false;
    CHECK(result10);
    auto constexpr result11 = IsNormal( C::DenormalMin ) == false;
    CHECK(result11);
    auto constexpr result12 = IsNormal( C::Min );
    CHECK(result12);
    auto constexpr result13 = IsNormal( C::Max );
    CHECK(result13);
    auto constexpr result14 = IsNormal( C::Infinity ) == false;
    CHECK(result14);

    auto constexpr result15 = IsNormal( C::Lowest, -C::Min );
    CHECK(result15);

    auto constexpr result16 = IsNormal( C::Lowest, 0 ,C::Min ) == false;
    CHECK(result16);


}
TEST_CASE("ConstexprMathTests / DoubleIsNormalTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;

    auto constexpr result1 = IsNormal( C::NaN ) == false;
    CHECK(result1);
    auto constexpr result2 = IsNormal( C::NegativeNaN ) == false;
    CHECK(result2);
    auto constexpr result3 = IsNormal( C::sNaN ) == false;
    CHECK(result3);
    auto constexpr result4 = IsNormal( C::sNegativeNaN ) == false;
    CHECK(result4);
    auto constexpr result5 = IsNormal( C::NegativeInfinity ) == false;
    CHECK(result5);
    auto constexpr result6 = IsNormal( C::Lowest );
    CHECK(result6);
    auto constexpr result7 = IsNormal( -C::Min );
    CHECK(result7);
    auto constexpr result8 = IsNormal( -C::DenormalMin ) == false;
    CHECK(result8);
    auto constexpr result9 = IsNormal( -C::Zero ) == false;
    CHECK(result9);
    auto constexpr result10 = IsNormal( C::Zero ) == false;
    CHECK(result10);
    auto constexpr result11 = IsNormal( C::DenormalMin ) == false;
    CHECK(result11);
    auto constexpr result12 = IsNormal( C::Min );
    CHECK(result12);
    auto constexpr result13 = IsNormal( C::Max );
    CHECK(result13);
    auto constexpr result14 = IsNormal( C::Infinity ) == false;
    CHECK(result14);
}
TEST_CASE("ConstexprMathTests / FloatAbsTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;
    
    auto constexpr result1 = IsNaN( Abs( C::NaN ) );
    CHECK(result1);
    auto constexpr result2 = IsNaN( Abs( C::NegativeNaN ) );
    CHECK(result2);
    auto constexpr result3 = IsNaN( Abs( C::sNaN ) );
    CHECK(result3);
    auto constexpr result4 = IsNaN( Abs( C::sNegativeNaN ) );
    CHECK(result4);

    auto constexpr result5 = Abs( C::NegativeInfinity );
    CHECK(IsSameValue( result5, C::Infinity ));
    auto constexpr result6 = Abs( C::Lowest );
    CHECK(IsSameValue( result6, C::Max ));
    auto constexpr result7 = Abs( -C::Min );
    CHECK(IsSameValue( result7, C::Min ));
    auto constexpr result8 = Abs( -C::DenormalMin );
    CHECK(IsSameValue( result8, C::DenormalMin ));
    auto constexpr result9 = Abs( -C::Zero );
    CHECK(IsSameValue( result9, C::Zero ));
}
TEST_CASE("ConstexprMathTests / DoubleAbsTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;

    auto constexpr result1 = IsNaN( Abs( C::NaN ) );
    CHECK(result1);
    auto constexpr result2 = IsNaN( Abs( C::NegativeNaN ) );
    CHECK(result2);
    auto constexpr result3 = IsNaN( Abs( C::sNaN ) );
    CHECK(result3);
    auto constexpr result4 = IsNaN( Abs( C::sNegativeNaN ) );
    CHECK(result4);

    auto constexpr result5 = Abs( C::NegativeInfinity );
    CHECK(IsSameValue( result5, C::Infinity ));
    auto constexpr result6 = Abs( C::Lowest );
    CHECK(IsSameValue( result6, C::Max ));
    auto constexpr result7 = Abs( -C::Min );
    CHECK(IsSameValue( result7, C::Min ));
    auto constexpr result8 = Abs( -C::DenormalMin );
    CHECK(IsSameValue( result8, C::DenormalMin ));
    auto constexpr result9 = Abs( -C::Zero );
    CHECK(IsSameValue( result9, C::Zero ));
}
TEST_CASE("ConstexprMathTests / IntegralAbsTest1", "[math][ConstexprMathTests]")
{
    constexpr auto result1 = Abs( -1 );
    constexpr auto expected1 = 1;
    constexpr auto success1 = result1 == expected1;
    CHECK(success1);

    constexpr auto result2 = Abs( MinInt32 + 1 );
    constexpr auto expected2 = MaxInt32;
    constexpr auto success2 = result2 == expected2;
    CHECK(success2);


    constexpr auto result3 = Abs( -1LL );
    constexpr auto expected3 = 1;
    constexpr auto success3 = result3 == expected3;
    CHECK(success3);

    constexpr auto result4 = Abs( MinInt64 + 1 );
    constexpr auto expected4 = MaxInt64;
    constexpr auto success4 = result4 == expected4;
    CHECK(success4);

    constexpr auto result5 = Abs( MinInt64 );
    constexpr auto expected5 = MaxInt64;
    constexpr auto success5 = result5 == expected5;
    CHECK(success5);

    constexpr auto result6 = Abs( MinInt32 );
    constexpr auto expected6 = MaxInt32;
    constexpr auto success6 = result6 == expected6;
    CHECK(success6);

    constexpr auto result7 = Abs( MinInt16 );
    constexpr auto expected7 = MaxInt16;
    constexpr auto success7 = result7 == expected7;
    CHECK(success7);

    constexpr auto result8 = Abs( MinInt8 );
    constexpr auto expected8 = MaxInt8;
    constexpr auto success8 = result8 == expected8;
    CHECK(success8);

    constexpr auto result9 = UnsignedAbs( MinInt64 );
    constexpr auto expected9 = std::bit_cast< UInt64 >( MinInt64 );
    constexpr auto success9 = result9 == expected9;
    CHECK(success9);

    constexpr auto result10 = UnsignedAbs( MinInt32 );
    constexpr auto expected10 = std::bit_cast< UInt32 >( MinInt32 );
    constexpr auto success10 = result10 == expected10;
    CHECK(success10);

    constexpr auto result11 = UnsignedAbs( MinInt16 );
    constexpr auto expected11 = std::bit_cast< UInt16 >( MinInt16 );
    constexpr auto success11 = result11 == expected11;
    CHECK(success11);

    constexpr auto result12 = UnsignedAbs( MinInt8 );
    constexpr auto expected12 = std::bit_cast< Byte >( MinInt8 );
    constexpr auto success12 = result12 == expected12;
    CHECK(success12);


}
TEST_CASE("ConstexprMathTests / FloatFastAbsTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    auto constexpr result1 = IsNaN( FastAbs( C::NaN ) );
    CHECK(result1);
    auto constexpr result2 = IsNaN( FastAbs( C::NegativeNaN ) );
    CHECK(result2);
    auto constexpr result3 = IsNaN( FastAbs( C::sNaN ) );
    CHECK(result3);
    auto constexpr result4 = IsNaN( FastAbs( C::sNegativeNaN ) );
    CHECK(result4);

    auto constexpr result5 = FastAbs( C::NegativeInfinity );
    CHECK(IsSameValue( result5, C::Infinity ));
    auto constexpr result6 = FastAbs( C::Lowest );
    CHECK(IsSameValue( result6, C::Max ));
    auto constexpr result7 = FastAbs( -C::Min );
    CHECK(IsSameValue( result7, C::Min ));
    auto constexpr result8 = FastAbs( -C::DenormalMin );
    CHECK(IsSameValue( result8, C::DenormalMin ));
    auto constexpr result9 = FastAbs( -C::Zero );
    CHECK(IsSameValue( result9, C::Zero ));
}
TEST_CASE("ConstexprMathTests / DoubleFastAbsTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;

    auto constexpr result1 = IsNaN( FastAbs( C::NaN ) );
    CHECK(result1);
    auto constexpr result2 = IsNaN( FastAbs( C::NegativeNaN ) );
    CHECK(result2);
    auto constexpr result3 = IsNaN( FastAbs( C::sNaN ) );
    CHECK(result3);
    auto constexpr result4 = IsNaN( FastAbs( C::sNegativeNaN ) );
    CHECK(result4);

    auto constexpr result5 = FastAbs( C::NegativeInfinity );
    CHECK(IsSameValue( result5, C::Infinity ));
    auto constexpr result6 = FastAbs( C::Lowest );
    CHECK(IsSameValue( result6, C::Max ));
    auto constexpr result7 = FastAbs( -C::Min );
    CHECK(IsSameValue( result7, C::Min ));
    auto constexpr result8 = FastAbs( -C::DenormalMin );
    CHECK(IsSameValue( result8, C::DenormalMin ));
    auto constexpr result9 = FastAbs( -C::Zero );
    CHECK(IsSameValue( result9, C::Zero ));
}
TEST_CASE("ConstexprMathTests / IntegralFastAbsTest1", "[math][ConstexprMathTests]")
{
    constexpr auto result1 = FastAbs( -1 );
    constexpr auto expected1 = 1;
    constexpr auto success1 = result1 == expected1;
    CHECK(success1);

    constexpr auto result2 = FastAbs( MinInt32 + 1 );
    constexpr auto expected2 = MaxInt32;
    constexpr auto success2 = result2 == expected2;
    CHECK(success2);


    constexpr auto result3 = FastAbs( -1LL );
    constexpr auto expected3 = 1;
    constexpr auto success3 = result3 == expected3;
    CHECK(success3);

    constexpr auto result4 = FastAbs( MinInt64 + 1 );
    constexpr auto expected4 = MaxInt64;
    constexpr auto success4 = result4 == expected4;
    CHECK(success4);

    constexpr auto result5 = FastAbs( 1 );
    constexpr auto expected5 = 1;
    constexpr auto success5 = result5 == expected5;
    CHECK(success5);

    constexpr auto result6 = FastAbs( static_cast<SByte>( -1 ) );
    constexpr auto expected6 = 1;
    constexpr auto success6 = result6 == expected6;
    CHECK(success6);

    constexpr auto result7 = FastAbs( static_cast< Int16 >( -1 ) );
    constexpr auto expected7 = 1;
    constexpr auto success7 = result7 == expected7;
    CHECK(success7);

    constexpr auto result8 = FastAbs( static_cast< Int32 >( -1 ) );
    constexpr auto expected8 = 1;
    constexpr auto success8 = result8 == expected8;
    CHECK(success8);

    constexpr auto result9 = FastAbs( static_cast< Int64 >( -1 ) );
    constexpr auto expected9 = 1;
    constexpr auto success9 = result9 == expected9;
    CHECK(success9);




}
TEST_CASE("ConstexprMathTests / FloatSignBitTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    auto constexpr result1 = Math::SignBit( C::NaN ) == false;
    CHECK(result1);
    auto constexpr result2 = Math::SignBit( C::NegativeNaN );
    CHECK(result2);
    auto constexpr result3 = Math::SignBit( C::sNaN ) == false;
    CHECK(result3);
    auto constexpr result4 = Math::SignBit( C::sNegativeNaN );
    CHECK(result4);
    auto constexpr result5 = Math::SignBit( C::NegativeInfinity );
    CHECK(result5);
    auto constexpr result6 = Math::SignBit( C::Lowest );
    CHECK(result6);
    auto constexpr result7 = Math::SignBit( -C::Min );
    CHECK(result7);
    auto constexpr result8 = Math::SignBit( -C::DenormalMin );
    CHECK(result8);
    auto constexpr result9 = Math::SignBit( -C::Zero );
    CHECK(result9);
    auto constexpr result10 = Math::SignBit( C::Zero ) == false;
    CHECK(result10);
    auto constexpr result11 = Math::SignBit( C::DenormalMin ) == false;
    CHECK(result11);
    auto constexpr result12 = Math::SignBit( C::Min ) == false;
    CHECK(result12);
    auto constexpr result13 = Math::SignBit( C::Max ) == false;
    CHECK(result13);
    auto constexpr result14 = Math::SignBit( C::Infinity ) == false;
    CHECK(result14);
}
TEST_CASE("ConstexprMathTests / DoubleSignBitTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;

    auto constexpr result1 = Math::SignBit( C::NaN ) == false;
    CHECK(result1);
    auto constexpr result2 = Math::SignBit( C::NegativeNaN );
    CHECK(result2);
    auto constexpr result3 = Math::SignBit( C::sNaN ) == false;
    CHECK(result3);
    auto constexpr result4 = Math::SignBit( C::sNegativeNaN );
    CHECK(result4);
    auto constexpr result5 = Math::SignBit( C::NegativeInfinity );
    CHECK(result5);
    auto constexpr result6 = Math::SignBit( C::Lowest );
    CHECK(result6);
    auto constexpr result7 = Math::SignBit( -C::Min );
    CHECK(result7);
    auto constexpr result8 = Math::SignBit( -C::DenormalMin );
    CHECK(result8);
    auto constexpr result9 = Math::SignBit( -C::Zero );
    CHECK(result9);
    auto constexpr result10 = Math::SignBit( C::Zero ) == false;
    CHECK(result10);
    auto constexpr result11 = Math::SignBit( C::DenormalMin ) == false;
    CHECK(result11);
    auto constexpr result12 = Math::SignBit( C::Min ) == false;
    CHECK(result12);
    auto constexpr result13 = Math::SignBit( C::Max ) == false;
    CHECK(result13);
    auto constexpr result14 = Math::SignBit( C::Infinity ) == false;
    CHECK(result14);
}
TEST_CASE("ConstexprMathTests / FloatFRExpTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    auto Check = []( const std::pair<C::ValueType, int> result, C::ValueType first, int second ) -> bool
        {
            return IsSameValue( result.first, first ) && IsSameValue( result.second, second );
        };


    auto constexpr result1 = FRExp( C::NaN );
    CHECK(Check(result1, C::NaN, 0 ));
    auto constexpr result2 = FRExp( C::NegativeNaN );
    CHECK(Check( result2, C::NegativeNaN, 0 ));
    auto constexpr result3 = FRExp( C::sNaN );
    CHECK(Check( result3, C::sNaN, 0 ));
    auto constexpr result4 = FRExp( C::sNegativeNaN );
    CHECK(Check( result4, C::sNegativeNaN, 0 ));
    auto constexpr result5 = FRExp( C::NegativeInfinity );
    CHECK(Check( result5, C::NegativeInfinity, 0 ));
    auto constexpr result6 = FRExp( C::Lowest );
    CHECK(Check( result6, -0.99999994f, 128 ));
    auto constexpr result7 = FRExp( -C::Min );
    CHECK(Check( result7, -0.5f, -125 ));
    auto constexpr result8 = FRExp( -C::DenormalMin );
    CHECK(Check( result8, -0.5f, -148 ));
    auto constexpr result9 = FRExp( -C::Zero );
    CHECK(Check( result9, -0.f, 0 ));
    auto constexpr result10 = FRExp( C::Zero );
    CHECK(Check( result10, 0.f, 0 ));
    auto constexpr result11 = FRExp( C::DenormalMin );
    CHECK(Check( result11, 0.5f, -148 ));
    auto constexpr result12 = FRExp( C::Min );
    CHECK(Check( result12, 0.5f, -125 ));
    auto constexpr result13 = FRExp( C::Max );
    CHECK(Check( result13, 0.99999994f, 128 ));
    auto constexpr result14 = FRExp( C::Infinity );
    CHECK(Check( result14, C::Infinity, 0 ));
}
TEST_CASE("ConstexprMathTests / DoubleFRExpTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;

    auto Check = []( const std::pair<C::ValueType, int> result, C::ValueType first, int second ) -> bool
        {
            return IsSameValue( result.first, first ) && IsSameValue( result.second, second );
        };


    auto constexpr result1 = FRExp( C::NaN );
    CHECK(Check( result1, C::NaN, 0 ));
    auto constexpr result2 = FRExp( C::NegativeNaN );
    CHECK(Check( result2, C::NegativeNaN, 0 ));
    auto constexpr result3 = FRExp( C::sNaN );
    CHECK(Check( result3, C::sNaN, 0 ));
    auto constexpr result4 = FRExp( C::sNegativeNaN );
    CHECK(Check( result4, C::sNegativeNaN, 0 ));
    auto constexpr result5 = FRExp( C::NegativeInfinity );
    CHECK(Check( result5, C::NegativeInfinity, 0 ));
    auto constexpr result6 = FRExp( C::Lowest );
    CHECK(Check( result6, -0.99999999999999989, 1024 ));
    auto constexpr result7 = FRExp( -C::Min );
    CHECK(Check( result7, -0.5, -1021 ));
    auto constexpr result8 = FRExp( -C::DenormalMin );
    CHECK(Check( result8, -0.5, -1073 ));
    auto constexpr result9 = FRExp( -C::Zero );
    CHECK(Check( result9, -0., 0 ));
    auto constexpr result10 = FRExp( C::Zero );
    CHECK(Check( result10, 0., 0 ));
    auto constexpr result11 = FRExp( C::DenormalMin );
    CHECK(Check( result11, 0.5, -1073 ));
    auto constexpr result12 = FRExp( C::Min );
    CHECK(Check( result12, 0.5, -1021 ));
    auto constexpr result13 = FRExp( C::Max );
    CHECK(Check( result13, 0.99999999999999989, 1024 ));
    auto constexpr result14 = FRExp( C::Infinity );
    CHECK(Check( result14, C::Infinity, 0 ));
}
TEST_CASE("ConstexprMathTests / FloatModFTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    auto Check = []( const std::pair<C::ValueType, C::ValueType > result, C::ValueType first, C::ValueType second ) -> bool
        {
            return IsSameValue( result.first, first ) && IsSameValue( result.second, second );
        };

    auto CheckIsNaN = []( const std::pair<C::ValueType, C::ValueType > result ) -> bool
        {
            return IsNaN( result.first ) && IsNaN( result.second );
        };


    auto constexpr result1 = ModF( C::NaN );
    CHECK(CheckIsNaN( result1 ));
    auto constexpr result2 = ModF( C::NegativeNaN );
    CHECK(CheckIsNaN( result2 ));
    auto constexpr result3 = ModF( C::sNaN );
    CHECK(CheckIsNaN( result3 ));
    auto constexpr result4 = ModF( C::sNegativeNaN );
    CHECK(CheckIsNaN( result4 ));

    auto constexpr result5 = ModF( C::NegativeInfinity );
    CHECK(Check( result5, C::NegativeInfinity, -0.f ));
    auto constexpr result6 = ModF( C::Lowest );
    CHECK(Check( result6, -3.40282347e+38f, -0.f ));
    auto constexpr result7 = ModF( -C::Min );
    CHECK(Check( result7, -0.f, -1.17549435e-38f ));
    auto constexpr result8 = ModF( -C::DenormalMin );
    CHECK(Check( result8, -0.f, -1.401e-45f ));
    auto constexpr result9 = ModF( -C::Zero );
    CHECK(Check( result9, -0.f, -0.f ));
    auto constexpr result10 = ModF( C::Zero );
    CHECK(Check( result10, 0.f, 0.f ));
    auto constexpr result11 = ModF( C::DenormalMin );
    CHECK(Check( result11, 0.f, 1.401e-45f ));
    auto constexpr result12 = ModF( C::Min );
    CHECK(Check( result12, 0.f, 1.17549435e-38f ));
    auto constexpr result13 = ModF( C::Max );
    CHECK(Check( result13, 3.40282347e+38f, 0.f ));
    auto constexpr result14 = ModF( C::Infinity );
    CHECK(Check( result14, C::Infinity, 0.f ));
}
TEST_CASE("ConstexprMathTests / DoubleModFTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;

    auto Check = []( const std::pair<C::ValueType, C::ValueType > result, C::ValueType first, C::ValueType second ) -> bool
        {
            return IsSameValue( result.first, first ) && IsSameValue( result.second, second );
        };

    auto CheckIsNaN = []( const std::pair<C::ValueType, C::ValueType > result ) -> bool
        {
            return IsNaN( result.first ) && IsNaN( result.second );
        };


    auto constexpr result1 = ModF( C::NaN );
    CHECK(CheckIsNaN( result1 ));
    auto constexpr result2 = ModF( C::NegativeNaN );
    CHECK(CheckIsNaN( result2 ));
    auto constexpr result3 = ModF( C::sNaN );
    CHECK(CheckIsNaN( result3 ));
    auto constexpr result4 = ModF( C::sNegativeNaN );
    CHECK(CheckIsNaN( result4 ));

    auto constexpr result5 = ModF( C::NegativeInfinity );
    CHECK(Check( result5, C::NegativeInfinity, -0.f ));
    auto constexpr result6 = ModF( C::Lowest );
    CHECK(Check( result6, -1.7976931348623157e+308, -0. ));
    auto constexpr result7 = ModF( -C::Min );
    CHECK(Check( result7, -0., -2.2250738585072014e-308 ));
    auto constexpr result8 = ModF( -C::DenormalMin );
    CHECK(Check( result8, -0., -4.940656458412e-324 ));
    auto constexpr result9 = ModF( -C::Zero );
    CHECK(Check( result9, -0., -0. ));
    auto constexpr result10 = ModF( C::Zero );
    CHECK(Check( result10, 0., 0. ));
    auto constexpr result11 = ModF( C::DenormalMin );
    CHECK(Check( result11, 0.f, 4.940656458412e-324 ));
    auto constexpr result12 = ModF( C::Min );
    CHECK(Check( result12, 0.f, 2.2250738585072014e-308 ));
    auto constexpr result13 = ModF( C::Max );
    CHECK(Check( result13, 1.7976931348623157e+308, 0.f ));
    auto constexpr result14 = ModF( C::Infinity );
    CHECK(Check( result14, C::Infinity, 0. ));
}
TEST_CASE("ConstexprMathTests / FloatMinTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    constexpr auto minValue = Math::Min( 5.f, 4.f, 3.f, 4.f, 4.f );
    constexpr bool equal = minValue == 3.f;
    CHECK(equal);

    constexpr auto check1 = Min( C::Infinity, C::NegativeInfinity ) == C::NegativeInfinity;
    CHECK(check1);

    constexpr auto check2 = Min( C::NaN, C::NegativeInfinity ) == C::NegativeInfinity;
    CHECK(check2);

    constexpr auto check3 = Min( C::NegativeInfinity, C::NaN ) == C::NegativeInfinity;
    CHECK(check3);

    constexpr auto check4 = IsSameValue( Min( C::Zero, -C::Zero ), -C::Zero );
    CHECK(check4);

    constexpr auto check5 = IsSameValue( Min( -C::Zero, C::Zero ), -C::Zero );
    CHECK(check5);

}
TEST_CASE("ConstexprMathTests / DoubleMinTest1", "[math][ConstexprMathTests]")
{
    constexpr auto minValue = Math::Min( 5., 4., 3., 4., 4. );
    constexpr bool equal = minValue == 3.;
    CHECK(equal);
}
TEST_CASE("ConstexprMathTests / FloatMaxTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;
    constexpr auto minValue = Math::Max( 5.f, 4.f, 3.f, 4.f, 4.f );
    constexpr bool equal = minValue == 5.f;
    CHECK(equal);

    constexpr auto check1 = Max( C::Infinity, C::NegativeInfinity ) == C::Infinity;
    CHECK(check1);

    constexpr auto check2 = Max( C::NaN, C::NegativeInfinity ) == C::NegativeInfinity;
    CHECK(check2);

    constexpr auto check3 = Max( C::NegativeInfinity, C::NaN  ) == C::NegativeInfinity;
    CHECK(check3);

    constexpr auto check4 = IsSameValue(Max( C::Zero, -C::Zero ), C::Zero );
    CHECK(check4);

    constexpr auto check5 = IsSameValue( Max( -C::Zero, C::Zero ), C::Zero );
    CHECK(check5);


}
TEST_CASE("ConstexprMathTests / DoubleMaxTest1", "[math][ConstexprMathTests]")
{
    constexpr auto minValue = Math::Max( 5., 4., 3., 4., 4. );
    constexpr bool equal = minValue == 5.;
    CHECK(equal);
}
TEST_CASE("ConstexprMathTests / FloatFloorTest1", "[math][ConstexprMathTests]")
{
    constexpr float value1 = -1.5f;
    constexpr float value2 = -0.5f;
    constexpr float value3 = -0.0f;
    constexpr float value4 = 0.0f;
    constexpr float value5 = 0.5f;
    constexpr float value6 = 1.5f;

    constexpr double result1 = Floor( value1 );
    CHECK(result1 == -2.f);
    constexpr double result2 = Floor( value2 );
    CHECK(result2 == -1.f);
    constexpr double result3 = Floor( value3 );
    CHECK(result3 == -0.f);
    constexpr double result4 = Floor( value4 );
    CHECK(result4 == 0.f);
    constexpr double result5 = Floor( value5 );
    CHECK(result5 == 0.f);
    constexpr double result6 = Floor( value6 );
    CHECK(result6 == 1.f);
}
TEST_CASE("ConstexprMathTests / DoubleFloorTest1", "[math][ConstexprMathTests]")
{
    constexpr double value1 = -1.5;
    constexpr double value2 = -0.5;
    constexpr double value3 = -0.0;
    constexpr double value4 = 0.0;
    constexpr double value5 = 0.5;
    constexpr double value6 = 1.5;

    constexpr double result1 = Floor( value1 );
    CHECK(result1 == -2.);
    constexpr double result2 = Floor( value2 );
    CHECK(result2 == -1.);
    constexpr double result3 = Floor( value3 );
    CHECK(result3 == -0.);
    constexpr double result4 = Floor( value4 );
    CHECK(result4 == 0.);
    constexpr double result5 = Floor( value5 );
    CHECK(result5 == 0.);
    constexpr double result6 = Floor( value6 );
    CHECK(result6 == 1.);

}
TEST_CASE("ConstexprMathTests / OpenLibMFloorDoubleTest1", "[math][ConstexprMathTests]")
{
    constexpr double value1 = -1.5;
    constexpr double value2 = -0.5;
    constexpr double value3 = -0.0;
    constexpr double value4 = 0.0;
    constexpr double value5 = 0.5;
    constexpr double value6 = 1.5;

    constexpr double result1 = OpenLibM::floor( value1 );
    CHECK(result1 == -2.);
    constexpr double result2 = OpenLibM::floor( value2 );
    CHECK(result2 == -1.);
    constexpr double result3 = OpenLibM::floor( value3 );
    CHECK(result3 == -0.);
    constexpr double result4 = OpenLibM::floor( value4 );
    CHECK(result4 == 0.);
    constexpr double result5 = OpenLibM::floor( value5 );
    CHECK(result5 == 0.);
    constexpr double result6 = OpenLibM::floor( value6 );
    CHECK(result6 == 1.);
}
TEST_CASE("ConstexprMathTests / FloatCeilTest1", "[math][ConstexprMathTests]")
{
    constexpr float value1 = -1.5f;
    constexpr float value2 = -0.5f;
    constexpr float value3 = -0.0f;
    constexpr float value4 = 0.0f;
    constexpr float value5 = 0.5f;
    constexpr float value6 = 1.5f;

    constexpr double result1 = Ceil( value1 );
    CHECK(result1 == -1.f);
    constexpr double result2 = Ceil( value2 );
    CHECK(result2 == -0.f);
    constexpr double result3 = Ceil( value3 );
    CHECK(result3 == -0.f);
    constexpr double result4 = Ceil( value4 );
    CHECK(result4 == 0.f);
    constexpr double result5 = Ceil( value5 );
    CHECK(result5 == 1.f);
    constexpr double result6 = Ceil( value6 );
    CHECK(result6 == 2.f);
}
TEST_CASE("ConstexprMathTests / DoubleCeilTest1", "[math][ConstexprMathTests]")
{
    constexpr double value1 = -1.5;
    constexpr double value2 = -0.5;
    constexpr double value3 = -0.0;
    constexpr double value4 = 0.0;
    constexpr double value5 = 0.5;
    constexpr double value6 = 1.5;

    constexpr double result1 = Ceil( value1 );
    CHECK(result1 == -1.);
    constexpr double result2 = Ceil( value2 );
    CHECK(result2 == -0.);
    constexpr double result3 = Ceil( value3 );
    CHECK(result3 == -0.);
    constexpr double result4 = Ceil( value4 );
    CHECK(result4 == 0.);
    constexpr double result5 = Ceil( value5 );
    CHECK(result5 == 1.);
    constexpr double result6 = Ceil( value6 );
    CHECK(result6 == 2.);
}
TEST_CASE("ConstexprMathTests / OpenLibMCeilDoubleTest1", "[math][ConstexprMathTests]")
{
    constexpr double value1 = -1.5;
    constexpr double value2 = -0.5;
    constexpr double value3 = -0.0;
    constexpr double value4 = 0.0;
    constexpr double value5 = 0.5;
    constexpr double value6 = 1.5;

    constexpr double result1 = OpenLibM::ceil( value1 );
    CHECK(result1 == -1.);
    constexpr double result2 = OpenLibM::ceil( value2 );
    CHECK(result2 == -0.);
    constexpr double result3 = OpenLibM::ceil( value3 );
    CHECK(result3 == -0.);
    constexpr double result4 = OpenLibM::ceil( value4 );
    CHECK(result4 == 0.);
    constexpr double result5 = OpenLibM::ceil( value5 );
    CHECK(result5 == 1.);
    constexpr double result6 = OpenLibM::ceil( value6 );
    CHECK(result6 == 2.);

}
TEST_CASE("ConstexprMathTests / FloatTruncTest1", "[math][ConstexprMathTests]")
{
    constexpr float value1 = -1.5f;
    constexpr float value2 = -0.5f;
    constexpr float value3 = -0.0f;
    constexpr float value4 = 0.0f;
    constexpr float value5 = 0.5f;
    constexpr float value6 = 1.5f;

    constexpr double result1 = Trunc( value1 );
    CHECK(result1 == -1.f);
    constexpr double result2 = Trunc( value2 );
    CHECK(result2 == -0.f);
    constexpr double result3 = Trunc( value3 );
    CHECK(result3 == -0.f);
    constexpr double result4 = Trunc( value4 );
    CHECK(result4 == 0.f);
    constexpr double result5 = Trunc( value5 );
    CHECK(result5 == 0.f);
    constexpr double result6 = Trunc( value6 );
    CHECK(result6 == 1.f);
}
TEST_CASE("ConstexprMathTests / DoubleTruncTest1", "[math][ConstexprMathTests]")
{
    constexpr double value1 = -1.5;
    constexpr double value2 = -0.5;
    constexpr double value3 = -0.0;
    constexpr double value4 = 0.0;
    constexpr double value5 = 0.5;
    constexpr double value6 = 1.5;

    constexpr double result1 = Trunc( value1 );
    CHECK(result1 == -1.);
    constexpr double result2 = Trunc( value2 );
    CHECK(result2 == -0.);
    constexpr double result3 = Trunc( value3 );
    CHECK(result3 == -0.);
    constexpr double result4 = Trunc( value4 );
    CHECK(result4 == 0.);
    constexpr double result5 = Trunc( value5 );
    CHECK(result5 == 0.);
    constexpr double result6 = Trunc( value6 );
    CHECK(result6 == 1.);
}
TEST_CASE("ConstexprMathTests / FloatRoundTest1", "[math][ConstexprMathTests]")
{
    constexpr float value1 = -1.5f;
    constexpr float value2 = -0.5f;
    constexpr float value3 = -0.0f;
    constexpr float value4 = 0.0f;
    constexpr float value5 = 0.5f;
    constexpr float value6 = 1.5f;

    constexpr double result1 = Round( value1 );
    CHECK(result1 == -2.f);
    constexpr double result2 = Round( value2 );
    CHECK(result2 == -1.f);
    constexpr double result3 = Round( value3 );
    CHECK(result3 == -0.f);
    constexpr double result4 = Round( value4 );
    CHECK(result4 == 0.f);
    constexpr double result5 = Round( value5 );
    CHECK(result5 == 1.f);
    constexpr double result6 = Round( value6 );
    CHECK(result6 == 2.f);
}
TEST_CASE("ConstexprMathTests / DoubleRoundTest1", "[math][ConstexprMathTests]")
{
    constexpr double value1 = -1.5;
    constexpr double value2 = -0.5;
    constexpr double value3 = -0.0;
    constexpr double value4 = 0.0;
    constexpr double value5 = 0.5;
    constexpr double value6 = 1.5;

    constexpr double result1 = Round( value1 );
    CHECK(result1 == -2.);
    constexpr double result2 = Round( value2 );
    CHECK(result2 == -1.);
    constexpr double result3 = Round( value3 );
    CHECK(result3 == -0.);
    constexpr double result4 = Round( value4 );
    CHECK(result4 == 0.);
    constexpr double result5 = Round( value5 );
    CHECK(result5 == 1.);
    constexpr double result6 = Round( value6 );
    CHECK(result6 == 2.);
}
TEST_CASE("ConstexprMathTests / FloatClampTest1", "[math][ConstexprMathTests]")
{
    constexpr float result1 = Clamp( -1.f, 0.f, 10.f );
    CHECK(result1 == 0.f);
    constexpr float result2 = Clamp( 11.f, 0.f, 10.f );
    CHECK(result2 == 10.f);
    constexpr float result3 = Clamp( 5.f, 0.f, 10.f );
    CHECK(result3 == 5.f);
}
TEST_CASE("ConstexprMathTests / DoublelampTest1", "[math][ConstexprMathTests]")
{
    constexpr double result1 = Clamp( -1., 0., 10. );
    CHECK(result1 == 0.);
    constexpr double result2 = Clamp( 11., 0., 10. );
    CHECK(result2 == 10.);
    constexpr double result3 = Clamp( 5., 0., 10. );
    CHECK(result3 == 5.);
}
TEST_CASE("ConstexprMathTests / FloatLerpTest1", "[math][ConstexprMathTests]")
{
    constexpr auto result1 = Lerp( 3.f, 5.f, 0.5f );
    CHECK(result1 == 4.f);
    constexpr auto result2 = Lerp( 3.f, 5.f, -0.5f );
    CHECK(result2 == 2.f);
    constexpr auto result3 = Lerp( 3.f, 5.f, 1.5f );
    CHECK(result3 == 6.f);
    constexpr auto result4 = Lerp( 3.f, 5.f, 0.f );
    CHECK(result4 == 3.f);
    constexpr auto result5 = Lerp( 3.f, 5.f, 1.f );
    CHECK(result5 == 5.f);
}
TEST_CASE("ConstexprMathTests / DoubleLerpTest1", "[math][ConstexprMathTests]")
{
    constexpr auto result1 = Lerp( 3., 5., 0.5 );
    CHECK(result1 == 4.f);
    constexpr auto result2 = Lerp( 3., 5., -0.5 );
    CHECK(result2 == 2.f);
    constexpr auto result3 = Lerp( 3., 5., 1.5 );
    CHECK(result3 == 6.f);
    constexpr auto result4 = Lerp( 3., 5., 0. );
    CHECK(result4 == 3.f);
    constexpr auto result5 = Lerp( 3., 5., 1. );
    CHECK(result5 == 5.f);
}
TEST_CASE("ConstexprMathTests / FloatCopySignTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    constexpr auto result1 = CopySign( C::One, C::sNegativeNaN );
    CHECK(result1 == -C::One);

    constexpr auto result2 = CopySign( C::One, C::NegativeNaN );
    CHECK(result2 == -C::One);

    constexpr auto result3 = CopySign( C::One, C::NegativeInfinity );
    CHECK(result3 == -C::One);

    constexpr auto result4 = CopySign( C::sNegativeNaN, C::One );
    CHECK(IsNaN( result4 ));

    constexpr auto result5 = CopySign( C::NegativeNaN, C::One );
    CHECK(IsNaN( result5 ));

    constexpr auto result6 = CopySign( C::NegativeInfinity, C::One );
    CHECK(result6 == C::Infinity);

    constexpr auto result7 = CopySign( C::Infinity, -C::One );
    CHECK(result7 == C::NegativeInfinity);

    constexpr auto result8 = CopySign( C::Max, -C::One );
    CHECK(result8 == C::Lowest);

    constexpr auto result9 = CopySign( C::Lowest, C::One );
    CHECK(result9 == C::Max);

    constexpr auto result10 = CopySign( C::DenormalMin, -C::One );
    CHECK(result10 == -C::DenormalMin);

    constexpr auto result11 = CopySign( -C::DenormalMin, C::One );
    CHECK(result11 == C::DenormalMin);

    
}
TEST_CASE("ConstexprMathTests / DoubleCopySignTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;

    constexpr auto result1 = CopySign( C::One, C::sNegativeNaN );
    CHECK(result1 == -C::One);

    constexpr auto result2 = CopySign( C::One, C::NegativeNaN );
    CHECK(result2 == -C::One);

    constexpr auto result3 = CopySign( C::One, C::NegativeInfinity );
    CHECK(result3 == -C::One);

    constexpr auto result4 = CopySign( C::sNegativeNaN, C::One );
    CHECK(IsNaN( result4 ));

    constexpr auto result5 = CopySign( C::NegativeNaN, C::One );
    CHECK(IsNaN( result5 ));

    constexpr auto result6 = CopySign( C::NegativeInfinity, C::One );
    CHECK(result6 == C::Infinity);

    constexpr auto result7 = CopySign( C::Infinity, -C::One );
    CHECK(result7 == C::NegativeInfinity);

    constexpr auto result8 = CopySign( C::Max, -C::One );
    CHECK(result8 == C::Lowest);

    constexpr auto result9 = CopySign( C::Lowest, C::One );
    CHECK(result9 == C::Max);

    constexpr auto result10 = CopySign( C::DenormalMin, -C::One );
    CHECK(result10 == -C::DenormalMin);

    constexpr auto result11 = CopySign( -C::DenormalMin, C::One );
    CHECK(result11 == C::DenormalMin);
}
TEST_CASE("ConstexprMathTests / FloatScaleByNTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;
    
    constexpr auto result1 = ScaleBN( C::NaN, C::Two );
    CHECK(IsNaN( result1 ));

    constexpr auto result2 = ScaleBN( C::Infinity, C::Two );
    CHECK(IsInf( result2 ));

    constexpr auto result3 = ScaleBN( C::Max, C::Two );
    CHECK(IsInf( result3 ));

    constexpr auto result4 = ScaleBN( -C::Max, C::Two );
    CHECK(IsInf( result4 ));

    auto result5 = std::scalbn( -C::Max, C::Two );
    CHECK(IsInf( result5 ));
    CHECK(result4 == result5);

    constexpr auto result6 = ScaleBN( -C::Max, C::Three );
    CHECK(IsInf( result6 ));

    auto result7 = std::scalbn( -C::Max, C::Three );
    CHECK(IsInf( result7 ));
    CHECK(result6 == result7);

    constexpr auto result8 = ScaleBN( C::Two, C::Two );
    CHECK(result8 == 8.f);

    constexpr auto result9 = ScaleBN( -C::Two, C::Two );
    CHECK(result9 == -8.f);
}
TEST_CASE("ConstexprMathTests / DoubleScaleByNTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;

    constexpr auto result1 = ScaleBN( C::NaN, C::Two );
    CHECK(IsNaN( result1 ));

    constexpr auto result2 = ScaleBN( C::Infinity, C::Two );
    CHECK(IsInf( result2 ));

    constexpr auto result3 = ScaleBN( C::Max, C::Two );
    CHECK(IsInf( result3 ));

    constexpr auto result4 = ScaleBN( -C::Max, C::Two );
    CHECK(IsInf( result4 ));

    auto result5 = std::scalbn( -C::Max, C::Two );
    CHECK(IsInf( result5 ));
    CHECK(result4 == result5);

    constexpr auto result6 = ScaleBN( -C::Max, C::Three );
    CHECK(IsInf( result6 ));

    auto result7 = std::scalbn( -C::Max, C::Three );
    CHECK(IsInf( result7 ));
    CHECK(result6 == result7);

    constexpr auto result8 = ScaleBN( C::Two, C::Two );
    CHECK(result8 == 8.);

    constexpr auto result9 = ScaleBN( -C::Two, C::Two );
    CHECK(result9 == -8.);
}
TEST_CASE("ConstexprMathTests / FloatFModTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;
    
    constexpr auto result1 = FMod( C::NaN, C::Two );
    CHECK(IsNaN( result1 ));

    constexpr auto result2 = FMod( C::sNaN, C::Two );
    CHECK(IsNaN( result2 ));

    constexpr auto result3 = FMod( C::NegativeNaN, C::Two );
    CHECK(IsNaN( result3 ));

    constexpr auto result4 = FMod( C::sNegativeNaN, C::Two );
    CHECK(IsNaN( result4 ));

    constexpr auto result5 = FMod( C::Two, C::NaN );
    CHECK(IsNaN( result5 ));

    constexpr auto result6 = FMod( C::Two, C::Infinity );
    CHECK(result6 == C::Two);

    constexpr auto result7 = FMod( C::Two, C::Max );
    CHECK(result7 == C::Two);

    constexpr auto result8 = FMod( C::Two, C::Three );
    CHECK(result8 == C::Two);

    constexpr auto result9 = FMod( C::Three, C::Two );
    CHECK(result9 == C::One);

    constexpr auto result10 = FMod( C::Three + .5f, C::Two );
    CHECK(result10 == 1.5f);

    constexpr auto result11 = FMod( (C::Pi * 3)+C::PiOver4, C::Pi );
    constexpr auto equal11 = AreNearlyEqual( result11, C::PiOver4 );
    CHECK(equal11);
}
TEST_CASE("ConstexprMathTests / DoubleFModTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;

    constexpr auto result1 = FMod( C::NaN, C::Two );
    CHECK(IsNaN( result1 ));

    constexpr auto result2 = FMod( C::sNaN, C::Two );
    CHECK(IsNaN( result2 ));

    constexpr auto result3 = FMod( C::NegativeNaN, C::Two );
    CHECK(IsNaN( result3 ));

    constexpr auto result4 = FMod( C::sNegativeNaN, C::Two );
    CHECK(IsNaN( result4 ));

    constexpr auto result5 = FMod( C::Two, C::NaN );
    CHECK(IsNaN( result5 ));

    constexpr auto result6 = FMod( C::Two, C::Infinity );
    CHECK(result6 == C::Two);

    constexpr auto result7 = FMod( C::Two, C::Max );
    CHECK(result7 == C::Two);

    constexpr auto result8 = FMod( C::Two, C::Three );
    CHECK(result8 == C::Two);

    constexpr auto result9 = FMod( C::Three, C::Two );
    CHECK(result9 == C::One);

    constexpr auto result10 = FMod( C::Three + .5, C::Two );
    CHECK(result10 == 1.5);

    constexpr auto result11 = FMod( ( C::Pi * 3 ) + C::PiOver4, C::Pi );
    constexpr auto equal11 = AreNearlyEqual( result11, C::PiOver4 );
    CHECK(equal11);
}
TEST_CASE("ConstexprMathTests / FloatExpTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    constexpr auto result1 = Exp( C::Infinity );
    CHECK(IsInf( result1 ));

    constexpr auto result2 = Exp( C::NegativeInfinity );
    CHECK(result2 == 0);

    constexpr auto result3 = Exp( C::Zero );
    CHECK(result3 == 1);

    constexpr auto result4 = Exp( -C::Zero );
    CHECK(result4 == 1);

    constexpr auto result5 = Exp( C::NaN );
    CHECK(IsNaN( result5 ));

    constexpr auto result6 = Exp( C::One );
    CHECK(result6 == C::E);

    constexpr auto result7 = Exp( C::Two );
    constexpr auto equal7 = AreNearlyEqual( result7, C::E2 );
    CHECK(equal7);

    constexpr auto result8 = Exp( C::Three );
    constexpr auto equal8 = AreNearlyEqual( result8, C::E3 );
    CHECK(equal8);

    constexpr auto result9 = Exp( .7f );
    CHECK(result9 == 2.01375270f);

    constexpr auto result10 = Exp( 50.f );
    CHECK(result10 == 5.18470546e+21f);
}
TEST_CASE("ConstexprMathTests / DoubleExpTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;

    constexpr auto result1 = Exp( C::Infinity );
    CHECK(IsInf( result1 ));

    constexpr auto result2 = Exp( C::NegativeInfinity );
    CHECK(result2 == 0);

    constexpr auto result3 = Exp( C::Zero );
    CHECK(result3 == 1);

    constexpr auto result4 = Exp( -C::Zero );
    CHECK(result4 == 1);

    constexpr auto result5 = Exp( C::NaN );
    CHECK(IsNaN( result5 ));

    constexpr auto result6 = Exp( C::One );
    CHECK(result6 == C::E);

    constexpr auto result7 = Exp( C::Two );
    constexpr auto equal7 = AreNearlyEqual( result7, C::E2 );
    CHECK(equal7);

    constexpr auto result8 = Exp( C::Three );
    constexpr auto equal8 = AreNearlyEqual( result8, C::E3 );
    CHECK(equal8);

    constexpr auto result9 = Exp( .7 );
    constexpr auto equal9 = AreNearlyEqual( result9, 2.0137527074704765216 );
    CHECK(equal9);

    constexpr auto result10 = Exp( 50. );
    constexpr auto equal10 = AreNearlyEqual( result10, 5184705528587072464087.45332293348538 );
    CHECK(equal10);
}
TEST_CASE("ConstexprMathTests / FloatExp2Test1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    constexpr auto result1 = Exp2( C::Infinity );
    CHECK(IsInf( result1 ));

    constexpr auto result2 = Exp2( C::NegativeInfinity );
    CHECK(result2 == 0);

    constexpr auto result3 = Exp2( C::Zero );
    CHECK(result3 == 1);

    constexpr auto result4 = Exp2( -C::Zero );
    CHECK(result4 == 1);

    constexpr auto result5 = Exp2( C::NaN );
    CHECK(IsNaN( result5 ));

    constexpr auto result6 = Exp2( C::One );
    CHECK(result6 == 2.f);

    constexpr auto result7 = Exp2( C::Two );
    CHECK(result7 == 4.f);

    constexpr auto result8 = Exp2( C::Three );
    CHECK(result8 == 8.f);

    constexpr auto result9 = Exp2( .7f );
    CHECK(result9 == 1.62450480f);
}
TEST_CASE("ConstexprMathTests / DoubleExp2Test1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;

    constexpr auto result1 = Exp2( C::Infinity );
    CHECK(IsInf( result1 ));

    constexpr auto result2 = Exp2( C::NegativeInfinity );
    CHECK(result2 == 0);

    constexpr auto result3 = Exp2( C::Zero );
    CHECK(result3 == 1);

    constexpr auto result4 = Exp2( -C::Zero );
    CHECK(result4 == 1);

    constexpr auto result5 = Exp2( C::NaN );
    CHECK(IsNaN( result5 ));

    constexpr auto result6 = Exp2( C::One );
    
    constexpr auto equal6 = AreNearlyEqual( result6, 2. );
    CHECK(equal6);

    constexpr auto result7 = Exp2( C::Two );
    constexpr auto equal7 = AreNearlyEqual( result7, 4. );
    CHECK(equal7);

    constexpr auto result8 = Exp2( C::Three );
    constexpr auto equal8 = AreNearlyEqual( result8, 8. );
    CHECK(equal8);

    constexpr auto result9 = Exp2( .7 );
    constexpr auto equal9 = AreNearlyEqual( result9, 1.6245047927124710452 );
    CHECK(equal9);
}
TEST_CASE("ConstexprMathTests / FloatExp10Test1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    constexpr auto result1 = Exp10( C::Infinity );
    CHECK(IsInf( result1 ));

    constexpr auto result2 = Exp10( C::NegativeInfinity );
    CHECK(result2 == 0);

    constexpr auto result3 = Exp10( C::Zero );
    CHECK(result3 == 1);

    constexpr auto result4 = Exp10( -C::Zero );
    CHECK(result4 == 1);

    constexpr auto result5 = Exp10( C::NaN );
    CHECK(IsNaN( result5 ));

    constexpr auto result6 = Exp10( C::One );
    constexpr auto equal6 = AreNearlyEqual( result6, 10.f );
    CHECK(equal6);

    constexpr auto result7 = Exp10( C::Two );
    constexpr auto equal7 = AreNearlyEqual( result7, 100.f );
    CHECK(equal7);

    constexpr auto result8 = Exp10( C::Three );
    constexpr auto equal8 = AreNearlyEqual( result8, 1000.f, 1.e-3f );
    CHECK(equal8);

    
    
    constexpr auto result9 = Exp10( .7f );
    constexpr auto equal9 = AreNearlyEqual( result9, 5.0118723362727228500155418688494574f );
    CHECK(equal9);
}
TEST_CASE("ConstexprMathTests / DoubleExp10Test1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;

    constexpr auto result1 = Exp10( C::Infinity );
    CHECK(IsInf( result1 ));

    constexpr auto result2 = Exp10( C::NegativeInfinity );
    CHECK(result2 == 0);

    constexpr auto result3 = Exp10( C::Zero );
    CHECK(result3 == 1);

    constexpr auto result4 = Exp10( -C::Zero );
    CHECK(result4 == 1);

    constexpr auto result5 = Exp10( C::NaN );
    CHECK(IsNaN( result5 ));

    constexpr auto result6 = Exp10( C::One );
    constexpr auto equal6 = AreNearlyEqual( result6, 10. );
    CHECK(equal6);

    constexpr auto result7 = Exp10( C::Two );
    constexpr auto equal7 = AreNearlyEqual( result7, 100. );
    CHECK(equal7);

    constexpr auto result8 = Exp10( C::Three );
    constexpr auto equal8 = AreNearlyEqual( result8, 1000. );
    CHECK(equal8);

    constexpr auto result9 = Exp10( 0.7 );
    constexpr auto equal9 = AreNearlyEqual( result9, 5.0118723362727228500155418688494574 );
    CHECK(equal9);
}
TEST_CASE("ConstexprMathTests / FloatExpM1Test1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    constexpr auto result1 = ExpM1( C::Infinity );
    CHECK(IsInf( result1 ));

    constexpr auto result2 = ExpM1( C::NegativeInfinity );
    CHECK(result2 == -1);

    constexpr auto result3 = ExpM1( C::Zero );
    CHECK(result3 == 0);

    constexpr auto result4 = ExpM1( -C::Zero );
    CHECK(result4 == 0);

    constexpr auto result5 = ExpM1( C::NaN );
    CHECK(IsNaN( result5 ));

    constexpr auto result6 = ExpM1( C::One );
    CHECK(result6 == (C::E - 1));

    constexpr auto result7 = ExpM1( C::Two );
    constexpr auto equal7 = AreNearlyEqual( result7, ( C::E2 - 1 ) );
    CHECK(equal7);

    constexpr auto result8 = ExpM1( C::Three );
    constexpr auto equal8 = AreNearlyEqual( result8, ( C::E3 - 1 ) );
    CHECK(equal8);

    constexpr auto result9 = ExpM1( .7f );
    CHECK(result9 == 1.01375270f);

    constexpr auto result10 = ExpM1( 50.f );
    CHECK(result10 == 5.18470546e+21f);
}
TEST_CASE("ConstexprMathTests / DoubleExpM1Test1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;

    constexpr auto result1 = ExpM1( C::Infinity );
    CHECK(IsInf( result1 ));

    constexpr auto result2 = ExpM1( C::NegativeInfinity );
    CHECK(result2 == -1);

    constexpr auto result3 = ExpM1( C::Zero );
    CHECK(result3 == 0);

    constexpr auto result4 = ExpM1( -C::Zero );
    CHECK(result4 == 0);

    constexpr auto result5 = ExpM1( C::NaN );
    CHECK(IsNaN( result5 ));

    constexpr auto result6 = ExpM1( C::One );
    CHECK(result6 == ( C::E - 1 ));

    constexpr auto result7 = ExpM1( C::Two );
    constexpr auto equal7 = AreNearlyEqual( result7, ( C::E2 - 1 ) );
    CHECK(equal7);

    constexpr auto result8 = ExpM1( C::Three );
    constexpr auto equal8 = AreNearlyEqual( result8, ( C::E3 - 1 ) );
    CHECK(equal8);

    constexpr auto result9 = ExpM1( .7 );
    constexpr auto equal9 = AreNearlyEqual( result9, 1.0137527074704765216 );
    CHECK(equal9);

    constexpr auto result10 = ExpM1( 50. );
    constexpr auto equal10 = AreNearlyEqual( result10, 5184705528587072464086.45332293348538 );
    CHECK(equal10);
}
TEST_CASE("ConstexprMathTests / FloatHypotTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    constexpr auto result = Hypot( C::Two, C::Two );
    constexpr auto expected = Sqrt( C::Two * C::Two + C::Two * C::Two );
    constexpr auto equal = result == expected;
    CHECK(result);
}
TEST_CASE("ConstexprMathTests / DoubleHypotTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;

    constexpr auto result = Hypot( C::Two, C::Two );
    constexpr auto expected = Sqrt( C::Two * C::Two + C::Two * C::Two );
    constexpr auto equal = result == expected;
    CHECK(result);
}
TEST_CASE("ConstexprMathTests / FloatHypot3Test1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    constexpr auto result = Hypot( C::Two, C::Two, C::Two );
    constexpr auto expected = Sqrt( C::Two * C::Two + C::Two * C::Two + C::Two * C::Two );
    constexpr auto equal = result == expected;
    CHECK(result);
}
TEST_CASE("ConstexprMathTests / DoubleHypot3Test1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;

    constexpr auto result = Hypot( C::Two, C::Two, C::Two );
    constexpr auto expected = Sqrt( C::Two * C::Two + C::Two * C::Two + C::Two * C::Two );
    constexpr auto equal = result == expected;
    CHECK(result);
}
TEST_CASE("ConstexprMathTests / FloatLogTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    constexpr auto result1 = Log( C::Infinity );
    CHECK(IsInf( result1 ));

    constexpr auto result2 = Log( C::NegativeInfinity );
    CHECK(IsNaN( result2 ));

    constexpr auto result3 = Log( C::Zero );
    CHECK(IsInf( result3 ));

    constexpr auto result4 = Log( -C::Zero );
    CHECK(IsInf( result4 ));

    constexpr auto result5 = Log( C::NaN );
    CHECK(IsNaN( result5 ));

    constexpr auto result6 = Log( C::One );
    CHECK(result6 == C::Zero);

    constexpr auto result7 = Log( -C::One );
    CHECK(IsNaN( result7 ));

    constexpr auto result8 = Log( C::E );
    CHECK(result8 == C::One);

    constexpr auto result9 = Log( C::E2 );
    CHECK(result9 == C::Two);

    constexpr auto result10 = Log( C::E3 );
    CHECK(result10 == C::Three);

    constexpr auto result11 = Log( .7f );
    CHECK(result11 == -0.356674969f);
}
TEST_CASE("ConstexprMathTests / DoubleLogTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;

    constexpr auto result1 = Log( C::Infinity );
    CHECK(IsInf( result1 ));

    constexpr auto result2 = Log( C::NegativeInfinity );
    CHECK(IsNaN( result2 ));

    constexpr auto result3 = Log( C::Zero );
    CHECK(IsInf( result3 ));

    constexpr auto result4 = Log( -C::Zero );
    CHECK(IsInf( result4 ));

    constexpr auto result5 = Log( C::NaN );
    CHECK(IsNaN( result5 ));

    constexpr auto result6 = Log( C::One );
    CHECK(result6 == C::Zero);

    constexpr auto result7 = Log( -C::One );
    CHECK(IsNaN( result7 ));

    constexpr auto result8 = Log( C::E );
    CHECK(result8 == C::One);

    constexpr auto result9 = Log( C::E2 );
    CHECK(result9 == C::Two);

    constexpr auto result10 = Log( C::E3 );
    CHECK(result10 == C::Three);


    constexpr auto result11 = Log( .7 );
    constexpr auto equal11 = AreNearlyEqual( result11, -0.35667494393873237891263871124118447 );
    CHECK(equal11);
}
TEST_CASE("ConstexprMathTests / FloatLog2Test1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    constexpr auto result1 = Log2( C::Infinity );
    CHECK(IsInf( result1 ));

    constexpr auto result2 = Log2( C::NegativeInfinity );
    CHECK(IsNaN( result2 ));

    constexpr auto result3 = Log2( C::Zero );
    CHECK(IsInf( result3 ));

    constexpr auto result4 = Log2( -C::Zero );
    CHECK(IsInf( result4 ));

    constexpr auto result5 = Log2( C::NaN );
    CHECK(IsNaN( result5 ));

    constexpr auto result6 = Log2( C::One );
    CHECK(result6 == C::Zero);

    constexpr auto result7 = Log2( -C::One );
    CHECK(IsNaN( result7 ));

    constexpr auto result8 = Log2( C::Two );
    CHECK(result8 == C::One);

    constexpr auto result9 = Log2( C::Two* C::Two );
    CHECK(result9 == C::Two);

    constexpr auto result10 = Log2( C::Two * C::Two * C::Two );
    CHECK(result10 == C::Three);

    constexpr auto result11 = Log2( .7f );
    CHECK(result11 == -0.514573216f);
}
TEST_CASE("ConstexprMathTests / DoubleLog2Test1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;

    constexpr auto result1 = Log2( C::Infinity );
    CHECK(IsInf( result1 ));

    constexpr auto result2 = Log2( C::NegativeInfinity );
    CHECK(IsNaN( result2 ));

    constexpr auto result3 = Log2( C::Zero );
    CHECK(IsInf( result3 ));

    constexpr auto result4 = Log2( -C::Zero );
    CHECK(IsInf( result4 ));

    constexpr auto result5 = Log2( C::NaN );
    CHECK(IsNaN( result5 ));

    constexpr auto result6 = Log2( C::One );
    CHECK(result6 == C::Zero);

    constexpr auto result7 = Log2( -C::One );
    CHECK(IsNaN( result7 ));

    constexpr auto result8 = Log2( C::Two );
    CHECK(result8 == C::One);

    constexpr auto result9 = Log2( C::Two * C::Two );
    CHECK(result9 == C::Two);

    constexpr auto result10 = Log2( C::Two * C::Two * C::Two );
    CHECK(result10 == C::Three);


    constexpr auto result11 = Log2( .7 );
    constexpr auto equal11 = AreNearlyEqual( result11, -0.51457317282975824043 );
    CHECK(equal11);
}
TEST_CASE("ConstexprMathTests / FloatLog10Test1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    constexpr auto result1 = Log10( C::Infinity );
    CHECK(IsInf( result1 ));

    constexpr auto result2 = Log10( C::NegativeInfinity );
    CHECK(IsNaN( result2 ));

    constexpr auto result3 = Log10( C::Zero );
    CHECK(IsInf( result3 ));

    constexpr auto result4 = Log10( -C::Zero );
    CHECK(IsInf( result4 ));

    constexpr auto result5 = Log10( C::NaN );
    CHECK(IsNaN( result5 ));

    constexpr auto result6 = Log10( C::One );
    CHECK(result6 == C::Zero);

    constexpr auto result7 = Log10( -C::One );
    CHECK(IsNaN( result7 ));

    constexpr auto result8 = Log10( 10.f );
    CHECK(result8 == C::One);

    constexpr auto result9 = Log10( 100.f );
    CHECK(result9 == C::Two);

    constexpr auto result10 = Log10( 1000.f );
    CHECK(result10 == C::Three);

    constexpr auto result11 = Log10( .7f );
    CHECK(result11 == -0.154901966f);
}
TEST_CASE("ConstexprMathTests / DoubleLog10Test1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;

    constexpr auto result1 = Log10( C::Infinity );
    CHECK(IsInf( result1 ));

    constexpr auto result2 = Log10( C::NegativeInfinity );
    CHECK(IsNaN( result2 ));

    constexpr auto result3 = Log10( C::Zero );
    CHECK(IsInf( result3 ));

    constexpr auto result4 = Log10( -C::Zero );
    CHECK(IsInf( result4 ));

    constexpr auto result5 = Log10( C::NaN );
    CHECK(IsNaN( result5 ));

    constexpr auto result6 = Log10( C::One );
    CHECK(result6 == C::Zero);

    constexpr auto result7 = Log10( -C::One );
    CHECK(IsNaN( result7 ));

    constexpr auto result8 = Log10( 10. );
    CHECK(result8 == C::One);

    constexpr auto result9 = Log10( 100. );
    CHECK(result9 == C::Two);

    constexpr auto result10 = Log10( 1000. );
    CHECK(result10 == C::Three);


    constexpr auto result11 = Log10( .7 );
    constexpr auto equal11 = AreNearlyEqual( result11, -0.15490195998574316929 );
    CHECK(equal11);
}
TEST_CASE("ConstexprMathTests / FloatLog1PTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    constexpr auto result1 = Log1P( C::Infinity );
    CHECK(IsInf( result1 ));

    constexpr auto result2 = Log1P( C::NegativeInfinity );
    CHECK(IsNaN( result2 ));

    constexpr auto result3 = Log1P( C::Zero );
    CHECK(result3 == C::Zero);

    constexpr auto result4 = Log1P( -C::Zero );
    CHECK(result4 == C::Zero);

    constexpr auto result5 = Log1P( C::NaN );
    CHECK(IsNaN( result5 ));

    constexpr auto result6 = Log1P( C::One );
    CHECK(result6 == 0.693147182f);

    constexpr auto result7 = Log1P( -C::One );
    CHECK(IsInf( result7 ));

    constexpr auto result8 = Log1P( C::E - 1 );
    CHECK(result8 == C::One);

    constexpr auto result9 = Log1P( C::E2 - 1 );
    CHECK(result9 == C::Two);

    constexpr auto result10 = Log1P( C::E3 - 1 );
    CHECK(result10 == C::Three);


    constexpr auto result11 = Log1P( -0.3f );
    CHECK(result11 == -0.356674969f);
}
TEST_CASE("ConstexprMathTests / DoubleLog1PTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;

    constexpr auto result1 = Log1P( C::Infinity );
    CHECK(IsInf( result1 ));

    constexpr auto result2 = Log1P( C::NegativeInfinity );
    CHECK(IsNaN( result2 ));

    constexpr auto result3 = Log1P( C::Zero );
    CHECK(result3 == C::Zero);

    constexpr auto result4 = Log1P( -C::Zero );
    CHECK(result4 == C::Zero);

    constexpr auto result5 = Log1P( C::NaN );
    CHECK(IsNaN( result5 ));

    constexpr auto result6 = Log1P( C::One );
    CHECK(result6 == 0.69314718055994529);

    constexpr auto result7 = Log1P( -C::One );
    CHECK(IsInf( result7 ));

    constexpr auto result8 = Log1P( C::E - 1 );
    CHECK(result8 == C::One);

    constexpr auto result9 = Log1P( C::E2 - 1 );
    CHECK(result9 == C::Two);

    constexpr auto result10 = Log1P( C::E3 - 1 );
    CHECK(result10 == C::Three);


    constexpr auto result11 = Log1P( -0.3 );
    constexpr auto equal11 = AreNearlyEqual( result11, -0.35667494393873237891263871124118447 );
    CHECK(equal11);
}
TEST_CASE("ConstexprMathTests / FloatPowTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;
    constexpr auto Check = []( C::ValueType x, C::ValueType y, C::ValueType expected ) -> bool
        {
            auto r = Pow( x, y );
            return IsSameValue( r, expected );
        };
    constexpr auto CheckIsNaN = []( C::ValueType x, C::ValueType y ) -> bool
        {
            auto r = Pow( x, y );
            return IsNaN( r );
        };

    constexpr auto CheckIsInf = []( C::ValueType x, C::ValueType y ) -> bool
        {
            auto r = Pow( x, y );
            return IsInf( r );
        };

    constexpr auto CheckIsPosInf = []( C::ValueType x, C::ValueType y ) -> bool
        {
            auto r = Pow( x, y );
            return IsSameValue( r, C::Infinity );
        };

    constexpr auto CheckIsNegInf = []( C::ValueType x, C::ValueType y ) -> bool
        {
            auto r = Pow( x, y );
            return IsSameValue( r, C::NegativeInfinity );
        };


    constexpr auto check1 = Check( 0., 0., 1 ) && Check( -0., 0., 1 ) && Check( 0., -0., 1 ) && Check( -0., -0., 1 );
    CHECK(check1);
    constexpr auto check2 = Check( 10., 0., 1 ) && Check( -10., 0., 1 ) && Check( 10., -0., 1 ) && Check( -10., -0., 1 );
    CHECK(check2);
    constexpr auto check3 = Check( C::NaN, 0., 1 ) && Check( C::NaN, -0., 1 );
    CHECK(check3);

    constexpr auto check4 = CheckIsInf( 1.1f, C::Infinity ) && 
        CheckIsInf( C::Infinity, C::Infinity ) && 
        CheckIsInf( -1.1f, C::Infinity ) &&
        CheckIsInf( -C::Infinity, C::Infinity );
    CHECK(check4);

    constexpr auto check5 = Check( 0.9f, C::Infinity, 0.f ) && 
        Check( 1e-7, C::Infinity, 0 ) && 
        Check( -0.9, C::Infinity, 0 ) && 
        Check( -1e-7, C::Infinity, 0 );
    CHECK(check5);

    constexpr auto check6 = Check( 1.1, -C::Infinity, 0 ) && Check( C::Infinity, -C::Infinity, 0 ) && Check( -1.1, -C::Infinity, 0 ) && Check( -C::Infinity, -C::Infinity, 0 );
    CHECK(check6);

    constexpr auto check7 = CheckIsInf( 0.9, -C::Infinity ) && CheckIsInf( 1e-7, -C::Infinity ) && CheckIsInf( -0.9, -C::Infinity ) && CheckIsInf( -1e-7, -C::Infinity );
    CHECK(check7);

    constexpr auto check8 = CheckIsInf( C::Infinity, 1e-7 ) && CheckIsInf( C::Infinity, 1 ) && CheckIsInf( C::Infinity, 1e7 );
    CHECK(check8);

    constexpr auto check9 = Check( C::Infinity, -1e-7, 0 ) && Check( C::Infinity, -1, 0 ) && Check( C::Infinity, -1e7, 0 );
    CHECK(check9);

    constexpr auto check10 = CheckIsNegInf( -C::Infinity, 1 ) && CheckIsNegInf( -C::Infinity, 11 ) && CheckIsNegInf( -C::Infinity, 1001 );
    CHECK(check10);

    constexpr auto check11 = CheckIsPosInf( -C::Infinity, 2 ) &&
        CheckIsPosInf( -C::Infinity, 12 ) &&
        CheckIsPosInf( -C::Infinity, 1002 ) &&
        CheckIsPosInf( -C::Infinity, 0.1 ) &&
        CheckIsPosInf( -C::Infinity, 1.1 ) &&
        CheckIsPosInf( -C::Infinity, 11.1 ) &&
        CheckIsPosInf( -C::Infinity, 1001.1 );
    CHECK(check11);

    constexpr auto check12 = Check( -C::Infinity, -1, -0.f ) && Check( -C::Infinity, -11, -0.f ) && Check( -C::Infinity, -1001, -0.f );
    CHECK(check12);

    constexpr auto check13 = Check( -C::Infinity, -2, 0. ) &&
        Check( -C::Infinity, -12, 0. ) &&
        Check( -C::Infinity, -1002, 0. ) &&
        Check( -C::Infinity, -0.1, 0. ) &&
        Check( -C::Infinity, -1.1, 0. ) &&
        Check( -C::Infinity, -11.1, 0. ) &&
        Check( -C::Infinity, -1001.1, 0. );
    CHECK(check13);

    constexpr auto check14 = CheckIsNaN( C::NaN, C::NaN ) &&
        CheckIsNaN( 0.f, C::NaN ) &&
        Check( 1.f, C::NaN, 1.f ) &&
        CheckIsNaN( -1.f, C::NaN ) &&
        CheckIsNaN( C::NaN, 1.f ) &&
        CheckIsNaN( C::NaN, -1.f ) &&
        CheckIsNaN( 3.f, C::NaN );
    CHECK(check14);

    constexpr auto check15 = Check( 1.f, C::Infinity, 1.f ) &&
        Check( -1.f, C::Infinity, 1.f ) &&
        Check( 1.f, -C::Infinity, 1.f ) &&
        Check( -1.f, -C::Infinity, 1.f );
    CHECK(check15);

    constexpr auto check16 = CheckIsNaN( -0.1f, 1.1f ) &&
        CheckIsNaN( -0.1f, -1.1f ) &&
        CheckIsNaN( -10.1f, 1.1f ) &&
        CheckIsNaN( -10.1f, -1.1f );
    CHECK(check16);


    constexpr auto check17 = CheckIsPosInf( 0.f, -1.f ) &&
        CheckIsPosInf( 0.f, -11.f ) &&
        CheckIsNegInf( -0.f, -1.f )&&
        CheckIsNegInf( -0.f, -11.f );
    CHECK(check17);

    constexpr auto check18 = CheckIsPosInf( 0., -2. ) &&
        CheckIsPosInf( 0, -11.1 ) &&
        CheckIsPosInf( -0.f, -2 ) &&
        CheckIsPosInf( -0.f, -11.1 );
    CHECK(check18);

    constexpr auto check19 = Check( 0.f, 1.f, 0.f ) &&
        Check( 0.f, 11.f, 0.f ) &&
        Check( -0.f, 1.f, -0.f ) &&
        Check( -0.f, 11.f, -0.f ) &&
        Check( 0.f, 2.f, 0.f )&&
        Check( 0.f, 11.1f, 0.f ) &&
        Check( -0.f, 2.f, 0.f ) &&
        Check( -0.f, 11.1f, 0.f );
    CHECK(check19);

    constexpr auto check20 = CheckIsPosInf( 1.5, C::Infinity ) &&
        Check( 0.5, C::Infinity, 0. ) &&
        Check( 1.5, -C::Infinity, 0. ) &&
        CheckIsPosInf( 0.5, -C::Infinity );
    CHECK(check20);

    // pow (inf, 2) == inf
    constexpr auto check21 = CheckIsPosInf( C::Infinity, 2.f );
    CHECK(check21);

    // pow (inf, -1) == 0.0
    constexpr auto check22 = Check( C::Infinity, -1.f, 0.f );
    CHECK(check22);

    // pow (-inf, 27) == -inf
    constexpr auto check23 = CheckIsNegInf( -C::Infinity, 27.f );
    CHECK(check23);

    // pow (-inf, 28) == inf
    constexpr auto check24 = CheckIsPosInf( -C::Infinity, 28.f );
    CHECK(check24);

    // pow (-inf, -3) == -0
    constexpr auto check25 = Check( -C::Infinity, -3.f, -0.f );
    CHECK(check25);

    // pow (-inf, -2.0) == 0.0
    constexpr auto check26 = Check( -C::Infinity, -2.f, 0.f );
    CHECK(check26);

    // pow (0.0, 27) == 0.0
    constexpr auto check27 = Check( 0., 27.f, 0.f );
    CHECK(check27);

    // pow (-0, 27) == -0
    constexpr auto check28 = Check( -0., 27.f, -0.f );
    CHECK(check28);

    // pow (0.0, 4) == 0.0
    constexpr auto check29 = Check( 0., 4.f, 0.f );
    CHECK(check29);

    // pow (-0, 4) == 0.0
    constexpr auto check30 = Check( -0., 4.f, 0.f );
    CHECK(check30);

    // pow (0.7, 1.2) == 0.65180494056638638188
    constexpr auto check31 = Check( 0.7f, 1.2f, 0.65180494056638638188f );
    CHECK(check31);

}
TEST_CASE("ConstexprMathTests / DoublePowTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;
    constexpr auto Check = []( C::ValueType x, C::ValueType y, C::ValueType expected ) -> bool
        {
            auto r = Pow( x, y );
            return IsSameValue( r, expected );
        };
    constexpr auto CheckIsNaN = []( C::ValueType x, C::ValueType y ) -> bool
        {
            auto r = Pow( x, y );
            return IsNaN( r );
        };

    constexpr auto CheckIsInf = []( C::ValueType x, C::ValueType y ) -> bool
        {
            auto r = Pow( x, y );
            return IsInf( r );
        };

    constexpr auto CheckIsPosInf = []( C::ValueType x, C::ValueType y ) -> bool
        {
            auto r = Pow( x, y );
            return IsSameValue( r, C::Infinity );
        };

    constexpr auto CheckIsNegInf = []( C::ValueType x, C::ValueType y ) -> bool
        {
            auto r = Pow( x, y );
            return IsSameValue( r, C::NegativeInfinity );
        };


    constexpr auto check1 = Check( 0., 0., 1 ) && Check( -0., 0., 1 ) && Check( 0., -0., 1 ) && Check( -0., -0., 1 );
    CHECK(check1);
    constexpr auto check2 = Check( 10., 0., 1 ) && Check( -10., 0., 1 ) && Check( 10., -0., 1 ) && Check( -10., -0., 1 );
    CHECK(check2);
    constexpr auto check3 = Check( C::NaN, 0., 1 ) && Check( C::NaN, -0., 1 );
    CHECK(check3);

    constexpr auto check4 = CheckIsInf( 1.1, C::Infinity ) &&
        CheckIsInf( C::Infinity, C::Infinity ) &&
        CheckIsInf( -1.1f, C::Infinity ) &&
        CheckIsInf( -C::Infinity, C::Infinity );
    CHECK(check4);

    constexpr auto check5 = Check( 0.9, C::Infinity, 0.f ) &&
        Check( 1e-7, C::Infinity, 0 ) &&
        Check( -0.9, C::Infinity, 0 ) &&
        Check( -1e-7, C::Infinity, 0 );
    CHECK(check5);

    constexpr auto check6 = Check( 1.1, -C::Infinity, 0 ) && Check( C::Infinity, -C::Infinity, 0 ) && Check( -1.1, -C::Infinity, 0 ) && Check( -C::Infinity, -C::Infinity, 0 );
    CHECK(check6);

    constexpr auto check7 = CheckIsInf( 0.9, -C::Infinity ) && CheckIsInf( 1e-7, -C::Infinity ) && CheckIsInf( -0.9, -C::Infinity ) && CheckIsInf( -1e-7, -C::Infinity );
    CHECK(check7);

    constexpr auto check8 = CheckIsInf( C::Infinity, 1e-7 ) && CheckIsInf( C::Infinity, 1 ) && CheckIsInf( C::Infinity, 1e7 );
    CHECK(check8);

    constexpr auto check9 = Check( C::Infinity, -1e-7, 0 ) && Check( C::Infinity, -1, 0 ) && Check( C::Infinity, -1e7, 0 );
    CHECK(check9);

    constexpr auto check10 = CheckIsNegInf( -C::Infinity, 1 ) && CheckIsNegInf( -C::Infinity, 11 ) && CheckIsNegInf( -C::Infinity, 1001 );
    CHECK(check10);

    constexpr auto check11 = CheckIsPosInf( -C::Infinity, 2 ) &&
        CheckIsPosInf( -C::Infinity, 12 ) &&
        CheckIsPosInf( -C::Infinity, 1002 ) &&
        CheckIsPosInf( -C::Infinity, 0.1 ) &&
        CheckIsPosInf( -C::Infinity, 1.1 ) &&
        CheckIsPosInf( -C::Infinity, 11.1 ) &&
        CheckIsPosInf( -C::Infinity, 1001.1 );
    CHECK(check11);

    constexpr auto check12 = Check( -C::Infinity, -1., -0. ) && Check( -C::Infinity, -11, -0. ) && Check( -C::Infinity, -1001, -0. );
    CHECK(check12);

    constexpr auto check13 = Check( -C::Infinity, -2, 0. ) &&
        Check( -C::Infinity, -12, 0. ) &&
        Check( -C::Infinity, -1002, 0. ) &&
        Check( -C::Infinity, -0.1, 0. ) &&
        Check( -C::Infinity, -1.1, 0. ) &&
        Check( -C::Infinity, -11.1, 0. ) &&
        Check( -C::Infinity, -1001.1, 0. );
    CHECK(check13);

    constexpr auto check14 = CheckIsNaN( C::NaN, C::NaN ) &&
        CheckIsNaN( 0., C::NaN ) &&
        Check( 1., C::NaN, 1. ) &&
        CheckIsNaN( -1., C::NaN ) &&
        CheckIsNaN( C::NaN, 1. ) &&
        CheckIsNaN( C::NaN, -1. ) &&
        CheckIsNaN( 3., C::NaN );
    CHECK(check14);

    constexpr auto check15 = Check( 1., C::Infinity, 1. ) &&
        Check( -1., C::Infinity, 1. ) &&
        Check( 1., -C::Infinity, 1. ) &&
        Check( -1., -C::Infinity, 1. );
    CHECK(check15);

    constexpr auto check16 = CheckIsNaN( -0.1, 1.1 ) &&
        CheckIsNaN( -0.1, -1.1 ) &&
        CheckIsNaN( -10.1, 1.1 ) &&
        CheckIsNaN( -10.1, -1.1 );
    CHECK(check16);


    constexpr auto check17 = CheckIsPosInf( 0., -1. ) &&
        CheckIsPosInf( 0., -11. ) &&
        CheckIsNegInf( -0., -1. ) &&
        CheckIsNegInf( -0., -11. );
    CHECK(check17);

    constexpr auto check18 = CheckIsPosInf( 0., -2. ) &&
        CheckIsPosInf( 0, -11.1 ) &&
        CheckIsPosInf( -0., -2 ) &&
        CheckIsPosInf( -0., -11.1 );
    CHECK(check18);

    constexpr auto check19 = Check( 0., 1., 0. ) &&
        Check( 0., 11., 0. ) &&
        Check( -0., 1., -0. ) &&
        Check( -0., 11., -0. ) &&
        Check( 0., 2., 0. ) &&
        Check( 0., 11.1, 0. ) &&
        Check( -0., 2., 0.f ) &&
        Check( -0., 11.1, 0.f );
    CHECK(check19);

    constexpr auto check20 = CheckIsPosInf( 1.5, C::Infinity ) &&
        Check( 0.5, C::Infinity, 0. ) &&
        Check( 1.5, -C::Infinity, 0. ) &&
        CheckIsPosInf( 0.5, -C::Infinity );
    CHECK(check20);

    // pow (inf, 2) == inf
    constexpr auto check21 = CheckIsPosInf( C::Infinity, 2. );
    CHECK(check21);

    // pow (inf, -1) == 0.0
    constexpr auto check22 = Check( C::Infinity, -1., 0. );
    CHECK(check22);

    // pow (-inf, 27) == -inf
    constexpr auto check23 = CheckIsNegInf( -C::Infinity, 27. );
    CHECK(check23);

    // pow (-inf, 28) == inf
    constexpr auto check24 = CheckIsPosInf( -C::Infinity, 28. );
    CHECK(check24);

    // pow (-inf, -3) == -0
    constexpr auto check25 = Check( -C::Infinity, -3., -0. );
    CHECK(check25);

    // pow (-inf, -2.0) == 0.0
    constexpr auto check26 = Check( -C::Infinity, -2., 0. );
    CHECK(check26);

    // pow (0.0, 27) == 0.0
    constexpr auto check27 = Check( 0., 27., 0. );
    CHECK(check27);

    // pow (-0, 27) == -0
    constexpr auto check28 = Check( -0., 27., -0. );
    CHECK(check28);

    // pow (0.0, 4) == 0.0
    constexpr auto check29 = Check( 0., 4., 0. );
    CHECK(check29);

    // pow (-0, 4) == 0.0
    constexpr auto check30 = Check( -0., 4., 0. );
    CHECK(check30);

    // pow (0.7, 1.2) == 0.65180494056638638188
    constexpr auto check31 = Check( 0.7, 1.2, 0.65180494056638638188 );
    CHECK(check31);

}
TEST_CASE("ConstexprMathTests / FloatRemainderTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;
    constexpr auto Check = []( C::ValueType x, C::ValueType y, C::ValueType expected ) -> bool
        {
            auto r = Remainder( x, y );
            return IsSameValue( r, expected );
        };
    constexpr auto CheckIsNaN = []( C::ValueType x, C::ValueType y ) -> bool
        {
            auto r = Remainder( x, y );
            return IsNaN( r );
        };

    // remainder (1, 0) == NaN
    constexpr auto check1 = CheckIsNaN( 1., 0. );
    CHECK(check1);

    // remainder (1, -0) == NaN
    constexpr auto check2 = CheckIsNaN( 1., -0. );
    CHECK(check2);

    // remainder (inf, 1) == NaN
    constexpr auto check3 = CheckIsNaN( C::Infinity, 1. );
    CHECK(check3);

    // remainder (-inf, 1) == NaN
    constexpr auto check4 = CheckIsNaN( C::NegativeInfinity, 1. );
    CHECK(check4);

    // remainder (NaN, NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN, C::NaN );
    CHECK(check5);

    // remainder (1.625, 1.0) == -0.375
    constexpr auto check6 = Check( 1.625, 1.0, -0.375 );
    CHECK(check6);

    // remainder (-1.625, 1.0) == 0.375
    constexpr auto check7 = Check( -1.625, 1.0, 0.375 );
    CHECK(check7);

    // remainder (1.625, -1.0) == -0.375
    constexpr auto check8 = Check( 1.625, -1.0, -0.375 );
    CHECK(check8);

    // remainder (-1.625, -1.0) == 0.375
    constexpr auto check9 = Check( -1.625, -1.0, 0.375 );
    CHECK(check9);

    // remainder (5.0, 2.0) == 1.0
    constexpr auto check10 = Check( 5.0, 2.0, 1.0 );
    CHECK(check10);

    // remainder (3.0, 2.0) == -1.0
    constexpr auto check11 = Check( 3.0, 2.0, -1.0 );
    CHECK(check11);
}
TEST_CASE("ConstexprMathTests / DoubleRemainderTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;
    constexpr auto Check = []( C::ValueType x, C::ValueType y, C::ValueType expected ) -> bool
        {
            auto r = Remainder( x, y );
            return IsSameValue( r, expected );
        };
    constexpr auto CheckIsNaN = []( C::ValueType x, C::ValueType y ) -> bool
        {
            auto r = Remainder( x, y );
            return IsNaN( r );
        };

    // remainder (1, 0) == NaN
    constexpr auto check1 = CheckIsNaN( 1., 0. );
    CHECK(check1);

    // remainder (1, -0) == NaN
    constexpr auto check2 = CheckIsNaN( 1., -0. );
    CHECK(check2);

    // remainder (inf, 1) == NaN
    constexpr auto check3 = CheckIsNaN( C::Infinity, 1. );
    CHECK(check3);

    // remainder (-inf, 1) == NaN
    constexpr auto check4 = CheckIsNaN( C::NegativeInfinity, 1. );
    CHECK(check4);

    // remainder (NaN, NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN, C::NaN );
    CHECK(check5);

    // remainder (1.625, 1.0) == -0.375
    constexpr auto check6 = Check( 1.625, 1.0, -0.375 );
    CHECK(check6);

    // remainder (-1.625, 1.0) == 0.375
    constexpr auto check7 = Check( -1.625, 1.0, 0.375 );
    CHECK(check7);

    // remainder (1.625, -1.0) == -0.375
    constexpr auto check8 = Check( 1.625, -1.0, -0.375 );
    CHECK(check8);

    // remainder (-1.625, -1.0) == 0.375
    constexpr auto check9 = Check( -1.625, -1.0, 0.375 );
    CHECK(check9);

    // remainder (5.0, 2.0) == 1.0
    constexpr auto check10 = Check( 5.0, 2.0, 1.0 );
    CHECK(check10);

    // remainder (3.0, 2.0) == -1.0
    constexpr auto check11 = Check( 3.0, 2.0, -1.0 );
    CHECK(check11);
}
TEST_CASE("ConstexprMathTests / FloatRemQuoTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;
    constexpr auto Check = []( C::ValueType x, C::ValueType y, C::ValueType expected, int expectedQuo ) -> bool
        {
            int quo{};
            auto r = RemQuo( x, y, &quo );
            return IsSameValue( r, expected ) && expectedQuo == quo;
        };
    constexpr auto CheckIsNaN = []( C::ValueType x, C::ValueType y ) -> bool
        {
            int quo{};
            auto r = RemQuo( x, y, &quo );
            return IsNaN( r );
        };

    // remquo (1, 0, &x) == NaN
    constexpr auto check1 = CheckIsNaN( 1., 0. );
    CHECK(check1);

    // remquo (1, -0, &x) == NaN
    constexpr auto check2 = CheckIsNaN( 1., -0. );
    CHECK(check2);

    // remquo (inf, 1, &x) == NaN
    constexpr auto check3 = CheckIsNaN( C::Infinity, 1. );
    CHECK(check3);

    // remquo (-inf, 1, &x) == NaN
    constexpr auto check4 = CheckIsNaN( -C::Infinity, 1. );
    CHECK(check4);

    // remquo (NaN, NaN, &x) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN, C::NaN );
    CHECK(check5);

    // remquo (1.625, 1.0, &x) == -0.375, x == 2
    constexpr auto check6 = Check( 1.625, 1.0, -0.375, 2 );
    CHECK(check6);

    // remquo (-1.625, 1.0, &x) == 0.375, x == -2
    constexpr auto check7 = Check( -1.625, 1.0, 0.375, -2 );
    CHECK(check7);

    // remquo (1.625, -1.0, &x) == -0.375, x == -2
    constexpr auto check8 = Check( 1.625, -1.0, -0.375, -2 );
    CHECK(check8);

    // remquo (-1.625, -1.0, &x) == 0.375, x == 2
    constexpr auto check9 = Check( -1.625, -1.0, 0.375, 2 );
    CHECK(check9);

    // remquo (5, 2, &x) == 1, x == 2
    constexpr auto check10 = Check( 5, 2, 1., 2 );
    CHECK(check10);

    // remquo (3, 2, &x) == -1, x == 2
    constexpr auto check11 = Check( 3, 2, -1., 2 );
    CHECK(check11);
}
TEST_CASE("ConstexprMathTests / DoubleRemQuoTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;
    constexpr auto Check = []( C::ValueType x, C::ValueType y, C::ValueType expected, int expectedQuo ) -> bool
        {
            int quo{};
            auto r = RemQuo( x, y, &quo );
            return IsSameValue( r, expected ) && expectedQuo == quo;
        };
    constexpr auto CheckIsNaN = []( C::ValueType x, C::ValueType y ) -> bool
        {
            int quo{};
            auto r = RemQuo( x, y, &quo );
            return IsNaN( r );
        };

    // remquo (1, 0, &x) == NaN
    constexpr auto check1 = CheckIsNaN( 1., 0. );
    CHECK(check1);

    // remquo (1, -0, &x) == NaN
    constexpr auto check2 = CheckIsNaN( 1., -0. );
    CHECK(check2);

    // remquo (inf, 1, &x) == NaN
    constexpr auto check3 = CheckIsNaN( C::Infinity, 1. );
    CHECK(check3);

    // remquo (-inf, 1, &x) == NaN
    constexpr auto check4 = CheckIsNaN( -C::Infinity, 1. );
    CHECK(check4);

    // remquo (NaN, NaN, &x) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN, C::NaN );
    CHECK(check5);

    // remquo (1.625, 1.0, &x) == -0.375, x == 2
    constexpr auto check6 = Check( 1.625, 1.0, -0.375, 2 );
    CHECK(check6);

    // remquo (-1.625, 1.0, &x) == 0.375, x == -2
    constexpr auto check7 = Check( -1.625, 1.0, 0.375, -2 );
    CHECK(check7);

    // remquo (1.625, -1.0, &x) == -0.375, x == -2
    constexpr auto check8 = Check( 1.625, -1.0, -0.375, -2 );
    CHECK(check8);

    // remquo (-1.625, -1.0, &x) == 0.375, x == 2
    constexpr auto check9 = Check( -1.625, -1.0, 0.375, 2 );
    CHECK(check9);

    // remquo (5, 2, &x) == 1, x == 2
    constexpr auto check10 = Check( 5, 2, 1., 2 );
    CHECK(check10);

    // remquo (3, 2, &x) == -1, x == 2
    constexpr auto check11 = Check( 3, 2, -1., 2 );
    CHECK(check11);
}
TEST_CASE("ConstexprMathTests / FloatDeg2RadTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    constexpr auto result1 = Deg2Rad( 0.f );
    CHECK(result1 == C::Zero);

    constexpr auto result2 = Deg2Rad( 45.f );
    static_assert( result2 == C::PiOver4 );
    CHECK(result2 == C::PiOver4);

    constexpr auto result3 = Deg2Rad( 90.f );
    static_assert( result3 == C::PiOver2 );
    CHECK(result3 == C::PiOver2);

}
TEST_CASE("ConstexprMathTests / DoubleDeg2RadTest1", "[math][ConstexprMathTests]")
{
    constexpr auto arg = 0.001;
    const auto& arg2 = arg;
    constexpr auto result1 = Deg2Rad( arg );
    CHECK(result1 == 1.7453292519943296e-5);

    auto result2 = Deg2Rad<double>( arg2 );

}
TEST_CASE("ConstexprMathTests / FloatRad2DegTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    constexpr auto result1 = Rad2Deg( 0.f );
    CHECK(result1 == C::Zero);

    constexpr auto result2 = Rad2Deg( C::PiOver4 );
    static_assert( result2 == 45.f );
    CHECK(result2 == 45.f);

    constexpr auto result3 = Rad2Deg( C::PiOver2 );
    static_assert( result3 == 90.f );
    CHECK(result3 == 90.f);

}
TEST_CASE("ConstexprMathTests / FloatSinTest1", "[math][ConstexprMathTests]")
{
    constexpr auto rM20000 = Deg2Rad( -20000.f );
    constexpr auto rM720 = Deg2Rad( -720.f );
    constexpr auto rM360 = Deg2Rad( -360.f );
    constexpr auto rM180 = Deg2Rad( -180.f );
    constexpr auto rM135 = Deg2Rad( 135.f );
    constexpr auto rM90 = Deg2Rad( -90.f );
    constexpr auto rM45 = Deg2Rad( -45.f );
    constexpr auto r0 = Deg2Rad( 0.f );
    constexpr auto r45 = Deg2Rad( 45.f );
    constexpr auto r90 = Deg2Rad( 90.f );
    constexpr auto r135 = Deg2Rad( 135.f );
    constexpr auto r180 = Deg2Rad( 180.f );
    constexpr auto r360 = Deg2Rad( 360.f );
    constexpr auto r720 = Deg2Rad( 720.f );
    constexpr auto r20000 = Deg2Rad( 20000.f );

    constexpr auto sineRM20000 = Sin( rM20000 );
    constexpr auto sineRM720 = Sin( rM720 );
    constexpr auto sineRM360 = Sin( rM360 );
    constexpr auto sineRM180 = Sin( rM180 );
    constexpr auto sineRM135 = Sin( rM135 );
    constexpr auto sineRM90 = Sin( rM90 );
    constexpr auto sineRM45 = Sin( rM45 );
    constexpr auto sineR0 = Sin( r0 );
    constexpr auto sineR45 = Sin( r45 );
    constexpr auto sineR90 = Sin( r90 );
    constexpr auto sineR135 = Sin( r135 );
    constexpr auto sineR180 = Sin( r180 );
    constexpr auto sineR360 = Sin( r360 );
    constexpr auto sineR720 = Sin( r720 );
    constexpr auto sineR20000 = Sin( r20000 );
    constexpr auto sineMax = Sin( std::numeric_limits<float>::max() );

    auto expectedSineRM20000 = std::sin( rM20000 );
    auto expectedSineRM720 = std::sin( rM720 );
    auto expectedSineRM360 = std::sin( rM360 );
    auto expectedSineRM180 = std::sin( rM180 );
    auto expectedSineRM135 = std::sin( rM135 );
    auto expectedSineRM90 = std::sin( rM90 );
    auto expectedSineRM45 = std::sin( rM45 );
    auto expectedSineR0 = std::sin( r0 );
    auto expectedSineR45 = std::sin( r45 );
    auto expectedSineR90 = std::sin( r90 );
    auto expectedSineR135 = std::sin( r135 );
    auto expectedSineR180 = std::sin( r180 );
    auto expectedSineR360 = std::sin( r360 );
    auto expectedSineR720 = std::sin( r720 );
    auto expectedSineR20000 = std::sin( r20000 );
    auto expectedSineMax = std::sin( std::numeric_limits<float>::max( ) );

    CHECK(expectedSineRM20000 == sineRM20000);
    CHECK(expectedSineRM720 == sineRM720);
    CHECK(expectedSineRM360 == sineRM360);
    CHECK(expectedSineRM180 == sineRM180);
    CHECK(expectedSineRM135 == sineRM135);
    CHECK(expectedSineRM90 == sineRM90);
    CHECK((expectedSineRM45) == Catch::Approx(sineRM45).epsilon((0.0000000000001) / 100.0));
    CHECK(expectedSineR0 == sineR0);
    CHECK((expectedSineR45) == Catch::Approx(sineR45).epsilon((0.0000000000001) / 100.0));
    CHECK(expectedSineR90 == sineR90);
    CHECK(expectedSineR135 == sineR135);
    CHECK(expectedSineR180 == sineR180);
    CHECK(expectedSineR360 == sineR360);
    CHECK(expectedSineR720 == sineR720);
    CHECK(expectedSineR20000 == sineR20000);
    CHECK(expectedSineMax == sineMax);


    constexpr auto radians = Deg2Rad( 0.001f );
    constexpr auto result1a = Sin( radians );
    auto result1b = std::sin( radians );
    auto result1Diff = result1a - result1b;
    CHECK(result1a == result1b);
    CHECK(result1a == 1.7453292519057202e-5f);
    CHECK(result1b == 1.7453292519057202e-5f);
}
TEST_CASE("ConstexprMathTests / DoubleSinTest1", "[math][ConstexprMathTests]")
{
    constexpr auto rM20000 = Deg2Rad( -20000. );
    constexpr auto rM720 = Deg2Rad( -720. );
    constexpr auto rM360 = Deg2Rad( -360. );
    constexpr auto rM180 = Deg2Rad( -180. );
    constexpr auto rM135 = Deg2Rad( 135. );
    constexpr auto rM90 = Deg2Rad( -90. );
    constexpr auto rM45 = Deg2Rad( -45. );
    constexpr auto r0 = Deg2Rad( 0. );
    constexpr auto r45 = Deg2Rad( 45. );
    constexpr auto r90 = Deg2Rad( 90. );
    constexpr auto r135 = Deg2Rad( 135. );
    constexpr auto r180 = Deg2Rad( 180. );
    constexpr auto r360 = Deg2Rad( 360. );
    constexpr auto r720 = Deg2Rad( 720. );
    constexpr auto r20000 = Deg2Rad( 20000. );

    constexpr auto sineRM20000 = Sin( rM20000 );
    constexpr auto sineRM720 = Sin( rM720 );
    constexpr auto sineRM360 = Sin( rM360 );
    constexpr auto sineRM180 = Sin( rM180 );
    constexpr auto sineRM135 = Sin( rM135 );
    constexpr auto sineRM90 = Sin( rM90 );
    constexpr auto sineRM45 = Sin( rM45 );
    constexpr auto sineR0 = Sin( r0 );
    constexpr auto sineR45 = Sin( r45 );
    constexpr auto sineR90 = Sin( r90 );
    constexpr auto sineR135 = Sin( r135 );
    constexpr auto sineR180 = Sin( r180 );
    constexpr auto sineR360 = Sin( r360 );
    constexpr auto sineR720 = Sin( r720 );
    constexpr auto sineR20000 = Sin( r20000 );
    constexpr auto sineMax = Sin( std::numeric_limits<double>::max( ) );

    auto expectedSineRM20000 = std::sin( rM20000 );
    auto expectedSineRM720 = std::sin( rM720 );
    auto expectedSineRM360 = std::sin( rM360 );
    auto expectedSineRM180 = std::sin( rM180 );
    auto expectedSineRM135 = std::sin( rM135 );
    auto expectedSineRM90 = std::sin( rM90 );
    auto expectedSineRM45 = std::sin( rM45 );
    auto expectedSineR0 = std::sin( r0 );
    auto expectedSineR45 = std::sin( r45 );
    auto expectedSineR90 = std::sin( r90 );
    auto expectedSineR135 = std::sin( r135 );
    auto expectedSineR180 = std::sin( r180 );
    auto expectedSineR360 = std::sin( r360 );
    auto expectedSineR720 = std::sin( r720 );
    auto expectedSineR20000 = std::sin( r20000 );
    auto expectedSineMax = std::sin( std::numeric_limits<double>::max( ) );

    CHECK(expectedSineRM20000 == sineRM20000);
    CHECK(expectedSineRM720 == sineRM720);
    CHECK(expectedSineRM360 == sineRM360);
    CHECK(expectedSineRM180 == sineRM180);
    CHECK(expectedSineRM135 == sineRM135);
    CHECK(expectedSineRM90 == sineRM90);
    CHECK((expectedSineRM45) == Catch::Approx(sineRM45).epsilon((0.0000000000001) / 100.0));
    CHECK(expectedSineR0 == sineR0);
    CHECK((expectedSineR45) == Catch::Approx(sineR45).epsilon((0.0000000000001) / 100.0));
    CHECK(expectedSineR90 == sineR90);
    CHECK(expectedSineR135 == sineR135);
    CHECK(expectedSineR180 == sineR180);
    CHECK(expectedSineR360 == sineR360);
    CHECK(expectedSineR720 == sineR720);
    CHECK(expectedSineR20000 == sineR20000);
    CHECK(expectedSineMax == sineMax);

    constexpr auto radians = Deg2Rad( 0.001 );
    constexpr auto result1a = Sin( radians );
    auto result1b = std::sin( radians );
    auto result1Diff = result1a - result1b;
    CHECK(result1a == result1b);
    CHECK(result1a == 1.7453292519057202e-5);
    CHECK(result1b == 1.7453292519057202e-5);
}
TEST_CASE("ConstexprMathTests / FloatCosTest1", "[math][ConstexprMathTests]")
{
    constexpr auto rM20000 = Deg2Rad( -20000.f );
    constexpr auto rM720 = Deg2Rad( -720.f );
    constexpr auto rM360 = Deg2Rad( -360.f );
    constexpr auto rM180 = Deg2Rad( -180.f );
    constexpr auto rM135 = Deg2Rad( 135.f );
    constexpr auto rM90 = Deg2Rad( -90.f );
    constexpr auto rM45 = Deg2Rad( -45.f );
    constexpr auto r0 = Deg2Rad( 0.f );
    constexpr auto r45 = Deg2Rad( 45.f );
    constexpr auto r90 = Deg2Rad( 90.f );
    constexpr auto r135 = Deg2Rad( 135.f );
    constexpr auto r180 = Deg2Rad( 180.f );
    constexpr auto r360 = Deg2Rad( 360.f );
    constexpr auto r720 = Deg2Rad( 720.f );
    constexpr auto r20000 = Deg2Rad( 20000.f );

    constexpr auto cosineRM20000 = Cos( rM20000 );
    constexpr auto cosineRM720 = Cos( rM720 );
    constexpr auto cosineRM360 = Cos( rM360 );
    constexpr auto cosineRM180 = Cos( rM180 );
    constexpr auto cosineRM135 = Cos( rM135 );
    constexpr auto cosineRM90 = Cos( rM90 );
    constexpr auto cosineRM45 = Cos( rM45 );
    constexpr auto cosineR0 = Cos( r0 );
    constexpr auto cosineR45 = Cos( r45 );
    constexpr auto cosineR90 = Cos( r90 );
    constexpr auto cosineR135 = Cos( r135 );
    constexpr auto cosineR180 = Cos( r180 );
    constexpr auto cosineR360 = Cos( r360 );
    constexpr auto cosineR720 = Cos( r720 );
    constexpr auto cosineR20000 = Cos( r20000 );

    auto expectedCosineRM20000 = std::cos( rM20000 );
    auto expectedCosineRM720 = std::cos( rM720 );
    auto expectedCosineRM360 = std::cos( rM360 );
    auto expectedCosineRM180 = std::cos( rM180 );
    auto expectedCosineRM135 = std::cos( rM135 );
    auto expectedCosineRM90 = std::cos( rM90 );
    auto expectedCosineRM45 = std::cos( rM45 );
    auto expectedCosineR0 = std::cos( r0 );
    auto expectedCosineR45 = std::cos( r45 );
    auto expectedCosineR90 = std::cos( r90 );
    auto expectedCosineR135 = std::cos( r135 );
    auto expectedCosineR180 = std::cos( r180 );
    auto expectedCosineR360 = std::cos( r360 );
    auto expectedCosineR720 = std::cos( r720 );
    auto expectedCosineR20000 = std::cos( r20000 );

    CHECK(expectedCosineRM20000 == cosineRM20000);
    CHECK(expectedCosineRM720 == cosineRM720);
    CHECK(expectedCosineRM360 == cosineRM360);
    CHECK(expectedCosineRM180 == cosineRM180);
    CHECK(expectedCosineRM135 == cosineRM135);
    CHECK(expectedCosineRM90 == cosineRM90);
    CHECK((expectedCosineRM45) == Catch::Approx(cosineRM45).epsilon((0.0000000000001) / 100.0));
    CHECK(expectedCosineR0 == cosineR0);
    CHECK((expectedCosineR45) == Catch::Approx(cosineR45).epsilon((0.0000000000001) / 100.0));
    CHECK(expectedCosineR90 == cosineR90);
    CHECK(expectedCosineR135 == cosineR135);
    CHECK(expectedCosineR180 == cosineR180);
    CHECK(expectedCosineR360 == cosineR360);
    CHECK(expectedCosineR720 == cosineR720);
    CHECK(expectedCosineR20000 == cosineR20000);


    constexpr auto radians = Deg2Rad( 0.001f );
    constexpr auto result1a = Cos( radians );
    auto result1b = std::cos( radians );
    auto result1Diff = result1a - result1b;
    CHECK(result1a == result1b);
    CHECK(result1a == 1.f);
    CHECK(result1b == 1.f);
}
TEST_CASE("ConstexprMathTests / DoubleCosTest1", "[math][ConstexprMathTests]")
{
    constexpr auto rM20000 = Deg2Rad( -20000. );
    constexpr auto rM720 = Deg2Rad( -720. );
    constexpr auto rM360 = Deg2Rad( -360. );
    constexpr auto rM180 = Deg2Rad( -180. );
    constexpr auto rM135 = Deg2Rad( 135. );
    constexpr auto rM90 = Deg2Rad( -90. );
    constexpr auto rM45 = Deg2Rad( -45. );
    constexpr auto r0 = Deg2Rad( 0. );
    constexpr auto r45 = Deg2Rad( 45. );
    constexpr auto r90 = Deg2Rad( 90. );
    constexpr auto r135 = Deg2Rad( 135. );
    constexpr auto r180 = Deg2Rad( 180. );
    constexpr auto r360 = Deg2Rad( 360. );
    constexpr auto r720 = Deg2Rad( 720. );
    constexpr auto r20000 = Deg2Rad( 20000. );

    constexpr auto cosineRM20000 = Cos( rM20000 );
    constexpr auto cosineRM720 = Cos( rM720 );
    constexpr auto cosineRM360 = Cos( rM360 );
    constexpr auto cosineRM180 = Cos( rM180 );
    constexpr auto cosineRM135 = Cos( rM135 );
    constexpr auto cosineRM90 = Cos( rM90 );
    constexpr auto cosineRM45 = Cos( rM45 );
    constexpr auto cosineR0 = Cos( r0 );
    constexpr auto cosineR45 = Cos( r45 );
    constexpr auto cosineR90 = Cos( r90 );
    constexpr auto cosineR135 = Cos( r135 );
    constexpr auto cosineR180 = Cos( r180 );
    constexpr auto cosineR360 = Cos( r360 );
    constexpr auto cosineR720 = Cos( r720 );
    constexpr auto cosineR20000 = Cos( r20000 );

    auto expectedCosineRM20000 = std::cos( rM20000 );
    auto expectedCosineRM720 = std::cos( rM720 );
    auto expectedCosineRM360 = std::cos( rM360 );
    auto expectedCosineRM180 = std::cos( rM180 );
    auto expectedCosineRM135 = std::cos( rM135 );
    auto expectedCosineRM90 = std::cos( rM90 );
    auto expectedCosineRM45 = std::cos( rM45 );
    auto expectedCosineR0 = std::cos( r0 );
    auto expectedCosineR45 = std::cos( r45 );
    auto expectedCosineR90 = std::cos( r90 );
    auto expectedCosineR135 = std::cos( r135 );
    auto expectedCosineR180 = std::cos( r180 );
    auto expectedCosineR360 = std::cos( r360 );
    auto expectedCosineR720 = std::cos( r720 );
    auto expectedCosineR20000 = std::cos( r20000 );

    CHECK(expectedCosineRM20000 == cosineRM20000);
    CHECK(expectedCosineRM720 == cosineRM720);
    CHECK(expectedCosineRM360 == cosineRM360);
    CHECK(expectedCosineRM180 == cosineRM180);
    CHECK(expectedCosineRM135 == cosineRM135);
    CHECK(expectedCosineRM90 == cosineRM90);
    CHECK((expectedCosineRM45) == Catch::Approx(cosineRM45).epsilon((0.0000000000001) / 100.0));
    CHECK(expectedCosineR0 == cosineR0);
    CHECK((expectedCosineR45) == Catch::Approx(cosineR45).epsilon((0.0000000000001) / 100.0));
    CHECK(expectedCosineR90 == cosineR90);
    CHECK(expectedCosineR135 == cosineR135);
    CHECK(expectedCosineR180 == cosineR180);
    CHECK(expectedCosineR360 == cosineR360);
    CHECK(expectedCosineR720 == cosineR720);
    CHECK(expectedCosineR20000 == cosineR20000);


    constexpr auto radians = Deg2Rad( 0.001 );
    constexpr auto result1a = Cos( radians );
    auto result1b = std::cos( radians );
    auto result1Diff = result1a - result1b;
    CHECK(result1a == result1b);
    CHECK(result1a == 0.99999999984769128);
    CHECK(result1b == 0.99999999984769128);
}
TEST_CASE("ConstexprMathTests / FloatTanTest1", "[math][ConstexprMathTests]")
{
    constexpr auto rM20000 = Deg2Rad( -20000.f );
    constexpr auto rM720 = Deg2Rad( -720.f );
    constexpr auto rM360 = Deg2Rad( -360.f );
    constexpr auto rM180 = Deg2Rad( -180.f );
    constexpr auto rM135 = Deg2Rad( 135.f );
    constexpr auto rM90 = Deg2Rad( -90.f );
    constexpr auto rM45 = Deg2Rad( -45.f );
    constexpr auto r0 = Deg2Rad( 0.f );
    constexpr auto r45 = Deg2Rad( 45.f );
    constexpr auto r90 = Deg2Rad( 90.f );
    constexpr auto r135 = Deg2Rad( 135.f );
    constexpr auto r180 = Deg2Rad( 180.f );
    constexpr auto r360 = Deg2Rad( 360.f );
    constexpr auto r720 = Deg2Rad( 720.f );
    constexpr auto r20000 = Deg2Rad( 20000.f );

    constexpr auto tanRM20000 = Tan( rM20000 );
    constexpr auto tanRM720 = Tan( rM720 );
    constexpr auto tanRM360 = Tan( rM360 );
    constexpr auto tanRM180 = Tan( rM180 );
    constexpr auto tanRM135 = Tan( rM135 );
    constexpr auto tanRM90 = Tan( rM90 );
    constexpr auto tanRM45 = Tan( rM45 );
    constexpr auto tanR0 = Tan( r0 );
    constexpr auto tanR45 = Tan( r45 );
    constexpr auto tanR90 = Tan( r90 );
    constexpr auto tanR135 = Tan( r135 );
    constexpr auto tanR180 = Tan( r180 );
    constexpr auto tanR360 = Tan( r360 );
    constexpr auto tanR720 = Tan( r720 );
    constexpr auto tanR20000 = Tan( r20000 );

    auto expectedTanRM20000 = std::tan( rM20000 );
    auto expectedTanRM720 = std::tan( rM720 );
    auto expectedTanRM360 = std::tan( rM360 );
    auto expectedTanRM180 = std::tan( rM180 );
    auto expectedTanRM135 = std::tan( rM135 );
    auto expectedTanRM90 = std::tan( rM90 );
    auto expectedTanRM45 = std::tan( rM45 );
    auto expectedTanR0 = std::tan( r0 );
    auto expectedTanR45 = std::tan( r45 );
    auto expectedTanR90 = std::tan( r90 );
    auto expectedTanR135 = std::tan( r135 );
    auto expectedTanR180 = std::tan( r180 );
    auto expectedTanR360 = std::tan( r360 );
    auto expectedTanR720 = std::tan( r720 );
    auto expectedTanR20000 = std::tan( r20000 );

    CHECK(expectedTanRM20000 == tanRM20000);
    CHECK(expectedTanRM720 == tanRM720);
    CHECK((expectedTanRM360) == Catch::Approx(tanRM360).epsilon((0.00001f) / 100.0));
    CHECK((expectedTanRM180) == Catch::Approx(tanRM180).epsilon((0.00001f) / 100.0));
    CHECK(expectedTanRM135 == tanRM135);
    CHECK_THAT(tanRM90, Catch::Matchers::WithinULP(expectedTanRM90, 1));
    CHECK_THAT(tanRM90, Catch::Matchers::WithinULP(static_cast<float>(std::tan(static_cast<double>(rM90))), 1));
    CHECK(expectedTanRM45 == tanRM45);
    CHECK(expectedTanR0 == tanR0);
    CHECK(expectedTanR45 == tanR45);
    CHECK_THAT(tanR90, Catch::Matchers::WithinULP(expectedTanR90, 1));
    CHECK_THAT(tanR90, Catch::Matchers::WithinULP(static_cast<float>(std::tan(static_cast<double>(r90))), 1));
    CHECK(expectedTanR135 == tanR135);
    CHECK((expectedTanR180) == Catch::Approx(tanR180).epsilon((0.00001f) / 100.0));
    CHECK((expectedTanR360) == Catch::Approx(tanR360).epsilon((0.00001f) / 100.0));
    CHECK(expectedTanR720 == tanR720);
    CHECK(expectedTanR20000 == tanR20000);


    constexpr auto radians = Deg2Rad( 0.001f );
    constexpr auto result1a = Tan( radians );
    auto result1b = std::tan( radians );
    auto result1Diff = result1a - result1b;
    CHECK(result1a == result1b);
    CHECK(result1a == 1.74532925e-05f);
    CHECK(result1b == 1.74532925e-05f);
}
TEST_CASE("ConstexprMathTests / DoubleTanTest1", "[math][ConstexprMathTests]")
{
    constexpr auto rM20000 = Deg2Rad( -20000. );
    constexpr auto rM720 = Deg2Rad( -720. );
    constexpr auto rM360 = Deg2Rad( -360. );
    constexpr auto rM180 = Deg2Rad( -180. );
    constexpr auto rM135 = Deg2Rad( 135. );
    constexpr auto rM90 = Deg2Rad( -90. );
    constexpr auto rM45 = Deg2Rad( -45. );
    constexpr auto r0 = Deg2Rad( 0. );
    constexpr auto r45 = Deg2Rad( 45. );
    constexpr auto r90 = Deg2Rad( 90. );
    constexpr auto r135 = Deg2Rad( 135. );
    constexpr auto r180 = Deg2Rad( 180. );
    constexpr auto r360 = Deg2Rad( 360. );
    constexpr auto r720 = Deg2Rad( 720. );
    constexpr auto r20000 = Deg2Rad( 20000. );

    constexpr auto tanRM20000 = Tan( rM20000 );
    constexpr auto tanRM720 = Tan( rM720 );
    constexpr auto tanRM360 = Tan( rM360 );
    constexpr auto tanRM180 = Tan( rM180 );
    constexpr auto tanRM135 = Tan( rM135 );
    constexpr auto tanRM90 = Tan( rM90 );
    constexpr auto tanRM45 = Tan( rM45 );
    constexpr auto tanR0 = Tan( r0 );
    constexpr auto tanR45 = Tan( r45 );
    constexpr auto tanR90 = Tan( r90 );
    constexpr auto tanR135 = Tan( r135 );
    constexpr auto tanR180 = Tan( r180 );
    constexpr auto tanR360 = Tan( r360 );
    constexpr auto tanR720 = Tan( r720 );
    constexpr auto tanR20000 = Tan( r20000 );

    auto expectedTanRM20000 = std::tan( rM20000 );
    auto expectedTanRM720 = std::tan( rM720 );
    auto expectedTanRM360 = std::tan( rM360 );
    auto expectedTanRM180 = std::tan( rM180 );
    auto expectedTanRM135 = std::tan( rM135 );
    auto expectedTanRM90 = std::tan( rM90 );
    auto expectedTanRM45 = std::tan( rM45 );
    auto expectedTanR0 = std::tan( r0 );
    auto expectedTanR45 = std::tan( r45 );
    auto expectedTanR90 = std::tan( r90 );
    auto expectedTanR135 = std::tan( r135 );
    auto expectedTanR180 = std::tan( r180 );
    auto expectedTanR360 = std::tan( r360 );
    auto expectedTanR720 = std::tan( r720 );
    auto expectedTanR20000 = std::tan( r20000 );

    CHECK(expectedTanRM20000 == tanRM20000);
    CHECK(expectedTanRM720 == tanRM720);
    CHECK((expectedTanRM360) == Catch::Approx(tanRM360).epsilon((0.00001f) / 100.0));
    CHECK((expectedTanRM180) == Catch::Approx(tanRM180).epsilon((0.00001f) / 100.0));
    CHECK(expectedTanRM135 == tanRM135);
    CHECK(expectedTanRM90 == tanRM90);
    CHECK(expectedTanRM45 == tanRM45);
    CHECK(expectedTanR0 == tanR0);
    CHECK(expectedTanR45 == tanR45);
    CHECK(expectedTanR90 == tanR90);
    CHECK(expectedTanR135 == tanR135);
    CHECK((expectedTanR180) == Catch::Approx(tanR180).epsilon((0.00001f) / 100.0));
    CHECK((expectedTanR360) == Catch::Approx(tanR360).epsilon((0.00001f) / 100.0));
    CHECK(expectedTanR720 == tanR720);
    CHECK(expectedTanR20000 == tanR20000);


    constexpr auto radians = Deg2Rad( 0.001 );
    constexpr auto result1a = Tan( radians );
    auto result1b = std::tan( radians );
    auto result1Diff = result1a - result1b;
    CHECK(result1a == result1b);
    CHECK(result1a == 1.7453292521715489e-05);
    CHECK(result1b == 1.7453292521715489e-05);
}
TEST_CASE("ConstexprMathTests / FloatASinTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = ASin( x );
            return IsSameValue( r, expected );
        };
    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = ASin( x );
            return IsNaN( r );
        };

    // asin( inf ) == NaN
    constexpr auto check1 = CheckIsNaN( C::Infinity );
    CHECK(check1);

    // asin (-inf) == NaN
    constexpr auto check2 = CheckIsNaN( -C::Infinity );
    CHECK(check2);

    // asin (NaN) == NaN
    constexpr auto check3 = CheckIsNaN( C::NaN );
    CHECK(check3);

    // asin (1.1) == NaN
    constexpr auto check4 = CheckIsNaN( 1.1 );
    CHECK(check4);

    // asin (-1.1) == NaN
    constexpr auto check5 = CheckIsNaN( -1.1 );
    CHECK(check5);

    // asin (0) == 0
    constexpr auto check6 = Check( 0., 0. );
    CHECK(check6);

    // asin (-0) == -0
    constexpr auto check7 = Check( -0., -0. );
    CHECK(check7);

    // asin (0.5) == pi/6
    constexpr auto check8 = Check( 0.5, C::Pi/6.f );
    CHECK(check8);

    // asin (-0.5) == -pi/6
    constexpr auto check9 = Check( -0.5, -C::Pi / 6.f );
    CHECK(check9);

    // asin (1.0) == pi/2
    constexpr auto check10 = Check( 1.0, C::Pi / 2.f );
    CHECK(check10);

    // asin (-1.0) == -pi/2
    constexpr auto check11 = Check( -1.0, -C::Pi / 2.f );
    CHECK(check11);

    // asin (0.7) == 0.77539749661075306374035335271498708
    
    constexpr auto check12 = Check( 0.7, 0.775397539f );
    CHECK(check12);
}
TEST_CASE("ConstexprMathTests / DoubleASinTest1", "[math][ConstexprMathTests]")
{
    using ValueType = double;
    using C = Constants<ValueType>;

    constexpr auto Check = []( ValueType x, ValueType expected ) -> bool
        {
            auto r = ASin( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( ValueType x, ValueType expected, ValueType epsilon = std::numeric_limits<ValueType>::epsilon() * static_cast<ValueType>(10) ) -> bool
        {
            auto r = ASin( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( ValueType x ) -> bool
        {
            auto r = ASin( x );
            return IsNaN( r );
        };

    // asin( inf ) == NaN
    constexpr auto check1 = CheckIsNaN( C::Infinity );
    CHECK(check1);

    // asin (-inf) == NaN
    constexpr auto check2 = CheckIsNaN( -C::Infinity );
    CHECK(check2);

    // asin (NaN) == NaN
    constexpr auto check3 = CheckIsNaN( C::NaN );
    CHECK(check3);

    // asin (1.1) == NaN
    constexpr auto check4 = CheckIsNaN( 1.1 );
    CHECK(check4);

    // asin (-1.1) == NaN
    constexpr auto check5 = CheckIsNaN( -1.1 );
    CHECK(check5);

    // asin (0) == 0
    constexpr auto check6 = Check( 0., 0. );
    CHECK(check6);

    // asin (-0) == -0
    constexpr auto check7 = Check( -0., -0. );
    CHECK(check7);

    // asin (0.5) == pi/6

    auto res = ASin( 0.5 );
    constexpr auto check8 = CheckClose( 0.5, C::PiOver6 );
    CHECK(check8);

    // asin (-0.5) == -pi/6
    constexpr auto check9 = CheckClose( -0.5, -C::PiOver6 );
    CHECK(check9);

    // asin (1.0) == pi/2
    constexpr auto check10 = CheckClose( 1.0, C::PiOver2 );
    CHECK(check10);

    // asin (-1.0) == -pi/2
    constexpr auto check11 = CheckClose( -1.0, -C::PiOver2 );
    CHECK(check11);

    // asin (0.7) == 0.77539749661075306374035335271498708
    constexpr auto check12 = Check( 0.7, 0.77539749661075306374035335271498708 );
    CHECK(check12);


}
TEST_CASE("ConstexprMathTests / FloatACosTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = ACos( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = ACos( x );
            return IsNaN( r );
        };

    // acos (inf) == NaN
    constexpr auto check1 = CheckIsNaN( C::Infinity );
    CHECK(check1);

    // acos (-inf) == NaN
    constexpr auto check2 = CheckIsNaN( C::NegativeInfinity );
    CHECK(check2);

    // acos (NaN) == NaN
    constexpr auto check3 = CheckIsNaN( C::NaN );
    CHECK(check3);

    // acos (1.1) == NaN
    constexpr auto check4 = CheckIsNaN( 1.1f );
    CHECK(check4);

    // acos (-1.1) == NaN
    constexpr auto check5 = CheckIsNaN( -1.1f );
    CHECK(check5);

    // acos (0) == pi/2
    constexpr auto check6 = Check( 0.f, C::PiOver2 );
    CHECK(check6);

    // acos (-0) == pi/2
    constexpr auto check7 = Check( -0.f, C::PiOver2 );
    CHECK(check7);

    // acos (1) == 0
    constexpr auto check8 = Check( 1.f, C::Zero );
    CHECK(check8);

    // acos (-1) == pi
    constexpr auto check9 = Check( -1.f, C::Pi );
    CHECK(check9);

    // acos (0.5) == M_PI_6l*2.0
    constexpr auto check10 = Check( 0.5f, 1.04719758f );
    CHECK(check10);

    // acos (-0.5) == M_PI_6l*4.0
    constexpr auto check11 = Check( -0.5f, 2.09439516f );
    CHECK(check11);

    // acos (0.7) == 0.795398831f
    constexpr auto check12 = Check( 0.7f, 0.795398831f );
    CHECK(check12);
}
TEST_CASE("ConstexprMathTests / DoubleACosTest1", "[math][ConstexprMathTests]")
{
    using ValueType = double;
    using C = Constants<ValueType>;

    constexpr auto Check = []( ValueType x, ValueType expected ) -> bool
        {
            auto r = ACos( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( ValueType x, ValueType expected, ValueType epsilon = std::numeric_limits<ValueType>::epsilon( ) * static_cast<ValueType>(10) ) -> bool
        {
            auto r = ACos( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( ValueType x ) -> bool
        {
            auto r = ACos( x );
            return IsNaN( r );
        };

    // acos (inf) == NaN
    constexpr auto check1 = CheckIsNaN( C::Infinity );
    CHECK(check1);

    // acos (-inf) == NaN
    constexpr auto check2 = CheckIsNaN( C::NegativeInfinity );
    CHECK(check2);

    // acos (NaN) == NaN
    constexpr auto check3 = CheckIsNaN( C::NaN );
    CHECK(check3);

    // acos (1.1) == NaN
    constexpr auto check4 = CheckIsNaN( 1.1 );
    CHECK(check4);

    // acos (-1.1) == NaN
    constexpr auto check5 = CheckIsNaN( -1.1 );
    CHECK(check5);

    // acos (0) == pi/2
    constexpr auto check6 = Check( 0., C::PiOver2 );
    CHECK(check6);

    // acos (-0) == pi/2
    constexpr auto check7 = Check( -0., C::PiOver2 );
    CHECK(check7);

    // acos (1) == 0
    constexpr auto check8 = Check( 1., C::Zero );
    CHECK(check8);

    // acos (-1) == pi
    constexpr auto check9 = Check( -1., C::Pi );
    CHECK(check9);

    // acos (0.5) == M_PI_6l*2.0
    constexpr auto check10 = CheckClose( 0.5, C::PiOver6 * 2. );
    CHECK(check10);

    // acos (-0.5) == M_PI_6l*4.0
    constexpr auto check11 = CheckClose( -0.5, C::PiOver6 * 4. );
    CHECK(check11);

    // acos (0.7) == 0.79539883018414355549096833892476432
    constexpr auto check12 = Check( 0.7, 0.79539883018414355549096833892476432 );
    CHECK(check12);


}
TEST_CASE("ConstexprMathTests / FloatATanTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = ATan( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = ATan( x );
            return IsNaN( r );
        };

    // atan (0) == 0
    constexpr auto check1 = Check( 0., 0. );
    CHECK(check1);

    // atan (-0) == -0
    constexpr auto check2 = Check( -0., -0. );
    CHECK(check2);

    // atan (inf) == pi/2
    constexpr auto check3 = Check( C::Infinity, C::PiOver2 );
    CHECK(check3);

    // atan (-inf) == -pi/2
    constexpr auto check4 = Check( -C::Infinity, -C::PiOver2 );
    CHECK(check4);

    // atan (NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN );
    CHECK(check5);

    // atan (1) == pi/4
    constexpr auto check6 = Check( C::One, C::PiOver4 );
    CHECK(check6);

    // atan (-1) == -pi/4
    constexpr auto check7 = Check( -C::One, -C::PiOver4 );
    CHECK(check7);

    // atan (0.7) == 0.610725939f
    constexpr auto check8 = Check( 0.7, 0.610725939f );
    CHECK(check8);
}
TEST_CASE("ConstexprMathTests / DoubleATanTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<double>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = ATan( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = ATan( x );
            return IsNaN( r );
        };

    // atan (0) == 0
    constexpr auto check1 = Check( 0., 0. );
    CHECK(check1);

    // atan (-0) == -0
    constexpr auto check2 = Check( -0., -0. );
    CHECK(check2);

    // atan (inf) == pi/2
    constexpr auto check3 = Check( C::Infinity, C::PiOver2 );
    CHECK(check3);

    // atan (-inf) == -pi/2
    constexpr auto check4 = Check( -C::Infinity, -C::PiOver2 );
    CHECK(check4);

    // atan (NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN );
    CHECK(check5);

    // atan (1) == pi/4
    constexpr auto check6 = Check( C::One, C::PiOver4 );
    CHECK(check6);

    // atan (-1) == -pi/4
    constexpr auto check7 = Check( -C::One, -C::PiOver4 );
    CHECK(check7);

    // atan (0.7) == 0.61072596438920861654375887649023613
    constexpr auto check8 = Check( 0.7, 0.61072596438920861654375887649023613 );
    CHECK(check8);
}
TEST_CASE("ConstexprMathTests / FloatATan2Test1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    constexpr auto Check = []( C::ValueType x, C::ValueType y, C::ValueType expected ) -> bool
        {
            auto r = ATan2( x, y );
            return IsSameValue( r, expected );
        };
    constexpr auto CheckIsNaN = []( C::ValueType x, C::ValueType y ) -> bool
        {
            auto r = ATan2( x, y );
            return IsNaN( r );
        };

    // atan2 (0,x) == 0 for x > 0
    // atan2 (0, 1) == 0
    constexpr auto check1 = Check( 0, 1., 0 );
    CHECK(check1);

    // atan2 (-0,x) == -0 for x > 0
    // atan2 (-0, 1) == -0
    constexpr auto check2 = Check( -0, 1., -0 );
    CHECK(check2);

    // atan2 (0, 0) == 0
    constexpr auto check3 = Check( 0, 0., 0 );
    CHECK(check3);

    // atan2 (-0, 0) == -0
    constexpr auto check4 = Check( -0., 0., -0. );
    CHECK(check4);

    // atan2 (+0,x) == +pi for x < 0
    // atan2 (0, -1) == pi
    constexpr auto check5 = Check( 0., -1., C::Pi );
    CHECK(check5);


    // atan2 (-0,x) == -pi for x < 0
    // atan2 (-0, -1) == -pi
    constexpr auto check6 = Check( -0., -1., -C::Pi );
    CHECK(check6);


    // atan2 (0, -0) == pi
    constexpr auto check7 = Check( 0., -0., C::Pi );
    CHECK(check7);

    // atan2 (-0, -0) == -pi
    constexpr auto check8 = Check( -0., -0., -C::Pi );
    CHECK(check8);

    // atan2 (y,+0) == pi/2 for y > 0
    // atan2 (1, 0) == pi/2
    constexpr auto check9 = Check( 1., 0., C::PiOver2 );
    CHECK(check9);

    // atan2 (y,-0) == pi/2 for y > 0
    // atan2 (1, -0) == pi/2
    constexpr auto check10 = Check( 1., -0., C::PiOver2 );
    CHECK(check10);

    // atan2 (y,+0) == -pi/2 for y < 0
    // atan2 (-1, 0) == -pi/2
    constexpr auto check11 = Check( -1., 0., -C::PiOver2 );
    CHECK(check11);

    // atan2 (y,-0) == -pi/2 for y < 0
    // atan2 (-1, -0) == -pi/2
    constexpr auto check12 = Check( -1., -0., -C::PiOver2 );
    CHECK(check12);

    // atan2 (y,inf) == +0 for finite y > 0
    // atan2 (1, inf) == 0
    constexpr auto check13 = Check( 1., C::Infinity, C::Zero );
    CHECK(check13);

    // atan2 (y,inf) == -0 for finite y < 0
    // atan2 (-1, inf) == -0
    constexpr auto check14 = Check( -1., C::Infinity, -C::Zero );
    CHECK(check14);

    // atan2(+inf, x) == pi/2 for finite x
    // atan2 (inf, -1) == pi/2
    constexpr auto check15 = Check( C::Infinity, -1., C::PiOver2 );
    CHECK(check15);

    // atan2(-inf, x) == -pi/2 for finite x
    // atan2 (-inf, 1) == -pi/2
    constexpr auto check16 = Check( -C::Infinity, 1., -C::PiOver2 );
    CHECK(check16);

    // atan2 (y,-inf) == +pi for finite y > 0
    // atan2 (1, -inf) == pi
    constexpr auto check17 = Check( 1., -C::Infinity, C::Pi );
    CHECK(check17);

    // atan2 (y,-inf) == -pi for finite y < 0
    // atan2 (-1, -inf) == -pi
    constexpr auto check18 = Check( -1., -C::Infinity, -C::Pi );
    CHECK(check18);

    // atan2 (inf, inf) == pi/4
    constexpr auto check19 = Check( C::Infinity, C::Infinity, C::PiOver4 );
    CHECK(check19);

    // atan2 (-inf, inf) == -pi/4
    constexpr auto check20 = Check( -C::Infinity, C::Infinity, -C::PiOver4 );
    CHECK(check20);

    // atan2 (inf, -inf) == 3/4 pi
    constexpr auto check21 = Check( C::Infinity, -C::Infinity, 3.*C::PiOver4 );
    CHECK(check21);


    // atan2 (-inf, -inf) == -3/4 pi
    constexpr auto check22 = Check( -C::Infinity, -C::Infinity, -3. * C::PiOver4 );
    CHECK(check22);

    // atan2 (NaN, NaN) == NaN
    constexpr auto check23 = CheckIsNaN( C::NaN, C::NaN );
    CHECK(check23);

    // atan2 (0.7, 1) == 0.610725939f
    constexpr auto check24 = Check( 0.7f, 1.f, 0.610725939f );
    CHECK(check24);

    // atan2 (-0.7, 1.0) == -0.610725939f
    constexpr auto check25 = Check( -0.7f, 1.f, -0.610725939f );
    CHECK(check25);

    // atan2 (0.7, -1.0) == 2.53086662f
    constexpr auto check26 = Check( 0.7f, -1.f, 2.53086662f );
    CHECK(check26);

    // atan2 (-0.7, -1.0) == -2.53086662f
    constexpr auto check27 = Check( -0.7f, -1.f, -2.53086662f );
    CHECK(check27);

    // atan2 (0.4, 0.0003) == 1.57004631
    constexpr auto check28 = Check( 0.4f, 0.0003f, 1.57004631f );
    CHECK(check28);

    // atan2 (1.4, -0.93) == 2.15714884f
    constexpr auto check29 = Check( 1.4f, -0.93f, 2.15714884f );
    CHECK(check29);
}
TEST_CASE("ConstexprMathTests / DoubleATan2Test1", "[math][ConstexprMathTests]")
{
    using ValueType = double;
    using C = Constants<ValueType>;

    constexpr auto Check = []( ValueType x, ValueType y, ValueType expected ) -> bool
        {
            auto r = ATan2( x, y );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( ValueType x, ValueType y, ValueType expected, ValueType epsilon = std::numeric_limits<ValueType>::epsilon( ) * static_cast<ValueType>(10) ) -> bool
        {
            auto r = ATan2( x, y );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( ValueType x, ValueType y ) -> bool
        {
            auto r = ATan2( x, y );
            return IsNaN( r );
        };

    // atan2 (0,x) == 0 for x > 0
    // atan2 (0, 1) == 0
    constexpr auto check1 = Check( 0, 1., 0 );
    CHECK(check1);

    // atan2 (-0,x) == -0 for x > 0
    // atan2 (-0, 1) == -0
    constexpr auto check2 = Check( -0, 1., -0 );
    CHECK(check2);

    // atan2 (0, 0) == 0
    constexpr auto check3 = Check( 0, 0., 0 );
    CHECK(check3);

    // atan2 (-0, 0) == -0
    constexpr auto check4 = Check( -0., 0., -0. );
    CHECK(check4);

    // atan2 (+0,x) == +pi for x < 0
    // atan2 (0, -1) == pi
    constexpr auto check5 = Check( 0., -1., C::Pi );
    CHECK(check5);


    // atan2 (-0,x) == -pi for x < 0
    // atan2 (-0, -1) == -pi
    constexpr auto check6 = Check( -0., -1., -C::Pi );
    CHECK(check6);


    // atan2 (0, -0) == pi
    constexpr auto check7 = Check( 0., -0., C::Pi );
    CHECK(check7);

    // atan2 (-0, -0) == -pi
    constexpr auto check8 = Check( -0., -0., -C::Pi );
    CHECK(check8);

    // atan2 (y,+0) == pi/2 for y > 0
    // atan2 (1, 0) == pi/2
    constexpr auto check9 = Check( 1., 0., C::PiOver2 );
    CHECK(check9);

    // atan2 (y,-0) == pi/2 for y > 0
    // atan2 (1, -0) == pi/2
    constexpr auto check10 = Check( 1., -0., C::PiOver2 );
    CHECK(check10);

    // atan2 (y,+0) == -pi/2 for y < 0
    // atan2 (-1, 0) == -pi/2
    constexpr auto check11 = Check( -1., 0., -C::PiOver2 );
    CHECK(check11);

    // atan2 (y,-0) == -pi/2 for y < 0
    // atan2 (-1, -0) == -pi/2
    constexpr auto check12 = Check( -1., -0., -C::PiOver2 );
    CHECK(check12);

    // atan2 (y,inf) == +0 for finite y > 0
    // atan2 (1, inf) == 0
    constexpr auto check13 = Check( 1., C::Infinity, C::Zero );
    CHECK(check13);

    // atan2 (y,inf) == -0 for finite y < 0
    // atan2 (-1, inf) == -0
    constexpr auto check14 = Check( -1., C::Infinity, -C::Zero );
    CHECK(check14);

    // atan2(+inf, x) == pi/2 for finite x
    // atan2 (inf, -1) == pi/2
    constexpr auto check15 = Check( C::Infinity, -1., C::PiOver2 );
    CHECK(check15);

    // atan2(-inf, x) == -pi/2 for finite x
    // atan2 (-inf, 1) == -pi/2
    constexpr auto check16 = Check( -C::Infinity, 1., -C::PiOver2 );
    CHECK(check16);

    // atan2 (y,-inf) == +pi for finite y > 0
    // atan2 (1, -inf) == pi
    constexpr auto check17 = Check( 1., -C::Infinity, C::Pi );
    CHECK(check17);

    // atan2 (y,-inf) == -pi for finite y < 0
    // atan2 (-1, -inf) == -pi
    constexpr auto check18 = Check( -1., -C::Infinity, -C::Pi );
    CHECK(check18);

    // atan2 (inf, inf) == pi/4
    constexpr auto check19 = Check( C::Infinity, C::Infinity, C::PiOver4 );
    CHECK(check19);

    // atan2 (-inf, inf) == -pi/4
    constexpr auto check20 = Check( -C::Infinity, C::Infinity, -C::PiOver4 );
    CHECK(check20);

    // atan2 (inf, -inf) == 3/4 pi
    constexpr auto check21 = Check( C::Infinity, -C::Infinity, 3. * C::PiOver4 );
    CHECK(check21);


    // atan2 (-inf, -inf) == -3/4 pi
    constexpr auto check22 = Check( -C::Infinity, -C::Infinity, -3. * C::PiOver4 );
    CHECK(check22);

    // atan2 (NaN, NaN) == NaN
    constexpr auto check23 = CheckIsNaN( C::NaN, C::NaN );
    CHECK(check23);

    // atan2 (0.7, 1) == 0.61072596438920861654375887649023613
    constexpr auto check24 = Check( 0.7, 1, 0.61072596438920861654375887649023613 );
    CHECK(check24);

    // atan2 (-0.7, 1.0) == -0.61072596438920861654375887649023613
    constexpr auto check25 = Check( -0.7, 1, -0.61072596438920861654375887649023613 );
    CHECK(check25);

    // atan2 (0.7, -1.0) == 2.530866689200584621918884506789267
    constexpr auto check26 = Check( 0.7, -1, 2.530866689200584621918884506789267 );
    CHECK(check26);

    // atan2 (-0.7, -1.0) == -2.530866689200584621918884506789267
    constexpr auto check27 = Check( -0.7, -1, -2.530866689200584621918884506789267 );
    CHECK(check27);

    // atan2 (0.4, 0.0003) == 1.5700463269355215717704032607580829
    constexpr auto check28 = Check( 0.4, 0.0003, 1.5700463269355215717704032607580829 );
    CHECK(check28);

    // atan2 (1.4, -0.93) == 2.1571487668237843754887415992772736
    constexpr auto check29 = Check( 1.4, -0.93, 2.1571487668237843754887415992772736 );
    CHECK(check29);
}
TEST_CASE("ConstexprMathTests / FloatSinCosTest1", "[math][ConstexprMathTests]")
{
    using ValueType = float;
    using C = Constants<ValueType>;

    constexpr auto Check = []( ValueType x, ValueType expectedSine, ValueType expectedCosine ) -> bool
        {
            ValueType sine, cosine;
            SinCos( x, &sine, &cosine );
            return IsSameValue( sine, expectedSine ) && IsSameValue( cosine, expectedCosine );
        };

    constexpr auto CheckClose = []( ValueType x, ValueType expectedSine, ValueType expectedCosine, ValueType epsilon = std::numeric_limits<ValueType>::epsilon( ) * static_cast<ValueType>(10) ) -> bool
        {
            ValueType sine, cosine;
            SinCos( x, &sine, &cosine );
            return AreNearlyEqual( sine, expectedSine, epsilon ) && AreNearlyEqual( cosine, expectedCosine, epsilon );
        };

    constexpr auto CheckIsNaN = []( ValueType x ) -> bool
        {
            ValueType sine, cosine;
            SinCos( x, &sine, &cosine );
            return IsNaN( sine ) && IsNaN( cosine );
        };

    constexpr auto check1 = Check( 0, 0, 1 );
    CHECK(check1);

    constexpr auto check2 = Check( -0., -0., 1 );
    CHECK(check2);


    constexpr auto check3 = CheckIsNaN( C::Infinity );
    CHECK(check3);

    constexpr auto check4 = CheckIsNaN( C::NegativeInfinity );
    CHECK(check4);

    constexpr auto check5 = CheckIsNaN( C::NaN );
    CHECK(check5);

    constexpr auto check6 = CheckClose( C::PiOver2, 1., 0. );
    CHECK(check6);

    constexpr auto check7 = Check( C::PiOver6, 0.5, 0.86602540378443864676372317075293616f );
    CHECK(check7);

    constexpr auto check8 = CheckClose( 2* C::PiOver6, 0.86602540378443864676372317075293616f, 0.5f );
    CHECK(check8);

    constexpr auto check9 = Check( 0.7, 0.64421768723769105367261435139872014f, 0.76484218728448842625585999019186495f );
    CHECK(check9);

}
TEST_CASE("ConstexprMathTests / DoubleSinCosTest1", "[math][ConstexprMathTests]")
{
    using ValueType = double;
    using C = Constants<ValueType>;

    constexpr auto Check = []( ValueType x, ValueType expectedSine, ValueType expectedCosine ) -> bool
        {
            ValueType sine, cosine;
            SinCos( x, &sine, &cosine );
            return IsSameValue( sine, expectedSine ) && IsSameValue( cosine, expectedCosine );
        };

    constexpr auto CheckClose = []( ValueType x, ValueType expectedSine, ValueType expectedCosine, ValueType epsilon = std::numeric_limits<ValueType>::epsilon( ) * static_cast<ValueType>(10) ) -> bool
        {
            ValueType sine, cosine;
            SinCos( x, &sine, &cosine );
            return AreNearlyEqual( sine, expectedSine, epsilon ) && AreNearlyEqual( cosine, expectedCosine, epsilon );
        };

    constexpr auto CheckIsNaN = []( ValueType x ) -> bool
        {
            ValueType sine, cosine;
            SinCos( x, &sine, &cosine );
            return IsNaN( sine ) && IsNaN( cosine );
        };

    constexpr auto check1 = Check( 0, 0, 1 );
    CHECK(check1);

    constexpr auto check2 = Check( -0., -0., 1 );
    CHECK(check2);


    constexpr auto check3 = CheckIsNaN( C::Infinity );
    CHECK(check3);

    constexpr auto check4 = CheckIsNaN( C::NegativeInfinity );
    CHECK(check4);

    constexpr auto check5 = CheckIsNaN( C::NaN );
    CHECK(check5);

    constexpr auto check6 = CheckClose( C::PiOver2, 1., 0. );
    CHECK(check6);

    constexpr auto check7 = CheckClose( C::PiOver6, 0.5, 0.86602540378443864676372317075293616 );
    CHECK(check7);

    constexpr auto check8 = CheckClose( 2 * C::PiOver6, 0.86602540378443864676372317075293616, 0.5 );
    CHECK(check8);

    constexpr auto check9 = CheckClose( 0.7, 0.64421768723769105367261435139872014, 0.76484218728448842625585999019186495 );
    CHECK(check9);

}
TEST_CASE("ConstexprMathTests / FloatSinHTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = SinH( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = SinH( x );
            return IsNaN( r );
        };

    // sinh (0) == 0
    constexpr auto check1 = Check( 0., 0. );
    CHECK(check1);

    // sinh (-0) == -0
    constexpr auto check2 = Check( -0., -0. );
    CHECK(check2);

    // sinh (inf) == inf
    constexpr auto check3 = Check( C::Infinity, C::Infinity );
    CHECK(check3);

    // sinh (-inf) == -inf
    constexpr auto check4 = Check( -C::Infinity, -C::Infinity );
    CHECK(check4);

    // sinh (NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN );
    CHECK(check5);

    // sinh (0.7) == 0.758583665f
    constexpr auto check6 = Check( 0.7f, 0.758583665f );
    CHECK(check6);

}
TEST_CASE("ConstexprMathTests / DoubleSinHTest1", "[math][ConstexprMathTests]")
{
    using ValueType = double;
    using C = Constants<ValueType>;

    constexpr auto Check = []( ValueType x, ValueType expected ) -> bool
        {
            auto r = SinH( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( ValueType x, ValueType expected, ValueType epsilon = std::numeric_limits<ValueType>::epsilon( ) * static_cast<ValueType>(10) ) -> bool
        {
            auto r = SinH( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( ValueType x ) -> bool
        {
            auto r = SinH( x );
            return IsNaN( r );
        };

    // sinh (0) == 0
    constexpr auto check1 = Check( 0., 0. );
    CHECK(check1);

    // sinh (-0) == -0
    constexpr auto check2 = Check( -0., -0. );
    CHECK(check2);

    // sinh (inf) == inf
    constexpr auto check3 = Check( C::Infinity, C::Infinity );
    CHECK(check3);

    // sinh (-inf) == -inf
    constexpr auto check4 = Check( -C::Infinity, -C::Infinity );
    CHECK(check4);

    // sinh (NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN );
    CHECK(check5);

    // sinh (0.7) == 0.75858370183953350346
    constexpr auto check6 = CheckClose( 0.7, 0.75858370183953350346 );
    CHECK(check6);

}
TEST_CASE("ConstexprMathTests / FloatASinHTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = ASinH( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = ASinH( x );
            return IsNaN( r );
        };

    // asinh (0) == 0
    constexpr auto check1 = Check( 0., 0. );
    CHECK(check1);

    // asinh (-0) == -0
    constexpr auto check2 = Check( -0., -0. );
    CHECK(check2);

    // asinh (inf) == inf
    constexpr auto check3 = Check( C::Infinity, C::Infinity );
    CHECK(check3);

    // asinh (-inf) == -inf
    constexpr auto check4 = Check( -C::Infinity, -C::Infinity );
    CHECK(check4);

    // asinh (NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN );
    CHECK(check5);

    // asinh (0.7) == 0.652666569f
    constexpr auto check6 = Check( 0.7f, 0.652666569f );
    CHECK(check6);
}
TEST_CASE("ConstexprMathTests / DoubleASinHTest1", "[math][ConstexprMathTests]")
{
    using ValueType = double;
    using C = Constants<ValueType>;

    constexpr auto Check = []( ValueType x, ValueType expected ) -> bool
        {
            auto r = ASinH( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( ValueType x, ValueType expected, ValueType epsilon = std::numeric_limits<ValueType>::epsilon( ) * static_cast<ValueType>(10) ) -> bool
        {
            auto r = ASinH( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( ValueType x ) -> bool
        {
            auto r = ASinH( x );
            return IsNaN( r );
        };

    // asinh (0) == 0
    constexpr auto check1 = Check( 0., 0. );
    CHECK(check1);

    // asinh (-0) == -0
    constexpr auto check2 = Check( -0., -0. );
    CHECK(check2);

    // asinh (inf) == inf
    constexpr auto check3 = Check( C::Infinity, C::Infinity );
    CHECK(check3);

    // asinh (-inf) == -inf
    constexpr auto check4 = Check( -C::Infinity, -C::Infinity );
    CHECK(check4);

    // asinh (NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN );
    CHECK(check5);

    // asinh (0.7) == 0.652666566082355786
    constexpr auto check6 = Check( 0.7, 0.652666566082355786 );
    CHECK(check6);
}
TEST_CASE("ConstexprMathTests / FloatCosHTest1", "[math][ConstexprMathTests]")
{
    using C = Constants<float>;

    constexpr auto Check = []( C::ValueType x, C::ValueType expected ) -> bool
        {
            auto r = CosH( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( C::ValueType x ) -> bool
        {
            auto r = CosH( x );
            return IsNaN( r );
        };

    // cosh (0) == 1
    constexpr auto check1 = Check( 0.f, 1.f );
    CHECK(check1);

    // cosh (-0) == 1
    constexpr auto check2 = Check( -0.f, 1.f );
    CHECK(check2);

    // cosh (inf) == inf
    constexpr auto check3 = Check( C::Infinity, C::Infinity );
    CHECK(check3);

    // cosh (-inf) == inf
    constexpr auto check4 = Check( -C::Infinity, C::Infinity );
    CHECK(check4);

    // cosh (NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN );
    CHECK(check5);

    // cosh (0.7) == 1.25516903f
    constexpr auto check6 = Check( 0.7f, 1.25516903f );
    CHECK(check6);

}
TEST_CASE("ConstexprMathTests / DoubleCosHTest1", "[math][ConstexprMathTests]")
{
    using ValueType = double;
    using C = Constants<ValueType>;

    constexpr auto Check = []( ValueType x, ValueType expected ) -> bool
        {
            auto r = CosH( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( ValueType x, ValueType expected, ValueType epsilon = std::numeric_limits<ValueType>::epsilon( ) * static_cast<ValueType>(10) ) -> bool
        {
            auto r = CosH( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( ValueType x ) -> bool
        {
            auto r = CosH( x );
            return IsNaN( r );
        };

    // cosh (0) == 1
    constexpr auto check1 = Check( 0., 1. );
    CHECK(check1);

    // cosh (-0) == 1
    constexpr auto check2 = Check( -0., 1. );
    CHECK(check2);

    // cosh (inf) == inf
    constexpr auto check3 = Check( C::Infinity, C::Infinity );
    CHECK(check3);

    // cosh (-inf) == inf
    constexpr auto check4 = Check( -C::Infinity, C::Infinity );
    CHECK(check4);

    // cosh (NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN );
    CHECK(check5);

    // cosh (0.7) == 1.255169005630943018
    constexpr auto check6 = Check( 0.7, 1.255169005630943018 );
    CHECK(check6);

}
TEST_CASE("ConstexprMathTests / FloatACosHTest1", "[math][ConstexprMathTests]")
{
    using ValueType = float;
    using C = Constants<ValueType>;

    constexpr auto Check = []( ValueType x, ValueType expected ) -> bool
        {
            auto r = ACosH( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( ValueType x ) -> bool
        {
            auto r = ACosH( x );
            return IsNaN( r );
        };

    // acosh (inf) == inf
    constexpr auto check1 = Check( C::Infinity, C::Infinity );
    CHECK(check1);

    // acosh (-inf) == NaN
    constexpr auto check2 = CheckIsNaN( -C::Infinity );
    CHECK(check2);

    // acosh (-1.1) == NaN
    constexpr auto check3 = CheckIsNaN( -1.1 );
    CHECK(check3);

    // acosh (1) == 0
    constexpr auto check4 = Check( C::One, C::Zero );
    CHECK(check4);

    // acosh (7) == 2.63391590f
    constexpr auto check5 = Check( 7.f, 2.63391590f );
    CHECK(check5);

}
TEST_CASE("ConstexprMathTests / DoubleACosHTest1", "[math][ConstexprMathTests]")
{
    using ValueType = double;
    using C = Constants<ValueType>;

    constexpr auto Check = []( ValueType x, ValueType expected ) -> bool
        {
            auto r = ACosH( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( ValueType x, ValueType expected, ValueType epsilon = std::numeric_limits<ValueType>::epsilon( ) * static_cast<ValueType>(10) ) -> bool
        {
            auto r = ACosH( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( ValueType x ) -> bool
        {
            auto r = ACosH( x );
            return IsNaN( r );
        };

    // acosh (inf) == inf
    constexpr auto check1 = Check( C::Infinity, C::Infinity );
    CHECK(check1);

    // acosh (-inf) == NaN
    constexpr auto check2 = CheckIsNaN( -C::Infinity );
    CHECK(check2);

    // acosh (-1.1) == NaN
    constexpr auto check3 = CheckIsNaN( -1.1 );
    CHECK(check3);

    // acosh (1) == 0
    constexpr auto check4 = Check( C::One, C::Zero );
    CHECK(check4);

    // acosh (7) == 2.633915793849633417250092694615937
    constexpr auto check5 = Check( 7., 2.633915793849633417250092694615937 );
    CHECK(check5);

}
TEST_CASE("ConstexprMathTests / FloatTanHTest1", "[math][ConstexprMathTests]")
{
    using ValueType = float;
    using C = Constants<ValueType>;

    constexpr auto Check = []( ValueType x, ValueType expected ) -> bool
        {
            auto r = TanH( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( ValueType x ) -> bool
        {
            auto r = TanH( x );
            return IsNaN( r );
        };

    // tanh (0) == 0
    constexpr auto check1 = Check( C::Zero, C::Zero );
    CHECK(check1);

    // tanh (-0) == -0
    constexpr auto check2 = Check( -C::Zero, -C::Zero );
    CHECK(check2);

    // tanh (inf) == 1
    constexpr auto check3 = Check( C::Infinity, C::One );
    CHECK(check3);

    // tanh (NaN) == NaN
    constexpr auto check4 = CheckIsNaN( C::NaN );
    CHECK(check4);

    // tanh (0.7) == 0.604367733f
    constexpr auto check5 = Check( 0.7f, 0.604367733f );
    CHECK(check5);

    // tanh (-0.7) == -0.604367733f
    constexpr auto check6 = Check( -0.7f, -0.604367733f );
    CHECK(check6);

    // tanh (1.0) == 0.761594176f
    constexpr auto check7 = Check( 1.f, 0.761594176f );
    CHECK(check7);

    // tanh (-1.0) == -0.761594176f
    constexpr auto check8 = Check( -1., -0.761594176f );
    CHECK(check8);

    // tanh (6.93889390e-18) == 6.93889390e-18
    constexpr auto check9 = Check( 6.93889390e-18f, 6.93889390e-18f );
    CHECK(check9);
}
TEST_CASE("ConstexprMathTests / DoubleTanHTest1", "[math][ConstexprMathTests]")
{
    using ValueType = double;
    using C = Constants<ValueType>;

    constexpr auto Check = []( ValueType x, ValueType expected ) -> bool
        {
            auto r = TanH( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( ValueType x, ValueType expected, ValueType epsilon = std::numeric_limits<ValueType>::epsilon( ) * static_cast<ValueType>(10) ) -> bool
        {
            auto r = TanH( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( ValueType x ) -> bool
        {
            auto r = TanH( x );
            return IsNaN( r );
        };

    // tanh (0) == 0
    constexpr auto check1 = Check( C::Zero, C::Zero );
    CHECK(check1);

    // tanh (-0) == -0
    constexpr auto check2 = Check( -C::Zero, -C::Zero );
    CHECK(check2);

    // tanh (inf) == 1
    constexpr auto check3 = Check( C::Infinity, C::One );
    CHECK(check3);

    // tanh (NaN) == NaN
    constexpr auto check4 = CheckIsNaN( C::NaN );
    CHECK(check4);

    // tanh (0.7) == 0.60436777711716349631
    constexpr auto check5 = CheckClose( 0.7, 0.60436777711716349631 );
    CHECK(check5);

    // tanh (-0.7) == -0.60436777711716349631
    constexpr auto check6 = CheckClose( -0.7, -0.60436777711716349631 );
    CHECK(check6);

    // tanh (1.0) == 0.7615941559557648881194582826047935904
    constexpr auto check7 = Check( 1., 0.7615941559557648881194582826047935904 );
    CHECK(check7);

    // tanh (-1.0) == -0.7615941559557648881194582826047935904
    constexpr auto check8 = Check( -1., -0.7615941559557648881194582826047935904 );
    CHECK(check8);

    // tanh (6.938893903907228377647697925567626953125e-18) == 6.938893903907228377647697925567626953125e-18
    constexpr auto check9 = Check( 6.938893903907228377647697925567626953125e-18, 6.938893903907228377647697925567626953125e-18 );
    CHECK(check9);
}
TEST_CASE("ConstexprMathTests / FloatATanHTest1", "[math][ConstexprMathTests]")
{
    using ValueType = float;
    using C = Constants<ValueType>;

    constexpr auto Check = []( ValueType x, ValueType expected ) -> bool
        {
            auto r = ATanH( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( ValueType x ) -> bool
        {
            auto r = ATanH( x );
            return IsNaN( r );
        };

    // atanh (0) == 0
    constexpr auto check1 = Check( 0., 0. );
    CHECK(check1);

    // atanh (-0) == -0
    constexpr auto check2 = Check( -0., -0. );
    CHECK(check2);

    // atanh (1) == inf
    constexpr auto check3 = Check( 1., C::Infinity );
    CHECK(check3);

    // atanh (-1) == -inf
    constexpr auto check4 = Check( -1., -C::Infinity );
    CHECK(check4);

    // atanh (NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN );
    CHECK(check5);
    // atanh (1.1) == NaN
    constexpr auto check6 = CheckIsNaN( 1.1 );
    CHECK(check6);

    // atanh (-1.1) == NaN
    constexpr auto check7 = CheckIsNaN( -1.1 );
    CHECK(check7);

    // atanh (0.7) == 0.867300510f
    constexpr auto check8 = Check( 0.7, 0.867300510f );
    CHECK(check8);
}
TEST_CASE("ConstexprMathTests / DoubleATanHTest1", "[math][ConstexprMathTests]")
{
    using ValueType = double;   
    using C = Constants<ValueType>;

    constexpr auto Check = []( ValueType x, ValueType expected ) -> bool
        {
            auto r = ATanH( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( ValueType x ) -> bool
        {
            auto r = ATanH( x );
            return IsNaN( r );
        };

    // atanh (0) == 0
    constexpr auto check1 = Check( 0., 0. );
    CHECK(check1);

    // atanh (-0) == -0
    constexpr auto check2 = Check( -0., -0. );
    CHECK(check2);

    // atanh (1) == inf
    constexpr auto check3 = Check( 1., C::Infinity );
    CHECK(check3);

    // atanh (-1) == -inf
    constexpr auto check4 = Check( -1., -C::Infinity );
    CHECK(check4);

    // atanh (NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN );
    CHECK(check5);
    // atanh (1.1) == NaN
    constexpr auto check6 = CheckIsNaN( 1.1 );
    CHECK(check6);

    // atanh (-1.1) == NaN
    constexpr auto check7 = CheckIsNaN( -1.1 );
    CHECK(check7);

    // atanh (0.7) == 0.86730052769405308
    constexpr auto check8 = Check( 0.7, 0.86730052769405308 );
    CHECK(check8);
}
TEST_CASE("ConstexprMathTests / FloatJ0Test1", "[math][ConstexprMathTests]")
{
    using ValueType = float;
    using C = Constants<ValueType>;

    constexpr auto Check = []( ValueType x, ValueType expected ) -> bool
        {
            auto r = J0( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( ValueType x ) -> bool
        {
            auto r = J0( x );
            return IsNaN( r );
        };

    // j0 (NaN) == NaN
    constexpr auto check1 = CheckIsNaN( C::NaN );
    CHECK(check1);

    // j0 (inf) == 0
    constexpr auto check2 = Check( C::Infinity, 0. );
    CHECK(check2);

    // j0 (-1.0) == 0.765197694f
    constexpr auto check3 = Check( -C::One, 0.765197694f );
    CHECK(check3);

    // j0 (0.0) == 1.0
    constexpr auto check4 = Check( C::Zero, 1.0 );
    CHECK(check4);

    // j0( 0.1 ) == 0.997501552f
    constexpr auto check5 = Check( 0.1, 0.997501552f );
    CHECK(check5);
    
    // j0( 0.7 ) == 0.881200910f
    constexpr auto check6 = Check( 0.7, 0.881200910f );
    CHECK(check6);

    // j0( 1.0 ) == 0.765197694f
    constexpr auto check7 = Check( C::One, 0.765197694f );
    CHECK(check7);

    // j0( 1.5 ) == 0.511827648f
    constexpr auto check8 = Check( 1.5, 0.511827648f );
    CHECK(check8);

    // j0( 2.0 ) == 0.223890811f
    constexpr auto check9 = Check( 2.0, 0.223890811f );
    CHECK(check9);

    // j0( 8.0 ) == 0.171650827f
    constexpr auto check10 = Check( 8.0, 0.171650827f );
    CHECK(check10);

    // j0 (10.0) == -0.245935783f
    constexpr auto check11 = Check( 10.0, -0.245935783f );
    CHECK(check11);
}
TEST_CASE("ConstexprMathTests / DoubleJ0Test1", "[math][ConstexprMathTests]")
{
    using ValueType = double;
    using C = Constants<ValueType>;

    constexpr auto Check = []( ValueType x, ValueType expected ) -> bool
        {
            auto r = J0( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( ValueType x, ValueType expected, ValueType epsilon = std::numeric_limits<ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = J0( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( ValueType x ) -> bool
        {
            auto r = J0( x );
            return IsNaN( r );
        };

    // j0 (NaN) == NaN
    constexpr auto check1 = CheckIsNaN( C::NaN );
    CHECK(check1);

    // j0 (inf) == 0
    constexpr auto check2 = Check( C::Infinity, 0. );
    CHECK(check2);

    // j0 (-1.0) == 0.76519768655796655145
    constexpr auto check3 = Check( -C::One, 0.76519768655796655145 );
    CHECK(check3);

    // j0 (0.0) == 1.0
    constexpr auto check4 = Check( C::Zero, 1.0 );
    CHECK(check4);

    // j0( 0.1 ) == 0.99750156206604003228
    constexpr auto check5 = Check( 0.1, 0.99750156206604003228 );
    CHECK(check5);

    // j0( 0.7 ) == 0.88120088860740528084
    constexpr auto check6 = Check( 0.7, 0.88120088860740528084 );
    CHECK(check6);

    // j0( 1.0 ) == 0.76519768655796655145
    constexpr auto check7 = Check( C::One, 0.76519768655796655145 );
    CHECK(check7);

    // j0( 1.5 ) == 0.51182767173591812875
    constexpr auto check8 = Check( 1.5, 0.51182767173591812875 );
    CHECK(check8);

    // j0( 2.0 ) == 0.22389077914123566805
    constexpr auto check9 = Check( 2.0, 0.22389077914123566805 );
    CHECK(check9);

    // j0( 8.0 ) == 0.17165080713755390609
    constexpr auto check10 = Check( 8.0, 0.17165080713755390609 );
    CHECK(check10);

    // j0 (10.0) == -0.24593576445134833520
    constexpr auto check11 = CheckClose( 10.0, -0.24593576445134833520 );
    CHECK(check11);
}
TEST_CASE("ConstexprMathTests / FloatJ1Test1", "[math][ConstexprMathTests]")
{
    using ValueType = float;
    using C = Constants<ValueType>;

    constexpr auto Check = []( ValueType x, ValueType expected ) -> bool
        {
            auto r = J1( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( ValueType x, ValueType expected, ValueType epsilon = std::numeric_limits<ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = J1( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( ValueType x ) -> bool
        {
            auto r = J1( x );
            return IsNaN( r );
        };

    // j1 (NaN) == NaN
    constexpr auto check1 = CheckIsNaN( C::NaN );
    CHECK(check1);

    // j1 (inf) == 0
    constexpr auto check2 = Check( C::Infinity, 0. );
    CHECK(check2);

    // j1 (-1.0) == -0.44005058574493351596
    constexpr auto check3 = Check( -1.0, -0.44005058574493351596 );
    CHECK(check3);
    
    // j1 (0.0) == 0.0
    constexpr auto check4 = Check( 0.0, 0.0 );
    CHECK(check4);

    // j1 (0.1) == 0.049937526036241997556
    constexpr auto check5 = Check( 0.1, 0.049937526036241997556 );
    CHECK(check5);

    // j1 (0.7) == 0.32899574154005894785
    constexpr auto check6 = Check( 0.7, 0.32899574154005894785 );
    CHECK(check6);

    // j1 (1.0) == 0.44005058574493351596
    constexpr auto check7 = Check( 1.0, 0.44005058574493351596 );
    CHECK(check7);

    // j1 (1.5) == 0.55793650791009964199
    constexpr auto check8 = Check( 1.5, 0.55793650791009964199 );
    CHECK(check8);

    // j1 (2.0) == 0.57672480775687338720
    constexpr auto check9 = Check( 2.0, 0.57672480775687338720 );
    CHECK(check9);

    // j1 (8.0) == 0.23463634685391462438
    constexpr auto check10 = Check( 8.0, 0.23463634685391462438 );
    CHECK(check10);

    // j1 (10.0) == 0.043472746168861436670
    constexpr auto check11 = CheckClose( 10.0, 0.043472746168861436670 );
    CHECK(check11);

}
TEST_CASE("ConstexprMathTests / DoubleJ1Test1", "[math][ConstexprMathTests]")
{
    using ValueType = double;
    using C = Constants<ValueType>;

    constexpr auto Check = []( ValueType x, ValueType expected ) -> bool
        {
            auto r = J1( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( ValueType x, ValueType expected, ValueType epsilon = std::numeric_limits<ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = J1( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( ValueType x ) -> bool
        {
            auto r = J1( x );
            return IsNaN( r );
        };

    // j1 (NaN) == NaN
    constexpr auto check1 = CheckIsNaN( C::NaN );
    CHECK(check1);

    // j1 (inf) == 0
    constexpr auto check2 = Check( C::Infinity, 0. );
    CHECK(check2);

    // j1 (-1.0) == -0.44005058574493351596
    constexpr auto check3 = Check( -1.0, -0.44005058574493351596 );
    CHECK(check3);

    // j1 (0.0) == 0.0
    constexpr auto check4 = Check( 0.0, 0.0 );
    CHECK(check4);

    // j1 (0.1) == 0.049937526036241997556
    constexpr auto check5 = Check( 0.1, 0.049937526036241997556 );
    CHECK(check5);

    // j1 (0.7) == 0.32899574154005894785
    constexpr auto check6 = Check( 0.7, 0.32899574154005894785 );
    CHECK(check6);

    // j1 (1.0) == 0.44005058574493351596
    constexpr auto check7 = Check( 1.0, 0.44005058574493351596 );
    CHECK(check7);

    // j1 (1.5) == 0.55793650791009964199
    constexpr auto check8 = Check( 1.5, 0.55793650791009964199 );
    CHECK(check8);

    // j1 (2.0) == 0.57672480775687338720
    constexpr auto check9 = CheckClose( 2.0, 0.57672480775687338720 );
    CHECK(check9);

    // j1 (8.0) == 0.23463634685391462438
    constexpr auto check10 = CheckClose( 8.0, 0.23463634685391462438 );
    CHECK(check10);

    // j1 (10.0) == 0.043472746168861436670
    constexpr auto check11 = Check( 10.0, 0.043472746168861436670 );
    CHECK(check11);

}
TEST_CASE("ConstexprMathTests / FloatJNTest1", "[math][ConstexprMathTests]")
{
    using ValueType = float;
    using C = Constants<ValueType>;

    constexpr auto Check = []( int n, ValueType x, ValueType expected ) -> bool
        {
            auto r = JN( n, x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( int n, ValueType x, ValueType expected, ValueType epsilon = std::numeric_limits<ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = JN( n, x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( int n, ValueType x ) -> bool
        {
            auto r = JN( n, x );
            return IsNaN( r );
        };

    // jn (0, x) == j0 (x)  
    // jn (0, NaN) == NaN
    constexpr auto check1 = CheckIsNaN( 0, C::NaN );
    CHECK(check1);

    // jn (0, inf) == 0
    constexpr auto check2 = Check( 0, C::Infinity, 0. );
    CHECK(check2);

    // jn (0, -1.0) == 0.76519768655796655145
    constexpr auto check3 = Check( 0, -1.0, 0.76519768655796655145 );
    CHECK(check3);

    // jn (0, 0.0) == 1.0
    constexpr auto check4 = Check( 0, 0.0, 1.0 );
    CHECK(check4);

    // jn (0, 0.1) == 0.99750156206604003228
    constexpr auto check5 = Check( 0, 0.1, 0.99750156206604003228 );
    CHECK(check5);

    // jn (0, 0.7) == 0.88120088860740528084
    constexpr auto check6 = Check( 0, 0.7, 0.88120088860740528084 );
    CHECK(check6);

    // jn (0, 1.0) == 0.76519768655796655145
    constexpr auto check7 = Check( 0, 1.0, 0.76519768655796655145 );
    CHECK(check7);

    // jn (0, 1.5) == 0.51182767173591812875
    constexpr auto check8 = Check( 0, 1.5, 0.51182767173591812875 );
    CHECK(check8);

    // jn (0, 2.0) == 0.22389077914123566805
    constexpr auto check9 = CheckClose( 0, 2.0, 0.22389077914123566805 );
    CHECK(check9);

    // jn (0, 8.0) == 0.17165080713755390609
    constexpr auto check10 = CheckClose( 0, 8.0, 0.17165080713755390609 );
    CHECK(check10);

    // jn (0, 10.0) == -0.24593576445134833520
    constexpr auto check11 = CheckClose( 0, 10.0, -0.24593576445134833520 );
    CHECK(check11);

    // jn (1, x) == j1 (x)  
    // jn (1, NaN) == NaN
    constexpr auto check12 = CheckIsNaN( 1, C::NaN );
    CHECK(check12);

    // jn (1, inf) == 0
    constexpr auto check13 = Check( 1, C::Infinity, 0. );
    CHECK(check13);

    // jn (1, -1.0) == -0.44005058574493351596
    constexpr auto check14 = Check( 1, -1.0, -0.44005058574493351596 );
    CHECK(check14);

    // jn (1, 0.0) == 0.0
    constexpr auto check15 = Check( 1, 0.0, 0.0 );
    CHECK(check15);

    // jn (1, 0.1) == 0.049937526036241997556
    constexpr auto check16 = Check( 1, 0.1, 0.049937526036241997556 );
    CHECK(check16);

    // jn (1, 0.7) == 0.32899574154005894785
    constexpr auto check17 = Check( 1, 0.7, 0.32899574154005894785 );
    CHECK(check17);

    // jn (1, 1.0) == 0.44005058574493351596
    constexpr auto check18 = Check( 1, 1.0, 0.44005058574493351596 );
    CHECK(check18);
    
    // jn (1, 1.5) == 0.55793650791009964199
    constexpr auto check19 = Check( 1, 1.5, 0.55793650791009964199 );
    CHECK(check19);

    // jn (1, 2.0) == 0.57672480775687338720
    constexpr auto check20 = Check( 1, 2.0, 0.57672480775687338720 );
    CHECK(check20);

    // jn (1, 8.0) == 0.23463634685391462438
    constexpr auto check21 = Check( 1, 8.0, 0.23463634685391462438 );
    CHECK(check21);

    // jn (1, 10.0) == 0.043472746168861436670
    constexpr auto check22 = CheckClose( 1, 10.0, 0.043472746168861436670 );
    CHECK(check22);

    // jn (3, x)  
    // jn (3, NaN) == NaN
    constexpr auto check23 = CheckIsNaN( 3, C::NaN );
    CHECK(check23);

    // jn (3, inf) == 0
    constexpr auto check24 = Check( 3, C::Infinity, 0.0 );
    CHECK(check24);

    // jn (3, -1.0) == -0.019563353982668405919
    constexpr auto check25 = Check( 3, -1.0, -0.019563353982668405919 );
    CHECK(check25);

    // jn (3, 0.0) == 0.0
    constexpr auto check26 = Check( 3, 0.0, 0.0 );
    CHECK(check26);

    // jn (3, 0.1) == 0.000020820315754756261429
    constexpr auto check27 = Check( 3, 0.1, 0.000020820315754756261429 );
    CHECK(check27);

    // jn (3, 0.7) == 0.0069296548267508408077
    constexpr auto check28 = CheckClose( 3, 0.7, 0.0069296548267508408077 );
    CHECK(check28);

    // jn (3, 1.0) == 0.019563353982668405919
    constexpr auto check29 = Check( 3, 1.0, 0.019563353982668405919 );
    CHECK(check29);

    // jn (3, 2.0) == 0.12894324947440205110
    constexpr auto check30 = CheckClose( 3, 2.0, 0.12894324947440205110 );
    CHECK(check30);

    // jn (3, 10.0) == 0.058379379305186812343
    constexpr auto check31 = CheckClose( 3, 10.0, 0.058379379305186812343 );
    CHECK(check31);

    //  jn (10, x)  
    // jn (10, NaN) == NaN
    constexpr auto check32 = CheckIsNaN( 10, C::NaN );
    CHECK(check32);

    // jn (10, inf) == 0
    constexpr auto check33 = Check( 10, C::Infinity, 0.0 );
    CHECK(check33);

    // jn (10, -1.0) == 0.26306151236874532070e-9
    constexpr auto check34 = Check( 10, -1.0, 0.26306151236874532070e-9 );
    CHECK(check34);

    // jn (10, 0.0) == 0.0
    constexpr auto check35 = Check( 10, 0.0, 0.0 );
    CHECK(check35);

    // jn (10, 0.1) == 0.26905328954342155795e-19
    constexpr auto check36 = CheckClose( 10, 0.1, 0.26905328954342155795e-19 );
    CHECK(check36);

    // jn (10, 0.7) == 0.75175911502153953928e-11
    constexpr auto check37 = CheckClose( 10, 0.7, 0.75175911502153953928e-11 );
    CHECK(check37);

    // jn (10, 1.0) == 0.26306151236874532070e-9
    constexpr auto check38 = Check( 10, 1.0, 0.26306151236874532070e-9 );
    CHECK(check38);

    // jn (10, 2.0) == 0.25153862827167367096e-6
    constexpr auto check39 = CheckClose( 10, 2.0, 0.25153862827167367096e-6 );
    CHECK(check39);

    // jn (10, 10.0) == 0.20748610663335885770
    constexpr auto check40 = CheckClose( 10, 10.0, 0.20748610663335885770 );
    CHECK(check40);

}
TEST_CASE("ConstexprMathTests / DoubleJNTest1", "[math][ConstexprMathTests]")
{
    using ValueType = double;
    using C = Constants<ValueType>;

    constexpr auto Check = []( int n, ValueType x, ValueType expected ) -> bool
        {
            auto r = JN( n, x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( int n, ValueType x, ValueType expected, ValueType epsilon = std::numeric_limits<ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = JN( n, x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( int n, ValueType x ) -> bool
        {
            auto r = JN( n, x );
            return IsNaN( r );
        };

    // jn (0, x) == j0 (x)  
    // jn (0, NaN) == NaN
    constexpr auto check1 = CheckIsNaN( 0, C::NaN );
    CHECK(check1);

    // jn (0, inf) == 0
    constexpr auto check2 = Check( 0, C::Infinity, 0. );
    CHECK(check2);

    // jn (0, -1.0) == 0.76519768655796655145
    constexpr auto check3 = Check( 0, -1.0, 0.76519768655796655145 );
    CHECK(check3);

    // jn (0, 0.0) == 1.0
    constexpr auto check4 = Check( 0, 0.0, 1.0 );
    CHECK(check4);

    // jn (0, 0.1) == 0.99750156206604003228
    constexpr auto check5 = Check( 0, 0.1, 0.99750156206604003228 );
    CHECK(check5);

    // jn (0, 0.7) == 0.88120088860740528084
    constexpr auto check6 = Check( 0, 0.7, 0.88120088860740528084 );
    CHECK(check6);

    // jn (0, 1.0) == 0.76519768655796655145
    constexpr auto check7 = Check( 0, 1.0, 0.76519768655796655145 );
    CHECK(check7);

    // jn (0, 1.5) == 0.51182767173591812875
    constexpr auto check8 = Check( 0, 1.5, 0.51182767173591812875 );
    CHECK(check8);

    // jn (0, 2.0) == 0.22389077914123566805
    constexpr auto check9 = Check( 0, 2.0, 0.22389077914123566805 );
    CHECK(check9);

    // jn (0, 8.0) == 0.17165080713755390609
    constexpr auto check10 = Check( 0, 8.0, 0.17165080713755390609 );
    CHECK(check10);

    // jn (0, 10.0) == -0.24593576445134833520
    constexpr auto check11 = CheckClose( 0, 10.0, -0.24593576445134833520 );
    CHECK(check11);

    // jn (1, x) == j1 (x)  
    // jn (1, NaN) == NaN
    constexpr auto check12 = CheckIsNaN( 1, C::NaN );
    CHECK(check12);

    // jn (1, inf) == 0
    constexpr auto check13 = Check( 1, C::Infinity, 0. );
    CHECK(check13);

    // jn (1, -1.0) == -0.44005058574493351596
    constexpr auto check14 = Check( 1, -1.0, -0.44005058574493351596 );
    CHECK(check14);

    // jn (1, 0.0) == 0.0
    constexpr auto check15 = Check( 1, 0.0, 0.0 );
    CHECK(check15);

    // jn (1, 0.1) == 0.049937526036241997556
    constexpr auto check16 = Check( 1, 0.1, 0.049937526036241997556 );
    CHECK(check16);

    // jn (1, 0.7) == 0.32899574154005894785
    constexpr auto check17 = Check( 1, 0.7, 0.32899574154005894785 );
    CHECK(check17);

    // jn (1, 1.0) == 0.44005058574493351596
    constexpr auto check18 = Check( 1, 1.0, 0.44005058574493351596 );
    CHECK(check18);

    // jn (1, 1.5) == 0.55793650791009964199
    constexpr auto check19 = Check( 1, 1.5, 0.55793650791009964199 );
    CHECK(check19);

    // jn (1, 2.0) == 0.57672480775687338720
    constexpr auto check20 = CheckClose( 1, 2.0, 0.57672480775687338720 );
    CHECK(check20);

    // jn (1, 8.0) == 0.23463634685391462438
    constexpr auto check21 = CheckClose( 1, 8.0, 0.23463634685391462438 );
    CHECK(check21);

    // jn (1, 10.0) == 0.043472746168861436670
    constexpr auto check22 = Check( 1, 10.0, 0.043472746168861436670 );
    CHECK(check22);

    // jn (3, x)  
    // jn (3, NaN) == NaN
    constexpr auto check23 = CheckIsNaN( 3, C::NaN );
    CHECK(check23);

    // jn (3, inf) == 0
    constexpr auto check24 = Check( 3, C::Infinity, 0.0 );
    CHECK(check24);

    // jn (3, -1.0) == -0.019563353982668405919
    constexpr auto check25 = Check( 3, -1.0, -0.019563353982668405919 );
    CHECK(check25);

    // jn (3, 0.0) == 0.0
    constexpr auto check26 = Check( 3, 0.0, 0.0 );
    CHECK(check26);

    // jn (3, 0.1) == 0.000020820315754756261429
    constexpr auto check27 = CheckClose( 3, 0.1, 0.000020820315754756261429 );
    CHECK(check27);

    // jn (3, 0.7) == 0.0069296548267508408077
    constexpr auto check28 = Check( 3, 0.7, 0.0069296548267508408077 );
    CHECK(check28);

    // jn (3, 1.0) == 0.019563353982668405919
    constexpr auto check29 = Check( 3, 1.0, 0.019563353982668405919 );
    CHECK(check29);

    // jn (3, 2.0) == 0.12894324947440205110
    constexpr auto check30 = Check( 3, 2.0, 0.12894324947440205110 );
    CHECK(check30);

    // jn (3, 10.0) == 0.058379379305186812343
    constexpr auto check31 = CheckClose( 3, 10.0, 0.058379379305186812343 );
    CHECK(check31);

    //  jn (10, x)  
    // jn (10, NaN) == NaN
    constexpr auto check32 = CheckIsNaN( 10, C::NaN );
    CHECK(check32);

    // jn (10, inf) == 0
    constexpr auto check33 = Check( 10, C::Infinity, 0.0 );
    CHECK(check33);

    // jn (10, -1.0) == 0.26306151236874532070e-9
    constexpr auto check34 = Check( 10, -1.0, 0.26306151236874532070e-9 );
    CHECK(check34);

    // jn (10, 0.0) == 0.0
    constexpr auto check35 = Check( 10, 0.0, 0.0 );
    CHECK(check35);

    // jn (10, 0.1) == 0.26905328954342155795e-19
    constexpr auto check36 = CheckClose( 10, 0.1, 0.26905328954342155795e-19 );
    CHECK(check36);

    // jn (10, 0.7) == 0.75175911502153953928e-11
    constexpr auto check37 = CheckClose( 10, 0.7, 0.75175911502153953928e-11 );
    CHECK(check37);

    // jn (10, 1.0) == 0.26306151236874532070e-9
    constexpr auto check38 = Check( 10, 1.0, 0.26306151236874532070e-9 );
    CHECK(check38);

    // jn (10, 2.0) == 0.25153862827167367096e-6
    constexpr auto check39 = CheckClose( 10, 2.0, 0.25153862827167367096e-6 );
    CHECK(check39);

    // jn (10, 10.0) == 0.20748610663335885770
    constexpr auto check40 = CheckClose( 10, 10.0, 0.20748610663335885770 );
    CHECK(check40);

}
TEST_CASE("ConstexprMathTests / FloatY0Test1", "[math][ConstexprMathTests]")
{
    using ValueType = float;
    using C = Constants<ValueType>;

    constexpr auto Check = []( ValueType x, ValueType expected ) -> bool
        {
            auto r = Y0( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( ValueType x, ValueType expected, ValueType epsilon = std::numeric_limits<ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = Y0( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( ValueType x ) -> bool
        {
            auto r = Y0( x );
            return IsNaN( r );
        };

    // y0 (-1.0) == NaN
    constexpr auto check1 = CheckIsNaN( -1.0 );
    CHECK(check1);

    // y0 (0.0) == -inf
    constexpr auto check2 = Check( 0.0, -C::Infinity );
    CHECK(check2);

    // y0 (NaN) == NaN
    constexpr auto check3 = CheckIsNaN( C::NaN );
    CHECK(check3);

    // y0 (inf) == 0
    constexpr auto check4 = Check( C::Infinity, 0.0 );
    CHECK(check4);

    // y0 (0.1) == -1.5342386513503668441
    constexpr auto check5 = Check( 0.1, -1.5342386513503668441 );
    CHECK(check5);
    
    // y0 (0.7) == -0.19066492933739506743
    constexpr auto check6 = CheckClose( 0.7, -0.19066492933739506743 );
    CHECK(check6);

    // y0 (1.0) == 0.088256964215676957983
    constexpr auto check7 = CheckClose( 1.0, 0.088256964215676957983f );
    CHECK(check7);
    
    // y0 (1.5) == 0.38244892379775884396
    constexpr auto check8 = CheckClose( 1.5, 0.38244892379775884396 );
    CHECK(check8);

    // y0 (2.0) == 0.51037567264974511960
    constexpr auto check9 = Check( 2.0, 0.51037567264974511960 );
    CHECK(check9);

    // y0 (8.0) == 0.22352148938756622053
    constexpr auto check10 = CheckClose( 8.0, 0.22352148938756622053 );
    CHECK(check10);

    // y0 (10.0) == 0.055671167283599391424
    constexpr auto check11 = CheckClose( 10.0, 0.055671167283599391424 );
    CHECK(check11);
}
TEST_CASE("ConstexprMathTests / DoubleY0Test1", "[math][ConstexprMathTests]")
{
    using ValueType = double;
    using C = Constants<ValueType>;

    constexpr auto Check = []( ValueType x, ValueType expected ) -> bool
        {
            auto r = Y0( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( ValueType x, ValueType expected, ValueType epsilon = std::numeric_limits<ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = Y0( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( ValueType x ) -> bool
        {
            auto r = Y0( x );
            return IsNaN( r );
        };

    // y0 (-1.0) == NaN
    constexpr auto check1 = CheckIsNaN( -1.0 );
    CHECK(check1);

    // y0 (0.0) == -inf
    constexpr auto check2 = Check( 0.0, -C::Infinity );
    CHECK(check2);

    // y0 (NaN) == NaN
    constexpr auto check3 = CheckIsNaN( C::NaN );
    CHECK(check3);

    // y0 (inf) == 0
    constexpr auto check4 = Check( C::Infinity, 0.0 );
    CHECK(check4);

    // y0 (0.1) == -1.5342386513503668441
    constexpr auto check5 = Check( 0.1, -1.5342386513503668441 );
    CHECK(check5);

    // y0 (0.7) == -0.19066492933739506743
    constexpr auto check6 = CheckClose( 0.7, -0.19066492933739506743 );
    CHECK(check6);

    // y0 (1.0) == 0.088256964215676957983
    constexpr auto check7 = CheckClose( 1.0, 0.088256964215676957983 );
    CHECK(check7);

    // y0 (1.5) == 0.38244892379775884396
    constexpr auto check8 = CheckClose( 1.5, 0.38244892379775884396 );
    CHECK(check8);

    // y0 (2.0) == 0.51037567264974511960
    constexpr auto check9 = Check( 2.0, 0.51037567264974511960 );
    CHECK(check9);

    // y0 (8.0) == 0.22352148938756622053
    constexpr auto check10 = CheckClose( 8.0, 0.22352148938756622053 );
    CHECK(check10);

    // y0 (10.0) == 0.055671167283599391424
    constexpr auto check11 = Check( 10.0, 0.055671167283599391424 );
    CHECK(check11);


}
TEST_CASE("ConstexprMathTests / FloatY1Test1", "[math][ConstexprMathTests]")
{
    using ValueType = float;
    using C = Constants<ValueType>;

    constexpr auto Check = []( ValueType x, ValueType expected ) -> bool
        {
            auto r = Y1( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( ValueType x, ValueType expected, ValueType epsilon = std::numeric_limits<ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = Y1( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( ValueType x ) -> bool
        {
            auto r = Y1( x );
            return IsNaN( r );
        };

    // y1 (-1.0) == NaN
    constexpr auto check1 = CheckIsNaN( -1.0 );
    CHECK(check1);

    // y1 (0.0) == -inf
    constexpr auto check2 = Check( 0.0, -C::Infinity );
    CHECK(check2);

    // y1 (inf) == 0
    constexpr auto check3 = Check( C::Infinity,0.0 );
    CHECK(check3);

    // y1 (NaN) == NaN
    constexpr auto check4 = CheckIsNaN( C::NaN );
    CHECK(check4);

    // y1 (0.1) == -6.4589510947020269877
    constexpr auto check5 = Check( 0.1, -6.4589510947020269877 );
    CHECK(check5);

    // y1 (0.7) == -1.1032498719076333697
    constexpr auto check6 = CheckClose( 0.7, -1.1032498719076333697 );
    CHECK(check6);

    // y1 (1.0) == -0.78121282130028871655
    constexpr auto check7 = Check( 1.0, -0.78121282130028871655 );
    CHECK(check7);

    // y1 (1.5) == -0.41230862697391129595
    constexpr auto check8 = CheckClose( 1.5, -0.41230862697391129595 );
    CHECK(check8);

    // y1 (2.0) == -0.10703243154093754689
    constexpr auto check9 = CheckClose( 2.0, -0.10703243154093754689 );
    CHECK(check9);

    // y1 (8.0) == -0.15806046173124749426
    constexpr auto check10 = CheckClose( 8.0, -0.15806046173124749426 );
    CHECK(check10);

    // y1 (10.0) == 0.24901542420695388392
    constexpr auto check11 = CheckClose( 10.0, 0.24901542420695388392 );
    CHECK(check11);


}
TEST_CASE("ConstexprMathTests / DoubleY1Test1", "[math][ConstexprMathTests]")
{
    using ValueType = double;
    using C = Constants<ValueType>;

    constexpr auto Check = []( ValueType x, ValueType expected ) -> bool
        {
            auto r = Y1( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( ValueType x, ValueType expected, ValueType epsilon = std::numeric_limits<ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = Y1( x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( ValueType x ) -> bool
        {
            auto r = Y1( x );
            return IsNaN( r );
        };

    // y1 (-1.0) == NaN
    constexpr auto check1 = CheckIsNaN( -1.0 );
    CHECK(check1);

    // y1 (0.0) == -inf
    constexpr auto check2 = Check( 0.0, -C::Infinity );
    CHECK(check2);

    // y1 (inf) == 0
    constexpr auto check3 = Check( C::Infinity, 0.0 );
    CHECK(check3);

    // y1 (NaN) == NaN
    constexpr auto check4 = CheckIsNaN( C::NaN );
    CHECK(check4);

    // y1 (0.1) == -6.4589510947020269877
    constexpr auto check5 = CheckClose( 0.1, -6.4589510947020269877 );
    CHECK(check5);

    // y1 (0.7) == -1.1032498719076333697
    constexpr auto check6 = CheckClose( 0.7, -1.1032498719076333697 );
    CHECK(check6);

    // y1 (1.0) == -0.78121282130028871655
    constexpr auto check7 = Check( 1.0, -0.78121282130028871655 );
    CHECK(check7);

    // y1 (1.5) == -0.41230862697391129595
    constexpr auto check8 = Check( 1.5, -0.41230862697391129595 );
    CHECK(check8);

    // y1 (2.0) == -0.10703243154093754689
    constexpr auto check9 = CheckClose( 2.0, -0.10703243154093754689 );
    CHECK(check9);

    // y1 (8.0) == -0.15806046173124749426
    constexpr auto check10 = CheckClose( 8.0, -0.15806046173124749426 );
    CHECK(check10);

    // y1 (10.0) == 0.24901542420695388392
    constexpr auto check11 = CheckClose( 10.0, 0.24901542420695388392 );
    CHECK(check11);


}
TEST_CASE("ConstexprMathTests / FloatYNTest1", "[math][ConstexprMathTests]")
{
    using ValueType = float;
    using C = Constants<ValueType>;

    constexpr auto Check = []( int n, ValueType x, ValueType expected ) -> bool
        {
            auto r = YN( n, x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( int n, ValueType x, ValueType expected, ValueType epsilon = std::numeric_limits<ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = YN( n, x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( int n, ValueType x ) -> bool
        {
            auto r = YN( n, x );
            return IsNaN( r );
        };

    // y0 (-1.0) == NaN
    constexpr auto check1 = CheckIsNaN( 0, -1.0 );
    CHECK(check1);

    // y0 (0.0) == -inf
    constexpr auto check2 = Check( 0, 0.0, -C::Infinity );
    CHECK(check2);

    // y0 (NaN) == NaN
    constexpr auto check3 = CheckIsNaN( 0, C::NaN );
    CHECK(check3);

    // y0 (inf) == 0
    constexpr auto check4 = Check( 0, C::Infinity, 0.0 );
    CHECK(check4);

    // y0 (0.1) == -1.5342386513503668441
    constexpr auto check5 = Check( 0, 0.1, -1.5342386513503668441 );
    CHECK(check5);

    // y0 (0.7) == -0.19066492933739506743
    constexpr auto check6 = CheckClose( 0, 0.7, -0.19066492933739506743 );
    CHECK(check6);

    // y0 (1.0) == 0.088256964215676957983
    constexpr auto check7 = CheckClose( 0, 1.0, 0.088256964215676957983f );
    CHECK(check7);

    // y0 (1.5) == 0.38244892379775884396
    constexpr auto check8 = CheckClose( 0, 1.5, 0.38244892379775884396 );
    CHECK(check8);

    // y0 (2.0) == 0.51037567264974511960
    constexpr auto check9 = Check( 0, 2.0, 0.51037567264974511960 );
    CHECK(check9);

    // y0 (8.0) == 0.22352148938756622053
    constexpr auto check10 = CheckClose( 0, 8.0, 0.22352148938756622053 );
    CHECK(check10);

    // y0 (10.0) == 0.055671167283599391424
    constexpr auto check11 = CheckClose( 0, 10.0, 0.055671167283599391424 );
    CHECK(check11);

    // y1 (-1.0) == NaN
    constexpr auto check12 = CheckIsNaN( 1, -1.0 );
    CHECK(check12);

    // y1 (0.0) == -inf
    constexpr auto check13 = Check( 1, 0.0, -C::Infinity );
    CHECK(check13);

    // y1 (inf) == 0
    constexpr auto check14 = Check( 1, C::Infinity, 0.0 );
    CHECK(check14);

    // y1 (NaN) == NaN
    constexpr auto check15 = CheckIsNaN( 1, C::NaN );
    CHECK(check15);

    // y1 (0.1) == -6.4589510947020269877
    constexpr auto check16 = Check( 1, 0.1, -6.4589510947020269877 );
    CHECK(check16);

    // y1 (0.7) == -1.1032498719076333697
    constexpr auto check17 = CheckClose( 1, 0.7, -1.1032498719076333697 );
    CHECK(check17);

    // y1 (1.0) == -0.78121282130028871655
    constexpr auto check18 = Check( 1, 1.0, -0.78121282130028871655 );
    CHECK(check18);

    // y1 (1.5) == -0.41230862697391129595
    constexpr auto check19 = CheckClose( 1, 1.5, -0.41230862697391129595 );
    CHECK(check19);

    // y1 (2.0) == -0.10703243154093754689
    constexpr auto check20 = CheckClose( 1, 2.0, -0.10703243154093754689 );
    CHECK(check20);

    // y1 (8.0) == -0.15806046173124749426
    constexpr auto check21 = CheckClose( 1, 8.0, -0.15806046173124749426 );
    CHECK(check21);

    // y1 (10.0) == 0.24901542420695388392
    constexpr auto check22 = CheckClose( 1, 10.0, 0.24901542420695388392 );
    CHECK(check22);

    /* yn (3, x)  */
    // yn (3, inf) == 0
    constexpr auto check23 = Check( 3, C::Infinity, 0.0 );
    CHECK(check23);

    // yn (3, NaN) == NaN
    constexpr auto check24 = CheckIsNaN( 3, C::NaN );
    CHECK(check24);

    // yn (3, 0.1) == -5099.33203
    constexpr auto check25 = Check( 3, 0.1, -5099.33203 );
    CHECK(check25);

    // yn (3, 0.7) == -15.8194780
    constexpr auto check26 = Check( 3, 0.7, -15.8194780 );
    CHECK(check26);

    // yn (3, 1.0) == -5.82151747
    constexpr auto check27 = Check( 3, 1.0, -5.82151747 );
    CHECK(check27);

    // yn (3, 2.0) == -1.12778378
    constexpr auto check28 = Check( 3, 2.0, -1.12778378 );
    CHECK(check28);

    // yn (3, 10.0) == -0.251362681
    constexpr auto check29 = Check( 3, 10.0, -0.251362681 );
    CHECK(check29);

    /* yn (10, x)  */
    // yn (10, inf) == 0
    constexpr auto check30 = Check( 10, C::Infinity, 0.0 );
    CHECK(check30);

    // yn (10, NaN) == NaN
    constexpr auto check31 = CheckIsNaN( 10, C::NaN );
    CHECK(check31);

    // yn (10, 0.1) == -1.18313320e+18
    constexpr auto check32 = Check( 10, 0.1, -1.18313320e+18 );
    CHECK(check32);

    // yn (10, 0.7) == -4.24471936e+09
    constexpr auto check33 = Check( 10, 0.7, -4.24471936e+09 );
    CHECK(check33);

    // yn (10, 1.0) == -121618016.
    constexpr auto check34 = Check( 10, 1.0, -121618016. );
    CHECK(check34);

    // yn (10, 2.0) == -129184.539
    constexpr auto check35 = Check( 10, 2.0, -129184.539 );
    CHECK(check35);

    // yn (10, 10.0) == -0.359814137
    constexpr auto check36 = Check( 10, 10.0, -0.359814137 );
    CHECK(check36);
}
TEST_CASE("ConstexprMathTests / DoubleYNTest1", "[math][ConstexprMathTests]")
{
    using ValueType = double;
    using C = Constants<ValueType>;

    constexpr auto Check = []( int n, ValueType x, ValueType expected ) -> bool
        {
            auto r = YN( n, x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckClose = []( int n, ValueType x, ValueType expected, ValueType epsilon = std::numeric_limits<ValueType>::epsilon( ) * 10 ) -> bool
        {
            auto r = YN( n, x );
            return AreNearlyEqual( r, expected, epsilon );
        };

    constexpr auto CheckIsNaN = []( int n, ValueType x ) -> bool
        {
            auto r = YN( n, x );
            return IsNaN( r );
        };

    // y0 (-1.0) == NaN
    constexpr auto check1 = CheckIsNaN( 0, -1.0 );
    CHECK(check1);

    // y0 (0.0) == -inf
    constexpr auto check2 = Check( 0, 0.0, -C::Infinity );
    CHECK(check2);

    // y0 (NaN) == NaN
    constexpr auto check3 = CheckIsNaN( 0, C::NaN );
    CHECK(check3);

    // y0 (inf) == 0
    constexpr auto check4 = Check( 0, C::Infinity, 0.0 );
    CHECK(check4);

    // y0 (0.1) == -1.5342386513503668441
    constexpr auto check5 = Check( 0, 0.1, -1.5342386513503668441 );
    CHECK(check5);

    // y0 (0.7) == -0.19066492933739506743
    constexpr auto check6 = CheckClose( 0, 0.7, -0.19066492933739506743 );
    CHECK(check6);

    // y0 (1.0) == 0.088256964215676957983
    constexpr auto check7 = CheckClose( 0, 1.0, 0.088256964215676957983 );
    CHECK(check7);

    // y0 (1.5) == 0.38244892379775884396
    constexpr auto check8 = CheckClose( 0, 1.5, 0.38244892379775884396 );
    CHECK(check8);

    // y0 (2.0) == 0.51037567264974511960
    constexpr auto check9 = Check( 0, 2.0, 0.51037567264974511960 );
    CHECK(check9);

    // y0 (8.0) == 0.22352148938756622053
    constexpr auto check10 = CheckClose( 0, 8.0, 0.22352148938756622053 );
    CHECK(check10);

    // y0 (10.0) == 0.055671167283599391424
    constexpr auto check11 = CheckClose( 0, 10.0, 0.055671167283599391424 );
    CHECK(check11);

    // y1 (-1.0) == NaN
    constexpr auto check12 = CheckIsNaN( 1, -1.0 );
    CHECK(check12);

    // y1 (0.0) == -inf
    constexpr auto check13 = Check( 1, 0.0, -C::Infinity );
    CHECK(check13);

    // y1 (inf) == 0
    constexpr auto check14 = Check( 1, C::Infinity, 0.0 );
    CHECK(check14);

    // y1 (NaN) == NaN
    constexpr auto check15 = CheckIsNaN( 1, C::NaN );
    CHECK(check15);

    // y1 (0.1) == -6.4589510947020269877
    constexpr auto check16 = CheckClose( 1, 0.1, -6.4589510947020269877 );
    CHECK(check16);

    // y1 (0.7) == -1.1032498719076333697
    constexpr auto check17 = CheckClose( 1, 0.7, -1.1032498719076333697 );
    CHECK(check17);

    // y1 (1.0) == -0.78121282130028871655
    constexpr auto check18 = Check( 1, 1.0, -0.78121282130028871655 );
    CHECK(check18);

    // y1 (1.5) == -0.41230862697391129595
    constexpr auto check19 = CheckClose( 1, 1.5, -0.41230862697391129595 );
    CHECK(check19);

    // y1 (2.0) == -0.10703243154093754689
    constexpr auto check20 = CheckClose( 1, 2.0, -0.10703243154093754689 );
    CHECK(check20);

    // y1 (8.0) == -0.15806046173124749426
    constexpr auto check21 = CheckClose( 1, 8.0, -0.15806046173124749426 );
    CHECK(check21);

    // y1 (10.0) == 0.24901542420695388392
    constexpr auto check22 = CheckClose( 1, 10.0, 0.24901542420695388392 );
    CHECK(check22);

    /* yn (3, x)  */
    // yn (3, inf) == 0
    constexpr auto check23 = Check( 3, C::Infinity, 0.0 );
    CHECK(check23);

    // yn (3, NaN) == NaN
    constexpr auto check24 = CheckIsNaN( 3, C::NaN );
    CHECK(check24);

    // yn (3, 0.1) == -5099.3323786129058

    constexpr auto check25 = Check( 3, 0.1, -5099.3323786129058 );
    CHECK(check25);

    // yn (3, 0.7) == -15.819479052819633505
    constexpr auto check26 = Check( 3, 0.7, -15.819479052819640 );
    CHECK(check26);

    // yn (3, 1.0) == -5.8215176059647291
    constexpr auto check27 = Check( 3, 1.0, -5.8215176059647291 );
    CHECK(check27);

    // yn (3, 2.0) == -1.1277837768404280
    constexpr auto check28 = Check( 3, 2.0, -1.1277837768404280 );
    CHECK(check28);

    // yn (3, 10.0) == -0.25136265718383727
    constexpr auto check29 = Check( 3, 10.0, -0.25136265718383727 );
    CHECK(check29);

    /* yn (10, x)  */
    // yn (10, inf) == 0
    constexpr auto check30 = Check( 10, C::Infinity, 0.0 );
    CHECK(check30);

    // yn (10, NaN) == NaN
    constexpr auto check31 = CheckIsNaN( 10, C::NaN );
    CHECK(check31);

    // yn (10, 0.1) == -1.1831335132045202e+18
    constexpr auto check32 = Check( 10, 0.1, -1.1831335132045202e+18 );
    CHECK(check32);

    // yn (10, 0.7) == -4244719426.0703883
    constexpr auto check33 = Check( 10, 0.7, -4244719426.0703883 );
    CHECK(check33);

    // yn (10, 1.0) == -121618014.27868918
    constexpr auto check34 = Check( 10, 1.0, -121618014.27868918 );
    CHECK(check34);

    // yn (10, 2.0) == -129184.54220803932
    constexpr auto check35 = Check( 10, 2.0, -129184.54220803932 );
    CHECK(check35);

    // yn (10, 10.0) == -0.35981415218340268
    constexpr auto check36 = Check( 10, 10.0, -0.35981415218340268 );
    CHECK(check36);
}
TEST_CASE("ConstexprMathTests / FloatErfTest1", "[math][ConstexprMathTests]")
{
    using ValueType = float;
    using C = Constants<ValueType>;

    constexpr auto Check = []( ValueType x, ValueType expected ) -> bool
        {
            auto r = Erf( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( ValueType x ) -> bool
        {
            auto r = Erf( x );
            return IsNaN( r );
        };

    // erf (0) == 0
    constexpr auto check1 = Check( C::Zero, C::Zero );
    CHECK(check1);

    // erf (-0) == -0
    constexpr auto check2 = Check( -C::Zero, -C::Zero );
    CHECK(check2);

    // erf (inf) == 1
    constexpr auto check3 = Check( C::Infinity, C::One );
    CHECK(check3);

    // erf (-inf) == -1
    constexpr auto check4 = Check( C::NegativeInfinity, -C::One );
    CHECK(check4);

    // erf (NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN );
    CHECK(check5);

    // erf (0.7) == 0.67780119383741847297
    constexpr auto check6 = Check( 0.7, 0.67780119383741847297 );
    CHECK(check6);

    // erf (1.2) == 0.91031397822963538024
    constexpr auto check7 = Check( 1.2, 0.91031397822963538024 );
    CHECK(check7);

    // erf (2.0) == 0.99532226501895273416
    constexpr auto check8 = Check( 2.0, 0.99532226501895273416 );
    CHECK(check8);

    // erf (4.1) == 0.99999999329997234592
    constexpr auto check9 = Check( 4.1, 0.99999999329997234592 );
    CHECK(check9);

    // erf (27) == 1.0
    constexpr auto check10 = Check( 27, 1.0 );
    CHECK(check10);

}
TEST_CASE("ConstexprMathTests / DoubleErfTest1", "[math][ConstexprMathTests]")
{
    using ValueType = double;
    using C = Constants<ValueType>;

    constexpr auto Check = []( ValueType x, ValueType expected ) -> bool
        {
            auto r = Erf( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( ValueType x ) -> bool
        {
            auto r = Erf( x );
            return IsNaN( r );
        };

    // erf (0) == 0
    constexpr auto check1 = Check( C::Zero, C::Zero );
    CHECK(check1);

    // erf (-0) == -0
    constexpr auto check2 = Check( -C::Zero, -C::Zero );
    CHECK(check2);

    // erf (inf) == 1
    constexpr auto check3 = Check( C::Infinity, C::One );
    CHECK(check3);

    // erf (-inf) == -1
    constexpr auto check4 = Check( C::NegativeInfinity, -C::One );
    CHECK(check4);

    // erf (NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN );
    CHECK(check5);

    // erf (0.7) == 0.67780119383741847297
    constexpr auto check6 = Check( 0.7, 0.67780119383741847297 );
    CHECK(check6);

    // erf (1.2) == 0.91031397822963538024
    constexpr auto check7 = Check( 1.2, 0.91031397822963538024 );
    CHECK(check7);

    // erf (2.0) == 0.99532226501895273416
    constexpr auto check8 = Check( 2.0, 0.99532226501895273416 );
    CHECK(check8);

    // erf (4.1) == 0.99999999329997234592
    constexpr auto check9 = Check( 4.1, 0.99999999329997234592 );
    CHECK(check9);

    // erf (27) == 1.0
    constexpr auto check10 = Check( 27, 1.0 );
    CHECK(check10);

}
TEST_CASE("ConstexprMathTests / FloatErfCTest1", "[math][ConstexprMathTests]")
{
    using ValueType = float;
    using C = Constants<ValueType>;

    constexpr auto Check = []( ValueType x, ValueType expected ) -> bool
        {
            auto r = ErfC( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( ValueType x ) -> bool
        {
            auto r = ErfC( x );
            return IsNaN( r );
        };

    // erfc (inf) == 0.0
    constexpr auto check1 = Check( C::Infinity, C::Zero );
    static_assert( ErfC( C::Infinity ) == C::Zero );
    CHECK(check1);

    // erfc (-inf) == 2.0
    constexpr auto check2 = Check( C::NegativeInfinity, C::Two );
    CHECK(check2);
    
    // erfc (0.0) == 1.0
    constexpr auto check3 = Check( C::Zero, C::One );
    CHECK(check3);

    // erfc (-0) == 1.0
    constexpr auto check4 = Check( -C::Zero, C::One );
    CHECK(check4);

    // erfc (NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN );
    CHECK(check5);

    // erfc (0.7) == 0.322198808
    constexpr auto check6 = Check( 0.7f, 0.322198808f );
    CHECK(check6);

    // erfc (1.2) == 0.0896860063
    constexpr auto check7 = Check( 1.2f, 0.0896860063f );
    CHECK(check7);

    // erfc (2.0) == 0.00467773527
    constexpr auto check8 = Check( 2.0f, 0.00467773527f );
    static_assert( ErfC( 2.0f ) == 0.00467773527f );
    CHECK(check8);

    // erfc (4.1) == 6.70003297e-09
    constexpr auto check9 = Check( 4.1f, 6.70003297e-09f );
    CHECK(check9);

    // erfc (9) == 4.13703171e-37
    constexpr auto check10 = Check( 9.f, 4.13703171e-37f );
    CHECK(check10);

}
TEST_CASE("ConstexprMathTests / DoubleErfCTest1", "[math][ConstexprMathTests]")
{
    using ValueType = double;
    using C = Constants<ValueType>;

    constexpr auto Check = []( ValueType x, ValueType expected ) -> bool
        {
            auto r = ErfC( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( ValueType x ) -> bool
        {
            auto r = ErfC( x );
            return IsNaN( r );
        };

    // erfc (inf) == 0.0
    constexpr auto check1 = Check( C::Infinity, C::Zero );
    CHECK(check1);

    // erfc (-inf) == 2.0
    constexpr auto check2 = Check( C::NegativeInfinity, C::Two );
    CHECK(check2);

    // erfc (0.0) == 1.0
    constexpr auto check3 = Check( C::Zero, C::One );
    CHECK(check3);

    // erfc (-0) == 1.0
    constexpr auto check4 = Check( -C::Zero, C::One );
    CHECK(check4);

    // erfc (NaN) == NaN
    constexpr auto check5 = CheckIsNaN( C::NaN );
    CHECK(check5);

    // erfc (0.7) == 0.32219880616258156
    constexpr auto check6 = Check( 0.7, 0.32219880616258156 );
    CHECK(check6);

    // erfc (1.2) == 0.089686021770364638
    constexpr auto check7 = Check( 1.2, 0.089686021770364638 );
    CHECK(check7);

    // erfc (2.0) == 0.0046777349810472662
    constexpr auto check8 = Check( 2.0, 0.0046777349810472662 );
    CHECK(check8);

    // erfc (4.1) == 6.7000276540849183e-09
    constexpr auto check9 = Check( 4.1, 6.7000276540849183e-09 );
    CHECK(check9);

    // erfc (9) == 4.1370317465138101e-37
    constexpr auto check10 = Check( 9., 4.1370317465138101e-37 );
    CHECK(check10);

}
TEST_CASE("ConstexprMathTests / DoubleTGammaTest1", "[math][ConstexprMathTests]")
{
    using ValueType = double;
    using C = Constants<ValueType>;

    constexpr auto Check = []( ValueType x, ValueType expected ) -> bool
        {
            auto r = TGamma( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( ValueType x ) -> bool
        {
            auto r = TGamma( x );
            return IsNaN( r );
        };

    // tgamma (inf) == inf
    constexpr auto check1 = Check( C::Infinity, C::Infinity );
    CHECK(check1);

    // tgamma (0) == inf
    constexpr auto check2 = Check( C::Zero, C::Infinity );
    CHECK(check2);
    
    // tgamma (-0) == inf
    constexpr auto check3 = Check( -C::Zero, C::Infinity );
    CHECK(check3);

    // tgamma (-2) == NaN
    constexpr auto check4 = CheckIsNaN( -C::Two );
    CHECK(check4);
    // tgamma (-inf) == NaN
    constexpr auto check5 = CheckIsNaN( -C::Infinity );
    CHECK(check5);
    // tgamma (NaN) == NaN
    constexpr auto check6 = CheckIsNaN( C::NaN );
    CHECK(check6);

    // tgamma (0.5) == sqrt (pi)
    constexpr auto check7 = Check( .5, Sqrt( C::Pi ) );
    CHECK(check7);
    // tgamma (-0.5) == -2 sqrt (pi)
    constexpr auto check8 = Check( -.5, -2. * Sqrt( C::Pi ) );
    CHECK(check8);

    // tgamma (1) == 1
    constexpr auto check9 = Check( 1., 1. );
    CHECK(check9);
    // tgamma (4) == 6
    constexpr auto check10 = Check( 4., 6. );
    CHECK(check10);

    // tgamma (0.7) == 1.29805533264755778568
    constexpr auto check11 = Check( 0.7, 1.29805533264755778568 );
    CHECK(check11);
                       
    // tgamma (1.2) == 0.91816874239976054
    constexpr auto check12 = Check( 1.2, 0.91816874239976054 );
    CHECK(check12);

}
TEST_CASE("ConstexprMathTests / FloatLGammaTest1", "[math][ConstexprMathTests]")
{
    using ValueType = float;
    using C = Constants<ValueType>;

    constexpr auto Check = []( ValueType x, ValueType expected ) -> bool
        {
            auto r = LGamma( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( ValueType x ) -> bool
        {
            auto r = LGamma( x );
            return IsNaN( r );
        };

    constexpr auto check1 = Check( C::Infinity, C::Infinity );
    CHECK(check1);

    constexpr auto check2 = Check( C::Zero, C::Infinity );
    CHECK(check2);

    constexpr auto check3 = Check( -3.0, C::Infinity );
    CHECK(check3);

    constexpr auto check4 = Check( -C::Infinity, C::Infinity );
    CHECK(check4);

    constexpr auto check5 = CheckIsNaN( C::NaN );
    CHECK(check5);

    constexpr auto check6 = Check( C::One, C::Zero );
    CHECK(check6);

    constexpr auto check7 = Check( C::Three, 0.6931471805599453094172321214581766 );
    CHECK(check7);

    constexpr auto check8 = Check( 0.5, 0.57236494292470008707171367567652933 );
    CHECK(check8);

    constexpr auto check9 = Check( -0.5, 1.265512123484645396488945797134706 );
    CHECK(check9);
}
TEST_CASE("ConstexprMathTests / DoubleLGammaTest1", "[math][ConstexprMathTests]")
{
    using ValueType = double;
    using C = Constants<ValueType>;

    constexpr auto Check = []( ValueType x, ValueType expected ) -> bool
        {
            auto r = LGamma( x );
            return IsSameValue( r, expected );
        };

    constexpr auto CheckIsNaN = []( ValueType x ) -> bool
        {
            auto r = LGamma( x );
            return IsNaN( r );
        };

    constexpr auto check1 = Check( C::Infinity, C::Infinity );
    CHECK(check1);

    constexpr auto check2 = Check( C::Zero, C::Infinity );
    CHECK(check2);

    constexpr auto check3 = Check( -3.0, C::Infinity );
    CHECK(check3);

    constexpr auto check4 = Check( -C::Infinity, C::Infinity );
    CHECK(check4);

    constexpr auto check5 = CheckIsNaN( C::NaN );
    CHECK(check5);

    constexpr auto check6 = Check( C::One, C::Zero );
    CHECK(check6);

    constexpr auto check7 = Check( C::Three, 0.6931471805599453094172321214581766 );
    CHECK(check7);

    constexpr auto check8 = Check( 0.5, 0.57236494292470008707171367567652933 );
    CHECK(check8);

    constexpr auto check9 = Check( -0.5, 1.265512123484645396488945797134706 );
    CHECK(check9);
}
