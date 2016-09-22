#ifndef PARSER_H
#define PARSER_H

#define SHELL_MAX_ARGS 30

/* Allow c++ to link */
#ifdef __cplusplus
extern "C" {
#endif

struct command
{
        /* Pointer to an array of pointers to strings, one per argument,
         * with an additional NULL pointer after the last argument to
         * mark the end of the argument list.
         */
        char *args[SHELL_MAX_ARGS + 1];

        /* File to redirect stdin from, or NULL for no redirection. */
        char *in_redir;

        /* File to redirect stdout to, or NULL for no redirection. */
        char *out_redir;
};

void free_command(struct command *cmd);
//static char *Strdup(const char *s);
//static struct command *alloc_command(void);
struct command *parse_command(const char *cmdline);

#ifdef __cplusplus
} /* matches extern "C" */
#endif

#endif
