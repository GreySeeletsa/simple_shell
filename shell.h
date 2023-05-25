#ifndef SHELL_H
#define SHELL_H

#define END_OF_FILE -2
#define EXIT -3
#include <limits.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>

/*DATA STRUCTURES*/

/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
char *dir;
struct list_s *next;
} list_t;


/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
char *name;
int (*f)(char **argv, char **front);
} builtin_t;


/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 * alias_t - Global aliases linked list
 */
typedef struct alias_s
{
char *name;
char *value;
struct alias_s *next;

} alias_t;

alias_t *aliases;

/**
 * struct data_shell - Shell data structure
 * @dir: A pointer to a character array representing the current directory
 * @in_home: Flag indicating whether the current directory is within
 * the home directory
 * @in_home2: Flag or indicator related to the current directory's location
 * @is_ddash: Flag to check if the command or input includes a double dash (--)
 * @args: Check argument input
 * @ustatus: current directory, flags, and other relevant information.
 */
typedef struct data_shell
{
char *dir;
int in_home;
int in_home2;
int is_ddash;
unsigned int ustatus;
char args;
} data_shell;

/**
 *struct ino_t - Custom data structure for managing file descriptors.
 *@readfd: Integer variable representing a file descriptor for reading data.
 */
typedef struct ino_t
{
int readfd;
} my_ino_t;

/* FILE PROTOTYPES/ FUNCTIONS*/

/* interactive_shell.c */
int shell_interactive(my_ino_t *);
int is_delimiter(char, char *);
int is_alpha(int);
int string_to_int(char *);

/* getline prototype */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);

/*var_replacement prototypes */
int is_chain_command(ino_t *, char *, size_t *);
void check_chain_command(ino_t *, char *, size_t *, size_t, size_t);
int replace_alias_command(ino_t *);
int replace_variables(ino_t *);
int replace_string_content(char **, char *);


/*builtin_exit prototypes*/
int exit_shell(data_shell *datash);
int is_valid_status(unsigned int status);


/*exit.c prototypes */
void help_exit(void);


/* getline.c prototype */
void handle_line(char **line, ssize_t read);


/* History.c Prototypes. */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *get_location(char *command);
list_t *get_path_dir(char *path);
void help_history(void);

/* builtin_alias.c prototypes */
int shellby_alias(char **args, char __attribute__((__unused__)) **front);
char set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);
char **replace_aliases(char **args);
alias_t *add_alias_end(alias_t **head, char *name, char *value);
/*list_t *add_node_end(list_t **head, char *dir);*/
/*void free_alias_list(void);*/
void help_alias(void);

/* arg.c prototypes */
char *get_args(char *line, int *exe_ret);
int call_args(char **args,int *exe_ret);
int run_args(char **args, int *exe_ret);
void free_args(char **args,char **front);

/*args1.c prototype*/
int handle_args(int *exe_ret);
int check_args(char **args);


/* setenv.c prototypes */
int shellby_env(char **args, char __attribute__(
(__unused__)) **front, char **environ);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);


/* env_builtin.c prototypes */
int (*get_builtin(char *command))(char **args, char **front);
void help_env(void);


/* seperator.c */
void handle_line(char **line, ssize_t read);
ssize_t get_new_len(char *line);
void logical_ops(char *line, ssize_t *new_len);


/* builtin.c prototypes */
int shellby_cd(char **args, char __attribute__((__unused__)) **front);
int shellby_exit(char **args);
int shellby_help(char **args, char __attribute__((__unused__)) **front);
int cd_shell(data_shell *datash);
int shellby_help(char **args, char __attribute__((__unused__)) **front);

/* seperator.c*/
int num_len(int num);
char *_itoa(int num);
int create_error(char **args, int err);

/*commits.c (error_ Handling) */
int create_error(char **args, int err);
char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
char *error_126(char **args);
char *error_127(char **args);

/* String functions */
int _strlen(const char *s);
char *strcat(char *dest, const char *src);
char *strncat(char *dest, const char *src, size_t n);
char *strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char **strings(char **env);

/* linkedlist.c */
alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);




/* builtin_ helper*/
void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);

/* error.c prototype */
int num_len(int num);
char *_itoa(int num);
int create_error(char **args, int err);

int execute(char **args);

int proc_file_commands(char *file_path, int *exe_ret);

#endif  /* SHELL_H */
