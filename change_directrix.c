#include "header.h"

bool hop(char *command)
{
    char *temp = decode_path(command);
    if (chdir(temp) != 0)
    {
        perror("hop");
        if (command[0] == '~' && strlen(command) != 1)
            free(temp);
        return false;
    }
    else
    {
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            printf("%s\n", cwd);
        }
        else
        {
            perror("getcwd");
        }
        if (command[0] == '~' && strlen(command) != 1)
            free(temp);
        return true;
    }
    return false;
}

bool cd(char *command)
{
    char *temp = decode_path(command);
    if (chdir(temp) != 0)
    {
        perror("cd");
        if (command[0] == '~' && strlen(command) != 1)
            free(temp);
        return false;
    }
    else
    {
        if (command[0] == '~' && strlen(command) != 1)
            free(temp);
        return true;
    }
}

void hop_handler(char *pipe, int flag_read, char *in_file)
{
    char *command = strtok(pipe, " \t");
    command = strtok(NULL, " \t");
    if (command == NULL)
    {
        char previous_dir2[PATH_MAX];
        getcwd(previous_dir2, PATH_MAX);
        if (hop(home_path))
        {
            char prev3[PATH_MAX];
            getcwd(prev3, PATH_MAX);
            if (strcmp(prev3, previous_dir2) != 0)
                strcpy(previous_dir, previous_dir2);
        }
    }
    while (command != NULL && strcmp(command, ">>") != 0 && strcmp(command, ">") != 0 && strcmp(command, "<") != 0)
    {
        char previous_dir2[PATH_MAX];
        getcwd(previous_dir2, PATH_MAX);
        if (hop(command))
        {
            char prev3[PATH_MAX];
            getcwd(prev3, PATH_MAX);
            if (strcmp(prev3, previous_dir2) != 0)
                strcpy(previous_dir, previous_dir2);
        }
        command = strtok(NULL, " \t");
    }
    if (flag_read)
    {
        printf("Invalid use of redirection!!\n");
    }
}

void cd_handler(char *pipe, int flag_read, char *in_file)
{
    if (!flag_read)
    {
        char *command = strtok(pipe, " \t");
        command = strtok(NULL, " \t");
        if (command == NULL)
        {
            char previous_dir2[PATH_MAX];
            getcwd(previous_dir2, PATH_MAX);
            if (cd(home_path))
            {
                char prev3[PATH_MAX];
                getcwd(prev3, PATH_MAX);
                if (strcmp(prev3, previous_dir2) != 0)
                    strcpy(previous_dir, previous_dir2);
            }
        }
        while (command != NULL && strcmp(command, ">>") != 0 && strcmp(command, ">") != 0 && strcmp(command, "<") != 0)
        {
            char previous_dir2[PATH_MAX];
            getcwd(previous_dir2, PATH_MAX);
            if (cd(command))
            {
                char prev3[PATH_MAX];
                getcwd(prev3, PATH_MAX);
                if (strcmp(prev3, previous_dir2) != 0)
                    strcpy(previous_dir, previous_dir2);
            }
            command = strtok(NULL, " \t");
        }
    }
    else
    {
        printf("Invalid use of redirection!!\n");
    }
}