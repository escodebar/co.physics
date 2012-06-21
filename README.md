# co.physics #

## Computerorientierte Physik - Universität Bern ##
The course is aimed to provide students with a basic knowledge of C programming language and of its employment to address physics related questions such as numerical integration, solution of differential equation, Monte Carlo method for simulation of physical processes. The course will consist of three hours per week, one hour of theory and two hours of exercises. The students are not expected to have any background in programming.

### Index ###

* 09.1.1 - Bisection for Roots: root_bisection(function, start, end, precision, result)
* 09.1.2 - Newton Raphson for Roots: root_newton_raphson(function, derivate function, start, precision, result)
* 10.1.1 - Trapezoidal Integration: trapezoidal_integration(function, precision, start, end)
* 10.1.2 - Simpson's Integration: simpsons_integration(function, precision, start, end)
* 11.1.1 - Euler for Differential Equations: diff_eq_euler(function, startval, start, end, stepsize)
* 11.1.2 - Runge Kutta 2 for Differential Equations: diff_runge_kutta(function, startval, start, end, stepsize)
* 12.1.1 - Random Number Generator with Evaluation of Expectation Value, Variance for different Parameters
* 12.1.2 - Random Number Generator with Evaluation of the best Parameters
* 12.2.1 - Simulation of Ladders and Snakes with our Random Number Generator
* 12.2.2 - Simulation of Ladders and Snakes with the Random Number Generator of the Standard C Lib
* 13.1.1 - Sample Mean Monte Carlo Integration: monte_carlo(function, start, end, steps)
* 13.1.2 - Acceptance and Rejection Monte Carlo Integration: ar_monte_carlo(function, variance, x_start, x_end, y_start, y_end, precision)
* 13.2 - CDF Monte Carlo: cdf_monte_carlo(function, steps, bins)
