

#include "AbsoluteShadowCommonSystem.fx"

shared texture AbsoluteShadowMap: OFFSCREENRENDERTARGET;
sampler ShadowMapSampler = sampler_state {
    texture = <AbsoluteShadowMap>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = LINEAR;
    AddressU  = CLAMP;
    AddressV = CLAMP;
};


//////////////////////////////////////////////////////////////////////////////////////////////////


#if MIPMAP_ENABLE==0

///////////////////////////////////////////////////////////////////////////////////
// �V���h�E�pZ�o�b�t�@�̂ڂ����ǂݎ��
// ���_�T���v�����O�łڂ���

//9�_�T���v�����O
float2 GetZBufSample(float2 texc){
    float2 Out;
    float step = sampstep;
    
    Out = tex2D(ShadowMapSampler,texc).rg * 2;
    
    Out += tex2D(ShadowMapSampler,texc + float2(0, step)).rg;
    Out += tex2D(ShadowMapSampler,texc + float2(0, -step)).rg;
    Out += tex2D(ShadowMapSampler,texc + float2(step, 0)).rg;
    Out += tex2D(ShadowMapSampler,texc + float2(-step, 0)).rg;
    Out += tex2D(ShadowMapSampler,texc + float2(step, step)).rg;
    Out += tex2D(ShadowMapSampler,texc + float2(-step, step)).rg;
    Out += tex2D(ShadowMapSampler,texc + float2(step, -step)).rg;
    Out += tex2D(ShadowMapSampler,texc + float2(-step, -step)).rg;
    
    Out /= 10;
    return Out;
}

#else

/////////////////////////////////////////////////////////////////////////////////////
// �V���h�E�pZ�o�b�t�@�̂ڂ����ǂݎ��
// �~�b�v�}�b�v�𗘗p���A���L�͈͂̂ڂ������s��

float2 GetZBufSampleMip(float2 texc, float steprate, float mip){
    float2 Out;
    float step = sampstep * steprate;
    
    Out = tex2Dlod(ShadowMapSampler, float4(texc, 0, mip)) * 2;
    
    Out += tex2Dlod(ShadowMapSampler, float4(texc + float2(0, step), 0, mip));
    Out += tex2Dlod(ShadowMapSampler, float4(texc + float2(0, -step), 0, mip));
    Out += tex2Dlod(ShadowMapSampler, float4(texc + float2(step, 0), 0, mip));
    Out += tex2Dlod(ShadowMapSampler, float4(texc + float2(-step, 0), 0, mip));
    Out += tex2Dlod(ShadowMapSampler, float4(texc + float2(step, step), 0, mip));
    Out += tex2Dlod(ShadowMapSampler, float4(texc + float2(-step, step), 0, mip));
    Out += tex2Dlod(ShadowMapSampler, float4(texc + float2(step, -step), 0, mip));
    Out += tex2Dlod(ShadowMapSampler, float4(texc + float2(-step, -step), 0, mip));
    
    Out /= 10;
    return Out;
}

float2 GetZBufSample(float2 texc){
    float2 Out;
    
    //���̂ւ�̒萔�͊��Œ���
    Out = GetZBufSampleMip(texc, 1, 0) * 0.6;
    Out += GetZBufSampleMip(texc, 1.8, 0.8) * 0.3;
    //Out += GetZBufSampleMip(texc, 3.4, 1.6) * 0.10;
    
    Out = GetZBufSampleMip(texc, 1, 0.3) * 0.65;
    Out += GetZBufSampleMip(texc, 1.8, 1.2) * 0.35;
    
    return Out;
}

#endif

//�ڂ����Ȃ��T���v�����O
float2 GetZBufSampleN(float2 texc){
    float2 Out;
    Out = tex2D(ShadowMapSampler,texc).rg;
    
    return Out;
}



