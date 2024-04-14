#include <igraph.h>
#include <cstdio>

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
    // Create a temporary file with the input data
    FILE *tempFile = tmpfile();
    if (tempFile == NULL)
    {
        return 0;
    }

    // Write the input data to the temporary file
    fwrite(Data, 1, Size, tempFile);

    // Rewind the file pointer to the beginning of the file
    rewind(tempFile);

    // Create an empty igraph_t structure to store the graph
    igraph_t graph;
    igraph_empty(&graph, 0, IGRAPH_UNDIRECTED);

    // Call igraph_read_graph_graphml() to parse the input data as a GraphML file
    igraph_error_t err = igraph_read_graph_graphml(&graph, tempFile, 0);

    // Close the temporary file
    fclose(tempFile);

    // Check if the function call was successful
    if (err == IGRAPH_SUCCESS)
    {
        // If successful, destroy the graph to free resources and return 0
        igraph_destroy(&graph);
        return 0;
    }
    else
    {
        // If unsuccessful, destroy the graph to free resources and return 1
        igraph_destroy(&graph);
        return 1;
    }
}