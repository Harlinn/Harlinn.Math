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
    inline bool Equal( const Math::SquareMatrix<float, 4>& m1, const Math::SquareMatrix<float, 4>& m2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 4; i++ )
        {
            for ( size_t j = 0; j < 4; j++ )
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
TEST_CASE("SquareMatrix4FloatTests / InverseTest1", "[math][SquareMatrix4FloatTests]")
{
    using namespace Harlinn::Math;
    SquareMatrix<float, 4> matrix( 0.285714f,  0.857143f, -0.428571f, 0.0f,
                                        -0.857143f, 0.428571f, 0.285714f, 0.0f,
                                        0.428571f, 0.285714f, 0.857143f, 0.0f,
                                        1.0f, 2.0f, 3.0f, 1.0f );

    SquareMatrix<float, 4> expected( 0.285714f, -0.857143f, 0.428571f, 0.0f,
                                        0.857143f, 0.428571f, 0.285714f, 0.0f,
                                        -0.428571f, 0.285714f, 0.857143f, 0.0f,
                                        -0.714286f, -0.857143f, -3.57143f, 1.0f );

    SquareMatrix<float, 4> inverse = Math::Inverse( matrix );

    bool equal = Equal( inverse, expected );

    CHECK(equal);
}
TEST_CASE("SquareMatrix4FloatTests / DeterminantTest1", "[math][SquareMatrix4FloatTests]")
{
    using namespace Harlinn::Math;
    SquareMatrix<float, 4> matrix( 0.285714f, 0.857143f, -0.428571f, 0.0f,
        -0.857143f, 0.428571f, 0.285714f, 0.0f,
        0.428571f, 0.285714f, 0.857143f, 0.0f,
        1.0f, 2.0f, 3.0f, 1.0f );

    auto expected = 1.f;

    auto determinant = Math::ScalarDeterminant( matrix );

    CHECK((determinant) == Catch::Approx(expected).epsilon((0.01f) / 100.0));
}
TEST_CASE("SquareMatrix4FloatTests / DecomposeTest1", "[math][SquareMatrix4FloatTests]")
{
    using namespace Harlinn::Math;
    SquareMatrix<float, 4>::Simd matrix = SquareMatrix<float, 4>( 0.285714f, 0.857143f, -0.428571f, 0.0f,
        -0.857143f, 0.428571f, 0.285714f, 0.0f,
        0.428571f, 0.285714f, 0.857143f, 0.0f,
        1.0f, 2.0f, 3.0f, 1.0f );

    Vector3f::Simd scale;
    Quaternion<float>::Simd rotationQuaternion;
    Vector3f::Simd translation;

    auto success = Decompose( matrix, &scale, &rotationQuaternion, &translation );

    CHECK(success);

    Vector3f::Simd expectedScale{ 0.999999821, 0.999999821, 0.999999821 };
    Quaternion<float>::Simd expectedRotationQuaternion{ -0.00000000, 0.267261058, 0.534522712, 0.801783681 };
    Vector3f::Simd expectedTranslation{ 1.00000000, 2.00000000, 3.00000000 };

    auto hasExpectedScale = expectedScale == scale;
    CHECK(hasExpectedScale);
    auto hasExpectedRotationQuaternion = expectedRotationQuaternion == rotationQuaternion;
    CHECK(hasExpectedRotationQuaternion);
    auto hasExpectedTranslation = expectedTranslation == translation;
    CHECK(hasExpectedTranslation);
    
}
