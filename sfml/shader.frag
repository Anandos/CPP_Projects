#version 120

uniform sampler2D texture;

void main(){
    vec4 color = texture2D(texture, gl_TexCoord[0].xy);

    float grey = dot(color.rgb, vec3(0.1, 0.2, 0.3));

    gl_FragColor = vec4(vec3(grey), color.a);

}
