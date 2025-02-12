uniform vec2 resolution;

void main()
{
	//vec2 uv = (gl_FragCoord.xy-0.5*resolution.xy) / resolution.y;
	vec2 uv = (gl_FragCoord.xy-0.5*resolution.xy) / resolution.y ;
	// Use to move left/right, up/down
	uv.x = (gl_FragCoord.x -0.5 * resolution.x) / resolution.x;
	uv.y = (gl_FragCoord.y -0.2 * resolution.y) / resolution.y;

	uv *=  1.0 - uv.yx;   //vec2(1.0)- uv.yx; -> 1.-u.yx; Thanks FabriceNeyret !

	float vig = uv.x*uv.y * 2.8; // multiply with sth for intensity

	vig = pow(vig, 0.6); // change pow for modifying the extend of the  vignette


	gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0) * vig;
}