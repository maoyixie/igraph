#include <igraph.h>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
    if (Size < 1)
    {
        return 0;
    }

    igraph_t graph;
    igraph_integer_t res;
    igraph_bool_t checks;
    igraph_vector_t edges;
    igraph_error_t err;

    // Initialize the edge vector
    igraph_vector_init(&edges, 0);

    // Fill the edge vector with the fuzzer data
    for (size_t i = 0; i < Size - 1; i += 2)
    {
        igraph_vector_push_back(&edges, Data[i]);
        igraph_vector_push_back(&edges, Data[i + 1]);
    }

    // Create a graph from the edges
    err = igraph_create(&graph, &edges, 0, IGRAPH_UNDIRECTED);

    if (err == IGRAPH_SUCCESS)
    {
        // Set checks to true or false based on the last byte of the input data
        checks = Data[Size - 1] % 2;

        // Call the target function
        igraph_edge_connectivity(&graph, &res, checks);

        // Destroy the graph
        igraph_destroy(&graph);
    }

    // Destroy the edge vector
    igraph_vector_destroy(&edges);

    return 0;
}