#include <gtest/gtest.h>

#include "exchange_graph.h"
#include "greedy_solver.h"

#include "exchange_test_cases.h"

#include "solver_tests.h"

namespace cyclus {

#if GTEST_HAS_TYPED_TEST

using testing::Types;

// The list of types we want to test, add yours to it!
template <>
ExchangeCase* CreateExchangeCase<Case0>() { return new Case0; }

template <>
ExchangeCase* CreateExchangeCase<Case1a>() { return new Case1a; }

template <>
ExchangeCase* CreateExchangeCase<Case1b>() { return new Case1b; }

template <>
ExchangeCase* CreateExchangeCase<Case2a>() { return new Case2a; }

template <>
ExchangeCase* CreateExchangeCase<Case2b>() { return new Case2b; }

template <>
ExchangeCase* CreateExchangeCase<Case2c>() { return new Case2c; }

template <>
ExchangeCase* CreateExchangeCase<Case2d>() { return new Case2d; }

template <>
ExchangeCase* CreateExchangeCase<Case2e>() { return new Case2e; }

template <>
ExchangeCase* CreateExchangeCase<Case2f>() { return new Case2f; }

template <>
ExchangeCase* CreateExchangeCase<Case2g>() { return new Case2g; }

template <>
ExchangeCase* CreateExchangeCase<Case2h>() { return new Case2h; }

// template <>
// ExchangeCase* CreateExchangeCase<Case3a>() { return new Case3a; }

// template <>
// ExchangeCase* CreateExchangeCase<Case3b>() { return new Case3b; }

// template <>
// ExchangeCase* CreateExchangeCase<Case3c>() { return new Case3c; }

// template <>
// ExchangeCase* CreateExchangeCase<Case3d>() { return new Case3d; }

// template <>
// ExchangeCase* CreateExchangeCase<Case3e>() { return new Case3e; }

// template <>
// ExchangeCase* CreateExchangeCase<Case3f>() { return new Case3f; }

template <>
ExchangeCase* CreateExchangeCase<Case6a>() { return new Case6a; }

template <>
ExchangeCase* CreateExchangeCase<Case6b>() { return new Case6b; }

template <>
ExchangeCase* CreateExchangeCase<Case7>() { return new Case7; }

// Add it again here
typedef Types<Case0,
              Case1a, Case1b,
              Case2a, Case2b, Case2c, Case2d, Case2e, Case2f, Case2g, Case2h,
              // Case3a, Case3b, Case3c, Case3d, Case3e, Case3f,
              Case6a, Case6b,
              Case7>
Implementations;

TYPED_TEST_CASE(ExchangeSolverTest, Implementations);

TYPED_TEST(ExchangeSolverTest, GreedySolver) {
  std::string type = "greedy";
  ExchangeGraph g;
  this->case_->Construct(&g);
  GreedySolver solver(&g);
  solver.Solve();
  this->case_->Test(type, &g);
}

// add any more solvers to test here

#endif  // GTEST_HAS_TYPED_TEST

} // namespace cyclus