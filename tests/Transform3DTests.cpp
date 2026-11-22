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
TEST_CASE("Transform3DTests / PointRotationAxisTest1", "[math][Transform3DTests]")
{
    using Constants = Math::Constants<float>;
    Math::Vector3f axis( 0.f, 1.f, 0.f );
    float angle = Constants::PiOver2;
    auto transformation = Math::RotationAxis( axis, angle );
    Math::Point3f p1( 2.f, 2.f, 2.f );
    Math::Point3f expected( 2.f, 2.f, -2.f );
    Math::Point3f result = Math::Transform( p1, transformation );
    auto equal = Equal( expected, result );
    CHECK(equal);
}
TEST_CASE("Transform3DTests / VectorRotationAxisTest1", "[math][Transform3DTests]")
{
    using Constants = Math::Constants<float>;
    Math::Vector3f axis( 0.f, 1.f, 0.f );
    float angle = Constants::PiOver2;
    auto transformation = Math::RotationAxis( axis, angle );
    Math::Vector<float,3> v1( 2.f, 2.f, 2.f );
    Math::Vector<float, 3> expected( 2.f, 2.f, -2.f );
    Math::Vector<float, 3> result = Math::Transform( v1, transformation );
    auto equal = Equal( expected, result );
    CHECK(equal);
}
TEST_CASE("Transform3DTests / NormalRotationAxisTest1", "[math][Transform3DTests]")
{
    using Constants = Math::Constants<float>;
    Math::Vector3f axis( 0.f, 1.f, 0.f );
    float angle = Constants::PiOver2;
    auto transformation = Math::RotationAxis( axis, angle );
    Math::Normal3f n1( 2.f, 2.f, 2.f );
    Math::Normal3f expected( 2.f, 2.f, -2.f );
    Math::Normal3f result = Math::Transform( n1, transformation );
    auto equal = Equal( expected, result );
    CHECK(equal);
}
TEST_CASE("Transform3DTests / PointTranslationTest1", "[math][Transform3DTests]")
{
    using Constants = Math::Constants<float>;
    
    float offsetX = 3.f;
    float offsetY = 2.f;
    float offsetZ = 1.f;
    auto transformation = Math::Translation( offsetX, offsetY, offsetZ );
    Math::Point3f p1( 2.f, 2.f, 2.f );
    Math::Point3f expected( 5.f, 4.f, 3.f );
    Math::Point3f result = Math::Transform( p1, transformation );
    auto equal = Equal( expected, result );
    CHECK(equal);
}
TEST_CASE("Transform3DTests / VectorTranslationTest1", "[math][Transform3DTests]")
{
    using Constants = Math::Constants<float>;

    float offsetX = 3.f;
    float offsetY = 2.f;
    float offsetZ = 1.f;
    auto transformation = Math::Translation( offsetX, offsetY, offsetZ );
    Math::Vector3f v1( 2.f, 2.f, 2.f );
    Math::Vector3f expected( 5.f, 4.f, 3.f );
    Math::Vector3f result = Math::Transform( v1, transformation );
    auto equal = Equal( expected, result );
    CHECK(equal);
}
TEST_CASE("Transform3DTests / NormalTranslationTest1", "[math][Transform3DTests]")
{
    using Constants = Math::Constants<float>;

    float offsetX = 3.f;
    float offsetY = 2.f;
    float offsetZ = 1.f;
    auto transformation = Math::Translation( offsetX, offsetY, offsetZ );
    Math::Normal3f n1( 2.f, 2.f, 2.f );
    Math::Normal3f expected( 2.f, 2.f, 2.f );
    Math::Normal3f result = Math::Transform( n1, transformation );
    auto equal = Equal( expected, result );
    CHECK(equal);
}
TEST_CASE("Transform3DTests / PointScalingTest1", "[math][Transform3DTests]")
{
    using Constants = Math::Constants<float>;

    float scalingX = 3.f;
    float scalingY = 2.f;
    float scalingZ = 1.f;
    auto transformation = Math::Scaling( scalingX, scalingY, scalingZ );
    Math::Point3f p1( 2.f, 2.f, 2.f );
    Math::Point3f expected( 6.f, 4.f, 2.f );
    Math::Point3f result = Math::Transform( p1, transformation );
    auto equal = Equal( expected, result );
    CHECK(equal);
}
TEST_CASE("Transform3DTests / VectorScalingTest1", "[math][Transform3DTests]")
{
    using Constants = Math::Constants<float>;

    float scalingX = 3.f;
    float scalingY = 2.f;
    float scalingZ = 1.f;
    auto transformation = Math::Scaling( scalingX, scalingY, scalingZ );
    Math::Vector3f v1( 2.f, 2.f, 2.f );
    Math::Vector3f expected( 6.f, 4.f, 2.f );
    Math::Vector3f result = Math::Transform( v1, transformation );
    auto equal = Equal( expected, result );
    CHECK(equal);
}
TEST_CASE("Transform3DTests / NormalScalingTest1", "[math][Transform3DTests]")
{
    using Constants = Math::Constants<float>;

    float scalingX = 3.f;
    float scalingY = 2.f;
    float scalingZ = 1.f;
    auto transformation = Math::Scaling( scalingX, scalingY, scalingZ );
    Math::Normal3f n1( 2.f, 2.f, 2.f );
    Math::Normal3f expected( 6.f, 4.f, 2.f );
    Math::Normal3f result = Math::Transform( n1, transformation );
    auto equal = Equal( expected, result );
    CHECK(equal);
}



#pragma optimize( "", off )
TEST_CASE("Transform3DTests / PointTransformationMatrixTest1", "[math][Transform3DTests]")
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    const Point3f scalingOrigin( 10.f, 10.f, 10.f );
    const Quaternion<float> scalingOrientationQuaternion( Constants::Pi * 0.6f, Constants::Pi * 0.6f, Constants::Pi * 0.6f );
    const Math::Vector<float, 3> scaling(.8f, .8f, .8f );
    const Math::Point3f rotationOrigin( 5.f, 5.f, 5.f );
    const Quaternion<float> rotationQuaternion( Constants::Pi * 0.3f, Constants::Pi * 0.3f, Constants::Pi * 0.3f );
    const Math::Vector<float, 3> translation( 4.f, 4.f, 4.f );

    auto transformation = Math::TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling, rotationOrigin, rotationQuaternion, translation );
    //PrintLn( L"Transformation: {}", transformation );

    Math::Point3f p1( 2.f, 2.f, 2.f );
    Math::Point3f expected( 7.23640394f, 8.98319530f, 7.33583355f );
    Math::Point3f::Simd result1 = Math::Transform( p1, transformation );
    auto equal = AllEqual( expected, result1, 1.0e-7f );
    if ( !equal )
    {
        PrintLn( L"Expected: {}", expected );
        PrintLn( L"Result1:   {}", result1 );
    }
    Math::Point3f result = result1;
    equal = AllEqual( expected, result, 1.0e-7f );
    if( !equal )
    {
        PrintLn(L"Expected: {}", expected );
        PrintLn(L"Result:   {}", result );
    }
    CHECK(equal);
}
#pragma optimize( "", on )
TEST_CASE("Transform3DTests / VectorTransformationMatrixTest1", "[math][Transform3DTests]")
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    const Point3f scalingOrigin( 10.f, 10.f, 10.f );
    const Quaternion<float> scalingOrientationQuaternion( Constants::Pi * 0.6f, Constants::Pi * 0.6f, Constants::Pi * 0.6f );
    const Math::Vector<float, 3> scaling( .8f, .8f, .8f );
    const Math::Point3f rotationOrigin( 5.f, 5.f, 5.f );
    const Quaternion<float> rotationQuaternion( Constants::Pi * 0.3f, Constants::Pi * 0.3f, Constants::Pi * 0.3f );
    const Math::Vector<float, 3> translation( 4.f, 4.f, 4.f );

    auto transformation = Math::TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling, rotationOrigin, rotationQuaternion, translation );
    Math::Vector3f v1( 2.f, 2.f, 2.f );
    Math::Vector3f expected( 7.23640394f, 8.98319530f, 7.33583355f );
    Math::Vector3f result = Math::Transform( v1, transformation );
    auto equal = AllEqual( expected, result, 1.0e-7f );
    CHECK(equal);
}
TEST_CASE("Transform3DTests / NormalTransformationMatrixTest1", "[math][Transform3DTests]")
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    const Point3f scalingOrigin( 10.f, 10.f, 10.f );
    const Quaternion<float> scalingOrientationQuaternion( Constants::Pi * 0.6f, Constants::Pi * 0.6f, Constants::Pi * 0.6f );
    const Math::Vector<float, 3> scaling( .8f, .8f, .8f );
    const Math::Point3f rotationOrigin( 5.f, 5.f, 5.f );
    const Quaternion<float> rotationQuaternion( Constants::Pi * 0.3f, Constants::Pi * 0.3f, Constants::Pi * 0.3f );
    const Math::Vector<float, 3> translation( 4.f, 4.f, 4.f );

    auto transformation = Math::TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling, rotationOrigin, rotationQuaternion, translation );
    Math::Normal3f n1( 2.f, 2.f, 2.f );
    Math::Normal3f expected( 2.01553679f, 0.0192041993f, 1.90190506f );
    Math::Normal3f result = Math::Transform( n1, transformation );
    auto equal = AllEqual( expected, result, 1.0e-7f );
    CHECK(equal);
}
TEST_CASE("Transform3DTests / PointAffineTransformationMatrixTest1", "[math][Transform3DTests]")
{
    using namespace Math;
    using Constants = Math::Constants<float>;


    const Math::Vector3f scaling( 1.5f, 2.5f, 1.f );
    const Math::Point3f rotationOrigin( 5.f, 5.f, 5.f );
    const Quaternion<float> rotationQuaternion( Constants::Pi * 0.3f, Constants::Pi * 0.3f, Constants::Pi * 0.3f );
    const Math::Vector3f translation( 4.f, 4.f, 4.f );

    auto transformation = Math::AffineTransformationMatrix( scaling, rotationOrigin, rotationQuaternion, translation );
    Math::Point3f p1( 2.f, 2.f, 2.f );
    Math::Point3f expected( 5.82341528f, 10.4759951f, 8.14516068f );
    Math::Point3f result = Math::Transform( p1, transformation );
    auto equal = Equal( expected, result );
    CHECK(equal);
}
TEST_CASE("Transform3DTests / VectorAffineTransformationMatrixTest1", "[math][Transform3DTests]")
{
    using namespace Math;
    using Constants = Math::Constants<float>;


    const Math::Vector3f scaling( 1.5f, 2.5f, 1.f );
    const Math::Point3f rotationOrigin( 5.f, 5.f, 5.f );
    const Quaternion<float> rotationQuaternion( Constants::Pi * 0.3f, Constants::Pi * 0.3f, Constants::Pi * 0.3f );
    const Math::Vector3f translation( 4.f, 4.f, 4.f );

    auto transformation = Math::AffineTransformationMatrix( scaling, rotationOrigin, rotationQuaternion, translation );
    Math::Vector3f p1( 2.f, 2.f, 2.f );
    Math::Vector3f expected( 5.82341528f, 10.4759951f, 8.14516068f );
    Math::Vector3f result = Math::Transform( p1, transformation );
    auto equal = Equal( expected, result );
    CHECK(equal);
}
TEST_CASE("Transform3DTests / NormalAffineTransformationMatrixTest1", "[math][Transform3DTests]")
{
    using namespace Math;
    using Constants = Math::Constants<float>;


    const Math::Vector3f scaling( 1.5f, 2.5f, 1.f );
    const Math::Point3f rotationOrigin( 5.f, 5.f, 5.f );
    const Quaternion<float> rotationQuaternion( Constants::Pi * 0.3f, Constants::Pi * 0.3f, Constants::Pi * 0.3f );
    const Math::Vector3f translation( 4.f, 4.f, 4.f );

    auto transformation = Math::AffineTransformationMatrix( scaling, rotationOrigin, rotationQuaternion, translation );
    Math::Normal3f p1( 2.f, 2.f, 2.f );
    Math::Normal3f expected( 3.12196779f, 1.53600752f, 5.08861494f );
    Math::Normal3f result = Math::Transform( p1, transformation );
    auto equal = Equal( expected, result );
    CHECK(equal);
}
TEST_CASE("Transform3DTests / PointLookToTest1", "[math][Transform3DTests]")
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    Point3f cameraPosition(-2.f, 1.f, -3.f);
    Vector3f cameraDirection(1.5f, 1.5f, 1.5f );
    Vector3f upDirection( 0.f, 1.f, 0.f );
    

    auto transformation = Math::LookTo( cameraPosition, cameraDirection, upDirection );
    Math::Point3f p1( 2.f, 2.f, 2.f );
    Math::Point3f result = Math::Transform( p1, transformation );

    Math::Point3f expected( -0.707106709f, -2.85773802f, 5.77350330f );
    auto equal = Equal( expected, result );
    CHECK(equal);
}
TEST_CASE("Transform3DTests / VectorLookToTest1", "[math][Transform3DTests]")
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    Point3f cameraPosition( -2.f, 1.f, -3.f );
    Vector3f cameraDirection( 1.5f, 1.5f, 1.5f );
    Vector3f upDirection( 0.f, 1.f, 0.f );


    auto transformation = Math::LookTo( cameraPosition, cameraDirection, upDirection );
    Math::Vector3f p1( 2.f, 2.f, 2.f );
    Math::Vector3f result = Math::Transform( p1, transformation );

    Math::Vector3f expected( -0.707106709f, -2.85773802f, 5.77350330f );
    auto equal = Equal( expected, result );
    CHECK(equal);
}
TEST_CASE("Transform3DTests / NormalLookToTest1", "[math][Transform3DTests]")
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    Point3f cameraPosition( -2.f, 1.f, -3.f );
    Vector3f cameraDirection( 1.5f, 1.5f, 1.5f );
    Vector3f upDirection( 0.f, 1.f, 0.f );


    auto transformation = Math::LookTo( cameraPosition, cameraDirection, upDirection );
    Math::Normal3f p1( 10.f, 10.f, 10.f );
    Math::Normal3f result = Math::Transform( p1, transformation );

    Math::Normal3f expected( -1.19209290e-07f, -2.38418579e-07f, 17.3205090f );
    auto equal = Equal( expected, result );
    CHECK(equal);
}
TEST_CASE("Transform3DTests / PointLookAtTest1", "[math][Transform3DTests]")
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    Point3f cameraPosition( -2.f, 1.f, -3.f );
    Vector3f focusPoint( 1.5f, 1.5f, 1.5f );
    Vector3f upDirection( 0.f, 1.f, 0.f );


    auto transformation = Math::LookAt( cameraPosition, focusPoint, upDirection );
    Math::Point3f p1( 2.f, 2.f, 2.f );
    Math::Point3f result = Math::Transform( p1, transformation );

    Math::Point3f expected( 0.0877057314f, 0.436784744f, 6.46540976f );
    auto equal = Equal( expected, result );
    CHECK(equal);
}
TEST_CASE("Transform3DTests / VectorLookAtTest1", "[math][Transform3DTests]")
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    Point3f cameraPosition( -2.f, 1.f, -3.f );
    Vector3f focusPoint( 1.5f, 1.5f, 1.5f );
    Vector3f upDirection( 0.f, 1.f, 0.f );


    auto transformation = Math::LookAt( cameraPosition, focusPoint, upDirection );
    Math::Vector3f p1( 2.f, 2.f, 2.f );
    Math::Vector3f result = Math::Transform( p1, transformation );

    Math::Vector3f expected( 0.0877057314f, 0.436784744f, 6.46540976f );
    auto equal = Equal( expected, result );
    CHECK(equal);
}
TEST_CASE("Transform3DTests / NormalLookAtTest1", "[math][Transform3DTests]")
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    Point3f cameraPosition( -2.f, 1.f, -3.f );
    Vector3f focusPoint( 1.5f, 1.5f, 1.5f );
    Vector3f upDirection( 0.f, 1.f, 0.f );


    auto transformation = Math::LookAt( cameraPosition, focusPoint, upDirection );
    Math::Normal3f p1( 2.f, 2.f, 2.f );
    Math::Normal3f result = Math::Transform( p1, transformation );

    Math::Normal3f expected( 0.350823164f, 1.74713910f, 2.97059369f );
    auto equal = Equal( expected, result );
    CHECK(equal);
}
TEST_CASE("Transform3DTests / PointPerspectiveProjectionTest1", "[math][Transform3DTests]")
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    float viewWidth = 1024; 
    float viewHeight = 768; 
    float nearZ = Constants::MachineEpsilon; 
    float farZ = 1000;

    auto transformation = Math::PerspectiveProjection( viewWidth, viewHeight, nearZ, farZ );
    Math::Point3f p1( 200.f, 300.f, 300.f );
    Math::Point3f result = Math::Transform( p1, transformation );

    Math::Point3f expected( 7.76102169e-11f, 1.55220434e-10f, 1.00000000f );
    auto equal = Equal( expected, result );
    CHECK(equal);
}
TEST_CASE("Transform3DTests / VectorPerspectiveProjectionTest1", "[math][Transform3DTests]")
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    float viewWidth = 1024;
    float viewHeight = 768;
    float nearZ = Constants::MachineEpsilon;
    float farZ = 1000;

    auto transformation = Math::PerspectiveProjection( viewWidth, viewHeight, nearZ, farZ );
    Math::Vector3f p1( 200.f, 300.f, 300.f );
    Math::Vector3f result = Math::Transform( p1, transformation );

    Math::Vector3f expected( 2.32830644e-08f, 4.65661287e-08f, 300.000000f );
    auto equal = Equal( expected, result );
    CHECK(equal);
}
TEST_CASE("Transform3DTests / NormalPerspectiveProjectionTest1", "[math][Transform3DTests]")
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    float viewWidth = 1024;
    float viewHeight = 768;
    float nearZ = Constants::MachineEpsilon;
    float farZ = 1000;

    auto transformation = Math::PerspectiveProjection( viewWidth, viewHeight, nearZ, farZ );
    Math::Normal3f p1( 200.f, 300.f, 300.f );
    Math::Normal3f result = Math::Transform( p1, transformation );

    Math::Normal3f expected( 2.32830644e-08f, 4.65661287e-08f, 300.000000f );
    auto equal = Equal( expected, result );
    CHECK(equal);
}
TEST_CASE("Transform3DTests / PointPerspectiveProjectionFovTest1", "[math][Transform3DTests]")
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    float fovAngleY = Constants::PiOver4;
    float aspectRatio = 1.4f;
    float nearZ = Constants::MachineEpsilon;
    float farZ = 1000;

    auto transformation = Math::PerspectiveFovProjection( fovAngleY, aspectRatio, nearZ, farZ );
    Math::Point3f p1( 200.f, 300.f, 300.f );
    Math::Point3f result = Math::Transform( p1, transformation );

    Math::Point3f expected( 1.14962542f, 2.41421342f, 1.00000000f );
    auto equal = Equal( expected, result );
    CHECK(equal);
}
TEST_CASE("Transform3DTests / VectorPerspectiveProjectionFovTest1", "[math][Transform3DTests]")
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    float fovAngleY = Constants::PiOver4;
    float aspectRatio = 1.4f;
    float nearZ = Constants::MachineEpsilon;
    float farZ = 1000;

    auto transformation = Math::PerspectiveFovProjection( fovAngleY, aspectRatio, nearZ, farZ );
    Math::Vector3f p1( 200.f, 300.f, 300.f );
    Math::Vector3f result = Math::Transform( p1, transformation );

    Math::Vector3f expected( 344.887634f, 724.264038f, 300.f );
    auto equal = Equal( expected, result );
    CHECK(equal);
}
TEST_CASE("Transform3DTests / NormalPerspectiveProjectionFovTest1", "[math][Transform3DTests]")
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    float fovAngleY = Constants::PiOver4;
    float aspectRatio = 1.4f;
    float nearZ = Constants::MachineEpsilon;
    float farZ = 1000;

    auto transformation = Math::PerspectiveFovProjection( fovAngleY, aspectRatio, nearZ, farZ );
    Math::Normal3f p1( 200.f, 300.f, 300.f );
    Math::Normal3f result = Math::Transform( p1, transformation );

    Math::Normal3f expected( 344.887634f, 724.264038f, 300.f );
    auto equal = Equal( expected, result );
    CHECK(equal);
}
TEST_CASE("Transform3DTests / PointProjectTest1", "[math][Transform3DTests]")
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    float viewPortX = 0;
    float viewPortY = 0;
    float viewportWidth = 1024;
    float viewportHeight = 768;
    float viewportMinZ = 0.f;
    float viewportMaxZ = 1.f;

    SquareMatrix<float, 4> viewTransformation;

    Point3f cameraPosition( -2.f, 1.f, -3.f );
    Vector3f focusPoint( 1.5f, 1.5f, 1.5f );
    Vector3f upDirection( 0.f, 1.f, 0.f );

    auto worldTransformation = Math::LookAt( cameraPosition, focusPoint, upDirection );

    float fovAngleY = Constants::PiOver4;
    float aspectRatio = 1.4f;
    float nearZ = Constants::MachineEpsilon;
    float farZ = 1000;

    auto projection = Math::PerspectiveFovProjection( fovAngleY, aspectRatio, nearZ, farZ );


    Math::Point3f p1( 200.f, 300.f, 300.f );
    Math::Point3f result = Math::Project( p1.ToSimd(), viewPortX, viewPortY, viewportWidth, viewportHeight, viewportMinZ, viewportMaxZ, projection, viewTransformation.ToSimd( ), worldTransformation );

    Math::Point3f expected( 451.515869f, -251.981598f, 1.f );
    auto equal = Equal( expected, result );
    CHECK(equal);
}
