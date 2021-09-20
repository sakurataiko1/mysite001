attribute vec3 vertexPosition;
attribute vec3 vertexNormal;

attribute vec2 vertexUV_a;
varying vec2 vertexUV;

varying vec3 lightIntensity;

uniform vec3 lightPosition;
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
