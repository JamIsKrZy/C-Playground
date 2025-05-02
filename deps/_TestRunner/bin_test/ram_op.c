#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *filepath = "/mnt/tmp-file/my_config.txt";

    // Write data to file
    FILE *fp = fopen(filepath, "w");
    if (!fp) {
        perror("Failed to open file for writing");
        return 1;
    }
    fprintf(fp, "stored_in_ram=1\n");
    fclose(fp);

    // Reopen and read data
    fp = fopen(filepath, "r");
    if (!fp) {
        perror("Failed to open file for reading");
        return 1;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp)) {
        printf("Read line: %s", buffer);
    }
    fclose(fp);

    return 0;
}
