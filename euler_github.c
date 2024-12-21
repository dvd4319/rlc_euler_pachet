// Vasile-Daniel DAN 
// 17 December 2024
// Project Name: Euler Method applied to a RC circuit in time domain.
#include <stdio.h>
#define E 5.0 // [V]
#define C 0.001 // [F]
#define R 100.0 // [Ohm]
#define DT 0.001 
#define NUM_STEPS 500 


double derivative(double u){
    double tau = R*C;
    return (E-u)/tau;
}

int main(){

    double t[NUM_STEPS];
    double u[NUM_STEPS]; 
    double u_next; 

    t[0] = 0.00;
    u[0] = 0.00; 

    FILE *fp = NULL; 

    fp = fopen("rc_output_data.txt", "w");

    if(fp == NULL){
        printf("Error opening  the file.");
        return 1; 
    }

    for (int i = 0; i<= NUM_STEPS-1; i++){

        printf("t[%d] = %lf, u[%d] = %lf \n", i, t[i], i, u[i]);
        fprintf(fp," %lf\t %lf\n", t[i], u[i]);
        u_next = u[i] + DT*derivative(u[i]);
        t[i+1] = t[i] + DT; 
        u[i+1] = u_next; 
    }
    fclose(fp);
    // =============== GNU PLOT ==================== // 

    FILE *gnuplotPipe = NULL; 

    gnuplotPipe = popen("gnuplot -persist", "w");

    if(gnuplotPipe == NULL){
        printf("Error opening  Gnuplot");
        return 1; 
    }

    fprintf(gnuplotPipe, "set terminal png\n");
    fprintf(gnuplotPipe, "set output 'rc_euler_plot.png'\n");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set xlabel 't[s]'\n");
    fprintf(gnuplotPipe, "set ylabel 'u_C [V]'\n");
    fprintf(gnuplotPipe, "set label 'u_C(t) = E * (1-e^{-t/tau})' at 0.125,3\n");
    fprintf(gnuplotPipe, "set title 'Euler Method applied to a RC circuit in time domain'\n");
 
    fprintf(gnuplotPipe, "plot 'rc_output_data.txt' using 1:2 with lines linewidth 2 linecolor rgb 'blue'\n");

    fflush(gnuplotPipe);
    fprintf(gnuplotPipe, "exit\n");
    pclose(gnuplotPipe);
    
    return 0; 
}