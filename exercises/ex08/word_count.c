#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#define BUFFER_SIZE 2048
#define FILE_NAME "the_double_search.txt"
#define PUNCTUATION "\n\\“-,$%^&*!@#\\_.;:()'/\""

void print(gpointer key, gpointer value, gpointer meta_data) {
    printf("%s: %d\n", (char *) key, GPOINTER_TO_INT(value));
}

gchar *remove_punctuations(gchar *word) {
    return g_strdelimit(word, PUNCTUATION, '\0');
}

int main(int argc, char **argv) {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        exit(1);
    }

    GHashTable *hash = g_hash_table_new(g_str_hash, g_str_equal);
    gchar word[BUFFER_SIZE];
    gpointer value;
    gchar *key;

    while (fscanf(file, "%2048s", word) == 1) {
        key = remove_punctuations(word);
        value = g_hash_table_lookup(hash, key);
        if (value) {
            value = GINT_TO_POINTER(GPOINTER_TO_INT(value) + 1);
        } else {
            value = GINT_TO_POINTER(1);
        }
        g_hash_table_insert(hash, g_strdup(key), value);
    }
    fclose(file);
    g_hash_table_foreach(hash, print, NULL);
}
