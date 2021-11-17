#version 330 core

// Ray Marching
const int MAX_STEPS = 128;
const float MIN_DIST = 0.0;
const float MAX_DIST = 100.0;
const float EPSILON = 0.001;
const float FOV = 120.0;

// Fractals
float POWER = 11;
const float BAILOUT = 50.0;
const int ITERATIONS = 20;
const int COLORITERATIONS = 5;

// Shader
const float shadowIntensity = 0.8; //Range from 0 - 1
const float shadowDiffuse = 1.0 - shadowIntensity;
const float diffuseStrength = 1.0;
const float orbitStrength = 0.8;
vec4 orbitTrap = vec4(MAX_DIST);
int curr_Step;

vec2 mouseDelta;

in vec3 fragCoord;
in vec2 texCoord;

out vec4 fragColor;

uniform float SystemTime;
uniform vec2 SystemResolution;
uniform lowp vec3 Camera_pos;
uniform lowp vec2 Mouse_delta;

uniform float rotateRate;
uniform float zoom;

float sdTorus(vec3 p, vec2 r) 
{
	float x = length(p.xz) - r.x;
    return length(vec2(x, p.y)) - r.y;
}

float SierpenskiEstimator(vec3 z)
{
    float scale = 2.0;
 
    vec3 a1 = vec3(1, 1, -1);
    vec3 a2 = vec3(-1, -1, -1);
    vec3 a3 = vec3(1, -1, 1);
    vec3 a4 = vec3(-1, 1, 1);
    vec3 c;

    int n = 0;
    float dist, d;

    while(n < ITERATIONS)
    {
        c = a1; dist = length(z - a1);
        d = length(z - a2); if (d < dist) { c = a2; dist = d; }
		d = length(z - a3); if (d < dist) { c = a3; dist = d; }
		d = length(z - a4); if (d < dist) { c = a4; dist = d; }

        z = scale * z - c * (scale - 1.0);

        n++;
    }

    return length(z) * pow(scale, float(-n));
}

mat4 RotateX(float theta)
{
    return mat4
    (
        vec4(1, 0, 0, 0),
        vec4(0, cos(theta), -sin(theta), 0),
        vec4(0, sin(theta), cos(theta), 0),
        vec4(0, 0, 0, 1)
    );
}
mat4 RotateY(float theta)
{
    return mat4
    (
        vec4(cos(theta), 0, sin(theta), 0),
        vec4(0, 1, 0, 0),
        vec4(-sin(theta), 0, cos(theta), 0),
        vec4(0, 0, 0, 1)
    );
}
mat4 RotateZ(float theta)
{
    return mat4
    (
        vec4(cos(theta), -sin(theta), 0, 0),
        vec4(sin(theta), cos(theta), 0, 0),
        vec4(0, 0, 1, 0),
        vec4(0, 0, 0, 1)
    );
}
mat2 Rot(float theta) 
{
    float s = sin(theta);
    float c = cos(theta);
    return mat2(c, -s, s, c);
}

float GetDist(vec3 p) 
{
    float plane = p.y + 1.0;
    //float box = sdTorus(p - vec3(0, 1, 0), vec2(1.5));
    float box = SierpenskiEstimator(p - vec3(0, 1, 0));
    
    float d = min(plane, box);
    return d;
}

float RayMarch(vec3 ro, vec3 rd) 
{
	float dO = 0.0;
    
    for(int i = 0; i < MAX_STEPS; i++) 
    {
    	vec3 p = ro + rd * dO;
        float dS = GetDist(p);
        dO += dS;

        if(dO > MAX_DIST || dS < EPSILON) break;
    }
    
    return dO;
}

vec3 GetNormal(vec3 sample)
{
    float distanceToPoint = GetDist(sample);
    vec2 e = vec2(0.001, 0);

    vec3 normal = distanceToPoint - vec3
    (
        GetDist(sample - e.xyy),
        GetDist(sample - e.yxy),
        GetDist(sample - e.yyx)
    ); 

    return normalize(normal);
}

float GetLight(vec3 sample)
{
    vec3 lightPos = vec3(3, 5, 4);
    vec3 light = normalize(lightPos - sample);
    vec3 normal = GetNormal(sample);

    float diff = clamp(dot(normal, light) * diffuseStrength, 0.0, 1.0);

    float distanceToLight = RayMarch(sample + normal * EPSILON * 2.0, light);
    /*
    if(distanceToLight < length(lightPos - sample))
        diff *= shadowDiffuse;
    */
    return diff;
}

vec3 R(vec2 uv, vec3 p, vec3 l, float z) 
{
    vec3 f = normalize(l-p),
        r = normalize(cross(vec3(0,1,0), f)),
        u = cross(f,r),
        c = p+f*z,
        i = c + uv.x*r + uv.y*u,
        d = normalize(i-p);
    return d;
}

void main()
{
    vec3 color = vec3(0.1, 0.0, 0.1);
    vec3 ro = vec3(0, 1, -7);
    ro.xz *= Rot(rotateRate * 10);

    vec3 rd = R(-texCoord, ro, vec3(0, 1, 0), zoom);

    float d = RayMarch(ro, rd);

    if(d < MAX_DIST)
    {
        vec3 p = ro + rd * d;

        float diff = GetLight(p);
        color = (vec3(0, 255, 251) / 255) * vec3(diff);
    }
    color = pow(color, vec3(0.4545));

    fragColor = vec4(color, 1.0);
}
