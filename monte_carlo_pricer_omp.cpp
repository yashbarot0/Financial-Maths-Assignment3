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
    T = gsl_rng_default;

    double sum = 0.0;

    #pragma omp parallel
    {
        gsl_rng * local_rng = gsl_rng_alloc(T);
        const int seed = omp_get_thread_num() + 1; // Unique seed per thread
        gsl_rng_set(local_rng, seed);

        double local_sum = 0.0;

        #pragma omp for
        for (int i = 0; i < n; ++i) {
            double z = gsl_ran_gaussian(local_rng, 1.0);
            double ST = S0 * exp((r - 0.5 * sigma * sigma) + sigma * z);
            double payoff = std::max(ST - K, 0.0);
            double discounted_payoff = payoff * exp(-r);
            local_sum += discounted_payoff;
        }

        #pragma omp atomic
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

    auto start = std::chrono::high_resolution_clock::now();

    double price = european_call_price_omp(n, S0, K, sigma, r);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "European Call Option Price: " << price << std::endl;
    std::cout << "Execution Time: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}