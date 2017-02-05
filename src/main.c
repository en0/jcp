/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <irlaird@gmail.com> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.           Ian Laird
 * ----------------------------------------------------------------------------
 */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib-object.h>
#include <json-glib/json-glib.h>

#define LOAD_BUFFER_LIMIT 4096
#define PROGRAM "jcp"

void printNodeValue(JsonNode *node) {
    JsonGenerator *generator = json_generator_new();
    json_generator_set_root(generator, node);
    char *str = json_generator_to_data(generator, NULL);
    g_print("%s\n", str);
    g_object_unref(generator);
}

void showErrorIf(const char *message, GError *error) {
    if (error) {
        g_print("%s: %s\n", message, error->message);
        g_error_free(error);
        exit(EXIT_FAILURE);
    }
}

char* getJsonData(const char* path, ssize_t *size) {

    int fd = 0;

    if(strcmp(path, "-") != 0) {
        fd = open(path, O_RDONLY | O_NONBLOCK);

        if(fd==-1) {
            fprintf(stderr, "Cannot open file: %s", path);
            exit(EXIT_FAILURE);
        }
    }

    char* buffer = (char *)malloc(LOAD_BUFFER_LIMIT);
    ssize_t rc = read(fd, buffer, LOAD_BUFFER_LIMIT);

    if(!strcmp(path, "-"))
        close(fd);

    if(rc == LOAD_BUFFER_LIMIT) {
        fprintf(stderr, "Buffer limit exceeded.");
        free(buffer);
        exit(EXIT_FAILURE);
    } else if(rc==-1) {
        fprintf(stderr, "Cannot read file: %s", path);
        free(buffer);
        exit(EXIT_FAILURE);
    }

    *size = rc;

    return buffer;
}

int main (int argc, char *argv[]) {

    JsonParser *parser;
    GError *error;
    char *buffer;
    ssize_t buffer_size;

    if (argc < 2) {
        g_printf("Usage: %s JSONPath [PATH]\n", PROGRAM);
        g_printf("Example: %s '$.name' file.json\n", PROGRAM);
        return EXIT_FAILURE;
    } else if(argc == 2)
        buffer = getJsonData("-", &buffer_size);
    else
        buffer = getJsonData(argv[2], &buffer_size);

    g_type_init();

    parser = json_parser_new();

    error = NULL;
    json_parser_load_from_data (parser, buffer, buffer_size, &error);
    free(buffer);

    showErrorIf("Bad json data", error);

    JsonNode *root = json_parser_get_root(parser);
    JsonNode *matches = json_path_query(argv[1], root, &error);

    showErrorIf("Bad path selector", error);

    JsonArray *nodeArray = json_node_get_array(matches);

    int arrayLen = json_array_get_length(nodeArray);
    for(int i = 0; i < arrayLen; i++)
        printNodeValue(json_array_get_element(nodeArray, i));

    return EXIT_SUCCESS;
}
