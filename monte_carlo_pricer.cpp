#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <cmath>
#include <iostream>
#include <chrono>

double european_call_price(int n, double S0, double K, double sigma, double r) {
    const gsl_rng_type * T;
    gsl_rng * rng;

    gsl_rng_env_setup();
    T = gsl_rng_default;
    rng = gsl_rng_alloc(T);
    gsl_rng_set(rng, 0); // Set seed for reproducibility

    double sum = 0.0;
    for (int i = 0; i < n; ++i) {
        double z = gsl_ran_gaussian(rng, 1.0);
        double ST = S0 * exp((r - 0.5 * sigma * sigma) + sigma * z);
        double payoff = std::max(ST - K, 0.0);
        double discounted_payoff = payoff * exp(-r);
        sum += discounted_payoff;
    }

    gsl_rng_free(rng);
    return sum / n;
}

int main() {
    int n = 1000000; // Number of Monte Carlo samples
    double S0 = 100.0; // Spot price
    double K = 100.0; // Strike price
    double sigma = 0.2; // Volatility
    double r = 0.05; // Risk-free rate

    auto start = std::chrono::high_resolution_clock::now();

    double price = european_call_price(n, S0, K, sigma, r);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "European Call Option Price: " << price << std::endl;
    std::cout << "Execution Time: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}