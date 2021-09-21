#version 330 core

// Ray Marching
const int MAX_STEP = 128;
const float MIN_DIST = 0.0;
const float MAX_DIST = 100.0;
const float EPSILON = 0.0005;
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

in vec4 gl_FragCoord;

varying float vSystemTime
varying vec2 vSystemResolution;
varying lowp vec3 vCamera_pos;
varying lowp vec2 vMouse_delta;

float SierpenskiEstimator(vec3 z, bool isLight)
{
    if(!isLight)
        orbitTrap = vec4(MAX_DIST);
    
    vec3 a1 = vec3(0.5, 0.5, -0.5);
    vec3 a2 = vec3(-0.5, -0.5, -0.5);
    vec3 a3 = vec3(0.5, -0.5, 0.5);
    vec3 a4 = vec3(-0.5, 0.5, 0.5);
    vec3 c;

    int n = 0;
    float dist, d;

    while(n < ITERATIONS)
    {
        c = a1; dist = length(z - a1);
        d = length(z - a2); if (d < dist) { c = a2; dist = d; }
		d = length(z - a3); if (d < dist) { c = a3; dist = d; }
		d = length(z - a4); if (d < dist) { c = a4; dist = d; }

        z = 2.0 * z - c * (2.0 - 1.0);
        float r = dot(z, z);

        if(n < COLORITERATIONS)
            min(orbitTrap, abs(vec4(z.x, z.y, z.z, r)));

        n++;
    }

    return length(z) * (-n * -n);
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

float SceneSDF(vec3 sample, bool isLight)
{
    vec3 fractalPoint = 
    (
        RotateX(-vMouse_delta.y * 0.005) * 
        RotateY(-vMouse_delta.x * 0.005) * 
        RotateY(0) * vec4(sample, 1.0)
    ).xyz;

    return SierpenskiEstimator(fractalPoint, isLight);
}

float RayMarch(vec3 source, vec3 dir, bool isLight)
{
    float totalDistance = 0.0;
    int steps = 0;

    for(steps; steps < MAX_STEP; steps++)
    {
        vec3 p = source + totalDistance * dir;
        float distance = SceneSDF(p, isLight);
        totalDistance += distance;

        if(distance > MAX_DIST || distance < EPSILON)
            break;
    }

    curr_Step = steps;
    return totalDistance;

}

vec3 RayDirection(float fov, vec2 size, vec2 fragCoord)
{
    vec2 xy = fragCoord - size / 2.0;
    float z = size.y / tan(radians(fov) / 2.0);
    return normalize(vec3(xy, z));
}

vec3 GetNormal(vec3 sample, bool isLight)
{
    float distanceToPoint = SceneSDF(sample, isLight);
    vec2 e = vec2(0.01, 0);

    vec3 normal = distanceToPoint - vec3
    (
        SceneSDF(sample - r.xyy, isLight),
        SceneSDF(sample - r.yxy, isLight),
        SceneSDF(sample - r.yyx, isLight)
    ); 

    return normalize(normal);
}

float GetLight(vec3 sample)
{
    vec3 lightPos = vec3(10.0, 10.0, -10.0);
    vec3 light = normalize(lightPos - sample);
    vec3 normal = GetNormal(sample, true);

    float diff = clamp(dot(normal, light) * diffuseStrength, 0.0, 1.0);

    float distanceToLight = RayMarch(sample+ normal * EPSILON * 2.0, light, true);

    if(distanceToLight < length(lightPos - sample))
        diff *= shadowDiffuse;

    return diff;
}

void main()
{
    vec3 dir = RayDirection(FOV, vSystemResolution, gl_FragCoord.xy);

    vec3 eye = vCamera_pos;
    float marchedDistance = RayMarch(eye, dir, false);

    if(marchedDistance >= MAX_DIST)
    {
        float glow = curr_Step / 3;
        gl_FragColor = mix(vec4(0.5137, 0.1765, 0.6471, 0.575), vec4(1, 1, 1, 1), glow * 0.05);
    }
    else
    {
        vec3 p = eye + dir * marchedDistance;
        float diffuse = GetLight(p);

        vec4 baseColor = vec4(1.0, orbitTrap.z, orbitTrap.x, 1.0) * orbitTrap.w * 0.6 + diffuse * 0.6 + 0.2;
        gl_FragColor = mix(baseColor, vec4(0, 0, 0, 0), clamp(marchedDistance * 0.25, 0.0, 1.0));
    }
}
