#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void list_files(const char *path, size_t indent) {
    struct dirent *entry;
    DIR *dir = opendir(path);
    char buffer[255];

    if (dir == NULL) {
        perror("Unable to open directory ");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {

            // printf("%*s", (int)(indent * 4), "");
            // printf("%s - [Type: %u]\n", entry->d_name, entry->d_type);

            if(entry->d_type == 4){


                char buffer[255];

                snprintf(buffer, sizeof(buffer), "%s/%s", path, entry->d_name);
                printf("%*s", (int)(indent * 4), "");
                printf("📂%s - \"%s\"]{\n", entry->d_name, buffer);

                list_files(buffer, indent+1);

                printf("%*s", (int)(indent * 4), "");
                printf("}\n");
            } else {

                printf("%*s", (int)(indent * 4), "");
                printf("📃%s\n", entry->d_name);
            }
        }
    }

    closedir(dir);
}

int main(int argc, char const *argv[])
{
    const char *file_dir = ".";
    list_files(file_dir, 0); 
    return 0;
}
