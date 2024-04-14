#include <igraph.h>
#include <cstdio>

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
    FILE *stream;
    igraph_t graph;
    igraph_bool_t names, directed;
    igraph_add_weights_t weights;

    // Create a temporary file from the fuzzed input data
    stream = fmemopen((void *)Data, Size, "rb");
    if (!stream)
    {
        return 0; // Cannot open the stream
    }

    // Randomly choose values for names and directed
    names = (Data[0] % 2) ? 1 : 0;
    directed = (Data[1] % 2) ? 1 : 0;

    // Randomly choose a value for weights
    weights = Data[2] % 3;

    // Call the target function with the fuzzed input
    igraph_read_graph_lgl(&graph, stream, names, weights, directed);

    // Free resources
    fclose(stream);
    igraph_destroy(&graph);

    return 0;
}