/*
 Cesar Valdez
 
 */

uniform mat4 MVP;

attribute vec3 position;
attribute vec3 color;
attribute vec2 textura_cord;

varying vec2 textura_cord_out;
varying vec3 s_color;



void main(void)
{
	
	s_color = color;
    textura_cord_out = textura_cord;
    gl_Position = MVP * vec4(position, 1.0);
    
    
}