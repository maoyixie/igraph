#include <igraph.h>
#include <cstdio>

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
    if (Size < 1)
    {
        return 0;
    }

    FILE *instream = fmemopen((void *)Data, Size, "rb");
    if (!instream)
    {
        return 0;
    }

    igraph_t graph;
    igraph_empty(&graph, 0, IGRAPH_UNDIRECTED);

    igraph_bool_t directed = Data[0] % 2;
    igraph_error_t err = igraph_read_graph_dl(&graph, instream, directed);

    if (err == IGRAPH_SUCCESS)
    {
        igraph_destroy(&graph);
    }

    fclose(instream);
    return 0;
}