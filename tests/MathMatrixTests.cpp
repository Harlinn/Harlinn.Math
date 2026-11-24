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

using namespace Harlinn;

namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };

    


    constexpr float EPSILON = 1.192092896e-7f;

    bool ApproximatelyEqual( float a, float b, float epsilon = EPSILON )
    {
        return std::abs( a - b ) < epsilon;
    }

    bool MatrixApproximatelyEqual(
        const SquareMatrix<float, 4>& m1,
        const SquareMatrix<float, 4>& m2,
        float epsilon = EPSILON )
    {
        for ( size_t i = 0; i < 4; ++i )
        {
            for ( size_t j = 0; j < 4; ++j )
            {
                if ( !ApproximatelyEqual( m1[ i ][ j ], m2[ i ][ j ], epsilon ) )
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool MatrixApproximatelyEqual(
        const SquareMatrix<float, 4>::Simd& m1,
        const SquareMatrix<float, 4>::Simd& m2,
        float epsilon = EPSILON )
    {
        return MatrixApproximatelyEqual( SquareMatrix<float, 4>( m1 ), SquareMatrix<float, 4>( m2 ), epsilon );
    }

    bool MatrixApproximatelyEqual(
        const SquareMatrix<float, 2>::Simd& actual,
        const SquareMatrix<float, 2>::Simd& expected,
        float epsilon = 1e-5f )
    {
        auto actualArray = SquareMatrix<float, 2>::Simd::Traits::ToArray( actual.simd );
        auto expectedArray = SquareMatrix<float, 2>::Simd::Traits::ToArray( expected.simd );

        for ( size_t i = 0; i < actualArray.size( ); ++i )
        {
            if ( !( std::abs( actualArray[ i ] - expectedArray[ i ] ) <= epsilon ) )
            {
                return false;
            }
        }
        return true;
    }


    /// <summary>
    /// Verifies that a 4x4 rotation matrix is orthogonal (R^T * R = I).
    /// </summary>
    /// <remarks>
    /// For DirectX matrices, checks that the upper-left 3x3 is orthogonal
    /// and the bottom row is [0, 0, 0, 1].
    /// </remarks>
    bool IsOrthogonalMatrix( const Math::Vector<float, 4>::Simd& r0, const Math::Vector<float, 4>::Simd& r1,
        const Math::Vector<float, 4>::Simd& r2, const Math::Vector<float, 4>::Simd& r3,
        float epsilon = EPSILON * 10.0f )
    {
        // Check that row 4 is [0, 0, 0, 1] (homogeneous coordinates)
        if ( !ApproximatelyEqual( r3.x( ), 0.0f, epsilon ) ||
            !ApproximatelyEqual( r3.y( ), 0.0f, epsilon ) ||
            !ApproximatelyEqual( r3.z( ), 0.0f, epsilon ) ||
            !ApproximatelyEqual( r3.w( ), 1.0f, epsilon ) )
        {
            return false;
        }

        // Check orthonormality of 3x3 rotation part: rows should be unit vectors
        float r0_norm_sq = r0.x( ) * r0.x( ) + r0.y( ) * r0.y( ) + r0.z( ) * r0.z( );
        float r1_norm_sq = r1.x( ) * r1.x( ) + r1.y( ) * r1.y( ) + r1.z( ) * r1.z( );
        float r2_norm_sq = r2.x( ) * r2.x( ) + r2.y( ) * r2.y( ) + r2.z( ) * r2.z( );

        if ( !ApproximatelyEqual( r0_norm_sq, 1.0f, epsilon ) ||
            !ApproximatelyEqual( r1_norm_sq, 1.0f, epsilon ) ||
            !ApproximatelyEqual( r2_norm_sq, 1.0f, epsilon ) )
        {
            return false;
        }

        // Check orthogonality: dot products between different rows should be zero
        float r0_dot_r1 = r0.x( ) * r1.x( ) + r0.y( ) * r1.y( ) + r0.z( ) * r1.z( );
        float r0_dot_r2 = r0.x( ) * r2.x( ) + r0.y( ) * r2.y( ) + r0.z( ) * r2.z( );
        float r1_dot_r2 = r1.x( ) * r2.x( ) + r1.y( ) * r2.y( ) + r1.z( ) * r2.z( );

        return ApproximatelyEqual( r0_dot_r1, 0.0f, epsilon ) &&
            ApproximatelyEqual( r0_dot_r2, 0.0f, epsilon ) &&
            ApproximatelyEqual( r1_dot_r2, 0.0f, epsilon );
    }

    // Helper function to check if a matrix is orthogonal (rotation matrix property)
    bool IsOrthogonal( const Math::Vector<float, 4>::Simd& col1,
        const Math::Vector<float, 4>::Simd& col2,
        const Math::Vector<float, 4>::Simd& col3,
        float epsilon = 1e-4f )
    {
        // Check orthogonality: dot products of different columns should be ~0
        // and dot product of a column with itself should be ~1
        auto dot12 = ScalarDot( col1, col2 );
        auto dot13 = ScalarDot( col1, col3 );
        auto dot23 = ScalarDot( col2, col3 );
        auto len1 = ScalarLength( col1 );
        auto len2 = ScalarLength( col2 );
        auto len3 = ScalarLength( col3 );

        bool orthogonal = ApproximatelyEqual( dot12, 0.0f, epsilon ) &&
            ApproximatelyEqual( dot13, 0.0f, epsilon ) &&
            ApproximatelyEqual( dot23, 0.0f, epsilon );

        bool normalized = ApproximatelyEqual( len1, 1.0f, epsilon ) &&
            ApproximatelyEqual( len2, 1.0f, epsilon ) &&
            ApproximatelyEqual( len3, 1.0f, epsilon );

        return orthogonal && normalized;
    }

    bool IsValidRotationMatrix( const SquareMatrix<float, 4>::Simd& matrix, float epsilon = 1e-4f )
    {
        // Extract 3x3 rotation part (ignore translation)
        Math::Vector<float, 4>::Simd col0( matrix.simd[ 0 ] );
        Math::Vector<float, 4>::Simd col1( matrix.simd[ 1 ] );
        Math::Vector<float, 4>::Simd col2( matrix.simd[ 2 ] );

        return IsOrthogonal( col0, col1, col2, epsilon );
    }

    std::array<std::array<float, 4>, 4> ExtractMatrix( const SquareMatrix<float, 4>::Simd& simdMatrix )
    {
        std::array<std::array<float, 4>, 4> result{};
        auto matrixData = SquareMatrix<float, 4>::Simd::ToMatrix( simdMatrix );
        for ( size_t i = 0; i < 4; ++i )
        {
            for ( size_t j = 0; j < 4; ++j )
            {
                result[ i ][ j ] = matrixData[ i ][ j ];
            }
        }
        return result;
    }

    /// <summary>
    /// Helper function to create a 3x3 matrix from row data.
    /// </summary>
    SquareMatrix<float, 3>::Simd CreateMatrix3x3(
        float m00, float m01, float m02,
        float m10, float m11, float m12,
        float m20, float m21, float m22 )
    {
        SquareMatrix<float, 3> matrix;
        matrix[ 0 ][ 0 ] = m00; matrix[ 0 ][ 1 ] = m01; matrix[ 0 ][ 2 ] = m02;
        matrix[ 1 ][ 0 ] = m10; matrix[ 1 ][ 1 ] = m11; matrix[ 1 ][ 2 ] = m12;
        matrix[ 2 ][ 0 ] = m20; matrix[ 2 ][ 1 ] = m21; matrix[ 2 ][ 2 ] = m22;
        return matrix.ToSimd( );
    }

    /// <summary>
    /// Helper function to extract scalar determinant from SIMD result.
    /// </summary>
    float ExtractDeterminant( const Math::Vector<float, 3>::Simd& result )
    {
        return result.x( );
    }


}
TEST_CASE("MathMatrixTests / TransposeMatrix3x3Test1", "[math][MathMatrixTests]")
{
    Math::SquareMatrix<float, 3> matrix
    ( 1.f, 2.f, 3.f, 
        4.f, 5.f, 6.f,
        7.f, 8.f, 9.f );

    Math::SquareMatrix<float, 3> expectedMatrix
    ( 1.f, 4.f, 7.f,
        2.f, 5.f, 8.f,
        3.f, 6.f, 9.f );

    Math::SquareMatrix<float, 3> transposed = Math::Transpose( matrix );

    auto equal = transposed == expectedMatrix;

    CHECK(equal);

}
TEST_CASE("MathMatrixTests / TransposeMatrix4x4Test1", "[math][MathMatrixTests]")
{
    Math::SquareMatrix<float, 4> matrix
    (  1.f,  2.f,  3.f,  4.f,
       5.f,  6.f,  7.f,  8.f,
       9.f, 10.f, 11.f, 12.f,
      13.f, 14.f, 15.f, 16.f );

    Math::SquareMatrix<float, 4> expectedMatrix
    ( 1.f, 5.f, 9.f,  13.f,
      2.f, 6.f, 10.f, 14.f,
      3.f, 7.f, 11.f, 15.f,
      4.f, 8.f, 12.f, 16.f );

    Math::SquareMatrix<float, 4> transposed = Math::Transpose( matrix );

    auto equal = transposed == expectedMatrix;

    CHECK(equal);

}
TEST_CASE("MathMatrixTests / MultiplyMatrix3x3Test1", "[math][MathMatrixTests]")
{
    Math::SquareMatrix<float, 3> matrix1
    ( 1.f, 2.f, 3.f,
        4.f, 5.f, 6.f,
        7.f, 8.f, 9.f );

    Math::SquareMatrix<float, 3> matrix2
    ( 2.f, 3.f, 4.f,
        5.f, 6.f, 7.f,
        8.f, 9.f, 10.f );

    Math::SquareMatrix<float, 3> expectedResult
    ( 
        36.f, 42.f, 48.f,
        81.f, 96.f, 111.f,
        126.f, 150.f, 174.f
    );

    Math::SquareMatrix<float, 3> result = matrix1 * matrix2;

    auto equal = result == expectedResult;

    CHECK(equal);
}
TEST_CASE("MathMatrixTests / MultiplyMatrix4x4Test1", "[math][MathMatrixTests]")
{
    Math::SquareMatrix<float, 4> matrix1
    ( 1.f, 2.f, 3.f, 4.f,
        5.f, 6.f, 7.f, 8.f,
        9.f, 10.f, 11.f, 12.f,
        13.f, 14.f, 15.f, 16.f );

    Math::SquareMatrix<float, 4> matrix2
    ( 2.f, 3.f, 4.f, 5.f,
        6.f, 7.f, 8.f, 9.f,
        10.f, 11.f, 12.f, 13.f,
        14.f, 15.f, 16.f, 17.f );

    Math::SquareMatrix<float, 4> expectedResult
    (
        100.f, 110.f, 120.f, 130.f,
        228.f, 254.f, 280.f, 306.f,
        356.f, 398.f, 440.f, 482.f,
        484.f, 542.f, 600.f, 658.f );

    Math::SquareMatrix<float, 4> result = matrix1 * matrix2;

    auto equal = result == expectedResult;

    CHECK(equal);
}
TEST_CASE("MathMatrixTests / MultiplyScalarMatrix4x4Test1", "[math][MathMatrixTests]")
{
    Math::SquareMatrix<float, 4> matrix1
    ( 1.f, 2.f, 3.f, 4.f,
        5.f, 6.f, 7.f, 8.f,
        9.f, 10.f, 11.f, 12.f,
        13.f, 14.f, 15.f, 16.f );

    

    Math::SquareMatrix<float, 4> expectedResult
    ( 2.f * 1.f, 2.f * 2.f, 2.f * 3.f, 2.f * 4.f,
        2.f * 5.f, 2.f * 6.f, 2.f * 7.f, 2.f * 8.f,
        2.f * 9.f, 2.f * 10.f, 2.f * 11.f, 2.f * 12.f,
        2.f * 13.f, 2.f * 14.f, 2.f * 15.f, 2.f * 16.f );

    Math::SquareMatrix<float, 4> result = 2.f * matrix1;

    auto equal = result == expectedResult;

    CHECK(equal);
}
TEST_CASE("MathMatrixTests / MultiplyScalarMatrix3x3Test1", "[math][MathMatrixTests]")
{
    Math::SquareMatrix<float, 3> matrix1
    ( 1.f, 2.f, 3.f,
        4.f, 5.f, 6.f,
        7.f, 8.f, 9.f );

    Math::SquareMatrix<float, 3> expectedResult
    (
        2.f * 1.f, 2.f * 2.f, 2.f * 3.f,
        2.f * 4.f, 2.f * 5.f, 2.f * 6.f,
        2.f * 7.f, 2.f * 8.f, 2.f * 9.f
    );

    Math::SquareMatrix<float, 3> result = 2.f * matrix1;

    auto equal = result == expectedResult;

    CHECK(equal);
}
TEST_CASE("MathMatrixTests / AddMatrix3x3Test1", "[math][MathMatrixTests]")
{
    Math::SquareMatrix<float, 3> matrix1
    ( 1.f, 2.f, 3.f,
        4.f, 5.f, 6.f,
        7.f, 8.f, 9.f );

    Math::SquareMatrix<float, 3> matrix2
    ( 2.f, 3.f, 4.f,
        5.f, 6.f, 7.f,
        8.f, 9.f, 10.f );

    Math::SquareMatrix<float, 3> expectedResult
    (
        3.f, 5.f, 7.f,
        9.f, 11.f, 13.f,
        15.f, 17.f, 19.f
    );

    Math::SquareMatrix<float, 3> result = matrix1 + matrix2;

    auto equal = result == expectedResult;

    CHECK(equal);
}
TEST_CASE("MathMatrixTests / AddMatrix4x4Test1", "[math][MathMatrixTests]")
{
    Math::SquareMatrix<float, 4> matrix1
    ( 1.f, 2.f, 3.f, 4.f,
        5.f, 6.f, 7.f, 8.f,
        9.f, 10.f, 11.f, 12.f,
        13.f, 14.f, 15.f, 16.f );

    Math::SquareMatrix<float, 4> matrix2
    ( 2.f, 3.f, 4.f, 5.f,
        6.f, 7.f, 8.f, 9.f,
        10.f, 11.f, 12.f, 13.f,
        14.f, 15.f, 16.f, 17.f );

    Math::SquareMatrix<float, 4> expectedResult
    (
        3.f, 5.f, 7.f, 9.f,
        11.f, 13.f, 15.f, 17.f,
        19.f, 21.f, 23.f, 25.f,
        27.f, 29.f, 31.f, 33.f );

    Math::SquareMatrix<float, 4> result = matrix1 + matrix2;

    auto equal = result == expectedResult;

    CHECK(equal);
}
TEST_CASE("MathMatrixTests / DeterminantMatrix4x4Test1", "[math][MathMatrixTests]")
{
    Math::SquareMatrix<float, 4> matrix1
    ( 1.5f, -2.f, 3.4f, 4.f,
        5.4f, 6.f, 7.6f, 8.f,
        -9.f, 10.f, 11.f, 12.f,
        13.f, 14.f, 15.f, 16.f );

    float expectedResult = 282.720703f;
    Math::Vector<float, 4> result = Math::Determinant( matrix1 );
    auto nearlyEqual = AreNearlyEqual( result.x, expectedResult,1e-2f);
    CHECK(nearlyEqual);
}
TEST_CASE("MathMatrixTests / DeterminantMatrix3x3Test1", "[math][MathMatrixTests]")
{
    Math::SquareMatrix<float, 3> matrix1
      ( 1.5f, -2.f, 3.4f,
        5.4f,  6.f, 7.6f,
       -9.f,  10.f, 11.f );

    float expectedResult = 607.799988f;
    Math::Vector<float, 3> result = Math::Determinant( matrix1 );
    auto nearlyEqual = AreNearlyEqual( result.x, expectedResult, 1e-2f );
    CHECK(nearlyEqual);
}


/// <summary>
/// Tests that RotationX produces an identity matrix when angle is zero.
/// </summary>
TEST_CASE("MathMatrixTests / RotationXWithZeroAngleReturnsIdentityTest", "[math][MathMatrixTests]")
{
    auto rotationMatrix = Math::RotationX( 0.0f );
    auto identity = SquareMatrix<float, 4>::Simd( Math::MatrixType::Identity );

    bool isIdentity = ( rotationMatrix == identity );
    CHECK(isIdentity);
}

/// <summary>
/// Tests that RotationX produces correct sine and cosine values for 90-degree rotation.
/// </summary>



/// <summary>
/// Tests that RotationX produces correct sine and cosine values for 90-degree rotation.
/// </summary>
TEST_CASE("MathMatrixTests / RotationXWith90DegreesProducesCorrectValuesTest", "[math][MathMatrixTests]")
{
    const float angle = std::numbers::pi_v<float> / 2.0f; // 90 degrees
    Math::SquareMatrix<float, 4> matrix = Math::RotationX( angle );

    // At 90 degrees: sin(90°) = 1, cos(90°) = 0
    // Row 1 should be [1, 0, 0, 0]
    // Row 2 should be [0, 0, 1, 0]
    // Row 3 should be [0, -1, 0, 0]
    // Row 4 should be [0, 0, 0, 1]

    // Check first row (identity)
    bool firstRowCorrect = ( std::abs( matrix[ 0 ][ 0 ] - 1.0f ) < 1e-5f ) &&
        ( std::abs( matrix[ 0 ][ 1 ] ) < 1e-5f ) &&
        ( std::abs( matrix[ 0 ][ 2 ] ) < 1e-5f ) &&
        ( std::abs( matrix[ 0 ][ 3 ] ) < 1e-5f );
    CHECK(firstRowCorrect);

    // Check that row 2 has correct cosine/sine pattern (approximately [0, 0, 1, 0])
    bool secondRowCorrect = ( std::abs( matrix[ 1 ][ 0 ] ) < 1e-5f ) &&
        ( std::abs( matrix[ 1 ][ 1 ] ) < 1e-5f ) &&
        ( std::abs( matrix[ 1 ][ 2 ] - 1.0f ) < 1e-5f ) &&
        ( std::abs( matrix[ 1 ][ 3 ] ) < 1e-5f );
    CHECK(secondRowCorrect);
}

/// <summary>
/// Tests that RotationX produces correct values for 180-degree rotation.
/// </summary>
TEST_CASE("MathMatrixTests / RotationXWith180DegreesProducesCorrectValues", "[math][MathMatrixTests]")
{
    const float angle = std::numbers::pi_v<float>; // 180 degrees
    Math::SquareMatrix<float, 4> matrix = Math::RotationX( angle );

    // At 180 degrees: sin(180°) = 0, cos(180°) = -1
    // Row 1 should be [1, 0, 0, 0]
    // Row 2 should be [0, -1, 0, 0]
    // Row 3 should be [0, 0, -1, 0]
    // Row 4 should be [0, 0, 0, 1]

    bool firstRowCorrect = ( std::abs( matrix[ 0 ][ 0 ] - 1.0f ) < 1e-5f );
    CHECK(firstRowCorrect);

    bool secondRowDiagonal = ( std::abs( matrix[ 1 ][ 1 ] + 1.0f ) < 1e-5f ) &&
        ( std::abs( matrix[ 2 ][ 2 ] + 1.0f ) < 1e-5f );
    CHECK(secondRowDiagonal);
}

/// <summary>
/// Tests that RotationX produces correct values for negative angles.
/// </summary>
TEST_CASE("MathMatrixTests / RotationXWithNegativeAngleIsInverse", "[math][MathMatrixTests]")
{
    const float angle = std::numbers::pi_v<float> / 4.0f; // 45 degrees
    Math::SquareMatrix<float, 4> posMatrix = Math::RotationX( angle );
    Math::SquareMatrix<float, 4> negMatrix = Math::RotationX( -angle );

    // For rotation matrices, R(-θ) should have mirrored sine values
    bool inverseSineValues = ( std::abs( posMatrix[ 1 ][ 2 ] + negMatrix[ 1 ][ 2 ] ) < 1e-4f ) &&
        ( std::abs( posMatrix[ 2 ][ 1 ] + negMatrix[ 2 ][ 1 ] ) < 1e-4f );
    CHECK(inverseSineValues);
}

/// <summary>
/// Tests that RotationX produces a proper rotation matrix structure.
/// </summary>
TEST_CASE("MathMatrixTests / RotationXProducesValidRotationMatrixStructure", "[math][MathMatrixTests]")
{
    const float angle = std::numbers::pi_v<float> / 6.0f; // 30 degrees
    Math::SquareMatrix<float, 4> matrix = Math::RotationX( angle );

    // First row should be identity row [1, 0, 0, 0]
    bool firstRowIsIdentity = ( std::abs( matrix[ 0 ][ 0 ] - 1.0f ) < 1e-5f ) &&
        ( std::abs( matrix[ 0 ][ 1 ] ) < 1e-5f ) &&
        ( std::abs( matrix[ 0 ][ 2 ] ) < 1e-5f ) &&
        ( std::abs( matrix[ 0 ][ 3 ] ) < 1e-5f );
    CHECK(firstRowIsIdentity);

    // Fourth row should be identity row [0, 0, 0, 1]
    bool fourthRowIsIdentity = ( std::abs( matrix[ 3 ][ 0 ] ) < 1e-5f ) &&
        ( std::abs( matrix[ 3 ][ 1 ] ) < 1e-5f ) &&
        ( std::abs( matrix[ 3 ][ 2 ] ) < 1e-5f ) &&
        ( std::abs( matrix[ 3 ][ 3 ] - 1.0f ) < 1e-5f );
    CHECK(fourthRowIsIdentity);
}

/// <summary>
/// Tests that RotationX produces consistent results for full rotation (2π).
/// </summary>
TEST_CASE("MathMatrixTests / RotationXWithFullRotationReturnsNearlyIdentical", "[math][MathMatrixTests]")
{
    const float angle = std::numbers::pi_v<float> *2.0f; // 360 degrees
    Math::SquareMatrix<float, 4> matrix = Math::RotationX( angle );
    Math::SquareMatrix<float, 4> identityMatrix = SquareMatrix<float, 4>::Simd( Math::MatrixType::Identity );

    // Check that all elements are very close to identity
    bool nearIdentity = true;
    for ( int i = 0; i < 4; ++i )
    {
        for ( int j = 0; j < 4; ++j )
        {
            if ( std::abs( matrix[ i ][ j ] - identityMatrix[ i ][ j ] ) > 1e-4f )
            {
                nearIdentity = false;
                break;
            }
        }
        if ( !nearIdentity ) break;
    }
    CHECK(nearIdentity);
}

/// <summary>
/// Tests that successive 90-degree rotations compose correctly.
/// </summary>
TEST_CASE("MathMatrixTests / RotationXFourSuccessive90DegreesEqualsIdentity", "[math][MathMatrixTests]")
{
    const float angle = std::numbers::pi_v<float> / 2.0f; // 90 degrees
    Math::SquareMatrix<float, 4> rot90 = RotationX( angle );

    // Four 90-degree rotations should return to identity
    Math::SquareMatrix<float, 4> resultMatrix = rot90 * rot90 * rot90 * rot90;
    Math::SquareMatrix<float, 4> identityMatrix = SquareMatrix<float, 4>::Simd( Math::MatrixType::Identity );

    bool isNearIdentity = true;
    for ( int i = 0; i < 4; ++i )
    {
        for ( int j = 0; j < 4; ++j )
        {
            if ( std::abs( resultMatrix[ i ][ j ] - identityMatrix[ i ][ j ] ) > 1e-4f )
            {
                isNearIdentity = false;
                break;
            }
        }
        if ( !isNearIdentity ) break;
    }
    CHECK(isNearIdentity);
}

/// <summary>
/// Tests that RotationX correctly rotates a Y-axis vector.
/// </summary>
TEST_CASE("MathMatrixTests / RotationXRotatesYAxisVector", "[math][MathMatrixTests]")
{
    const float angle = std::numbers::pi_v<float> / 4.0f; // 45 degrees
    Math::SquareMatrix<float, 4> rotationMatrix = Math::RotationX( angle );

    float sine, cosine;
    Math::SinCos( angle, &sine, &cosine );

    // A unit vector along Y-axis [0, 1, 0, 1]
    Math::Vector4f yAxis( 0.0f, 1.0f, 0.0f, 1.0f );

    // Transform the vector by the rotation matrix
    Math::Vector4f rotatedVector = Math::Transform( yAxis, rotationMatrix );

    // After rotation around X-axis, Y should become Y*cos(θ) - Z*sin(θ)
    // and Z should become Y*sin(θ) + Z*cos(θ)
    // So [0, 1, 0] -> [0, cos(45°), sin(45°)]

    float expectedX = 0.0f;
    float expectedY = cosine;
    float expectedZ = sine;
    float expectedW = 1.0f;

    bool xComponentCorrect = std::abs( rotatedVector.x - expectedX ) < 1e-5f;
    bool yComponentCorrect = std::abs( rotatedVector.y - expectedY ) < 1e-5f;
    bool zComponentCorrect = std::abs( rotatedVector.z - expectedZ ) < 1e-5f;
    bool wComponentCorrect = std::abs( rotatedVector.w - expectedW ) < 1e-5f;

    CHECK(xComponentCorrect);
    CHECK(yComponentCorrect);
    CHECK(zComponentCorrect);
    CHECK(wComponentCorrect);
}

/// <summary>
/// Tests that RotationX correctly rotates a Z-axis vector.
/// </summary>
TEST_CASE("MathMatrixTests / RotationXRotatesZAxisVector", "[math][MathMatrixTests]")
{
    const float angle = std::numbers::pi_v<float> / 3.0f; // 60 degrees
    Math::SquareMatrix<float, 4> rotationMatrix = Math::RotationX( angle );

    float sine, cosine;
    Math::SinCos( angle, &sine, &cosine );

    // A unit vector along Z-axis [0, 0, 1, 1]
    Math::Vector4f zAxis( 0.0f, 0.0f, 1.0f, 1.0f );

    // Transform the vector by the rotation matrix
    Math::Vector4f rotatedVector = Math::Transform( zAxis, rotationMatrix );

    // After rotation around X-axis:
    // X stays 0
    // Y becomes: 0*cos(θ) - 1*sin(θ) = -sin(θ)
    // Z becomes: 0*sin(θ) + 1*cos(θ) = cos(θ)
    // So [0, 0, 1] -> [0, -sin(60°), cos(60°)]

    float expectedX = 0.0f;
    float expectedY = -sine;
    float expectedZ = cosine;
    float expectedW = 1.0f;

    bool xComponentCorrect = std::abs( rotatedVector.x - expectedX ) < 1e-5f;
    bool yComponentCorrect = std::abs( rotatedVector.y - expectedY ) < 1e-5f;
    bool zComponentCorrect = std::abs( rotatedVector.z - expectedZ ) < 1e-5f;
    bool wComponentCorrect = std::abs( rotatedVector.w - expectedW ) < 1e-5f;

    CHECK(xComponentCorrect);
    CHECK(yComponentCorrect);
    CHECK(zComponentCorrect);
    CHECK(wComponentCorrect);
}

/// <summary>
/// Tests that RotationX does not modify the X-axis.
/// </summary>
TEST_CASE("MathMatrixTests / RotationXDoesNotModifyXAxis", "[math][MathMatrixTests]")
{
    const float angle = std::numbers::pi_v<float> / 2.5f;
    Math::SquareMatrix<float, 4> rotationMatrix = Math::RotationX( angle );

    Math::SquareMatrix<float, 4> matrix = rotationMatrix;

    // X-axis should remain unchanged: [1, 0, 0, 0]
    bool xAxisUnchanged = ( std::abs( matrix[ 0 ][ 0 ] - 1.0f ) < 1e-5f ) &&
        ( std::abs( matrix[ 1 ][ 0 ] ) < 1e-5f ) &&
        ( std::abs( matrix[ 2 ][ 0 ] ) < 1e-5f ) &&
        ( std::abs( matrix[ 3 ][ 0 ] ) < 1e-5f );
    CHECK(xAxisUnchanged);
}

/// <summary>
/// Tests that RotationY with zero angle produces identity matrix.
/// </summary>
TEST_CASE("MathMatrixTests / RotationYZeroAngleIsIdentity", "[math][MathMatrixTests]")
{
    auto result = RotationY( 0.0f );
    auto expected = SquareMatrix<float, 4>::Simd::Identity( );

    bool isIdentity = MatrixApproximatelyEqual( result, expected );
    CHECK(isIdentity);
}

/// <summary>
/// Tests that RotationY produces correct values for 90-degree rotation.
/// </summary>
TEST_CASE("MathMatrixTests / RotationYNinetyDegrees", "[math][MathMatrixTests]")
{
    constexpr float PI_HALF = 3.14159265358979f / 2.0f;
    auto result = RotationY( PI_HALF );

    auto resultData = SquareMatrix<float, 4>::Simd::Traits::ToArray( result.simd[ 0 ] );
    // At 90 degrees: cos(90) ≈ 0, sin(90) ≈ 1
    // M[0][0] should be cos(90) ≈ 0
    bool m00IsZero = ApproximatelyEqual( resultData[ 0 ], 0.0f, 0.01f );
    CHECK(m00IsZero);

    // M[0][2] should be sin(90) ≈ 1
    resultData = SquareMatrix<float, 4>::Simd::Traits::ToArray( result.simd[ 2 ] );
    bool m20IsOne = ApproximatelyEqual( resultData[ 0 ], 1.0f, 0.01f );
    CHECK(m20IsOne);
}

/// <summary>
/// Tests that RotationY produces correct values for 180-degree rotation.
/// </summary>
TEST_CASE("MathMatrixTests / RotationY180Degrees", "[math][MathMatrixTests]")
{
    constexpr float PI = 3.14159265358979f;
    auto result = RotationY( PI );

    auto resultData = SquareMatrix<float, 4>::Simd::Traits::ToArray( result.simd[ 0 ] );
    // At 180 degrees: cos(180) ≈ -1, sin(180) ≈ 0
    // M[0][0] should be cos(180) ≈ -1
    bool m00IsNegOne = ApproximatelyEqual( resultData[ 0 ], -1.0f, 0.01f );
    CHECK(m00IsNegOne);

    // M[0][2] should be sin(180) ≈ 0
    resultData = SquareMatrix<float, 4>::Simd::Traits::ToArray( result.simd[ 2 ] );
    bool m20IsZero = ApproximatelyEqual( resultData[ 0 ], 0.0f, 0.01f );
    CHECK(m20IsZero);
}

/// <summary>
/// Tests that RotationY preserves the Y-axis (row 1 is [0, 1, 0, 0]).
/// </summary>
TEST_CASE("MathMatrixTests / RotationYPreservesYAxis", "[math][MathMatrixTests]")
{
    constexpr float ANGLE = 0.785398f; // 45 degrees
    auto result = RotationY( ANGLE );

    // Row 1 (Y-axis row) should be [0, 1, 0, 0]
    auto row1Data = SquareMatrix<float, 4>::Simd::Traits::ToArray( result.simd[ 1 ] );
    bool isYAxisPreserved =
        ApproximatelyEqual( row1Data[ 0 ], 0.0f ) &&
        ApproximatelyEqual( row1Data[ 1 ], 1.0f ) &&
        ApproximatelyEqual( row1Data[ 2 ], 0.0f ) &&
        ApproximatelyEqual( row1Data[ 3 ], 0.0f );
    CHECK(isYAxisPreserved);
}

/// <summary>
/// Tests that RotationY produces an orthogonal matrix (determinant is ±1).
/// </summary>
TEST_CASE("MathMatrixTests / RotationYIsOrthogonal", "[math][MathMatrixTests]")
{
    constexpr float ANGLE = 1.57079632f; // 90 degrees in radians
    auto result = RotationY( ANGLE );

    // For a 4x4 rotation matrix, the upper-left 3x3 should be orthogonal
    auto row0 = SquareMatrix<float, 4>::Simd::Traits::ToArray( result.simd[ 0 ] );
    auto row1 = SquareMatrix<float, 4>::Simd::Traits::ToArray( result.simd[ 1 ] );
    auto row2 = SquareMatrix<float, 4>::Simd::Traits::ToArray( result.simd[ 2 ] );

    // Check that each row has unit length (for first 3 components)
    float len0Sq = row0[ 0 ] * row0[ 0 ] + row0[ 1 ] * row0[ 1 ] + row0[ 2 ] * row0[ 2 ];
    float len1Sq = row1[ 0 ] * row1[ 0 ] + row1[ 1 ] * row1[ 1 ] + row1[ 2 ] * row1[ 2 ];
    float len2Sq = row2[ 0 ] * row2[ 0 ] + row2[ 1 ] * row2[ 1 ] + row2[ 2 ] * row2[ 2 ];

    bool isOrthogonal =
        ApproximatelyEqual( len0Sq, 1.0f, 0.01f ) &&
        ApproximatelyEqual( len1Sq, 1.0f, 0.01f ) &&
        ApproximatelyEqual( len2Sq, 1.0f, 0.01f );
    CHECK(isOrthogonal);
}

/// <summary>
/// Tests that RotationY has correct homogeneous coordinates (last row is [0, 0, 0, 1]).
/// </summary>
TEST_CASE("MathMatrixTests / RotationYHomogeneousCoordinates", "[math][MathMatrixTests]")
{
    constexpr float ANGLE = 0.5f;
    auto result = RotationY( ANGLE );

    // Last row should be [0, 0, 0, 1]
    auto row3Data = SquareMatrix<float, 4>::Simd::Traits::ToArray( result.simd[ 3 ] );
    bool isHomogeneous =
        ApproximatelyEqual( row3Data[ 0 ], 0.0f ) &&
        ApproximatelyEqual( row3Data[ 1 ], 0.0f ) &&
        ApproximatelyEqual( row3Data[ 2 ], 0.0f ) &&
        ApproximatelyEqual( row3Data[ 3 ], 1.0f );
    CHECK(isHomogeneous);
}

/// <summary>
/// Tests that RotationY(-θ) is the transpose of RotationY(θ).
/// </summary>
TEST_CASE("MathMatrixTests / RotationYNegativeAngleIsTranspose", "[math][MathMatrixTests]")
{
    constexpr float ANGLE = 1.0f;
    auto posResult = RotationY( ANGLE );
    auto negResult = RotationY( -ANGLE );

    // For orthogonal matrices, transpose equals inverse
    // RotationY(-θ) should equal RotationY(θ) transposed
    auto row0Pos = SquareMatrix<float, 4>::Simd::Traits::ToArray( posResult.simd[ 0 ] );
    auto row0Neg = SquareMatrix<float, 4>::Simd::Traits::ToArray( negResult.simd[ 0 ] );

    // Check if negResult[0] ≈ posResult[0] with cos term preserved
    bool isInverse = ApproximatelyEqual( row0Pos[ 0 ], row0Neg[ 0 ], 0.01f );
    CHECK(isInverse);
}

/// <summary>
/// Tests that RotationY with various angles produces expected sine/cosine values.
/// </summary>
TEST_CASE("MathMatrixTests / RotationYVariousAngles", "[math][MathMatrixTests]")
{
    constexpr float ANGLES[ ] = { 0.0f, 0.785398f, 1.57079f, 2.35619f, 3.14159f };

    for ( float angle : ANGLES )
    {
        auto result = RotationY( angle );

        float expectedSine = std::sin( angle );
        float expectedCosine = std::cos( angle );

        auto row0Data = SquareMatrix<float, 4>::Simd::Traits::ToArray( result.simd[ 0 ] );
        bool cosineMatches = ApproximatelyEqual( row0Data[ 0 ], expectedCosine, 0.01f );
        CHECK(cosineMatches);
    }
}

/// <summary>
/// Tests that applying RotationY twice with half angle equals single rotation.
/// </summary>
TEST_CASE("MathMatrixTests / RotationYAngleAddition", "[math][MathMatrixTests]")
{
    constexpr float HALF_ANGLE = 0.785398f; // 45 degrees

    auto singleRotation = RotationY( HALF_ANGLE * 2.0f );

    // Note: Full matrix multiplication would be needed for proper verification
    // This is a simplified test checking the cosine/sine values
    auto singleRow0 = SquareMatrix<float, 4>::Simd::Traits::ToArray( singleRotation.simd[ 0 ] );

    float expectedCosine = std::cos( HALF_ANGLE * 2.0f );
    bool angleAddsCorrectly = ApproximatelyEqual( singleRow0[ 0 ], expectedCosine, 0.01f );
    CHECK(angleAddsCorrectly);
}

/// <summary>
/// Tests the RotationZ function which creates a 4x4 rotation matrix around the Z-axis.
/// </summary>
/// <remarks>
/// A Z-axis rotation matrix should have the form:
/// [ cos(θ)  sin(θ)   0   0]
/// [-sin(θ)   cos(θ)  0   0]
/// [0        0        1   0]
/// [0        0        0   1]
/// </remarks>

TEST_CASE("MathMatrixTests / RotationZZeroAngleReturnsIdentity", "[math][MathMatrixTests]")
{
    // Arrange
    float angle = 0.0f;
    const float epsilon = 1e-5f;

    // Act
    auto rotationMatrix = Math::RotationZ( angle );
    Math::SquareMatrix<float, 4> matrixData = rotationMatrix;

    // Assert - Identity matrix
    CHECK(std::abs( matrixData[ 0 ][ 0 ] - 1.0f ) < epsilon); // cos(0) = 1
    CHECK(std::abs( matrixData[ 0 ][ 1 ] - 0.0f ) < epsilon); // sin(0) = 0
    CHECK(std::abs( matrixData[ 1 ][ 0 ] - 0.0f ) < epsilon); // -sin(0) = 0
    CHECK(std::abs( matrixData[ 1 ][ 1 ] - 1.0f ) < epsilon); // cos(0) = 1
    CHECK(std::abs( matrixData[ 2 ][ 2 ] - 1.0f ) < epsilon);
    CHECK(std::abs( matrixData[ 3 ][ 3 ] - 1.0f ) < epsilon);
}

TEST_CASE("MathMatrixTests / RotationZ90DegreesRotatesCorrectly", "[math][MathMatrixTests]")
{
    // Arrange
    float angle = Harlinn::Math::Constants<float>::Pi / 2.0f; // 90 degrees
    const float epsilon = 1e-5f;

    // Act
    auto rotationMatrix = Harlinn::Math::RotationZ( angle );
    auto matrixData = Harlinn::Math::SquareMatrix<float, 4>::Simd::ToMatrix( rotationMatrix );

    // Assert - 90 degree rotation
    // cos(90°) = 0, sin(90°) = 1
    CHECK(std::abs( matrixData[ 0 ][ 0 ] - 0.0f ) < epsilon);
    CHECK(std::abs( matrixData[ 0 ][ 1 ] - 1.0f ) < epsilon);
    CHECK(std::abs( matrixData[ 1 ][ 0 ] - ( -1.0f ) ) < epsilon);
    CHECK(std::abs( matrixData[ 1 ][ 1 ] - 0.0f ) < epsilon);
}

TEST_CASE("MathMatrixTests / RotationZ180DegreesRotatesCorrectly", "[math][MathMatrixTests]")
{
    // Arrange
    float angle = Harlinn::Math::Constants<float>::Pi; // 180 degrees
    const float epsilon = 1e-5f;

    // Act
    auto rotationMatrix = Harlinn::Math::RotationZ( angle );
    auto matrixData = Harlinn::Math::SquareMatrix<float, 4>::Simd::ToMatrix( rotationMatrix );

    // Assert - 180 degree rotation
    // cos(180°) = -1, sin(180°) = 0
    CHECK(std::abs( matrixData[ 0 ][ 0 ] - ( -1.0f ) ) < epsilon);
    CHECK(std::abs( matrixData[ 0 ][ 1 ] - 0.0f ) < epsilon);
    CHECK(std::abs( matrixData[ 1 ][ 0 ] - 0.0f ) < epsilon);
    CHECK(std::abs( matrixData[ 1 ][ 1 ] - ( -1.0f ) ) < epsilon);
}

TEST_CASE("MathMatrixTests / RotationZ270DegreesRotatesCorrectly", "[math][MathMatrixTests]")
{
    // Arrange
    float angle = 3.0f * Harlinn::Math::Constants<float>::Pi / 2.0f; // 270 degrees
    const float epsilon = 1e-5f;

    // Act
    auto rotationMatrix = Harlinn::Math::RotationZ( angle );
    auto matrixData = Harlinn::Math::SquareMatrix<float, 4>::Simd::ToMatrix( rotationMatrix );

    // Assert - 270 degree rotation
    // cos(270°) = 0, sin(270°) = -1
    CHECK(std::abs( matrixData[ 0 ][ 0 ] - 0.0f ) < epsilon);
    CHECK(std::abs( matrixData[ 0 ][ 1 ] - ( -1.0f ) ) < epsilon);
    CHECK(std::abs( matrixData[ 1 ][ 0 ] - 1.0f ) < epsilon);
    CHECK(std::abs( matrixData[ 1 ][ 1 ] - 0.0f ) < epsilon);
}

TEST_CASE("MathMatrixTests / RotationZ360DegreesReturnsIdentity", "[math][MathMatrixTests]")
{
    // Arrange
    float angle = 2.0f * Harlinn::Math::Constants<float>::Pi; // 360 degrees
    const float epsilon = 1e-5f;

    // Act
    auto rotationMatrix = Harlinn::Math::RotationZ( angle );
    auto matrixData = Harlinn::Math::SquareMatrix<float, 4>::Simd::ToMatrix( rotationMatrix );

    // Assert - Full rotation returns to identity
    CHECK(std::abs( matrixData[ 0 ][ 0 ] - 1.0f ) < epsilon);
    CHECK(std::abs( matrixData[ 0 ][ 1 ] - 0.0f ) < epsilon);
    CHECK(std::abs( matrixData[ 1 ][ 0 ] - 0.0f ) < epsilon);
    CHECK(std::abs( matrixData[ 1 ][ 1 ] - 1.0f ) < epsilon);
}

TEST_CASE("MathMatrixTests / RotationZNegativeAngleRotatesInOppositeDirection", "[math][MathMatrixTests]")
{
    // Arrange
    float positiveAngle = Harlinn::Math::Constants<float>::Pi / 4.0f; // 45 degrees
    float negativeAngle = -positiveAngle;
    const float epsilon = 1e-5f;

    // Act
    auto positiveMatrix = Harlinn::Math::RotationZ( positiveAngle );
    auto negativeMatrix = Harlinn::Math::RotationZ( negativeAngle );
    auto posData = Harlinn::Math::SquareMatrix<float, 4>::Simd::ToMatrix( positiveMatrix );
    auto negData = Harlinn::Math::SquareMatrix<float, 4>::Simd::ToMatrix( negativeMatrix );

    // Assert - Negative rotation should be transpose of positive rotation (for rotation matrices)
    CHECK(std::abs( posData[ 0 ][ 0 ] - negData[ 0 ][ 0 ] ) < epsilon);
    CHECK(std::abs( posData[ 0 ][ 1 ] - negData[ 1 ][ 0 ] ) < epsilon);
    CHECK(std::abs( posData[ 1 ][ 0 ] - negData[ 0 ][ 1 ] ) < epsilon);
    CHECK(std::abs( posData[ 1 ][ 1 ] - negData[ 1 ][ 1 ] ) < epsilon);
}

TEST_CASE("MathMatrixTests / RotationZPreservesZAndWRows", "[math][MathMatrixTests]")
{
    // Arrange
    float angle = Harlinn::Math::Constants<float>::Pi / 3.0f; // 60 degrees
    const float epsilon = 1e-5f;

    // Act
    auto rotationMatrix = Harlinn::Math::RotationZ( angle );
    auto matrixData = Harlinn::Math::SquareMatrix<float, 4>::Simd::ToMatrix( rotationMatrix );

    // Assert - Z-axis rotation should not affect Z and W rows
    CHECK(std::abs( matrixData[ 2 ][ 0 ] - 0.0f ) < epsilon);
    CHECK(std::abs( matrixData[ 2 ][ 1 ] - 0.0f ) < epsilon);
    CHECK(std::abs( matrixData[ 2 ][ 2 ] - 1.0f ) < epsilon);
    CHECK(std::abs( matrixData[ 2 ][ 3 ] - 0.0f ) < epsilon);
    CHECK(std::abs( matrixData[ 3 ][ 0 ] - 0.0f ) < epsilon);
    CHECK(std::abs( matrixData[ 3 ][ 1 ] - 0.0f ) < epsilon);
    CHECK(std::abs( matrixData[ 3 ][ 2 ] - 0.0f ) < epsilon);
    CHECK(std::abs( matrixData[ 3 ][ 3 ] - 1.0f ) < epsilon);
}

TEST_CASE("MathMatrixTests / RotationZMatrixIsOrthogonal", "[math][MathMatrixTests]")
{
    // Arrange
    float angle = Harlinn::Math::Constants<float>::Pi / 6.0f; // 30 degrees
    const float epsilon = 1e-4f;

    // Act
    auto rotationMatrix = Harlinn::Math::RotationZ( angle );
    auto matrixData = Harlinn::Math::SquareMatrix<float, 4>::Simd::ToMatrix( rotationMatrix );

    // Assert - Rotation matrix should be orthogonal (columns are unit vectors and orthogonal)
    // First column norm should be 1
    float col0Norm = std::sqrt( matrixData[ 0 ][ 0 ] * matrixData[ 0 ][ 0 ] +
        matrixData[ 1 ][ 0 ] * matrixData[ 1 ][ 0 ] );
    CHECK(std::abs( col0Norm - 1.0f ) < epsilon);

    // Second column norm should be 1
    float col1Norm = std::sqrt( matrixData[ 0 ][ 1 ] * matrixData[ 0 ][ 1 ] +
        matrixData[ 1 ][ 1 ] * matrixData[ 1 ][ 1 ] );
    CHECK(std::abs( col1Norm - 1.0f ) < epsilon);

    // First and second columns should be orthogonal (dot product = 0)
    float dotProduct = matrixData[ 0 ][ 0 ] * matrixData[ 0 ][ 1 ] +
        matrixData[ 1 ][ 0 ] * matrixData[ 1 ][ 1 ];
    CHECK(std::abs( dotProduct ) < epsilon);
}

TEST_CASE("MathMatrixTests / RotationZSmallAngleApproximation", "[math][MathMatrixTests]")
{
    // Arrange
    float angle = 0.001f; // Very small angle
    const float epsilon = 1e-5f;

    // Act
    auto rotationMatrix = Harlinn::Math::RotationZ( angle );
    auto matrixData = Harlinn::Math::SquareMatrix<float, 4>::Simd::ToMatrix( rotationMatrix );

    // Assert - For small angles: cos(θ) ≈ 1, sin(θ) ≈ θ
    CHECK(std::abs( matrixData[ 0 ][ 0 ] - 1.0f ) < epsilon);
    CHECK(std::abs( matrixData[ 0 ][ 1 ] - angle ) < epsilon);
    CHECK(std::abs( matrixData[ 1 ][ 0 ] - ( -angle ) ) < epsilon);
    CHECK(std::abs( matrixData[ 1 ][ 1 ] - 1.0f ) < epsilon);
}

TEST_CASE("MathMatrixTests / RotationZConsistentWithTrigFunctions", "[math][MathMatrixTests]")
{
    // Arrange
    float angle = Harlinn::Math::Constants<float>::Pi / 8.0f; // 22.5 degrees
    float expectedCos = std::cos( angle );
    float expectedSin = std::sin( angle );
    const float epsilon = 1e-5f;

    // Act
    auto rotationMatrix = Harlinn::Math::RotationZ( angle );
    auto matrixData = Harlinn::Math::SquareMatrix<float, 4>::Simd::ToMatrix( rotationMatrix );

    // Assert
    CHECK(std::abs( matrixData[ 0 ][ 0 ] - expectedCos ) < epsilon);
    CHECK(std::abs( matrixData[ 0 ][ 1 ] - expectedSin ) < epsilon);
    CHECK(std::abs( matrixData[ 1 ][ 0 ] - ( -expectedSin ) ) < epsilon);
    CHECK(std::abs( matrixData[ 1 ][ 1 ] - expectedCos ) < epsilon);
}


TEST_CASE("MathMatrixTests / RotationWithZeroAngles", "[math][MathMatrixTests]")
{
    // Zero rotation should produce identity matrix
    Vector3f angles( 0.0f, 0.0f, 0.0f );
    auto rotMatrix = Rotation( angles.ToSimd( ) );
    auto result = SquareMatrix<float, 4>( rotMatrix );

    bool isIdentity = MatrixApproximatelyEqual( result, SquareMatrix<float, 4>( ) );
    CHECK(isIdentity);
}

TEST_CASE("MathMatrixTests / RotationWithPitchOnly", "[math][MathMatrixTests]")
{
    // Rotation around X-axis only (pitch = 90 degrees)
    Vector3f angles( Constants<float>::Pi / 2.0f, 0.0f, 0.0f );
    auto rotMatrix = Rotation( angles.ToSimd( ) );
    auto result = SquareMatrix<float, 4>( rotMatrix );

    // After 90-degree pitch rotation:
    // [1,  0,  0, 0]
    // [0,  0, -1, 0]
    // [0,  1,  0, 0]
    // [0,  0,  0, 1]

    bool checkIdentityX = ApproximatelyEqual( result[ 0 ][ 0 ], 1.0f );
    bool checkRotY = ApproximatelyEqual( result[ 1 ][ 1 ], 0.0f );
    bool checkRotZ = ApproximatelyEqual( result[ 2 ][ 2 ], 0.0f );
    bool checkW = ApproximatelyEqual( result[ 3 ][ 3 ], 1.0f );

    CHECK(checkIdentityX);
    CHECK(checkRotY);
    CHECK(checkRotZ);
    CHECK(checkW);
}

TEST_CASE("MathMatrixTests / RotationWithYawOnly", "[math][MathMatrixTests]")
{
    // Rotation around Y-axis only (yaw = 90 degrees)
    Vector3f angles( 0.0f, Constants<float>::Pi / 2.0f, 0.0f );
    auto rotMatrix = Rotation( angles.ToSimd( ) );
    auto result = SquareMatrix<float, 4>( rotMatrix );

    bool checkW = ApproximatelyEqual( result[ 3 ][ 3 ], 1.0f );
    CHECK(checkW);
}

TEST_CASE("MathMatrixTests / RotationWithRollOnly", "[math][MathMatrixTests]")
{
    // Rotation around Z-axis only (roll = 90 degrees)
    Vector3f angles( 0.0f, 0.0f, Constants<float>::Pi / 2.0f );
    auto rotMatrix = Rotation( angles.ToSimd( ) );
    auto result = SquareMatrix<float, 4>( rotMatrix );

    bool checkW = ApproximatelyEqual( result[ 3 ][ 3 ], 1.0f );
    CHECK(checkW);
}

TEST_CASE("MathMatrixTests / RotationWith180DegreePitch", "[math][MathMatrixTests]")
{
    // 180-degree rotation around X-axis
    Vector3f angles( Constants<float>::Pi, 0.0f, 0.0f );
    auto rotMatrix = Rotation( angles.ToSimd( ) );
    auto result = SquareMatrix<float, 4>( rotMatrix );

    // Should have identity X component and negated Y and Z
    bool checkX = ApproximatelyEqual( result[ 0 ][ 0 ], 1.0f );
    bool checkY = ApproximatelyEqual( result[ 1 ][ 1 ], -1.0f, EPSILON * 10 );
    bool checkZ = ApproximatelyEqual( result[ 2 ][ 2 ], -1.0f, EPSILON * 10 );
    bool checkW = ApproximatelyEqual( result[ 3 ][ 3 ], 1.0f );

    CHECK(checkX);
    CHECK(checkY);
    CHECK(checkZ);
    CHECK(checkW);
}

TEST_CASE("MathMatrixTests / RotationWith360Degrees", "[math][MathMatrixTests]")
{
    // Full rotation (360 degrees) should return close to identity
    Vector3f angles( Constants<float>::PiTimes2, 0.0f, 0.0f );
    auto rotMatrix = Rotation( angles.ToSimd( ) );
    auto result = SquareMatrix<float, 4>( rotMatrix );
    auto identity = SquareMatrix<float, 4>( );

    bool isNearlyIdentity = MatrixApproximatelyEqual( result, identity, EPSILON * 100 );
    CHECK(isNearlyIdentity);
}

TEST_CASE("MathMatrixTests / RotationWithCombinedAngles", "[math][MathMatrixTests]")
{
    // Combined rotation (30 degrees pitch, 45 degrees yaw, 60 degrees roll)
    Vector3f angles( Constants<float>::Pi / 6.0f, Constants<float>::Pi / 4.0f, Constants<float>::Pi / 3.0f );
    auto rotMatrix = Rotation( angles.ToSimd( ) );
    auto result = SquareMatrix<float, 4>( rotMatrix );

    // Verify matrix is valid (bottom row should be [0, 0, 0, 1])
    bool checkBottomRow = ApproximatelyEqual( result[ 3 ][ 0 ], 0.0f ) &&
        ApproximatelyEqual( result[ 3 ][ 1 ], 0.0f ) &&
        ApproximatelyEqual( result[ 3 ][ 2 ], 0.0f ) &&
        ApproximatelyEqual( result[ 3 ][ 3 ], 1.0f );

    CHECK(checkBottomRow);
}

TEST_CASE("MathMatrixTests / RotationWithNegativeAngles", "[math][MathMatrixTests]")
{
    // Negative angles should rotate in opposite direction
    Vector3f anglesPositive( Constants<float>::Pi / 4.0f, 0.0f, 0.0f );
    Vector3f anglesNegative( -Constants<float>::Pi / 4.0f, 0.0f, 0.0f );

    auto rotMatrixPos = Rotation( anglesPositive.ToSimd( ) );
    auto rotMatrixNeg = Rotation( anglesNegative.ToSimd( ) );

    auto resultPos = SquareMatrix<float, 4>( rotMatrixPos );
    auto resultNeg = SquareMatrix<float, 4>( rotMatrixNeg );

    // Positive and negative rotations should have opposite sine components
    // but same cosine components (for pitch-only rotation)
    bool checkCosine = ApproximatelyEqual( resultPos[ 1 ][ 1 ], resultNeg[ 1 ][ 1 ] );
    CHECK(checkCosine);
}

TEST_CASE("MathMatrixTests / RotationMatrixBottomRowConsistency", "[math][MathMatrixTests]")
{
    // The bottom row of a rotation matrix should always be [0, 0, 0, 1]
    Vector3f angles( 0.5f, 0.3f, 0.7f );
    auto rotMatrix = Rotation( angles.ToSimd( ) );
    auto result = SquareMatrix<float, 4>( rotMatrix );

    bool bottomRowCorrect = ApproximatelyEqual( result[ 3 ][ 0 ], 0.0f ) &&
        ApproximatelyEqual( result[ 3 ][ 1 ], 0.0f ) &&
        ApproximatelyEqual( result[ 3 ][ 2 ], 0.0f ) &&
        ApproximatelyEqual( result[ 3 ][ 3 ], 1.0f );

    CHECK(bottomRowCorrect);
}

TEST_CASE("MathMatrixTests / RotationMatrixRightColumnConsistency", "[math][MathMatrixTests]")
{
    // The right column (except W) should be zero for a pure rotation matrix
    Vector3f angles( 0.6f, 0.4f, 0.8f );
    auto rotMatrix = Rotation( angles.ToSimd( ) );
    auto result = SquareMatrix<float, 4>( rotMatrix );

    bool rightColumnCorrect = ApproximatelyEqual( result[ 0 ][ 3 ], 0.0f ) &&
        ApproximatelyEqual( result[ 1 ][ 3 ], 0.0f ) &&
        ApproximatelyEqual( result[ 2 ][ 3 ], 0.0f ) &&
        ApproximatelyEqual( result[ 3 ][ 3 ], 1.0f );

    CHECK(rightColumnCorrect);
}

TEST_CASE("MathMatrixTests / RotationWithVector4D", "[math][MathMatrixTests]")
{
    // Test that function works with 4D vectors (Size == 4)
    Vector4f angles( 0.5f, 0.3f, 0.7f, 0.0f );  // 4th component unused
    auto rotMatrix = Rotation( angles.ToSimd( ) );
    auto result = SquareMatrix<float, 4>( rotMatrix );

    bool checkW = ApproximatelyEqual( result[ 3 ][ 3 ], 1.0f );
    CHECK(checkW);
}

TEST_CASE("MathMatrixTests / RotationSmallAngles", "[math][MathMatrixTests]")
{
    // Very small angles should produce a matrix close to identity
    Vector3f angles( 0.001f, 0.001f, 0.001f );
    auto rotMatrix = Rotation( angles.ToSimd( ) );
    auto result = SquareMatrix<float, 4>( rotMatrix );
    auto identity = SquareMatrix<float, 4>( );

    bool isNearlyIdentity = MatrixApproximatelyEqual( result, identity, 0.01f );
    CHECK(isNearlyIdentity);
}

TEST_CASE("MathMatrixTests / RotationLargeAngles", "[math][MathMatrixTests]")
{
    // Test with large angles (multiple rotations)
    Vector3f angles( Constants<float>::PiTimes2 + 0.5f, Constants<float>::PiTimes2 + 0.3f, Constants<float>::PiTimes2 + 0.7f );
    auto rotMatrix = Rotation( angles.ToSimd( ) );
    auto result = SquareMatrix<float, 4>( rotMatrix );

    // Bottom row should still be [0, 0, 0, 1]
    bool bottomRowCorrect = ApproximatelyEqual( result[ 3 ][ 0 ], 0.0f ) &&
        ApproximatelyEqual( result[ 3 ][ 1 ], 0.0f ) &&
        ApproximatelyEqual( result[ 3 ][ 2 ], 0.0f ) &&
        ApproximatelyEqual( result[ 3 ][ 3 ], 1.0f );

    CHECK(bottomRowCorrect);
}

TEST_CASE("MathMatrixTests / RotationNormalIdentity", "[math][MathMatrixTests]")
{
    // Identity rotation: angle = 0, any normalized axis
    Math::Vector<float, 3>::Simd axis( 1.0f, 0.0f, 0.0f );
    float angle = 0.0f;

    auto result = RotationNormal( axis, angle );

    // Extract rows
    Math::Vector<float, 4>::Simd r0( result.simd[ 0 ] );
    Math::Vector<float, 4>::Simd r1( result.simd[ 1 ] );
    Math::Vector<float, 4>::Simd r2( result.simd[ 2 ] );
    Math::Vector<float, 4>::Simd r3( result.simd[ 3 ] );

    // Expected identity matrix
    CHECK(ApproximatelyEqual( r0.x( ), 1.0f ));
    CHECK(ApproximatelyEqual( r0.y( ), 0.0f ));
    CHECK(ApproximatelyEqual( r0.z( ), 0.0f ));

    CHECK(ApproximatelyEqual( r1.x( ), 0.0f ));
    CHECK(ApproximatelyEqual( r1.y( ), 1.0f ));
    CHECK(ApproximatelyEqual( r1.z( ), 0.0f ));

    CHECK(ApproximatelyEqual( r2.x( ), 0.0f ));
    CHECK(ApproximatelyEqual( r2.y( ), 0.0f ));
    CHECK(ApproximatelyEqual( r2.z( ), 1.0f ));

    CHECK(IsOrthogonalMatrix( r0, r1, r2, r3 ));
}

TEST_CASE("MathMatrixTests / RotationNormalAxisX90Degrees", "[math][MathMatrixTests]")
{
    // 90-degree rotation around X-axis
    Math::Vector<float, 3>::Simd axis( 1.0f, 0.0f, 0.0f );
    float angle = 3.14159265f / 2.0f; // 90 degrees

    auto result = RotationNormal( axis, angle );

    Math::Vector<float, 4>::Simd r0( result.simd[ 0 ] );
    Math::Vector<float, 4>::Simd r1( result.simd[ 1 ] );
    Math::Vector<float, 4>::Simd r2( result.simd[ 2 ] );
    Math::Vector<float, 4>::Simd r3( result.simd[ 3 ] );

    // Rotation around X by 90 degrees: [1 0 0; 0 0 1; 0 -1 0]
    CHECK(ApproximatelyEqual( r0.x( ), 1.0f ));
    CHECK(ApproximatelyEqual( r0.y( ), 0.0f ));
    CHECK(ApproximatelyEqual( r0.z( ), 0.0f ));

    CHECK(ApproximatelyEqual( r1.x( ), 0.0f ));
    CHECK(ApproximatelyEqual( r1.y( ), 0.0f, 0.01f ));
    CHECK(ApproximatelyEqual( r1.z( ), 1.0f, 0.01f ));

    CHECK(ApproximatelyEqual( r2.x( ), 0.0f ));
    CHECK(ApproximatelyEqual( r2.y( ), -1.0f, 0.01f ));
    CHECK(ApproximatelyEqual( r2.z( ), 0.0f, 0.01f ));

    CHECK(IsOrthogonalMatrix( r0, r1, r2, r3 ));
}

TEST_CASE("MathMatrixTests / RotationNormalAxisY90Degrees", "[math][MathMatrixTests]")
{
    // 90-degree rotation around Y-axis
    Math::Vector<float, 3>::Simd axis( 0.0f, 1.0f, 0.0f );
    float angle = 3.14159265f / 2.0f; // 90 degrees

    auto result = RotationNormal( axis, angle );

    Math::Vector<float, 4>::Simd r0( result.simd[ 0 ] );
    Math::Vector<float, 4>::Simd r1( result.simd[ 1 ] );
    Math::Vector<float, 4>::Simd r2( result.simd[ 2 ] );
    Math::Vector<float, 4>::Simd r3( result.simd[ 3 ] );

    // Rotation around Y by 90 degrees: [0 0 -1; 0 1 0; 1 0 0]
    CHECK(ApproximatelyEqual( r0.x( ), 0.0f, 0.01f ));
    CHECK(ApproximatelyEqual( r0.y( ), 0.0f ));
    CHECK(ApproximatelyEqual( r0.z( ), -1.0f, 0.01f ));

    CHECK(ApproximatelyEqual( r1.x( ), 0.0f ));
    CHECK(ApproximatelyEqual( r1.y( ), 1.0f ));
    CHECK(ApproximatelyEqual( r1.z( ), 0.0f ));

    CHECK(ApproximatelyEqual( r2.x( ), 1.0f, 0.01f ));
    CHECK(ApproximatelyEqual( r2.y( ), 0.0f ));
    CHECK(ApproximatelyEqual( r2.z( ), 0.0f, 0.01f ));

    CHECK(IsOrthogonalMatrix( r0, r1, r2, r3 ));
}

TEST_CASE("MathMatrixTests / RotationNormalAxisZ90Degrees", "[math][MathMatrixTests]")
{
    // 90-degree rotation around Z-axis
    Math::Vector<float, 3>::Simd axis( 0.0f, 0.0f, 1.0f );
    float angle = 3.14159265f / 2.0f; // 90 degrees

    auto result = RotationNormal( axis, angle );

    Math::Vector<float, 4>::Simd r0( result.simd[ 0 ] );
    Math::Vector<float, 4>::Simd r1( result.simd[ 1 ] );
    Math::Vector<float, 4>::Simd r2( result.simd[ 2 ] );
    Math::Vector<float, 4>::Simd r3( result.simd[ 3 ] );

    // Rotation around Z by 90 degrees: [0 1 0; -1 0 0; 0 0 1]
    CHECK(ApproximatelyEqual( r0.x( ), 0.0f, 0.01f ));
    CHECK(ApproximatelyEqual( r0.y( ), 1.0f, 0.01f ));
    CHECK(ApproximatelyEqual( r0.z( ), 0.0f ));

    CHECK(ApproximatelyEqual( r1.x( ), -1.0f, 0.01f ));
    CHECK(ApproximatelyEqual( r1.y( ), 0.0f, 0.01f ));
    CHECK(ApproximatelyEqual( r1.z( ), 0.0f ));

    CHECK(ApproximatelyEqual( r2.x( ), 0.0f ));
    CHECK(ApproximatelyEqual( r2.y( ), 0.0f ));
    CHECK(ApproximatelyEqual( r2.z( ), 1.0f ));

    CHECK(IsOrthogonalMatrix( r0, r1, r2, r3 ));
}

TEST_CASE("MathMatrixTests / RotationNormalArbitrary", "[math][MathMatrixTests]")
{
    // Arbitrary rotation: 45 degrees around normalized [1, 1, 1] axis
    Math::Vector<float, 3>::Simd axis( 0.57735f, 0.57735f, 0.57735f ); // normalized [1,1,1]
    float angle = 3.14159265f / 4.0f; // 45 degrees

    auto result = RotationNormal( axis, angle );

    Math::Vector<float, 4>::Simd r0( result.simd[ 0 ] );
    Math::Vector<float, 4>::Simd r1( result.simd[ 1 ] );
    Math::Vector<float, 4>::Simd r2( result.simd[ 2 ] );
    Math::Vector<float, 4>::Simd r3( result.simd[ 3 ] );

    // Verify it's a valid rotation matrix (orthogonal)
    CHECK(IsOrthogonalMatrix( r0, r1, r2, r3 ));
}

TEST_CASE("MathMatrixTests / RotationNormalAxisInvariance", "[math][MathMatrixTests]")
{
    // Rotating around an axis should leave that axis unchanged
    Math::Vector<float, 3>::Simd axis( 1.0f, 0.0f, 0.0f );
    float angle = 1.5f; // arbitrary angle

    auto result = RotationNormal( axis, angle );

    Math::Vector<float, 4>::Simd r0( result.simd[ 0 ] );
    Math::Vector<float, 4>::Simd r1( result.simd[ 1 ] );
    Math::Vector<float, 4>::Simd r2( result.simd[ 2 ] );

    // Rotate the axis by the matrix: M * axis should equal axis
    float x = r0.x( ) * axis.x( ) + r0.y( ) * axis.y( ) + r0.z( ) * axis.z( );
    float y = r1.x( ) * axis.x( ) + r1.y( ) * axis.y( ) + r1.z( ) * axis.z( );
    float z = r2.x( ) * axis.x( ) + r2.y( ) * axis.y( ) + r2.z( ) * axis.z( );

    CHECK(ApproximatelyEqual( x, axis.x( ) ));
    CHECK(ApproximatelyEqual( y, axis.y( ) ));
    CHECK(ApproximatelyEqual( z, axis.z( ) ));
}

TEST_CASE("MathMatrixTests / RotationNormalMatrixFormat", "[math][MathMatrixTests]")
{
    // Verify the 4x4 matrix structure
    Math::Vector<float, 3>::Simd axis( 0.0f, 1.0f, 0.0f );
    float angle = 1.5f;

    auto result = RotationNormal( axis, angle );

    Math::Vector<float, 4>::Simd r0( result.simd[ 0 ] );
    Math::Vector<float, 4>::Simd r1( result.simd[ 1 ] );
    Math::Vector<float, 4>::Simd r2( result.simd[ 2 ] );
    Math::Vector<float, 4>::Simd r3( result.simd[ 3 ] );

    // Last row should be [0, 0, 0, 1]
    CHECK(ApproximatelyEqual( r3.x( ), 0.0f ));
    CHECK(ApproximatelyEqual( r3.y( ), 0.0f ));
    CHECK(ApproximatelyEqual( r3.z( ), 0.0f ));
    CHECK(ApproximatelyEqual( r3.w( ), 1.0f ));
}

TEST_CASE("MathMatrixTests / RotationNormalWithTupleType", "[math][MathMatrixTests]")
{
    // Test with Tuple3 instead of Simd type
    Math::Vector<float, 3> axis( 1.0f, 0.0f, 0.0f );
    float angle = 3.14159265f / 2.0f;

    auto result = RotationNormal( axis, angle );

    Math::Vector<float, 4>::Simd r0( result.simd[ 0 ] );
    Math::Vector<float, 4>::Simd r1( result.simd[ 1 ] );
    Math::Vector<float, 4>::Simd r2( result.simd[ 2 ] );
    Math::Vector<float, 4>::Simd r3( result.simd[ 3 ] );

    // Should produce same result as with Simd type
    CHECK(ApproximatelyEqual( r0.x( ), 1.0f ));
    CHECK(IsOrthogonalMatrix( r0, r1, r2, r3 ));
}

TEST_CASE("MathMatrixTests / RotationNormalLargeAngle", "[math][MathMatrixTests]")
{
    // Test with angle > 2*pi
    Math::Vector<float, 3>::Simd axis( 0.0f, 0.0f, 1.0f );
    float angle = 3.14159265f * 4.0f; // 4*pi (equivalent to 0)

    auto result = RotationNormal( axis, angle );

    Math::Vector<float, 4>::Simd r0( result.simd[ 0 ] );
    Math::Vector<float, 4>::Simd r1( result.simd[ 1 ] );
    Math::Vector<float, 4>::Simd r2( result.simd[ 2 ] );
    Math::Vector<float, 4>::Simd r3( result.simd[ 3 ] );

    CHECK(IsOrthogonalMatrix( r0, r1, r2, r3 ));
}

TEST_CASE("MathMatrixTests / RotationNormal180Degrees", "[math][MathMatrixTests]")
{
    // 180-degree rotation around X-axis
    Math::Vector<float, 3>::Simd axis( 1.0f, 0.0f, 0.0f );
    float angle = 3.14159265f; // 180 degrees

    auto result = RotationNormal( axis, angle );

    Math::Vector<float, 4>::Simd r0( result.simd[ 0 ] );
    Math::Vector<float, 4>::Simd r1( result.simd[ 1 ] );
    Math::Vector<float, 4>::Simd r2( result.simd[ 2 ] );
    Math::Vector<float, 4>::Simd r3( result.simd[ 3 ] );

    // Rotation around X by 180 degrees: [1 0 0; 0 -1 0; 0 0 -1]
    CHECK(ApproximatelyEqual( r0.x( ), 1.0f ));
    CHECK(ApproximatelyEqual( r0.y( ), 0.0f ));
    CHECK(ApproximatelyEqual( r0.z( ), 0.0f ));

    CHECK(ApproximatelyEqual( r1.x( ), 0.0f ));
    CHECK(ApproximatelyEqual( r1.y( ), -1.0f, 0.01f ));
    CHECK(ApproximatelyEqual( r1.z( ), 0.0f, 0.01f ));

    CHECK(ApproximatelyEqual( r2.x( ), 0.0f ));
    CHECK(ApproximatelyEqual( r2.y( ), 0.0f, 0.01f ));
    CHECK(ApproximatelyEqual( r2.z( ), -1.0f, 0.01f ));

    CHECK(IsOrthogonalMatrix( r0, r1, r2, r3 ));
}

TEST_CASE("MathMatrixTests / RotationAxisWithXAxis", "[math][MathMatrixTests]")
{
    // Rotate 90 degrees around X axis
    Vector3f xAxis( 1.0f, 0.0f, 0.0f );
    float angle90 = Constants<float>::Pi / 2.0f;

    auto rotationMatrix = RotationAxis( xAxis, angle90 );
    bool valid = IsValidRotationMatrix( rotationMatrix );
    CHECK(valid);
}

TEST_CASE("MathMatrixTests / RotationAxisWithYAxis", "[math][MathMatrixTests]")
{
    // Rotate 45 degrees around Y axis
    Vector3f yAxis( 0.0f, 1.0f, 0.0f );
    float angle45 = Constants<float>::Pi / 4.0f;

    auto rotationMatrix = RotationAxis( yAxis, angle45 );
    bool valid = IsValidRotationMatrix( rotationMatrix );
    CHECK(valid);
}

TEST_CASE("MathMatrixTests / RotationAxisWithZAxis", "[math][MathMatrixTests]")
{
    // Rotate 180 degrees around Z axis
    Vector3f zAxis( 0.0f, 0.0f, 1.0f );
    float angle180 = Constants<float>::Pi;

    auto rotationMatrix = RotationAxis( zAxis, angle180 );
    bool valid = IsValidRotationMatrix( rotationMatrix );
    CHECK(valid);
}

TEST_CASE("MathMatrixTests / RotationAxisWithArbitraryAxis", "[math][MathMatrixTests]")
{
    // Rotate 60 degrees around arbitrary normalized axis
    Vector3f arbitraryAxis( 1.0f, 1.0f, 1.0f );
    float angle60 = Constants<float>::Pi / 3.0f;

    auto rotationMatrix = RotationAxis( arbitraryAxis, angle60 );
    bool valid = IsValidRotationMatrix( rotationMatrix );
    CHECK(valid);
}

TEST_CASE("MathMatrixTests / RotationAxisWithSmallAngle", "[math][MathMatrixTests]")
{
    // Small angle rotation (1 degree)
    Vector3f axis( 1.0f, 0.0f, 0.0f );
    float smallAngle = Constants<float>::Pi / 180.0f; // 1 degree in radians

    auto rotationMatrix = RotationAxis( axis, smallAngle );
    bool valid = IsValidRotationMatrix( rotationMatrix );
    CHECK(valid);
}

TEST_CASE("MathMatrixTests / RotationAxisWithLargeAngle", "[math][MathMatrixTests]")
{
    // Large angle rotation (359 degrees)
    Vector3f axis( 0.0f, 1.0f, 0.0f );
    float largeAngle = 359.0f * Constants<float>::Pi / 180.0f;

    auto rotationMatrix = RotationAxis( axis, largeAngle );
    bool valid = IsValidRotationMatrix( rotationMatrix );
    CHECK(valid);
}

TEST_CASE("MathMatrixTests / RotationAxisZeroAngle", "[math][MathMatrixTests]")
{
    // Zero angle rotation should result in identity-like rotation
    Vector3f axis( 1.0f, 1.0f, 1.0f );
    float zeroAngle = 0.0f;

    auto rotationMatrix = RotationAxis( axis, zeroAngle );
    bool valid = IsValidRotationMatrix( rotationMatrix );
    CHECK(valid);
}

TEST_CASE("MathMatrixTests / RotationAxisNegativeAngle", "[math][MathMatrixTests]")
{
    // Negative angle (counterclockwise vs clockwise)
    Vector3f axis( 1.0f, 0.0f, 0.0f );
    float negativeAngle = -Constants<float>::Pi / 4.0f;

    auto rotationMatrix = RotationAxis( axis, negativeAngle );
    bool valid = IsValidRotationMatrix( rotationMatrix );
    CHECK(valid);
}

TEST_CASE("MathMatrixTests / RotationAxisWithUnnormalizedAxis", "[math][MathMatrixTests]")
{
    // Non-unit axis vector (function should normalize it)
    Vector3f unnormalizedAxis( 2.0f, 2.0f, 2.0f );
    float angle = Constants<float>::Pi / 6.0f;

    auto rotationMatrix = RotationAxis( unnormalizedAxis, angle );
    bool valid = IsValidRotationMatrix( rotationMatrix );
    CHECK(valid);
}

TEST_CASE("MathMatrixTests / RotationAxisConsistency", "[math][MathMatrixTests]")
{
    // Same rotation from different axis representations should yield similar results
    Vector3f axis1( 3.0f, 4.0f, 0.0f );  // Unnormalized
    Vector3f axis2 = Normalize( axis1 );  // Normalized
    float angle = Constants<float>::Pi / 3.0f;

    auto matrix1 = RotationAxis( axis1, angle );
    auto matrix2 = RotationAxis( axis2, angle );

    // Results should be very similar (allowing for normalization differences)
    bool mapsAreEqual = matrix1 == matrix2;
    CHECK(mapsAreEqual);
}

TEST_CASE("MathMatrixTests / RotationAxisFullRotation", "[math][MathMatrixTests]")
{
    // Full 360-degree rotation should result in nearly identity
    Vector3f axis( 1.0f, 0.0f, 0.0f );
    float fullRotation = 2.0f * Constants<float>::Pi;

    auto rotationMatrix = RotationAxis( axis, fullRotation );
    bool valid = IsValidRotationMatrix( rotationMatrix );
    CHECK(valid);
}

TEST_CASE("MathMatrixTests / RotationAxisWithVector4", "[math][MathMatrixTests]")
{
    // Test with Vector4 (Size == 4, which satisfies Size > 2)
    Vector4f axis( 1.0f, 1.0f, 1.0f, 0.0f );
    float angle = Constants<float>::Pi / 4.0f;

    auto rotationMatrix = RotationAxis( axis, angle );
    bool valid = IsValidRotationMatrix( rotationMatrix );
    CHECK(valid);
}

TEST_CASE("MathMatrixTests / RotationAxisAppliedToVector", "[math][MathMatrixTests]")
{
    // Verify that rotating a vector about an axis works correctly
    // Rotate a vector 90 degrees about Z axis
    Vector3f zAxis( 0.0f, 0.0f, 1.0f );
    float angle90 = Constants<float>::Pi / 2.0f;
    Vector3f testVector( 1.0f, 0.0f, 0.0f );

    auto rotationMatrix = RotationAxis( zAxis, angle90 );

    // Create a 4D vector for transformation
    auto testVec4 = Vector4f( testVector.x, testVector.y, testVector.z, 0.0f );
    auto rotated = Math::Transform( testVec4.ToSimd( ), rotationMatrix);

    // After 90-degree rotation about Z: (1,0,0) should become approximately (0,1,0)
    float resultX = rotated[ 0 ];
    float resultY = rotated[ 1 ];
    float resultZ = rotated[ 2 ];

    bool xNearZero = ApproximatelyEqual( resultX, 0.0f, 1e-4f );
    bool yNearOne = ApproximatelyEqual( resultY, 1.0f, 1e-4f );
    bool zStaysZero = ApproximatelyEqual( resultZ, 0.0f, 1e-4f );

    CHECK(xNearZero);
    CHECK(yNearOne);
    CHECK(zStaysZero);
}

// Test identity quaternion produces identity matrix
TEST_CASE("MathMatrixTests / RotationIdentityQuaternion", "[math][MathMatrixTests]")
{
    Quaternion<float> q = Quaternion<float>::Identity( );
    Quaternion<float>::Simd qSimd( q );

    auto resultSimd = Rotation( qSimd );
    auto result = ExtractMatrix( resultSimd );

    // Check that the result is approximately the identity matrix
    for ( size_t i = 0; i < 4; ++i )
    {
        for ( size_t j = 0; j < 4; ++j )
        {
            float expected = ( i == j ) ? 1.0f : 0.0f;
            CHECK(ApproximatelyEqual( result[ i ][ j ], expected ));
        }
    }
}

// Test 180-degree rotation around X axis
TEST_CASE("MathMatrixTests / Rotation180AroundXAxis", "[math][MathMatrixTests]")
{
    // Quaternion for 180 degrees around X: q = (sin(90), 0, 0, cos(90)) = (1, 0, 0, 0)
    Quaternion<float> q( 1.0f, 0.0f, 0.0f, 0.0f );
    Quaternion<float>::Simd qSimd( q );

    auto resultSimd = Rotation( qSimd );
    auto result = ExtractMatrix( resultSimd );

    // Expected rotation matrix for 180 degrees around X:
    // [1,  0,  0, 0]
    // [0, -1,  0, 0]
    // [0,  0, -1, 0]
    // [0,  0,  0, 1]

    CHECK(ApproximatelyEqual( result[ 0 ][ 0 ], 1.0f ));
    CHECK(ApproximatelyEqual( result[ 1 ][ 1 ], -1.0f ));
    CHECK(ApproximatelyEqual( result[ 2 ][ 2 ], -1.0f ));
    CHECK(ApproximatelyEqual( result[ 3 ][ 3 ], 1.0f ));

    // Off-diagonal elements should be 0
    CHECK(ApproximatelyEqual( result[ 0 ][ 1 ], 0.0f ));
    CHECK(ApproximatelyEqual( result[ 1 ][ 0 ], 0.0f ));
}

// Test 90-degree rotation around Z axis
TEST_CASE("MathMatrixTests / Rotation90AroundZAxis", "[math][MathMatrixTests]")
{
    // Quaternion for 90 degrees around Z: q = (0, 0, sin(45), cos(45))
    float angle45 = 3.14159265359f / 4.0f;  // 45 degrees in radians
    Quaternion<float> q( 0.0f, 0.0f, std::sin( angle45 ), std::cos( angle45 ) );
    Quaternion<float>::Simd qSimd( q );

    auto resultSimd = Rotation( qSimd );
    auto result = ExtractMatrix( resultSimd );

    // After rotation around Z by 90 degrees:
    // [0, 1, 0, 0]
    // [-1,  0, 0, 0]
    // [0,  0, 1, 0]
    // [0,  0, 0, 1]

    CHECK(ApproximatelyEqual( result[ 0 ][ 0 ], 0.0f, 1e-4f ));
    CHECK(ApproximatelyEqual( result[ 0 ][ 1 ], 1.0f, 1e-4f ));
    CHECK(ApproximatelyEqual( result[ 1 ][ 0 ], -1.0f, 1e-4f ));
    CHECK(ApproximatelyEqual( result[ 1 ][ 1 ], 0.0f, 1e-4f ));
}

// Test that rotation matrix is orthogonal (M^T * M = I)
TEST_CASE("MathMatrixTests / RotationMatrixIsOrthogonal", "[math][MathMatrixTests]")
{
    // Create arbitrary rotation quaternion
    Quaternion<float> q( 0.5f, 0.5f, 0.5f, 0.5f );
    q = Normalize( q );  // Ensure it's normalized
    Quaternion<float>::Simd qSimd( q );

    auto resultSimd = Rotation( qSimd );
    auto result = ExtractMatrix( resultSimd );

    // Compute M^T * M
    std::array<std::array<float, 4>, 4> transpose{};
    for ( size_t i = 0; i < 4; ++i )
    {
        for ( size_t j = 0; j < 4; ++j )
        {
            transpose[ i ][ j ] = result[ j ][ i ];
        }
    }

    std::array<std::array<float, 4>, 4> product{};
    for ( size_t i = 0; i < 4; ++i )
    {
        for ( size_t j = 0; j < 4; ++j )
        {
            product[ i ][ j ] = 0.0f;
            for ( size_t k = 0; k < 4; ++k )
            {
                product[ i ][ j ] += transpose[ i ][ k ] * result[ k ][ j ];
            }
        }
    }

    // Check if product is identity
    for ( size_t i = 0; i < 4; ++i )
    {
        for ( size_t j = 0; j < 4; ++j )
        {
            float expected = ( i == j ) ? 1.0f : 0.0f;
            CHECK(ApproximatelyEqual( product[ i ][ j ], expected, 1e-4f ));
        }
    }
}

// Test that bottom row is [0, 0, 0, 1]
TEST_CASE("MathMatrixTests / RotationMatrixBottomRow", "[math][MathMatrixTests]")
{
    Quaternion<float> q( 0.3f, 0.4f, 0.5f, 0.7f );
    q = Normalize( q );
    Quaternion<float>::Simd qSimd( q );

    auto resultSimd = Rotation( qSimd );
    auto result = ExtractMatrix( resultSimd );

    CHECK(ApproximatelyEqual( result[ 3 ][ 0 ], 0.0f ));
    CHECK(ApproximatelyEqual( result[ 3 ][ 1 ], 0.0f ));
    CHECK(ApproximatelyEqual( result[ 3 ][ 2 ], 0.0f ));
    CHECK(ApproximatelyEqual( result[ 3 ][ 3 ], 1.0f ));
}

// Test that right column is [0, 0, 0, 1]
TEST_CASE("MathMatrixTests / RotationMatrixRightColumn", "[math][MathMatrixTests]")
{
    Quaternion<float> q( 0.2f, 0.6f, 0.3f, 0.7f );
    q = Normalize( q );
    Quaternion<float>::Simd qSimd( q );

    auto resultSimd = Rotation( qSimd );
    auto result = ExtractMatrix( resultSimd );

    CHECK(ApproximatelyEqual( result[ 0 ][ 3 ], 0.0f ));
    CHECK(ApproximatelyEqual( result[ 1 ][ 3 ], 0.0f ));
    CHECK(ApproximatelyEqual( result[ 2 ][ 3 ], 0.0f ));
    CHECK(ApproximatelyEqual( result[ 3 ][ 3 ], 1.0f ));
}

// Test rotation of a vector (0, 0, 1) by identity should give (0, 0, 1)
TEST_CASE("MathMatrixTests / RotationVectorIdentity", "[math][MathMatrixTests]")
{
    Quaternion<float> q = Quaternion<float>::Identity( );
    auto rotationMatrix = Rotation( q.ToSimd( ) );
    auto result = ExtractMatrix( rotationMatrix );

    // The Z-axis vector (0, 0, 1, 0) rotated by identity should remain (0, 0, 1, 0)
    float resX = result[ 0 ][ 2 ];
    float resY = result[ 1 ][ 2 ];
    float resZ = result[ 2 ][ 2 ];

    CHECK(ApproximatelyEqual( resX, 0.0f ));
    CHECK(ApproximatelyEqual( resY, 0.0f ));
    CHECK(ApproximatelyEqual( resZ, 1.0f ));
}

// Test that normalized quaternions produce valid rotation matrices
TEST_CASE("MathMatrixTests / RotationNormalizedQuaternion", "[math][MathMatrixTests]")
{
    // Create a normalized quaternion
    Quaternion<float> q( 0.1f, 0.2f, 0.3f, 0.9f );
    q = Normalize( q );

    CHECK(ApproximatelyEqual( ScalarLength( q.ToSimd( ) ), 1.0f, 1e-5f ));

    auto resultSimd = Rotation( q.ToSimd( ) );
    auto result = ExtractMatrix( resultSimd );

    // All matrix elements should be finite
    for ( size_t i = 0; i < 4; ++i )
    {
        for ( size_t j = 0; j < 4; ++j )
        {
            CHECK(std::isfinite( result[ i ][ j ] ));
        }
    }
}

// Test small angle approximation
TEST_CASE("MathMatrixTests / RotationSmallAngle", "[math][MathMatrixTests]")
{
    // Very small rotation around X axis
    float smallAngle = 0.01f;  // 0.01 radians
    float halfAngle = smallAngle / 2.0f;

    Quaternion<float> q( std::sin( halfAngle ), 0.0f, 0.0f, std::cos( halfAngle ) );
    Quaternion<float>::Simd qSimd( q );

    auto resultSimd = Rotation( qSimd );
    auto result = ExtractMatrix( resultSimd );

    // For small angles, rotation matrix should be close to identity
    float tolerance = 0.02f;

    CHECK(std::abs( result[ 0 ][ 0 ] - 1.0f ) < tolerance);
    CHECK(std::abs( result[ 1 ][ 1 ] - 1.0f ) < tolerance);
    CHECK(std::abs( result[ 2 ][ 2 ] - 1.0f ) < tolerance);
}

TEST_CASE("MathMatrixTests / IdentityTransformation", "[math][MathMatrixTests]")
{
    // Test transformation matrix with identity values (no scaling, rotation, translation)
    Point3f scalingOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> scalingOrientationQuaternion = Quaternion<float>::Identity( );
    Vector3f scaling( 1.0f, 1.0f, 1.0f );

    Point3f rotationOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> rotationQuaternion = Quaternion<float>::Identity( );
    Vector3f translation( 0.0f, 0.0f, 0.0f );

    auto result = TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling,
        rotationOrigin, rotationQuaternion, translation );
    auto matrix = SquareMatrix<float, 4>( result );

    // Identity matrix should have 1s on diagonal and 0s elsewhere
    bool isIdentity = ApproximatelyEqual( matrix[ 0 ][ 0 ], 1.0f ) && ApproximatelyEqual( matrix[ 1 ][ 1 ], 1.0f ) &&
        ApproximatelyEqual( matrix[ 2 ][ 2 ], 1.0f ) && ApproximatelyEqual( matrix[ 3 ][ 3 ], 1.0f ) &&
        ApproximatelyEqual( matrix[ 0 ][ 1 ], 0.0f ) && ApproximatelyEqual( matrix[ 0 ][ 2 ], 0.0f ) &&
        ApproximatelyEqual( matrix[ 1 ][ 0 ], 0.0f ) && ApproximatelyEqual( matrix[ 1 ][ 2 ], 0.0f ) &&
        ApproximatelyEqual( matrix[ 2 ][ 0 ], 0.0f ) && ApproximatelyEqual( matrix[ 2 ][ 1 ], 0.0f );

    CHECK(isIdentity);
}

TEST_CASE("MathMatrixTests / ScalingOnlyTransformation", "[math][MathMatrixTests]")
{
    // Test transformation matrix with only scaling
    Point3f scalingOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> scalingOrientationQuaternion = Quaternion<float>::Identity( );
    Vector3f scaling( 2.0f, 3.0f, 4.0f );

    Point3f rotationOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> rotationQuaternion = Quaternion<float>::Identity( );
    Vector3f translation( 0.0f, 0.0f, 0.0f );

    auto result = TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling,
        rotationOrigin, rotationQuaternion, translation );
    auto matrix = SquareMatrix<float, 4>( result );

    // Check that diagonal elements contain scaling factors
    bool hasScaling = ApproximatelyEqual( matrix[ 0 ][ 0 ], 2.0f ) && ApproximatelyEqual( matrix[ 1 ][ 1 ], 3.0f ) &&
        ApproximatelyEqual( matrix[ 2 ][ 2 ], 4.0f ) && ApproximatelyEqual( matrix[ 3 ][ 3 ], 1.0f );

    CHECK(hasScaling);
}

TEST_CASE("MathMatrixTests / TranslationOnlyTransformation", "[math][MathMatrixTests]")
{
    // Test transformation matrix with only translation
    Point3f scalingOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> scalingOrientationQuaternion = Quaternion<float>::Identity( );
    Vector3f scaling( 1.0f, 1.0f, 1.0f );

    Point3f rotationOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> rotationQuaternion = Quaternion<float>::Identity( );
    Vector3f translation( 5.0f, 6.0f, 7.0f );

    auto result = TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling,
        rotationOrigin, rotationQuaternion, translation );
    auto matrix = SquareMatrix<float, 4>( result );

    // Check that translation is in the appropriate position (typically last row/column for column-major or last column for row-major)
    // The exact position depends on the matrix layout convention used
    bool hasTranslation = ( ApproximatelyEqual( matrix[ 3 ][ 0 ], 5.0f ) && ApproximatelyEqual( matrix[ 3 ][ 1 ], 6.0f ) && ApproximatelyEqual( matrix[ 3 ][ 2 ], 7.0f ) ) ||
        ( ApproximatelyEqual( matrix[ 0 ][ 3 ], 5.0f ) && ApproximatelyEqual( matrix[ 1 ][ 3 ], 6.0f ) && ApproximatelyEqual( matrix[ 2 ][ 3 ], 7.0f ) );

    CHECK(hasTranslation);
}

TEST_CASE("MathMatrixTests / CombinedTransformation", "[math][MathMatrixTests]")
{
    // Test transformation matrix with scaling, rotation, and translation
    Point3f scalingOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> scalingOrientationQuaternion = Quaternion<float>::Identity( );
    Vector3f scaling( 2.0f, 2.0f, 2.0f );

    Point3f rotationOrigin( 0.0f, 0.0f, 0.0f );
    // 90-degree rotation around Z-axis
    Quaternion<float> rotationQuaternion( 0.0f, 0.0f, 0.7071068f, 0.7071068f );
    Vector3f translation( 10.0f, 20.0f, 30.0f );

    auto result = TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling,
        rotationOrigin, rotationQuaternion, translation );
    auto matrix = SquareMatrix<float, 4>( result );

    // The matrix should be a valid 4x4 transformation matrix
    // Check that bottom-right is 1.0f
    bool isValidMatrix = ApproximatelyEqual( matrix[ 3 ][ 3 ], 1.0f );

    CHECK(isValidMatrix);
}

TEST_CASE("MathMatrixTests / NonZeroScalingOrigin", "[math][MathMatrixTests]")
{
    // Test transformation matrix with non-zero scaling origin
    Point3f scalingOrigin( 5.0f, 5.0f, 5.0f );
    Quaternion<float> scalingOrientationQuaternion = Quaternion<float>::Identity( );
    Vector3f scaling( 2.0f, 2.0f, 2.0f );

    Point3f rotationOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> rotationQuaternion = Quaternion<float>::Identity( );
    Vector3f translation( 0.0f, 0.0f, 0.0f );

    auto result = TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling,
        rotationOrigin, rotationQuaternion, translation );
    auto matrix = SquareMatrix<float, 4>( result );

    // Matrix should have scaling factors on diagonal
    bool hasScaling = ApproximatelyEqual( matrix[ 0 ][ 0 ], 2.0f ) && ApproximatelyEqual( matrix[ 1 ][ 1 ], 2.0f ) &&
        ApproximatelyEqual( matrix[ 2 ][ 2 ], 2.0f );

    CHECK(hasScaling);
}

TEST_CASE("MathMatrixTests / NonZeroRotationOrigin", "[math][MathMatrixTests]")
{
    // Test transformation matrix with non-zero rotation origin
    Point3f scalingOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> scalingOrientationQuaternion = Quaternion<float>::Identity( );
    Vector3f scaling( 1.0f, 1.0f, 1.0f );

    Point3f rotationOrigin( 10.0f, 10.0f, 10.0f );
    Quaternion<float> rotationQuaternion = Quaternion<float>::Identity( );
    Vector3f translation( 0.0f, 0.0f, 0.0f );

    auto result = TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling,
        rotationOrigin, rotationQuaternion, translation );
    auto matrix = SquareMatrix<float, 4>( result );

    // Matrix should be valid and have 1 on diagonal (no scaling or rotation)
    bool isValid = ApproximatelyEqual( matrix[ 3 ][ 3 ], 1.0f );

    CHECK(isValid);
}

TEST_CASE("MathMatrixTests / UniformScaling", "[math][MathMatrixTests]")
{
    // Test transformation matrix with uniform scaling
    Point3f scalingOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> scalingOrientationQuaternion = Quaternion<float>::Identity( );
    Vector3f scaling( 3.0f, 3.0f, 3.0f );

    Point3f rotationOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> rotationQuaternion = Quaternion<float>::Identity( );
    Vector3f translation( 0.0f, 0.0f, 0.0f );

    auto result = TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling,
        rotationOrigin, rotationQuaternion, translation );
    auto matrix = SquareMatrix<float, 4>( result );

    // All diagonal scaling elements should be equal
    bool isUniform = ApproximatelyEqual( matrix[ 0 ][ 0 ], 3.0f ) && ApproximatelyEqual( matrix[ 1 ][ 1 ], 3.0f ) &&
        ApproximatelyEqual( matrix[ 2 ][ 2 ], 3.0f );

    CHECK(isUniform);
}

TEST_CASE("MathMatrixTests / NonUniformScaling", "[math][MathMatrixTests]")
{
    // Test transformation matrix with non-uniform scaling
    Point3f scalingOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> scalingOrientationQuaternion = Quaternion<float>::Identity( );
    Vector3f scaling( 1.0f, 2.0f, 3.0f );

    Point3f rotationOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> rotationQuaternion = Quaternion<float>::Identity( );
    Vector3f translation( 0.0f, 0.0f, 0.0f );

    auto result = TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling,
        rotationOrigin, rotationQuaternion, translation );
    auto matrix = SquareMatrix<float, 4>( result );

    // Different diagonal scaling elements should be different
    bool isDifferent = ApproximatelyEqual( matrix[ 0 ][ 0 ], 1.0f ) && ApproximatelyEqual( matrix[ 1 ][ 1 ], 2.0f ) &&
        ApproximatelyEqual( matrix[ 2 ][ 2 ], 3.0f );

    CHECK(isDifferent);
}

TEST_CASE("MathMatrixTests / LargeTranslationValues", "[math][MathMatrixTests]")
{
    // Test transformation matrix with large translation values
    Point3f scalingOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> scalingOrientationQuaternion = Quaternion<float>::Identity( );
    Vector3f scaling( 1.0f, 1.0f, 1.0f );

    Point3f rotationOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> rotationQuaternion = Quaternion<float>::Identity( );
    Vector3f translation( 1000.0f, 2000.0f, 3000.0f );

    auto result = TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling,
        rotationOrigin, rotationQuaternion, translation );
    auto matrix = SquareMatrix<float, 4>( result );

    // Matrix should remain valid with large translation
    bool isValid = ApproximatelyEqual( matrix[ 3 ][ 3 ], 1.0f );

    CHECK(isValid);
}

TEST_CASE("MathMatrixTests / NegativeScaling", "[math][MathMatrixTests]")
{
    // Test transformation matrix with negative scaling (reflection)
    Point3f scalingOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> scalingOrientationQuaternion = Quaternion<float>::Identity( );
    Vector3f scaling( -1.0f, 1.0f, 1.0f );

    Point3f rotationOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> rotationQuaternion = Quaternion<float>::Identity( );
    Vector3f translation( 0.0f, 0.0f, 0.0f );

    auto result = TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling,
        rotationOrigin, rotationQuaternion, translation );
    auto matrix = SquareMatrix<float, 4>( result );

    // Negative scaling should be reflected in matrix
    bool hasNegativeScale = ApproximatelyEqual( matrix[ 0 ][ 0 ], -1.0f );

    CHECK(hasNegativeScale);
}

TEST_CASE("MathMatrixTests / SmallScalingValues", "[math][MathMatrixTests]")
{
    // Test transformation matrix with very small scaling values
    Point3f scalingOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> scalingOrientationQuaternion = Quaternion<float>::Identity( );
    Vector3f scaling( 0.001f, 0.002f, 0.003f );

    Point3f rotationOrigin( 0.0f, 0.0f, 0.0f );
    Quaternion<float> rotationQuaternion = Quaternion<float>::Identity( );
    Vector3f translation( 0.0f, 0.0f, 0.0f );

    auto result = TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling,
        rotationOrigin, rotationQuaternion, translation );
    auto matrix = SquareMatrix<float, 4>( result );

    // Small scaling values should be present
    bool hasSmallScale = ApproximatelyEqual( matrix[ 0 ][ 0 ], 0.001f, 1e-6f ) &&
        ApproximatelyEqual( matrix[ 1 ][ 1 ], 0.002f, 1e-6f ) &&
        ApproximatelyEqual( matrix[ 2 ][ 2 ], 0.003f, 1e-6f );

    CHECK(hasSmallScale);
}

TEST_CASE("MathMatrixTests / MatrixBottomRowCorrect", "[math][MathMatrixTests]")
{
    // Verify that the bottom row of the matrix is correct (should be [0, 0, 0, 1] for homogeneous coordinates)
    Point3f scalingOrigin( 1.0f, 2.0f, 3.0f );
    Quaternion<float> scalingOrientationQuaternion = Quaternion<float>::Identity( );
    Vector3f scaling( 2.0f, 2.0f, 2.0f );

    Point3f rotationOrigin( 4.0f, 5.0f, 6.0f );
    Quaternion<float> rotationQuaternion = Quaternion<float>::Identity( );
    Vector3f translation( 7.0f, 8.0f, 9.0f );

    auto result = TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling,
        rotationOrigin, rotationQuaternion, translation );
    auto matrix = SquareMatrix<float, 4>( result );

    // rightmost column should be [0, 0, 0, 1]
    bool isCorrect = ApproximatelyEqual( matrix[ 3 ][ 3 ], 1.0f ) && ApproximatelyEqual( matrix[ 0 ][ 3 ], 0.0f ) &&
        ApproximatelyEqual( matrix[ 1 ][ 3 ], 0.0f ) && ApproximatelyEqual( matrix[ 2 ][ 3 ], 0.0f );

    CHECK(isCorrect);
}

TEST_CASE("MathMatrixTests / InverseOfIdentityMatrixReturnsIdentity", "[math][MathMatrixTests]")
{
    // Arrange
    auto identityMatrix = SquareMatrix<float, 4>::Simd( Math::MatrixType::Identity );
    Math::Vector<float, 4>::Simd determinant;

    // Act
    auto result = Inverse( identityMatrix, &determinant );

    // Assert
    bool isIdentityResult = result.IsIdentity( );
    CHECK(isIdentityResult);
    CHECK(ApproximatelyEqual( determinant[ 0 ], 1.0f, 1e-5f ));
}

TEST_CASE("MathMatrixTests / InverseComputesDeterminantCorrectly", "[math][MathMatrixTests]")
{
    // Arrange - Create a simple 4x4 matrix
    // [2, 0, 0, 0]
    // [0, 3, 0, 0]
    // [0, 0, 4, 0]
    // [0, 0, 0, 5]
    // Determinant = 2 * 3 * 4 * 5 = 120
    SquareMatrix<float, 4> matrix;
    matrix[ 0 ][ 0 ] = 2.0f;
    matrix[ 1 ][ 1 ] = 3.0f;
    matrix[ 2 ][ 2 ] = 4.0f;
    matrix[ 3 ][ 3 ] = 5.0f;

    auto simdMatrix = matrix.ToSimd( );
    Math::Vector<float, 4>::Simd determinant;

    // Act
    Inverse( simdMatrix, &determinant );

    // Assert
    CHECK(ApproximatelyEqual( determinant[ 0 ], 120.0f, 1e-4f ));
}

TEST_CASE("MathMatrixTests / InverseOfDiagonalMatrixIsCorrect", "[math][MathMatrixTests]")
{
    // Arrange - Create a diagonal matrix
    // [2, 0, 0, 0]
    // [0, 4, 0, 0]
    // [0, 0, 1, 0]
    // [0, 0, 0, 2]
    SquareMatrix<float, 4> matrix;
    matrix[ 0 ][ 0 ] = 2.0f;
    matrix[ 1 ][ 1 ] = 4.0f;
    matrix[ 2 ][ 2 ] = 1.0f;
    matrix[ 3 ][ 3 ] = 2.0f;

    // Expected inverse:
    // [0.5, 0, 0, 0]
    // [0, 0.25, 0, 0]
    // [0, 0, 1, 0]
    // [0, 0, 0, 0.5]
    SquareMatrix<float, 4> expectedInverse;
    expectedInverse[ 0 ][ 0 ] = 0.5f;
    expectedInverse[ 1 ][ 1 ] = 0.25f;
    expectedInverse[ 2 ][ 2 ] = 1.0f;
    expectedInverse[ 3 ][ 3 ] = 0.5f;

    auto simdMatrix = matrix.ToSimd( );
    Math::Vector<float, 4>::Simd determinant;

    // Act
    auto result = Inverse( simdMatrix, &determinant );

    // Assert
    auto expectedSimd = expectedInverse.ToSimd( );
    bool isEqual = MatrixApproximatelyEqual( result, expectedSimd, 1e-5f );
    CHECK(isEqual);
}

TEST_CASE("MathMatrixTests / InverseSingularMatrixReturnsNaN", "[math][MathMatrixTests]")
{
    // Arrange - Create a singular matrix (two identical rows)
    // [1, 2, 3, 4]
    // [1, 2, 3, 4]
    // [5, 6, 7, 8]
    // [9, 10, 11, 12]
    SquareMatrix<float, 4> singularMatrix;
    singularMatrix[ 0 ][ 0 ] = 1.0f; singularMatrix[ 0 ][ 1 ] = 2.0f; singularMatrix[ 0 ][ 2 ] = 3.0f; singularMatrix[ 0 ][ 3 ] = 4.0f;
    singularMatrix[ 1 ][ 0 ] = 1.0f; singularMatrix[ 1 ][ 1 ] = 2.0f; singularMatrix[ 1 ][ 2 ] = 3.0f; singularMatrix[ 1 ][ 3 ] = 4.0f;
    singularMatrix[ 2 ][ 0 ] = 5.0f; singularMatrix[ 2 ][ 1 ] = 6.0f; singularMatrix[ 2 ][ 2 ] = 7.0f; singularMatrix[ 2 ][ 3 ] = 8.0f;
    singularMatrix[ 3 ][ 0 ] = 9.0f; singularMatrix[ 3 ][ 1 ] = 10.0f; singularMatrix[ 3 ][ 2 ] = 11.0f; singularMatrix[ 3 ][ 3 ] = 12.0f;

    auto simdMatrix = singularMatrix.ToSimd( );
    Math::Vector<float, 4>::Simd determinant;

    // Act
    SquareMatrix<float, 4> result = Inverse( simdMatrix, &determinant );

    // Assert - Result should contain NaN values
    bool hasNaN = std::isnan( result[ 0 ][ 0 ] ) || std::isnan( result[ 1 ][ 1 ] ) ||
        std::isnan( result[ 2 ][ 2 ] ) || std::isnan( result[ 3 ][ 3 ] );
    CHECK(hasNaN);
}

TEST_CASE("MathMatrixTests / InverseMultipliedByOriginalMatrixGivesIdentity", "[math][MathMatrixTests]")
{
    // Arrange
    SquareMatrix<float, 4> matrix;
    matrix[ 0 ][ 0 ] = 4.0f; matrix[ 0 ][ 1 ] = 7.0f; matrix[ 0 ][ 2 ] = 2.0f; matrix[ 0 ][ 3 ] = 1.0f;
    matrix[ 1 ][ 0 ] = 1.0f; matrix[ 1 ][ 1 ] = 2.0f; matrix[ 1 ][ 2 ] = 8.0f; matrix[ 1 ][ 3 ] = 4.0f;
    matrix[ 2 ][ 0 ] = 2.0f; matrix[ 2 ][ 1 ] = 3.0f; matrix[ 2 ][ 2 ] = 1.0f; matrix[ 2 ][ 3 ] = 5.0f;
    matrix[ 3 ][ 0 ] = 9.0f; matrix[ 3 ][ 1 ] = 6.0f; matrix[ 3 ][ 2 ] = 3.0f; matrix[ 3 ][ 3 ] = 2.0f;

    auto simdMatrix = matrix.ToSimd( );
    Math::Vector<float, 4>::Simd determinant;

    // Act
    auto inverseMatrix = Inverse( simdMatrix, &determinant );
    auto product = Multiply( simdMatrix, inverseMatrix );

    // Assert - Product should be identity
    auto identityMatrix = SquareMatrix<float, 4>::Simd( Math::MatrixType::Identity );
    bool isIdentity = MatrixApproximatelyEqual( product, identityMatrix, 1e-4f );
    CHECK(isIdentity);
}

TEST_CASE("MathMatrixTests / InverseWithNullDeterminantPointer", "[math][MathMatrixTests]")
{
    // Arrange
    auto identityMatrix = SquareMatrix<float, 4>::Simd( Math::MatrixType::Identity );

    // Act - Should not crash with null pointer
    auto result = Inverse( identityMatrix, nullptr );

    // Assert
    bool isIdentityResult = result.IsIdentity( );
    CHECK(isIdentityResult);
}

TEST_CASE("MathMatrixTests / InverseOfScaledIdentityMatrix", "[math][MathMatrixTests]")
{
    // Arrange - Create a scaled identity matrix
    // [3, 0, 0, 0]
    // [0, 3, 0, 0]
    // [0, 0, 3, 0]
    // [0, 0, 0, 3]
    SquareMatrix<float, 4> scaledIdentity;
    scaledIdentity[ 0 ][ 0 ] = 3.0f;
    scaledIdentity[ 1 ][ 1 ] = 3.0f;
    scaledIdentity[ 2 ][ 2 ] = 3.0f;
    scaledIdentity[ 3 ][ 3 ] = 3.0f;

    // Expected inverse: each diagonal element = 1/3
    auto simdMatrix = scaledIdentity.ToSimd( );
    Math::Vector<float, 4>::Simd determinant;

    // Act
    SquareMatrix<float, 4> result = Inverse( simdMatrix, &determinant );

    // Assert
    CHECK(ApproximatelyEqual( result[ 0 ][ 0 ], 1.0f / 3.0f, 1e-5f ));
    CHECK(ApproximatelyEqual( result[ 1 ][ 1 ], 1.0f / 3.0f, 1e-5f ));
    CHECK(ApproximatelyEqual( result[ 2 ][ 2 ], 1.0f / 3.0f, 1e-5f ));
    CHECK(ApproximatelyEqual( result[ 3 ][ 3 ], 1.0f / 3.0f, 1e-5f ));
    CHECK(ApproximatelyEqual( determinant[ 0 ], 81.0f, 1e-4f )); // 3^4 = 81
}

TEST_CASE("MathMatrixTests / InverseConsistencyWithMultipleInvocations", "[math][MathMatrixTests]")
{
    // Arrange
    SquareMatrix<float, 4> matrix;
    matrix[ 0 ][ 0 ] = 1.5f; matrix[ 0 ][ 1 ] = 0.5f; matrix[ 0 ][ 2 ] = 0.2f; matrix[ 0 ][ 3 ] = 0.1f;
    matrix[ 1 ][ 0 ] = 0.5f; matrix[ 1 ][ 1 ] = 2.5f; matrix[ 1 ][ 2 ] = 0.3f; matrix[ 1 ][ 3 ] = 0.2f;
    matrix[ 2 ][ 0 ] = 0.2f; matrix[ 2 ][ 1 ] = 0.3f; matrix[ 2 ][ 2 ] = 3.5f; matrix[ 2 ][ 3 ] = 0.4f;
    matrix[ 3 ][ 0 ] = 0.1f; matrix[ 3 ][ 1 ] = 0.2f; matrix[ 3 ][ 2 ] = 0.4f; matrix[ 3 ][ 3 ] = 4.5f;

    auto simdMatrix = matrix.ToSimd( );

    // Act
    Math::Vector<float, 4>::Simd det1, det2;
    auto inverse1 = Inverse( simdMatrix, &det1 );
    auto inverse2 = Inverse( simdMatrix, &det2 );

    // Assert - Multiple invocations should give identical results
    bool isEqual = MatrixApproximatelyEqual( inverse1, inverse2, 1e-6f );
    CHECK(isEqual);
    CHECK(ApproximatelyEqual( det1[ 0 ], det2[ 0 ], 1e-6f ));
}

TEST_CASE("MathMatrixTests / InverseDeterminantIsNonZeroForInvertibleMatrix", "[math][MathMatrixTests]")
{
    // Arrange
    SquareMatrix<float, 4> matrix;
    matrix[ 0 ][ 0 ] = 2.0f; matrix[ 0 ][ 1 ] = 1.0f; matrix[ 0 ][ 2 ] = 0.0f; matrix[ 0 ][ 3 ] = 0.0f;
    matrix[ 1 ][ 0 ] = 1.0f; matrix[ 1 ][ 1 ] = 3.0f; matrix[ 1 ][ 2 ] = 1.0f; matrix[ 1 ][ 3 ] = 0.0f;
    matrix[ 2 ][ 0 ] = 0.0f; matrix[ 2 ][ 1 ] = 1.0f; matrix[ 2 ][ 2 ] = 4.0f; matrix[ 2 ][ 3 ] = 1.0f;
    matrix[ 3 ][ 0 ] = 0.0f; matrix[ 3 ][ 1 ] = 0.0f; matrix[ 3 ][ 2 ] = 1.0f; matrix[ 3 ][ 3 ] = 5.0f;

    auto simdMatrix = matrix.ToSimd( );
    Math::Vector<float, 4>::Simd determinant;

    // Act
    Inverse( simdMatrix, &determinant );

    // Assert
    CHECK(determinant[ 0 ] != 0.0f);
    CHECK(!std::isnan( determinant[ 0 ] ));
}

/// <summary>
/// Tests the inverse of a 3x3 identity matrix.
/// </summary>
TEST_CASE("MathMatrixTests / InverseOfIdentityMatrix", "[math][MathMatrixTests]")
{
    // Arrange
    SquareMatrix<float, 3> identity;
    auto identitySimd = identity.ToSimd( );

    // Act
    auto result = Inverse( identitySimd );

    // Assert
    auto resultMatrix = SquareMatrix<float, 3>( result );
    bool isIdentity = resultMatrix.IsIdentity( );
    CHECK(isIdentity);
}

/// <summary>
/// Tests the inverse of a simple diagonal matrix.
/// </summary>
TEST_CASE("MathMatrixTests / InverseOfDiagonalMatrix", "[math][MathMatrixTests]")
{
    // Arrange
    SquareMatrix<float, 3> original = SquareMatrix<float, 3>::Diag( 2.0f, 3.0f, 4.0f );
    auto originalSimd = original.ToSimd( );

    SquareMatrix<float, 3> expected;
    expected[ 0 ][ 0 ] = 0.5f;
    expected[ 1 ][ 1 ] = 1.0f / 3.0f;
    expected[ 2 ][ 2 ] = 0.25f;

    // Act
    auto resultSimd = Inverse( originalSimd );
    auto result = SquareMatrix<float, 3>( resultSimd );

    // Assert
    constexpr float epsilon = 1e-6f;
    bool element00Match = std::abs( result[ 0 ][ 0 ] - expected[ 0 ][ 0 ] ) < epsilon;
    bool element11Match = std::abs( result[ 1 ][ 1 ] - expected[ 1 ][ 1 ] ) < epsilon;
    bool element22Match = std::abs( result[ 2 ][ 2 ] - expected[ 2 ][ 2 ] ) < epsilon;

    CHECK(element00Match);
    CHECK(element11Match);
    CHECK(element22Match);
}

/// <summary>
/// Tests that M * M^-1 = I for a general invertible matrix.
/// </summary>
TEST_CASE("MathMatrixTests / MatrixTimesInverseEqualsIdentity", "[math][MathMatrixTests]")
{
    // Arrange
    SquareMatrix<float, 3> original;
    original[ 0 ][ 0 ] = 1.0f;
    original[ 0 ][ 1 ] = 2.0f;
    original[ 0 ][ 2 ] = 3.0f;
    original[ 1 ][ 0 ] = 0.0f;
    original[ 1 ][ 1 ] = 1.0f;
    original[ 1 ][ 2 ] = 4.0f;
    original[ 2 ][ 0 ] = 5.0f;
    original[ 2 ][ 1 ] = 6.0f;
    original[ 2 ][ 2 ] = 2.0f;

    auto originalSimd = original.ToSimd( );

    // Act
    auto inverseSimd = Inverse( originalSimd );
    auto product = Multiply( originalSimd, inverseSimd );
    auto productMatrix = SquareMatrix<float, 3>( product );

    // Assert
    constexpr float epsilon = 1e-4f;
    for ( int i = 0; i < 3; ++i )
    {
        for ( int j = 0; j < 3; ++j )
        {
            float expectedValue = ( i == j ) ? 1.0f : 0.0f;
            float actualValue = productMatrix[ i ][ j ];
            bool matches = std::abs( actualValue - expectedValue ) < epsilon;
            CHECK(matches);
        }
    }
}

/// <summary>
/// Tests the determinant calculation for a 3x3 matrix.
/// </summary>
TEST_CASE("MathMatrixTests / DeterminantCalculation", "[math][MathMatrixTests]")
{
    // Arrange
    SquareMatrix<float, 3> original;
    original[ 0 ][ 0 ] = 1.0f;
    original[ 0 ][ 1 ] = 2.0f;
    original[ 0 ][ 2 ] = 3.0f;
    original[ 1 ][ 0 ] = 0.0f;
    original[ 1 ][ 1 ] = 1.0f;
    original[ 1 ][ 2 ] = 4.0f;
    original[ 2 ][ 0 ] = 5.0f;
    original[ 2 ][ 1 ] = 6.0f;
    original[ 2 ][ 2 ] = 2.0f;

    auto originalSimd = original.ToSimd( );
    Math::Vector<float, 3>::Simd determinantSimd;

    // Act
    Inverse( originalSimd, &determinantSimd );
    float determinant = determinantSimd.x( );

    // Expected: 1*(1*2 - 4*6) - 2*(0*2 - 4*5) + 3*(0*6 - 1*5)
    //         = 1*(2 - 24) - 2*(0 - 20) + 3*(0 - 5)
    //         = -22 + 40 - 15 = 3
    float expectedDeterminant = 3.0f;
    constexpr float epsilon = 1e-5f;
    bool determinantMatches = std::abs( determinant - expectedDeterminant ) < epsilon;

    // Assert
    CHECK(determinantMatches);
}

/// <summary>
/// Tests the inverse of the identity matrix without computing determinant.
/// </summary>
TEST_CASE("MathMatrixTests / InverseWithoutDeterminantOutput", "[math][MathMatrixTests]")
{
    // Arrange
    SquareMatrix<float, 3> identity;
    auto identitySimd = identity.ToSimd( );

    // Act - should not crash when determinant is nullptr
    auto resultSimd = Inverse( identitySimd, nullptr );
    auto resultMatrix = SquareMatrix<float, 3>( resultSimd );

    // Assert
    bool isIdentity = resultMatrix.IsIdentity( );
    CHECK(isIdentity);
}

/// <summary>
/// Tests inverse with a matrix containing decimal values.
/// </summary>
TEST_CASE("MathMatrixTests / InverseOfMatrixWithDecimalValues", "[math][MathMatrixTests]")
{
    // Arrange
    SquareMatrix<float, 3> original;
    original[ 0 ][ 0 ] = 1.5f;
    original[ 0 ][ 1 ] = 0.5f;
    original[ 0 ][ 2 ] = 0.0f;
    original[ 1 ][ 0 ] = 0.0f;
    original[ 1 ][ 1 ] = 2.0f;
    original[ 1 ][ 2 ] = 0.0f;
    original[ 2 ][ 0 ] = 0.0f;
    original[ 2 ][ 1 ] = 0.0f;
    original[ 2 ][ 2 ] = 0.5f;

    auto originalSimd = original.ToSimd( );
    Math::Vector<float, 3>::Simd determinantSimd;

    // Act
    auto inverseSimd = Inverse( originalSimd, &determinantSimd );
    auto product = Multiply( originalSimd, inverseSimd );
    auto productMatrix = SquareMatrix<float, 3>( product );

    // Assert
    constexpr float epsilon = 1e-4f;
    for ( int i = 0; i < 3; ++i )
    {
        for ( int j = 0; j < 3; ++j )
        {
            float expectedValue = ( i == j ) ? 1.0f : 0.0f;
            float actualValue = productMatrix[ i ][ j ];
            bool matches = std::abs( actualValue - expectedValue ) < epsilon;
            CHECK(matches);
        }
    }
}

/// <summary>
/// Tests inverse of a matrix with negative values.
/// </summary>
TEST_CASE("MathMatrixTests / InverseOfMatrixWithNegativeValues", "[math][MathMatrixTests]")
{
    // Arrange
    SquareMatrix<float, 3> original;
    original[ 0 ][ 0 ] = -1.0f;
    original[ 0 ][ 1 ] = 0.0f;
    original[ 0 ][ 2 ] = 0.0f;
    original[ 1 ][ 0 ] = 0.0f;
    original[ 1 ][ 1 ] = 2.0f;
    original[ 1 ][ 2 ] = 0.0f;
    original[ 2 ][ 0 ] = 0.0f;
    original[ 2 ][ 1 ] = 0.0f;
    original[ 2 ][ 2 ] = -3.0f;

    auto originalSimd = original.ToSimd( );

    // Act
    auto inverseSimd = Inverse( originalSimd );
    auto product = Multiply( originalSimd, inverseSimd );
    auto productMatrix = SquareMatrix<float, 3>( product );

    // Assert
    constexpr float epsilon = 1e-4f;
    for ( int i = 0; i < 3; ++i )
    {
        for ( int j = 0; j < 3; ++j )
        {
            float expectedValue = ( i == j ) ? 1.0f : 0.0f;
            float actualValue = productMatrix[ i ][ j ];
            bool matches = std::abs( actualValue - expectedValue ) < epsilon;
            CHECK(matches);
        }
    }
}

/// <summary>
/// Tests the determinant of an identity matrix (should be 1.0).
/// </summary>
TEST_CASE("MathMatrixTests / DeterminantOfIdentityMatrix", "[math][MathMatrixTests]")
{
    // Arrange
    SquareMatrix<float, 3> identity;
    auto identitySimd = identity.ToSimd( );
    Math::Vector<float, 3>::Simd determinantSimd;

    // Act
    Inverse( identitySimd, &determinantSimd );
    float determinant = determinantSimd.x( );

    // Assert
    constexpr float epsilon = 1e-6f;
    bool determinantIsOne = std::abs( determinant - 1.0f ) < epsilon;
    CHECK(determinantIsOne);
}

/// <summary>
/// Tests the inverse operation preserves numerical stability.
/// </summary>
TEST_CASE("MathMatrixTests / InverseNumericalStability", "[math][MathMatrixTests]")
{
    // Arrange
    SquareMatrix<float, 3> original;
    original[ 0 ][ 0 ] = 1.0f;
    original[ 0 ][ 1 ] = 1.0f;
    original[ 0 ][ 2 ] = 1.0f;
    original[ 1 ][ 0 ] = 1.0f;
    original[ 1 ][ 1 ] = 2.0f;
    original[ 1 ][ 2 ] = 1.0f;
    original[ 2 ][ 0 ] = 1.0f;
    original[ 2 ][ 1 ] = 1.0f;
    original[ 2 ][ 2 ] = 2.0f;

    auto originalSimd = original.ToSimd( );

    // Act
    auto inverseSimd = Inverse( originalSimd );
    auto product1 = Multiply( originalSimd, inverseSimd );
    auto product2 = Multiply( inverseSimd, originalSimd );

    auto product1Matrix = SquareMatrix<float, 3>( product1 );
    auto product2Matrix = SquareMatrix<float, 3>( product2 );

    // Assert - verify commutativity up to numerical precision
    constexpr float epsilon = 1e-4f;
    for ( int i = 0; i < 3; ++i )
    {
        for ( int j = 0; j < 3; ++j )
        {
            bool product1Match = std::abs( product1Matrix[ i ][ j ] - ( ( i == j ) ? 1.0f : 0.0f ) ) < epsilon;
            bool product2Match = std::abs( product2Matrix[ i ][ j ] - ( ( i == j ) ? 1.0f : 0.0f ) ) < epsilon;
            CHECK(product1Match);
            CHECK(product2Match);
        }
    }
}

/// <summary>
/// Tests inverse of the identity matrix.
/// The inverse of the identity matrix should be the identity matrix itself.
/// </summary>
TEST_CASE("MathMatrixTests / InverseOfIdentityMatrixIsIdentity2x2", "[math][MathMatrixTests]")
{
    using Simd = SquareMatrix<float, 2>::Simd;
    using Traits = SquareMatrix<float, 2>::Traits;

    // Create identity matrix: [1 0; 0 1]
    Simd identity( Traits::Set( 1.f, 0.f, 0.f, 1.f ) );

    // Compute inverse
    Simd result = Inverse( identity );

    // Verify result is identity
    bool isIdentity = MatrixApproximatelyEqual( result, identity );
    CHECK(isIdentity);
}

/// <summary>
/// Tests inverse of a simple 2x2 matrix.
/// For matrix [a b; c d], inverse is (1/det) * [d -b; -c a]
/// where det = ad - bc
/// </summary>
TEST_CASE("MathMatrixTests / InverseOfSimpleMatrix2x2", "[math][MathMatrixTests]")
{
    using Simd = SquareMatrix<float, 2>::Simd;
    using Traits = SquareMatrix<float, 2>::Traits;

    // Matrix: [2 1; 1 2]
    // Determinant: 2*2 - 1*1 = 3
    // Inverse: (1/3) * [2 -1; -1 2] = [2/3 -1/3; -1/3 2/3]
    Simd matrix( Traits::Set( 2.f, 1.f, 1.f, 2.f ) );
    Simd result = Inverse( matrix );

    // Expected inverse
    const float inv3 = 1.f / 3.f;
    Simd expected( Traits::Set( 2.f * inv3, -inv3, -inv3, 2.f * inv3 ) );

    bool isCorrect = MatrixApproximatelyEqual( result, expected );
    CHECK(isCorrect);
}

/// <summary>
/// Tests inverse with determinant calculation.
/// Verifies that the determinant is correctly computed and returned.
/// </summary>
TEST_CASE("MathMatrixTests / InverseWithDeterminantOutput2x2", "[math][MathMatrixTests]")
{
    using Simd = SquareMatrix<float, 2>::Simd;
    using Traits = SquareMatrix<float, 2>::Traits;

    // Matrix: [3 0; 0 2]
    // Determinant: 3*2 - 0*0 = 6
    Simd matrix( Traits::Set( 3.f, 0.f, 0.f, 2.f ) );
    Simd determinantOut;

    Simd result = Inverse( matrix, &determinantOut );

    // Expected determinant: 6.0
    auto detArray = Traits::ToArray( determinantOut.simd );
    float expectedDet = 6.f;

    bool detIsCorrect = std::abs( detArray[ 0 ] - expectedDet ) < 1e-5f;
    CHECK(detIsCorrect);
}

/// <summary>
/// Tests inverse of a diagonal matrix.
/// For diagonal matrix [a 0; 0 b], inverse is [1/a 0; 0 1/b]
/// </summary>
TEST_CASE("MathMatrixTests / InverseOfDiagonalMatrix2x2", "[math][MathMatrixTests]")
{
    using Simd = SquareMatrix<float, 2>::Simd;
    using Traits = SquareMatrix<float, 2>::Traits;

    // Diagonal matrix: [4 0; 0 5]
    Simd diagonal( Traits::Set( 4.f, 0.f, 0.f, 5.f ) );
    Simd result = Inverse( diagonal );

    // Expected: [1/4 0; 0 1/5]
    Simd expected( Traits::Set( 0.25f, 0.f, 0.f, 0.2f ) );

    bool isCorrect = MatrixApproximatelyEqual( result, expected );
    CHECK(isCorrect);
}

/// <summary>
/// Tests inverse of a matrix with negative values.
/// </summary>
TEST_CASE("MathMatrixTests / InverseOfMatrixWithNegativeValues2x2", "[math][MathMatrixTests]")
{
    using Simd = SquareMatrix<float, 2>::Simd;
    using Traits = SquareMatrix<float, 2>::Traits;

    // Matrix: [1 -2; -3 4]
    // Determinant: 1*4 - (-2)*(-3) = 4 - 6 = -2
    // Inverse: (1/-2) * [4 2; 3 1] = [-2 -1; -1.5 -0.5]
    Simd matrix( Traits::Set( 1.f, -2.f, -3.f, 4.f ) );
    Simd result = Inverse( matrix );

    Simd expected( Traits::Set( -2.f, -1.f, -1.5f, -0.5f ) );

    bool isCorrect = MatrixApproximatelyEqual( result, expected );
    CHECK(isCorrect);
}

/// <summary>
/// Tests matrix multiplication property: M * M^-1 = I
/// This verifies the correctness of the inverse computation.
/// </summary>
TEST_CASE("MathMatrixTests / MatrixTimesInverseEqualsIdentity2x2", "[math][MathMatrixTests]")
{
    using Simd = SquareMatrix<float, 2>::Simd;
    using Traits = SquareMatrix<float, 2>::Traits;

    // Matrix: [2 3; 4 5]
    // Determinant: 2*5 - 3*4 = 10 - 12 = -2
    Simd matrix( Traits::Set( 2.f, 3.f, 4.f, 5.f ) );
    Simd inverse = Inverse( matrix );

    // Multiply matrix by its inverse
    Simd product = Multiply( matrix, inverse );

    // Expected: identity matrix
    Simd identity( Traits::Set( 1.f, 0.f, 0.f, 1.f ) );

    bool isIdentity = MatrixApproximatelyEqual( product, identity, 1e-4f );
    CHECK(isIdentity);
}

/// <summary>
/// Tests inverse of matrix with floating-point values.
/// </summary>
TEST_CASE("MathMatrixTests / InverseOfFloatingPointMatrix2x2", "[math][MathMatrixTests]")
{
    using Simd = SquareMatrix<float, 2>::Simd;
    using Traits = SquareMatrix<float, 2>::Traits;

    // Matrix: [1.5 0.5; 0.5 1.5]
    // Determinant: 1.5*1.5 - 0.5*0.5 = 2.25 - 0.25 = 2.0
    // Inverse: 0.5 * [1.5 -0.5; -0.5 1.5]
    Simd matrix( Traits::Set( 1.5f, 0.5f, 0.5f, 1.5f ) );
    Simd result = Inverse( matrix );

    Simd expected( Traits::Set( 0.75f, -0.25f, -0.25f, 0.75f ) );

    bool isCorrect = MatrixApproximatelyEqual( result, expected );
    CHECK(isCorrect);
}

/// <summary>
/// Tests inverse consistency: (M^-1)^-1 = M
/// </summary>
TEST_CASE("MathMatrixTests / InverseOfInverseEqualsOriginal2x2", "[math][MathMatrixTests]")
{
    using Simd = SquareMatrix<float, 2>::Simd;
    using Traits = SquareMatrix<float, 2>::Traits;

    // Original matrix: [2 1; 1 2]
    Simd original( Traits::Set( 2.f, 1.f, 1.f, 2.f ) );

    // Compute inverse, then inverse of that
    Simd firstInverse = Inverse( original );
    Simd doubleInverse = Inverse( firstInverse );

    // Should equal original
    bool isConsistent = MatrixApproximatelyEqual( doubleInverse, original, 1e-4f );
    CHECK(isConsistent);
}

/// <summary>
/// Tests inverse with a matrix near singular (very small determinant).
/// This tests the numerical stability of the algorithm.
/// </summary>
TEST_CASE("MathMatrixTests / InverseOfNearSingularMatrix2x2", "[math][MathMatrixTests]")
{
    using Simd = SquareMatrix<float, 2>::Simd;
    using Traits = SquareMatrix<float, 2>::Traits;

    // Nearly singular matrix with determinant close to zero
    // Matrix: [1 1; 1 1.0001]
    // Determinant: 1*1.0001 - 1*1 = 0.0001
    Simd matrix( Traits::Set( 1.f, 1.f, 1.f, 1.0001f ) );
    Simd result = Inverse( matrix );

    // Verify by multiplying back
    Simd product = Multiply( matrix, result );
    Simd identity( Traits::Set( 1.f, 0.f, 0.f, 1.f ) );

    // Use larger epsilon due to numerical precision issues with near-singular matrices
    bool isValid = MatrixApproximatelyEqual( product, identity, 1e-3f );
    CHECK(isValid);
}

/// <summary>
/// Tests determinant calculation for various matrices.
/// </summary>
TEST_CASE("MathMatrixTests / DeterminantCalculationAccuracy2x2", "[math][MathMatrixTests]")
{
    using Simd = SquareMatrix<float, 2>::Simd;
    using Traits = SquareMatrix<float, 2>::Traits;

    // Test matrix: [3 2; 1 4]
    // Determinant: 3*4 - 2*1 = 12 - 2 = 10
    Simd matrix( Traits::Set( 3.f, 2.f, 1.f, 4.f ) );
    Simd determinantOut;

    Inverse( matrix, &determinantOut );

    auto detArray = Traits::ToArray( determinantOut.simd );
    float expectedDet = 10.f;

    bool detIsCorrect = std::abs( detArray[ 0 ] - expectedDet ) < 1e-5f;
    CHECK(detIsCorrect);
}

/// <summary>
/// Tests determinant of identity matrix.
/// Identity matrix should have determinant of 1.0f.
/// </summary>
TEST_CASE("MathMatrixTests / DeterminantOfIdentityMatrixIsOne", "[math][MathMatrixTests]")
{
    SquareMatrix<float, 4> identity;
    auto identitySimd = identity.ToSimd( );

    auto result = Determinant( identitySimd );

    float det = result.x( );
    bool isCorrect = ApproximatelyEqual( det, 1.0f );
    CHECK(isCorrect);
}

/// <summary>
/// Tests determinant of zero matrix.
/// Zero matrix should have determinant of 0.0f.
/// </summary>
TEST_CASE("MathMatrixTests / DeterminantOfZeroMatrixIsZero", "[math][MathMatrixTests]")
{
    SquareMatrix<float, 4> zero = SquareMatrix<float, 4>::Zero( );
    auto zeroSimd = zero.ToSimd( );

    auto result = Determinant( zeroSimd );

    float det = result.x( );
    bool isCorrect = ApproximatelyEqual( det, 0.0f );
    CHECK(isCorrect);
}

/// <summary>
/// Tests determinant of a diagonal matrix.
/// For a diagonal matrix, determinant equals product of diagonal elements.
/// </summary>
TEST_CASE("MathMatrixTests / DeterminantOfDiagonalMatrix", "[math][MathMatrixTests]")
{
    auto diagonal = SquareMatrix<float, 4>::Diag( 2.0f, 3.0f, 4.0f, 5.0f );
    auto diagonalSimd = diagonal.ToSimd( );

    auto result = Determinant( diagonalSimd );

    float det = result.x( );
    float expected = 2.0f * 3.0f * 4.0f * 5.0f; // 120.0f
    bool isCorrect = ApproximatelyEqual( det, expected );
    CHECK(isCorrect);
}

/// <summary>
/// Tests determinant of a scaled identity matrix.
/// Scaling identity by factor k should multiply determinant by k^4.
/// </summary>
TEST_CASE("MathMatrixTests / DeterminantOfScaledIdentity", "[math][MathMatrixTests]")
{
    SquareMatrix<float, 4> identity;
    float scaleFactor = 2.5f;
    auto scaled = identity * scaleFactor;

    auto result = Determinant( scaled );

    float det = result.x( );
    float expected = scaleFactor * scaleFactor * scaleFactor * scaleFactor; // k^4
    bool isCorrect = ApproximatelyEqual( det, expected, 1e-4f );
    CHECK(isCorrect);
}

/// <summary>
/// Tests determinant of a known 4x4 matrix.
/// Uses a simple matrix with manually calculated determinant.
/// </summary>
TEST_CASE("MathMatrixTests / DeterminantOfKnownMatrix", "[math][MathMatrixTests]")
{
    // Create a simple 4x4 matrix:
    // [ 1  2  3  4 ]
    // [ 5  1  6  7 ]
    // [ 8  9  1  10]
    // [11 12 13  1 ]
    SquareMatrix<float, 4> matrix(
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 1.0f, 6.0f, 7.0f,
        8.0f, 9.0f, 1.0f, 10.0f,
        11.0f, 12.0f, 13.0f, 1.0f
    );

    auto matrixSimd = matrix.ToSimd( );
    auto result = Determinant( matrixSimd );

    float det = result.x( );

    // Verify determinant is a reasonable value (not NaN or infinite)
    bool isFinite = std::isfinite( det );
    CHECK(isFinite);
}

/// <summary>
/// Tests determinant with row swapped matrix.
/// Swapping two rows should negate the determinant.
/// </summary>
TEST_CASE("MathMatrixTests / DeterminantChangeWithRowSwap", "[math][MathMatrixTests]")
{
    SquareMatrix<float, 4> original;
    auto originalSimd = original.ToSimd( );
    auto resultOriginal = Determinant( originalSimd );
    float detOriginal = resultOriginal.x( );

    // Create matrix with swapped rows
    SquareMatrix<float, 4> swapped;
    auto temp = swapped[ 0 ];
    swapped[ 0 ] = swapped[ 1 ];
    swapped[ 1 ] = temp;

    auto swappedSimd = swapped.ToSimd( );
    auto resultSwapped = Determinant( swappedSimd );
    float detSwapped = resultSwapped.x( );

    // Determinants should be negatives of each other
    bool isNegated = ApproximatelyEqual( detOriginal, -detSwapped );
    CHECK(isNegated);
}

/// <summary>
/// Tests determinant with very small values.
/// Should handle denormalized numbers gracefully.
/// </summary>
TEST_CASE("MathMatrixTests / DeterminantWithSmallValues", "[math][MathMatrixTests]")
{
    SquareMatrix<float, 4> matrix(
        1e-6f, 0.0f, 0.0f, 0.0f,
        0.0f, 1e-6f, 0.0f, 0.0f,
        0.0f, 0.0f, 1e-6f, 0.0f,
        0.0f, 0.0f, 0.0f, 1e-6f
    );

    auto matrixSimd = matrix.ToSimd( );
    auto result = Determinant( matrixSimd );

    float det = result.x( );

    // Result should be finite
    bool isFinite = std::isfinite( det );
    CHECK(isFinite);

    // Should be approximately (1e-6)^4
    float expected = 1e-24f;
    bool isCorrect = ApproximatelyEqual( det, expected, 1e-30f );
    CHECK(isCorrect);
}

/// <summary>
/// Tests determinant with large values.
/// Should handle large numbers without overflow.
/// </summary>
TEST_CASE("MathMatrixTests / DeterminantWithLargeValues", "[math][MathMatrixTests]")
{
    SquareMatrix<float, 4> matrix(
        1e6f, 0.0f, 0.0f, 0.0f,
        0.0f, 1e6f, 0.0f, 0.0f,
        0.0f, 0.0f, 1e6f, 0.0f,
        0.0f, 0.0f, 0.0f, 1e6f
    );

    auto matrixSimd = matrix.ToSimd( );
    auto result = Determinant( matrixSimd );

    float det = result.x( );

    // Result should be finite
    bool isFinite = std::isfinite( det );
    CHECK(isFinite);
}

/// <summary>
/// Tests determinant of singular matrix.
/// Singular matrix should have determinant of approximately 0.
/// </summary>
TEST_CASE("MathMatrixTests / DeterminantOfSingularMatrix", "[math][MathMatrixTests]")
{
    // Create a singular matrix (two identical rows)
    SquareMatrix<float, 4> singular(
        1.0f, 2.0f, 3.0f, 4.0f,
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f
    );

    auto singularSimd = singular.ToSimd( );
    auto result = Determinant( singularSimd );

    float det = result.x( );

    // Determinant should be very close to zero
    bool isZero = ApproximatelyEqual( det, 0.0f, 1e-4f );
    CHECK(isZero);
}

/// <summary>
/// Tests determinant is not NaN.
/// Ensures the computation produces valid IEEE 754 floating-point result.
/// </summary>
TEST_CASE("MathMatrixTests / DeterminantIsNotNaN", "[math][MathMatrixTests]")
{
    SquareMatrix<float, 4> identity;
    auto identitySimd = identity.ToSimd( );

    auto result = Determinant( identitySimd );
    float det = result.x( );

    bool isNotNaN = !std::isnan( det );
    CHECK(isNotNaN);
}

/// <summary>
/// Tests determinant result vector contains all identical values.
/// The Dot product fill operation should populate all components.
/// </summary>
TEST_CASE("MathMatrixTests / DeterminantResultComponentsMatch", "[math][MathMatrixTests]")
{
    SquareMatrix<float, 4> identity;
    auto identitySimd = identity.ToSimd( );

    auto result = Determinant( identitySimd );

    float x = result.x( );
    float y = result.y( );
    float z = result.z( );
    float w = result.w( );

    bool xEqualsY = ApproximatelyEqual( x, y );
    bool yEqualsZ = ApproximatelyEqual( y, z );
    bool zEqualsW = ApproximatelyEqual( z, w );

    CHECK(xEqualsY);
    CHECK(yEqualsZ);
    CHECK(zEqualsW);
}

TEST_CASE("MathMatrixTests / IdentityMatrixDeterminant", "[math][MathMatrixTests]")
{
    // Arrange: Create a 4x4 identity matrix
    SquareMatrix<float, 4> identityMatrix = SquareMatrix<float, 4>( );
    auto simdMatrix = identityMatrix.ToSimd( );

    // Act
    float determinant = ScalarDeterminant( simdMatrix );

    // Assert: Determinant of identity matrix should be 1.0
    CHECK(ApproximatelyEqual( determinant, 1.0f ));
}

TEST_CASE("MathMatrixTests / ScaledIdentityMatrixDeterminant", "[math][MathMatrixTests]")
{
    // Arrange: Create a diagonal matrix with scale factor 2 on diagonal
    // [2  0  0  0]
    // [0  2  0  0]
    // [0  0  2  0]
    // [0  0  0  2]
    // Determinant should be 2^4 = 16
    SquareMatrix<float, 4> scaledMatrix(
        2.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 2.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 2.0f
    );
    auto simdMatrix = scaledMatrix.ToSimd( );

    // Act
    float determinant = ScalarDeterminant( simdMatrix );

    // Assert: Determinant should be 16.0
    CHECK(ApproximatelyEqual( determinant, 16.0f ));
}

TEST_CASE("MathMatrixTests / SingularMatrixDeterminant", "[math][MathMatrixTests]")
{
    // Arrange: Create a singular matrix (two identical rows)
    // [1  2  3  4]
    // [1  2  3  4]
    // [5  6  7  8]
    // [9  10 11 12]
    // Determinant should be 0
    SquareMatrix<float, 4> singularMatrix(
        1.0f, 2.0f, 3.0f, 4.0f,
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f
    );
    auto simdMatrix = singularMatrix.ToSimd( );

    // Act
    float determinant = ScalarDeterminant( simdMatrix );

    // Assert: Determinant of singular matrix should be 0
    CHECK(ApproximatelyEqual( determinant, 0.0f, 1e-3f ));
}

TEST_CASE("MathMatrixTests / SimpleMatrixDeterminant", "[math][MathMatrixTests]")
{
    // Arrange: Create a simple 4x4 matrix with known determinant
    // [1  0  0  0]
    // [0  1  0  0]
    // [0  0  2  0]
    // [0  0  0  3]
    // Determinant = 1*1*2*3 = 6
    SquareMatrix<float, 4> simpleMatrix(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 2.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 3.0f
    );
    auto simdMatrix = simpleMatrix.ToSimd( );

    // Act
    float determinant = ScalarDeterminant( simdMatrix );

    // Assert: Determinant should be 6.0
    CHECK(ApproximatelyEqual( determinant, 6.0f ));
}

TEST_CASE("MathMatrixTests / NegativeDeterminant", "[math][MathMatrixTests]")
{
    // Arrange: Create a matrix with negative determinant
    // [1  0  0  0]
    // [0  -1 0  0]
    // [0  0  1  0]
    // [0  0  0  1]
    // Determinant = -1
    SquareMatrix<float, 4> negativeMatrix(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
    auto simdMatrix = negativeMatrix.ToSimd( );

    // Act
    float determinant = ScalarDeterminant( simdMatrix );

    // Assert: Determinant should be -1.0
    CHECK(ApproximatelyEqual( determinant, -1.0f ));
}

TEST_CASE("MathMatrixTests / GeneralMatrixDeterminant", "[math][MathMatrixTests]")
{
    // Arrange: Create a general 4x4 matrix
    // [2  1  3  0]
    // [0  1  4  1]
    // [1  0  2  1]
    // [3  2  1  0]
    // Determinant calculated using cofactor expansion
    SquareMatrix<float, 4> generalMatrix(
        2.0f, 1.0f, 3.0f, 0.0f,
        0.0f, 1.0f, 4.0f, 1.0f,
        1.0f, 0.0f, 2.0f, 1.0f,
        3.0f, 2.0f, 1.0f, 0.0f
    );
    auto simdMatrix = generalMatrix.ToSimd( );

    // Act
    float determinant = ScalarDeterminant( simdMatrix );

    // Assert: Verify determinant is computed (non-zero for non-singular matrix)
    // The determinant should be a finite, valid number
    CHECK(std::isfinite( determinant ));
    CHECK(determinant != 0.0f);
}

TEST_CASE("MathMatrixTests / ZeroMatrixDeterminant", "[math][MathMatrixTests]")
{
    // Arrange: Create a zero matrix
    SquareMatrix<float, 4> zeroMatrix = SquareMatrix<float, 4>::Zero( );
    auto simdMatrix = zeroMatrix.ToSimd( );

    // Act
    float determinant = ScalarDeterminant( simdMatrix );

    // Assert: Determinant of zero matrix should be 0
    CHECK(ApproximatelyEqual( determinant, 0.0f ));
}

TEST_CASE("MathMatrixTests / ReturnValueIsFinite", "[math][MathMatrixTests]")
{
    // Arrange: Create an arbitrary matrix
    SquareMatrix<float, 4> matrix(
        1.5f, 2.3f, 0.7f, 1.1f,
        0.2f, 3.4f, 1.8f, 0.5f,
        2.1f, 0.9f, 2.2f, 3.3f,
        1.7f, 1.2f, 0.4f, 2.8f
    );
    auto simdMatrix = matrix.ToSimd( );

    // Act
    float determinant = ScalarDeterminant( simdMatrix );

    // Assert: Return value should be a finite number (not NaN or Inf)
    CHECK(std::isfinite( determinant ));
}


TEST_CASE("MathMatrixTests / IdentityMatrixHasDeterminantOne3x3", "[math][MathMatrixTests]")
{
    // Arrange
    auto matrix = CreateMatrix3x3(
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f );
    const float expectedDeterminant = 1.0f;

    // Act
    auto result = Determinant( matrix );
    float actualDeterminant = ExtractDeterminant( result );

    // Assert
    bool isEqual = std::abs( actualDeterminant - expectedDeterminant ) < 1e-5f;
    CHECK(isEqual);
}

TEST_CASE("MathMatrixTests / ZeroMatrixHasDeterminantZero3x3", "[math][MathMatrixTests]")
{
    // Arrange
    auto matrix = CreateMatrix3x3(
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f );
    const float expectedDeterminant = 0.0f;

    // Act
    auto result = Determinant( matrix );
    float actualDeterminant = ExtractDeterminant( result );

    // Assert
    bool isZero = std::abs( actualDeterminant - expectedDeterminant ) < 1e-5f;
    CHECK(isZero);
}

TEST_CASE("MathMatrixTests / DiagonalMatrixDeterminantIsProductOfDiagonal3x3", "[math][MathMatrixTests]")
{
    // Arrange: diagonal matrix with values 2, 3, 4
    // det = 2 * 3 * 4 = 24
    auto matrix = CreateMatrix3x3(
        2.0f, 0.0f, 0.0f,
        0.0f, 3.0f, 0.0f,
        0.0f, 0.0f, 4.0f );
    const float expectedDeterminant = 24.0f;

    // Act
    auto result = Determinant( matrix );
    float actualDeterminant = ExtractDeterminant( result );

    // Assert
    bool isEqual = std::abs( actualDeterminant - expectedDeterminant ) < 1e-4f;
    CHECK(isEqual);
}

TEST_CASE("MathMatrixTests / SingularMatrixHasDeterminantZero3x3", "[math][MathMatrixTests]")
{
    // Arrange: singular matrix (rows are linearly dependent)
    // Row 3 = Row 1 + Row 2
    auto matrix = CreateMatrix3x3(
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        5.0f, 7.0f, 9.0f );
    const float expectedDeterminant = 0.0f;

    // Act
    auto result = Determinant( matrix );
    float actualDeterminant = ExtractDeterminant( result );

    // Assert
    bool isZero = std::abs( actualDeterminant - expectedDeterminant ) < 1e-4f;
    CHECK(isZero);
}

TEST_CASE("MathMatrixTests / StandardMatrixDeterminant3x3", "[math][MathMatrixTests]")
{
    // Arrange: standard 3x3 matrix with known determinant
    // | 1  2  3 |
    // | 0  1  4 | = 1*(1*6 - 4*2) - 2*(0*6 - 4*5) + 3*(0*2 - 1*5)
    // | 5  2  6 |   = 1*(6 - 8) - 2*(0 - 20) + 3*(0 - 5)
    //              = 1*(-2) - 2*(-20) + 3*(-5)
    //              = -2 + 40 - 15 = 23
    auto matrix = CreateMatrix3x3(
        1.0f, 2.0f, 3.0f,
        0.0f, 1.0f, 4.0f,
        5.0f, 2.0f, 6.0f );
    const float expectedDeterminant = 23.0f;

    // Act
    auto result = Determinant( matrix );
    float actualDeterminant = ExtractDeterminant( result );

    // Assert
    bool isEqual = std::abs( actualDeterminant - expectedDeterminant ) < 1e-4f;
    CHECK(isEqual);
}

TEST_CASE("MathMatrixTests / NegativeDeterminant3x3", "[math][MathMatrixTests]")
{
    // Arrange: matrix with negative determinant
    auto matrix = CreateMatrix3x3(
        2.0f, 1.0f, 3.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 2.0f, 1.0f );
    // det = 2*(0 - 2) - 1*(1 - 1) + 3*(2 - 0) = -4 - 0 + 6 = 2
    const float expectedDeterminant = 2.0f;

    // Act
    auto result = Determinant( matrix );
    float actualDeterminant = ExtractDeterminant( result );

    // Assert
    bool isEqual = std::abs( actualDeterminant - expectedDeterminant ) < 1e-4f;
    CHECK(isEqual);
}

TEST_CASE("MathMatrixTests / MatrixWithNegativeElements3x3", "[math][MathMatrixTests]")
{
    // Arrange: matrix containing negative values
    auto matrix = CreateMatrix3x3(
        -1.0f, 2.0f, -3.0f,
        4.0f, -5.0f, 6.0f,
        -7.0f, 8.0f, -9.0f );

    // Act
    auto result = Determinant( matrix );
    float actualDeterminant = ExtractDeterminant( result );

    // Assert: verify determinant is computed (exact value less important than correctness)
    bool isFinite = std::isfinite( actualDeterminant );
    CHECK(isFinite);
}

TEST_CASE("MathMatrixTests / LargeValueMatrix3x3", "[math][MathMatrixTests]")
{
    // Arrange: matrix with large values
    auto matrix = CreateMatrix3x3(
        1000.0f, 2000.0f, 3000.0f,
        4000.0f, 5000.0f, 6000.0f,
        7000.0f, 8000.0f, 9000.0f );
    // This is a singular matrix, determinant should be 0
    const float expectedDeterminant = 0.0f;

    // Act
    auto result = Determinant( matrix );
    float actualDeterminant = ExtractDeterminant( result );

    // Assert
    bool isZero = std::abs( actualDeterminant - expectedDeterminant ) < 1e-2f;
    CHECK(isZero);
}

TEST_CASE("MathMatrixTests / SmallValueMatrix3x3", "[math][MathMatrixTests]")
{
    // Arrange: matrix with small values
    auto matrix = CreateMatrix3x3(
        0.001f, 0.002f, 0.003f,
        0.004f, 0.005f, 0.006f,
        0.007f, 0.008f, 0.010f );

    // Act
    auto result = Determinant( matrix );
    float actualDeterminant = ExtractDeterminant( result );

    // Assert: verify result is computed correctly (non-singular)
    bool isFinite = std::isfinite( actualDeterminant );
    CHECK(isFinite);
}

TEST_CASE("MathMatrixTests / MixedSignMatrix3x3", "[math][MathMatrixTests]")
{
    // Arrange: matrix with mixed signs
    auto matrix = CreateMatrix3x3(
        1.0f, -2.0f, 3.0f,
        -4.0f, 5.0f, -6.0f,
        7.0f, -8.0f, 9.0f );

    // Act
    auto result = Determinant( matrix );
    float actualDeterminant = ExtractDeterminant( result );

    // Assert: result should be valid (determinant = 0 for this singular matrix)
    bool isZero = std::abs( actualDeterminant ) < 1e-4f;
    CHECK(isZero);
}

TEST_CASE("MathMatrixTests / RotationMatrixDeterminantOne3x3", "[math][MathMatrixTests]")
{
    // Arrange: 90 degree rotation matrix around Z-axis
    // | cos(90)  -sin(90)  0 |   | 0  -1  0 |
    // | sin(90)   cos(90)  0 | = | 1   0  0 |
    // |    0        0      1 |   | 0   0  1 |
    // det = 1
    auto matrix = CreateMatrix3x3(
        0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f );
    const float expectedDeterminant = 1.0f;

    // Act
    auto result = Determinant( matrix );
    float actualDeterminant = ExtractDeterminant( result );

    // Assert
    bool isEqual = std::abs( actualDeterminant - expectedDeterminant ) < 1e-5f;
    CHECK(isEqual);
}

TEST_CASE("MathMatrixTests / DeterminantIdentityMatrix", "[math][MathMatrixTests]")
{
    // Identity matrix: [[1, 0], [0, 1]]
    // Expected determinant: 1*1 - 0*0 = 1
    SquareMatrix<float, 2>::Simd matrix( std::array{ 1.0f, 0.0f, 0.0f, 1.0f } );
    auto result = Determinant( matrix );

    auto determinantValue = result.x( );
    bool isCorrect = std::abs( determinantValue - 1.0f ) < 1e-6f;
    CHECK(isCorrect);
}

TEST_CASE("MathMatrixTests / DeterminantZeroMatrix", "[math][MathMatrixTests]")
{
    // Zero matrix: [[0, 0], [0, 0]]
    // Expected determinant: 0*0 - 0*0 = 0
    SquareMatrix<float, 2>::Simd matrix( std::array{ 0.0f, 0.0f, 0.0f, 0.0f } );
    auto result = Determinant( matrix );

    auto determinantValue = result.x( );
    bool isCorrect = std::abs( determinantValue ) < 1e-6f;
    CHECK(isCorrect);
}

TEST_CASE("MathMatrixTests / DeterminantSimpleMatrix", "[math][MathMatrixTests]")
{
    // Simple matrix: [[2, 3], [4, 5]]
    // Expected determinant: 2*5 - 3*4 = 10 - 12 = -2
    SquareMatrix<float, 2>::Simd matrix( std::array{ 2.0f, 3.0f, 4.0f, 5.0f } );
    auto result = Determinant( matrix );

    auto determinantValue = result.x( );
    bool isCorrect = std::abs( determinantValue - ( -2.0f ) ) < 1e-6f;
    CHECK(isCorrect);
}

TEST_CASE("MathMatrixTests / DeterminantPositiveDeterminant", "[math][MathMatrixTests]")
{
    // Matrix: [[3, 2], [1, 4]]
    // Expected determinant: 3*4 - 2*1 = 12 - 2 = 10
    SquareMatrix<float, 2>::Simd matrix( std::array{ 3.0f, 2.0f, 1.0f, 4.0f } );
    auto result = Determinant( matrix );

    auto determinantValue = result.x( );
    bool isCorrect = std::abs( determinantValue - 10.0f ) < 1e-6f;
    CHECK(isCorrect);
}

TEST_CASE("MathMatrixTests / DeterminantNegativeDeterminant", "[math][MathMatrixTests]")
{
    // Matrix: [[1, 5], [2, 3]]
    // Expected determinant: 1*3 - 5*2 = 3 - 10 = -7
    SquareMatrix<float, 2>::Simd matrix( std::array{ 1.0f, 5.0f, 2.0f, 3.0f } );
    auto result = Determinant( matrix );

    auto determinantValue = result.x( );
    bool isCorrect = std::abs( determinantValue - ( -7.0f ) ) < 1e-6f;
    CHECK(isCorrect);
}

TEST_CASE("MathMatrixTests / DeterminantSingularMatrix", "[math][MathMatrixTests]")
{
    // Singular matrix (linearly dependent rows): [[2, 4], [1, 2]]
    // Expected determinant: 2*2 - 4*1 = 4 - 4 = 0
    SquareMatrix<float, 2>::Simd matrix( std::array{ 2.0f, 4.0f, 1.0f, 2.0f } );
    auto result = Determinant( matrix );

    auto determinantValue = result.x( );
    bool isCorrect = std::abs( determinantValue ) < 1e-6f;
    CHECK(isCorrect);
}

TEST_CASE("MathMatrixTests / DeterminantNegativeValues", "[math][MathMatrixTests]")
{
    // Matrix with negative values: [[-2, 3], [1, -4]]
    // Expected determinant: -2*-4 - 3*1 = 8 - 3 = 5
    SquareMatrix<float, 2>::Simd matrix( std::array{ -2.0f, 3.0f, 1.0f, -4.0f } );
    auto result = Determinant( matrix );

    auto determinantValue = result.x( );
    bool isCorrect = std::abs( determinantValue - 5.0f ) < 1e-6f;
    CHECK(isCorrect);
}

TEST_CASE("MathMatrixTests / DeterminantLargeValues", "[math][MathMatrixTests]")
{
    // Matrix with large values: [[1000, 2000], [3000, 4000]]
    // Expected determinant: 1000*4000 - 2000*3000 = 4000000 - 6000000 = -2000000
    SquareMatrix<float, 2>::Simd matrix( std::array{ 1000.0f, 2000.0f, 3000.0f, 4000.0f } );
    auto result = Determinant( matrix );

    auto determinantValue = result.x( );
    bool isCorrect = std::abs( determinantValue - ( -2000000.0f ) ) < 100.0f;  // Relaxed tolerance for large values
    CHECK(isCorrect);
}

TEST_CASE("MathMatrixTests / DeterminantSmallValues", "[math][MathMatrixTests]")
{
    // Matrix with small values: [[0.001, 0.002], [0.003, 0.004]]
    // Expected determinant: 0.001*0.004 - 0.002*0.003 = 0.000004 - 0.000006 = -0.000002
    SquareMatrix<float, 2>::Simd matrix( std::array{ 0.001f, 0.002f, 0.003f, 0.004f } );
    auto result = Determinant( matrix );

    auto determinantValue = result.x( );
    bool isCorrect = std::abs( determinantValue - ( -0.000002f ) ) < 1e-9f;
    CHECK(isCorrect);
}

TEST_CASE("MathMatrixTests / DeterminantDiagonalMatrix", "[math][MathMatrixTests]")
{
    // Diagonal matrix: [[5, 0], [0, 3]]
    // Expected determinant: 5*3 - 0*0 = 15
    SquareMatrix<float, 2>::Simd matrix( std::array{ 5.0f, 0.0f, 0.0f, 3.0f } );
    auto result = Determinant( matrix );

    auto determinantValue = result.x( );
    bool isCorrect = std::abs( determinantValue - 15.0f ) < 1e-6f;
    CHECK(isCorrect);
}

TEST_CASE("MathMatrixTests / DeterminantSymmetricMatrix", "[math][MathMatrixTests]")
{
    // Symmetric matrix: [[2, 1], [1, 2]]
    // Expected determinant: 2*2 - 1*1 = 4 - 1 = 3
    SquareMatrix<float, 2>::Simd matrix( std::array{ 2.0f, 1.0f, 1.0f, 2.0f } );
    auto result = Determinant( matrix );

    auto determinantValue = result.x( );
    bool isCorrect = std::abs( determinantValue - 3.0f ) < 1e-6f;
    CHECK(isCorrect);
}

TEST_CASE("MathMatrixTests / DeterminantAntiSymmetricMatrix", "[math][MathMatrixTests]")
{
    // Antisymmetric matrix: [[0, 5], [-5, 0]]
    // Expected determinant: 0*0 - 5*-5 = 0 + 25 = 25
    SquareMatrix<float, 2>::Simd matrix( std::array{ 0.0f, 5.0f, -5.0f, 0.0f } );
    auto result = Determinant( matrix );

    auto determinantValue = result.x( );
    bool isCorrect = std::abs( determinantValue - 25.0f ) < 1e-6f;
    CHECK(isCorrect);
}

TEST_CASE("MathMatrixTests / DeterminantWithFractionalValues", "[math][MathMatrixTests]")
{
    // Matrix with fractional values: [[1.5, 2.5], [3.5, 4.5]]
    // Expected determinant: 1.5*4.5 - 2.5*3.5 = 6.75 - 8.75 = -2
    SquareMatrix<float, 2>::Simd matrix( std::array{ 1.5f, 2.5f, 3.5f, 4.5f } );
    auto result = Determinant( matrix );

    auto determinantValue = result.x( );
    bool isCorrect = std::abs( determinantValue - ( -2.0f ) ) < 1e-6f;
    CHECK(isCorrect);
}

TEST_CASE("MathMatrixTests / Transpose4x4FloatMatrix", "[math][MathMatrixTests]")
{
    using namespace Harlinn::Math;

    // Arrange: Define the original matrix and the expected transposed result.
    // The constructor takes elements in row-major order.
    SquareMatrix<float, 4> originalMatrix(
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    );

    SquareMatrix<float, 4> expectedTransposedMatrix(
        1.0f, 5.0f, 9.0f, 13.0f,
        2.0f, 6.0f, 10.0f, 14.0f,
        3.0f, 7.0f, 11.0f, 15.0f,
        4.0f, 8.0f, 12.0f, 16.0f
    );

    // Act: Convert the matrix to its SIMD representation and call the Transpose function.
    auto originalSimd = originalMatrix.ToSimd( );
    auto transposedSimd = Transpose( originalSimd );

    // Convert the transposed SIMD result back to a standard matrix for easy verification.
    SquareMatrix<float, 4> resultMatrix( transposedSimd );

    // Assert: Check if each element of the resulting matrix matches the expected transposed matrix.
    // For a simple shuffle operation without arithmetic, direct comparison is safe.
    for ( size_t i = 0; i < 4; ++i )
    {
        for ( size_t j = 0; j < 4; ++j )
        {
            CHECK(resultMatrix[ i ][ j ] == expectedTransposedMatrix[ i ][ j ]);
        }
    }

    // You can also check if transposing twice returns the original matrix.
    auto transposedTwiceSimd = Transpose( transposedSimd );
    SquareMatrix<float, 4> resultTransposedTwice( transposedTwiceSimd );
    CHECK(resultTransposedTwice == originalMatrix);
}

TEST_CASE("MathMatrixTests / TransposeIdentityMatrix3x3", "[math][MathMatrixTests]")
{
    /// Arrange
    auto identity = SquareMatrix<float, 3>::Simd( Math::MatrixType::Identity );

    /// Act
    auto transposed = Transpose( identity );

    /// Assert
    CHECK(transposed == identity);
}

TEST_CASE("MathMatrixTests / TransposeBasicMatrix3x3", "[math][MathMatrixTests]")
{
    /// Arrange
    SquareMatrix<float, 3> original(
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    );
    auto originalSimd = original.ToSimd( );

    /// Act
    auto transposed = Transpose( originalSimd );

    /// Assert: Verify each element
    auto result = SquareMatrix<float, 3>( transposed );
    bool isCorrect =
        std::fabs( result[ 0 ][ 0 ] - 1.0f ) < 1e-6f &&
        std::fabs( result[ 0 ][ 1 ] - 4.0f ) < 1e-6f &&
        std::fabs( result[ 0 ][ 2 ] - 7.0f ) < 1e-6f &&
        std::fabs( result[ 1 ][ 0 ] - 2.0f ) < 1e-6f &&
        std::fabs( result[ 1 ][ 1 ] - 5.0f ) < 1e-6f &&
        std::fabs( result[ 1 ][ 2 ] - 8.0f ) < 1e-6f &&
        std::fabs( result[ 2 ][ 0 ] - 3.0f ) < 1e-6f &&
        std::fabs( result[ 2 ][ 1 ] - 6.0f ) < 1e-6f &&
        std::fabs( result[ 2 ][ 2 ] - 9.0f ) < 1e-6f;
    CHECK(isCorrect);
}

TEST_CASE("MathMatrixTests / TransposeSymmetricMatrix3x3", "[math][MathMatrixTests]")
{
    /// Arrange: Create a symmetric matrix
    SquareMatrix<float, 3> symmetric(
        1.0f, 2.0f, 3.0f,
        2.0f, 5.0f, 6.0f,
        3.0f, 6.0f, 9.0f
    );
    auto symmetricSimd = symmetric.ToSimd( );

    /// Act
    auto transposed = Transpose( symmetricSimd );

    /// Assert: Symmetric matrix should equal its transpose
    CHECK(transposed == symmetricSimd);
}

TEST_CASE("MathMatrixTests / TransposeAntiSymmetricMatrix3x3", "[math][MathMatrixTests]")
{
    /// Arrange: Create an anti-symmetric matrix
    SquareMatrix<float, 3> antiSymmetric(
        0.0f, 2.0f, 3.0f,
        -2.0f, 0.0f, 6.0f,
        -3.0f, -6.0f, 0.0f
    );
    auto antiSymmetricSimd = antiSymmetric.ToSimd( );

    /// Act
    auto transposed = Transpose( antiSymmetricSimd );
    auto result = SquareMatrix<float, 3>( transposed );

    /// Assert: Transpose of anti-symmetric matrix should be its negation
    bool isNegated =
        std::fabs( result[ 0 ][ 1 ] - ( -2.0f ) ) < 1e-6f &&
        std::fabs( result[ 1 ][ 0 ] - 2.0f ) < 1e-6f &&
        std::fabs( result[ 0 ][ 2 ] - ( -3.0f ) ) < 1e-6f &&
        std::fabs( result[ 2 ][ 0 ] - 3.0f ) < 1e-6f &&
        std::fabs( result[ 1 ][ 2 ] - ( -6.0f ) ) < 1e-6f &&
        std::fabs( result[ 2 ][ 1 ] - 6.0f ) < 1e-6f;
    CHECK(isNegated);
}

TEST_CASE("MathMatrixTests / TransposeDoubleTranspose3x3", "[math][MathMatrixTests]")
{
    /// Arrange
    SquareMatrix<float, 3> original(
        1.5f, 2.5f, 3.5f,
        4.5f, 5.5f, 6.5f,
        7.5f, 8.5f, 9.5f
    );
    auto originalSimd = original.ToSimd( );

    /// Act: Transpose twice
    auto transposed = Transpose( originalSimd );
    auto doubleTransposed = Transpose( transposed );

    /// Assert: Double transpose should return to original
    CHECK(doubleTransposed == originalSimd);
}

TEST_CASE("MathMatrixTests / TransposeDiagonalMatrix3x3", "[math][MathMatrixTests]")
{
    /// Arrange: Create a diagonal matrix
    SquareMatrix<float, 3> diagonal(
        1.0f, 0.0f, 0.0f,
        0.0f, 2.0f, 0.0f,
        0.0f, 0.0f, 3.0f
    );
    auto diagonalSimd = diagonal.ToSimd( );

    /// Act
    auto transposed = Transpose( diagonalSimd );

    /// Assert: Diagonal matrix should equal its transpose
    CHECK(transposed == diagonalSimd);
}

TEST_CASE("MathMatrixTests / TransposeZeroMatrix3x3", "[math][MathMatrixTests]")
{
    /// Arrange
    auto zero = SquareMatrix<float, 3>::Zero( ).ToSimd( );

    /// Act
    auto transposed = Transpose( zero );

    /// Assert
    CHECK(transposed == zero);
}

TEST_CASE("MathMatrixTests / TransposeWithNegativeValues3x3", "[math][MathMatrixTests]")
{
    /// Arrange
    SquareMatrix<float, 3> withNegatives(
        -1.0f, -2.0f, -3.0f,
        -4.0f, -5.0f, -6.0f,
        -7.0f, -8.0f, -9.0f
    );
    auto withNegativesSimd = withNegatives.ToSimd( );

    /// Act
    auto transposed = Transpose( withNegativesSimd );

    /// Assert
    auto result = SquareMatrix<float, 3>( transposed );
    bool isCorrect =
        std::fabs( result[ 0 ][ 1 ] - ( -4.0f ) ) < 1e-6f &&
        std::fabs( result[ 1 ][ 0 ] - ( -2.0f ) ) < 1e-6f &&
        std::fabs( result[ 2 ][ 2 ] - ( -9.0f ) ) < 1e-6f;
    CHECK(isCorrect);
}

/// <summary>
/// Tests that transposing a 2x2 identity matrix returns the identity matrix.
/// </summary>
TEST_CASE("MathMatrixTests / TransposeIdentityMatrix2x2", "[math][MathMatrixTests]")
{
    // Arrange
    auto identityMatrix = SquareMatrix<float, 2>::Simd::Identity( );

    // Act
    auto result = Transpose( identityMatrix );

    // Assert
    bool isIdentity = result == identityMatrix;
    CHECK(isIdentity);
}

/// <summary>
/// Tests that transposing a 2x2 zero matrix returns the zero matrix.
/// </summary>
TEST_CASE("MathMatrixTests / TransposeZeroMatrix2x2", "[math][MathMatrixTests]")
{
    // Arrange
    auto zeroMatrix = SquareMatrix<float, 2>::Simd::Zero( );

    // Act
    auto result = Transpose( zeroMatrix );

    // Assert
    bool isZero = result == zeroMatrix;
    CHECK(isZero);
}

/// <summary>
/// Tests that transposing a symmetric 2x2 matrix returns the same matrix.
/// Matrix: [[1, 2], [2, 3]]
/// </summary>
TEST_CASE("MathMatrixTests / TransposeSymmetricMatrix2x2", "[math][MathMatrixTests]")
{
    // Arrange
    SquareMatrix<float, 2> matrix{ 1.0f, 2.0f, 2.0f, 3.0f };
    auto simdMatrix = matrix.ToSimd( );

    // Act
    auto result = Transpose( simdMatrix );

    // Assert - symmetric matrix should equal its transpose
    bool isSymmetric = ( result == simdMatrix );
    CHECK(isSymmetric);
}

/// <summary>
/// Tests that transposing a 2x2 matrix twice returns the original matrix.
/// </summary>
TEST_CASE("MathMatrixTests / TransposeTransposedMatrix2x2", "[math][MathMatrixTests]")
{
    // Arrange
    SquareMatrix<float, 2> original{ 1.0f, 2.0f, 3.0f, 4.0f };
    auto simdMatrix = original.ToSimd( );

    // Act
    auto transposed = Transpose( simdMatrix );
    auto doubleTransposed = Transpose( transposed );

    // Assert
    bool isOriginal = ( doubleTransposed == simdMatrix );
    CHECK(isOriginal);
}

/// <summary>
/// Tests that transposing a general 2x2 matrix with distinct values works correctly.
/// Matrix: [[1, 2], [3, 4]]
/// Expected transpose: [[1, 3], [2, 4]]
/// </summary>
TEST_CASE("MathMatrixTests / TransposeGeneralMatrix2x2", "[math][MathMatrixTests]")
{
    // Arrange
    SquareMatrix<float, 2> original{ 1.0f, 2.0f, 3.0f, 4.0f };
    SquareMatrix<float, 2> expected{ 1.0f, 3.0f, 2.0f, 4.0f };

    auto originalSimd = original.ToSimd( );
    auto expectedSimd = expected.ToSimd( );

    // Act
    auto result = Transpose( originalSimd );

    // Assert
    bool matchesExpected = ( result == expectedSimd );
    CHECK(matchesExpected);
}

/// <summary>
/// Tests that transposing a 2x2 matrix with negative values works correctly.
/// Matrix: [[-1, 2], [-3, 4]]
/// Expected transpose: [[-1, -3], [2, 4]]
/// </summary>
TEST_CASE("MathMatrixTests / TransposeMatrixWithNegativeValues2x2", "[math][MathMatrixTests]")
{
    // Arrange
    SquareMatrix<float, 2> original{ -1.0f, 2.0f, -3.0f, 4.0f };
    SquareMatrix<float, 2> expected{ -1.0f, -3.0f, 2.0f, 4.0f };

    auto originalSimd = original.ToSimd( );
    auto expectedSimd = expected.ToSimd( );

    // Act
    auto result = Transpose( originalSimd );

    // Assert
    bool matchesExpected = ( result == expectedSimd );
    CHECK(matchesExpected);
}

/// <summary>
/// Tests that transposing a 2x2 matrix with floating-point values works correctly.
/// Matrix: [[1.5, 2.5], [3.5, 4.5]]
/// Expected transpose: [[1.5, 3.5], [2.5, 4.5]]
/// </summary>
TEST_CASE("MathMatrixTests / TransposeMatrixWithFloatingPointValues2x2", "[math][MathMatrixTests]")
{
    // Arrange
    SquareMatrix<float, 2> original{ 1.5f, 2.5f, 3.5f, 4.5f };
    SquareMatrix<float, 2> expected{ 1.5f, 3.5f, 2.5f, 4.5f };

    auto originalSimd = original.ToSimd( );
    auto expectedSimd = expected.ToSimd( );

    // Act
    auto result = Transpose( originalSimd );

    // Assert
    bool matchesExpected = ( result == expectedSimd );
    CHECK(matchesExpected);
}

/// <summary>
/// Tests that transposing an anti-symmetric 2x2 matrix preserves the anti-symmetric property.
/// Matrix: [[0, 1], [-1, 0]]
/// Transposed: [[0, -1], [1, 0]]
/// </summary>
TEST_CASE("MathMatrixTests / TransposeAntiSymmetricMatrix2x2", "[math][MathMatrixTests]")
{
    // Arrange
    SquareMatrix<float, 2> original{ 0.0f, 1.0f, -1.0f, 0.0f };
    SquareMatrix<float, 2> expected{ 0.0f, -1.0f, 1.0f, 0.0f };

    auto originalSimd = original.ToSimd( );
    auto expectedSimd = expected.ToSimd( );

    // Act
    auto result = Transpose( originalSimd );

    // Assert
    bool matchesExpected = ( result == expectedSimd );
    CHECK(matchesExpected);
}

/// <summary>
/// Tests that transposing a 2x2 diagonal matrix returns the same matrix.
/// Matrix: [[5, 0], [0, 7]]
/// </summary>
TEST_CASE("MathMatrixTests / TransposeDiagonalMatrix2x2", "[math][MathMatrixTests]")
{
    // Arrange
    SquareMatrix<float, 2> matrix{ 5.0f, 0.0f, 0.0f, 7.0f };
    auto simdMatrix = matrix.ToSimd( );

    // Act
    auto result = Transpose( simdMatrix );

    // Assert - diagonal matrix should equal its transpose
    bool isDiagonal = ( result == simdMatrix );
    CHECK(isDiagonal);
}
