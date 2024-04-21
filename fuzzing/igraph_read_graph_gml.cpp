#include <igraph.h>
#include <cstdio>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
    FILE *input = NULL;
    igraph_t graph;

    // Create a temporary file with the provided data
    input = fmemopen((void *)Data, Size, "rb"); // input error
    if (!input)
    {
        return 0; // If the file could not be opened, return 0 (no crash)
    }

    // Initialize the graph
    igraph_empty(&graph, 0, IGRAPH_UNDIRECTED);

    // Call the fuzzed function
    igraph_error_t err = igraph_read_graph_gml(&graph, input); // input error

    // Close the temporary file
    fclose(input);

    // Destroy the graph to free resources
    igraph_destroy(&graph);

    // Return 1 if the fuzzed function failed, 0 otherwise
    return (err != IGRAPH_SUCCESS);
}