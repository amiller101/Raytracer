#include <vec3.h>
#include <math.h>

typedef double vec3[3];

typedef struct{
double s;
vec3 v;
}quaternion;

void quaternion_mul(quaternion *out, quaternion *p, quaternion *q){
    vec3 tmp;

    //pq = <s_p * s_q - v_p * v_q, v_p x v_q + s_p * v_q + s_q * v_p>
    out->s = p->s * q->s - (p->v * q->v);
    vec3_cross(out->v, p->v,q->v);
    tmp = q->v * p->s;
    out->v += tmp; 
    tmp = p->v * q->s;
    out->v += tmp; 
}

//angle is in degree
quaternion_rot(vec3 v, vec3 axis, double angle)
{
    //t == theta
    // rot = <cos(t/2,) xsint(t/2), ysin(t/2), zsin(t/2)>
    double t = angle * M_PI / 180.0;
    double sint2;
    quaternion rot, rotinv;
    quaternion q, p;

    rot.s = cos(t/2.0);
    sint2 = sin(t/2.0); // using variable so we don thave to call sin seveeral times
    rot.v = vec3(axis) * sint2; // fix to be mre verbose like below
    rotinv.s = rot.s;
    rotinv.v = -1 * rot.v;

    p.s = 1;
    p.v[0] = v[0];
    p.v[1] = v[1];
    p.v[2] = v[2];

    // Inverse of a quat: p = -1 * original

    q.s = 1;
    q.v[0] = -v[0];
    q.v[1] = -v[1];
    q.v[2] = -v[2];

    //Rotation p-prime = qinv * p * q
    //Reversing p = q * p-prime * qinv

    quaternion_mul(&p, &rotinv, &p);
    quaternion_mul(&p, &p, &rot);

    v = quaternion(p); //or doo each index copying

}