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

    inline bool Equal( const Math::SquareMatrix<float, 3>& m1, const Math::SquareMatrix<float, 3>& m2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            for ( size_t j = 0; j < 3; j++ )
            {
                auto v1 = m1[ i ][ j ];
                float v2 = m2[ i ][ j ];
                auto delta = v1 - v2;
                if ( !( std::abs( delta ) <= epsilon ) )
                {
                    return false;
                }
            }
        }
        return true;
    }
}
TEST_CASE("SquareMatrix3FloatTests / AddTest1", "[math][SquareMatrix3FloatTests]")
{
    using namespace Harlinn::Math;
    SquareMatrix<float, 3> matrix1( 1.f, 2.f, 3.f, 
                                    4.f, 5.f, 6.f,
                                    7.f, 8.f, 9.f);
    SquareMatrix<float, 3> matrix2( 2.f, 3.f, 4.f,
                                    5.f, 6.f, 7.f,
                                    8.f, 9.f, 10.f );

    SquareMatrix<float, 3> expected( 3.f, 5.f, 7.f,
                                    9.f, 11.f, 13.f,
                                    15.f, 17.f, 19.f );

    SquareMatrix<float, 3> result = matrix1 + matrix2;

    bool equal = Equal( result, expected );

    CHECK(equal);
}
TEST_CASE("SquareMatrix3FloatTests / SubTest1", "[math][SquareMatrix3FloatTests]")
{
    using namespace Harlinn::Math;
    SquareMatrix<float, 3> matrix1( 2.f, 3.f, 4.f,
                                    5.f, 6.f, 7.f,
                                    8.f, 9.f, 10.f );
    SquareMatrix<float, 3> matrix2( 1.f, 2.f, 3.f,
                                    4.f, 5.f, 6.f,
                                    7.f, 8.f, 9.f );


    SquareMatrix<float, 3> expected( 1.f, 1.f, 1.f,
                                    1.f, 1.f, 1.f,
                                    1.f, 1.f, 1.f );

    SquareMatrix<float, 3> result = matrix1 - matrix2;

    bool equal = Equal( result, expected );

    CHECK(equal);
}
TEST_CASE("SquareMatrix3FloatTests / MulTest1", "[math][SquareMatrix3FloatTests]")
{
    using namespace Harlinn::Math;
    SquareMatrix<float, 3> matrix1( 1.f, 2.f, 3.f,
                                    4.f, 5.f, 6.f,
                                    7.f, 8.f, 9.f );
    SquareMatrix<float, 3> matrix2( 2.f, 3.f, 4.f,
                                    5.f, 6.f, 7.f,
                                    8.f, 9.f, 10.f );


    SquareMatrix<float, 3> expected( 36.f, 42.f, 48.f,
                                    81.f, 96.f, 111.f,
                                    126.f, 150.f, 174.f );

    SquareMatrix<float, 3> result = matrix1 * matrix2;

    bool equal = Equal( result, expected );

    CHECK(equal);
}
TEST_CASE("SquareMatrix3FloatTests / TransposeTest1", "[math][SquareMatrix3FloatTests]")
{
    using namespace Harlinn::Math;
    SquareMatrix<float, 3> matrix1( 1.f, 2.f, 3.f,
                                    4.f, 5.f, 6.f,
                                    7.f, 8.f, 9.f );

    SquareMatrix<float, 3> expected( 1.f, 4.f, 7.f,
                                    2.f, 5.f, 8.f,
                                    3.f, 6.f, 9.f );

    SquareMatrix<float, 3> result = Transpose( matrix1 );

    bool equal = Equal( result, expected );

    CHECK(equal);
}
TEST_CASE("SquareMatrix3FloatTests / DeterminantTest1", "[math][SquareMatrix3FloatTests]")
{
    using namespace Harlinn::Math;
    SquareMatrix<float, 3> matrix1( 3.f, 2.f, 3.f,
                            4.f, 2.f, 4.f,
                            8.f, 2.f, 2.f );

    Math::Vector<float, 3> result = Determinant( matrix1 );

    bool equal = result.x == 12.f;

    CHECK(equal);
}
TEST_CASE("SquareMatrix3FloatTests / InverseTest1", "[math][SquareMatrix3FloatTests]")
{
    using namespace Harlinn::Math;
    SquareMatrix<float, 3> matrix( 3.f, 2.f, 3.f,
                                4.f, 2.f, 4.f,
                                8.f, 2.f, 2.f );

    SquareMatrix<float, 3> expected( -0.333333f, 0.166667f, 0.166667f,
                                    2.0f, -1.5f, 0.0f,
                                    -0.666667f, 0.833333f, -0.166667f );

    SquareMatrix<float, 3> inverse = Math::Inverse( matrix );

    bool equal = Equal( inverse, expected );

    CHECK(equal);
}
