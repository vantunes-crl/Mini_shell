#This project is one of the projects of the 42 school which consists in imitating the linux bash.
##Mini_shell
Your shell should:
 

 - [x]  Not interpret unclosed quotes or unspecified special characters
       like \ or;.
 - [x] • Show a prompt when waiting for a new command.
 - [x] • Have a working History.
 - [x] • Search and launch the right executable (based on the PATH
       variable or by using relative or absolute path)
• It must implement the builtins:
 - [x] ◦ echo with option -n
 - [x] ◦ cd with only a relative or absolute path
 - [x] ◦ pwd with no options
 - [x] ◦ export with no options
 - [x] ◦ unset with no options
 - [x] ◦ env with no options or arguments 
 - [x] ◦ exit with no options
 - [x] • ’ inhibit all interpretation of a sequence of characters.
 - [x] • " inhibit all interpretation of a sequence of characters except
       for $.
 - • Redirections:
 - [x] ◦ < should redirect input.
 - [x] ◦ > should redirect output.
 - [x] ◦ “<<” read input from the current source until a line containing
       only the de- limiter is seen. it doesn’t need to update history!
 - [x] ◦ “>>” should redirect output with append mode.
 - [x] • Pipes | The output of each command in the pipeline is connected
       via a pipe to the input of the next command.
 - [X] • Environment variables ($ followed by characters) should expand
       to their values.
 - [X] • $? should expands to the exit status of the most recently
       executed foreground pipeline.
 - [x] • ctrl-C ctrl-D ctrl-\ should work like in bash.
• When interactive:
 - [x] ◦ ctrl-C print a new prompt on a newline.
 - [X] ◦ ctrl-D exit the shell. ◦ ctrl-\ do nothing.
