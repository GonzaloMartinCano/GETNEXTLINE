/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:47:48 by gmartin-          #+#    #+#             */
/*   Updated: 2019/12/04 14:35:39 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*ft_del(char *ptr)							// con esta función liberamos y ponemos en null el auxiliar una ve que se ha usado
{															// lo hemos hecho aqui porque no cabia en la función ft_line
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (ptr);
}

static int		ft_return(int len, char **line)				// con esta funcion retornamos -1 o 0 cuando la lectura ha llegado al final o ha sido erronea en get_next_line
{
	if (len < 0)
		return (-1);
	*line = ft_strdup("");
	return (0);
}

static char		*ft_line(char *auxfd, char **line, int *len)  
{
	int		pos;
	char	*temp;

	pos = 0;
	while (auxfd[pos] != '\n' && auxfd[pos] != '\0')		//recorremos el aux para saber su tamaño
		pos++;
	if (auxfd[pos] == '\n')									// si la posición final fuera un salto de linea
	{
		*line = ft_substr(auxfd, 0, pos);					// copiamos el contenido de auxiliar en *line
		temp = ft_strdup(auxfd + (pos + 1));				// pasamos a un temporal lo que haya despues del salto de linea hasta el final para que se quede preparado para la siguiente llamada y copia de contenido
		free(auxfd);										// liberamos el auxiliar con el contenido que traiamos incialmente, lo que habia hasta el salto de linea
		auxfd = temp;										// metemos en auxiliar el contenido siguiente que intentaremos pasar a *line
		if (auxfd[0] == '\0')								// si el nuevo contenido de auxiliar trajera un \0 habriamos llegado al final
			auxfd = ft_del(auxfd);							// borramos y liberamos el axuliar con ft_del y lo dejamos apuntando a NULL
		*len = 1;											// Marcamos len como 1, para que cuando retorne en get_next_line de 1 como que ha leido una linea
	}
	else													// si no hubiera ningun salto de linea
	{
		*line = ft_strdup(auxfd);							// solamente copiamos el contenido de auxiliar en *line
		free(auxfd);										// liberamos el auxiliar
		auxfd = NULL;										// apuntamos auxiliar a NULL
		*len = 0;											// ponemos len a 0, para que cuando retorne en get_next_line de 0 y sepamos que estamos en el final
	}
	return (auxfd);											// retorna aux vacio si estamos al final, o lleno y preparado para la siguiente copia si aun no hemos llegado
}

int				get_next_line(int fd, char **line)
{
	static char *auxfd[4096];
	char		*buff;
	int			len;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1)          //Comprobaciones para fd vacio, line vacio o buffersize 0 que daria errores
		return (-1);										
	if (!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))	//reserva de memoria para buff, donde vamos a guardar cada lectura de buffer
		return (-1);
	while ((len = read(fd, buff, BUFFER_SIZE)) > 0)			// Leemos con read el fd y vamos guardando lo que hayamos sido capaces de leer con el tamaño BUFERSIZE en buff
	{														// si no hay un fallo de lectura, read retorna -1, si ha llegado al final 0. Si lee retorna la cantidad de bits que ha leido.	
		buff[len] = '\0';									// Como tenemos la cantidad de bits copiados, ponemos el nulo al final de lo que hemos copiado en buff
		if (auxfd[fd] == NULL)								// Si es la primera vez que vamos a copiar al auxiliar que hemos creado este tendra valor null, por lo que solo copiamos lo que tenemos en buff sobre el auxiliar
			auxfd[fd] = ft_strdup(buff);					// Metemos en el auxiliar creado lo que tenemos en buff
		else
			auxfd[fd] = ft_strjoin(auxfd[fd], buff);		// Si ya habiamos copiado antes, el auxiliar tendra contenido, por lo que pasara por aqui y concatenamos el nuevo contenido de buff a lo que ya teniamos en auxiliar. es importante recordar que tenemos que liberar la memoria del anterior auxiliar ya que creamos otro nuevo en otra dirección, esto lo hacemos en ft_strjoin liberando s1
		if (ft_strchr(auxfd[fd], '\n'))						// Este if lo ponemos para que pare de copiar en el momento que encuentre un salto de linea
			break ;
	}
	free(buff);												// Liberamos el buff que ha quedad con memoria llena
	if ((len < 0) || (len == 0 && auxfd[fd] == NULL))		// Si la lectura(len) viniera con error (-1) o hubiera terminado (0) hacemos que retonrne con ft_return ese valor.
		return (ft_return(len, line));
	auxfd[fd] = ft_line(auxfd[fd], line, &len);				// En caso de que la lectura sea correcta y aun no haya terminado hacemos ft_line para ir guardando en **line tal como se pide
	return (len);											// retornamos len (0 o 1) en funcion de lo que retorne ft_line, 1 si hemos leido una linea, 0 si hemos terminado de leer.
}
