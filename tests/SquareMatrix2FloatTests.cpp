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

namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };

    inline bool Equal( const Math::SquareMatrix<float, 2>& m1, const Math::SquareMatrix<float, 2>& m2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 2; i++ )
        {
            for ( size_t j = 0; j < 2; j++ )
            {
                auto v1 = m1[ i ][ j ];
                float v2 = m2[ i ][ j ];
                auto delta = v1 - v2;
                if ( std::abs( delta ) > epsilon )
                {
                    return false;
                }
            }
        }
        return true;
    }
}
TEST_CASE("SquareMatrix2FloatTests / AddTest1", "[math][SquareMatrix2FloatTests]")
{
    using namespace Harlinn::Math;
    SquareMatrix<float, 2> matrix1( 1.f, 2.f, 3.f, 4.f );
    SquareMatrix<float, 2> matrix2( 2.f, 3.f, 4.f, 5.f );

    SquareMatrix<float, 2> expected( 3.f, 5.f, 7.f, 9.f );

    SquareMatrix<float, 2> result = matrix1 + matrix2;

    bool equal = Equal( result, expected );

    CHECK(equal);
}
TEST_CASE("SquareMatrix2FloatTests / SubTest1", "[math][SquareMatrix2FloatTests]")
{
    using namespace Harlinn::Math;
    SquareMatrix<float, 2> matrix1( 2.f, 3.f, 4.f, 5.f );
    SquareMatrix<float, 2> matrix2( 1.f, 2.f, 2.f, 2.f );
    

    SquareMatrix<float, 2> expected( 1.f, 1.f, 2.f, 3.f );

    SquareMatrix<float, 2> result = matrix1 - matrix2;

    bool equal = Equal( result, expected );

    CHECK(equal);
}
TEST_CASE("SquareMatrix2FloatTests / MulTest1", "[math][SquareMatrix2FloatTests]")
{
    using namespace Harlinn::Math;
    SquareMatrix<float, 2> matrix1( 2.f, 3.f, 4.f, 5.f );
    SquareMatrix<float, 2> matrix2( 1.f, 2.f, 2.f, 2.f );


    SquareMatrix<float, 2> expected( 8.f, 10.f, 14.f, 18.f );

    SquareMatrix<float, 2> result = matrix1 * matrix2;

    bool equal = Equal( result, expected );

    CHECK(equal);
}
TEST_CASE("SquareMatrix2FloatTests / TransposeTest1", "[math][SquareMatrix2FloatTests]")
{
    using namespace Harlinn::Math;
    SquareMatrix<float, 2> matrix1( 1.f, 2.f, 3.f, 4.f );

    SquareMatrix<float, 2> expected( 1.f, 3.f, 2.f, 4.f );

    SquareMatrix<float, 2> result = Transpose( matrix1 );

    bool equal = Equal( result, expected );

    CHECK(equal);
}
TEST_CASE("SquareMatrix2FloatTests / DeterminantTest1", "[math][SquareMatrix2FloatTests]")
{
    using namespace Harlinn::Math;
    SquareMatrix<float, 2> matrix1( 1.f, 2.f, 3.f, 4.f );

    Math::Vector<float, 2> result = Determinant( matrix1 );

    bool equal = result.x == -2.f;

    CHECK(equal);
}
TEST_CASE("SquareMatrix2FloatTests / InverseTest1", "[math][SquareMatrix2FloatTests]")
{
    using namespace Harlinn::Math;
    SquareMatrix<float, 2> matrix( 0.285714f, 0.857143f, -0.428571f, 0.0f );

    SquareMatrix<float, 2> expected( 0.0f, -2.33334f, 1.16667f, 0.777778f );

    SquareMatrix<float, 2> inverse = Math::Inverse( matrix );

    bool equal = Equal( inverse, expected );

    CHECK(equal);
}
