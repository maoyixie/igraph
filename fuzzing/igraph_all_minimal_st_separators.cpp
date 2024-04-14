#include <igraph.h>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
    if (Size < 2)
    {
        return 0;
    }

    igraph_t graph;
    igraph_vector_int_list_t separators;

    // Initialize the graph
    igraph_empty(&graph, 0, IGRAPH_UNDIRECTED);

    // Add edges based on input data
    for (size_t i = 0; i < Size - 1; i += 2)
    {
        igraph_integer_t from = Data[i] % igraph_vcount(&graph);
        igraph_integer_t to = Data[i + 1] % igraph_vcount(&graph);

        if (igraph_vcount(&graph) == 0 || from != to)
        {
            igraph_add_vertices(&graph, 1, 0);
        }
        igraph_add_edge(&graph, from, to);
    }

    // Call the function to be fuzzed
    igraph_all_minimal_st_separators(&graph, &separators);

    // Clean up
    igraph_vector_int_list_destroy(&separators);
    igraph_destroy(&graph);

    return 0;
}