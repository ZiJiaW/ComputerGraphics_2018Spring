#version 330 core
out vec4 FragColor;

struct PointLight {
    vec3 position;
	vec3 color;
};

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
uniform vec3 viewPos;
uniform PointLight pointLights[2];
uniform sampler2D texture_diffuse1;

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 FragPos, vec3 viewDir);
void main()
{    
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 result = CalcPointLight(pointLights[0], norm, FragPos, viewDir)+CalcPointLight(pointLights[1], norm, FragPos, viewDir);
    FragColor = vec4(result,1.0) * texture(texture_diffuse1, TexCoords);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 FragPos, vec3 viewDir)
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * light.color;// 环境光分量

	vec3 lightDir = normalize(light.position - FragPos);// 片段指向光源的单位向量
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * light.color;// 漫反射分量
	
	float specularStrength = 0.5;//镜面强度
	vec3 reflectDir = reflect(-lightDir, normal);// 将之前计算的光源与照射点方向取反，再计算反射方向
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);// 视线与反射方向点乘，计算32次幂（光的反射度）
	vec3 specular = specularStrength * spec * light.color;
	
	return (ambient+diffuse+specular);
}