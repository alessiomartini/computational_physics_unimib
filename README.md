# Computational Physics — Exercise Collection (UniMiB)

The twenty programming exercises of the *Fisica Computazionale* course, BSc in
Physics, Università degli Studi di Milano-Bicocca — Alessio Martini (student
no. 867624).

Each exercise is a **self-contained C program** that writes its results to a
text file, paired with a **Mathematica notebook** that reads that file and
produces the plots and the discussion. The full written report is
[`Fisica Computazionale - Alessio Martini 867624.pdf`](Fisica%20Computazionale%20-%20Alessio%20Martini%20867624.pdf).

Code comments are in Italian.

## The exercises

The collection walks through the standard curriculum of numerical methods for
physics, in four blocks.

### Floating-point arithmetic and series summation — `es1`, `es2`

Where numerical analysis starts: finite precision. Summing a series forwards
versus backwards and watching the two answers disagree; single versus double
precision; catastrophic cancellation, and the growth of round-off error with the
number of terms.

### Numerical integration — `es3` … `es7`

| Exercise | Content |
| --- | --- |
| `es3_x^7e^-x` | Trapezoid, Simpson and **Romberg** on $\int x^7 e^{-x}\,dx$, compared against the exact value |
| `es4_coseno_iperbolico` | The same three methods on the hyperbolic cosine |
| `es5` | Trapezoid, Simpson, Romberg **and Gauss–Legendre** on the same integrand, so the quadrature families can be compared directly |
| `es6` | Romberg built on top of trapezoid *and* on top of Simpson, compared |
| `es7` | **Gaussian quadrature** on infinite ranges: Gauss–Laguerre and Gauss–Hermite, using precomputed nodes and weights |

The shared machinery lives in the headers at the repository root:
`integration.h` (the `GLAW` node/weight structure and the quadrature drivers)
with `legendre_data.h`, `laguerre_data.h` and `hermite_data.h` supplying the
tabulated abscissae and weights up to order 20.

### Monte Carlo methods — `es8` … `es13`

| Exercise | Content |
| --- | --- |
| `es8_ipersfera` | Volume of the **hypersphere** in $d$ dimensions by hit-or-miss sampling — the textbook demonstration that Monte Carlo wins as the dimension grows |
| `es9` | **Moments of the distribution of the sample mean**: many independent averages are generated, each from `N_PUNTI` points, and their moments are tracked as `N_PUNTI` grows — the Central Limit Theorem, measured |
| `es10` | **Error estimation**: mean and quadratic mean, the statistical error that follows from them, and the fraction of rejected points in hit-or-miss sampling |
| `es11`, `es12` | Sampling non-uniform distributions from a uniform generator — the exact (inversion) method and rejection — with the result checked against the target density by histogram |
| `es13` | **Importance sampling**: choosing a sampling density matched to the integrand to cut the variance |

### Differential equations and root finding — `es14` … `es20`

| Exercise | Content |
| --- | --- |
| `es14_oscillatore_armonico_semplice` | The simple harmonic oscillator: Euler versus Runge–Kutta, and the energy drift that exposes an unstable scheme |
| `es15` | The **damped** oscillator (viscous friction) |
| `es16` | The **damped and driven** oscillator, with `MU`, `ALPHA`, `BETA` as tunable parameters |
| `es17` | A three-dimensional first-order system, integrated with Euler, RK2 and RK4 side by side |
| `es18_tre_corpi` | The **three-body problem**: a vector second-order ODE with a `struct part` per particle, integrated as a full N-body step |
| `es19_zeri_reali` | **Real roots**: bracketing by scanning with resolution $\varepsilon$, then bisection and Newton |
| `es20_zeri_complessi` | **Complex roots** with `std::complex`, over a grid of starting points — which is how a Newton fractal appears |

## Building and running

Every source file carries its own compile line as the first comment, so nothing
needs to be guessed. Most are plain C:

```bash
cd es1
gcc -o esercizio1.exe esercizio1.c -lm && ./esercizio1.exe
```

A few (`es10`, `es14`, `es15`, `es18`, `es20`) use C++ features — `std::tuple`,
`std::complex` — and are compiled with `g++` instead; their header comment says
so.

Each program writes a `data.txt` (or similar) next to itself. Open the matching
`esercizioN.nb` in Mathematica to load that file and reproduce the plots.

## A note on the structure

The exercises with a descriptive suffix (`es3_x^7e^-x`,
`es8_ipersfera`, `es18_tre_corpi`, `es19_zeri_reali`, `es20_zeri_complessi`, …)
are the ones whose topic was worth recording in the folder name; the bare
numbered ones follow the numbering of the course assignment sheet. The table
above is the map between the two.
