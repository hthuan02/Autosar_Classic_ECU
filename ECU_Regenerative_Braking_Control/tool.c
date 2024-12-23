#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

typedef struct {
    char name[256];
    int level;
    int is_dir;
    char full_path[1024];
} DirectoryEntry;

int is_directory(const char *path) {
    DWORD attribs = GetFileAttributes(path);
    if (attribs == INVALID_FILE_ATTRIBUTES) {
        return 0;
    }
    return (attribs & FILE_ATTRIBUTE_DIRECTORY);
}

int read_directory(const char *dir_name, int level, DirectoryEntry *entries, int entry_count) {
    WIN32_FIND_DATA find_data;
    HANDLE hFind;
    char search_path[1024];

    snprintf(search_path, sizeof(search_path), "%s\\*", dir_name);
    hFind = FindFirstFile(search_path, &find_data);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Error opening directory: %s\n", dir_name);
        return entry_count;
    }

    do {
        if (strcmp(find_data.cFileName, ".") != 0 && strcmp(find_data.cFileName, "..") != 0) {
            char path[1024];
            snprintf(path, sizeof(path), "%s\\%s", dir_name, find_data.cFileName);

            strcpy(entries[entry_count].name, find_data.cFileName);
            entries[entry_count].level = level;
            entries[entry_count].is_dir = is_directory(path);
            strcpy(entries[entry_count].full_path, path);
            entry_count++;

            if (entries[entry_count - 1].is_dir) {
                entry_count = read_directory(path, level + 1, entries, entry_count);
            }
        }
    } while (FindNextFile(hFind, &find_data) != 0);

    FindClose(hFind);
    return entry_count;
}

int has_h_extension(const char *filename) {
    const char *dot = strrchr(filename, '.');
    return (dot && strcmp(dot, ".h") == 0);
}

int has_c_extension(const char *filename) {
    const char *dot = strrchr(filename, '.');
    return (dot && strcmp(dot, ".c") == 0 && strcmp(filename, "tool.c") != 0);
}

int directory_exists(char dirs[100][1024], int dir_count, const char *dir) {
    int i;
    for (i = 0; i < dir_count; i++) {
        if (strcmp(dirs[i], dir) == 0) {
            return 1;  // Directory already exists
        }
    }
    return 0;
}

int add_unique_directory(char dirs[100][1024], int dir_count, const char *dir) {
    if (!directory_exists(dirs, dir_count, dir)) {
        strcpy(dirs[dir_count], dir);
        dir_count++;
    }
    return dir_count;
}

void write_cflags(FILE *fp, DirectoryEntry *entries, int entry_count) {
    char dirs[100][1024];
    int dir_count = 0;
    int i;
    for (i = 0; i < entry_count; i++) {
        if (!entries[i].is_dir && has_h_extension(entries[i].name)) {
            char dir[1024];
            strncpy(dir, entries[i].full_path, strrchr(entries[i].full_path, '\\') - entries[i].full_path);
            dir[strrchr(entries[i].full_path, '\\') - entries[i].full_path] = '\0';
            dir_count = add_unique_directory(dirs, dir_count, dir);
        }
    }

    for (i = 0; i < dir_count; i++) {
        if (i == dir_count - 1) {
            fprintf(fp, "-I%s\n", dirs[i]);
        } else {
            fprintf(fp, "-I%s\\\n", dirs[i]);
        }
    }
}

void write_sources(FILE *fp, DirectoryEntry *entries, int entry_count) {
    fprintf(fp, "\nSRC = ");
    int first = 1;
    int i;
    for (i = 0; i < entry_count; i++) {
        if (!entries[i].is_dir && has_c_extension(entries[i].name)) {
            if (!first) {
                fprintf(fp, " \\\n");
            }
            fprintf(fp, "%s", entries[i].full_path);
            first = 0;
        }
    }
    fprintf(fp, " \n\n");
}

void create_makefile(DirectoryEntry *entries, int entry_count) {
    FILE *fp = fopen("Makefile", "w");
    if (fp == NULL) {
        exit(1);
    }

    fprintf(fp, "# Compiler and flags\n"
                "CC = gcc\n"
                "CFLAGS = -Wall -g\\\n");

    write_cflags(fp, entries, entry_count);

    fprintf(fp, "# Object directory\n"
                "OBJDIR = bin\n"
                "# Executable\n"
                "TARGET = $(OBJDIR)/ecu\n");

    write_sources(fp, entries, entry_count);

    fprintf(fp, "# Object files\n"
                "OBJ = $(SRC:%%.c=$(OBJDIR)/%%.o)\n\n"
                "# Build executable\n"
                "$(TARGET): $(OBJ)\n"
                "\t@echo \"Linking all objects to create $(TARGET)...\"\n"
                "\t$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)\n"
                "\t@echo \"Build successful!\"\n\n"
                "# Compile object files\n"
                "$(OBJDIR)/%%.o: %%.c\n"
                "\t@mkdir -p $(dir $@)\n"
                "\t$(CC) $(CFLAGS) -c $< -o $@\n"
                "\t@echo \"Compiled: $<\"\n\n"
                "# Clean up\n"
                ".PHONY: clean\n"
                "clean:\n"
                "\t@echo \"Cleaning up...\"\n"
                "\trm -rf $(OBJDIR)\n"
                "\t@echo \"Clean done!\"\n\n"
                "# Run program\n"
                ".PHONY: run\n"
                "run: $(TARGET)\n"
                "\t@echo \"Running program...\"\n"
                "\t$(TARGET)\n");

    fclose(fp);
}

void call_terminal() {
    system("make clean");
    system("make run");
}

int main() {
    int entry_count = 0;
    DirectoryEntry entries[100];

    entry_count = read_directory(".", 0, entries, entry_count);

    create_makefile(entries, entry_count);

    call_terminal();

    return 0;
}
