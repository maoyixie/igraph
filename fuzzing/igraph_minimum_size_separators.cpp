#include <igraph.h>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
    igraph_t graph;
    igraph_vector_int_list_t separators;
    igraph_error_t err;

    // Initialize the igraph library
    igraph_i_set_attribute_table(&igraph_cattribute_table);

    // Create a graph from the input data
    err = igraph_read_graph_edgelist(&graph, Data, Size / 2, 0);
    if (err != IGRAPH_SUCCESS)
    {
        return 0;
    }

    // Initialize the separators vector list
    err = igraph_vector_int_list_init(&separators, 0);
    if (err != IGRAPH_SUCCESS)
    {
        igraph_destroy(&graph);
        return 0;
    }

    // Call the function to be fuzzed
    err = igraph_minimum_size_separators(&graph, &separators);
    if (err != IGRAPH_SUCCESS)
    {
        igraph_vector_int_list_destroy(&separators);
        igraph_destroy(&graph);
        return 0;
    }

    // Clean up
    igraph_vector_int_list_destroy(&separators);
    igraph_destroy(&graph);

    return 0;
}