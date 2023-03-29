cbuffer BufferLow : register(b0)
{
    matrix  gView;
    matrix  gProjection;
    // matrix  gProjectionInverted;
    matrix  gViewProjection;
    // matrix  gViewProjectionInverted;

    // float   gDeltaTime;
    // float   gTime;
    // float   gFrame;
    // float   gCameraAperture;

    // float   gCameraNear;
    // float   gCameraFar;

    // float3  gCameraPosition;

    // float   gGamma;
    // float   gDirectionalLightIntensity;
    // float   gShadowResolution;
};

cbuffer BufferMedium : register(b1)
{
};
