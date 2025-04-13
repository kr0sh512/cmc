#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <linux/limits.h>
#include <time.h>

int
main(int argc, char **argv)
{
    if (argc < 2) {
        return 1;
    }

    char script_template[] = "#!/usr/bin/env python3\n"
                             "import os\n"
                             "print(";
    char script_end[] = ")\n"
                        "os.remove(__file__)\n";

    size_t script_size = strlen(script_template) + strlen(script_end) + 1;
    for (int i = 1; i < argc; i++) {
        script_size += strlen(argv[i]) + 1;
    }

    char *script_content;
    if (!(script_content = malloc(script_size))) {
        return 1;
    }

    strcpy(script_content, script_template);

    for (int i = 1; i < argc; i++) {
        strcat(script_content, argv[i]);

        if (i < argc - 1) {
            strcat(script_content, "*");
        }
    }

    strcat(script_content, script_end);

    char *tmpdir = getenv("XDG_RUNTIME_DIR");
    if (!tmpdir) {
        tmpdir = getenv("TMPDIR");

        if (!tmpdir) {
            tmpdir = "/tmp";
        }
    }

    char script_path[PATH_MAX];
    int r = snprintf(script_path, sizeof(script_path), "%s/%d", tmpdir, (int) (getpid() * time(NULL) % 1000000));
    if (r < 0 || r > PATH_MAX) {
        exit(1);
    }

    int fd = open(script_path, O_RDWR | O_CREAT | O_EXCL, 0600);
    if (fd == -1) {
        free(script_content);
        return 1;
    }

    FILE *script_file = fdopen(fd, "w");
    if (!script_file) {
        close(fd);
        unlink(script_path);
        free(script_content);
        return 1;
    }

    fprintf(script_file, "%s", script_content);
    fclose(script_file);
    free(script_content);

    if (chmod(script_path, 0700) == -1) {
        unlink(script_path);
        return 1;
    }

    execl(script_path, script_path, (char *) NULL);
    unlink(script_path);

    return 1;
}
