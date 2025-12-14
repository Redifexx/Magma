#version 460 core

// OUTPUTS: The final color written to the screen
layout (location = 0) out vec4 FragColor;

void main()
{
    // Output the interpolated color with Alpha = 1.0 (Opaque)
    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}