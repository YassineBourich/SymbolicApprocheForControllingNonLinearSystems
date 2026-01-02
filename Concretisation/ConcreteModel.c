#include "ConcreteModel.h"


trajectory* construct_trajectory_for_safety_controller(cont_sys f, static_symb_controller* h, float_vec3* w, float_vec3* x0, int s) {
    trajectory* t = (trajectory*)malloc(sizeof(trajectory));
    t->points = (float_vec3*)malloc(sizeof(float_vec3) * s);
    t->traj_size = 1;

    t->points[0] = *x0;

    float_vec3 xk;
    float_vec3 xkp1;
    int_vec3 ksi;
    int_vec2 sigma;
    float_vec2 uk;
    while (t->traj_size < s) {
        xk = t->points[t->traj_size - 1];
        ksi = q(&xk, &Nx, &x_min, &x_max);
        printf("ksi at %llu is (%d, %d, %d)\n", t->traj_size, ksi.v1, ksi.v2, ksi.v3);
        sigma = h->h[ksi.v1][ksi.v2][ksi.v3];
        if (int_vec2_all_eq(&sigma, &INT_VEC2_ZERO)) {
            printf("sigma is 0, 0\n");
            break;
        }
        uk = p(&sigma, &Nu, &u_min, &u_max);

        xkp1 = f(&xk, &uk, w);
        // THE PROBLEM HERE, WHEN COMMENTED IT WORKS
        if (xkp1.v3 < -PI) {
            xkp1.v3 += 2 * PI;
        }
        if (xkp1.v3 > PI) {
            xkp1.v3 -= 2 * PI;
        }
        //------------------------------------------
        printf("The point is (%f, %f, %f)\n", xkp1.v1, xkp1.v2, xkp1.v3);
        if (t->traj_size < s)
            t->points[t->traj_size++] = xkp1;
    }

    return t;
}


trajectory* construct_trajectory_for_reachability_controller(cont_sys f, static_symb_controller* h, float_vec3* w, float_vec3* x0, int_vec3_bitmap* Qa, int s) {
    trajectory* t = (trajectory*)malloc(sizeof(trajectory));
    t->points = (float_vec3*)malloc(sizeof(float_vec3) * s);
    t->traj_size = 1;

    t->points[0] = *x0;

    float_vec3 xk;
    float_vec3 xkp1;
    int_vec3 ksi;
    int_vec2 sigma;
    float_vec2 uk;
    while (!is_reachability_achieved(Qa, t->points[t->traj_size - 1]) && t->traj_size < s) {
        printf("The point is (%f, %f, %f)\n", t->points[t->traj_size].v1, t->points[t->traj_size].v2, t->points[t->traj_size].v3);
        printf("It is inside the region? %d\n", is_reachability_achieved(Qa, t->points[t->traj_size]));
        xk = t->points[t->traj_size - 1];
        ksi = q(&xk, &Nx, &x_min, &x_max);
        printf("ksi at %llu is (%d, %d, %d)\n", t->traj_size, ksi.v1, ksi.v2, ksi.v3);
        sigma = h->h[ksi.v1][ksi.v2][ksi.v3];
        if (int_vec2_all_eq(&sigma, &INT_VEC2_ZERO)) {
            printf("sigma is 0, 0\n");
            break;
        }
        uk = p(&sigma, &Nu, &u_min, &u_max);

        xkp1 = f(&xk, &uk, w);
        // THE PROBLEM HERE, WHEN COMMENTED IT WORKS
        if (xkp1.v3 < -PI) {
            xkp1.v3 += 2 * PI;
        }
        if (xkp1.v3 > PI) {
            xkp1.v3 -= 2 * PI;
        }
        //------------------------------------------
        if (t->traj_size < s)
            t->points[t->traj_size++] = xkp1;
        printf("The point is (%f, %f, %f)\n", t->points[t->traj_size].v1, t->points[t->traj_size].v2, t->points[t->traj_size].v3);
        printf("It is inside the region? %d\n", is_reachability_achieved(Qa, t->points[t->traj_size]));
    }

    return t;
}


trajectory* construct_trajectory_for_dynamic_controller(cont_sys f, dynamic_symb_controller* h, float_vec3* w, float_vec3* x0, int s) {
    trajectory* t = (trajectory*)malloc(sizeof(trajectory));
    t->points = (float_vec3*)malloc(sizeof(float_vec3) * s);
    t->traj_size = 1;

    t->points[0] = *x0;

    float_vec3 xk;
    float_vec3 xkp1;
    int_vec3 ksi;
    int_vec2 sigma;
    float_vec2 uk;
    int psi = q0;

    while (!is_specification_achieved(psi) && t->traj_size < s) {
        printf("The point is (%f, %f, %f)\n", t->points[t->traj_size - 1].v1, t->points[t->traj_size - 1].v2, t->points[t->traj_size - 1].v3);
        printf("Current state: %d\n", psi);
        xk = t->points[t->traj_size - 1];
        ksi = q(&xk, &Nx, &x_min, &x_max);
        printf("ksi at %llu is (%d, %d, %d)\n", t->traj_size, ksi.v1, ksi.v2, ksi.v3);
        sigma = h->h2[ksi.v1][ksi.v2][ksi.v3][psi];
        psi = h->h1[ksi.v1][ksi.v2][ksi.v3][psi];
        printf("Current state: %d\n", psi);
        if (int_vec2_all_eq(&sigma, &INT_VEC2_ZERO)) {
            printf("sigma is 0, 0\n");
            break;
        }
        uk = p(&sigma, &Nu, &u_min, &u_max);

        xkp1 = f(&xk, &uk, w);
        // THE PROBLEM HERE, WHEN COMMENTED IT WORKS
        if (xkp1.v3 < -PI) {
            xkp1.v3 += 2 * PI;
        }
        if (xkp1.v3 > PI) {
            xkp1.v3 -= 2 * PI;
        }
        //------------------------------------------
        if (t->traj_size < s)
            t->points[t->traj_size++] = xkp1;
        printf("The point is (%f, %f, %f)\n", t->points[t->traj_size-1].v1, t->points[t->traj_size-1].v2, t->points[t->traj_size-1].v3);
    }
    printf("rrr\n");

    return t;
}