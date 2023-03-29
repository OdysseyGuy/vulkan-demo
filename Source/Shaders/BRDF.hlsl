float3 F_Schlick(const float3 F0, float F90, float VdotH)
{
    return F0 + (F90 - F0) * pow(1.0 - VdotH, 5.0);
}

float3 F_Schlick(const float3 F0, float VdotH)
{
    float F = pow(1.0 - VdotH, 5.0);
    return F + F0 * (1.0 - F);
}

float3 F_Schlick_Roughness(float3 F0, float CosTheta, float Roughness)
{
    float3 A = 1.0 - Roughness;
    return F0 + (max(A, F0) - F0) * pow(max(1.0 - CosTheta, 0.0), 5.0);
}

float V_SmithGGXCorrelated()
{
}

float D_GGX(float NdotH, float M)
{
    float MSq = M * M;
    float F = (NdotH * MSq - NdotH) * NdotH + 1;
    return MSq / (F * F);
}
