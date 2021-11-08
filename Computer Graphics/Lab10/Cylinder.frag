#version 330

in float diffTerm;
out vec4 outputColor;

void main()
{
	outputColor = diffTerm*vec4(1);
}
