#include <igraph.h>
#include <cstdio>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
    // Create a temporary file from the fuzz input data
    char filename[] = "/tmp/fuzzXXXXXX";
    int fd = mkstemp(filename);
    if (fd == -1)
    {
        perror("mkstemp");
        return 0;
    }

    // Write fuzz input data to the temporary file
    if (write(fd, Data, Size) != Size)
    {
        perror("write");
        close(fd);
        unlink(filename);
        return 0;
    }

    // Close the temporary file
    close(fd);

    // Open the temporary file for reading
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        perror("fopen");
        unlink(filename);
        return 0;
    }

    // Initialize an igraph object
    igraph_t graph;
    igraph_empty(&graph, 0, IGRAPH_UNDIRECTED);

    // Call the function to be fuzzed with the opened file
    igraph_error_t error = igraph_read_graph_graphdb(&graph, file, IGRAPH_UNDIRECTED);

    // Clean up resources
    fclose(file);
    igraph_destroy(&graph);
    unlink(filename);

    // Return 0 to indicate that the fuzzing input has been processed successfully
    return 0;
}