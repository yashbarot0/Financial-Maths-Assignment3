#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <cmath>
#include <iostream>
#include <chrono>
#include <omp.h>

double european_call_price_omp(int n, double S0, double K, double sigma, double r) {
    const gsl_rng_type * T;
    gsl_rng * rng;
    gsl_rng_env_setup();
    T = gsl_rng_default; // Initialize GSL random number generator

    double sum = 0.0;

    #pragma omp parallel // Initialize OpenMP parallel region 
    {
        gsl_rng * local_rng = gsl_rng_alloc(T);
        const int seed = omp_get_thread_num() + 1; // Unique seed per thread
        gsl_rng_set(local_rng, seed);

        double local_sum = 0.0;

        #pragma omp for // Distribute iterations among threads
        for (int i = 0; i < n; ++i) {
            double z = gsl_ran_gaussian(local_rng, 1.0);
            double ST = S0 * exp((r - 0.5 * sigma * sigma) + sigma * z);
            double payoff = std::max(ST - K, 0.0);
            double discounted_payoff = payoff * exp(-r);
            local_sum += discounted_payoff;
        }

        #pragma omp atomic // Safely update the shared sum variable
        sum += local_sum;

        gsl_rng_free(local_rng);
    }

    return sum / n;
}

int main() {
    int n = 1000000; // Number of Monte Carlo samples
    double S0 = 100.0; // Spot price
    double K = 100.0; // Strike price
    double sigma = 0.2; // Volatility
    double r = 0.05; // Risk-free rate

    auto start = std::chrono::high_resolution_clock::now();  // Start timing

    double price = european_call_price_omp(n, S0, K, sigma, r);

    auto end = std::chrono::high_resolution_clock::now(); // End timing
    std::chrono::duration<double> elapsed = end - start; // Calculate elapsed time

    std::cout << "European Call Option Price: " << price << std::endl;
    std::cout << "Execution Time: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}