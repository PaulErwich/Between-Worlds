// Shader created by Tetane in 2018-03-24
// https://www.shadertoy.com/view/ldKyW1

#define pi 3.14159
uniform float time;
uniform vec2 resolution;

float glow(float x, float str, float dist){
	return dist / pow(x, str);
}

// Sinus Signed Distance Function (distance field)
float sinSDF(vec2 st, float A, float offset, float f, float phi){
	return abs((st.y - offset) + sin(st.x * f + phi) * A);
}

void main()
{
	vec2 st = (gl_FragCoord.xy-0.5*resolution.xy) / resolution.y ;
	// Use to move left/right, up/down
	st.x = (gl_FragCoord.x -0.48 * resolution.x) / resolution.x;
	st.y = (gl_FragCoord.y -0.2 * resolution.y) / resolution.y;
	float col = 0.0;
	float time = time/2.0;
	float str = 0.6; // Strength of the light
	float dist = 0.02; // Light propagation distance
	float nSin = 4.0; // Number of sinus functions drawn


	float timeHalfInv = -time * sign(st.x-0.5);
	float am = cos(st.x*3.0); // Amplitude modulation
	float offset = 0.5+sin(st.x*12.0+time)*am*0.05;
	for(float i = 0.0; i<nSin ; i++){
		col += glow(sinSDF(st, am*0.2, offset, 6.0, timeHalfInv+i*2.0*pi/nSin), str, dist);
	}

	// Reverse the color on one half of the screen
	vec3 s = cos( -0.1*st.y*vec3(1,1,1) - vec3(3,-3,3) ) * 0.5 ;
	float cut = st.x+ (s.x+s.y+s.z) / 33.0;

	vec3 red = vec3(1.0, 0.0, 0.1);
	vec3 blue = vec3(0.3, 0.0, 1.0);
	vec4 color = vec4(mix(red, blue, smoothstep(0.4, 0.6, st.x)), 1.0);

	if(color.r < 1.0 && color.b < 1.0)
	{
		color = vec4(color.rgb, (color.r + color.b) * 0.8);
	}

	gl_FragColor = color * col;
}