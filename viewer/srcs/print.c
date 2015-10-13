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
    x1 = (map->x * ZOOM);
    y1 = (map->y * ZOOM);
    map = get_node_by_num(ants->step);
    x2 = (map->x * ZOOM);
    y2 = (map->y * ZOOM);
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
    ft_global(NULL)->sprite = (void *)sfSprite_create();
    sfSprite_setTexture((sfSprite *)ft_global(NULL)->sprite, ((int)list->i % 2) ? (sfTexture *)ft_global(NULL)->ant1 : (sfTexture *)ft_global(NULL)->ant2, sfTrue);
    sfSprite_move((sfSprite *)ft_global(NULL)->sprite, (sfVector2f){list->x - 16, list->y - 50});
    sfRenderWindow_drawSprite((sfRenderWindow *)ft_global(NULL)->window, (sfSprite *)ft_global(NULL)->sprite, NULL);
    sfSprite_destroy((sfSprite *)ft_global(NULL)->sprite);
    list->x += list->dx;
    list->y += list->dy;
    list->i++;
    list = list->next;
  }
  sfRenderWindow_display((sfRenderWindow *)ft_global(NULL)->window);
  usleep(SPEED);
  return (lista->i <= (lista->longueur / 5) ? lista : list);
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

void draw_line(int node_a, int node_b, sfRenderTexture *texture)
{
  t_map *map;
  sfVertexArray *vertex;
  sfVertex      vert;
  float x, y, x1, x2, y1, y2, dx, dy, i;
  float longueur;

  longueur = 0;
  vertex = sfVertexArray_create();
  map = get_node_by_num(node_a);
  x1 = (map->x * ZOOM);
  y1 = (map->y * ZOOM);
  map = get_node_by_num(node_b);
  x2 = (map->x * ZOOM);
  y2 = (map->y * ZOOM);

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
    vert.color = (sfColor){150, 150, 150, 100};
    // vert.texCoords = (sfVector2f){x, y};
    sfVertexArray_append(vertex, vert);
    x = x + dx;
    y = y + dy;
    i++;
  }
  sfRenderTexture_drawVertexArray(texture, vertex, NULL);
}

int test_csfml(void)
{
      sfVideoMode mode = {WIDTH, HEIGHT, 64};
      sfRenderWindow* window;
      sfRenderWindow* window_save;
      sfEvent event;
      sfCircleShape *circle;
      t_map *map;
      t_ants *ants;
      t_links *save;
      sfRenderTexture *texture;
      const sfTexture *f_texture;
      sfSprite* sprite;

      map = ft_global(NULL);
      circle = sfCircleShape_create();
      sfCircleShape_setRadius(circle, NODE_SIZE);
      
      int i = 0;

      /* Create the main window */
      window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
      // Create the texture
      texture = sfRenderTexture_create(WIDTH, HEIGHT, 64);
      ft_global(NULL)->ant1 = (void *)sfTexture_createFromFile("ressources/img/mario1.png", NULL);
      ft_global(NULL)->ant2 = (void *)sfTexture_createFromFile("ressources/img/mario2.png", NULL);
      if (!window && !texture)
          return (0);
  
          /* Clear the screen */
          sfRenderWindow_clear(window, sfBlack);
          // Clear the texture
          sfRenderTexture_clear(texture, sfBlack);
          while (map)
          {
            if (map->links)
              save = map->links;
            while (save)
            {
              draw_line(map->num, save->node, texture);
              save = save->next;
            }
            map = map->next;
          }
          map = ft_global(NULL);
          while (map)
          {
            sfCircleShape_setPosition(circle, (sfVector2f){((map->x) * ZOOM) - NODE_SIZE, ((map->y) * ZOOM) - NODE_SIZE});
            if (map->start)
              sfCircleShape_setFillColor(circle, (sfColor){189, 181, 9, 255});
            else if (map->end)
              sfCircleShape_setFillColor(circle, (sfColor){9, 189, 89, 255});
            else
              sfCircleShape_setFillColor(circle, (sfColor){9, 157, 179, 255});
            sfRenderTexture_drawCircleShape(texture, circle, NULL);
            map = map->next;
          }

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
      while (sfRenderWindow_isOpen(window))
      {
          /* Process events */
          if (sfRenderWindow_pollEvent(window, &event))
          {
              /* Close window : exit */
              if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
              else if ((event.type == sfEvtKeyPressed) && (event.key.code == sfKeyEscape))
                sfRenderWindow_close(window);
          }
          print_them_all(ft_global(NULL)->ants);
          sleep(2);
          break;         
      }
      sfCircleShape_destroy(circle);

      /* Cleanup resources */
      sfRenderWindow_destroy(window);

      return (1);
}