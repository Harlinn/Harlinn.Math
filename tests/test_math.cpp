#include <catch2/catch_test_macros.hpp>
#include <harlinn/math/VectorMath.h>

#include <cfloat>
#include <span>
#include <vector>

static_assert( Harlinn::Common::ConstantRange<const std::vector<int>> );
static_assert( Harlinn::Common::ConstantRange<std::span<const int>> );
static_assert( !Harlinn::Common::ConstantRange<std::vector<int>> );
static_assert( !Harlinn::Common::ConstantRange<std::span<int>> );
static_assert( !Harlinn::Common::ConstantRange<int> );

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
