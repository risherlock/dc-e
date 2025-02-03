/**
 * @brief Implementation of nth-order IIR filter for given discrete transfer function coefficients.
 *
 * @details It uses Transposed Direct Form II structure which utilizes the fewest delay elements
 *          and multiplications. The implementation is based on Octave's 'filter()' function.
 *
 * @author risherlock
 * @date 2025-02-02
 */

template <int order>
class filter
{
private:
  double a[order + 1];   // Denominator coefficients
  double b[order + 1];   // Numerator coefficients
  double q[order] = {0}; // Internal state of the filter

public:
  filter(const double b_in[order + 1], const double a_in[order + 1]);

  double update(double input);
  void set_initial_state(const double x0[order]);
};

/**
 * @brief Set the coefficients of the IIR filter's transfer function, expressed as:
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
 * @brief Performs a single step of the discrete IIR filter i.e. returns the
 *        solution of linear, time-invariant different equation represented
 *        by H(z) using Transposed Direct Form II.
 *
 * @param input The discrete-time input signal x[t] to the transfer function.
 * @returns The discrete-time output signal y[t] from the transfer function.
 */
template <int order>
double filter<order>::update(double input)
{
  // Compute output using the first state
  double y = q[0] + b[0] * input;

  // Propagate the filter state
  for (int i = 0; i < order - 1; i++)
  {
    q[i] = q[i + 1] - a[i + 1] * y + b[i + 1] * input;
  }

  // Update the last state variable
  q[order - 1] = b[order] * input - a[order] * y;

  return y;
}

/**
 * @brief Sets the initial state of the filter, which would otherwise be zero.
 *        It is equivalent to equivalent to Octave’s si.
 *
 * @param x0[order] Initial states of the filter, equal in number to the filter order.
 */
template <int order>
void filter<order>::set_initial_state(const double q0[order])
{
  for (int i = 0; i < order; i++)
  {
    q[i] = q0[i];
  }
}
