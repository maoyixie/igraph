#include <igraph.h>
#include <cstdio>
// igraph_read_graph_edgelist参数不匹配

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
    FILE *f;
    igraph_t graph;
    igraph_integer_t n = 0;
    igraph_bool_t directed = 0;

    // Create a temporary file with the fuzzed data
    f = tmpfile();
    if (!f)
    {
        return 0;
    }

    // Write the fuzzed data to the temporary file
    fwrite(Data, sizeof(uint8_t), Size, f);

    // Set the file position to the beginning
    rewind(f);

    // Call the function to be fuzzed with the temporary file
    // igraph_read_graph_edgelist参数不匹配
    igraph_read_graph_edgelist(&graph, f, n, directed);

    // Close and remove the temporary file
    fclose(f);

    // Destroy the graph object
    igraph_destroy(&graph);

    return 0;
}