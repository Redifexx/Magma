#version 460 core

// INPUTS: These match your glVertexAttribPointer layout
// Layout 0 is usually Position, Layout 1 is usually Color or UVs
layout (location = 0) in vec3 aPos;

// UNIFORMS: Global variables sent from C++
layout (location = 0) uniform mat4 u_ViewProjection; // Camera Matrix
layout (location = 1) uniform mat4 u_Model;          // Object Position/Rotation

void main()
{
    // Pass the color through to the fragment shader

    // Calculate final vertex position on screen
    // Multiplication Order is crucial: Projection * View * Model * Vertex
    gl_Position = u_ViewProjection * u_Model * vec4(aPos, 1.0);
}