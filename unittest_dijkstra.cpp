#include <gtest/gtest.h>
#include "dijkstra.cpp"


void setup_graph(graph &g, string test_set = "europe"){
    load_vertices("graph_templates/" + test_set + "/vertices.dat", g);
    load_edges("graph_templates/" + test_set + "/edges.dat", g, true);
}


TEST(BasicTestsSuite, subproblemsTest) {
    graph g;
    setup_graph(g, "latvia");

    ASSERT_EQ(
        dijkstra(g.vertices["Riga"], g.vertices["Jurmala"]),
        dijkstra(g.vertices["Riga"], g.vertices["Babite"])
        + dijkstra(g.vertices["Babite"], g.vertices["Jurmala"]) 
        );
}


TEST(NonExistingNodeSuite, nullptrTest) {
    graph g; 
    setup_graph(g);

    vertex* from = g.vertices["Berlin"];
    vertex* to = g.vertices["-"];
    ASSERT_EQ(dijkstra(from, to), -1);
    g.reset();
}

TEST(NonExistingNodeSuite, fullConnectivityTest){
    ASSERT_EQ(
        dijkstra(
            new vertex("NewVertex"),
            new vertex("NewVertex2")
        ), -1
    );
}

TEST(NonExistingNodeSuite, partialConnectivityTest){
    graph g; 
    setup_graph(g);

    ASSERT_EQ(
        dijkstra(
            g.vertices["Berlin"],
            new vertex("NewVertex2")
        ), -1
    );

    g.reset();

    ASSERT_EQ(
        dijkstra(
            new vertex("NewVertex2"),
            g.vertices["Berlin"]
        ), -1
    );
}


TEST(NodeSwapSuite, nodeSwapTests) {
    graph g;
    setup_graph(g);

    ASSERT_EQ(
        dijkstra(new vertex("Berlin"), new vertex("Lisbon")),
        dijkstra(new vertex("Lisbon"), new vertex("Berlin"))
    );

    ASSERT_EQ(
        dijkstra(new vertex("Moscow"), new vertex("Copenhagen")),
        dijkstra(new vertex("Copenhagen"), new vertex("Moscow"))
    );

    ASSERT_EQ(
        dijkstra(new vertex("Tallinn"), new vertex("Vilnius")),
        dijkstra(new vertex("Vilnius"), new vertex("Tallinn"))
    );

    ASSERT_EQ(
        dijkstra(new vertex("Riga"), new vertex("Oslo")),
        dijkstra(new vertex("Oslo"), new vertex("Riga"))
    );
}

TEST(LargeSizeSuite, largeSizeTest) {
    graph g;
    setup_graph(g, "numerical_V500_E450");

    ASSERT_EQ(dijkstra(g.vertices["E1"], g.vertices["E381"]), 68851);
}


TEST(NegativeWeightSuite, negativeWeightTest) {
    graph g;
    g.add_vertex("1");
    g.add_vertex("2");
    g.add_vertex("3");
    g.add_vertex("4");
    g.add_vertex("5");
    g.add_edge("1", "2", -1);
    g.add_edge("2", "3", -1);
    g.add_edge("2", "5", -1); 

    ASSERT_EQ(dijkstra(g.vertices["1"], g.vertices["5"]), -2);
}

TEST(LoopSuite, loopTest) {
    graph g;
    g.add_vertex("1");
    g.add_vertex("2");
    g.add_vertex("3");
    g.add_vertex("4");
    g.add_vertex("5");
    g.add_vertex("6");
    g.add_edge("1", "2", 1);
    g.add_edge("2", "3", 1);
    g.add_edge("3", "1", 1);
    g.add_edge("2", "5", 1);
    g.add_edge("5", "6", 1);

    ASSERT_EQ(dijkstra(g.vertices["1"], g.vertices["6"]), 3);
}


int main(int argc, char **argv) {
    // Initialize Google Test library
    ::testing::InitGoogleTest(&argc, argv);
    
    // Run the tests
    return RUN_ALL_TESTS();
}