#ifndef PARSE_H
#define PARSE_H

//PARSE//
int		ft_check_file(t_scene scene, char *file);

//PARSE_UTILS//
void	ft_skipspace(char *str);
int		ft_comma(char *str);
t_color	ft_get_color(char *str);

#endif 
