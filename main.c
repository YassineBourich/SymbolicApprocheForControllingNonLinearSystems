#include <stdio.h>
#include "Concretisation/ConcreteModel.h"
#include "SymbolicModel/SymbolicModel.h"
#include "ReachabilityAnalysis/Reachability.h"
#include "SymbolicController/SafetyController.h"
#include "ContinuousSystem/Model_3D.h"
#include "BitMap/BitMap.h"
#include "Discretization/KSI.h"
#include "Discretization/SIGMA.h"
#include "Visualization/ploting.h"


int main() {
    /*// (2, 14, 8), (2, 2)
    int_vec3 ksi = (int_vec3){23, 51, 12};
    float_vec3_pair min_max = getPartitionMinAndMax(&ksi, &Nx, &x_min, &x_max);
    float_vec2 u = {0.5, 0};
    float_vec3 w = {0, 0, 0};
    float_vec3 x1 = f(&min_max.vect1, &u, &w);
    float_vec3 x2 = f(&min_max.vect2, &u, &w);

    printf("x_min is (%f, %f, %f)\n", x1.v1, x1.v2, x1.v3);
    printf("x_max is (%f, %f, %f)\n", x2.v1, x2.v2, x2.v3);

    
    float_vec3_pair f_min_max = get_reachable_region(&min_max.vect1, &min_max.vect2, &u, &w_min, &w_max, BOUNDED_JACOBIAN_REACHABILITY, Jacx, Jacw);

    if (f_min_max.vect1.v3 < -PI) {
        f_min_max.vect1.v3 += 2 * PI;
    }
    if (f_min_max.vect1.v3 > PI) {
        f_min_max.vect1.v3 -= 2 * PI;
    }
    if (f_min_max.vect2.v3 < -PI) {
        f_min_max.vect2.v3 += 2 * PI;
    }
    if (f_min_max.vect2.v3 > PI) {
        f_min_max.vect2.v3 -= 2 * PI;
    }
    
    printf("f_min is (%f, %f, %f)\n", f_min_max.vect1.v1, f_min_max.vect1.v2, f_min_max.vect1.v3);
    printf("f_max is (%f, %f, %f)\n", f_min_max.vect2.v1, f_min_max.vect2.v2, f_min_max.vect2.v3);

    int_vec3 q_min = q(&f_min_max.vect1, &Nx, &x_min, &x_max);
    int_vec3 q_max = q(&f_min_max.vect2, &Nx, &x_min, &x_max);
    
    printf("q_min is (%d, %d, %d)\n", q_min.v1, q_min.v2, q_min.v3);
    printf("q_max is (%d, %d, %d)\n", q_max.v1, q_max.v2, q_max.v3);*/
    printf("contructing symb model...\n");
    symb_model* m = construct_symbolic_model(BOUNDED_JACOBIAN_REACHABILITY);

    /*model_node no;
    for (int p1 = 1; p1 < NX_1; p1++) {
        for (int p2 = 1; p2 < NX_2; p2++) {
            for (int p3 = 1; p3 < NX_3; p3++) {
                for (int c1 = 1; c1 < NU_1; c1++) {
                    for (int c2 = 1; c2 < NU_2; c2++) {
                        no = m->model[p1][p2][p3][c1][c2];
                        printf("g((%d, %d, %d), (%d, %d)) = [(%d, %d, %d), (%d, %d, %d), %d]\n", p1, p2, p3, c1, c2, no.q_min_max.vect1.v1, no.q_min_max.vect1.v2, no.q_min_max.vect1.v3, no.q_min_max.vect2.v1, no.q_min_max.vect2.v2, no.q_min_max.vect2.v3, no.includes_0);
                    }
                }
            }
        }
    }*/

    /*float a = 2, b = 3, c = 5, d = 7;

    printf("Defining safety region...\n");
    int total = NX_1 * NX_2 * NX_3;
    int_vec3 *vectors = malloc(total * sizeof(int_vec3));
    if (!vectors) {
        fprintf(stderr, "malloc failed\n");
        return 1;
    }
    int list_size = 0;
    int_vec3 vec;
    float_vec3_pair min_max;
    for (int p1 = 1; p1 <= NX_1; p1++) {
        for (int p2 = 1; p2 <= NX_2; p2++) {
            for (int p3 = 1; p3 <= NX_3; p3++) {
                vec = (int_vec3){p1, p2, p3};
                min_max = getPartitionMinAndMax(&vec, &Nx, &x_min, &x_max);
                if (a <= min_max.vect1.v1 && min_max.vect2.v1 <= c && b <= min_max.vect1.v2 && min_max.vect2.v2 <= d) {
                    vectors[list_size++] = vec;
                }
            }
        }
    }

    printf("Creating bitmap...\n");
    fflush(stdout);
    fprintf(stderr, "Reached before bitmap\n");
    fflush(stderr);
    int_vec3_bitmap Qs = bitmap_create_from_array_vec3(vectors, list_size, &Nx);

    free(vectors);*/

    printf("Constructing the symbolic model...\n");
    //static_symb_controller* h = construct_safety_symbolic_controller(m, &Qs);
    //static_symb_controller* h = construct_reachability_symbolic_controller(m, &Qs);
    dynamic_symb_controller* h = construct_dynamic_symbolic_controller(m);
    //bitmap_free(&Qs);

    float_vec3 w = {0.01, -0.03, 0.02};
    float_vec3 x0 = getPartitionMinAndMax(&h->Q0.data[3], &Nx, &x_min, &x_max).vect1;

    printf("Constructing the trajectory...\n");
    trajectory* t = construct_trajectory_for_dynamic_controller(f, h, &w, &x0, 200);

    //bitmap_free(&Qs);
    free(m);
    dynamic_symb_controller_free(h);
    /*trajectory* t = malloc(sizeof(trajectory));
    int s = 200;
    t->points = (float_vec3*)malloc(sizeof(float_vec3) * s);
    t->traj_size = s;
    for (int i = 0; i < t->traj_size; i++) {
        t->points[i] = (float_vec3){i, i*i, 0};
    }*/
    
    for (int i = 0; i < t->traj_size; i++) {
        printf("point %d is: (%f, %f, %f)\n", i, t->points[i].v1, t->points[i].v2, t->points[i].v3);
    }

    //float_vec2 rec_min = (float_vec2){a, b};
    //float_vec2 rec_max = (float_vec2){c, d};
    //rect Rectangle = (rect){rec_min, rec_max};

    regions* R = regions_create(rectangls, colors, SIGMA);

    printf("Calling plot_trajectory...\n");
    fflush(stdout);
    plot_trajectory(t, *R);
    
    free(t->points);
    free(t);

    return 0;
}
