#version 330

uniform sampler2D screen_texture;
uniform float time;
uniform float dead_timer;

in vec2 uv;

layout(location = 0) out vec4 color;

vec2 distort(vec2 uv)
{
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // HANDLE THE WATER WAVE DISTORTION HERE (you may want to try sin/cos)
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    uv.y += cos(uv.x*5.+time)*0.005;
    uv.x += cos(uv.y*5.+time)*0.005;
    vec2 coord = uv.xy;
    return coord;
}

vec4 color_shift(vec4 in_color)
{
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // HANDLE THE COLOR SHIFTING HERE (you may want to make it blue-ish)
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    vec4 color = in_color;
    //color += 0.5 * sin(time*0.4) * vec4(0.1, 0.1, 0.1, 0);
    color += vec4(0.1, 0.1, 0.5, 0);
    return color;
}

vec4 fade_color(vec4 in_color)
{
    vec4 color = in_color;
    if (dead_timer > 0)
    color -= 0.1 * dead_timer * vec4(0.1, 0.1, 0.1, 0);

    return color;
}

void main()
{
    vec2 coord = distort(uv);
    vec4 in_color = texture(screen_texture, coord);
    color = color_shift(in_color);
    color = in_color;
}