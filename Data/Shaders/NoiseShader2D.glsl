// Created by sodazot in 2016-07-04
// https://www.shadertoy.com/view/lt33zn

float Noise1S = 0.3;
float Noise2S = 3.5;
//float Amp = 20.0;
float Amp = 0.8;
//float FreqX = 30.0;
float FreqX = 10.0;
float FreqY = 10.0;

uniform float time;
uniform vec2 resolution;
uniform vec2 offset;
uniform sampler2D texture;

// --- noise functions from https://www.shadertoy.com/view/XslGRr
// Created by inigo quilez - iq/2013
// License Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.

mat3 m = mat3( 0.00,  0.80,  0.60,
-0.80,  0.36, -0.48,
-0.60, -0.48,  0.64 );

float hash( float n )
{
    return fract(sin(n)*43758.5453);
}

float noise( in vec3 x )
{
    vec3 p = floor(x);
    vec3 f = fract(x);

    f = f*f*(3.0-2.0*f);

    float n = p.x + p.y*57.0 + 113.0*p.z;

    float res = mix(mix(mix( hash(n+  0.0), hash(n+  1.0),f.x),
    mix( hash(n+ 57.0), hash(n+ 58.0),f.x),f.y),
    mix(mix( hash(n+113.0), hash(n+114.0),f.x),
    mix( hash(n+170.0), hash(n+171.0),f.x),f.y),f.z);
    return res;
}

float fbm( vec3 p )
{
    float f;
    f  = 0.5000*noise( p ); p = m*p*2.02;
    f += 0.2500*noise( p ); p = m*p*2.03;
    f += 0.1250*noise( p ); p = m*p*2.01;
    f += 0.0625*noise( p );
    return f;
}
// --- End of: Created by inigo quilez --------------------
float mynoise ( vec3 p)
{
    return noise(p);
    //return .5+.5*sin(50.*noise(p));
}
float myfbm( vec3 p )
{
    float f;
    f  = 0.5000*mynoise( p ); p = m*p*2.02;
    f += 0.2500*mynoise( p ); p = m*p*2.03;
    f += 0.1250*mynoise( p ); p = m*p*2.01;
    f += 0.0625*mynoise( p ); p = m*p*2.05;
    f += 0.0625/2.*mynoise( p ); p = m*p*2.02;
    f += 0.0625/4.*mynoise( p );
    return f;
}
float myfbm2( vec3 p )
{
    float f;
    f  = 1. - 0.5000*mynoise( p ); p = m*p*2.02;
    f *= 1. - 0.2500*mynoise( p ); p = m*p*2.03;
    f *= 1. - 0.1250*mynoise( p ); p = m*p*2.01;
    f *= 1. - 0.0625*mynoise( p ); p = m*p*2.05;
    f *= 1. - 0.0625/2.*mynoise( p ); p = m*p*2.02;
    f *= 1. - 0.0625/4.*mynoise( p );
    return f;
}

void main()
{
    vec2 scale = vec2(2.0);
    vec2 uv = vec2((gl_FragCoord.x/ resolution.x) * 1.168, gl_FragCoord.y/ resolution.y) * 1.;

    uv.y = 1.0 - uv.y; // Flip the y component
    vec3 v;
    vec3 p = Noise2S*vec3(uv,0.)-time*(1.0, 1.0, 1.0)*0.1;
    float x = myfbm(p);
    v = (.5+.5*sin(x*vec3(FreqX, FreqY, 1.0)*Noise1S))/Noise1S;
    v *= Amp;
    vec4 Ti = texture2D(texture, vec2(.02*v.x+uv.x - 0.133, .02*v.y+uv.y+0.09));

    if (Ti.rgb == vec3(1.0)) {
        Ti.a = 0.0;
    }
    gl_FragColor =Ti;
}