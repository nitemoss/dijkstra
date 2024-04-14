#include <gtest/gtest.h>
#include "dijkstra.cpp"

int dijkstra_wrapper(graph g, string _from, string _to){
    vertex* from = g.vertices[_from];
    vertex* to = g.vertices[_to];
    int res = dijkstra(from, to);
    g.reset();
    return res;
}

void setup_graph(graph &g){
    load_vertices("graph_templates/europe/vertices.dat", g);
    load_edges("graph_templates/europe/edges.dat", g, true);
}

TEST(NonExistingNode, nullptrTest) {
    graph g; 
    setup_graph(g);

    vertex* from = g.vertices["Berlin"];
    vertex* to = g.vertices["-"];
    ASSERT_EQ(dijkstra(from, to), -1);
    g.reset();
}

TEST(NonExistingNode, connectivity_Test){
    ASSERT_EQ(
        dijkstra(
            new vertex("NewVertex"),
            new vertex("NewVertex2")
        ), -1
    );
}

TEST(NonExistingNode, partialConnectivityTest){
    graph g; 
    setup_graph(g);

    ASSERT_EQ(
        dijkstra(
            g.vertices["Berlin"],
            new vertex("NewVertex2")
        ), -1
    );
}


TEST(NodeTest, nodeSwapTests) {
    graph g;

    load_vertices("graph_templates/europe/vertices.dat", g);
    load_edges("graph_templates/europe/edges.dat", g, true);

    ASSERT_EQ(dijkstra_wrapper(g, "Berlin", "Lisbon"), 2432);
    ASSERT_EQ(dijkstra_wrapper(g, "Lisbon", "Berlin"), 2432);
    
    
}



int main(int argc, char **argv) {
    // Initialize Google Test library
    ::testing::InitGoogleTest(&argc, argv);
    
    // Run the tests
    return RUN_ALL_TESTS();
}