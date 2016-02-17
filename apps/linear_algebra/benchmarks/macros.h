#define time_it(code)                               \
    double elapsed = 0;                             \
    for (int iters = 20; ; iters *= 2) {                    \
        double best = 1e20;                                 \
        for (int trials = 0; trials < 5; trials++) {        \
            double start = current_time();                  \
            for (int i = 0; i < iters; i++) {               \
                code;                                       \
            }                                               \
            double end = current_time();                    \
            best = std::min(end-start, best);               \
        }                                                   \
        elapsed = 1000 * best;                              \
        if (elapsed > 1000000) {                            \
            elapsed /= iters;                               \
            break;                                          \
        }                                                   \
    }

#define L1GFLOPS(N) 2 * N * 1e-3 / elapsed
#define L1Benchmark(benchmark, type, code)                              \
    virtual void bench_##benchmark(int N) {                             \
        Scalar alpha = random_scalar();                                 \
        (void) alpha;                                                   \
        Vector x(random_vector(N));                                     \
        Vector y(random_vector(N));                                     \
                                                                        \
        time_it(code)                                                   \
                                                                        \
        std::cout << std::setw(8) << name                               \
                  << std::setw(15) << type << #benchmark                \
                  << std::setw(8) << std::to_string(N)                  \
                  << std::setw(20) << std::to_string(elapsed)           \
                  << std::setw(20) << L1GFLOPS(N)                       \
                  << std::endl;                                         \
    }

#define L2GFLOPS(N) (2 + N) * N * 1e-3 / elapsed
#define L2Benchmark(benchmark, type, code)                              \
    virtual void bench_##benchmark(int N) {                             \
        Scalar alpha = random_scalar();                                 \
        Scalar beta = random_scalar();                                  \
        (void) alpha;                                                   \
        (void) beta;                                                    \
        Vector x(random_vector(N));                                     \
        Vector y(random_vector(N));                                     \
        Matrix A(random_matrix(N));                                     \
                                                                        \
        time_it(code)                                                   \
                                                                        \
        std::cout << std::setw(8) << name                               \
        << std::setw(15) << type << #benchmark                          \
                  << std::setw(8) << std::to_string(N)                  \
                  << std::setw(20) << std::to_string(elapsed)           \
                  << std::setw(20) << L2GFLOPS(N)                       \
                  << std::endl;                                         \
    }

#define L3GFLOPS(N) (3 + N) * N * N * 1e-3 / elapsed
#define L3Benchmark(benchmark, type, code)                              \
    virtual void bench_##benchmark(int N) {                             \
        Scalar alpha = random_scalar();                                 \
        Scalar beta = random_scalar();                                  \
        Matrix A(random_matrix(N));                                     \
        Matrix B(random_matrix(N));                                     \
        Matrix C(random_matrix(N));                                     \
                                                                        \
        time_it(code)                                                   \
                                                                        \
        std::cout << std::setw(8) << name                               \
                  << std::setw(15) << type << #benchmark                \
                  << std::setw(8) << std::to_string(N)                  \
                  << std::setw(20) << std::to_string(elapsed)           \
                  << std::setw(20) << L3GFLOPS(N)                       \
                  << std::endl;                                         \
    }
