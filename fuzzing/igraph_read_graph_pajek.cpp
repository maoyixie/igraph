#include <igraph.h>
#include <cstdio>

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
    // Create a temporary file and write the Data into it
    FILE *temp_file = tmpfile();
    if (!temp_file)
    {
        return 0;
    }
    fwrite(Data, 1, Size, temp_file);
    rewind(temp_file);

    // Initialize the igraph_t structure
    igraph_t graph;
    igraph_empty(&graph, 0, IGRAPH_UNDIRECTED);

    // Call the function with the temporary file
    igraph_read_graph_pajek(&graph, temp_file);

    // Clean up
    igraph_destroy(&graph);
    fclose(temp_file);

    return 0;
}