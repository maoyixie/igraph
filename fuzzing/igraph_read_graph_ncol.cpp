#include <igraph.h>
#include <cstdio>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
    FILE *MemFile = fmemopen((void *)Data, Size, "rb");
    if (!MemFile)
    {
        return 0;
    }

    igraph_t graph;
    igraph_strvector_t predefnames;
    igraph_error_t err;

    igraph_strvector_init(&predefnames, 0);

    err = igraph_read_graph_ncol(&graph, MemFile, &predefnames, /*names=*/1, IGRAPH_ADD_WEIGHTS_NO, /*directed=*/1);
    if (err == IGRAPH_SUCCESS)
    {
        igraph_destroy(&graph);
    }

    igraph_strvector_destroy(&predefnames);
    fclose(MemFile);

    return 0;
}