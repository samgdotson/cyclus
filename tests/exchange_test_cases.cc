#include <gtest/gtest.h>

#include "exchange_test_cases.h"

#include "exchange_graph.h"

namespace cyclus {

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Case0::Construct(ExchangeGraph* g) {}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Case0::Test(std::string solver_type, ExchangeGraph* g) {
  EXPECT_TRUE(g->matches().empty());
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Case1a::Construct(ExchangeGraph* g) {
  RequestGroup::Ptr group = RequestGroup::Ptr(new RequestGroup());
  ExchangeNode::Ptr n = ExchangeNode::Ptr(new ExchangeNode());
  group->AddExchangeNode(n);
  g->AddRequestGroup(group);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Case1a::Test(std::string solver_type, ExchangeGraph* g) {
  EXPECT_TRUE(g->matches().empty());
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Case1b::Construct(ExchangeGraph* g) {
  ExchangeNodeGroup::Ptr group = ExchangeNodeGroup::Ptr(new ExchangeNodeGroup());
  ExchangeNode::Ptr n = ExchangeNode::Ptr(new ExchangeNode());
  group->AddExchangeNode(n);
  g->AddSupplyGroup(group);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Case1b::Test(std::string solver_type, ExchangeGraph* g) {
  EXPECT_TRUE(g->matches().empty());
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Case2::Construct(ExchangeGraph* g) {
  ExchangeNode::Ptr u(new ExchangeNode());
  ExchangeNode::Ptr v(new ExchangeNode());
  Arc a(u, v);

  u->unit_capacities[a].push_back(unit_cap_req);
  v->unit_capacities[a].push_back(unit_cap_sup);
  
  RequestGroup::Ptr request(new RequestGroup(qty));
  request->AddCapacity(qty);
  request->AddExchangeNode(u);  
  g->AddRequestGroup(request);

  ExchangeNodeGroup::Ptr supply(new ExchangeNodeGroup());
  supply->AddCapacity(capacity);
  supply->AddExchangeNode(v);  
  g->AddSupplyGroup(supply);

  g->AddArc(a);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Case2::Test(std::string solver_type, ExchangeGraph* g) {
  if (solver_type == "greedy") {
    ASSERT_TRUE(g->arcs().size() > 0);
    Match exp = Match(g->arcs().at(0), flow);
    ASSERT_TRUE(g->matches().size() > 0);
    EXPECT_EQ(exp, g->matches().at(0));
  }
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Case2a::Construct(ExchangeGraph* g) {
  // set 2a members
  qty = 5;
  unit_cap_req = 1;
  capacity = 10;
  unit_cap_sup = 1;
  flow = qty;

  Case2::Construct(g);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Case2b::Construct(ExchangeGraph* g) {
  // set 2b members
  qty = 10;
  unit_cap_req = 1;
  capacity = 10;
  unit_cap_sup = 2;
  flow = capacity / unit_cap_sup;

  Case2::Construct(g);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Case2c::Construct(ExchangeGraph* g) {
  // set 2c members
  qty = 10;
  unit_cap_req = 1;
  capacity = 5;
  unit_cap_sup = 1;
  flow = capacity;

  Case2::Construct(g);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Case2d::Construct(ExchangeGraph* g) {
  // set 2d members
  qty = 10;
  unit_cap_req = 1;
  capacity = 5;
  unit_cap_sup = 0.3;
  flow = qty;

  Case2::Construct(g);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Case2e::Construct(ExchangeGraph* g) {
  // set 2e members
  qty = 10;
  unit_cap_req = 1;
  capacity = 10;
  unit_cap_sup = 0.3;
  flow = qty;

  Case2::Construct(g);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Case2f::Construct(ExchangeGraph* g) {
  // set 2f members
  qty = 10;
  unit_cap_req = 1;
  capacity = 10;
  unit_cap_sup = 2;
  flow = capacity / unit_cap_sup;

  Case2::Construct(g);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Case2g::Construct(ExchangeGraph* g) {
  // set 2g members
  qty = 10;
  unit_cap_req = 0.9;
  capacity = 10;
  unit_cap_sup = 1;
  flow = capacity;

  Case2::Construct(g);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Case2h::Construct(ExchangeGraph* g) {
  // set 2h members
  qty = 10;
  unit_cap_req = 2;
  capacity = 10;
  unit_cap_sup = 1;
  flow = capacity / unit_cap_req;

  Case2::Construct(g);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Case6::Construct(ExchangeGraph* g) {  
  ExchangeNode::Ptr u1_1(new ExchangeNode());
  ExchangeNode::Ptr u1_2(new ExchangeNode());
  ExchangeNode::Ptr u2_1(new ExchangeNode());
  ExchangeNode::Ptr u2_2(new ExchangeNode());
  ExchangeNode::Ptr v1_1(new ExchangeNode());
  ExchangeNode::Ptr v1_2(new ExchangeNode());
  ExchangeNode::Ptr v2_1(new ExchangeNode());
  ExchangeNode::Ptr v2_2(new ExchangeNode());
  Arc a1(u1_1, v1_1);
  Arc a2(u1_2, v2_1);
  Arc a3(u2_1, v1_2);
  Arc a4(u2_2, v2_2);

  u1_1->unit_capacities[a1].push_back(1);
  u1_2->unit_capacities[a2].push_back(1);
  u2_1->unit_capacities[a3].push_back(1);
  u2_2->unit_capacities[a4].push_back(1);
  v1_1->unit_capacities[a1].push_back(1);
  v1_2->unit_capacities[a3].push_back(1);
  v2_1->unit_capacities[a2].push_back(1);
  v2_2->unit_capacities[a4].push_back(1);

  RequestGroup::Ptr req1(new RequestGroup(q1));
  req1->AddCapacity(q1);
  req1->AddExchangeNode(u1_1);
  req1->AddExchangeNode(u1_2);  
  g->AddRequestGroup(req1);
  
  RequestGroup::Ptr req2(new RequestGroup(q2));
  req2->AddCapacity(q2);
  req2->AddExchangeNode(u2_1);
  req2->AddExchangeNode(u2_2);  
  g->AddRequestGroup(req2);
  
  ExchangeNodeGroup::Ptr sup1(new ExchangeNodeGroup());
  sup1->AddCapacity(c1);
  sup1->AddExchangeNode(v1_1);  
  sup1->AddExchangeNode(v1_2);  
  g->AddSupplyGroup(sup1);
  
  ExchangeNodeGroup::Ptr sup2(new ExchangeNodeGroup());
  sup2->AddCapacity(c2);
  sup2->AddExchangeNode(v2_1);
  sup2->AddExchangeNode(v2_2);
  g->AddSupplyGroup(sup2);
  
  g->AddArc(a1);
  g->AddArc(a2);
  g->AddArc(a3);
  g->AddArc(a4);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Case6a::Construct(ExchangeGraph* g) {
  q1 = 7;
  c1 = 5;
  c2 = q1 - c1 + 3;
  q2 = c2 - (q1 - c1) - 1;
  f1 = c1;
  f2 = q1 - c1;
  f4 = q2;

  Case6::Construct(g);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Case6a::Test(std::string solver_type, ExchangeGraph* g) {
  if (solver_type == "greedy") {
    ASSERT_TRUE(g->arcs().size() > 3);
    EXPECT_EQ(g->arcs().size(), 4);
  
    Match exp1 = Match(g->arcs().at(0), f1);
    Match exp2 = Match(g->arcs().at(1), f2);
    Match exp3 = Match(g->arcs().at(3), f4);
    Match arr[] = {exp1, exp2, exp3};
    std::vector<Match> vexp(arr, arr + sizeof(arr) / sizeof(arr[0]));
    EXPECT_EQ(vexp, g->matches());
  }
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Case6b::Construct(ExchangeGraph* g) {
  q1 = 5;
  c1 = 7;
  q2 = c1 - q1 + 0.5;
  c2 = q2 - (c1 - q1) + 3;
  f1 = q1;
  f3 = c1 - q1;
  f4 = q2 - (c1 - q1);

  Case6::Construct(g);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Case6b::Test(std::string solver_type, ExchangeGraph* g) {
  if (solver_type == "greedy") {
    ASSERT_TRUE(g->arcs().size() > 3);
    EXPECT_EQ(g->arcs().size(), 4);
  
    Match exp1 = Match(g->arcs().at(0), f1);
    Match exp2 = Match(g->arcs().at(2), f3);
    Match exp3 = Match(g->arcs().at(3), f4);
    Match arr[] = {exp1, exp2, exp3};
    std::vector<Match> vexp(arr, arr + sizeof(arr) / sizeof(arr[0]));
    EXPECT_EQ(vexp, g->matches());
  }
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Case7::Construct(ExchangeGraph* g) {
  qty = 5;
  N = 10;
  flow = qty / N;
  
  // a single request for qty of a resource
  ExchangeNode::Ptr u(new ExchangeNode());
  RequestGroup::Ptr req(new RequestGroup(qty));
  req->AddCapacity(qty);
  req->AddExchangeNode(u);
  g->AddRequestGroup(req);

  // a node group with N bids for q/N of a resource
  ExchangeNodeGroup::Ptr sup(new ExchangeNodeGroup());
  sup->AddCapacity(qty);  
  for (int i = 0; i < N; i++) {
    ExchangeNode::Ptr v(new ExchangeNode(qty / N)); 
    sup->AddExchangeNode(v);  
    Arc a(u, v);
    u->unit_capacities[a].push_back(1);
    v->unit_capacities[a].push_back(1);
    g->AddArc(a);
  }
  g->AddSupplyGroup(sup);    
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Case7::Test(std::string solver_type, ExchangeGraph* g) {
  if (solver_type == "greedy") {
    ASSERT_EQ(g->arcs().size(), N);
    ASSERT_EQ(g->matches().size(), N);
    for (int i = 0; i < N; i++) {
      Match exp = Match(g->arcs().at(i), flow);
      EXPECT_EQ(exp, g->matches().at(i));
    }
  }
}

} // namespace cyclus