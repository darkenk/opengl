/**
 * Copyright (C) 2014, Dariusz Kluska <darkenk@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of the {organization} nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#version 330

// input from shader
in vec4 vColor;
in vec4 vNormal;
in vec4 WorldPos0;
out vec4 out_Color;

struct DirectionalLight
{
    //ambient light
    vec4 Color;
    float AmbientIntensity;
    // diffuse light
    float DiffuseIntensity;
    vec4 Direction;
};

uniform DirectionalLight gDirectionalLight = DirectionalLight(
            vec4(1.0, 1.0, 1.0, 1.0),
            1.0,
            1.0,
            vec4(1.0, 1.0, 1.0, 1.0));

uniform vec4 gEyePosition = vec4(0.0, 0.0, 0.0, 1.0);
uniform float gMatSpecularIntensity = 1.0;
uniform float gSpecularPower = 32;

void main(void)
{
    vec4 AmbientColor = gDirectionalLight.Color * gDirectionalLight.AmbientIntensity;
    vec4 LightDirection = -gDirectionalLight.Direction;
    vec3 Normal = normalize(vNormal.xyz);

    float DiffuseFactor = dot(Normal, LightDirection.xyz);

    vec4 DiffuseColor = vec4(0, 0, 0, 0);
    vec4 SpecularColor = vec4(0, 0, 0, 0);

    if (DiffuseFactor > 0) {
        DiffuseColor = vec4(gDirectionalLight.Color) * gDirectionalLight.DiffuseIntensity *DiffuseFactor;

        vec3 VertexToEye = normalize(gEyePosition.xyz - WorldPos0.xyz);
        vec3 LightReflect = normalize(reflect(gDirectionalLight.Direction.xyz, Normal));
        float SpecularFactor = dot(VertexToEye, LightReflect);
        SpecularFactor = pow(SpecularFactor, gSpecularPower);
        if (SpecularFactor > 0) {
            SpecularColor = vec4(gDirectionalLight.Color) * gMatSpecularIntensity * SpecularFactor;
        }
    }
    out_Color = vColor * (AmbientColor + DiffuseColor + SpecularColor);
}
