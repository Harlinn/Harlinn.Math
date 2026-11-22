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

using namespace Harlinn::Math;
namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };


}
TEST_CASE("TruncTests / TruncDoubleTest1", "[math][TruncTests]")
{
    using namespace Test;
    using namespace Test::Generators;
    using FloatT = double;
    Generators::RangeGenerator<FloatT> generator( std::numeric_limits<FloatT>::lowest(), std::numeric_limits<FloatT>::max( ) );

    NumericTest test( "TruncDoubleTest1" );
    auto success = test.Run( generator,
        []( auto x )
        {
            return std::trunc( x );
        },
        []( auto x )
        {
            return Math::Internal::FloatingPoint<FloatT>::Trunc( x );
        } );
    CHECK(success);
}
TEST_CASE("TruncTests / TruncFloatTest1", "[math][TruncTests]")
{
    using namespace Test;
    using namespace Test::Generators;
    using FloatT = float;
    Generators::RangeGenerator<FloatT> generator( std::numeric_limits<FloatT>::lowest( ), std::numeric_limits<FloatT>::max( ) );

    NumericTest test( "TruncDoubleTest1" );
    auto success = test.Run( generator,
        []( auto x )
        {
            return std::trunc( x );
        },
        []( auto x )
        {
            return Math::Internal::FloatingPoint<FloatT>::Trunc( x );
        } );
    CHECK(success);
}
