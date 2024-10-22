#version 330 core
in vec3 FragPos;       

out vec4 FragColor;

void main()
{
	vec3 edge1 = dFdx(FragPos);
    vec3 edge2 = dFdy(FragPos);
    vec3 Normal = normalize(cross(edge1,edge2));
	vec3 lightColor = vec3 (1);

    // Ambient lighting
    float ambientStrength = 0.6;
    vec3 ambient = ambientStrength * lightColor;

	vec3 lightPos = vec3(0,10,0);
    // Diffuse lighting
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

	vec3 objectColor = vec3(1);
    // Combine results
    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
}