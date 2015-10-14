#include "viewer.h"
#include "SFML/Audio.h"
#include "SFML/Config.h"
#include "SFML/Graphics.h"
#include "SFML/Network.h"
#include "SFML/OpenGL.h"
#include "SFML/System.h"
#include "SFML/Window.h"
#include <unistd.h>

#include "libft.h"

#include <stdio.h>

int is_on_good_way(int node)
{
  t_ants *ants;

  ants = ft_global(NULL)->ants;
  while (ants)
  {
    if (ants->step == node)
      return (1);
    ants = ants->next;
  }
  return (0);
}

int ft_get_max_longueur(t_ants *ants, int lap)
{
  t_ants  *begin;
  int     max;

  begin = ants;
  max = 0;
  while (ants && ants->lap == lap)
  {
    if (ants->longueur > max)
      max = ants->longueur;
    ants = ants->next;
  }
  while (ants)
  {
    if (ants->longueur == max && ants->i <= (max / 5))
      return (1);

    ants = ants->prev;
  }
  return (0);
}

static void ft_set_key(char *action)
{
  int  zoom;

  zoom = ft_global(NULL)->zoom;
  if (!ft_strcmp("plus", action))
    ft_global(NULL)->zoom = zoom + 10 <= 100 ? zoom + 10 : 100;
  else if (!ft_strcmp("minus", action))
    ft_global(NULL)->zoom = zoom - 10 >= 0 ? zoom - 10 : 0;
  if (ft_global(NULL)->zoom == 100 || ft_global(NULL)->zoom == 0)
    return ;
  calc_ant(ft_global(NULL)->ants);
  ft_get_window();
}

void ft_get_perso()
{
  static int j;

  if (j == 0)
  {
    j++;
    ft_global(NULL)->ant1 = (void *)sfTexture_createFromFile("ressources/img/ant1_red.png", NULL);
    ft_global(NULL)->ant2 = (void *)sfTexture_createFromFile("ressources/img/ant2_red.png", NULL);
  }
  else if (j == 1)
  {
    j++;
    ft_global(NULL)->ant1 = (void *)sfTexture_createFromFile("ressources/img/sacha1.png", NULL);
    ft_global(NULL)->ant2 = (void *)sfTexture_createFromFile("ressources/img/sacha2.png", NULL);
  }
  else if (j == 2)
  {
    j = 0;
    ft_global(NULL)->ant1 = (void *)sfTexture_createFromFile("ressources/img/fb1.png", NULL);
    ft_global(NULL)->ant2 = (void *)sfTexture_createFromFile("ressources/img/fb2.png", NULL);
  }
}

void get_event(sfRenderWindow *window)
{  
  sfEvent event;
  
  /* Process events */
  if (sfRenderWindow_pollEvent(window, &event))
  {
      /* Close window : exit */
      if (event.type == sfEvtClosed || ((event.type == sfEvtKeyPressed) && (event.key.code == sfKeyEscape)))
      {
        sfRenderWindow_close(window);
        exit(0);
      }
      else if ((event.type == sfEvtKeyPressed) && (event.key.code == sfKeySpace))
        ft_get_perso();   
      else if ((event.type == sfEvtKeyPressed) && (event.key.code == sfKeyAdd))
        ft_set_key("plus"); 
      else if ((event.type == sfEvtKeyPressed) && (event.key.code == sfKeySubtract))
        ft_set_key("minus");    
  }
}

t_map *get_node_by_num(int num)
{
  t_map *begin;

  begin = ft_global(NULL);
  while (begin->num != num)
    begin = begin->next;
  return (begin);
}

float absi(float i)
{
  if (i < 0)
    return (-i);
  return (i);
}

void  calc_ant(t_ants *ants)
{
  t_map *map;
  float x1;
  float x2;
  float y1;
  float y2;

  while (ants)
  {
    map = get_node_by_num(ants->start);
    x1 = (map->x * ft_global(NULL)->zoom);
    y1 = (map->y * ft_global(NULL)->zoom);
    map = get_node_by_num(ants->step);
    x2 = (map->x * ft_global(NULL)->zoom);
    y2 = (map->y * ft_global(NULL)->zoom);
    if (absi(x2 - x1) >= absi(y2 - y1))
      ants->longueur = absi(x2 -  x1);
    else
      ants->longueur = absi(y2 - x1);
    ants->dx = ((x2 - x1) / ants->longueur) * 5;
    ants->dy = ((y2 - y1) / ants->longueur) * 5;
    ants->x = x1 + 0.5;
    ants->y = y1 + 0.5;
    ants->i = 1;
    ants = ants->next;
  }
}

t_ants  *print_ant(t_ants *lista, int lap)
{
  t_ants *list;

  list = lista;
  sfRenderWindow_drawSprite((sfRenderWindow *)ft_global(NULL)->window, (sfSprite *)ft_global(NULL)->background, NULL);
  while (list && list->lap == lap)
  {
    if (list->i <= (list->longueur / 5))
    {
      get_event(ft_global(NULL)->window);
      ft_global(NULL)->sprite = (void *)sfSprite_create();
      sfSprite_setTexture((sfSprite *)ft_global(NULL)->sprite, ((int)list->i % 2) ? (sfTexture *)ft_global(NULL)->ant1 : (sfTexture *)ft_global(NULL)->ant2, sfTrue);
      sfSprite_move((sfSprite *)ft_global(NULL)->sprite, (sfVector2f){list->x - 9, list->y - 11});
      sfRenderWindow_drawSprite((sfRenderWindow *)ft_global(NULL)->window, (sfSprite *)ft_global(NULL)->sprite, NULL);
      sfSprite_destroy((sfSprite *)ft_global(NULL)->sprite);
    }
    list->x += list->dx;
    list->y += list->dy;
    list->i++;
    list = list->next;
  }
  sfRenderWindow_display((sfRenderWindow *)ft_global(NULL)->window);
  usleep(SPEED);
  return (lista->i < (lista->longueur / 5) ? lista : list);
}

void  print_them_all(t_ants *list)
{
  int lap;
  t_ants *tmp;

  lap = 0;
  calc_ant(list);
  tmp = list;
  while (tmp)
  {
    while ((tmp = print_ant(tmp, lap)) && tmp->lap == lap)
      ;
    lap++;
  }
}

void draw_line(int node_a, int node_b, sfRenderTexture *texture, sfColor color)
{
  t_map *map;
  sfVertexArray *vertex;
  sfVertex      vert;
  float x, y, x1, x2, y1, y2, dx, dy, i;
  float longueur;

  longueur = 0;
  vertex = sfVertexArray_create();
  map = get_node_by_num(node_a);
  x1 = (map->x * ft_global(NULL)->zoom);
  y1 = (map->y * ft_global(NULL)->zoom);
  map = get_node_by_num(node_b);
  x2 = (map->x * ft_global(NULL)->zoom);
  y2 = (map->y * ft_global(NULL)->zoom);

  if (absi(x2 - x1) >= absi(y2 - y1))
    longueur = absi(x2 -  x1);
  else
    longueur = absi(y2 - x1);
  dx = (x2 - x1) / longueur;
  dy = (y2 - y1) / longueur;
  x = x1 + 0.5;
  y = y1 + 0.5;
  i = 1;
  while (i <= longueur)
  {
    vert.position = (sfVector2f){x, y};
    vert.color = color;
    // vert.texCoords = (sfVector2f){x, y};
    sfVertexArray_append(vertex, vert);
    x = x + dx;
    y = y + dy;
    i++;
  }
  sfRenderTexture_drawVertexArray(texture, vertex, NULL);
}

void ft_update_texture(sfRenderTexture *texture, sfRenderWindow *window)
{
  sfSprite* sprite;
  const sfTexture *f_texture;

  /* Update the texture */
  sprite = sfSprite_create();
  sfRenderTexture_display(texture);
  f_texture = sfRenderTexture_getTexture(texture);
  sfSprite_setTexture(sprite, f_texture, sfTrue);
  ft_global(NULL)->background = sprite;
  sfRenderWindow_drawSprite(window, sprite, NULL);
  sfRenderWindow_display(window);
  ft_global(NULL)->window = (void *)window;
  ft_global(NULL)->sprite = (void *)sprite;
  ft_global(NULL)->f_texture = (void *)f_texture;
}

void draw_background(sfRenderTexture **texture, sfRenderWindow *window, sfCircleShape **circle)
{
  t_links *save;
  t_map *map;

  map = ft_global(NULL);
  /* Clear the screen */
  sfRenderWindow_clear(window, MYBROWN);
  // Clear the texture
  sfRenderTexture_clear(*texture, MYBROWN);
  while (map)
  {
    if (map->links)
      save = map->links;
    while (save)
    {
      draw_line(map->num, save->node, *texture, MYGREY);
      save = save->next;
    }
    map = map->next;
  }
  map = ft_global(NULL);
  while (map)
  {
    sfCircleShape_setPosition(*circle, (sfVector2f){((map->x) * ft_global(NULL)->zoom) - ft_global(NULL)->node_size, ((map->y) * ft_global(NULL)->zoom) - ft_global(NULL)->node_size});
    if (map->start)
      sfCircleShape_setFillColor(*circle, MYGREEN);
    else if (map->end)
      sfCircleShape_setFillColor(*circle, MYBLUE);
    else
      sfCircleShape_setFillColor(*circle, MYGREY);
    if (is_on_good_way(map->num))
    {
      sfCircleShape_setOutlineThickness(*circle, 2.5);
      sfCircleShape_setOutlineColor(*circle, MYBLUE);
    }
    sfRenderTexture_drawCircleShape(*texture, *circle, NULL);
    map = map->next;
  }
}

int ft_init_window(sfRenderTexture **texture, sfCircleShape **circle)
{
  ft_global(NULL)->zoom = ft_global(NULL)->zoom ? ft_global(NULL)->zoom : ZOOM;
  ft_global(NULL)->node_size = ft_global(NULL)->zoom / 3 ? ft_global(NULL)->zoom / 3 : 1;
  if (!(sfRenderWindow *)ft_global(NULL)->window && !texture)
    return (0);
  *circle = sfCircleShape_create();
  sfCircleShape_setRadius(*circle, ft_global(NULL)->node_size);
  // Create the texture
  *texture = sfRenderTexture_create(WIDTH, HEIGHT, 64);
  return (1);
}

int ft_get_window(void)
{
  sfRenderTexture *texture;
  sfRenderWindow *window;
  sfCircleShape *circle;

  window = NULL;
  texture = NULL;
  circle = NULL;
  ft_init_window(&texture, &circle);
  window = (sfRenderWindow *)ft_global(NULL)->window;
  ft_global(NULL)->circle = (void *)circle;
  draw_background(&texture, window, &circle);
  ft_update_texture(texture, window);
  return (1);
}

int test_csfml(void)
{
      sfRenderWindow *window;
      sfVideoMode mode = {WIDTH, HEIGHT, 64};
      
      window = NULL;
      ft_global(NULL)->zoom = 0;
      /* Create the main window */
      ft_global(NULL)->window = (void *)sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
      ft_get_window();
      ft_get_perso();
      window = ft_global(NULL)->window;
      while (sfRenderWindow_isOpen(window))
      {
          print_them_all(ft_global(NULL)->ants);
          break;         
      }
      /* Cleanup resources */
      sfCircleShape_destroy(ft_global(NULL)->circle);
      sfRenderWindow_destroy(window);
      ft_free_struct(ft_global(NULL));

      return (1);
}