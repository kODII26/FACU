#version 330 core
in vec2 fragTexCoords;
out vec4 fragColor;

void main() {
	vec2 uv = clamp(fragTexCoords, 0.0, 1.0);
	
	// Escalar a rango 0-65535 (16 bits)
	vec2 scaledUV = uv * 65535.0;
	
	// Separar en parte alta (8 bits más significativos) y baja (8 bits menos significativos)
	float u_hi = floor(scaledUV.x / 256.0) / 255.0;  // Byte alto de U
	float u_lo = mod(scaledUV.x, 256.0) / 255.0;     // Byte bajo de U
	
	float v_hi = floor(scaledUV.y / 256.0) / 255.0;  // Byte alto de V
	float v_lo = mod(scaledUV.y, 256.0) / 255.0;     // Byte bajo de V
	
	fragColor = vec4(u_hi, u_lo, v_hi, v_lo);
}
