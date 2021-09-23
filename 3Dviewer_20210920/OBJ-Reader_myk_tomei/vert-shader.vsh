attribute vec3 vertexPosition; //attribute変数定義:　.cppに書いてシェーダ(vert/frag)で受け取る　//頂点ごとに異なるデータを受け取る
attribute vec3 vertexNormal;

attribute vec2 vertexUV_a;
varying vec2 vertexUV;   //varying変数定義： 頂点シェーダからフラグメントシェーダにデータを渡す

varying vec3 lightIntensity;

uniform vec3 lightPosition; //uniform変数定義: .cppに書いてシェーダ(vert/frag)で受け取る //全ての頂点に対して一律に処理される情報として受け取る
uniform vec3 lightKd;
uniform vec3 lightLd;

uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewProjMatrix;

void main()
{
    vertexUV = vertexUV_a;

    // Diffuse
    vec3 tnorm = normalize(normalMatrix * vertexNormal);
    vec4 eyeCoords = modelViewMatrix * vec4(vertexPosition, 1.0);
    vec3 s = normalize(vec3( vec4(lightPosition, 1.0) - eyeCoords));
    lightIntensity = lightLd * lightKd * max( dot(s, tnorm), 0.0);
    gl_Position = modelViewProjMatrix * vec4(vertexPosition, 1.0);
}
