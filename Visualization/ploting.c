#include "ploting.h"

BOOL plot_trajectory(trajectory* t, regions R) {
    int n = t->traj_size;

    // Open pipe to gnuplot
    FILE *gp = _popen("gnuplot -persist", "w");
    if (!gp) {
        perror("_popen failed");
        return FALSE;
    }
    printf("gnuplot opened\n");

    // Gnuplot commands
    fprintf(gp, "set title 'Trajectory with safety rectangle'\n");
    fprintf(gp, "set xlabel 'x'\n");
    fprintf(gp, "set ylabel 'y'\n");
    printf("commands assigned\n");

    // lock view window to [0,10]x[0,10]
    fprintf(gp, "set xrange [0:10]\n");
    fprintf(gp, "set yrange [0:10]\n");
    printf("axis fixed\n");

    // turn grid on
    fprintf(gp, "set grid\n");

    // draw regions
    for (size_t c = 0; c < R.size; c++) {
        fprintf(gp, "set object 1 rect from %f,%f to %f,%f fc rgb '%s' fs solid 0.3\n", R.Rectangls[c].vec_min.v1, R.Rectangls[c].vec_min.v2, R.Rectangls[c].vec_max.v1, R.Rectangls[c].vec_max.v2, R.colors[c]);
    }

    // plot trajectory points
    fprintf(gp, "plot '-' with linespoints title 'trajectory'\n");

    printf("sending data\n");
    // Send data points
    for (int i = 0; i < n; i++) {
        fprintf(gp, "%lf %lf\n", t->points[i].v1, t->points[i].v2);
    }

    // End of data
    fprintf(gp, "e\n");

    fflush(gp);
    _pclose(gp);

    return TRUE;
}