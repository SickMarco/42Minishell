/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protoparser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 09:28:40 by mabaffo           #+#    #+#             */
/*   Updated: 2023/02/20 10:54:23 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

while (1) 
{
    char *line = malloc(128); // we need to be able to increase the pointer
    char *origLine = line;
    fgets(line, 128, stdin);

    char command[20];
    sscanf(line, "%20s ", command);

    line = strchr(line, ' ');

    printf("The Command is: %s\n", command);

    unsigned argumentsCount = 0;
    char **arguments = malloc(sizeof(char *));

    while (1)
    {
        char arg[20];
        if (line && (sscanf(++line, "%20s", arg) == 1))
        {
            arguments[argumentsCount] = malloc(sizeof(char) * 20);
            strncpy(arguments[argumentsCount], arg, 20);

            argumentsCount++;

            arguments = realloc(arguments, sizeof(char *) * argumentsCount + 1);
            line = strchr(line, ' ');
        }
        else {
            break;
        }
    }

    for (int i = 0; i < argumentsCount; i++) {
        printf("Argument %i is: %s\n", i, arguments[i]);
    }

    for (int i = 0; i < argumentsCount; i++) {
        free(arguments[i]);
    }

    free(arguments);
    free(origLine);
}  
