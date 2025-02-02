/**
 * @brief IIR filter for given coefficients of transfer function.
 * @author risherlock
 * @date 2025-02-02
 */

template <int n>
class filter
{
private:
  double a[n + 1];
  double b[n + 1];
  double x[n + 1] = {0};
  double y[n + 1] = {0};

public:
  filter(const double b_in[n + 1], const double a_in[n + 1]);
  double update(double input);
};

template <int n>
filter<n>::filter(const double b_in[n + 1], const double a_in[n + 1])
{
  for (int i = 0; i <= n; i++)
  {
    b[i] = b_in[i] / a_in[0];
    a[i] = a_in[i] / a_in[0];
  }
}

/*
  Transfer function:

          Y(z)     b[0] + b[1] * z^(-1) + b[2] * z^(-2) + ... + b[n] * z^(-n)
  H(z) = ------ = ------------------------------------------------------------
          X(z)     a[0] + a[1] * z^(-1) + a[2] * z^(-2) + ... + a[m] * z^(-m)

  where m <= n.
*/
template <int n>
double filter<n>::update(double input)
{
  x[0] = input;
  y[0] = b[0] * x[0];

  for (int i = 1; i <= n; ++i)
  {
    y[0] += b[i] * x[i] - a[i] * y[i];
  }

  for (int i = n; i > 0; --i)
  {
    x[i] = x[i - 1];
    y[i] = y[i - 1];
  }

  return y[0];
}
