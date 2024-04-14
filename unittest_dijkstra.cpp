#include <gtest/gtest.h>
#include "dijkstra.cpp"

int dijkstra_wrapper(graph g, string _from, string _to){
    vertex* from = g.vertices[_from];
    vertex* to = g.vertices[_to];
    int res = dijkstra(from, to);
    g.reset();
    return res;
}

void setup_graph(graph &g, string test_set = "europe"){
    load_vertices("graph_templates/" + test_set + "/vertices.dat", g);
    load_edges("graph_templates/" + test_set + "/edges.dat", g, true);
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

TEST(EqualEndpointsSuite, equalEndpointsTest) {
    graph g;
    setup_graph(g, "numerical_E500_V450");

    ASSERT_EQ(dijkstra(g.vertices["E1"], g.vertices["E381"]), 68851);
    

}



int main(int argc, char **argv) {
    // Initialize Google Test library
    ::testing::InitGoogleTest(&argc, argv);
    
    // Run the tests
    return RUN_ALL_TESTS();
}