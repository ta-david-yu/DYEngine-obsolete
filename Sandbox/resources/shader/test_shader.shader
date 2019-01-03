<?xml version="1.0" encoding="utf-8"?>
<shaderprogram name="test_shader">
		<vert filename="unlit.vert"/>
		<frag>
#version 150 compatibility

uniform vec4 unlitColor;

void main()
{
	gl_FragColor=unlitColor;
}
		</frag>
</shaderprogram>