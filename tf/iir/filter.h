/**
 * @brief nth-order IIR filter for given discrete transfer function coefficients.
 * @author risherlock
 * @date 2025-02-02
 */

template <int order>
class filter
{
private:
  double a[order + 1];
  double b[order + 1];
  double x[order + 1] = {0};
  double y[order + 1] = {0};

public:
  filter(const double b_in[order + 1], const double a_in[order + 1]);

  double update(double input);
  void set_x0(const double x0[order]);
};

/**
 * @brief Set the coefficients of the filter's transfer function, expressed as:
 *
 *         Y(z)     b[0] + b[1] * z^(-1) + b[2] * z^(-2) + ... + b[n] * z^(-n)
 * H(z) = ------ = ------------------------------------------------------------
 *         X(z)     a[0] + a[1] * z^(-1) + a[2] * z^(-2) + ... + a[m] * z^(-m)
 *
 * where m <= n and order of TF = n - 1.
 *
 * @note Please append zeros to a_in[] if m < n.
 *       If a[0] == 0, the update() function will return only zeros.
 */
template <int order>
filter<order>::filter(const double b_in[order + 1], const double a_in[order + 1])
{
  // Avoid division by zero
  if (a_in[0] == 0.0)
  {
    return;
  }

  for (int i = 0; i <= order; i++)
  {
    b[i] = b_in[i] / a_in[0];
    a[i] = a_in[i] / a_in[0];
  }
}

/**
 * @brief Performs a single step of the discrete IIR filter.
 *
 * @param input The discrete-time input signal x[t] to the transfer function.
 * @returns The discrete-time output signal y[t] from the transfer function.
 */
template <int order>
double filter<order>::update(double input)
{
  x[0] = input;
  y[0] = b[0] * x[0];

  for (int i = 1; i <= order; ++i)
  {
    y[0] += b[i] * x[i] - a[i] * y[i];
  }

  for (int i = order; i > 0; --i)
  {
    x[i] = x[i - 1];
    y[i] = y[i - 1];
  }

  return y[0];
}

/**
 * @brief Sets the initial state, which would otherwise be zero.
 *
 * Initializing the filter is analogous to setting initial conditions when integrating a
 * differential equation. After all, a transfer function is derived from a differential
 * equation, and this filter implementation represents its solution (i.e. numerical integration).
 *
 * @param x0[order] Initial states of the filter, equal in number to the filter order.
 *
 * @note Proper initialization results in a better transient response.
 */
template <int order>
void filter<order>::set_x0(const double x0[order])
{
  for (int i = order - 1; i > 0; i--)
  {
    x[i + 1] = x0[i];
  }
}
