uniform float time;
uniform vec2 resolution;

void main() {
	vec4 color;
	float gradient_pos = resolution.y; // Use the x coordinate as the gradient position
	vec4 start_color = vec4(1.0, 0.0, 0.0, 1.0); // Red
	vec4 end_color = vec4(0.0, 0.0, 1.0, 1.0); // Blue
	color = mix(start_color, end_color, gradient_pos * 0.04);
	gl_FragColor = color;
}