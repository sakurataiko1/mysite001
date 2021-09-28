varying vec3 lightIntensity;
varying vec2 vertexUV;

uniform bool renderTexture;

uniform sampler2D texture;

//-start- kuroda 追加
out vec4 fragColor;
varying vec4 varying_myColor;
//-end- kuroda 追加


void main()
{
    //-start- org
    //vec4 texCol = texture2D(texture, vertexUV);
    //gl_FragColor = renderTexture ? vec4(lightIntensity, 1.0) * texCol : vec4(lightIntensity, 1.0); //1.0 は透明度 0.0～1.0の値を指定する。 数値が小さいほど透明。
    //-end- org

    //-start- kuroda_test OK 個別の色にするため、gl_FragColorでは単一処理されてしまうため、fragColorで個別処理する. varying_myColorは vert.vshでライト値との計算した結果値。
    //fragColor = varying_myColor;
    //-end- kuroda_test

    vec4 texCol = texture2D(texture, vertexUV);
    fragColor = renderTexture ? varying_myColor * texCol : varying_myColor;

}
