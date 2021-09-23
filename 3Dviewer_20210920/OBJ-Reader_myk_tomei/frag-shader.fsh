varying vec3 lightIntensity;
varying vec2 vertexUV;

uniform bool renderTexture;

uniform sampler2D texture;

void main()
{
    //-start- org
    //vec4 texCol = texture2D(texture, vertexUV);
    //gl_FragColor = renderTexture ? vec4(lightIntensity, 1.0) * texCol : vec4(lightIntensity, 1.0);
    //-end- org

    //-start- NG-kuroda_test1　//参考：https://community.khronos.org/t/using-alpha-blending-with-shaders/64995
    vec4 texCol = texture2D(texture, vertexUV).aaaa; //.aaaaつけて透明化しているつもりだが、未確認
    gl_FragColor = renderTexture ? vec4(lightIntensity, 0.3) * texCol : vec4(lightIntensity, 0.3) ; //0.3にしてみた. (透明度は 0.0 ～ 1.0)
    //gl_FragColor = gl_FragColor * vec4(red,green,blue,calpha);
    //-end- NG-kuroda_test1
}
