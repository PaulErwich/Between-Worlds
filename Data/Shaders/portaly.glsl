uniform sampler2D texture1;
uniform vec2 resolution;
uniform float time;

#define TWO_PI 6.28318530718
#define PI 3.14159265359

float noise(vec2 p) {
	return texture(texture1, p * 0.05 ).x;
}

float fbm(vec2 p) {
	float a =1.;
	float f = 1.;
	return a*noise(p)
	+ a*0.5 * noise(p*f*2. )
	+ a*0.25 * noise(p*f*4. )
	+ a*0.1 * noise(p*f*8. );
}

float circle(vec2 p) {
	float r = length(p);
	float radius = 0.4;
	float height = 1.;
	float width = 60.;

	return height - pow(r - radius, 2.) *width ;
}

void main()
{
	vec2 uv = ( gl_FragCoord.xy-.5 * resolution.xy ) / resolution.y;
	//vec2 uv = (gl_FragCoord.xy - resolution.xy) / resolution.y;
	//vec2 uv = (gl_FragCoord.xy / resolution.xy) * 2.0 - 1.0;
	//uv.x *= resolution.x / resolution.y;
	//vec2 uv = gl_FragCoord.xy / resolution.xy;
	//vec2 uv = (gl_FragCoord.xy-0.5*resolution.xy) / resolution.y;
	//vec2 uv = ( gl_FragCoord.xy -.5 * resolution.xy ) / resolution.y;

	vec2 st  = vec2(
	atan(uv.y, uv.x) ,
	length(uv) * 3. + time * 0.9
	);


	st.x += st.y * 6.1;// - iTime * 0.3;
	st.x = mod(st.x , TWO_PI);


	float n = fbm(st ) * 0.25 -0.1 ;
	n = max(n, 1.1);
	float circle =  max(2.- circle(uv ), 0.8)  ;

	float color = n/circle;
	float mask = smoothstep(0.48, 0.4, length(uv));

	color *= mask;
	vec3 rez = vec3(1., 0.5, 0.25) * color;
	// Output to screen

	float a = 1.0;
	if(rez.rgb == vec3(0.0,0.0,0.0))
	{
		a = 0.0;
	}
	// Output to screen
	gl_FragColor = vec4(rez,a);
}