#include <cppsvc/cppsvc.hpp>

auto main() -> int
{
  auto result = name();
  return result == "cppsvc" ? 0 : 1;
}
